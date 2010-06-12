pokr: pokr.w
	cweave pokr.w && pdftex pokr.tex
#	cweave pokr.w && tex pokr.tex && dvipdf pokr.dvi
	ctangle pokr.w && g++ -W -Wall -Wshadow\
		-Wformat -Wsequence-point -Wunused\
		-Wuninitialized -Wfloat-equal -ansi\
		-pedantic -g -O2 -lm pokr.c -o pokr
texclean:
	rm -f pokr pokr.c pokr.idx pokr.log pokr.scn pokr.tex pokr.toc 
progclean:
	rm -f pokr
clean: texclean progclean

hardclean: clean
	rm -f pokr.pdf pokr.dvi
