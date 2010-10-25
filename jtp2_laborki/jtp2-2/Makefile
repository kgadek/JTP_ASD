CXX	= javac
CXXFLAGS =-encoding UTF-8 -g -verbose -d bin
DOCFLAGS =-d doc
SRC	= Tablica.java Tablica_wlasneWyjatki.java Macierze.java
PKGNAME	= GadekKonrad-jtp2-1.tgz

.PHONY: clean all pkg check_dirstruct doc

all: check_dirstruct $(SRC:.java=) doc

clean:
	rm -f $(PKGNAME) *~ .*.swp *.class
	rm -rf doc bin

check_dirstruct:
	[ -d bin ] || mkdir bin
	[ -d doc ] || mkdir doc
	[ -d src ] || mkdir doc

doc:
	#javadoc $(DOCFLAGS) $(SRC)

pkg: clean 
	tar -zcf $(PKGNAME) $(SRC) Makefile

%: %.java
	$(CXX) $(CXXFLAGS) $?

