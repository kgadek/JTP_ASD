pokr: pokr.w
	cweave pokr.w && pdftex pokr.tex
	ctangle pokr.w && g++ -O2 -lm -g -ansi -pedantic -W -Wall pokr.c -o pokr
clean:
	rm -f pokr.c pokr.idx pokr.log pokr.scn pokr.tex pokr.toc 
