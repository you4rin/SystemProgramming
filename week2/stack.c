//Template
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
	int nData;
	struct Node *next;
}Node;

typedef struct Stack{
	Node *top;
}Stack;

void InitializeStack(Stack *stack);
void Push(Stack *stack, int nData);
int Pop(Stack *stack);


int main(void){
	Stack* stack=malloc(sizeof(Stack));
	InitializeStack(stack);
	for(int i=0;i<10;++i){
		Push(stack,i);
		printf("Inserted Data: %d\n",stack->top->nData);
	}
	printf("\n");
	for(int i=0;i<10;++i){
		printf("Deleted Data: %d\n",Pop(stack));
	}
	return 0;
}

void InitializeStack(Stack *stack){
	stack->top=malloc(sizeof(Node));
	stack->top->next=NULL;
}

void Push(Stack *stack, int nData){
	Node* newNode=malloc(sizeof(Node));
	newNode->nData=nData;
	newNode->next=stack->top;
	stack->top=newNode;
}

int Pop(Stack *stack){
	Node* top=stack->top;
	if(top->next==NULL)exit(-1);
	int ret=stack->top->nData;
	stack->top=top->next;
	free(top);
	return ret;
}
