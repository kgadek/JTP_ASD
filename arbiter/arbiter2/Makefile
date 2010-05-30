pokr: pokr.w
	cweave pokr.w && pdftex pokr.tex
	ctangle pokr.w && g++ -O2 -lm -g -ansi -pedantic -W -Wall pokr.c -o pokr
texclean:
	rm -f pokr pokr.c pokr.idx pokr.log pokr.scn pokr.tex pokr.toc 
progclean:
	rm -f pokr
clean: texclean progclean

hardclean: clean
	rm -f pokr.pdf pokr.dvi
