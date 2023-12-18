"use strict";
// :NOTE: let -> const
let compareNumbers = ((a, b) => a - b);
let variables = {
    "x": 0, "y": 1, "z": 2,
}
let variable = (a) => (...args) => ([...args][variables[a]]);
let cnst = (a) => (...args) => a;
let pi = cnst(Math.PI);
let e = cnst(Math.E);
let consts = {
    "pi": pi, "e": e,
}
let multyOperation = n => f => (...argsF) => (...argsV) => {
    let array = [...argsF];
    for (let i = 0; i < n; i++) {
        array[i] = array[i](...argsV);
    }
    return (f(...array));
}
let negate = multyOperation(1)((a) => -a);
let abs = multyOperation(1)(Math.abs);
let sinh = multyOperation(1)(Math.sinh);
let cosh = multyOperation(1)(Math.cosh);
let sin = multyOperation(1)(Math.sin);
let cos = multyOperation(1)(Math.cos);
let add = multyOperation(2)((a, b) => a + b);
let subtract = multyOperation(2)((a, b) => a - b);
let multiply = multyOperation(2)((a, b) => a * b);
let divide = multyOperation(2)((a, b) => a / b);
let iff = multyOperation(3)((a, b, c) => (a >= 0 ? b : c));
let avg3 = multyOperation(3)((...args) => ([...args].reduce((a, b) => a + b)) / [...args].length);
let med5 = multyOperation(5)((...args) => [...args].sort(compareNumbers)[Math.floor([...args].length / 2)]);
let operations = {
    "negate": [1, negate],
    "abs": [1, abs],
    "+": [2, add],
    "-": [2, subtract],
    "*": [2, multiply],
    "/": [2, divide],
    "iff": [3, iff],
    "avg3": [3, avg3],
    "med5": [5, med5],
    "cosh": [1, cosh],
    "sinh": [1, sinh],
    "cos": [1, cos],
    "sin": [1, sin],
}
let getNumberEl = function (n, array) {
    let ret = [];
    // :NOTE: n^2
    for (let i = 0; i < n; i++) {
        ret.unshift(array.pop());
    }
    return ret;
}
let parse = (string) => (...args) => {
    let array = []
    let b = string.trim().split(/[ ]+/g)
    for (let i = 0; i < b.length; i++) {
        if (!isNaN(b[i])) {
            array.push(cnst(Number(b[i])));
        } else if (b[i] in consts) {
            array.push(consts[b[i]]);
        } else if (b[i] in operations) {
            array.push(operations[b[i]][1](...getNumberEl(operations[b[i]][0], array)));
        } else {
            array.push(variable(b[i]));
        }
    }
    return array[0](...args)
}