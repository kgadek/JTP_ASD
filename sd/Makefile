all: testerka

clean:
	rm -f testerka *.o
avl.o: avl.cpp
	g++ -O2 -Wall avl.cpp -c -o avl.o
testy.o: testy.cpp
	g++ -O2 testy.cpp -lcppunit -c -o testy.o
common.o: common.h common.cpp
	g++ -O2 common.cpp -lcppunit -c -o common.o
testerka: avl.o testerka.cpp common.o testy.o
	g++ -O2 testerka.cpp testy.o avl.o common.o -lcppunit -o testerka
	ctags -R *.c *.cpp *.h > /dev/null 2&> /dev/null
