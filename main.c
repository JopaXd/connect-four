#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BOARD_ROWS 6
#define BOARD_COLS 7

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
	//What.
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

int checkWinner(int (*b)[BOARD_ROWS][BOARD_COLS]){
	int token;
	int nextToken;
	int connectedTokens;
	for (int i = 0; i<BOARD_ROWS; i++){
		for (int j=0; j<BOARD_COLS; j++){
			if ((*b)[i][j] == -1){
				//Skip
				continue;
			}
			else{
				token = (*b)[i][j];
				//Left check:
				//Check if there are enough items to the left
				if (j>=3){
					for (int c = j; c>=0; c--){
						nextToken = (*b)[i][c];
						if (token == nextToken){
							connectedTokens++;
							if (connectedTokens==4){
								//If the token = 0, player one won, if its 1, player two won.
								return token;
							}
						}
						else{
							//Blocked by other players token, therefore no connection of 4, move on.
							connectedTokens=0;
							break;
						}
					}
					//Not enough tokens connected in this direction, reset the counter.
					connectedTokens = 0;
				}
				//Right check:
				//Check if there are enough items to the right.
				if (j<=3){
					for (int c = j; c<BOARD_COLS; c++){
						nextToken = (*b)[i][c];
						if (token == nextToken){
							connectedTokens++;
							if (connectedTokens==4){
								//If the token = 0, player one won, if its 1, player two won.
								return token;
							}
						}
						else{
							//Blocked by other players token, therefore no connection of 4, move on.
							connectedTokens=0;
							break;
						}
					}
					//Not enough tokens connected in this direction, reset the counter.
					connectedTokens = 0;
				}
				//Up Check:
				//Check if there are enough items above.
				if(i>=3){
					for (int c=i; c>=0; c--){
						nextToken = (*b)[c][j];
						if (token == nextToken){
							connectedTokens++;
							if (connectedTokens==4){
								//If the token = 0, player one won, if its 1, player two won.
								return token;
							}
						}
						else{
							//Blocked by other players token, therefore no connection of 4, move on.
							connectedTokens=0;
							break;
						}
					}
					//Not enough tokens connected in this direction, reset the counter.
					connectedTokens = 0;
				}
				//Bottom Check:
				//Check if there are enough items underneath.
				if(i<=3){
					for (int c=i; c<BOARD_ROWS; c++){
						nextToken = (*b)[c][j];
						if (token == nextToken){
							connectedTokens++;
							if (connectedTokens==4){
								//If the token = 0, player one won, if its 1, player two won.
								return token;
							}
						}
						else{
							//Blocked by other players token, therefore no connection of 4, move on.
							connectedTokens=0;
							break;
						}
					}
					//Not enough tokens connected in this direction, reset the counter.
					connectedTokens = 0;
				}
				//Diagoal checks:
				//Up left check:
				if (i >= 3 && j >= 3){
					for (int c=i, d=j; c>=0 && d>=0; c--,d--){
						nextToken = (*b)[c][d];
						if (token == nextToken){
							connectedTokens++;
							if (connectedTokens==4){
								//If the token = 0, player one won, if its 1, player two won.
								return token;
							}
						}
						else{
							//Blocked by other players token, therefore no connection of 4, move on.
							connectedTokens=0;
							break;
						}
					}
					//Not enough tokens connected in this direction, reset the counter.
					connectedTokens = 0;
				}
				//Up right check:
				if (i <=3 && j>=3){
					for (int c=i, d=j; c<BOARD_ROWS && d>=0; c++,d--){
						nextToken = (*b)[c][d];
						if (token == nextToken){
							connectedTokens++;
							if (connectedTokens==4){
								//If the token = 0, player one won, if its 1, player two won.
								return token;
							}
						}
						else{
							//Blocked by other players token, therefore no connection of 4, move on.
							connectedTokens=0;
							break;
						}
					}
					//Not enough tokens connected in this direction, reset the counter.
					connectedTokens = 0;
				}
				//Down left check
				if (i >= 3 && j<=3){
					for (int c=i, d=j; c>=0 && j<BOARD_COLS; c--, j++){
						nextToken = (*b)[c][d];
						if (token == nextToken){
							connectedTokens++;
							if (connectedTokens==4){
								//If the token = 0, player one won, if its 1, player two won.
								return token;
							}
						}
						else{
							//Blocked by other players token, therefore no connection of 4, move on.
							connectedTokens=0;
							break;
						}
					}
					//Not enough tokens connected in this direction, reset the counter.
					connectedTokens = 0;
				}
				//Down right check
				if (i <= 3 && j<=3){
					for (int c=i, d=j; c<BOARD_ROWS && j<BOARD_COLS; c++, d++){
						nextToken = (*b)[c][d];
						if (token == nextToken){
							connectedTokens++;
							if (connectedTokens==4){
								//If the token = 0, player one won, if its 1, player two won.
								return token;
							}
						}
						else{
							//Blocked by other players token, therefore no connection of 4, move on.
							connectedTokens=0;
							break;
						}
					}
					//Not enough tokens connected in this direction, reset the counter.
					connectedTokens = 0;
				}
			}
		}
	}
	//No winners
	return -1;
}

int checkTie(int (*b)[BOARD_ROWS][BOARD_COLS]){
	int isBoardFull = 1;
	for (int i=0; i<BOARD_ROWS; i++){
		for (int j=0; j<BOARD_COLS; j++){
			if ((*b)[i][j] == -1){
				isBoardFull = 0;
				break;
			}
		}
	}
	if (checkWinner(b) && isBoardFull == 1){
		//Tie
		return 1;
	}
	else{
		//Not a tie.
		return 0;
	}
}

int main() {
	const char ALPHABET[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
	int startChoice;
	int playingBoard[BOARD_ROWS][BOARD_COLS];
	int (*playingBoardPtr)[BOARD_ROWS][BOARD_COLS] = &playingBoard;
	char playableCols[BOARD_COLS];
	for (int i=0; i<=BOARD_COLS; i++){
		playableCols[i] = ALPHABET[i];
	}
	int turn=0;
	char *playerOne;
	char *playerTwo;
	//COMMENT THIS TO DEBUG
	clear_screen();
	while (1){
		clear_screen();
		playerOne = malloc(sizeof(char));
		playerTwo = malloc(sizeof(char));
		printf("Choose an option:\n");
		printf("1. Play a new game\n");
		printf("2. Load saved game\n");
		printf("3. Exit the game\n");
		// This %*c is necessary. Otherwise the scanf makes getchar in getUserInput get skipped.
		// No idea...
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
			int winner;
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
							winner = checkWinner(playingBoardPtr);
							if (winner != -1){
								if (winner == 0){
									printf("%s won!\n", playerOne);
								}
								else if (winner == 1){
									printf("%s won!\n", playerTwo);
								}
								printf("Press any key to continue...\n");
								getchar();
								free(playerOne);
								free(playerTwo);
								break;
							}
							else if (checkTie(playingBoardPtr) == 1){
								printf("It's a tie!\n");
								printf("Press any key to continue...\n");
								getchar();
								free(playerOne);
								free(playerTwo);
								break;
							}
							//Keep playing
							else{
								turn = 1;
							}
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
							winner = checkWinner(playingBoardPtr);
							if (winner != -1){
								if (winner == 0){
									printf("%s won!\n", playerOne);
								}
								else if (winner == 1){
									printf("%s won!\n", playerTwo);
								}
								printf("Press any key to continue...\n");
								getchar();
								free(playerOne);
								free(playerTwo);
								break;
							}
							//Keep playing
							else if (checkTie(playingBoardPtr) == 1){
								printf("It's a tie!\n");
								printf("Press any key to continue...\n");
								getchar();
								free(playerOne);
								free(playerTwo);
								break;
							}
							else{
								turn = 0;
							}
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
		}
		else if (startChoice == 2){
			//Implement.
		}
		else if (startChoice == 3){
			printf("Exiting...\n");
			free(playerOne);
			free(playerTwo);
			return 0;
		}
	}
	return 0;
}