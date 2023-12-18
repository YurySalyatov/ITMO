(defn red_func [f & args]
  (reduce f args))
(defn vect_binary [f]
  (fn [& args] (reduce (fn [a b]
                         {:pre [(== (count a) (count b))]}
                         (mapv f a b)) args))
  )
(defn vect_mul [a b]
  {:pre [(== (count a) (count b) 3)]}
  (vector (- (* (nth a 1) (nth b 2)) (* (nth a 2) (nth b 1))) (- (* (nth a 2) (nth b 0)) (* (nth a 0) (nth b 2))) (- (* (nth a 0) (nth b 1)) (* (nth a 1) (nth b 0)))))
(defn matrix_binary [f]
  (fn [& args] (reduce (fn [a b]
                         {:pre [(== (count a) (count b))]}
                         (mapv (vect_binary f) a b)) args))
  )
(def v+ (vect_binary +))
(def v- (vect_binary -))
(def v* (vect_binary *))
(def vd (vect_binary /))
(defn scalar [& args]
  (reduce + (reduce v* args)))
(defn vect [& args]
  (reduce vect_mul args))
(defn v*s [& args]
  (mapv #(* % (reduce * (rest args))) (first args)))
(def m+ (matrix_binary +))
(def m- (matrix_binary -))
(def m* (matrix_binary *))
(def md (matrix_binary /))
(defn transpose [matr]
  (apply mapv vector matr))
(defn m*s [& args]
  (mapv #(v*s % (reduce * (rest args))) (first args)))
(defn matrix_scal [a b]
  (mapv #(scalar % b) a))
(defn matrix_vec_mul [m v]
  {:pre [(== (count (first m)) (count v))]}
  (matrix_scal m v))
(defn m*v [& args]
  (reduce matrix_vec_mul args))
(defn m*m [& args](reduce (fn [a b]
                   {:pre [(== (count (first a)) (count b))]}
                   (transpose (map #(matrix_scal a %) (transpose b)))) args))
(defn s_binary [f]
  (fn [& args] (reduce (fn [a b]
                         (if (and (number? a) (number? b))
                           (f a b)
                           (mapv #((s_binary f) %1 %2) a b))) args))
  
  )
(def s+ (s_binary +))
(def s- (s_binary -))
(def s* (s_binary *))
(def sd (s_binary /))
;; (print (m+ [[1 2] [3 4]] [[4 5] [5 6]]))
;; (print (s+ 4 5))
;; (print (s+ [1 2 3] [4 5 6]))
;; (print (number? [1 2 3]))
;; (print (s+ (vector (vector 5.2 (vector 4.4))) (vector (vector 3.1 (vector 9.9)))))