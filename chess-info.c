#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int redPawns = 0;
int blackPawns = 0;
int redKings = 0;
int blackKings = 0;

//file indicates the column
int file = 0;
//rank indicates the row
int rank = 0;

char rules[] = "RULES:";
char *capture = "capture";
char *noCapture = "no capture";
char *singleJumps = "single jumps";
char *multipleJumps = "multiple jumps";

char turn[] = "TURN:";
char *red = "red";
char *black = "black";

char board[] = "BOARD:";
char moves[] = "MOVES:";
int validInfo = 0;
//if red set to 0; black set to 1
int startingColor = 0;
//used to add pieces to empty board
int boardIteration = 0;

char correctBoard[8][8] = { {'"','b','"','b','"','b','"','b'},
			    {'b','"','b','"','b','"','b','"'},
			    {'"','b','"','b','"','b','"','b'},
			    {'.','"','.','"','.','"','.','"'},
			    {'"','.','"','.','"','.','"','.'},
			    {'r','"','r','"','r','"','r','"'},
			    {'"','r','"','r','"','r','"','r'},
			    {'r','"','r','"','r','"','r','"'}};
char inputBoard[8][8];

void placeInputBoard(char* input);

int validBoard();

int charactersValid(char* c);

//Function used to into a  mock board; also calculates pieces
void placeInputBoard(char* input){
  int i = 0;
  while(input[i] != '\0'){
    if(input[i] == '"' || input[i] == 'b' || input[i] == '.' ||
       input[i] == 'r'){
      inputBoard[file][rank] = input[i];
      rank++;
      if(rank == 8){
	file++;
	rank = 0;
      }
    }
    if(input[i] == 'r'){
      redPawns++;
    }
    if(input[i] == 'R'){
      redKings++;
    }
    if(input[i] == 'b'){
      blackPawns++;
    }
    if(input[i] == 'B'){
      blackKings++;
    }
    i++;
  }
}
int validBoard(){
  for(int i = 0; i < 8; i++){
    for(int j = 0; j < 8; j++){
      if(inputBoard[i][j] != correctBoard[i][j]){
	return 0;
      }
    }
  }
  return 1;
}

int charactersValid(char* c){
  int i = 0;
  while(c[i] == '\0'){
    if(c[i] == '#'){
      break;
    }
    if(!(c[i] == 'a' || c[i] == 'b' || c[i] == 'c' || c[i] == 'd' || c[i] == 'e'
       || c[i] == 'f' || c[i] == 'g' || c[i] == 'h' || c[i] == ' ' ||
       c[i] == '-' ||  c[i] == '>' || c[i] == '1' || c[i] == '2' || c[i] == '3'
       || c[i] == '4' || c[i] == '5' || c[i] == '6' || c[i] == '7' ||
	 c[i] == '8')){
      return 0;
       }
    i++;
  }
  return 1;
}

int main(int argc, const char* argv[]){
  
  FILE *fin;
  fin = fopen(argv[1],"r");
  char currentLine[100];
  int n  = validInfo;

  if(fin == NULL){
    printf("File doesn't exist!\n");
    exit(1);
  }

  //file the format specified in the assignment pdf and hope for the best
  //First we scan for rules and delimit it.
  while(fgets(currentLine,sizeof(currentLine),fin)){
    if(validInfo == 6 && boardIteration < 8){
      placeInputBoard(currentLine);
      if(boardIteration == 7){
	validInfo++;
      }
      boardIteration++;
    }
    if(strstr(currentLine,rules) != NULL && validInfo == 0){
      validInfo++;
    }
    if(strstr(currentLine,rules) == NULL && validInfo == 0 && n == validInfo){
      printf("There are no rules present!\n");
      exit(1);
    }
    if((strstr(currentLine,capture) != NULL ||
	strstr(currentLine,noCapture) != NULL) && validInfo == 1){
      validInfo++;
    }
    if(strstr(currentLine,capture) == NULL &&
       strstr(currentLine,noCapture) == NULL && validInfo == 1 &&
       n == validInfo){
      printf("There are no correct capture configurations!\n");
      exit(1);
    }
    if((strstr(currentLine,singleJumps) != NULL ||
	strstr(currentLine,multipleJumps) != NULL) && validInfo == 2){
      validInfo++;
    }
    if(strstr(currentLine,singleJumps) == NULL &&
       strstr(currentLine,multipleJumps) == NULL && validInfo == 2 &&
       n == validInfo){
      printf("There are no correct jump configurations!\n");
      exit(1);
    }
    if(strstr(currentLine,turn) != NULL && validInfo == 3){
      validInfo++;
    }
    if(strstr(currentLine,turn) == NULL && validInfo == 3 &&
       n == validInfo){
      printf("There are no rules present!\n");
      exit(1);
    }
    if((strstr(currentLine,red) != NULL ||
       strstr(currentLine,black) != NULL) && validInfo == 4){
      if(strstr(currentLine,black) != NULL){
	startingColor = 1;
      }
      validInfo++;
    }
    if((strstr(currentLine,red) == NULL ||
	strstr(currentLine,black) == NULL) && validInfo == 4 &&
       n == validInfo){
      printf("Invalid use of color!\n");
      exit(1);
    }
    if(strstr(currentLine,board) != NULL  && validInfo == 5){
      validInfo++;
    }
    if(strstr(currentLine,board) == NULL && validInfo == 5 &&
       n == validInfo){
      printf("There is no board present!\n");
      exit(1);
    }
    if(validInfo == 7){
      int valid = validBoard();
      if(valid == 0){
	printf("This is an invalid board!\n");
	exit(1);
      }
      validInfo++;
    }
    if(strstr(currentLine,moves) != NULL && validInfo == 8){
      validInfo++;
    }
    if(strstr(currentLine,moves) == NULL && validInfo == 8 && n == validInfo){
      printf("There are no moves present!\n");
      exit(1);
    }

    
    if(validInfo == 9){
      int correctCharacters = charactersValid(currentLine);
      if(correctCharacters == 0){
	printf("There are invalid moves based on input");
	exit(1);
      }
    }
    n++;
  }
  validInfo++;
  fclose(fin);
 
  if(validInfo == 10){
    printf("VALID INPUT\n");
    printf("Initial configuration\n");
    printf("Turn: %s\n", startingColor == 0 ? red : black);
    printf("Red: %d kings, %d pawns\n",redKings,redPawns);
    printf("Black: %d kings, %d pawns\n", blackKings,blackPawns);
  }
}
