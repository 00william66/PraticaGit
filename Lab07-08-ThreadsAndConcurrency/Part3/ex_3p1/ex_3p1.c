#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>
#include <signal.h> // Timers
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <math.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <pthread.h>



typedef struct {
	double lower;
	double upper;
	long long nsteps;
	double *intVal;
} tIArgs_type;

static inline uint64_t ts_to_ns(const struct timespec *t);
static inline double ns_to_s(uint64_t ns);
static inline double func(double x);
int numIntegrate(double lower, double upper, long long nsteps, double *intVal);
void *integrate_thread(void *arg);




/*
 * main()
 */
int main() {
    double a = 0.0, b = 10.0;				// Integration limits
    double sa, sb, segsize = 0, stepSize;	// Variables for segments
    long long np = 1000000000, snp = 0; 	// Number of poinst - total and segment
    int nseg = 0;							// Total segmnets
    double integral=0,integ_s1=0, integ_s2=0, 
		integ_s3=0, integ_s4=0;				// Integral results
    int res;								// Function return code
    struct timespec t0, t1;					// For measuring computation time
    uint64_t total_ns;


    pthread_t tid[4];						// Thread handles
    tIArgs_type args[4];					// Arguments of each thread
    double *results[4];						// Where each thread stores its result
    void *ret;								// Value returned by a thread
    int i;

    
    /* Compute the integral - SINGLE THREAD */
    clock_gettime(CLOCK_MONOTONIC, &t0);
    res=numIntegrate(a, b, np, &integral);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    total_ns = (ts_to_ns(&t1) - ts_to_ns(&t0));
    
    if(res == EXIT_SUCCESS) {
		printf("Integral on [%.6f, %.6f] with n=%lld = %.12f\n", a, b, np, integral);
		printf("Took %ld to complete\n", total_ns);
	} else {
		printf("Integral computation failed \n");
		exit(EXIT_FAILURE);
    }
    uint64_t single_ns = total_ns; /*SÓ PARA DEPOIS CALCULAR SPEEDUP*/
    

    

    /* Compute the integral - 4 segments, one thread per segment */
    clock_gettime(CLOCK_MONOTONIC, &t0);
    nseg=4;					// Number of segments
    snp = np/nseg;			// Number of points in each segment
    segsize = (b-a) / (double) nseg;	// The segment range
    stepSize = (b - a) / (double)np;
    res = 0;

    results[0] = &integ_s1;
    results[1] = &integ_s2;
    results[2] = &integ_s3;
    results[3] = &integ_s4;

    // 1 thread por segmento
    for (i = 0; i < nseg; i++) {
        sa = a + i*segsize;
        if (i < nseg-1)
            sb = sa + segsize - stepSize;
        else
            sb = sa + segsize;

        args[i].lower  = sa;
        args[i].upper  = sb;
        args[i].nsteps = snp;
        args[i].intVal = results[i];

        res = pthread_create(&tid[i], NULL, integrate_thread, &args[i]);
        if (res != 0) {
            fprintf(stderr, "pthread_create (segment %d): %s\n", i+1, strerror(res));
            exit(EXIT_FAILURE);
        }
    }

    // esperar pelas threads
    for (i = 0; i < nseg; i++) {
        res = pthread_join(tid[i], &ret);
        if (res != 0) {
            fprintf(stderr, "pthread_join (segment %d): %s\n", i+1, strerror(res));
            exit(EXIT_FAILURE);
        }
        if ((intptr_t)ret != EXIT_SUCCESS) {
            printf("Integral computation failed - segment %d\n", i+1);
            exit(EXIT_FAILURE);
        }
    }
	       
    integral = integ_s1 + integ_s2 + integ_s3 + integ_s4;
    
    clock_gettime(CLOCK_MONOTONIC, &t1);
    total_ns = (ts_to_ns(&t1) - ts_to_ns(&t0));
    
    printf("Integral on [%.6f, %.6f] with n=%lld = %.12f - segmented version \n", a, b, np, integral);
	printf("Took %ld to complete\n", total_ns);
    printf("Speedup: %.2f\n", (double)single_ns / (double)total_ns);   // T_single / T_threads
    
    
    // Done!
    return 0;
}

/*****************************************************************/
/* 
 * definições das funções declaradas em cima
 * 
 */
static inline uint64_t ts_to_ns(const struct timespec *t) {
    return (uint64_t)t->tv_sec * 1000000000ull + (uint64_t)t->tv_nsec;
}

static inline double ns_to_s(uint64_t ns) {
    return (double)ns / 1e9;
}


/* 
 * Function to integrate: 1 / (1 + x^2)
 */
static inline double func(double x) {    
    return 1.0 / (1.0 + pow(x,2.0));
}

/*
 *  Computes the integral of func on [lower, upper] with nsteps trapezoids
 * 
 */
int numIntegrate(double lower, double upper, long long nsteps, double *intVal)
{
    double stepSize, integration, k;
    long long i;
        
    // Check args
    if (nsteps <= 0) 
		return EXIT_FAILURE;

    stepSize = (upper - lower) / (double)nsteps;

    // Trapezoidal rule: h * [ (f(a)+f(b))/2 + sum_{i=1..n-1} f(a + i h) ]
    integration = 0.5 * (func(lower) + func(upper));

    for (i = 1; i <= nsteps - 1; ++i) {
        k = lower + i * stepSize;
        integration += func(k);
    }

    integration *= stepSize;
    
    *intVal = integration;
    return EXIT_SUCCESS;
}


void *integrate_thread(void *arg){
    tIArgs_type *p = (tIArgs_type *)arg;
    numIntegrate(p->lower, p->upper, p->nsteps, p->intVal);
    return NULL;
}


/*

willy@GIGABYTE-G5-W$ ./3p1
Integral on [0.000000, 10.000000] with n=1000000000 = 1.471127674304
Took 15778345465 to complete
Integral on [0.000000, 10.000000] with n=1000000000 = 1.471127672365 - segmented version
Took 4925364071 to complete
Speedup: 3.20

*/