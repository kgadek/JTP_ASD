#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill(double*, int); /* wypelnij tablice losowymi wartosciami
			    z przedzialu [-10.0, 10.0) */
void sort(double*, int); /* posortuj tablice algorytmen Insertion Sort*/

int main() {
    double xx[100];
    fill(xx,100);
    sort(xx,100);
    return 0;
}

void fill(double *x, int len) { /*________________________________________*/
	    /* 
		x	- wskaznik na tablice
		len	- rozmiar tablicy
	       
		proces tworzenia przedzialu:
		[0,199] -> [-100,99] -> [-10.0, 9.9] <=> [-10.0, 10.0)
	    */
    srand((unsigned int)time(NULL)); /* inicjuj generator
					liczb pseudolosowych */
    while(len--)                     /* wypelnij tablice */
	x[len] = ((double)(rand()%200-100))/10.0f;
}

void sort(double *x, int len) { /*________________________________________*/
	    /*
		x	- wskaznik na tablice
		len	- rozmiar tablicy
	    */
    int i,j;
    double mx;
    for(i=1; i<len; ++i) {
	mx=x[i];
	j=i-1;
	while(j>=0 && x[j]>mx) {
	    x[j+1] = x[j];
	    --j;
	}
	x[j+1] = mx;
    }
}

