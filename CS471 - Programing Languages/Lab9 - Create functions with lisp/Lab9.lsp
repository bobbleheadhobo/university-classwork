;;Name: Joey Troyer
;;Date: 11/16/22
;;Program: This program can do three things. One it can return the unique variables in a list. Two it can count the
;;         number of logical operators in a list. Three it can evaluate the logical operators AND, OR and NOT.


;; PRE: list
;; POST: Displays only the unique variables in the list
(define (uniq L)
    ;;if the list is empty return an empty list
    ( cond ((null? L) '() )

    ;;if not a list return an empty list
    ((not (list? L)) '() )

    ;;if the first item in the rest of the list get rid of it and recur through the list
    (( member (car L) (cdr L)) (uniq (cdr L)))

    ;;if the first item is not in the rest of the list just recur through the list
    (else ( cons (car L) (uniq (cdr L))))
    )
);; end uniq

;; PRE:  
;; POST: 
(define (clean L)
    ( cond ((null? L)'())
    ((eq? (car L) 1) (clean (cdr L)))
    ((eq? (car L) 0) (clean (cdr L)))
    ((eq? (car L) 'AND) (clean (cdr L)))
    ((eq? (car L) 'OR) (clean (cdr L)))
    ((eq? (car L) 'NOT) (clean (cdr L)))
    (else (cons (car L) (clean (cdr L))))
    )
);;end clean


;; PRE:  Flatten list of CD TERM we are looking for
;; POST: Count of term in LIST
(define (countem term L)
    ;; if list is null return 0
    ( cond ((null? L) 0)
        ;; if not a list return 0
        ((not (list? L)) 0)
        ;; if term equals the first item in the list then add one and recur with the last one in the list
        ((eq? term (car L)) (+ 1 (countem term (cdr L))))
        ;; if it does not equal then recur with the last on in the list
        ( else (countem term (cdr L)))
    )
);;end counttem



;; PRE:  CD
;; POST: calls appropriate function to reduce AND, OR, NOT
(define (reduce L)
    ( cond ((not (list? L)) L)
           ((eq? 'OR (car L)) (ro L))
           ((eq? 'NOT (car L)) (rn L))
           ((eq? 'AND (car L)) (ra L))
    )
);;end reduce



;; PRE:  CD
;; POST: reduces OR
(define (ro L)
    ;;reduces left hand side and right hand side
    ( let ([S1 (reduce (cadr L))]
           [S2 (reduce (caddr L))]
           )
           ;;if left hand side or right side is true displays 1
           (cond ((eq? S1 1) 1)
                 ((eq? S2 1) 1)

                 ;;if left hand side and rigth hand side are both false displays the value from the opposite side
                 ((eq? S1 0) S2)
                 ((eq? S2 0) S1)
                 (else (list 'or S1 S2))
            )
    )
);;end ro


;; PRE:  CD
;; POST: reduces NOT
(define (rn L)
    ;;reduces left hand side and right hand side
    ( let ([S1 (reduce (cadr L))]
           )
           ;;if value is 1 displays a 0
           (cond ((eq? S1 1) 0)
                 ;;if value if 0 displays a 1
                 ((eq? S1 0) 1)
                 (else (list 'NOT S1))
            )
    )
);;end rn


;; PRE:  CD
;; POST: reduces AND
(define (ra L)
    ;;reduces left hand side and right hand side
    ( let ([S1 (reduce (cadr L))]
           [S2 (reduce (caddr L))]
           )
           ;;if left hand side or right side is true displays value from opposite side
           (cond ((eq? S1 1) S2)
                 ((eq? S2 1) S1)

                 ;;if left hand side and rigth hand side are false displays 0
                 ((eq? S1 0) 0)
                 ((eq? S2 0) 0)
                 (else (list 'AND S1 S2))
            )
    )
);;end ra