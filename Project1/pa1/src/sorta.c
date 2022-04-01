#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void swap(int *a, int *b){
	int temp = *b;
	*b = *a;
	*a = temp;
}

void evenAndOdd(int array[], int size){
	for(int l = 0; l<size; l++){
		for(int r = size-1-1; r>0; r--){
			if(array[l] % 2 != 0 && array[l+1] % 2 == 0){
				swap(&array[l], &array[l+1]);
			}
			else if(array[r] % 2 == 0 && array[r-1] % 2 != 0){
				swap(&array[r-1], &array[r]);
			}
		}
	}
	return;
}
void insertionSort(int arr[], int size){
	for(int l = 0; l<size; l++){
		for(int r = size-1-1; r>0; r--){
			if(arr[l+1] % 2 == 0){
				if(arr[l] > arr[l+1]){
					swap(&arr[l], &arr[l+1]);
				}
			}
			if(arr[r-1] % 2 != 0){
				if(arr[r] > arr[r-1]){
					swap(&arr[r-1], &arr[r]);
				}
			}
		}
	}
	return;
}


int main(int argc, char* argv[argc + 1]){

	if(argc < 2){
		printf("insufficient arguments");
		return EXIT_SUCCESS;
	}
	

	FILE* f = fopen(argv[1], "r");
	int numbers;

	fscanf(f, "%d\n", &numbers);

	int array[numbers];
	for(int i =0; i < numbers; i++){
		fscanf(f, "%d\t", &array[i]);
	}
	evenAndOdd(array, numbers);
	insertionSort(array, numbers);
	for(int j = 0; j<numbers; j++){
		printf("%d\n", array[j]);
	}
	
					
	fclose(f);
	return EXIT_SUCCESS;
}
