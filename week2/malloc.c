#include <stdio.h>
#include <stdlib.h>

int main(void){
	char** pp_data = NULL;
	int n;
	int length;
	int i;

	scanf("%d", &n);


	//1. define & dynamic allocation
	pp_data=malloc(sizeof(char*)*n);
	scanf("%d",&length);
	for(int i=0;i<n;++i)pp_data[i]=malloc(sizeof(char)*length);
	for(int i=0;i<n;++i)scanf("%s",pp_data[i]);

	//2. print string
	for(int i=0;i<n;++i)printf("%s\n",pp_data[i]);

	//3. free memory
	for(int i=0;i<n;++i)free(pp_data[i]);
	free(pp_data);

	return 0;
}
