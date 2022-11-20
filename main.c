#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_ROWS 6
#define BOARD_COLS 7

typedef struct Board {
	int rows;
	int cols;
	int (*board)[BOARD_ROWS][BOARD_COLS];
} Board;

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

void print_board(Board b){
	printf("|A|B|C|D|E|F|G|");
	for (int i=0; i<b.cols; i++){
		printf("\n");
		for (int j=0; j<b.rows; j++){
			if (j==0){
				printf("|%d|", (*b.board)[i][j]);
			}
			else{
				printf("%d|", (*b.board)[i][j]);
			}
		}
	}
	printf("\n");
}

Board create_board(int rows, int cols){
	Board b;
	b.rows = rows;
	b.cols = cols;
	int board[rows][cols];
	memset(board, 0, sizeof(board));
	int (*boardPtr)[rows][cols] = &board;
	b.board = boardPtr;
	return b;
}

int main () {
	int startChoice;
	Board playingBoard;
	char *playerOne = malloc(sizeof(char));
	char *playerTwo = malloc(sizeof(char));
	// clear_screen();
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
		playingBoard = create_board(BOARD_ROWS, BOARD_COLS);
		print_board(playingBoard);
		// printf("%s, %s\n", playerOne, playerTwo);
		free(playerOne);
		free(playerTwo);
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