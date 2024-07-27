(defn mapsOperations [f]
  (fn [& operands]
    (apply mapv f operands))
  )

(def v+ (mapsOperations +))
(def v* (mapsOperations *))
(def v- (mapsOperations -))
(def vd (mapsOperations /))
(defn v*s [vect scal]
  (mapv (fn [x] (* x scal)) vect))
(defn scalar [& args]
  (reduce + (apply v* args)))
(defn vect [& args]
  (reduce (fn [vector1 vector2]
            (letfn ([getDet [i j] (- (* (get vector1 i) (get vector2 j)) (* (get vector1 j) (get vector2 i)))])
              (vector (getDet 1 2) (- (getDet 0 2)) (getDet 0 1)))) args))


(def m+ (mapsOperations v+))
(def m* (mapsOperations v*))
(def m- (mapsOperations v-))
(def md (mapsOperations vd))
(defn m*s [mat scal]
  (mapv (fn [x] (v*s x scal)) mat))
(defn transpose [matrix]
  (apply mapv vector matrix))
(defn m*v [matrix vec]
  (mapv (fn [x] (apply + (mapv * x vec))) matrix))
(defn m*m [matrix1 matrix2]
  (transpose (mapv (fn [x] (m*v matrix1 x)) (transpose matrix2))))

(def c4+ (mapsOperations #(mapv m+ %1 %2)))
(def c4- (mapsOperations #(mapv m- %1 %2)))
(def c4* (mapsOperations #(mapv m* %1 %2)))
(def c4d (mapsOperations #(mapv md %1 %2)))
