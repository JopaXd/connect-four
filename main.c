#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_ROWS 6
#define BOARD_COLS 7

void clear_screen(){
	#ifdef linux
	system("clear");
	#endif
	//Untested.
	#ifdef _WIN32
	system("cls");
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

void printBoard(int b[BOARD_ROWS][BOARD_COLS]){
	printf("|A|B|C|D|E|F|G|");
	for (int i=0; i<BOARD_ROWS; i++){
		printf("\n");
		for (int j=0; j<BOARD_COLS; j++){
			if (j==0){
				printf("|%d|", b[i][j]);
			}
			else{
				printf("%d|", b[i][j]);
			}
		}
	}
	printf("\n");
}

int main () {
	int startChoice;
	int playingBoard[BOARD_ROWS][BOARD_COLS];
	char *playerOne = malloc(sizeof(char));
	char *playerTwo = malloc(sizeof(char));
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
		printf("Name of the second player:");
		getUserInput(playerTwo);
		clear_screen();
		//Create playing board.
		//AKA. Fill it up with zeros.
		memset(playingBoard, 0, sizeof(playingBoard));
		printBoard(playingBoard);
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