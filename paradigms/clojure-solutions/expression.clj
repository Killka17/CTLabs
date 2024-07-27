(defn operations [f] (fn [& operands]
                       #(apply f (mapv (fn [x] (x %)) operands))))

(defn myDiv
  ([x] (/ 1.0 x))
  ([x & args] (reduce #(/ %1 (double %2)) x args)))

(def add (operations +))
(def divide (operations myDiv))
(def multiply (operations *))
(def subtract (operations -))
(def sinh (operations (fn [x] (Math/sinh x))))
(def cosh (operations (fn [x] (Math/cosh x))))
(defn negate [x] #(- (x %)))

(def constant constantly)
(defn variable [a] #(get % a))

(def operationsMap {'* multiply
                    '+ add
                    '/ divide
                    '- subtract
                    'negate negate
                    'sinh sinh
                    'cosh cosh})

(defn parse [myMap cn vr expr]
  (cond
    (number? expr) (cn expr)
    (list? expr) (apply (get myMap (first expr)) (mapv (partial parse myMap cn vr) (rest expr)))
    (symbol? expr) (vr (str expr))))

(defn parseFunction [expression]
  (parse operationsMap #(constant %) #(variable %) (read-string expression)))


(definterface Expression
  (^Number evaluate [vars])
  (^String toString []))

(deftype Const [val]
  Expression
  (evaluate [this _] val)
  (toString [this] (str val)))

(deftype Var [name]
  Expression
  (evaluate [this vars] (get vars name))
  (toString [this] name))

(def signToOp {"negate" -
               "+" +
               "-" -
               "*" *
               "/" myDiv
               "pow" (fn [x y] (Math/pow x y))
               "log" (fn [x y] (/ (Math/log (abs y)) (Math/log (abs x))))})

(deftype Operation [name args]
  Expression
  (evaluate [this arguments] (apply (get signToOp name) (mapv #(.evaluate % arguments) args)))
  (toString [this] (str "(" name " " (clojure.string/join " " args) ")"))
  )

(defn Op [sign]
  (fn [& args] (Operation. sign args)))

(def Add (Op "+"))
(def Divide (Op "/" ))
(def Multiply (Op "*"))
(def Subtract (Op "-"))
(def Negate (Op "negate"))
(def Pow (Op "pow"))
(def Log (Op "log"))
(defn Constant [value] (Const. value))
(defn Variable [name] (Var. name))
(defn evaluate [expr args] (.evaluate expr args))
(defn toString [expr] (.toString expr))

(def operationsObjectMap {'+ Add
                          'negate Negate
                          '* Multiply
                          '/ Divide
                          '- Subtract
                          'pow Pow
                          'log Log})

(defn parseObject [expression]
  (parse operationsObjectMap #(Const. %) #(Var. %) (read-string expression)))
