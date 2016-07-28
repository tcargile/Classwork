;this is the prototype for p3.scm (cs320 Program 3, Fall 2013)
;EDIT the next few comments to add header info (name, instructor, purpose, etc.)
;Trevor Cargile
;Dr. Carroll
;CS320 - Program 3
;November 2nd, 2013
;apart from adding the above header comments, leave this file section UNCHANGED
;To run this file, you would type (from the '%' prompt):
; scheme --load p3.scm
;

(load "~cs320/Scheme/simply.scm")
;Here I define a few handy lists that we can manipulate:
(DEFINE list1 (LIST 'a 'b 'c 'd 'e 'f 'g))
(DEFINE list2 (LIST 's 't 'u 'v 'w 'x 'y 'z))
(DEFINE list3 (LIST 'j 'k 'l 'm 'l 'k 'j))
(DEFINE list4 (LIST 'n 'o 'p 'q 'q 'p 'o 'n))
(DEFINE list5 '((a b) c (d e d) c (a b)) )
(DEFINE list6 '((h i) (j k) l (m n)))
;here is a typical function definition (from Page 681 of Sebesta):
(DEFINE (adder lis)
  (COND
    ((NULL? lis) 0)
    (ELSE (+ (CAR lis) (adder (CDR lis))))
))
;the above five lines are the sort of definition you would need to add to
;this file if you were asked to:
;"Create a function that accepts a single list as a parameter and returns
;the sum of the [numerical] atoms in the list.  To do this, uncomment the
;next DEFINE and modify it to conform to the specs."
; (DEFINE (adder ...complete this definition
; 
; 'adder' has already been defined for you (see above), but you must create
; the following four definitions [see ~cs320/program3 for full details]
; So, uncomment the next four DEFINEs, and modify them to conform to the
; specs given in the ~cs320/program3 writeup.

; (DEFINE (odds  ...complete this definition, as described in ~cs320/program3
; Algorithm explanation: First, if the input isn't a list, then it will prompt with message.
; Then, if the list is full, it will print the list (which is empty), otherwise it will check
; to see if the list has more than 1 element left in the list. Since my function takes the
; first element in the list each time, it will take that only element in the list because
; it will automatically be odd. If there are more than 1, take the first element, eliminate the
; next two, and start over again.
(DEFINE (odds lst)
    (COND
	((NOT (LIST? lst)) "USAGE: (odds [list])")
	((NULL? lst) lst)
	((NULL? (CDR lst)) CAR lst)
	(ELSE (CONS (CAR lst) (odds (CDDR lst))))
))
; (DEFINE (evenrev ...complete this definition, as described in ~cs320/program3
; Algorithm explanation: Like all my functions, if it isn't a list it will prompt with an
; error. First, this function will check if the list is empty and display it since an
; empty list is considered even and reversed. Next, it will check if there is only 1 element
; left. This last element will always be odd, so it will skip it and display an empty list,
; which won't be shown in the final result. If there are more than 1 element, it will take
; the second element and eliminate the first two elements. Then it will start over.
(DEFINE (evenrev lst)
    (COND
	((NOT (LIST? lst)) "USAGE: (evenrev [list])")
	((NULL? lst) lst)
	((NULL? (CDR lst)) '())
	(ELSE (append (evenrev (CDDR lst)) (CONS (CADR lst) '())))
))
; (DEFINE (penultimate ...complete this definition, as described in ~cs320/program3
; Algorithm explanation: Besides the error checker, this function first checks to see if
; the list is empty. If it is, display the empty list. This is true for any list that only
; has 1 element as well because there are no next to last elements. After these two checks
; it will see if there are only 2 elements left in the list. If so, grab the first and
; display it as a list by itself. If not, get rid of the first element in the list and
; go through it again.
(DEFINE (penultimate lst)
    (COND
	((NOT (LIST? lst)) "USAGE: (penultimate [list])")
	((NULL? lst) '())
	((NULL? (CDR lst)) '())
	((NULL? (CDDR lst)) (CONS (CAR lst) '()))
	(ELSE (penultimate (CDR lst)))
))
; (DEFINE (palindrome ...complete this definition, as described in ~cs320/program3
; Algorithm explanation: After the error check, the function checks to see if the list
; is empty, if it is then it is true (this is true for each recursive path because if
; the function makes it through all false checks, then there are an even number of elements
; and the last check will be for an empty list). If it isn't empty, check to see if there
; is only one element left. If so, then its true for the same reason above. If there are only
; two elements left, then check to see if those are true, and display whether the list is
; a palindrome or not based on this comparison. For the last case, if there are more than 2
; elements, take the first element and the last element and compare them. I created two functions
; to help do this. (endlist returns the last element in the list and noend returns a list with
; its last element gone). If the first and last elements match go through the process again
; with the first and last elements of the list gone. This will check each match for equality.
(DEFINE (palindrome lst)
    (COND
	((NOT (LIST? lst)) "USAGE: palindrome([list])")
	((NULL? lst) #T)
	((NULL? (CDR lst)) #T)
	((NULL? (CDDR lst)) (EQ? (CAR lst) (CADR lst)))
	((NOT (EQ? (CAR lst) (endlist lst))) #F)
	(ELSE (palindrome (CDR(noend lst))))
))
; Helper function to return a list with no end element
(DEFINE (noend lst)
    (COND
        ((NULL? (CDR lst)) '())
        (ELSE (CONS (CAR lst) (noend(CDR lst))))
))
; Helper function to return the last element of a list
(DEFINE (endlist lst)
    (COND
        ((NULL? (CDR lst)) (CAR lst))
        (ELSE (endlist(CDR lst)))
))

