#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _DBG 1

void fill(double*, int); /* wypelnij tablice losowymi wartosciami
			    z przedzialu [-10.0, 10.0) */

int main() {
    double xx[100];
#ifdef _DBG
    int i;
#endif
    fill(xx,100);
#ifdef _DBG
    for(i=0;i<100;++i)
	printf("%.1f\n",xx[i]);
#endif
    return 0;
}

void fill(double *x, int len) { /*________________________________________*/
 	/* proces tworzenia przedzialu:
	   [0,199] -> [-100,99] -> [-10.0, 9.9] <=> [-10.0, 10.0) */

    srand((unsigned int)time(NULL)); /* inicjuj generator
					liczb pseudolosowych */
    while(len--)                     /* wypelnij tablice */
	x[len] = ((double)(rand()%200-100))/10.0f;
}

