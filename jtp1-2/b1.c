#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double rr() { /* losuj liczbe z przedzialu [-30,30] */
	return (((double)rand())/(double)RAND_MAX)*60.0f-30.0f;
}

int main() {
	srand((unsigned int)time(NULL));
	return 0;
}

