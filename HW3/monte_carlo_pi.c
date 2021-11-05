#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <omp.h>

#define SEED 21
#define N 500000000

unsigned int seed = 479001599; 


double randUint(void){
    
	seed = seed * 1103515245 + 12345;
    
    return seed / (double)UINT_MAX ;
}


int main()
{
   
    long count=0;
    double pi, start, end;


    start = omp_get_wtime();
    #pragma omp parallel for reduction(+: count)
    for (long i=0; i<N; i++) {
//	int tid = omp_get_thread_num();
//	printf("%d\n",tid);
        double x,y;
        x = randUint();
        y = randUint();
        if (x*x+y*y <= 1)
            count++;
    }
    end = omp_get_wtime();
    pi=((double)count/(double)N) * 4.0;
    printf("Estimate of pi is %1.16f\nAbsolute error of %g\nTime %1.16f\n", pi, fabs(pi - M_PI), end -start);
    return 0;
}
