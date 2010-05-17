clean:
	rm -f avl testy *.o
avl.o: avl.cpp
	g++ -O2 -Wall -lcppunit avl.cpp -c -o avl.o
testy: avl.o testy.cpp
	g++ -O2 testy.cpp avl.o -lcppunit -o testy
	ctags -R *.c *.cpp *.h > /dev/null 2&> /dev/null
