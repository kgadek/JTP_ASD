CXX	= g++
CXXFLAGS = -W -Wall -Wshadow -Weffc++ -Wformat -Wsequence-point\
	   -Wunused -Wuninitialized -Wfloat-equal -ansi -pedantic
LDFLAGS	= -O2 -lm
SRC	= punkty.h punkty.cpp StosTablica.h StosTablica.cpp\
	  StosTablicaRosnaca.h StosTablicaRosnaca.cpp Makefile
PKGNAME	= GadekKonrad-jtp1-4.tgz

.PHONY: clean
.PHONY: all

clean:
	rm -f *.o punkty program $(PKGNAME) *~ *swp
all: program punkty

%: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -c -o $@

program: StosTablica.o StosTablicaRosnaca.o program.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -o $@

pkg: clean 
	tar -zcf $(PKGNAME) $(SRC)
