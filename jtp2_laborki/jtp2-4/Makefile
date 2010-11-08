CXX	= javac
CXXFLAGS =-encoding UTF-8 -g -verbose -d bin
DOCFLAGS =-d doc
SRC	= Orkiestra.java
PKGNAME	= GadekKonrad-jtp2-4.tar.7z
PKGOPT	= -t7z -m0=lzma -mx=9 -mfb=64 -md=32m -ms=on

.PHONY: clean all pkg doc check_dirstruct

all: check_dirstruct $(SRC:.java=) doc

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

