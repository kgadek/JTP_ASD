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

(defparameter dt nil)

(ql:quickload "cl-html-parse")

(with-open-file (in "~/mirror/mpk/rozklady.mpk.krakow.pl/aktualne/0144/t001.html")
  (setf dt
	(mpk-get-table-from-page
	 (html-parse:parse-html
      	  (read-line in nil)))))

;; Pokaż rozkład
(loop for x in dt do (format t "~A:~A~%" (mpk-read-hour x) (mpk-read-minutes-norm x)))
(loop for x in dt do (format t "~A:~A~%" (mpk-read-hour x) (mpk-read-minutes-sat x)))
(loop for x in dt do (format t "~A:~A~%" (mpk-read-hour x) (mpk-read-minutes-sun x)))

