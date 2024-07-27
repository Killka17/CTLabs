"use strict"

function CustomError(message) {
    this.message = message;
    Error.call(this, message)
}

CustomError.prototype = Object.create(Error.prototype)

function Expression(val) {
    this.val = val;
}

Expression.prototype.toString = function () {
    return this.val;
};
Expression.prototype.prefix = function () {
    return this.val;
};

function Const(value) {
    Expression.call(this, value.toString());
    this.value = value;
}

Const.prototype = Object.create(Expression.prototype);

Const.prototype.evaluate = function () {
    return this.value;
};

function Variable(name) {
    Expression.call(this, name);
    this.name = name;
}

Variable.prototype = Object.create(Expression.prototype);

Variable.prototype.evaluate = function (...args) {
    return args[this.name.charCodeAt(0) - 120];
};


function Operations(sign, func, ...args) {
    this.sign = sign;
    this.func = func;
    this.args = args;
}

Operations.prototype.prefix = function () {
    return `(${this.sign} ${this.args.map(val => val.prefix()).join(" ")})`
};
Operations.prototype.toString = function () {
    return `${this.args.map(val => val.toString()).join(" ")} ${this.sign}`
};

function Operate(sign, func, ...args) {
    Operations.call(this, sign, func, ...args)
}

Operate.prototype = Object.create(Operations.prototype)

Operate.prototype.evaluate = function (x, y, z) {
    return this.func(...this.args.map((a) => (a.evaluate(x, y, z))));
};

function Multiply(left, right) {
    return new Operate("*", (left, right) => left * right, left, right);
}

function Add(left, right) {
    return new Operate("+", (left, right) => left + right, left, right);
}

function Subtract(left, right) {
    return new Operate("-", (left, right) => left - right, left, right);
}

function Divide(left, right) {
    return new Operate("/", (left, right) => left / right, left, right);
}

function Cosh(left) {
    return new Operate("cosh", (value) => Math.cosh(value), left);
}

function Sinh(left) {
    return new Operate("sinh", (value) => Math.sinh(value), left);
}

function Negate(value) {
    return new Operate("negate", (value) => -value, value);
}

function Product(...args) {
    return new Operate("product", (...args) => args.reduce((a, b) => (a * b), 1), ...args)
}

function Geom(...args) {
    return new Operate("geom", (...args) => Math.pow(Math.abs(args.reduce((a, b) => (a * b), 1)), 1 / args.length), ...args)
}

const numberRegex = /^(-?\d+)$/;

function parse(expression) {
    const stack = [];
    const tokens = expression.trim().split(" ");

    for (const token of tokens) {
        if (token in binaryOperators) {
            const b = stack.pop();
            const a = stack.pop();
            stack.push(new binaryOperators[token](a, b));
        } else if (numberRegex.test(token)) {
            stack.push(new Const(parseInt(token)));
        } else if (['x', 'y', 'z'].includes(token)) {
            stack.push(new Variable(token));
        } else if (token in unaryOperators) {
            stack.push(new unaryOperators[token](stack.pop()))
        }
    }

    return stack.pop();
}
// :NOTE: unify
const binaryOperators = {
    '+': Add,
    '-': Subtract,
    '*': Multiply,
    '/': Divide,
};

const unaryOperators = {
    "sinh": Sinh,
    "cosh": Cosh,
    "negate": Negate,
};

function myParse(expression) {
    let lPar = 0;
    let rPar = 0;
    const stack = [];
    let counter = expression.length;

    for (let i = 0; i < counter; i++) {
        if (rPar < lPar)
            throw new CustomError('Incorrect parenthesis balance')

        const token = expression[i];

        if (token in operators) {
            if (expression[i + 1] !== '(')
                throw new CustomError('Missing (')

            if (i === expression.length - 1)
                throw new CustomError("less bracket")

            let currOps = [];
            let currSymb = stack.pop()

            while (currSymb !== ')' && stack.length !== 0) {
                currOps.push(currSymb)
                currSymb = stack.pop()
            }

            if (operators[token].length !== 0 && currOps.length !== operators[token].length)
                throw new CustomError("incorrect operands count")

            stack.push(new operators[token](...currOps))

        } else if (numberRegex.test(token)) {
            stack.push(new Const(parseInt(token)));
        } else if (['x', 'y', 'z'].includes(token)) {
            stack.push(new Variable(token));
        } else if (token === "(") {
            if (!(expression[i - 1] in operators))
                throw new CustomError("no operation")
            lPar++;
        } else if (token === ")") {
            stack.push(')')
            rPar++;
        } else throw new CustomError("incorrect input");
    }

    if (lPar !== rPar)
        throw new CustomError("incorrect parenthesis sequence")
    if (stack.length > 1)
        throw new CustomError('Excessive info')
    return stack.pop()
}

function parsePrefix(expression) {
    if (expression === "")
        throw new CustomError('Empty input')
    expression = expression.split(/\s+|(\(|\))/).filter(Boolean).reverse();
    return myParse(expression);
}

const operators = {
    '+': Add,
    '-': Subtract,
    '*': Multiply,
    '/': Divide,
    "sinh": Sinh,
    "cosh": Cosh,
    "negate": Negate,
    "product": Product,
    "geom": Geom,
};
