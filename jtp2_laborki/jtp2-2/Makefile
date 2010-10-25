CXX	= javac
CXXFLAGS =-encoding UTF-8 -g -verbose -d bin
LDFLAGS	= 
SRC	= Tablica.java
PKGNAME	= GadekKonrad-jtp2-1.tgz

.PHONY: clean all pkg check_dirstruct doc

all: check_dirstruct Tablica doc

clean:
	rm -f $(PKGNAME) *~ *swp *.class
	rm -rf doc bin

check_dirstruct:
	[ -d bin ] || mkdir bin
	[ -d doc ] || mkdir doc

doc:
	javadoc -d doc $(SRC)

pkg: clean 
	tar -zcf $(PKGNAME) $(SRC) Makefile

%: %.java
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $?

