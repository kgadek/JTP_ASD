CXX	= g++
CXXFLAGS = -W -Wall -Wshadow -Weffc++ -Wformat -Wsequence-point\
	   -Wunused -Wuninitialized -Wfloat-equal -ansi -pedantic
LDFLAGS	= -O2 -lm
SRC	= punkty.h punkty.cpp StosTablica.h StosTablica.cpp\
	  StosTablicaRosnaca.h StosTablicaRosnaca.cpp Makefile
PKGNAME	= GadekKonrad-jtp1-4.tgz

.PHONY: clean all pkg program punkty

clean:
	rm -f *.o punkty program $(PKGNAME) *~ *swp

all: punkty program

pkg: clean 
	tar -zcf $(PKGNAME) $(SRC)

# Kompilacja programu B1 (Punkty)
punkty: punkty.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -o $@

# Kompilacja programu B2 (StosTablica(Rosnaca))
program: StosTablica.o StosTablicaRosnaca.o program.o
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -o $@

# Regula kompilacji modulow (pasuje do *.o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -c -o $@

