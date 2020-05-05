#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node{
	char* s;
	unsigned int count;
	struct node* next;
};

struct hashtable{
	struct node** ptr;
	unsigned int arr_size;
};

struct hashtable* base;

void init_table(struct hashtable* T, unsigned size);
void add_to_table(struct hashtable* T, char* str);
void show_table(struct hashtable* T);

void init_table(struct hashtable* T, unsigned size){
	T = (struct hashtable*)calloc(size, sizeof(struct hashtable));
}

void add_to_table(struct hashtable* T, char* str){
	
}

void show_table(struct hashtable* T){
	for(int i = 0; i < T->arr_size; i++){
			struct node *ptr = T->ptr;
			if(ptr == NULL){
				printf("Nothing left\n");
			}else{
				while(ptr != NULL){
					printf("%d\t%s\n",ptr->count, ptr->s,);
				}
			}
	}
}

int main(int argc, char* argv[]){
	
	
	return 0;
}