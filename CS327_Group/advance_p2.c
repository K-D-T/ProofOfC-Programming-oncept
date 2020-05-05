#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

//Checks whether all valid input has been found
int valid = 0;

//Integers are used to count the covered cards, stock cards, waste cards respectively
//foundationCount checks to ensure all foundation are set correctly, coveredBool helps running through the tableau
int covered, stock, waste, foundationCount, coveredBool, stockBool = 0;

// These strings are used to make sure the proper values are on the file.
char *RULES = "RULES:";
char *FOUNDATIONS = "FOUNDATIONS:";
char *TABLEAU = "TABLEAU:";
char *STOCK = "STOCK:";
char *MOVES = "MOVES:";
char *turn1 = "turn 1";
char *turn3 = "turn 3";
char *unlimited = "unlimited";
char *limit = "limit ";
int clubFoundation, diamondFoundation, heartFoundation, spadeFoundation = 0;

//recognition for switches; numMoves for number of moves to process
int oSwitch, xSwitch, mSwitch, numMoves = 0;

//for numMoves we use min, if we determine -m is activated we set numMoves to the next string with atoi,

//arrays for the cards
char *clubsArr[] = {"_c", "Ac", "1c", "2c", "3c", "4c", "5c", "6c", "7c", "8c", "9c", "Tc", "Jc", "Qc", "Kc"};
char *diamondsArr[] = {"_d", "Ad", "1d", "2d", "3d", "4d", "5d", "6d", "7d", "8d", "9d", "Td", "Jd", "Qd", "Kd"};
char *heartsArr[] = {"_h", "Ah", "1h", "2h", "3h", "4h", "5h", "6h", "7h", "8h", "9h", "Th", "Jh", "Qh", "Kh"};
char *spadesArr[] = {"_s", "As", "1s", "2s", "3s", "4s", "5s", "6s", "7s", "8s", "9s", "Ts", "Js", "Qs", "Ks"};

struct card {

    //Rank of the card, Ace('A') through King('K')
    int rank;
    // Suit includes Hearts('h'),Diamonds('d'),Clubs('c'),Spades('s')
    char suit;
    //Suit and Rank, the whole value of the card;
    char *SR;
    //connection to the next card
    struct card *next;
};

//used for file I/O
FILE *in;

//prototypes
int isComment(char *s);

int inArray(char *s);

int whatsPresent(char *s);

int fCount(int fC, char *s);

void limitNumber(char *s);

int keywordErr(int v);

void finish();

void foundationSweep();

///RM initializes cards to be 'blank'
struct card cardInit(struct card init) {
    init.next = NULL;
    init.rank = 0;
    init.SR = NULL;
    init.suit = 's';
    return init;
}

//Function used to pass over lines with an initial comment
int isComment(char *s) {
    int a = 1;
    int b = 0;
    int c;
    return c = (s[0] == '#') ? a : b;
}

// place token to find out if its in array

// use this to also place values in linked-card struct
int inArray(char *s) {

    char c = s[1];
    int i = 0;
    switch (c) {
        case 'c':
            while (i < 15) {
                if (s == clubsArr[i]) {
                    return 1;
                }
                i++;
            }
            break;

        case 'd':
            while (i < 15) {
                if (s == diamondsArr[i]) {
                    return 1;
                }
                i++;
            }
            break;

        case 'h':
            while (i < 15) {
                if (s == heartsArr[i]) {
                    return 1;
                }
                i++;
            }
            break;

        case 's':
            while (i < 15) {
                if (s == spadesArr[i]) {
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
/*
///RM parses string to assign values to foundation as specified by the input file
void fillFound(char *s) {///unused?

    char c = s[1];
    int i = 0;
    switch (c) {
        case 'c':
            while (i < 15) {
                if (s == clubsArr[i]) {

                    return 1;
                }
                i++;
            }
            break;

        case 'd':
            while (i < 15) {
                if (s == diamondsArr[i]) {
                    return 1;
                }
                i++;
            }
            break;

        case 'h':
            while (i < 15) {
                if (s == heartsArr[i]) {
                    return 1;
                }
                i++;
            }
            break;

        case 's':
            while (i < 15) {
                if (s == spadesArr[i]) {
                    return 1;
                }
            }
            break;

        default:
            return 0;
    }
    i = 0;
}
*/

// collects vales for tableau
int whatsPresent(char *s) {
    char *delim = " \t\n\r";
    char *token;

    token = strtok(s, delim);

    while (token != NULL) {
        if (token == "|") {
            if (valid == 5) {
                coveredBool = 1;
            } else {
                stockBool = 1;
            }
        }
        if (coveredBool == 0 || stockBool == 1) {
            int j = inArray(token);
            int k = inArray(token);
            if (j == 1) {
                covered++;
            }
            if (j == 0 || k == 0) {
                fprintf(stderr, "the value of the card is not recognized");
            }
            if (k == 1) {
                stock++;
            }
        }
        token = strtok(NULL, s);
    }

    coveredBool = 0;
}

/*
///RM Handles reading and building foundations section when passed a single line
int readFound(char *s) {///Redundant?
    char *delim = " \t\n\r";
    char *token;

    token = strtok(s, delim);

    while (token != NULL) {
        fillFound(token);
        token = strtok(NULL, s);
    }

    coveredBool = 0;
}
 */

//used to check the ordering of the foundation; grabbing the second char in string
//should be clubs(c), diamonds(d), hearts(h), spades(s),
// fCis the foundation count should end at 4, c is input character
int fCount(int fC, char *s) {
    int i = 0;
    printf("This is the line being processed: %s", s);
    switch (fC) {
        //clubs
        case 0:
            for (i = 0; i < 15; i++) {
                if (strstr(s, clubsArr[i]) != NULL && clubFoundation == 0) {
                    foundationCount++;
                    clubFoundation = 1;
                    break;
                }
            }
            //diamonds
        case 1:
            for (i = 0; i < 15; i++) {
                if (strstr(s, diamondsArr[i]) != NULL && diamondFoundation == 0) {
                    foundationCount++;
                    diamondFoundation = 1;
                    break;
                }
            }
            //hearts
        case 2:
            for (i = 0; i < 15; i++) {
                if (strstr(s, heartsArr[i]) != NULL && heartFoundation == 0) {
                    foundationCount++;
                    heartFoundation = 1;
                    break;
                }
            }
            //spades
        case 3:
            for (i = 0; i < 15; i++) {
                if (strstr(s, spadesArr[i]) != NULL && spadeFoundation == 0) {
                    foundationCount++;
                    spadeFoundation = 1;
                    break;
                }
            }
    }
}

//used to find the number of waste cards
void limitNumber(char *s) {

    char *dest = strstr(s, limit);
    int pos;

    pos = dest - s;
    int val = pos + 6;

    char c = s[val];
    int x = c - '0';
    waste = x;

    return;
}

//Trying to check the correct ordering of keywords.
int keywordErr(int v) {
    if (v != valid) {
        printf("The keyword is out of order", stderr);
        exit(1);
    }
    return 1;
}

//method used to output 
void finish() {
    (valid == 7) ? printf("Input file is valid\n") : fprintf(stderr, "Input file is invalid\n");
    printf("%d Covered Cards\n", covered);
    printf("%d Stock Cards\n", stock);
    printf("%d Waste Cards", waste);
}


//This function is used to null out the foundationArrays so we can use them.
void foundationSweep() {
    for (int i = 1; i < 15; i++) {
        heartsArr[i] = NULL;
        spadesArr[i] = NULL;
        clubsArr[i] = NULL;
        diamondsArr[i] = NULL;
    }

}

int main(int argc, const char *argv[]) {

    ///counter to track number of times reset has been called
    int resetCount = 0;

    /// counts number of moves performed
    int moves;
    ///Allows table to continue running after the line that contains tableau
    int tBool = 0;

    ///Allows foundation to continue running after the line that contains foundation.
    int fBool = 0;

    ///Stores the rule for number of cards turned by a call to flip from stock to waste. 1 or 3.
    int turnNum = 1;

    ///Stores the number of times the waste can be reset
    int resetMax = 9999;

    int turnCount = 1; //stores the value of turn count.
    ///stock setup
    /*
     * stockHead -> stockDummy, .rank = 27
     * stockTail -> (last covered card) -- no waste if same as wasteTail
     * wasteTail -> (last card in list) -- no stock if same as stockHead
     */
    struct card stockDummy = cardInit(stockDummy);
    stockDummy.rank = 27;
    struct card *stockHead = &stockDummy;
    struct card *stockTail = &stockDummy;
    struct card wasteTail = stockDummy;

/// shuts off moving stocktail
    int covBool = 1;


    //filename saves for later
    const char *fin;

    char altFIN[100];
    // Current line for input/ used without allocating space
    char cLine[1000];

    ///Makes each foundation
    /// -A single card whose value will be that of the largest on the foundation or 0 if empty
    struct card cFound = cardInit(cFound);
    struct card hFound = cardInit(hFound);
    struct card sFound = cardInit(sFound);
    struct card dFound = cardInit(dFound);

    ///Makes the stock
    /// -


    ///Makes the table
    /// - An array of cards, location zero being a dummy and 1-7 corresponding to column on table (left to right)
    struct card table[8];
    ///initialize all
    for (int i = 1; i <= 7; i++) {
        table[i] = cardInit(table[i]);
    }
    /*RM commented out... do I need this?
	struct card* head = NULL;
	head = (struct card*)malloc(sizeof(struct card));
	*/
    //if the filename is specified in the command line argument
    if (argc == 2) {
        //redundant
        fin = argv[1];
        in = fopen(fin, "r");

    } else if (fin == NULL) {
        fgets(altFIN, 100, stdin);
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

    if (in == NULL) {
        fprintf(stderr, "File not found, check location again\n");
        exit(1);
    }
    while (fgets(cLine, sizeof(cLine), in)) {

        //Stating if the initial character is not a comment then parse
        if (isComment(cLine) != 1) {
            //Here we check for valid things using switch
            //no break statements in case graders are playing games
            switch (valid) {
                case 0:///Verifies that rules section is first
                    if (strstr(cLine, RULES) != NULL) {
                        valid++;
                    }
                case 1:/// sets number of cards to turn from stock
                    if (strstr(cLine, turn1) != NULL) {
                        turnNum = 1;
                        valid++;
                    } else if (strstr(cLine, turn3) != NULL) {
                        turnNum = 3;
                        valid++;
                    }

                case 2:
                    if (strstr(cLine, unlimited) != NULL) {
                        valid++;
                    }
                        ////Here we switch it up and also find the number of waste cards;
                    else if (strstr(cLine, limit) != NULL) {
                        valid++;
                        limitNumber(cLine);
                    }
                case 3:///Read the foundations section and assign values to each of the initialized foundation cards
                    //Still need to check foundations
                    if (strstr(cLine, FOUNDATIONS) != NULL || fBool == 1) {
                        char *delim = " \t\n\r";
                        char *token;

                        token = strtok(cLine, delim);

                        while (token != NULL) {
                            int fCount = 0;
                            char c = token[1];
                            int i = 0;
                            switch (c) {
                                case 'c':
                                    while (i < 14) {
                                        if (token == clubsArr[i]) {
                                            fBool++;
                                            cFound.rank = i;
                                            cFound.SR = token;
                                            continue;
                                        }
                                        i++;
                                    }
                                    break;

                                case 'd':
                                    while (i < 14) {
                                        if (token == diamondsArr[i]) {
                                            fBool++;
                                            dFound.rank = i;
                                            dFound.SR = token;
                                            continue;
                                        }
                                        i++;
                                    }
                                    break;

                                case 'h':
                                    while (i < 14) {
                                        if (token == heartsArr[i]) {
                                            fBool++;
                                            hFound.rank = i;
                                            hFound.SR = token;
                                            continue;
                                        }
                                        i++;
                                    }
                                    break;

                                case 's':
                                    while (i < 14) {
                                        if (token == spadesArr[i]) {
                                            fBool++;
                                            sFound.rank = i;
                                            sFound.SR = token;
                                            continue;
                                        }
                                        i++;
                                    }
                                    break;

                                default:
                                    continue; ///error message?
                            }
                        }
                        if (fBool == 4) {
                            valid++;
                        }
                        token = strtok(NULL, delim);
                    }
                case 4:
                    ////check the TABLEAU for cards
                    ////checks for cards in tableau, add to columns
                    if (strstr(cLine, TABLEAU) != NULL || tBool < 7) {
                        char *delim = " \t\n\r";
                        char *token;

                        token = strtok(cLine, delim);

                        while (token != NULL) {
                            int fCount = 0;///used as counter for number of foundations initialized
                            char c = token[1];
                            int i = 0;
                            if (*token == '|') {///todo: rest of cards are uncovered
                                struct card *tempCard;

                            }
                            switch (c) {
                                case 'c':
                                    while (i < 14) {
                                        if (token == clubsArr[i]) {
                                            struct card *tempCard = &table[tBool + 1];
                                            while (tempCard->next !=
                                                   NULL) {///finds last card in list and assigns to tempCard
                                                tempCard = tempCard->next;
                                            }
                                            tempCard->next = (struct card *) malloc(
                                                    sizeof(struct card)); ///Makes a new card to go next
                                            tempCard = tempCard->next;
                                            tempCard->suit = 'c';
                                            tempCard->rank = i;
                                            tempCard->SR = token;
                                            continue;///handle next token
                                        }
                                        i++;
                                    }
                                    break;

                                case 'd':
                                    while (i < 14) {
                                        if (token == diamondsArr[i]) {
                                            struct card *tempCard = &table[tBool + 1];
                                            while (tempCard->next !=
                                                   NULL) { ///finds last card in list and assigns to tempCard
                                                tempCard = tempCard->next;
                                            }
                                            tempCard->next = (struct card *) malloc(
                                                    sizeof(struct card)); ///Makes a new card to go next
                                            tempCard = tempCard->next;
                                            tempCard->suit = 'd';
                                            tempCard->rank = i;
                                            tempCard->SR = token;
                                            continue;///handle next token
                                        }
                                        i++;
                                    }
                                    break;

                                case 'h':
                                    while (i < 14) {
                                        if (token == heartsArr[i]) {
                                            struct card *tempCard = &table[tBool + 1];
                                            while (tempCard->next !=
                                                   NULL) { ///finds last card in list and assigns to tempCard
                                                tempCard = tempCard->next;
                                            }
                                            tempCard->next = (struct card *) malloc(
                                                    sizeof(struct card)); ///Makes a new card to go next
                                            tempCard = tempCard->next;
                                            tempCard->suit = 'h';
                                            tempCard->rank = i;
                                            tempCard->SR = token;
                                            continue;///handle next token
                                        }
                                        i++;
                                    }
                                    break;

                                case 's':
                                    while (i < 14) {
                                        if (token == spadesArr[i]) {
                                            struct card *tempCard = &table[tBool +
                                                                           1]; //todo: verify this method to point at root card->
                                            while (tempCard->next !=
                                                   NULL) { ///finds last card in list and assigns to tempCard
                                                tempCard = tempCard->next;
                                            }
                                            tempCard->next = (struct card *) malloc(
                                                    sizeof(struct card)); ///Makes a new card to go next
                                            tempCard = tempCard->next;
                                            tempCard->suit = 's';
                                            tempCard->rank = i;
                                            tempCard->SR = token;
                                            continue;///handle next token
                                        }
                                        i++;
                                    }
                                    break;

                                default:
                                    continue; ///error message?
                            }
                            tBool++;
                            if (tBool == 7) {
                                valid++;
                            }
                            token = strtok(NULL, delim);
                        }

                    }
                    valid++;

                    //check the STOCK for cards
                    //checks for cards in the stock
                case 5:///build stock
                    if (valid == 5) {
                        int covBool = 1;
                        char *delim = " \t\n\r";
                        char *token;

                        token = strtok(cLine, delim);

                        while (token != NULL) {
                            int i = 0;
                            char c;
                            struct card *addCard;
                            if (token[0] == '|') {/// checks for | and handles
                                c = token[0];
                            } else {
                                c = token[1];
                                addCard = (struct card *) malloc(sizeof(struct card));
                                cardInit(*addCard);
                            }
                            switch (c) {
                                case 'c':
                                    while (i < 14) {
                                        if (token == clubsArr[i]) {
                                            addCard->rank = i;
                                            addCard->SR = token;
                                            addCard->suit = 'c';
                                            wasteTail.next = addCard;
                                            wasteTail = *addCard;
                                            if (covBool)
                                                stockTail = addCard;
                                            continue;
                                        }
                                        i++;
                                    }
                                    break;

                                case 'd':
                                    while (i < 14) {
                                        if (token == diamondsArr[i]) {
                                            addCard->rank = i;
                                            addCard->SR = token;
                                            addCard->suit = 'd';
                                            wasteTail.next = addCard;
                                            wasteTail = *addCard;
                                            if (covBool)
                                                stockTail = addCard;
                                            continue;
                                        }
                                        i++;
                                    }
                                    break;

                                case 'h':
                                    while (i < 14) {
                                        if (token == heartsArr[i]) {
                                            addCard->rank = i;
                                            addCard->SR = token;
                                            addCard->suit = 'h';
                                            wasteTail.next = addCard;
                                            wasteTail = *addCard;
                                            if (covBool)
                                                stockTail = addCard;
                                            continue;
                                        }
                                        i++;
                                    }
                                    break;

                                case 's':
                                    while (i < 14) {
                                        if (token == spadesArr[i]) {
                                            addCard->rank = i;
                                            addCard->SR = token;
                                            addCard->suit = 's';
                                            wasteTail.next = addCard;
                                            wasteTail = *addCard;
                                            if (covBool)
                                                stockTail = addCard;
                                            continue;
                                        }
                                        i++;
                                    }
                                    break;

                                default: ///c == '|'
                                    covBool = 0;

                                    continue; ///error message?
                            }
                        }
                        token = strtok(NULL, delim);

                    }///todo: skip stock and others if needed(the word stock in ppr)

                case 6:///do moves
                    if (valid == 6) {
                        char *delim = " \t\n\r";
                        char *token;

                        token = strtok(cLine, delim);
                        while (token != NULL) {
                            char src = token[0];/// cover cases . and r here
                            //char des = token[1];/// wait until inside of other cases.
                            switch (src) {
                                case '.':///turn 1 or 3 depending on rule turnNum
                                    if (&stockHead == &stockTail)
                                        break;
                                    while (turnCount < turnNum && stockHead != stockTail) {}
                                    struct card *tmpCard = stockHead;
                                    while (tmpCard->next != stockTail) {
                                        tmpCard = tmpCard->next;
                                        stockTail = tmpCard;
                                    }

                            }

                            break;
                            case 'r':///reset waste to stock
                                if (resetCount < resetMax) {///add an else error message if resets run out.
                                    stockTail = &wasteTail;
                                    resetCount++;
                                }

                            break;
                            default: {
                                char des = token[3];
                                struct card *srcP; ///points at source card
                                struct card *dstP;/// points at destination card(if applicable)
                                if (token[0] == 'w') {//move stockTail.next to dst and fix pointers
                                    if (stockTail == &wasteTail) {
                                        break;///todo make error for no waste card to play
                                    } else {
                                        srcP = stockTail->next;
                                    }
                                    ///todo destination handling and free
                                    if (token[3] == 'f') {///case for each suit, check and update foundation
                                        char srcSuit = srcP->suit;
                                        switch (srcSuit) {
                                            case 'c':
                                                if (cFound.rank == srcP->rank - 1) {
                                                    cFound.rank++;
                                                    stockTail->next = stockTail->next->next;
                                                    free(srcP);
                                                }///else error code
                                                break;
                                            case 'd':
                                                if (dFound.rank == srcP->rank - 1) {
                                                    dFound.rank++;
                                                    stockTail->next = stockTail->next->next;
                                                    free(srcP);
                                                }///else error code
                                                break;

                                            case 'h':
                                                if (hFound.rank == srcP->rank - 1) {
                                                    hFound.rank++;
                                                    stockTail->next = stockTail->next->next;
                                                    free(srcP);
                                                }///else error code
                                                break;

                                            case 's':
                                                if (sFound.rank == srcP->rank - 1) {
                                                    sFound.rank++;
                                                    stockTail->next = stockTail->next->next;
                                                    free(srcP);
                                                }///else error code
                                                break;
                                            default:
                                                continue;
                                        }
                                    } else {///dst is char of 1-7, convert to int

                                        int tempCol = token[3] + '0';//char to int
                                        dstP = &table[tempCol + 1];
                                        while (dstP->next != NULL)//go to end of column
                                            dstP = dstP->next;
                                        if (dstP->rank == srcP->rank - 1)///validate rank

                                            if (((dstP->suit == 'c' || dstP->suit == 's') &&
                                                 (srcP->suit == 'h' || srcP->suit == 'd')) ||
                                                ((dstP->suit == 'h' || dstP->suit == 'd') &&
                                                 (srcP->suit == 'c' || srcP->suit == 's'))) {///verify opposite colors
                                                srcP->next = NULL;
                                                stockTail->next == stockTail->next->next;
                                                dstP->next = srcP;
                                            } //error message about suits


                                    }

                                    continue; ///error message?
                                } else {///token is a number at src
                                    int tempDCol = token[3] + '0';//char to int
                                    int tempSCol = src + '0';
                                    srcP = &table[tempSCol + 1];
                                    while (srcP->next != NULL)//go to end of column
                                        srcP = dstP->next;
                                    if (token[3] == 'f') {///case for each suit, check and update foundation
                                        char srcSuit = srcP->suit;
                                        switch (srcSuit) {
                                            case 'c':
                                                if (cFound.rank == srcP->rank - 1) {
                                                    cFound.rank++;
                                                    stockTail->next = stockTail->next->next;
                                                    free(srcP);
                                                }///else error code
                                                break;
                                            case 'd':
                                                if (dFound.rank == srcP->rank - 1) {
                                                    dFound.rank++;
                                                    stockTail->next = stockTail->next->next;
                                                    free(srcP);
                                                }///else error code
                                                break;

                                            case 'h':
                                                if (hFound.rank == srcP->rank - 1) {
                                                    hFound.rank++;
                                                    stockTail->next = stockTail->next->next;
                                                    free(srcP);
                                                }///else error code
                                                break;

                                            case 's':
                                                if (sFound.rank == srcP->rank - 1) {
                                                    sFound.rank++;
                                                    stockTail->next = stockTail->next->next;
                                                    free(srcP);
                                                }///else error code
                                                break;
                                            default:
                                                continue;
                                        }
                                    } else {///dst is char of 1-7, convert to int

                                        int tempCol = token[3] + '0';//char to int
                                        dstP = &table[tempCol + 1];
                                        while (dstP->next != NULL)//go to end of column
                                            dstP = dstP->next;
                                        if (dstP->rank == srcP->rank - 1)///validate rank

                                            if (((dstP->suit == 'c' || dstP->suit == 's') &&
                                                 (srcP->suit == 'h' || srcP->suit == 'd')) ||
                                                ((dstP->suit == 'h' || dstP->suit == 'd') &&
                                                 (srcP->suit == 'c' || srcP->suit == 's'))) {///verify opposite colors
                                                srcP->next = NULL;
                                                stockTail->next == stockTail->next->next;
                                                dstP->next = srcP;
                                            } //error message about suits


                                    }

                                    continue; ///error message?
                                }
                            }
                        }


                    token = strtok(NULL, delim);
            }

            }
        }


        valid++;/// eof reached
        if (valid == 7) {// find the number of things to check for
            finish();//
        }

    }

    fclose(in);

    return 0;
}