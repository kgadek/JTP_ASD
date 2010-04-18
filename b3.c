#include <stdio.h>

int main() {
    printf("Badana typ: %s\n"\
	    "\t* rozmiar:\t\t\t%8d [bajtow]\n"\
	    "\t* przykladowa wartosc A:\t%8d\n"\
	    "\t* przykladowa wartosc B:\t%8d\n",\
	    "int",sizeof(int), -4, 4);
    return 0;
}

