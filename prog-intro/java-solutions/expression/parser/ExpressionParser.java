package expression.parser;


import expression.*;

public final class ExpressionParser  implements TripleParser {



    public Expressions parse(final String source) {
        return parse(new StringSource(source));
    }

    public static Expressions parse(final CharSource source) {

        return new Parser(source).parseAll();
    }

    private static class Parser extends BaseParser {
        public Parser(final CharSource source) {
            super(source);
        }
        private void skipWhitespace() {
            String dict = "()+-*/^~&|\0";

            while (!(between('0', '9') || between('x', 'z') || dict.contains(String.valueOf(getCh())))) {
                take();
            }
        }

        private Expressions parseAll() {
            return parseOr();
        }

        private Expressions parseOr() {
            Expressions res = parseXor();
            while (true){
                skipWhitespace();
                if (take('|')) {
                    res = new Or(res, parseXor());
                } else {
                    return res;
                }
            }
        }

        private Expressions parseXor() {
            Expressions res = parseAnd();
            while (true){
                skipWhitespace();
                if (take('^')) {
                    res = new Xor(res, parseAnd());
                } else {
                    return res;
                }
            }
        }

        private Expressions parseAnd() {
            Expressions res = parseAdd();
            while (true){
                skipWhitespace();
                if (take('&')) {
                    res = new And(res, parseAdd());
                } else {
                    return res;
                }
            }
        }

        private Expressions parseAdd() {
            Expressions res =  parseMultiply();
            while (true){
                skipWhitespace();
                if (take('-')) {
                    res = new Subtract(res, parseMultiply());
                } else if (take('+')) {
                    res = new Add(res, parseMultiply());
                } else {
                    return res;
                }
            }
        }

        private Expressions parseMultiply() {
            Expressions res =  parseUnaryMines();
            while (true){
                skipWhitespace();
                if (take('/')) {
                    res = new Divide(res, parseUnaryMines());
                } else if (take('*')) {
                    res = new Multiply(res, parseUnaryMines());
                } else {
                    return res;
                }
            }
        }

        private Expressions parseUnaryMines() {
            skipWhitespace();
            if (take('-')) {
                if (take('(')){
                    Expressions res = parseAll();
                    expect(')');
                    return new UnaryMines(res);
                }
                return UnaryMines.createUnaryMines(parseExpression());
            } else if (take('~')) {
                if (take('(')){
                    Expressions res = parseAll();
                    expect(')');
                    return new UnaryNot(res);
                }
                return new UnaryNot(parseExpression());
            }
            return parseExpression();
        }

        private Expressions parseExpression() {
            skipWhitespace();
            if (take('(')) {
                Expressions res = parseAll();
                expect(')');
                return res;
            } else if (between('x', 'z')) {
                return parseVar();
            } else if (between('0', '9')) {
                return parseConst();
            } else if (take('-')) {
                return UnaryMines.createUnaryMines(parseExpression());
            } else if (take('~')) {
                return new UnaryNot(parseExpression());
            } else {
                throw error("Incorrect input");
            }
        }

        private StringBuilder takeDigits() {
            StringBuilder sb = new StringBuilder();
            while (between('0', '9')) {
                sb.append(take());
            }
            return sb;
        }

        private Expressions parseConst() {
            StringBuilder sb = takeDigits();
            if (sb.toString().equals("2147483648")) {
                return new Const(Integer.MIN_VALUE);
            }
            return new Const(Integer.parseInt(sb.toString()));
        }

        private Expressions parseVar() {
            char var = take();
            return new Variable(String.valueOf(var));
        }
    }
}
