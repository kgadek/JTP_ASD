(ql:quickload "cl-html-parse")

;;; ################################################################################
;;; MPK
;;; ################################################################################
(defun mpk-get-filename (line stop)
  (format nil "rozklady.mpk.krakow.pl/aktualne/~4,'0D/~4,'0Dt~3,'0D.htm.html" line line stop))
(defun mpk-get-table-from-page (x)
  (cddr (cadadr (caddar (cdaddr (caddar x))))))
(defun mpk-read-hour (x)
  (cadadr (cadr x)))
(defun mpk-read-minutes-norm (x)
  (cadr (caddr x)))
(defun mpk-read-minutes-sat (x)
  (cadar (cddddr x)))
(defun mpk-read-minutes-sun (x)
  (cadar (cddr (cddddr x))))
(defun mpk-read-stop (x)
  (cadr (cadadr (caddar (cdadar (cdadar (cdaddr (caddar dt))))))))


;;; ################################################################################
;;; String/Lisp operations
;;; ################################################################################
(defun split-string-by-one-space (str)
  (loop for i = 0 then (1+ j)
       as j = (position #\Space str :start i)
       collect (subseq str i j)
       while j))
(defun split-string-by-space (str)
  (delete "" (split-string-by-one-space str) :test #'equal))
(defmacro split (val yes no)
  (let ((g (gensym)))
    `(let ((,g ,val))
       (if ,g
	   (let ((head (car ,g))
		 (tail (cdr ,g)))
	     ,yes)
	   ,no))))
(defun pairs (lst)
  (labels ((f (lst acc)
	     (split lst
		    (if tail
			(f (cdr tail)
			   (cons (cons head (car tail))
				 acc))
			(reverse acc))
		    (reverse acc))))
    (f lst nil)))


;;; ################################################################################
;;; XML
;;; ################################################################################
(defun tag1% (name &key attr single closing)
  (format nil "<~A~A~A~A>~%"
	  (if closing "/" "")
	  (string-downcase name)
	  (if attr
	      (reduce #'(lambda(a b)
			  (concatenate 'string a b))
		      (loop for i in (pairs attr)
			 collect (format nil " ~a=\"~a\"" (car i) (cdr i))))
	      "")
	  (if single " /" "")))
(defmacro tag1 (name &key attr single closing noenter)
  `(tag1% ',name :attr ',attr :single ,single :closing ,closing))
(defmacro tag (name attr &body body)
  `(concatenate 'string
		(tag1 ,name :attr ,attr)
		,@body
		(tag1 ,name :closing t)))
(defmacro :xml (&body body)
  `(concatenate 'string
		"<?xml version=\"1.0\" encoding=\"UTF-8\"?>~%"
		,@body))

;;; ################################################################################
;;; Printing
;;; ################################################################################
(defun show-tables-raw (filename day)
  (let ((dt nil))
    (with-open-file (in filename)
      (setf dt
	    (mpk-get-table-from-page
	     (html-parse:parse-html
	      (read-line in nil))))
      (case day
	((:norm :week) (loop for x in dt when (not (null (mpk-read-minutes-norm x)))
	      do (format t "~A:~A~%" (mpk-read-hour x) (mpk-read-minutes-norm x))))
	(:sat (loop for x in dt when (not (null (mpk-read-minutes-norm x)))
	      do (format t "~A:~A~%" (mpk-read-hour x) (mpk-read-minutes-sat x))))
	(:sun (loop for x in dt when (not (null (mpk-read-minutes-norm x)))
	      do (format t "~A:~A~%" (mpk-read-hour x) (mpk-read-minutes-sun x))))
	(otherwise nil)))))
(defun show-precise-xml (line stop day)
  (let ((dt nil)
	(stop-name "?"))
    (with-open-file (in (mpk-get-filename line stop))
      (setf dt (html-parse:parse-html (read-line in nil))))
    (setf stop-name (mpk-read-stop dt)
	  dt (mpk-get-table-from-page dt))
    (format t "Nazwa: ~A~%" stop-name)
    (:l line (eval `(:s ,stop-name
			(reduce #'(lambda(a b) (concatenate 'string a b))
				(loop for d from 0 to 2
				   collect (:d d))))))))
(defun show-tables (line stop day)
  (show-tables-raw (mpk-get-filename line stop) day))
