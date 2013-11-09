
#lang racket

(provide (all-defined-out)) 

; 1
(define (sequence low high stride)
  (letrec ([loop (lambda(i) (if (< high i)
                                null
                                (cons i (loop (+ i stride)))))])
    (loop low)))

; 2
(define (string-append-map xs suffix)
  (map (lambda (s) (string-append s suffix)) xs))

; 3
(define (list-nth-mod xs n)
  (cond [(< n 0)     (error "list-nth-mod: negative number")]
        [(null? xs)  (error "list-nth-mod: empty list")]
        [#t (list-ref xs (remainder n (length xs)))]))

; 4
(define (stream-for-n-steps s n)
  (if (= n 0) null (cons (car (s)) (stream-for-n-steps (cdr (s)) (- n 1)))))

; 5
(define funny-number-stream 
  (letrec ([f (lambda (x) (cons (if (= 0 (remainder x 5)) (- 0 x) x) (lambda () (f (+ x 1)))))])
    (lambda () (f 1))))

; 6
(define dan-then-dog
  (lambda () (cons "dan.jpg" (lambda () (cons "dog.jpg" dan-then-dog)))))

; 7
(define (stream-add-zero s)
  (lambda () (cons (cons 0 (car (s))) (stream-add-zero (cdr (s))))))

; 8
(define (cycle-lists xs ys)
  (letrec ([f (lambda (n) (cons (cons (list-nth-mod xs n) 
                                      (list-nth-mod ys n)) 
                                (lambda () (f (+ n 1)))))])
    (lambda () (f 0))))

; 9
(define (vector-assoc v vec)
  (letrec ([len (vector-length vec)]
           [f (lambda (n) (cond [(= n len) #f]
                                [(not (pair? (vector-ref vec n))) (f (+ n 1))]
                                [(equal? v (car (vector-ref vec n))) (vector-ref vec n)]
                                [#t (f (+ n 1))]))])
    (f 0)))

; 10
(define (cached-assoc xs n)
  (letrec ([cache (make-vector n #f)]
           [index 0]
           [f (lambda (v) 
                (let ([ans (vector-assoc v cache)])
                  (if ans
                      ans 
                      (let ([new-ans (assoc v xs)])
                        (if new-ans
                            (begin
                              (vector-set! cache index new-ans)
                              (set! index (remainder (+ index 1) n))
                              new-ans)
                            #f)))))])
    f))
                  
; 11 - Challenge Problem
(define-syntax while-less
  (syntax-rules (do)
    [(while-less e1 do e2)
     (letrec ([pr e1]
              [f (lambda () (let ([res e2]) (if (< res pr)
                                                  (f)
                                                  #t)))])
       (f))]))







