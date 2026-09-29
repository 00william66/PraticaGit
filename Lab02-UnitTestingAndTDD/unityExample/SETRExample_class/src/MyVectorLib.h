#ifndef MYVECTORLIB_H
#define MYVECTORLIB_H

#define MYVECTLIB_MAXLEN 	10		/* Maximum size of vector 			*/

/* Return codes - *** DO NOT USE MAGIC NUMBERS *** */
#define MYVECTLIB_OK		0		/* Success return code code			*/
#define MYVECTLIB_NOTFOUND	0		/* Number not found					*/

/* Function prototypes */
void MyVectorLib_Init(void); 		/* Initializes the vector			*/
int MyVectorLib_Add(int number);	/* Adds a number to the vector		*/
int MyVectorLib_Find(int number); 	/* Finds if a number exists in the vector	*/
int MyVectorLib_Len(void);			/* Returns the length of the vector	*/
int MyVectorLib_Remove(int number);	/* Removes a number from the vector	*/
void MyVectorLib_Sort(void);		/* Sorts the vector in ascending order	*/    
int MyVectorLib_max(void);			/* Returns the maximum value in the vector	*/
int MyVectorLib_min(void);			/* Returns the minimum value in the vector	*/
int MyVectorLib_avg(void);            /* Returns the average value in the vector	*/

#endif
