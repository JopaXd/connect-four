#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_ROWS 6
#define BOARD_COLS 7
const char ALPHABET[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

void clear_screen(){
	//Linux
	#ifdef __linux__
	system("clear");
	#endif
	//Windows (Untested)
	#ifdef _WIN32
	system("cls");
	#endif
	#ifdef __APPLE__
	//macOS (untested)
	system("clear");	
	#endif
}

void getUserInput(char * s){
	int c;
	int i = 0;
	/* Read characters until found an EOF or newline character. */
	while((c = getchar()) != '\n' && c != EOF)
	{
		s[i++] = c;
		s = realloc(s, i+1); // Add space for another character to be read.
	}
	s[i] = '\0';  // Null terminate the string
}

void printBoard(int b[BOARD_ROWS][BOARD_COLS], char pCols[]){
	printf("|");
	for (int i=0; i<BOARD_COLS; i++){
		printf("%c|", pCols[i]);
	}
	char charToPrint = ' ';
	for (int i=0; i<BOARD_ROWS; i++){
		printf("\n");
		for (int j=0; j<BOARD_COLS; j++){
			if (b[i][j] == -1){
				charToPrint = ' ';
			}
			else if(b[i][j] == 0){
				charToPrint = 'X';
			}
			else if(b[i][j] == 1){
				charToPrint = 'O';
			} 
			if (j==0){

				printf("|%c|", charToPrint);
			}
			else{
				printf("%c|", charToPrint);
			}
		}
	}
	printf("\n");
}

int checkItemInArray(char item, char arr[], int arrLength){
	for (int i=0; i<arrLength; i++){
		if (arr[i] == item){
			return 1;
		}
	}
	return 0;
}

int makeMove(int (*b)[BOARD_ROWS][BOARD_COLS], char colToPlay, char pCols[], int player){
	int col;
	for (int i=0; i<BOARD_COLS; i++){
		if (pCols[i] == colToPlay){
			col = i;
			break;
		}
	}
	if ((*b)[0][col] != -1){
		//This column is full, therefore not playable.
		return 0;
	}
	for (int i=BOARD_ROWS; i>-1; i--){
		if ((*b)[i][col] == -1){
			if (player == 0){
				//Player one
				(*b)[i][col] = 0;
			}
			else if (player == 1){
				//Player two.
				(*b)[i][col] = 1;
			}
			break;
		}
	}
	return 1;
}

int main() {
	int startChoice;
	int playingBoard[BOARD_ROWS][BOARD_COLS];
	int (*playingBoardPtr)[BOARD_ROWS][BOARD_COLS] = &playingBoard;
	char playableCols[BOARD_COLS];
	for (int i=0; i<=BOARD_COLS; i++){
		playableCols[i] = ALPHABET[i];
	}
	int turn=0;
	char *playerOne = malloc(sizeof(char));
	char *playerTwo = malloc(sizeof(char));
	//COMMENT THIS TO DEBUG
	clear_screen();
	printf("Choose an option:\n");
	printf("1. Play a new game\n");
	printf("2. Load saved game\n");
	printf("3. Exit the game\n");
	// This %*c is necessary. Otherwise the scanf makes getchar in getUserInput get skipped.
	//No idea...
	scanf("%d%*c", &startChoice);
	if (startChoice == 1) {
		clear_screen();
		printf("Name of the first player: ");
		getUserInput(playerOne);
		clear_screen();
		printf("Name of the second player: ");
		getUserInput(playerTwo);
		clear_screen();
		//Create playing board.
		//AKA. Fill it up with -1.
		memset(playingBoard, -1, sizeof(playingBoard));
		printBoard(playingBoard, playableCols);
		printf("\n");
		char colChoice;
		while (1){
			if (turn == 0){
				//Player one turn.
				printf("%s, your turn! ", playerOne);
				scanf("%c%*c", &colChoice);
				if (checkItemInArray(colChoice, playableCols, sizeof(playableCols)) == 0){
					printf("\n");
					printf("Not a playable field!\n");
					continue;
				}
				else{
					if(makeMove(playingBoardPtr, colChoice, playableCols, turn) == 1) {
						//Check if there's a winnner.
						clear_screen();
						printBoard(playingBoard, playableCols);
						turn = 1;
					}
					else{
						printf("\n");
						printf("This column is full!\n");
						continue;
					}	
				}
				continue;
			}
			else{
				//Player two turn!
				printf("%s, your turn! ", playerTwo);
				scanf("%c%*c", &colChoice);
				if (checkItemInArray(colChoice, playableCols, sizeof(playableCols)) == 0){
					printf("\n");
					printf("Not a playable field!\n");
					continue;
				}
				
				else{
					if(makeMove(playingBoardPtr, colChoice, playableCols, turn) == 1) {
						//Check if there's a winnner.
						clear_screen();
						printBoard(playingBoard, playableCols);
						turn = 0;
					}
					else{
						printf("\n");
						printf("This coulmnn is full!\n");
						continue;
					}	
				}
				continue;
			}
		}
		// printf("%s, %s\n", playerOne, playerTwo);
		// free(playerOne);
		// free(playerTwo);
	}
	else if (startChoice == 2){
		//Implement.
	}
	else if (startChoice == 3){
		printf("Exiting...\n");
		return 0;
	}
	return 0;
}