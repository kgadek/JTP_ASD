pokr: pokr.w
	cweave pokr.w && pdftex pokr.tex
#	cweave pokr.w && tex pokr.tex && dvipdf pokr.dvi
	ctangle pokr.w - pokr.cpp && g++ -W -Wall -Wshadow\
		-Wformat -Wsequence-point -Wunused\
		-Wuninitialized -Wfloat-equal -ansi\
		-pedantic -Weffc++ -g -O0 -lm pokr.cpp -o pokr
texclean:
	rm -f pokr pokr.c pokr.idx pokr.log pokr.scn pokr.tex pokr.toc 
progclean:
	rm -f pokr
clean: texclean progclean

hardclean: clean
	rm -f pokr.pdf pokr.dvi
