//Template
#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

int compare(int a, int b){
	if(a>b)  
		return 1;
	else 
		return -1;
}


/***************************************************************
define bubble sort that uses pointer to 'compare' function above
***************************************************************/

void swap(int* a,int* b){
	int t=*a;
	*a=*b;
	*b=t;
}

void BubbleSort(int* arr,int size,int (*cmp)(int,int)){
	for(int i=0;i<size;++i){
		for(int j=0;j<size-i-1;++j){
			if(cmp(arr[j],arr[j+1])==1)swap(arr+j,arr+j+1);
		}
	}
}


int main(){
	int n_array[SIZE] = {2,-9, 10, 15, 1, 3, -12, 5, 4, 1};
	printf("Before Sorting: ");
	for(int i=0;i<SIZE;++i)printf("%d ",n_array[i]);
	printf("\n\n");
	BubbleSort(n_array,SIZE,compare);
	printf("After Sorting: ");
	for(int i=0;i<SIZE;++i)printf("%d ",n_array[i]);
	return 0;
}
