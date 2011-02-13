(ql:quickload "cl-html-parse")

(defun subtree-search (tree pat)
  (when (and (not (null tree))
	     (consp tree))
    (nconc (if (and (consp (car tree))
		    (eql (caar tree) pat))
	       (list (car tree))
	       (subtree-search (car tree) pat))
	   (subtree-search (cdr tree) pat))))

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

(defun split-string-by-one-space (str)
  (loop for i = 0 then (1+ j)
       as j = (position #\Space str :start i)
       collect (subseq str i j)
       while j))
(defun split-string-by-space (str)
  (delete "" (split-string-by-one-space str) :test #'equal))
(defun get-ints-from-string (str)
  (mapcar #'(lambda(x) (parse-integer x :junk-allowed t))
	  (split-string-by-space str)))

(defun print-tag (name atts &optional (closingp nil))
  (format nil "~&<~A~A~{~A~}>~%"
	  (if closingp "/" "")
	  (string-downcase name)
	  (mapcar #'(lambda (att)
		      (format nil " ~A=\"~A\""
			      (string-downcase (car att))
			      (cdr att)))
		  atts)))
(defmacro tag (name atts &body body)
  `(concatenate 'string
		(print-tag ',name
			   (list ,@(mapcar #'(lambda(x)
					       `(cons ',(car x) ,(cadr x)))
					   atts)))
		,@body
		(print-tag ',name nil t)))

;; Line -- numer linii
(defmacro :l (n &body body)
  `(tag l ((n ,n)) ,@body))
;; Day -- dzień (0 - roboczy, 1 - sobota, 2 - niedziela)
(defmacro :d (d &body body)
  `(tag d ((d ,d)) ,@body))
;; Stop -- przystanek
(let ((stops (make-hash-table))
      (cnt 0))
  (defmacro :s (x &body body)
    (when (not (gethash x stops))
      (incf cnt)
      (setf (gethash x stops) cnt))
    `(tag s ((i ,(gethash x stops))) ,@body)))
;; Time -- godzina odjazdu
(defmacro :t (h m)
  `(tag t nil (tag h nil (format nil "~A" ,h)) (tag m nil (format nil "~A" ,m))))

(defun show-line-xml (filename day)
  (let ((dt nil))
    (with-open-file (in filename)
      (setf dt
	    (mpk-get-table-from-page
	     (html-parse:parse-html
	      (read-line in nil))))
      (loop for day from 0 to 2 do
	   
      (case day
	((:norm :week) (loop for x in dt when (not (null (mpk-read-minutes-norm x)))
	      do (format t "~A:~A~%" (mpk-read-hour x) (mpk-read-minutes-norm x))))
	(:sat (loop for x in dt when (not (null (mpk-read-minutes-norm x)))
	      do (format t "~A:~A~%" (mpk-read-hour x) (mpk-read-minutes-sat x))))
	(:sun (loop for x in dt when (not (null (mpk-read-minutes-norm x)))
	      do (format t "~A:~A~%" (mpk-read-hour x) (mpk-read-minutes-sun x))))
	(otherwise nil))))))
(defun show-tables (line stop day)
  (show-tables-raw (format nil "rozklady.mpk.krakow.pl/aktualne/~4,'0D/~4,'0Dt~3,'0D.htm.html" line line stop)
		   day))
