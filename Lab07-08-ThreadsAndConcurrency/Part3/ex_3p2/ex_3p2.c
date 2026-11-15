// EX3_2 - explore the advantages of paralellizing compuations via threads 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <time.h>
#include <math.h>
#include <string.h>
#include <pthread.h>

#define NBINS	100	// Number of bins for histogram
#define RANGE   100		// Range for random numbers (-RANGE to +RANGE)

// Struct for storing the results - single threaded
typedef struct {
    double * sortArr;		// For array sorting function 
    double * matTransf;		// For mathematical transformation 
    int * hist;				// For histogram computation
} Stats_t;

// Struct to pass the arguments to the threads (input array, its size and where to store the results)
typedef struct {
    const double *a;
    int n;
    Stats_t *s;
} ThreadArgs_t;


static inline uint64_t ts_to_ns(const struct timespec *t);
static inline double ns_to_s(uint64_t ns);
static double rand_uniform_range(int range);
static void fill_random(double *a, int n,int range);
int compare_doubles(const void *a, const void *b);
void compute_all_one_thread(const double *a, int n, Stats_t *s);
void compute_all_three_threads(const double *a, int n, Stats_t *s);
void *sort_thread(void *arg);
void *transf_thread(void *arg);
void *hist_thread(void *arg);



/* 
 * The main() function
 */
int main() {
    int N = 100000000;     	// default array size
    long seed = 0;          // default seed; 0 means use time(NULL)
	double *arr;			// Pointer to array
	struct timespec t0, t1;	// For measuring computation time
	Stats_t s1T;			// Computation results for single thread version
	Stats_t s3T;			// Computation results for three threads version
	
	uint64_t totalA_ns;		// Time taken - single thread
	uint64_t totalB_ns;		// Time taken - three threads
    
    // Init seed with a fixed value to make it repeatible
    srand48(seed);

    // Allocate memory for the array
    arr = (double*)malloc(N * sizeof(double));
    if (!arr) {
        fprintf(stderr, "Allocation failed for N=%u\n", N);
        return 1;
    }

    // Fill once; we’ll reuse the same data for fairness between approaches
    fill_random(arr, N, RANGE);
    
    // Prepare input/output args
    s1T.sortArr = (double *)malloc(N * sizeof(double));
    s1T.matTransf = (double *)malloc(N * sizeof(double));
    s1T.hist = (int *)malloc(NBINS * sizeof(int));
    s3T.sortArr = (double *)malloc(N * sizeof(double));
    s3T.matTransf = (double *)malloc(N * sizeof(double));
    s3T.hist = (int *)malloc(NBINS * sizeof(int));
    	
	// Execute processing - one thread
	clock_gettime(CLOCK_MONOTONIC, &t0);
    compute_all_one_thread(arr, N, &s1T);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    totalA_ns = (ts_to_ns(&t1) - ts_to_ns(&t0));

	// Execute processing - three threads (one per task)
	clock_gettime(CLOCK_MONOTONIC, &t0);
    compute_all_three_threads(arr, N, &s3T);
    clock_gettime(CLOCK_MONOTONIC, &t1);
    totalB_ns = (ts_to_ns(&t1) - ts_to_ns(&t0));
	
    // After all timing is complete, we can safely print without affecting measured times
    printf("Single thread:\n");
    printf("Time taken was: %ld\n",totalA_ns);
    printf("Three threads:\n");
    printf("Time taken was: %ld\n",totalB_ns);
    printf("Speedup: %.2f\n", (double)totalA_ns / (double)totalB_ns);


	// Done! Release resources and finish
    free(arr);
    free(s1T.sortArr);
    free(s1T.matTransf);
    free(s1T.hist);
    free(s3T.sortArr);
    free(s3T.matTransf);
    free(s3T.hist);
    return 0;
}






/* 
 * Auxiliary function, to handle time and fill the array
 * 
 */
static inline uint64_t ts_to_ns(const struct timespec *t) {
    return (uint64_t)t->tv_sec * 1000000000ull + (uint64_t)t->tv_nsec;
}

static inline double ns_to_s(uint64_t ns) {
    return (double)ns / 1e9;
}

static double rand_uniform_range(int range) {
    // drand48() returns [0.0, 1.0); scale to [-range, +range]
    return (drand48() * (double)2*range) - (double)range;    
}

static void fill_random(double *a, int n,int range) {
	int i;
	
    for (i = 0; i < n; ++i) {
		a[i] = rand_uniform_range(range);
	}
	return;
}

/* 
 * Compare function for qsort 
 */
int compare_doubles(const void *a, const void *b)
{
    double da = *(const double *)a;
    double db = *(const double *)b;

    if (da < db)
		return -1;
    if (da > db)
		return 1;
    return 0;
}

/*
 * Approach A - one thread computes all values
 */
void compute_all_one_thread(const double *a, int n, Stats_t *s) {
    int i, bin;
     
	// QuickSort operation
	memcpy(s->sortArr,a,n*sizeof(double));
	qsort(s->sortArr, n, sizeof(double), compare_doubles);

    // Generic matTransf computation
	memcpy(s->matTransf,a,n*sizeof(double));
	for (i = 0; i < n; ++i) {
		s->matTransf[i] = sin(s->matTransf[i]) + sqrt(fabs(s->matTransf[i])) * exp(-s->matTransf[i] * s->matTransf[i]);
	}
	
    // Histogram computation
    for (i = 0; i < NBINS; i++) {
		s->hist[i] = 0;
	}
    for (i = 0; i < n; i++) {
		bin = (int)((a[i] + 100.0) / 2.0);  // Map [-100,100] → 100 bins
		if (bin >= 0 && bin < 100)
			s->hist[bin]++;
	}
   
    return;
}

/*
 * Approach B - one thread per task (sort, transformation, histogram)
 */
void compute_all_three_threads(const double *a, int n, Stats_t *s) {
    pthread_t tid[3];
    ThreadArgs_t args;
    int i, rc;
    void *(*tasks[3])(void *) = { sort_thread, transf_thread, hist_thread };	// Function run by each thread

    args.a = a;
    args.n = n;
    args.s = s;

    // Fork: create one thread per task
    for (i = 0; i < 3; i++) {
        rc = pthread_create(&tid[i], NULL, tasks[i], &args);
        if (rc != 0) {
            fprintf(stderr, "pthread_create (task %d): %s\n", i+1, strerror(rc));
            exit(EXIT_FAILURE);
        }
    }

    // Join: wait for all the threads to finish
    for (i = 0; i < 3; i++) {
        rc = pthread_join(tid[i], NULL);
        if (rc != 0) {
            fprintf(stderr, "pthread_join (task %d): %s\n", i+1, strerror(rc));
            exit(EXIT_FAILURE);
        }
    }

    return;
}

/*
 * Thread 1 - sorting
 */
void *sort_thread(void *arg) {
    ThreadArgs_t *p = (ThreadArgs_t *)arg;

	// QuickSort operation
	memcpy(p->s->sortArr, p->a, p->n*sizeof(double));
	qsort(p->s->sortArr, p->n, sizeof(double), compare_doubles);

    return NULL;
}

/*
 * Thread 2 - mathematical transformation
 */
void *transf_thread(void *arg) {
    ThreadArgs_t *p = (ThreadArgs_t *)arg;
    int i;

    // Generic matTransf computation
	memcpy(p->s->matTransf, p->a, p->n*sizeof(double));
	for (i = 0; i < p->n; ++i) {
		p->s->matTransf[i] = sin(p->s->matTransf[i]) + sqrt(fabs(p->s->matTransf[i])) * exp(-p->s->matTransf[i] * p->s->matTransf[i]);
	}

    return NULL;
}

/*
 * Thread 3 - histogram
 */
void *hist_thread(void *arg) {
    ThreadArgs_t *p = (ThreadArgs_t *)arg;
    int i, bin;

    // Histogram computation
    for (i = 0; i < NBINS; i++) {
		p->s->hist[i] = 0;
	}
    for (i = 0; i < p->n; i++) {
		bin = (int)((p->a[i] + 100.0) / 2.0);  // Map [-100,100] → 100 bins
		if (bin >= 0 && bin < 100)
			p->s->hist[bin]++;
	}

    return NULL;
}