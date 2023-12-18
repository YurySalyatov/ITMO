"use strict";
const WIGHTSPACE = " \n\t\r\v";
const ALFABET = "abcdefghijklmnopqrstuvwxyz";
const DIGITS = "1234567890";
const VARIABLES = {
    "x": 0,
    "y": 1,
    "z": 2,
}
let MAXLENGHTOPER = 6;
const OPERATIONS = {
    "negate": [Negate, (varr) => (a) => new Negate(a.diff(varr))],
    "cosh": [Cosh, (varr) => (a) => new Multiply(new Sinh(a), a.diff(varr))],
    "sinh": [Sinh, (varr) => (a) => new Multiply(new Cosh(a), a.diff(varr))],
    "+": [Add, (varr) => (a, b) => new Add(a.diff(varr), b.diff(varr))],
    "-": [Subtract, (varr) => (a, b) => new Subtract(a.diff(varr), b.diff(varr))],
    "*": [Multiply, (varr) => (a, b) => new Add(new Multiply(a.diff(varr), b), new Multiply(a, b.diff(varr)))],
    "/": [Divide, (varr) => (a, b) => new Divide(new Subtract(new Multiply(a.diff(varr),b), new Multiply(a,b.diff(varr))), new Multiply(b, b))],
    "pow": [Pow, (varr) => (a, b) => new Multiply(new Pow(a, b), new Multiply(new Ln(a), b).diff(varr))],
    "log": [Log, (varr) => (a, b) => new Divide(new Ln(b), new Ln(a)).diff(varr)],
    "gauss": [Gauss, (varr) => (a, b, c, x) =>
        new Multiply(a, new Exp(new Multiply(new Const(-1/2), new Multiply(new Divide(new Subtract(x, b), c), new Divide(new Subtract(x, b), c))))).diff(varr)],
    "ln": [Ln, (varr) => (a) => new Multiply(new Divide(new Const(1), a), a.diff(varr))],
    "exp": [Exp, (varr) => (a) => new Multiply(new Exp(a), a.diff(varr))],
    "min3": [Min3, (varr) => (a, b, c) => new Min3(a.diff(varr), b.diff(varr), c.diff(varr))],
    "max5": [Max5, (varr) => (a, b, c, d, f) => new Max5(a.diff(varr), b.diff(varr), c.diff(varr), d.diff(varr), f.diff(varr))],
    "mean": [Mean, (varr) => function (...args) {
        let array = [];
        for (let i = 0; i < [...args].length; i++) {
            array.push([...args][i].diff(varr));
        }
        return new Mean(...array);
        }],
    "var": [Var, (varr) => function(...args) {
        let array1 = [];
        for (let i = 0; i < [...args].length; i++) {
            array1.push(new Multiply([...args][i], [...args][i]));
        }
        return new Subtract(new Mean(...array1), new Multiply(new Mean(...args), new Mean(...args))).diff(varr);}
    ],
}
const VARIABLEOPERATIONS = "mean var";
const CONSTANTOPERATIONS = "negate + - * / pow log ln exp gauss min3 max5 sinh cosh";
    
const CONSTS = {
    "pi": Pi,
    "e": E,
}

function Const(a, oper) {
    this.toString = function() {
        return oper === undefined ? a + "" : oper;
    }
    this.prefix = function() {
        return oper === undefined ? a + "" : oper;
    }
    this.postfix = function() {
        return oper === undefined ? a + "" : oper;
    }
    this.evaluate = function() {
        return a;
    }
    this.diff = function() {
        return new Const(0);
    }
}
function Variable(a) {
    this.toString = function() {
        return a;
    }
    this.prefix = function() {
        return a;
    }
    this.postfix = function() {
        return a;
    }
    this.evaluate = function() {
        return arguments[VARIABLES[a]];
    }
    this.diff = function(varr) {
        return a === varr ? new Const(1) : new Const(0);
    }
}
function MultyOperation(f, oper, fs) {
    this.toString = function() {
        let str = "";
        for(let i = 0; i < fs.length; i++) {
            str += fs[i].toString() + " ";
        }
        str += oper;
        return str;
    }
    this.prefix = function() {
        let str = "(";
        str += oper;
        for (let i = 0; i < fs.length; i++) {
            str += " " + fs[i].prefix();
        }
        str += ")"
        return str;
    }
    this.postfix = function() {
        let str = "(";
        for (let i = 0; i < fs.length; i++) {
            str += fs[i].postfix() + " ";
        }
        str += oper;
        str += ")"
        return str;
    }
    this.evaluate = function(...args) {
        let array = [];
        for (let i = 0; i < fs.length; i++) {
            array.push(fs[i].evaluate(...args));
        }
        return f(...array);
    }
    this.diff = function(varr) {
        return OPERATIONS[oper][1](varr)(...fs);
    }
}
function Pi() {Const.call(this, Math.PI, "pi");}
function E() {Const.call(this, Math.E, "e");}
function Negate(a) {MultyOperation.call(this, (a) => -a, "negate", [a]);}
function Add (a, b) {MultyOperation.call(this, (a, b) => a + b, "+", [a, b])}
function Subtract(a, b) {MultyOperation.call(this, (a, b) => a - b, "-", [a, b]);}
function Multiply(a, b) {MultyOperation.call(this, (a, b) => a * b, "*", [a, b]);}
function Divide(a, b) {MultyOperation.call(this, (a, b) => a / b, "/", [a, b]);}
function Pow(a, b) {MultyOperation.call(this, (a, b) => Math.pow(a, b), "pow", [a, b]);}
function Log(a, b) {MultyOperation.call(this, (a, b) => Math.log(Math.abs(b)) / Math.log(Math.abs(a)), "log", [a,b]);}
function Gauss(a, b, c, x) {
    MultyOperation.call(this, (a, b, c, x) => a * Math.exp(-(1/2) * Math.pow((x - b)/c, 2)), "gauss", [a, b, c, x]);
}
function Exp(a) {MultyOperation.call(this, (a) => Math.exp(a), "exp", [a]);}
function Ln(a) {MultyOperation.call(this, (a) => Math.log(Math.abs(a)), "ln", [a]);}
function Cosh(a) {MultyOperation.call(this, (a) => Math.cosh(a), "cosh", [a]);}
function Sinh(a) {MultyOperation.call(this, (a) => Math.sinh(a), "sinh", [a]);}
function Min3(a, b, c) {MultyOperation.call(this, (a, b, c) => [a, b, c].reduce((a, b) => Math.min(a, b)), "min3", [a, b, c]);}
function Max5(a, b, c, d, f) {
    MultyOperation.call(this, (a, b, c, d, f) => [a, b, c, d, f].reduce((a, b) => Math.max(a, b)), "max5", [a, b, c, d, f]);
}
function Mean(...args) {MultyOperation.call(this, (...args) => [...args].reduce((a, b) => a + b) / [...args].length, "mean", [...args]);}
function Var(...args) {
    MultyOperation.call(this, (...args) =>
        [0, ...args].reduce((a, b) => a + b * b) / [...args].length - Math.pow([...args].reduce((a, b) => a + b) / [...args].length, 2),
    "var", [...args]);
}
function SumExp(...args) {MultyOperation.call(this, (...args) => [0, ...args].reduce((a, b) => a + Math.exp(b)), "sumexp", [...args]);}
function Softmax(...args) {
    MultyOperation.call(this, (...args) => Math.exp([...args][0]) / [0, ...args].reduce((a, b) => a + Math.exp(b)), "softmax", [...args])
}
let getNumberEl = function(n, array) {
    let ret = [];
    for (let i = 0; i < n; i++) {
        ret.unshift(array.pop());
    }
    return ret;
}
let parse = function(string) {
    let array = []
    let b = string.trim().split(/[ ]+/g)
    for (let i = 0; i < b.length; i++) {
        if (!isNaN(b[i])) {
            array.push(new Const(Number(b[i])));
        } else if (b[i] in CONSTS) {
            array.push(new CONSTS[b[i]]());
        } else if (b[i] in OPERATIONS) {
            array.push(new OPERATIONS[b[i]][0](...getNumberEl(OPERATIONS[b[i]][0].length, array)));
        } else {
            array.push(new Variable(b[i]));
        }
    }
    return array[0];
}
function StructureError(message) {
    Error.call(this, message);
    this.message = message;
}
StructureError.prototype = Object.create(Error.prototype);
StructureError.prototype.constructor = StructureError;
StructureError.prototype.name = "StructureError";
function VariableError(message) {
    Error.call(this, message);
    this.message = message;
}
VariableError.prototype = Object.create(Error.prototype);
VariableError.prototype.constructor = VariableError;
VariableError.prototype.name = "VariableError";
function OperationError(message) {
    Error.call(this, message);
    this.message = message;
}
OperationError.prototype = Object.create(Error.prototype);
OperationError.prototype.constructor = OperationError;
OperationError.prototype.name = "OperationError";
let ParseExpressPrototype  = {
    shift : function() {this.ind++;},
    isEnd : function() {
        return this.ind === this.string.length;
    },
    skipWightspace : function() {
        while (WIGHTSPACE.indexOf(this.string[this.ind]) > -1 && !this.isEnd()) {
            this.shift();
        }
    },
    getOper : function() {
        this.skipWightspace();
        let str = this.string[this.ind];
        this.shift();
        while(!(str in OPERATIONS) && !this.isEnd() && !this.isScobNow() && str !== undefined && !(WIGHTSPACE.indexOf(this.string[this.ind]) > -1)) {
            if (str.length > MAXLENGHTOPER) {
                throw new OperationError("Unknown operator: " + str);
            }
            str += this.string[this.ind];
            this.shift(); 
        }
        if (!(str in OPERATIONS)) {
            throw new OperationError("Unknown operator: " + str);
        }
        if (!(WIGHTSPACE.indexOf(this.string[this.ind]) > -1) && !this.isScobNow()) {
            throw new StructureError("Expected wightspace, found: " + this.string[this.ind]);
        }
        return str;
    },
    takeScob : function() {
        if(this.isScobNow()) {
            this.shift();
            return true;
        }
        return false;
    },
    parseConst : function(val) {
        this.skipWightspace();
        let cnst = this.string[this.ind];
        this.shift();
        while(!isNaN(this.string[this.ind]) && !this.isEnd() && !(WIGHTSPACE.indexOf(this.string[this.ind]) > -1)) {
            cnst += this.string[this.ind];
            this.shift();
        }
        return new Const(val * Number(cnst));
    },
    parseUnarMinus : function() {
        this.skipWightspace();
        if (ALFABET.indexOf(this.string[this.ind]) > -1) {
            return new Negate(this.parseVar());
        } else {
            if (!isNaN(this.string[this.ind])) {
                return this.parseConst(-1);
            } else {
                throw new StructureError("Uncnown expression, expected x, y, z or const, find: " + this.string[this.ind]);
            }
        }
    },
    isScobNow : function() {
        return this.string[this.ind] === "(" || this.string[this.ind] ===")";
    },
    parseVar : function() {
        let vrb = this.string[this.ind];
        this.shift();
        while(!(WIGHTSPACE.indexOf(this.string[this.ind]) > -1) && !this.isScobNow() && !this.isEnd()) {
            vrb += this.string[this.ind];
            this.shift();
        }
        if (vrb in VARIABLES) {
            return new Variable(vrb);
        } else {
            throw new VariableError("Expected x, y, z, found: " + vrb);
        }
    },
    chekEnd : function(first) {
        if (first) {
            this.skipWightspace();
            if (!this.isEnd()) {
                throw new StructureError("Expected end of expression, find: " + this.string[this.ind]);
            }
        }
        return;
    },
    
}
function PrefParser(string) {
    let parser = Object.create(ParseExpressPrototype);
    parser.string = string;
    parser.ind = 0;
    parser.getManyExprs = function(oper) {
        let array = [];
        if (CONSTANTOPERATIONS.indexOf(oper) > -1) {
            for (let i = 0; i < OPERATIONS[oper][0].length; i++) {
                array.push(this.getExpr(false));
            }
        } else  {
            if (VARIABLEOPERATIONS.indexOf(oper) > -1){
                while(this.string[this.ind] !== ")") {
                    array.push(this.getExpr(false));
                    this.skipWightspace();
                }
            }
        }
        return(array);
    };
    parser.getExpr = function(first) {
        this.skipWightspace();
        if (this.takeScob()) {
            let oper = this.getOper();
            let neew = new OPERATIONS[oper][0](...this.getManyExprs(oper));
            this.skipWightspace();
            if (this.takeScob()) {
                this.chekEnd(first);
                return neew;
            } else {
                throw new StructureError("Expected \")\", found: " + this.string[this.ind]);
            }
        } else {
            if(this.string[this.ind] === "-") {
                this.ind;
                this.shift();
                let neew = this.parseUnarMinus();
                this.chekEnd(first);
                return neew;
            } else {
                if (ALFABET.indexOf(this.string[this.ind]) > -1) {
                    let neew = this.parseVar();
                    this.chekEnd(first);
                    return neew;
                } else {
                    if (!isNaN(this.string[this.ind])) {
                        let neew = this.parseConst(1);
                        this.chekEnd(first);
                        return neew;
                    } else {
                        throw new StructureError("Expected expression, found: " + this.string[this.ind]);
                    }
                }
            }
        }
    };
    return parser;
}
function PostParser(string) {
    let parser = Object.create(ParseExpressPrototype);
    parser.string = string;
    parser.ind = 0;
    parser.getWord = function() {
        let word = "";
        while(this.string[this.ind] in ALFABET || this.string[this.ind] in DIGITS) {
            word += this.string[this.ind];
            this.shift();
        }
        return word;
    }
    parser.getExpr = function(first) {
        this.skipWightspace();
        if(this.takeScob()) {
            let array = [];
            let a = this.getExpr(false);
            while(!(a in OPERATIONS)) {
                array.push(a);
                if (this.isEnd()) {
                    throw new StructureError("Unexpected to find end of expression");
                }
                if (this.isScobNow()) {
                    throw new StructureError("Expected to find operation or expression, not scob");
                }
                a = this.getExpr(false);
            }
            let neww;
            if (CONSTANTOPERATIONS.indexOf(a) > -1) {
                if (array.length === OPERATIONS[a][0].length) {
                    neww = new OPERATIONS[a][0](...array);    
                } else {
                    throw new StructureError("Unsupported number of arguments for function: \"" + a + "\", expected " + OPERATIONS[a][0].length + " find " + array.length);
                }
            } else {
                neww = new OPERATIONS[a][0](...array);
            }
            if (first) {
                this.chekEnd();
                return neww;
            }
        } else {
            let word = this.getWord();
            if (word in OPERATIONS) {
                return word;
            } else if (!isNaN(word)) {
                return new Const(Number(word));
            } else if (word in VARIABLES) {
                return new Variable(word);
            } else {
                throw new StructureError("Unexpected word: " + word + " , please, chek it");
            }
        }
    }
    return parser;
}
let parsePrefix = function(string) {
    return PrefParser(string).getExpr(true);
}
let parsePostfix = function(string) {
    return PostParser(string).getExpr(true);
}