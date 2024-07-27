package expression.exceptions;

import expression.TripleExpression;
import expression.parser.ExcepsionsParser;
public class ExpressionParser implements TripleParser {

    @Override
    public TripleExpression parse(String expression) throws Exception {
        return new ExcepsionsParser().parse(expression);
    }
}