#include <string.h> 		/* For memset */
#include <MyVectorLib.h>

static int MyVectorLib_Vect[MYVECTLIB_MAXLEN]; 	/* Vector */
static int MyVectLen=0;							/* Number of elements in the vector*/

/* Initializes the vector */
void MyVectorLib_Init(void){
	MyVectLen=0;
	memset(MyVectorLib_Vect,0,sizeof(MyVectorLib_Vect));
	return;
} 		

/* Adds an element to the vector */
int MyVectorLib_Add(int number){
	MyVectorLib_Vect[MyVectLen]=number; 	
	MyVectLen++;
	return MYVECTLIB_OK;
}	

/* Returns the position of number (is it an index or ordinal?) --> ORDINAL!*/
int MyVectorLib_Find(int number)
{
    int i = 0;
        
    while (i < MyVectLen) {		
        if (MyVectorLib_Vect[i] == number)
			return (i+1);
		i++;
	}
	
    return MYVECTLIB_NOTFOUND;
}

/* Returns the number of elements in the vector */
int MyVectorLib_Len(void)
{
	return MyVectLen;
}


/* Removes a number from the vector */
int MyVectorLib_Remove(int number)
{
	int i=0;
	int j;
	while (i < MyVectLen) {
		if (MyVectorLib_Vect[i] == number) {
			/* Move all elements after the found number one position to the left */
			for (j=i; j<MyVectLen-1; j++) {
				MyVectorLib_Vect[j] = MyVectorLib_Vect[j+1];
			}
			MyVectLen--;
			return MYVECTLIB_OK;
		}
		i++;
	}
	return MYVECTLIB_NOTFOUND;
} 

void MyVectorLib_Sort(void){
	int i, j, temp;
	for (i=0; i < MyVectLen-1; i++) {
		for (j=0; j < MyVectLen-i-1; j++) {
			if (MyVectorLib_Vect[j] > MyVectorLib_Vect[j+1]) {
				/* Swap */
				temp = MyVectorLib_Vect[j];
				MyVectorLib_Vect[j] = MyVectorLib_Vect[j+1];
				MyVectorLib_Vect[j+1] = temp;
			}
		}
	}
}

int MyVectorLib_max(void)
{
	int max = MyVectorLib_Vect[0];
	int i = 0;
	for (i=0; i < MyVectLen; i++) {
		if (MyVectorLib_Vect[i] > max){
			max = MyVectorLib_Vect[i];
		}
	}
	return max;
}

int MyVectorLib_min(void)
{
	int min = MyVectorLib_Vect[0];
	int i = 0;
	for (i=0; i < MyVectLen; i++) {
		if (MyVectorLib_Vect[i]<min){
			min=MyVectorLib_Vect[i];
		}
	}
	return min;
}

int MyVectorLib_avg(void)
{
	int sum = 0;
	int i = 0;
	
	for (i = 0; i < MyVectLen; i++) {
		sum = sum + MyVectorLib_Vect[i];
	}
	return sum / MyVectLen;
}