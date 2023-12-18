(defn constant [n]
  (constantly n))
(defn variable [keyy]
  (fn [mapa] (mapa keyy)))
(defn varargs [f]
  (fn [& args]
    (fn [mapa]
      (apply f (mapv (fn [a] (a mapa)) args)))))
(def negate (varargs -))
(def add (varargs +))
(def subtract (varargs -))
(def multiply (varargs *))
(defn div ([x] (/ 1.0 (double x)))
  ([x & y] (reduce (fn [a b] (/ (double a) (double b))) x y)))
(defn divide [& args]
  (fn [mapa]
    (apply div (mapv (fn [a] (a mapa)) args))))
(defn meanf [& args] (/ (apply + args) (count args)))
(def mean (varargs meanf))
(defn varnf [& args] (apply meanf (mapv (fn [a] (* (- a (apply meanf args)) (- a (apply meanf args)))) args)))
(def varn (varargs varnf))
(defn sumexpf [& args] (reduce + (mapv (fn [a] (Math/exp a)) args)))
(def sumexp (varargs sumexpf))
(defn softmaxfif [& args] (/ (Math/exp (first args)) (apply sumexpf args)))
(def softmax (varargs softmaxfif))
(defn powf [a b] (Math/pow a b))
(def pow (varargs powf))
(defn logf [a b] (/ (Math/log (Math/abs b)) (Math/log (Math/abs a))))
(def log (varargs logf))
(defn lnf [a] (Math/log (Math/abs a)))
(def ln (varargs lnf))
(defn expf [a] (Math/exp a))
(def exp (varargs expf))
(def MAPOFFANCTION {"var" variable, "const" constant,
                    "+" add, "-" subtract, "*" multiply, "/" divide, "negate" negate,
                    "mean" mean, "varn" varn,
                    "sumexp" sumexp, "softmax" softmax,
                    "pow" pow, "log" log,
                    "ln" ln, "exp" exp})
(defn parse [mapa list]
  (cond
    (list? list) (apply (mapa (name (first list))) (mapv (fn [a] (parse mapa a)) (rest list)))
    (symbol? list) ((mapa "var") (name list))
    :else ((mapa "const") list)))
(defn parseFunction [string]
  (parse MAPOFFANCTION (read-string string)))

(defn proto-get
  ([obj key] (proto-get obj key nil))
  ([obj key defult]
   (cond
     (contains? obj key) (get obj key)
     (contains? obj :proto) (recur (get obj :proto) key defult)
     :else defult)))
(defn toString [this]
  ((proto-get this :toString) this))
(defn toStringSuffix [this]
  ((proto-get this :toStringSuffix) this))
(defn evaluate [this mapa]
  ((proto-get this :evaluate)  this mapa))
(defn getArgs [this]
  (proto-get this :args))
(defn getFunc [this]
  (proto-get this :func))
(defn getOper [this]
  (proto-get this :oper))
(defn diff [this vur]
  ((proto-get this :diff) this vur))
(defn Constant [n]
  {:toString (fn [this] (str (getArgs this)))
   :toStringSuffix (fn [this] (str (getArgs this)))
   :evaluate (fn [this mapa] (getArgs this))
   :args n
   :diff (fn [this vur] (Constant 0))})
(defn Variable [vur]
  {:toString (fn [this] (getArgs this))
   :toStringSuffix (fn [this] (getArgs this))
   :evaluate (fn [this mapa] (mapa (str (Character/toLowerCase (first (getArgs this))))))
   :args vur
   :diff (fn [this vur] (if (= vur (getArgs this))
                          (Constant 1)
                          (Constant 0)))})
(defn ProtoFunc [oper func args]
  {:evaluate (fn [this mapa] (apply (getFunc this) (mapv (fn [a] (evaluate a mapa)) (getArgs this))))
   :toString (fn [this] (cond
                          (== 0 (count (getArgs this))) (str "(" (getOper this) " )")
                          :else (str "(" (getOper this) (apply str (mapv (fn [a] (str " " (toString a))) (getArgs this))) ")")))
   :toStringSuffix (fn [this] (cond
                                (== 0 (count (getArgs this))) (str "( " (getOper this) ")")
                                :else (str "(" (apply str (mapv (fn [a] (str (toStringSuffix a) " ")) (getArgs this)))  (getOper this) ")")))
   :args args
   :oper oper
   :func func})
(defn Add [& args]
  {:proto (ProtoFunc "+" + args)
   :diff (fn [this vur] (apply Add (mapv (fn [a] (diff a vur)) (getArgs this))))})
(defn Subtract [& args]
  {:proto (ProtoFunc "-" - args)
   :diff (fn [this vur] (apply Subtract (mapv (fn [a] (diff a vur)) (getArgs this))))})
(defn Multiply [& args]
  {:proto (ProtoFunc "*" * args)
   :diff (fn [this vur] (cond
                          (== 0 (count (getArgs this))) (Constant 0)
                          (== 1 (count (getArgs this))) (diff (first (getArgs this)) vur)
                          (== 2 (count (getArgs this))) (Add (Multiply (first (getArgs this))
                                                                       (diff (nth (getArgs this) 1) vur))
                                                             (Multiply (nth (getArgs this) 1)
                                                                       (diff (first (getArgs this)) vur)))
                          :else (diff (Multiply (first (getArgs this)) (apply Multiply (rest (getArgs this)))) vur)))})

(defn Divide [& args]
  {:proto (ProtoFunc "/" div args)
   :diff (fn [this vur] (cond
                          (== 1 (count (getArgs this))) (diff (Divide (Constant 1.0) (first (getArgs this))) vur)
                          (== 2 (count (getArgs this))) (Divide (Subtract (Multiply (diff (nth (getArgs this) 0) vur) (nth (getArgs this) 1))
                                                                          (Multiply (diff (nth (getArgs this) 1) vur) (nth (getArgs this) 0)))
                                                                (Multiply (nth (getArgs this) 1) (nth (getArgs this) 1)))
                          :else (diff (Divide (first (getArgs this)) (apply Multiply (rest (getArgs this)))) vur)))})
(defn Negate [n]
  {:proto (ProtoFunc "negate" - [n])
   :diff (fn [this vur] (Negate (diff (first (getArgs this)) vur)))})
(defn Mean [& args]
  {:proto (ProtoFunc "mean" meanf args)
   :diff (fn [this vur] (apply Mean (mapv (fn [a] (diff a vur)) (getArgs this))))})
(defn Varn [& args]
  {:proto (ProtoFunc "varn" varnf args)
   :diff (fn [this vur] (diff (Subtract (apply Mean (mapv (fn [a] (Multiply a a)) (getArgs this)))
                                        (Multiply (apply Mean (getArgs this)) (apply Mean (getArgs this)))) vur))})
(defn Exp [arg]
  {:proto (ProtoFunc "exp" expf [arg])
   :diff (fn [this vur] (Multiply (Exp (first (getArgs this))) (diff (first (getArgs this)) vur)))})
(defn Ln [arg]
  {:proto (ProtoFunc "ln" lnf [arg])
   :diff (fn [this vur] (Divide (diff (first (getArgs this)) vur) (first (getArgs this))))})
(defn Pow [arg1 arg2]
  {:proto (ProtoFunc "pow" powf [arg1 arg2])
   :diff (fn [this vur] (Multiply this (diff (Multiply (Ln (nth (getArgs this) 0)) (nth (getArgs this) 1)) vur)))})
(defn Log [arg1 arg2]
  {:proto (ProtoFunc "log" logf [arg1 arg2])
   :diff (fn [this vur] (diff (Divide (Ln (nth (getArgs this) 1)) (Ln (nth (getArgs this) 0))) vur))})
(defn Sumexp [& args]
  {:proto (ProtoFunc "sumexp" sumexpf args)
   :diff (fn [this vur] (diff (apply Add (mapv (fn [a] (Exp a)) (getArgs this))) vur))})
(defn Softmax [& args]
  {:proto (ProtoFunc "softmax" softmaxfif args)
   :diff (fn [this vur] (diff (Divide (Exp (nth (getArgs this) 0)) (apply Sumexp (getArgs this))) vur))})
(defn sinhf [a] (Math/sinh a))
(defn ProtoSinh [arg]
  {:proto (ProtoFunc "sinh" sinhf [arg])})
(defn coshf [a] (Math/cosh a))
(defn Cosh [arg]
  {:proto (ProtoFunc "cosh" coshf [arg])
   :diff (fn [this vur] (Multiply (ProtoSinh (first (getArgs this))) (diff (first (getArgs this)) vur)))})
(defn Sinh [arg] (assoc (ProtoSinh arg) :diff (fn [this vur] (Multiply (Cosh (first (getArgs this))) (diff (first (getArgs this)) vur)))))
(defn sinf [a] (Math/sin a))
(defn ProtoSin [arg]
  {:proto (ProtoFunc "sin" sinf [arg])})
(defn cosf [a] (Math/cos a))
(defn Cos [arg]
  {:proto (ProtoFunc "cos" cosf [arg])
   :diff (fn [this vur] (Negate (Multiply (ProtoSin (first (getArgs this))) (diff (first (getArgs this)) vur))))})
(defn Sin [arg] (assoc (ProtoSin arg) :diff (fn [this vur] (Multiply (Cos (first (getArgs this))) (diff (first (getArgs this)) vur)))))
(defn BitOper [sign oper args]
  {:proto (ProtoFunc sign (fn [a b] (java.lang.Double/longBitsToDouble (oper (java.lang.Double/doubleToLongBits a) 
                                                                     (java.lang.Double/doubleToLongBits b)))) args)})
(defn BitAnd [a b] {:proto (BitOper "&" bit-and [a b])})
(defn BitOr [a b] {:proto (BitOper "|" bit-or [a b])})
(defn BitXor [a b] {:proto (BitOper "^" bit-xor [a b])})
(def MAPOFOBJECTS {"var" Variable, "const" Constant,
                   "+" Add, "-" Subtract, "*" Multiply, "/" Divide, "negate" Negate,
                   "mean" Mean, "varn" Varn,
                   "sumexp" Sumexp, "softmax" Softmax,
                   "pow" Pow, "log" Log,
                   "ln" Ln, "exp" Exp
                   "sinh" Sinh, "cosh" Cosh, "sin" Sin, "cos" Cos
                   "&" BitAnd, "|" BitOr "^" BitXor})
(defn parseObject [string]
  (parse MAPOFOBJECTS (read-string string)))
(defn -return [value tail] {:value value :tail tail})
(def -valid? boolean)
(def -value :value)
(def -tail :tail)
(defn _empty [value] (partial -return value))
(defn _char [p]
  (fn [[c & cs]]
    (if (and c (p c)) (-return c cs) nil)))
(defn _map [f]
  (fn [result]
    (if (-valid? result)
      (-return (f (-value result)) (-tail result)))))
(defn _combine [f a b]
  (fn [str]
    (let [ar ((force a) str)]
      (if (-valid? ar)
        ((_map (partial f (-value ar)))
         ((force b) (-tail ar)))
        nil))))
(defn _either [a b]
  (fn [str]
    (let [ar ((force a) str)]
      (if (-valid? ar) ar ((force b) str)))))
(defn _parser [p]
  (fn [input]
    (-value ((_combine (fn [v _] v) p (_char #{\u0001})) (str input \u0001)))))
(defn +char [chars] (_char (set chars)))
(defn +char-not [chars] (_char (comp not (set chars))))
(defn +map [f parser] (comp (_map f) parser))
(def +ignore (partial +map (constantly 'ignore)))
(defn iconj [coll value]
  (if (= value 'ignore) coll (conj coll value)))
(defn +seq [& ps]
  (reduce (partial _combine iconj) (_empty []) ps))
(defn +seqf [f & ps] (+map (partial apply f) (apply +seq ps)))
(defn +seqn [n & ps] (apply +seqf (fn [& vs] (nth vs n)) ps))
(defn +or [p & ps]
  (reduce (partial _either) p ps))
(defn +opt [p]
  (+or p (_empty nil)))
(defn +star [p]
  (letfn [(rec [] (+or (+seqf cons p (delay (rec))) (_empty ())))] (rec)))
(defn +plus [p] (+seqf cons p (+star p)))
(defn +str [p] (+map (partial apply str) p))
(def +parser _parser)
(def *all-chars (mapv char (range 0 128)))
(def *letter (+char (apply str (filter #(Character/isLetter %) *all-chars))))
(def *digit (+char (apply str (filter #(Character/isDigit %) *all-chars))))
(def *space (+char (apply str (filter #(Character/isWhitespace %) *all-chars))))
(def *ws (+ignore (+star *space)))
(defn combstr [p1 p2 p3 p4] (str (str p1) (apply str p2) (str p3) (apply str p4)))
(def *numbers (+map #(Constant (read-string %)) (+str (+seqf combstr (+opt (+char "+-")) (+plus *digit) (+opt (+char ".")) (+opt (+plus *digit))))))
(def *variables (+map #(Variable %) (+str (+plus (+char "xyzXYZ")))))
(def *binOperation (+char "+-*/&|^"))
(def *negate (+seqf (constantly "negate") (+char "n") (+char "e") (+char "g") (+char "a") (+char "t") (+char "e")))
(def *unarOperation *negate)
(def parseObjectSuffix
  (letfn [(unaryOper [a sign] ((MAPOFOBJECTS (str sign)) a))
          (*unaryOper [] (+seqf unaryOper (delay (*value)) *ws *unarOperation))
          (binaryOper [a b sign] ((MAPOFOBJECTS (str sign)) a b))
          (*binaryOper [] (+seqf binaryOper (delay (*value)) *ws (delay (*value)) *ws *binOperation))
          (*list [] (+seqn 1 (+char "(") *ws (+or (delay (*binaryOper)) (delay (*unaryOper))) *ws (+char ")")))
          (*value [] (+or *numbers *variables (*list)))]
    (+parser (+seqn 0 *ws (*value) *ws))))
;; (def parseObjectInfix
;;   (letfn[(+unaryOper [sign a] ((MAPOFOBJECTS (str sign)) a))
;;          (+binaryOper [a sign b] ((MAPOFOBJECTS (str sign)) a b))
;;          (*addsub [] (+seqf +binaryOper (delay (*value)) *ws (+char "+-") *ws (delay (*value))))
;;          (*multdiv [] (+seqf +binaryOper (delay (*value)) *ws (+char "*/") *ws (delay (+or *numbers *variables))))
;;          (*value [] (+or *numbers *variables (*multdiv) (*addsub)))]
;;    (+parser (+seqn 0 *ws (*value)  *ws))))
;; (println (toStringSuffix (parseObjectInfix "2 + 3")))