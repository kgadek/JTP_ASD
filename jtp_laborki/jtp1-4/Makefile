CC	= gcc
CXX	= g++
CFLAGS	= -ansi -pedantic -Wall -W -Wconversion -Wshadow -Wcast-qual -Wwrite-strings
CXXFLAGS = -W -Wall -Wshadow -Weffc++ -Wformat -Wsequence-point -Wunused -Wuninitialized -Wfloat-equal -ansi -pedantic
LDFLAGS	= -O2 -lm
SRC	= punkty.h punkty.cpp
PKGNAME	= GadekKonrad-jtp1-4.tgz

clean:
	rm -f *.o punkty program $(PKGNAME) *~ *swp

%: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -o $@

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -c -o $@

program: StosTablica.o StosTablicaRosnaca.o program.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -o $@

pkg: clean 
	tar -zcf $(PKGNAME) $(SRC)
