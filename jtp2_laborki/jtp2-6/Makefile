CXX	= javac
CXXFLAGS =-encoding UTF-8 -g -verbose -d bin
DOCFLAGS =-d doc
SRC	= Sthack SynchStack
PKGNAME	= GadekKonrad-jtp2-5.tar.7z
PKGOPT	= -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on

.PHONY: clean all pkg doc check_dirstruct

all: check_dirstruct $(SRC:.java=) doc Externalizacja Kalkulet\
				 FileCache Matrix kwa\
				 person wc\
				 FileReader Person
# Externalizacja i Kalkulet to programy autorstwa Grze¶ka Jurasa
# origin: http://student.agh.edu.pl/~juras/JTP2/lab.5/
# FileCache, Matrix i kwa to programy autorstwa Szymona Guta
# origin: http://student.agh.edu.pl/~gut/java/
# person i wc to programy Rafa³a Wojdy³y
# origin: http://student.agh.edu.pl/~wojdyla/jtp/
# FileReader i Person to programy kogo¶tam...
# origin: http://student.agh.edu.pl/~thankus/jtp2/

clean:
	rm -f $(PKGNAME) *~ .*.swp *.class
	rm -rf doc bin

check_dirstruct:
	[ -d bin ] || mkdir bin
	[ -d doc ] || mkdir doc
	[ -d src ] || mkdir src

doc:
	#javadoc $(DOCFLAGS) $(SRC)

pkg: clean 
	tar cf - src/$(SRC) Makefile | 7za a -si $(PKGOPT) $(PKGNAME)

%: src/%.java check_dirstruct
	$(CXX) $(CXXFLAGS) $<

Sthack: src/Sthack.java src/SynchStack.java check_dirstruct
	$(CXX) $(CXXFLAGS) src/Sthack.java src/SynchStack.java

