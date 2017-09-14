#!r7rs
(import (scheme base) (scheme inexact) (scheme write))
;;  Importation des bibliothèques prédéfinies nécessaires. Pour l'instant,
;;  retenez simplement que vous aurez toujours besoin de "base". De même, nous
;;  importerons toujours "write" pour réaliser des affichages à l'écran. Nous
;;  vous signalerons l'importation d'autres bibliothèques le cas échéant : ici,
;;  "inexact", car nous utilisons quelques fonctions trigonométriques et
;;  logarithmiques.

(write (+ 2017 (* (+ 22 1) (/ 14 (- 9 2)))))  ;  (*)

(newline)
(write "Hello world!")
(newline)
(display "Hello world!")
(newline)

(write ((lambda (x) (* x x)) 2016))  ;  (**)

(newline)

(define crash          ;  (***)  Pour bien montrer que Scheme n'�value pas sous
  (lambda () (/ 0)))   ;  la forme sp�ciale "lambda".

(define derive-wrt
  (lambda (f1 h)
    (lambda (x) (/ (- (f1 (+ x h)) (f1 x)) h))))

(write ((derive-wrt (lambda (x) (* x x)) 0.0001) 2))
(newline)

(write ((derive-wrt + 0.0001) 2))  ;  (****)

(define fact
  (lambda (n) (if (zero? n) 1 (* n (fact (- n 1))))))

(newline)
(write (fact 6))
(newline)

(define pi (* 4 (atan 1)))  ;  "atan" est la fonction "Arc tangente" en Scheme.

(define power
  (lambda (U I f0) (* U I (cos (* 2 pi f0)))))

(define fq->power
  (lambda (f0)
    (let ((coefficient (cos (* 2 pi f0))))
      (lambda (U I) (* coefficient U I)))))

(newline)
(write (+))
(newline)
(write(+ 6 10 217 1))
(newline)
(write(*))
(newline)
(write(* 12 10 2017 2))
(newline)

;;(write(-))
(newline)
(write(- 1))
(newline)
(write(- 7 2 2017 2))
(newline)

(write(/ 6 3))
(newline)
(write(/ 3 2))
(newline)

(write(/ 3.0 2.0))
(newline)
(write(+ 1 1.1))
(newline)
(write(/ 3.0 2))
(newline)

(write(/ 4 3))
(newline)
(write(quotient 4 3))
(newline)

(write(remainder 4 3))

(newline)

(write(remainder 4 3))

(newline)

(write(+ (* 4.1 9.8) (/ (* 2 pi) 3)))

(newline)

(write(+ (exp pi) (log (sin 2.1) 2) (sin (+ (/ 1 pi) pi)))) ;; ln = (log ... 2)

(newline)

(write((lambda (x) (* x x)) 2017))
(newline)
;;(write((lambda (x y) (* x y y)) 2017))
(newline)
(write((lambda (x y) (* x y y)) 2017 2016))
(newline)
;;(write((lambda (x y) (* x y y)) 2017 2016 2015))


(newline)

(write (2017))
(newline)
(write (lambda () 2017))
(newline)
(write ((lambda () 2017)))

(newline)
       
(write +)
(newline)
(write (+))
(newline)

(write(2017))
(newline)
(write((lambda () 2017)))
(newline)
(write ((lambda () 2017)))
(newline)
(write ((lambda () (lambda () 2017))))

(newline)

(write ((derive-wrt (lambda (x y) (+ (* 2 x) y)) 0.0001) 2))

(newline)

(write (power 220 7 50))

(newline)

(define power-50 (fq->power 50))
;;(define-50 220 7)
((fq->power 50) 220 7)




(define (pgcd x y)

    ;;local function
  (define (euclide a b)
  ;; a >= b > 0 assumed.
    (let ((the-remainder (remainder (a b)))
        (if (zero? the-remainder) b (euclide b the-remainder)))))

  
  (if (or (zero? x) (zero? y))
      (begin
        (display "can't do that sorry!")
        (newline)
        #f)
      (let ((x0 (abs x))
            (y0 (abs y)))
        (if (>= x0 y0) (euclide x0 y0) (euclide y0 x0)))))
  