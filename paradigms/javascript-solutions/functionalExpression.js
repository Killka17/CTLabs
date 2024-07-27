"use strict";
const binOp = (operator) => (a, b) => (x, y, z) => operator(a(x, y, z), b(x, y, z));
const cnst = val => () => val;
const add = binOp((a, b) => a + b);
const divide = binOp((a, b) => a / b);
const multiply = binOp((a, b) => a * b);
const subtract = binOp((a, b) => a - b);
const negate = a => (x, y, z) => -a(x, y, z);

const variable = name => {
    const nameToConst = {"x": 0, "y": 1, "z": 2};
    return (x, y, z) => [x, y, z][nameToConst[name]];
};
const pi = cnst(Math.PI);
const e = cnst(Math.E);
const cube = (a) => (x, y, z) => a(x, y, z) * a(x, y, z) * a(x, y, z);
const cbrt = (a) => (x, y, z) => Math.cbrt(a(x, y, z))

// let expr = add(subtract(multiply(variable("x"), variable("x")), multiply(cnst(2), variable("x"))), cnst(1))
//
// for (let i = 0; i < 11; i++) {
//     expr(i, 0, 0)
// }
