
/*

long i;
unsigned seed;

#pragma omp parallel private(seed)
{
    // Initialise the random number generator with different seed in each thread
    // The following constants are chosen arbitrarily... use something more sensible
    seed = 25234 + 17*omp_get_thread_num();
    #pragma omp for
    for (i = 0; i <= 1000000000; i++) {
       double x = rand_r(&seed);
    }
}


OR SOMETHING MORE:
*/
#include <stdio.h>
#include <omp.h>

#define NRANDS 100
#define MAX 2

int main(int argc, char **argv) {

 //   struct timeval t;
    int a[NRANDS], b[NRANDS];
    int i, j;
    double sum;

 //   tick(&t);

  /*	Intercalado:
	for ( j = omp_get_thread_num(); j < MAX ; ++j ) {
		srand(25234 + 17*j);
		
		printf("%d - %d\n", (25234 + 17*j), j );

		for( i = j ; i < NRANDS ; i += MAX) {
			printf("%d\n", i);
			b[i] = rand();
		}

	}
	*/



// Arrumar!



	/* Dividido por número de threads */
	for ( j = omp_get_thread_num(); j < MAX ; ++j ) {
		srand(25234 + 17*j);
		
		printf("%d - %d\n", (25234 + 17*j), j );

		for(i = 0 ; i < (NRANDS/MAX) ; ++i) 
			b[i+((NRANDS/MAX)*j)] = rand();
		

	}

	sum = 0.0;
	for( i = 0 ; i < NRANDS ; ++i) {
		sum += b[i];
		printf("%.5lf - %d -> %d\n", sum, b[i], i );
	}

	printf("Sum sequence = %.10lf\n", sum);


    #pragma omp parallel default(none) shared(a)
    {
        int i;

         printf("%d - %d\n", (25234 + 17*omp_get_thread_num()), omp_get_thread_num() );

        unsigned int myseed = 25234 + 17*omp_get_thread_num();
        #pragma omp for
        for(i = 0; i < NRANDS; ++i) 
			a[i] = rand_r(&myseed);
    }


    sum = 0.0;
 //   double time=tock(&t);
    for ( i=0; i<NRANDS; i++) {
        sum += a[i];
        printf("%.5lf - %d -> %d\n", sum, a[i], i );
    }
  //  printf("Time = %lf, sum = %lf\n", time, sum);
    printf("Sum = %.10lf\n", sum);

    return 0;
}