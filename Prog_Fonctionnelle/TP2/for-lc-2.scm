#!r7rs

(import (scheme base) (scheme write))

(define (writeln/return x)
  ;;  Fonction très utile pour pouvoir afficher un résultat suivi d'un passage
  ;;  à la ligne, tout en pouvant récupérer ce résultat dans une variable. Les
  ;;  trois expressions suivantes sont évaluées en séquence et la valeur de la
  ;;  dernière est retournée.
  (write x)
  (newline)
  x)

(define (first-mystery n)
  ;;  Rappelons que les fonctions "quotient" et "remainder" retournent
  ;;  respectivement le quotient entier et le reste d'une division euclidienne,
  ;;  à condition, bien sûr, que le diviseur ne soit pas nul.
  (if (< n 10) n (+ (first-mystery (quotient n 10)) (remainder n 10))))

(define (second-mystery n p)
  ;;
  (define (rec-mystery n0 p0)
    ;;  Rappelons �galement qu'une forme sp�ciale "define" interne � une forme
    ;;  "lambda " est �quivalente � l'utilisation d'une forme sp�ciale
    ;;  "letrec*".
    (if (zero? (remainder n0 p0)) (rec-mystery (quotient n0 p0) p0) n0))
  ;;
  ;;  Principal call:
  (if (or (zero? p) (zero? n)) n (rec-mystery n p)))

(define (volume-at t v0 lambdaB)
  (* v0 (+ 1 (* lambdaB t))))

(define absolute-zero -273.15)

(define (body->volume-at lambdaB)
  (lambda (t v0)
           (* v0
              (+ 1 (* lambdaB t)))))

(define gas-volume-at
  (body->volume-at
          (/ (- absolute-zero))))

(define (in-inches miles0 yards0 feet0 inches0)
  (let* ((in-yards0 (+ (* miles0 1760) yards0))
        (in-feet0 (+ (* in-yards0 3) feet0))
        (in-inches0 (+ (* in-feet0 12) inches0)))
    in-inches0))


(define (british-to-metric miles0 yards0 feet0 inches0)
  (* (in-inches miles0 yards0 feet0 inches0) 25.4))


(define (to-metric nb1 nb2 nb3 metric0)
  (lambda (x1 x2 x3 x4)
    (let* ((in-unit1 x1)
          (in-unit2 (+ (* in-unit1 nb1) x2))
          (in-unit3 (+ (* in-unit2 nb2) x3))
          (in-unit4 (+ (* in-unit3 nb3) x4)))
      (* in-unit4 metric0))))


(writeln/return
 ((to-metric 24 60 60 1)
 1 3 47 48))

 (writeln/return
  ((to-metric 10 2 12 (/ 1.13389 10 2 12))
 12 3 1 6))

(writeln/return
 (first-mystery 99999999999))


(define (one-digit n)
  (let ((n0 (first-mystery n)))
  (if (> n0 10) (one-digit n0) n0)))


(writeln/return
 (one-digit 99999999999))

(writeln/return
 (second-mystery 1022 2))


(define (haming-number1 n)
  (let* ((n1 (second-mystery n 2))
         (n2 (second-mystery n1 3))
         (n3 (second-mystery n2 5)))
    (= n3 1)))

(define (haming-number2 n)
    (= (second-mystery (second-mystery (second-mystery n 2) 3) 5) 1))

(writeln/return
 (haming-number2 14))

(define (diagonal n)
  (if (zero? n)
      (cons 0 0)
      (let* ((rec (diagonal (- n 1)))
             (p (car rec))
             (q (cdr rec)))
        (if (zero? q)
            (cons 0 (+ p 1))
            (cons (+ p 1) (- q 1))))))

(writeln/return
 (diagonal 5))
