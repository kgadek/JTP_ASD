#include <stdio.h>
#include <math.h>


double pi_a(int);
double pi_b(int);


int main() {
    int x;
    scanf("%d",&x);
    printf("%1.10f\n%1.10f\n", pi_a(x), pi_b(x));
    return 0;
}

double pi_a(int n) { /* wzor Eulera na liczbe pi */
    double ret = 0.0;
    int i = 1;
    for(; i<=n; ++i) {
	ret += 6.0/(double)(i*i);
    }
    return sqrt(ret);
}

double pi_b(int n) { /* wzor Wallisa na liczbe pi */
    double ret = 2.0;
    int even = -1,
	i = 1;
    for(; i<=n; ++i) {
	even *= -1;
	if(even>0) {
	    ret *= ((double)i+1.0);
	    ret /= (double)i;
	} else {
	    ret *= (double)i;
	    ret /= ((double)i+1.0);
	}
    }
    return ret;
}

