CXX	= g++
CXXFLAGS = -W -Wall -Wshadow -Weffc++ -Wformat -Wsequence-point\
	   -Wunused -Wuninitialized -Wfloat-equal -ansi -pedantic
LDFLAGS	= -O2 -lm
SRC	= punkty.h punkty.cpp 
PKGNAME	= GadekKonrad-jtp1-6.tgz

.PHONY: clean all pkg

clean:
	rm -f *.o $(PKGNAME) *~ *swp

all: punkty.o

pkg: clean 
	tar -zcf $(PKGNAME) $(SRC)

# Regula kompilacji modulow (pasuje do *.o)
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -c -o $@

