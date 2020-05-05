#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define min(a,b) (((a) < (b)) ? (a) : (b))

//Checks whether all valid input has been found
int valid = 0;

//Integers are used to count the covered cards, stock cards, waste cards respectively
//foundationCount checks to ensure all foundation are set correctly, coveredBool helps running through the tableau
int covered, stock, waste, foundationCount, coveredBool, stockBool = 0;

// These strings are used to make sure the proper values are on the file.
char* RULES = "RULES:"; char* FOUNDATIONS = "FOUNDATIONS:"; char* TABLEAU = "TABLEAU:"; char* STOCK = "STOCK:"; char* MOVES = "MOVES:";
char* turn1 = "turn 1"; char* turn3 = "turn 3"; char* unlimited = "unlimited"; char* limit = "limit ";
int clubFoundation, diamondFoundation, heartFoundation, spadeFoundation = 0;

//recognition for switches; numMoves for number of moves to process
int oSwitch, xSwitch, mSwitch, numMoves = 0;

//for numMoves we use min, if we determine -m is activated we set numMoves to the next string with atoi,

//arrays for the cards
char* clubsArr[] = {"_c", "Ac", "1c", "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "Tc", "Jc", "Qc", "Kc"};
char* diamondsArr[] = {"_d", "Ad", "1d", "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "Td", "Jd", "Qd", "Kd"};
char* heartsArr[] = {"_h", "Ah", "1h", "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "Th", "Jh", "Qh", "Kh"};
char* spadesArr[] = {"_s", "As", "1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "Ts", "Js", "Qs", "Ks"};

struct card{
	
	//Rank of the card, Ace('A') through King('K')
	char* rank;
	// Suit includes Hearts('h'),Diamonds('d'),Clubs('c'),Spades('s')
	char* suit;
	//Suit and Rank, the whole value of the card;
	char* SR;
	//connection to the next card
	struct card* next;
};

//used for file I/O
FILE* in;

//prototypes
int isComment(char* s);
int inArray(char* s);
int whatsPresent(char* s);
int fCount(int fC, char* s);
void limitNumber(char* s);
int keywordErr(int v);
void finish();
void foundationSweep();

//Function used to pass over lines with an initial comment
int isComment(char* s){
	int a = 1; int b = 0; int c;
	return c = (s[0] == '#') ? a : b;
}

// place token to find out if its in array

// use this to also place values in linked-card struct
int inArray(char * s){

	char c = s[1];
	int i = 0;
	switch(c){
		case 'c':
		while(i < 15){
			if(s == clubsArr[i]){
				return 1;
			}
			i++;
		}
		break;
		
		case 'd':
		while(i < 15){
			if(s == diamondsArr[i]){
				return 1;
			}
			i++;
		}
		break;
		
		case 'h':
		while(i < 15){
			if(s == heartsArr[i]){
				return 1;
			}
			i++;
		}
		break;
		
		case 's':
		while(i < 15){
			if(s == spadesArr[i]){
				return 1;
			}
		}
		break;
		
		case '|':
		return 1;
		
		default:
		return 0;
	}
	i = 0;
}

// collects vales for tableau
int whatsPresent(char* s){
	char* delim =  " \t\n\r";
	char* token;
	
	token = strtok(s, delim);
	
	while(token != NULL){
		if(token == "|"){
			if(valid == 5){
				coveredBool = 1;
			}
			else{
				stockBool = 1;
			}
		}
		if(coveredBool == 0 || stockBool == 1){
			int j = inArray(token);
			int k = inArray(token);
			if(j == 1){
				covered++;
			}
			if(j == 0 || k == 0){
				fprintf(stderr,"the value of the card is not recognized");
			}
			if(k == 1){
				stock++;
			}
		}
		token = strtok(NULL, s);
	}
	
	coveredBool = 0;
}

//used to check the ordering of the foundation; grabbing the second char in string
//should be clubs(c), diamonds(d), hearts(h), spades(s),
// fCis the foundation count should end at 4, c is input character
int fCount(int fC, char* s) {
	int i = 0;
	printf("This is the line being processed: %s",s);
	switch(fC){
		//clubs
		case 0:
		for(i = 0; i < 15; i++){
			if(strstr(s,clubsArr[i]) != NULL && clubFoundation == 0){
				foundationCount++;
				clubFoundation = 1;
				break;
			}
		}
		//diamonds
		case 1:
		for(i = 0; i < 15; i++){
			if(strstr(s,diamondsArr[i]) != NULL && diamondFoundation == 0){
				foundationCount++;
				diamondFoundation = 1;
				break;
			}
		}
		//hearts
		case 2:
		for(i = 0; i < 15; i++){
			if(strstr(s,heartsArr[i]) != NULL && heartFoundation == 0){
				foundationCount++;
				heartFoundation = 1;
				break;
			}
		}
		//spades
		case 3:
		for(i = 0; i < 15; i++){
			if(strstr(s,spadesArr[i]) != NULL && spadeFoundation == 0){
				foundationCount++;
				spadeFoundation = 1;
				break;
			}
		}
	}
}

//used to find the number of waste cards
void limitNumber(char* s){
	
	char *dest = strstr(s, limit);
	int pos ;
	
	pos = dest - s;
	int val = pos + 6;
	
	char c = s[val];
	int x = c - '0';
	waste = x;
	
	return;
}

//Trying to check the correct ordering of keywords.
int keywordErr(int v){
	if(v != valid){
		printf("The keyword is out of order",stderr);
		exit(1);
	}
	return 1;
}

//method used to output 
void finish(){
	(valid == 7) ? printf("Input file is valid\n") : fprintf(stderr,"Input file is invalid\n");
	printf("%d Covered Cards\n" ,covered);
	printf("%d Stock Cards\n", stock);
	printf("%d Waste Cards",waste);
}


//This function is used to null out the foundationArrays so we can use them.
void foundationSweep(){
	for(int i = 1; i < 15; i++){
		heartsArr[i] = NULL;
		spadesArr[i] = NULL;
		clubsArr[i] = NULL;
		diamondsArr[i] = NULL;
	}
	
}

int main(int argc, const char* argv[]){
	
	//filename saves for later
	const char* fin;
	
	char altFIN[100];
	// Current line for input/ used without allocating space
	char cLine[1000];
	
	///Makes the list to capture all the cards
	struct card* head = NULL;
	head = (struct card*)malloc(sizeof(struct card));
	
	//if the filename is specified in the command line argument
	if(argc == 2){
		//redundant 
		fin = argv[1];
		in = fopen(fin, "r");
		
	}
	else if(fin == NULL){
		fgets(altFIN,100,stdin);
		in = fopen(altFIN, "r");
	}
	// else if(argc == 4 && strstr(argv[0],"cat") != NULL && strstr(argv[2],"|") != NULL && strstr(argv[3],"./check") != NULL){
		// fin = argv[1];
		// in = fopen(fin, "r");
	// }
	//if the file name isn't present follow logic
	// else{
		// char* base;
		// printf("No input file recognized please provide a filename: \n");
		// if(fgets(base,sizeof(base),stdin) != NULL){
			// puts(base);
		// }
		// in = fopen(base, "r");
	// }
	
	if(in == NULL){
		fprintf(stderr,"File not found, check location again\n");
		exit(1);
	}
	while(fgets(cLine,sizeof(cLine),in)){
		
		//Stating if the initial character is not a comment then parse
		if(isComment(cLine) != 1){
			//Here we check for valid things using switch
			//no break statements in case graders are playing games
			switch(valid){
				case 0:
				if(strstr(cLine,RULES) != NULL){
					valid++;
				}
				case 1:
				if((strstr(cLine,turn1) != NULL || strstr(cLine, turn3) != NULL)){
					valid++;
				}
				case 2:
				if(strstr(cLine, unlimited) != NULL){
					valid++;
				}
				////Here we switch it up and also find the number of waste cards;
				else if(strstr(cLine,limit) != NULL){
					valid++;
					limitNumber(cLine);
				}
				case 3:
				//Still need to check foundations
				if(strstr(cLine,FOUNDATIONS) != NULL){
					valid++;
				}
				if(foundationCount != 3){
					fCount(foundationCount, cLine);
				}
				case 4:
				///check the TABLEAU for cards
				///checks for cards in tableau
				if(strstr(cLine,TABLEAU) != NULL){
					if(foundationCount != 4){
						fprintf(stderr, "There was an incorrect setting for Foundations");
						exit(1);
					}
					valid++;
				}
				//check the STOCK for cards
				//checks for cards in the stock
				case 5:
				if(valid == 5){
					whatsPresent(cLine);
				}
				if(strstr(cLine,STOCK) != NULL){
					valid++;
				}
				case 6:
				//FINISH
				if(valid == 6){
					whatsPresent(cLine);
				}
				if(strstr(cLine,MOVES) != NULL){
					valid++;
				}
			}
		}
		if(valid == 7){// find the number of things to check for
			finish();//
		}
	}
	
	fclose(in);
	
	return 0;
}
