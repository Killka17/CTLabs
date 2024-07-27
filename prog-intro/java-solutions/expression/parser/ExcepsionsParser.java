package expression.parser;


import expression.*;
import expression.Variable;
import expression.exceptions.*;


public final class ExcepsionsParser implements TripleParser {

    static boolean parenthesisFlag;
    public Expressions parse(final String source) {
        int left = 0;
        int right = 0;
        for (int i = 0; i < source.length(); i++) {
            if (source.charAt(i) == '(') {
                left++;
            } else if (source.charAt(i) == ')') {
                right++;
            }
        }
        parenthesisFlag = left == right;
        return parse(new StringSource(source));
    }
    public static boolean getF(){
        return parenthesisFlag;
    }


    public static Expressions parse(final CharSource source) {
        return new Parser(source).parseAll();
    }


    private static class Parser extends BaseParser {
        public Parser(final CharSource source) {
            super(source);
            checker();
        }
        String badSymbols = "%<>[]@";
        private void skipWhitespace() {
            if (Character.isUpperCase(getCh()) || badSymbols.contains(String.valueOf(getCh()))) {
                throw error("Incorrect input: Symbol:" + getCh());
            }
            while (take(' ') || take('\r') || take('\n') || take('\t') ||
                    take('\u000B') || take('\u2029') || take('\f')){
            }
        }


        private Expressions parseExpression() {
            skipWhitespace();
            if (take('(')) {
                Expressions res = parseAll();
                skipWhitespace();
                expect(')');
                return res;
            } else if (between('x', 'z')) {
                return parseVar();
            } else if (between('0', '9')) {
                return parseConst();
            } else if (take('-')) {
                return UnaryMines.createUnaryMines(parseExpression());
            } else if (take('l')) {
                expect("og2");
                return new CheckedLog(parseExpression());
            } else if (take('p')) {
                expect("ow2");
                return new CheckedPow(parseExpression());
            } else {
                throw error("Incorrect input");
            }
        }

        private Expressions parseAll() {
            skipWhitespace();
            Expressions res = parseAdd();
            return res;
        }

        private void checker() {
            if (!getF()) {
                throw error("incorrect parenthesis sequence");
            }
        }

        private Expressions parseAdd() {
            Expressions res =  parseMultiply();
            while (true){
                skipWhitespace();
                if (take('-')) {
                    res = new CheckedSubtract(res, parseMultiply());
                } else if (take('+')) {
                    res = new CheckedAdd(res, parseMultiply());
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
                    res = new CheckedDivide(res, parseUnaryMines());
                } else if (take('*')) {
                    res = new CheckedMultiply(res, parseUnaryMines());
                } else {
                    return res;
                }
            }
        }

        int minesFlag = 0;
        private Expressions parseUnaryMines() {
            skipWhitespace();
            if (take('-')) {
                minesFlag = 1;
                if (take('(')){
                    Expressions res = parseAll();
                    expect(')');
                    return new CheckedNegate(res);
                }
                return UnaryMines.createUnaryMines(parseExpression());
            } else if (take('l')) {
                expect("og2");
                isCorrectSymbol();
                skipWhitespace();
                if (take('(')){
                    Expressions res = parseAll();
                    expect(')');
                    return new CheckedLog(res);
                } else if (take('-')) {
                    minesFlag = 1;
                    if (take('(')) {
                        Expressions res = parseAll();
                        expect(')');
                        return new CheckedLog(new CheckedNegate(res));
                    } else {
                        return new CheckedLog(UnaryMines.createUnaryMines(parseExpression()));
                    }
                }
                return new CheckedLog(parseExpression());
            } else if (take('p')) {
                expect("ow2");
                isCorrectSymbol();
                skipWhitespace();
                if (take('(')){
                    Expressions res = parseAll();
                    expect(')');
                    return new CheckedPow(res);
                } else if (take('-')) {
                    minesFlag = 1;
                    if (take('(')) {
                        Expressions res = parseAll();
                        expect(')');
                        return new CheckedPow(new CheckedNegate(res));
                    } else {
                        return new CheckedPow(UnaryMines.createUnaryMines(parseExpression()));
                    }
                }
                return new CheckedPow(parseExpression());
            }
            return parseExpression();
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
            if (sb.toString().equals(String.valueOf(Integer.MIN_VALUE).substring(1))) {
                if (minesFlag == 1) {
                    return new Const(Integer.MIN_VALUE);
                } else {
                    throw new OverflowException("Const overflow");
                }
            }

            skipWhitespace();
            if (Character.isDigit(getCh())){
                throw error("space between numbers");
            }
            return new Const(Integer.parseInt(sb.toString()));
        }

        private Expressions parseVar() {
            char var = take();
            return new Variable(String.valueOf(var));
        }

        private void isCorrectSymbol(){
            if (Character.isDigit(getCh()) || Character.isLetter(getCh()) || badSymbols.contains(String.valueOf(getCh()))) {
                throw error("Incorrect input");
            }
        }
    }
}
