#!r7rs

(import (scheme base) (scheme case-lambda) (scheme cxr) (scheme write))

(define (writeln/return x)
  ;;  Fonction très utile pour pouvoir afficher un résultat suivi d'un passage
  ;;  à la ligne, tout en pouvant récupérer ce résultat dans une variable. Les
  ;;  trois expressions suivantes sont évaluées en séquence et la valeur de la
  ;;  dernière est retournée.
  (write x)
  (newline)
  x)

;;;  ==========================================================================
;;;  Start

(writeln/return (cons 0 1))
(writeln/return (cons 0.1 0.1))
(writeln/return (cons (cons 0.1 0.1) 1))
(writeln/return (cons 0.1 '()))
(writeln/return (cons '() 0.1))
(writeln/return (cons '() '()))

(define current-year 2017)
(define next-year (+ current-year 1))
(define academic-year (cons current-year next-year))
(define academic-year-0 (cons current-year 'next-year))
(define academic-year-1 (cons 'current-year 'next-year))
(define operations (cons + -))
(define symbols (cons '+ '-))
(define two-numbers (cons 0 1))
(define something (cons (cons 0.1 0.1) 1))

;;  (writeln/return academic-year)
;;  (writeln/return (quote academic-year))
;;  (writeln/return 'academic-year)
;;  (writeln/return 'undefined)
;;  (writeln/return undefined)
;;  (writeln/return +)
;;  (writeln/return '+)
;; (writeln/return (0 . 1))
;;  (writeln/return '(0 . 1))
;;  (writeln/return (+ . 1))
;;  (writeln/return '(+ . 1))

;;  (writeln/return (car academic-year))
;;  (writeln/return (cdr academic-year))
;;  (writeln/return (car next-year))
;;  (writeln/return academic-year-0)
;;  (writeln/return (cdr academic-year-0))
;;  (writeln/return academic-year-1)

;;  (writeln/return ((car operations) (car two-numbers) (cdr two-numbers)))
;;  (writeln/return ((cdr symbols) (cdr two-numbers) (car two-numbers)))
;;  (writeln/return (cons (cdr symbols) (car two-numbers)))
;;  (writeln/return (cons (cdr operations) (cdr two-numbers)))
;;  (writeln/return ((cdr operations) (cdr two-numbers)))
;;  (writeln/return (car something))
;;  (writeln/return (cdr (car something)))
;   (writeln/return (car (cdr something)))

;;;  ==========================================================================
;;;  From Pairs to Lists

(define (free-family? v w) not (zero? (- (* (car v) (cdr w)) (* (cdr v) (car w))) #t #f))

;;;  ==========================================================================
;;;  Lists

;;  (writeln/return '(Sometime . ((to . ()) . ((() . miss) . (now . ())))))
;;  (writeln/return '((Everybody . ()) . (() . wants) . (somebody . ())))

;;  (writeln/return
;;   '((Thats . ((() . ()) . why)) . ((() . I) . ((need . (you . baby)) . ()))))

  (writeln/return (cons (list 'Aint 'nobody 'else 'around) '()))

  (writeln/return (list 'Someone (cons 'to '(squeeze))))

  (writeln/return (list (list 'I 'need 'you)
  			       (cons 'you (cons 'you '()))))

  (writeln/return (append (list 'And 'I)
			       (append '(need) '(you))
  			       (cons 'you '(you))))

  (writeln/return
   (cons 'I-m (append '((so glad)) (list 'to 'be 'here 'tonight))))

(writeln/return (car (cdr' (0 1 2)))) ;cadr

(writeln/return (car (cdr (cdr'(0 1 2))))) ;caddr

(writeln/return (cdr (cdr (cdr '(0 1 2))))) ;cdddr

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
;;;  Operations on mini data bases

(writeln/return (memq 'master '(here master players)))
(writeln/return (map (lambda (x) (+ x 1)) '(26 9 2017)))
(writeln/return (map key stan-getz-r))

(define (all-different? key-list)
  (if (null? key-list)
      #t
      (let ((key-list-0 (cdr  key-list)))
        (and (not (memq (car key-list) key-list-0)) (all-different? key-list-0)))))

(define (unique-keys? jazz-mbd)
  (all-different?(map key jazz-mbd)))

  (writeln/return (unique-keys? miles-davis-r))
  (writeln/return (unique-keys? stan-getz-r))

(define (get-information-e key-0 sel-0 j-list)
  (if (null? j-list) #f
      (let ((first (car j-list)))
      (if (eq? (key first) key-0)
          (sel-0 first)
          (get-information-e key-0 sel-0 (cdr j-list))))))

(writeln/return (get-information-e 'd6 title miles-davis-r))
(writeln/return (get-information-e 'd66 title miles-davis-r))
(writeln/return (get-information-e 'd0 authors miles-davis-r))

(writeln/return (equal? '"here" "here"))
(writeln/return (eq? 'test 'test))

(define (get-key x0 sel0 j-list)
  (if (null? j-list) #f
      (let ((first (car j-list)))
      (if (equal? (sel0 first) x0)
          (key first)
          (get-key x0 sel0 (cdr j-list))))))

(writeln/return (get-key "Chance It" title miles-davis-r))


(define (those-that p1? j-list f1)
   (if (null? j-list) '()
      (let ((first (car j-list))
            (more (those-that p1? (cdr j-list) f1)))
      (if (p1? first) (cons (f1 first) more) more))))

(writeln/return (those-that (lambda (j) (= (year j) 1972)) miles-davis-r title))


(define (those-that-v2 p1? j-list f1)
  (let loop ((j-list-0 j-list)
             (accumulator '()))
    (if (null? j-list-0)
        accumulator
        (loop (cdr j-list-0)
              (let ((first (car j-list-0)))
                (if (p1? first)
                    (cons (f1 first) accumulator)
                    accumulator))))))

; liste des oeuvres enregistrees par miles davis en 1972
(writeln/return (those-that-v2 (lambda (j) (= (year j) 1972)) miles-davis-r title))

; liste des cles des enregistrements de stan getz concernant les pieces ayant plusieurs auteurs
(writeln/return (those-that-v2 (lambda (j)
                                 (let ((authors-0 (authors j)))
                                   (and (pair? authors-0) (pair? (cdr authors-0)))))
                                        stan-getz-r key))

; la liste des cles des enregistrements de miles davis concernant les pieces ayant un seul auteur
(writeln/return (those-that-v2 (lambda (j)
                                 (let ((authors-0 (authors j)))
                                   (and (pair? authors-0) (null? (cdr authors-0)))))
                                        miles-davis-r key))

; la liste des noms des pieces enregistrees par miles davis ou stan getz pour lesquelles l'editeur est inconnu
(writeln/return (those-that-v2 (lambda (j)
                                 (unknown? (publisher j)))
                                        (append stan-getz-r miles-davis-r)
                                        title))

; la liste des cles des oeuvres enregistrees par miles david dont l'editeur est EMI
(writeln/return (those-that-v2 (lambda (j)
                                 (equal? (publisher j) 'EMI))
                                        miles-davis-r key))

; la liste des noms des oeuvres de milea david qu'il a lui meme enregistrees
(writeln/return (those-that-v2 (lambda (j)
                                 (let ((authors-0 (authors j)))
                                   (and (not (unknown? authors-0))
                                   (memq 'Miles-Davis authors-0))))
                                        miles-davis-r title))

; la liste des cles des oeuvres enregistrees par stan getz et reprises sur plusieurs compact discs
(writeln/return (those-that-v2 (lambda (j)
                                 (let ((cds-0 (cds j)))
                                   (and (pair? cds-0) (pair? (cdr cds-0)))))
                                        stan-getz-r key))

(define year-alist '((1960 . 2) (2000 . 3) (1950 . 2) (2010 . 3) (2017 . 1)))

(define (find-top-years year-alist-0)
  (let thru ((year-alist-1 year-alist-0)
             (current-maximum 0)
             (hit-parade '()))
    (if (null? year-alist-1)
        hit-parade
        (let* ((first (car year-alist-1))
               (first-occ-nb (cdr first)))
        (cond ((< first-occ-nb current-maximum)
               (thru (cdr year-alist-1) current-maximum hit-parade))
              ((= first-occ-nb current-maximum)
               (thru (cdr year-alist-1) current-maximum (cons (car first) hit-parade)))
              (else (thru (cdr year-alist-1) first-occ-nb (list (car first)))))))))
               
(writeln/return (find-top-years year-alist))

(define (update-year-alist j-list-0 year-alist)
  (if (null? j-list-0)
      year-alist
      (let ((first-year (year (car j-list-0))))
        (update-year-alist (cdr j-list-0)                  
                           (let loop ((year-alist-0 year-alist))
                            (if (null? year-alist-0)
                                (list (cons first-year 1)
                                      (let ((year-alist-1 (cdr year-alist-0)))
                                        (if (= (caar year-alist-0) first-year)
                                            (cons (cons first-year (+ (cdar year-alist-0) 1))
                                        year-alist-1)
                                      (cons (car year-alist-0) (loop year-alist-1)))))))))))

;(writeln/return (update-year-alist miles-davis-r '()))
;(writeln/return (top-year miles-davis-r))



  
;;;  ==========================================================================
;;;  Merge Sort

(define (mergesort l rel-2?)
  ;;  La clôture lexicale permet aux fonctions locales d'accéder à la relation
  ;;  d'ordre "rel-2?".
  ;;
  (define (merge-2-groups g0 g1)
    (cond ((null? g0) g1)
	  ((null? g1) g0)
	  (else (let ((first-0 (car g0))
		      (first-1 (car g1)))
		  (if (rel-2? first-0 first-1)
		      (cons first-0 (merge-2-groups (cdr g0) g1))
		      (cons first-1 (merge-2-groups g0 (cdr g1))))))))
  ;;
  (define (merge-groups group-list)
    (if (or (null? group-list) (null? (cdr group-list)))
	group-list
	(cons (merge-2-groups (car group-list) (cadr group-list))
	      (merge-groups (cddr group-list)))))
  ;;
  (define (make-groups l0)
    ;;  "l0" est une liste linéaire non vide.
    (let ((first (car l0))
	  (rest (cdr l0)))
      (if (null? rest)
	  (list (list first))
	  (let ((next-groups (make-groups rest)))
	    (if (rel-2? first (car rest))
		(cons (cons first (car next-groups)) (cdr next-groups))
		(cons (list first) next-groups))))))
  ;;
  (if (null? l)
      '()
      (let iter-merge-groups ((group-list (make-groups l)))
	(if (null? (cdr group-list))
	    (car group-list)
	    (iter-merge-groups (merge-groups group-list))))))

(define cp-list-example
  '((5 . 5) (6 . 0) (3 . 3) (6 . 1) (7 . 7) (1 . 1) (6 . 2)))

(writeln/return (mergesort cp-list-example (lambda (c0 c1)
                                             (let ((left-0 (car c0))
                                                   (left-1 (car c1)))
                                               (or (< left-0 left-1)
                                                   (and (= left-0 left-1)
                                                        (<= (cdr c0) (cdr c1))))))))


(writeln/return (mergesort miles-davis-r (lambda (j0 j1)
                                                 (let ((y0 (year j0))
                                                       (y1 (year j1)))
                                                           (or (< y0 y1)
                                                               (and (= y0 y1)
                                                                    (string<=? (title j0) (title j1))))))))

(define (pretty-writeln/return x)
  ;;  Writes "x", followed by an end-of-line character, and returns "x".  If
  ;;  "x" is a linear list, successive lines are used for successive elements.
  (if (and (pair? x) (list? x))
      (begin
	(write-char #\()
	(write (car x))
	(for-each (lambda (x0)
		    (newline)
		    (write-char #\space)
		    (write x0))
		  (cdr x))
	(write-char #\)))
      (write x))
  (newline)
  x)

;;;  ==========================================================================
;;;  Apotheosis

(define (position x l)
  (let thru ((l0 l)
	     (current-position 0))
    (cond ((null? l0) #f)
	  ((equal? (car l0) x) current-position)
	  (else (thru (cdr l0) (+ current-position 1))))))

(define add-something
  (case-lambda
   ((x) (+ x 1))
   ((x y) (+ x y))))
