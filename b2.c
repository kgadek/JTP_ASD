#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void fill(double*, int); /* wypelnij tablice losowymi wartosciami
			    z przedzialu [-10.0, 10.0) */

int main() {
    double xx[100];
    int i;
    fill(xx,100);
    for(i=0;i<100;++i)
	printf("%.1f\n",xx[i]);
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

