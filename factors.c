#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define min(a,b) (((a) < (b)) ? (a) : (b))

unsigned* build_factors(unsigned N);
void show_array(unsigned* A);
unsigned* build_common(unsigned* A, unsigned* B);

unsigned* build_factors(unsigned N){
	unsigned i = N;
	unsigned* A;
	int a = 1;
	
	A = (unsigned*)calloc(a, sizeof(unsigned));
	int k = 0;
	if(A == NULL){
		printf("Problems with Memory Allocation");
		exit(0);
	}
	while(i % 2 == 0){
		i = i /  2; 
	}
	for(int j = 3; j <= sqrt(i); j += 2){
		while(i % j == 0){
			i = i / j;
			//Here j is the value we want
			A[k] = j;
			k++;
			a++;
			A = realloc(A, a * sizeof(unsigned));
		}
	}
	if(i > 2){
		a++;
		A = realloc(A, a * sizeof(unsigned));
	}
	a++;
	k++;
	A = realloc(A, a * sizeof(unsigned));
	A[k] = 0; 
	return A;
}

void show_array(unsigned* A){
	int i = 0;
	while(*A){
		if(A[i] != 0){
			printf("&d, ",A[i]);
		}
		i++;
	}
	printf("\n");
}

unsigned* build_common(unsigned* A, unsigned* B){
	int a1,b1 = 0;
	int c_size = 1;
	int a_length, b_length = 0;
	unsigned* C;
	C = (unsigned*)calloc(c_size, sizeof(unsigned));
	while(*A){
		*A++;
		a_length++;
	}
	while(*B){
		*B++;
		b_length++;
	}
	int sm = min(a_length,b_length);
	if(sm == a_length){
		while(*A){
			if(A[a1] == B[b1]){
				///add value to new array
				if(c_size == 1){
					C[0] = A[a1];
				}
				c_size++;
				C = realloc(C, c_size * sizeof(unsigned));
				C[c_size-1] = A[a1];
				b1++;
			}
			a1++;
			*A++;
		}
	}
	else if(sm == b_length){
		while(B[b1] == A[a1]){
			if(c_size == 1){
				C[0] = B[b1];
			}
			c_size++;
			C = realloc(C, c_size * sizeof(unsigned));
			C[c_size-1] = B[b1];
			a1++;
		}
		b1++;
		*B++;
	}
}

int main(int argc, char* argv[]){
	
	unsigned M,N;
	unsigned* A,B;
	printf("Enter two integers M, N: \n");
	scanf("%d, %d", &M, &N);
	
	*A = build_factors(M);
	*B = build_factors(N);
	
	printf("%d has factors: ", M);
	show_array(A);
	printf("%d has factors: ", N); 
	show_array(B);
	
	printf("%d and %d have common factors: ", M, N, build_common(*A,*B));
	

	
	free(A);
	free(B);
	return 0;
}