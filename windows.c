#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct window{
	unsigned int xlow;
	unsigned int ylow;
	unsigned int xhigh;
	unsigned int yhigh;
	
	char wch;
	
};

char arr[100][100];

void fill_line(struct window W[], unsigned wsize,
 unsigned x1, unsigned x2, unsigned y, char line[]);

unsigned fill_windows(struct window W[], unsigned wmax);


void fill_line(struct window W[], unsigned wsize,
 unsigned x1, unsigned x2, unsigned y, char line[]){
	for(int i = 0; i < wsize; i++){
		if((y == W[i].ylow) || (y == W[i].yhigh) &&
			(W[i].xlow >= x1 && W[i].xlow <= x1) &&
			(W[i].xhigh >= x2 && W[i].xhigh <= x2)){
				int j = x1;
				while(j <= x2){
					line[j] = W[i].wch;
					j++;
				}
		}
	}
}

unsigned fill_windows(struct window W[], unsigned wmax){
	unsigned int numw;
	int i,track = 0;
	
	char base[100]; 
	char *s = "q";
	printf("Enter values line by line\n"
	"type q when done\n");
	
	for(i = 0; i < wmax; i++){
		while(strstr(fgets(base,100,stdin),s) == NULL){
			const char s[4] = " ,";
			char* token;
			
			token = strtok(base,s);
			
			while(token != NULL){
				//printf("This is  the %d token: %s\n" ,track,token);
				token = strtok(NULL,s);
				
				switch(track){
					case 0:
					//printf("We made it to %d case \n",track);
					W[i].xlow = atoi(token);
					printf("This is the current 1st token %d\n",W[i].xlow);
					break;
					case 1:
					//printf("We made it to %d case \n",track);
					W[i].ylow = atoi(token);
					printf("This is the current 2nd token %d\n",W[i].ylow);
					break;
					case 2:
					//printf("We made it to %d case \n",track);
					W[i].xhigh = atoi(token);
					printf("This is the current 3rd token %d\n",W[i].xhigh);
					break;
					case 3:
					//printf("We made it to %d case \n",track);
					W[i].yhigh = atoi(token);
					printf("This is the current 4th token %d\n",W[i].yhigh);
					break;
					case 4:
					//printf("We made it to %d case \n",track);
					W[i].wch = token[0];
					printf("This is the current last token %c\n",W[i].wch);
					break;
				}
				track ++;
			}
			track = 0;
		}
	}

}

int main(int argc, char argv[]){
	struct window a;
	struct window b;
	struct window c;
	struct window d;
	struct window e;
	struct window full[5] = {a,b,c,d,e};
	fill_windows(full,5);
	//for(int i = 0; i < 5; i++){
		///char c = full[i].wch;
		//for(int j = full[i].xlow; j < full[i].xhigh; j++){
			//for(int k = full[i].ylow; k < full[i].yhigh; k++){
				//arr[j][k] = c;
			//}
		//}
	//}
	
	//for(int i = 0; i < 100; i++){
		//for(int j = 0; j < 100; j++){
			//printf("%c");
		//}
	//}
	return 0;
}
