package expression.exceptions;


import expression.*;

import java.util.Arrays;
import java.util.List;

public final class ExpressionParser implements TripleParser, ListParser{

    private static boolean parenthesisFlag;
    public static List<String> args;

    public Expressions parse(final String source) {
        int leftCir = 0;
        int rightCir = 0;
        int leftSq = 0;
        int rightSq = 0;
        int leftF = 0;
        int rightF = 0;
        for (int i = 0; i < source.length(); i++) {
            switch (source.charAt(i)) {
                case('(') -> leftCir++;
                case(')') -> rightCir++;
                case('[') -> leftSq++;
                case(']') -> rightSq++;
                case('{') -> leftF++;
                case('}') -> rightF++;
            }
        }
        parenthesisFlag = leftCir == rightCir && leftF == rightF && leftSq == rightSq;
        return parse(new StringSource(source));
    }

    public static boolean getF() {
        return parenthesisFlag;
    }

    public static Expressions parse(final CharSource source) {
        return new Parser(source).parseAll();
    }

    @Override
    public ListExpression parse(String expression, List<String> variables) {
        return parse(expression);
    }

    private static class Parser extends BaseParser {
        private int minesFlag = 0;
        int leftCir = 0;
        int rightCir = 0;
        int leftSq = 0;
        int rightSq = 0;
        int leftF = 0;
        int rightF = 0;


        public Parser(final CharSource source) {
            super(source);
            checker();
        }
        private void checker() {
            if (!getF()) {
                throw new ParseExcepsions("Incorrect parenthesis sequence");
           }
       }

        private void skipWhitespace() {
            String dict = "[]{}()$+-*pl/\0";
            while ((!between('0', '9') && !between('x', 'z') && !dict.contains(String.valueOf(getCh())))) {
                if (Character.isWhitespace(getCh())) {
                    take();
                    continue;
                }
                throw new ParseExcepsions("Unexpected symbol");
            }
        }

        private void firstArgError() {
            String dict = "([{p$l-";
            if (!Character.isDigit(getCh()) && !between('x', 'z') && !dict.contains(String.valueOf(getCh()))) {
                throw new ParseExcepsions("No first argument");
            }
        }

        private Expressions parentheticalExpressionParse(char ch) {
            take();
            skipWhitespace();
            firstArgError();
            Expressions res = parseAll();
            expect(ch);

            return res;
        }

        private Expressions parseAll() {
            skipWhitespace();
            Expressions res = parseAdd();
            if (leftCir == rightCir && leftF == rightF && leftSq == rightSq)
                return res;
            throw new ParseExcepsions("ddl");
        }

        private Expressions parseAdd() {
            Expressions res = parseSubtract();
            while (take('+')) {
                res = new CheckedAdd(res, parseSubtract());
                skipWhitespace();
            }
            return res;
        }

        private Expressions parseSubtract() {
            Expressions res = parseMultiply();
            while (take('-')) {
                res = new CheckedSubtract(res, parseMultiply());
                skipWhitespace();
            }
            return res;
        }

        private Expressions parseMultiply() {
            Expressions res = parseDivide();
            while (take('*')) {
                res = new CheckedMultiply(res, parseDivide());
                skipWhitespace();
            }
            return res;
        }

        private Expressions parseDivide() {
            Expressions res = parseUnaryOperation();
            skipWhitespace();
            while (take('/')) {
                res = new CheckedDivide(res, parseUnaryOperation());
                skipWhitespace();
            }
            return res;
        }

        private Expressions parseUnaryOperation() {
            skipWhitespace();
            switch (getCh()) {
                case ('-') -> {
                    take();
                    return parseUnaryMinus();
                }
                case ('l') -> {
                    take();
                    return parseLog();
                }
                case ('p') -> {
                    take();
                    return parsePow();
                }
                default -> {
                    return parseExpression();
                }
            }
        }

        private Expressions parseUnaryMinus() {
            minesFlag = 1;
            switch (getCh()) {
                case ('(') -> {
                    return new CheckedNegate(parentheticalExpressionParse(')'));
                }
                case ('[') -> {
                    return new CheckedNegate(parentheticalExpressionParse(']'));
                }
                case ('{') -> {
                    return new CheckedNegate(parentheticalExpressionParse('}'));
                }
                default -> {
                    Expressions res = parseExpression();
                    return (res instanceof Const) ? new Const(-((Const) res).evaluate()) : new UnaryMinus(res);
                }
            }
        }

        private Expressions parseLog() {
            expect("og2");
            checkedLogPowExcepsion();
            skipWhitespace();
            if (take('(')) {
                Expressions res = parseAll();
                expect(')');
                return new CheckedLog(res);
            } else if (take('-')) {
                return parseLogWithUnaryMinus();
            } else {
                return new CheckedLog(parseExpression());
            }
        }

        private Expressions parseLogWithUnaryMinus() {
            minesFlag = 1;
            if (take('(')) {
                Expressions res = parseAll();
                expect(')');
                return new CheckedLog(new CheckedNegate(res));
            } else {
                Expressions res = parseExpression();
                return (res instanceof Const) ? new Const(-((Const) res).evaluate()) : new UnaryMinus(res);
            }
        }

        private Expressions parsePow() {
            expect("ow2");
            checkedLogPowExcepsion();
            skipWhitespace();
            if (take('(')) {
                Expressions res = parseAll();
                expect(')');
                return new CheckedPow(res);
            } else if (take('-')) {
                return parsePowWithUnaryMinus();
            } else {
                return new CheckedPow(parseExpression());
            }

        }

        private void checkedLogPowExcepsion() {
            if (getCh() != '(' && getCh() != ' ') {
                throw new ParseExcepsions("Missing \"(\" or \" \" after log or pow");
            }
        }

        private Expressions parsePowWithUnaryMinus() {
            minesFlag = 1;
            if (take('(')) {
                Expressions res = parseAll();
                expect(')');
                return new CheckedPow(new CheckedNegate(res));
            } else {
                Expressions res = parseExpression();
                return (res instanceof Const) ? new Const(-((Const) res).evaluate()) : new UnaryMinus(res);
            }
        }

        private Expressions parseExpression() {
            skipWhitespace();
            switch (getCh()) {
                case ('(') -> {
                    return parentheticalExpressionParse(')');
                }
                case ('[') -> {
                    return parentheticalExpressionParse(']');
                }
                case ('{') -> {
                    return parentheticalExpressionParse('}');
                }
                case ('-') -> {
                    take();
                    Expressions res = parseExpression();
                    return (res instanceof Const) ? new Const(-((Const) res).evaluate()) : new UnaryMinus(res);
                }
                case ('p') -> {
                    take();
                    expect("ow2");
                    return new CheckedPow(parseExpression());
                }
                case ('l') -> {
                    take();
                    expect("og2");
                    return new CheckedLog(parseExpression());
                }
                case ('$') -> {
                    take();
                    return new Variable(Integer.parseInt(takeDigits().toString()));
                }
                case ('x'), ('y'), ('z') -> {
                    return parseVar();
                }
                default -> {
                    if (between('0', '9')) {
                        return parseConst();
                    }
                    throw new ParseExcepsions("Incorrect input");
                }
            }
        }

        private StringBuilder takeDigits() {
            StringBuilder sb = new StringBuilder();
            while (between('0', '9')) {
                sb.append(take());
            }

            try {
                if (!(sb.toString().equals(String.valueOf(Integer.MIN_VALUE).substring(1)))){
                    Integer.parseInt(sb.toString());
                }
            } catch (NumberFormatException e) {
                throw new OverflowException("Const overflow");
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
            if (Character.isDigit(getCh())) {
                throw new ParseExcepsions("Space between numbers");
            }
            return new Const(Integer.parseInt(sb.toString()));
        }

        private Expressions parseVar() {
            char var = take();
            return new Variable(String.valueOf(var));
        }
    }
}