CXX		= g++
CXXFLAGS	= -Wall
LDFLAGS		= -O2 -lm -lcppunit

clean:
	rm -f testerka *.o
%.cpp.o: %.cpp
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -c -o $@
testerka: avl.cpp.o common.cpp.o testy.cpp.o testerka.cpp 
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $? -o $@
