/*
 * pointers.c
 *
 * Nov. 9, 2026
 *
 * The purpose of this program is to develop an understanding of
 * how pointers work in the C programming language, and what
 * they can be used for.
 *
 */

#include <stdio.h>
#include <ctype.h>

#define SIZE 10

// Function prototypes
void numByReference(int *number);
void charactersInUpper(char *sPtr);
void printCharacters(const char *sPtr);
void bubbleSort(int * const array, int const size);
void swap(int *elementOnePtr, int *elementTwoPtr);


int main(void){
	int num = 256;
	
	// The best way to understand pointer declarations like this
	// are to read it from right to left
	//
	// i.e numPtr is a pointer (*) to a type integer
	int *numPtr;
	
	// Pointers point to memory address and do not hold specific values
	// Therefore, *numPtr is pointing to the address (&) of the variable num
	numPtr = &num;

	// & is the address operator, that returns the address of its operand
	
	// * is the dereferencing operator that returns the value of the object
	//   to which its operand points to

	printf("The value of num: %d\n", num);
	printf("The address of num: %p\n\n", &num);
	
	printf("The value of numPtr: %p\n", numPtr);
	printf("The value of *numPtr: %d\n", *numPtr);

	// In C, function arguments are passed by value, meaning that a copy
	// of the variable is made, and the original is left untouched
	// 
	// But C allows us to pass the address of the argument to a pointer
	// parameter in the function we're calling
	
	puts("");
	printf("Value of num before numByReference(): %d\n", num);
	numByReference(&num); // We are passing the address of the variable 'num' to the function
	printf("Value of num after numByReference(): %d\n", num);


	char lowerString[] = "is my string lowercase?";
	
	puts("");
	printf("before function call: %s\n", lowerString);
	charactersInUpper(lowerString);
	printf("after function call: %s\n", lowerString);


	char myString[] = "This is my string!";
	puts("");
	printCharacters(myString);
	puts("\n");

	int bubbleArray[SIZE] = {1, 34, 6, 7, 3, 23, 688, 420, 9, 0};

	puts("Data in original order");
	
	for (int i = 0; i < SIZE; i++){
		printf("%4d", bubbleArray[i]);
	}

	bubbleSort(bubbleArray, SIZE);

	puts("\nData in sorted order");

	for (int i = 0; i < SIZE; i++){
		printf("%4d", bubbleArray[i]);
	}

	puts("\n");

	return 0; // a return value of 0 means that our program finished executing without any problems
}

void numByReference(int *number){
	*number = *number / 8;
	// Because we're modifying the value of num directly, we don't need a return value here
}

// You may notice that the parameter for this function is a pointer
// but the argument we're passing is a character array...
// * and [] and the same thing...
// if you write it as char sPtr[], the C compiler still interprets it as char *sPtr
void charactersInUpper(char *sPtr) {
	while(*sPtr != '\0'){
		*sPtr = toupper(*sPtr);
		sPtr++;
	}
}


// Here we are using const because we don't want to modify the data that we're referencing
// we just want to print it to the console
void printCharacters(const char *sPtr){
	// because [] and * are equivalent, we can take the string and iterate through it
	// with a forloop, like an array
	
	// The first argument is optional, so the forloop will run until the condition is false
	for(; *sPtr != '\0'; sPtr++){
		printf("%c", *sPtr);
	}
}

// This part is pretty cool, because it shows that you can pass an array by reference to a function
// that can then sort the contents of it, and resolve the sorted array
void bubbleSort(int * const array, int const size){
	for(int pass = 0; pass < size; pass++){
		for(int i = 0; i < size; i++){
			if(array[i] > array[i + 1]){
				swap(&array[i], &array[i + 1]);
			}
		}
	}
}

void swap(int *elementOnePtr, int *elementTwoPtr){
	int hold = *elementOnePtr;
	*elementOnePtr = *elementTwoPtr;
	*elementTwoPtr = hold;
}
