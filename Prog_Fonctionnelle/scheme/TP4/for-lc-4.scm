#!r7rs

(import (scheme base) (scheme case-lambda) (scheme cxr) (scheme write))

(define (writeln/return x)
  (write x)
  (newline)
  x)

;;;  ==========================================================================
;;;  Mini data bases

(define unknown '??)

(define (unknown? x)
  (eq? x unknown))

(define (mk-recording key-0 title-0 author-list-0 year-0 publisher-0
		      key-list-0)
   ;; SYMBOL,STRING,LIST-of[SYMBOL}^,INTEGER,SYMBOL^,LIST-of[SYMBOL]^ -> JAZZ-R
  (list key-0 title-0 author-list-0 year-0 publisher-0 key-list-0))

(define miles-davis-r
  (list (mk-recording 'd0 "On the Corner" unknown 1972 unknown '(c40))
	(mk-recording 'd1 "New-York Girl" unknown 1972 unknown '(c40))
	(mk-recording 'd2 "Thinkin' One Thing and Doin' Another" unknown 1972
		      unknown '(c40))
	(mk-recording 'd3 "One and One" unknown 1972 unknown '(c40))
	(mk-recording 'd4 "Well You Needn't" '(Thelonius-Monk) 1954
		      'Blue-Ribbon-Music '(c41))
	(mk-recording 'd5 "Love for Sale" '(Cole-Porter) 1958 'Chappell '(c41))
	(mk-recording 'd6 "Something Else" '(Miles-Davis) 1958 'EMI '(c41))
	(mk-recording 'd7 "Dear Old Stockholm" '(Stan-Getz P-Golly) 1952
		      'Windswept-Pacific-Music '(c41))
	(mk-recording 'd8 "Black Satin" unknown 1972 unknown '(c40))
	(mk-recording 'd9 "Mr. Freedom X" unknown 1972 unknown '(c40))
	(mk-recording 'd10 "Helen Butte" unknown 1972 unknown '(c40))
	(mk-recording 'd11 "Boplicity" '(Cleo-Henry) 1949 'Campbell '(c40))
	(mk-recording 'd12 "Ray's Idea" '(Ray-Bonner W-G-Fuller) 1953
		      'Bosworth '(c41))
	(mk-recording 'd13 "Yesterdays" '(Kern Harbach) 1952 'Universal '(c42))
	(mk-recording 'd14 "Vote for Miles" unknown 1972 unknown '(c40))
	(mk-recording 'd15 "Deception" '(Miles-Davis) 1950 'Sony '(c41))
	(mk-recording 'd16 "Israel" '(John-Carisi) 1949 'EMI '(c41))
	(mk-recording 'd17 "How Deep is the Ocean" '(Irving-Berlin) 1952 'EMI
		      '(c41))
	(mk-recording 'd18 "Kelo" '(Jay-Jay-Johnson) 1953 'Kensington-Music
		      '(c41))
	(mk-recording 'd19 "Woody 'n' You" '(Dizzy-Gillepsie) 1952 'Chappell
		      '(c41))
	(mk-recording 'd20 "Chance It" '(Oscar-Petitford) 1952 'Orpheus-Music
		      '(c41))))

(define stan-getz-r
  (list (mk-recording 'g30 "Autumn Leaves" '(Kosma Prevert) 1980
		      'Peter-Maurice-Co-Ltd '(c44))
	(mk-recording 'g31 "Nature Boy" '(Abbon) 1980 'Chappell '(c44))))

(define key car)
(define title cadr)
(define authors  caddr)
(define year cadddr)
(define (publisher jazz-r0) (car (cddddr jazz-r0)))
(define (cds jazz-r0) (cadr (cddddr jazz-r0)))

;;;  ==========================================================================


(writeln/return (call-with-values (lambda () (values 'L 3)) cons))

(writeln/return (let ((a 'sure)
		      (b 'here)
		      (x 'little)
		      (y 'players))
		  (let-values (((a b) (values x y))
			       ((x y) (values a b)))
		    (list a b x y))))

(writeln/return (let ((a 'sure)
		      (b 'here)
		      (x 'little)
		      (y 'players))
		  (let*-values (((a b) (values x y))
				((x y) (values a b)))
		    (list a b x y))))

(writeln/return (let-values (((first) (car '(very little players)))
			     ((the-quotient the-remainder) (truncate/ 2000 9)))
		  (cons the-quotient (cons the-remainder first))))

(define (take n l)
  (if (zero? n) '() (cons (car l) (take (- n 1) (cdr l)))))

(define (drop n l)
  (if (zero? n) l (drop (- n 1) (cdr l))))

(define (take-while p1? l)
  (if (null? l)
      '()
      (let ((first (car l)))
	(if (p1? first) (cons first (take-while p1? (cdr l))) '()))))

(define (drop-while p1? l)
  (if (or (null? l) (not (p1? (car l)))) l (drop-while p1? (cdr l))))

(define-syntax write-values
  (syntax-rules ()
    ((write-values the-values) (let ((nothing-string "*nothing*")
				     (and-string " *and* "))
				 (call-with-values (lambda () the-values)
				   (lambda arg-list
				     (if (null? arg-list)
					 (display nothing-string)
					 (begin
					   (write (car arg-list))
					   (for-each (lambda (arg)
						       (display and-string)
						       (write arg))
						     (cdr arg-list))))
				     (newline)
				     #t))))))


(define (split-at n l)
  (if (zero? n)
      (values '() l)
      (call-with-values (lambda () (split-at (- n 1) (cdr l)))
                        (lambda (left right)
                          (values (cons (car l) left) right)))))

(write-values (split-at 3 '(0 0 7 James Bond)))
(write-values (split-at 0 '(What a pain)))


(define(span p1? l)
  (if (null? l)
      (values '() '())
      (let ((first (car l)))
        (if (p1? first)
            (call-with-values (lambda () (span p1? (cdr l)))
                              (lambda (left right)
                                (values (cons first left) right)))
             (values '() l)))))


(define (map-3-functions f1 g1 h1 l)
  (if (null? l)
      (values '() '() '())
      (let ((first (car l)))
        (let-values (((left middle right) (map-3-functions f1 g1 h1 (cdr l))))
          (values (cons (f1 first) left) (cons (g1 first) middle)
                  (cons (h1 first) right))))))

(write-values (map-3-functions (lambda (x) (+ x 1)) (lambda (x) (* 2 x)) (lambda (x) (* x x)) '(14 10 2017)))


(define (extract-max-author-nb/max-year j-list)
  (let thru ((j-list-0 j-list)
             (current-max-author-nb 0)
             (current-max-year 0))
    (if (null? j-list-0)
        (values current-max-author-nb current-max-year)
        (let *((first (car j-list-0)))
          (first-authors (authors first)))
          (thru (cdr j-list-0)
                (max current-max-author-nb
                     (if (unknown? first-authors) 0 (length first-authors)))
                (max current-max-year (year first))))))

(define (assq-split x alist)
  (let thru ((alist-0 alist)
             (alist-accumulator '()))
    (if (null? alist-0)
        (values #f alist-accumulator)
        (let ((first-association (car alist-)))
        (if (eq? (car first) x)
            (values first-association
                    (append alist-accumulator (cdr alist-0)))
            (thru (cdr alist-0)
            (cons first-association alist-accumulator)))))))

(define (merge-alists alist alist-0)
  (let loop ((alist-bis alist)
             (alist-0-bis alist-0)
             (alist-accumulator '())
             (key-list-accumulator '()))
    (if (null? alist-bis)
        (values (append alist-0-bis alist-accumulator) key-list-accumulator)
        (let* ((first-association (car alist-bis))
               (first-key (car first-association)))
          (let-values (((association-0 alist-o-ter)
                        (assq-split first-key alist-0-bis)))
            (if ( and association-0
                      (not (equal? (cdr first-association) (cdr association-0)))))
            (loop (cdr alist-bis) alist-0-ter alist-accumulator
                  (cons first-key key-list-accumulator))
            (loop (cdr alist-bis) alist-0-ter (cons first-association alist-accumulator)
                  Key-list-accumulator))))))

;; recursif terminal car sa fini par l'apelle recursif
(define (included-into? l0 l1)
  (or (null? l0) (and (member (car l0) l1) (included-into? (cdr l0) l1) #f)))

(define (same-ets? l0 l1)
  (and (included-into? l0 l1) (included-into? l1 l0)))

(define (memq x l)
  (cond ((null? l) #f)
        ((eq? (car l) x) l)
        (else (memq x (cdr l)))))

(define (find-tail p1? l)
  (cond ((null? l) #f)
        ((p1? (car l)) l)
        (else (find-tail p1? (cdr l)))))

(define (memq-rd x l)
  (find-tail (lambda (y) (eq? y x)) l))

(define (member-rd x l)
  (find-tail (lambda (y) (equal? y x)) l))

(define (find p1? l)
  (if (null? l)
      #f
      (let ((first (car l)))
        (if (p1? first) first (find p1? (cdr l))))))

(define (assq-ff x alist)
  (find-tail (lambda (association) (eq? (car association) x)) alist))

            