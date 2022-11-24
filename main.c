#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BOARD_ROWS 6
#define BOARD_COLS 7

#define BUFFER_SIZE 1000

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
			if (b[i][j] == 0){
				charToPrint = ' ';
			}
			else if(b[i][j] == 1){
				charToPrint = 'X';
			}
			else if(b[i][j] == 2){
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
	if ((*b)[0][col] != 0){
		//This column is full, therefore not playable.
		return 0;
	}
	//What.
	for (int i=BOARD_ROWS; i>-1; i--){
		if ((*b)[i][col] == 0){
			if (player == 1){
				//Player one
				(*b)[i][col] = 1;
			}
			else if (player == 2){
				//Player two.
				(*b)[i][col] = 2;
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
			if ((*b)[i][j] == 0){
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
	return 0;
}

int checkTie(int (*b)[BOARD_ROWS][BOARD_COLS]){
	int isBoardFull = 1;
	for (int i=0; i<BOARD_ROWS; i++){
		for (int j=0; j<BOARD_COLS; j++){
			if ((*b)[i][j] == 0){
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

typedef struct Game{
	int gameID;
    char player1[120];
    char player2[120];
    int board[BOARD_ROWS][BOARD_COLS];
} Game;

int charToInt(char c) {
    return c - '0';
}

int randomInt(int lower, int upper){
	srand(time(0));
	return (rand() % (upper - lower + 1)) + lower;
}

int findLineInFile(FILE *file, char *query){
	int lineCount = 0;
	char buffer[BUFFER_SIZE];
	while((fgets(buffer, BUFFER_SIZE, file)) != NULL){
		lineCount++;
		//Getting rid of the new line character so that string compare actually works...
		buffer[strcspn(buffer, "\n")] = 0;
		if(strcmp(query, buffer) == 0){
			return lineCount;
		}
	}
	//Not found.
	return 0;
}

int saveGame(int id, char *playerOne, char *playerTwo, int (*playingBoard)[BOARD_ROWS][BOARD_COLS]){
	FILE *file;
   	file = fopen("saves.txt","a+");
   	if (file == NULL){
   		//Failed to open the saves file.
   		return 0;
   	}
	if (id == 0){
		//New game, just write it down and generate an id for it.
		id = randomInt(1000, 9999);
		fprintf(file, "%d\n", id);
		fprintf(file, "%s\n", playerOne);
		fprintf(file, "%s\n", playerTwo);
		for (int i = 0; i<BOARD_ROWS; i++){
			for (int j = 0; j<BOARD_COLS; j++){
				fprintf(file, "%d", (*playingBoard)[i][j]);
			}
			fprintf(file, "\n");
		}
	}
	else{
		//Find in the file game is saved by id, then overwrite it.
		//The id will have 4 numbers.
		char idStr[4];
		sprintf(idStr, "%d", id);
		int lineWhereId = findLineInFile(file, idStr);
		//Create TMP file.
		FILE *fileTmp;
		fileTmp = fopen("temp.tmp", "w");
		int lineCount = 0;
		int skipLines = 0;
		//For whatever reason, after an fgets, the first line gets skipped.
		//This fixes that.
		fclose(file);
		file = fopen("saves.txt","a+");
		char buffer[BUFFER_SIZE];
		while((fgets(buffer, BUFFER_SIZE, file)) != NULL){
			lineCount++;
			if (lineCount == lineWhereId+3){
				//Start overwriting the board.
				for (int i = 0; i<BOARD_ROWS; i++){
					for (int j = 0; j<BOARD_COLS; j++){
						fprintf(fileTmp, "%d", (*playingBoard)[i][j]);
					}
					fprintf(fileTmp, "\n");
				}
				skipLines = 5;
			}
			else{
				if (skipLines > 0){
					skipLines--;
					continue;
				}
				fputs(buffer, fileTmp);
			}
		}
		fclose(fileTmp);
		fclose(file);
		rename("temp.tmp", "./saves.txt");
	}
	//Success.
	return 1;
}

Game readSavedGame(int id){
	FILE *file;
   	file = fopen("saves.txt","a+");
	char idStr[4];
	//Converting the id to string.
	sprintf(idStr, "%d", id);
	int lineWhereId = findLineInFile(file, idStr);
	Game savedGame;
	savedGame.gameID = id;
	char buffer[BUFFER_SIZE];
	int board[BOARD_ROWS][BOARD_COLS];
	int lineCount = 0;
	int boardRow = 0;
	if (file == NULL){
   		//Failed to open the saves file.
   		//Return an empty game instance.
   		return savedGame;
   	}
	//For whatever reason, after an fgets, the first line gets skipped.
	//This fixes that.
	fclose(file);
	file = fopen("saves.txt","a+");
	while((fgets(buffer, BUFFER_SIZE, file)) != NULL){
		lineCount++;
		if (lineCount == lineWhereId+1){
			memcpy(savedGame.player1, buffer, sizeof savedGame.player1);
		}
		else if(lineCount == lineWhereId+2){
			memcpy(savedGame.player2, buffer, sizeof savedGame.player2);
		}
		//ISSUE WITH -1 WHERE IT READS THE -, THEREFORE THE BOARD IS NOT BUILT PROPERLY
		//Might discard using -1 as an empty space, instead use 0, player 1 is 1, and player 2 is 2.
		else if(lineCount >= lineWhereId+3){
			for (int i=0; i<BOARD_COLS; i++){
				//Converting all the 0's (because they are char) to int.
				//Try and replace this with strtol.
				board[boardRow][i] = charToInt(buffer[i]);
			}
			boardRow++;
			if (boardRow == 6){
				//End of board, break.
				break;
			}
		}
	}
	memcpy(savedGame.board, board, sizeof savedGame.board);
	return savedGame;
}

Game *allSavedGames(){
	Game *games = malloc(sizeof(Game));
	FILE *file;
	char buffer[BUFFER_SIZE];
	int board[BOARD_ROWS][BOARD_COLS];
   	file = fopen("saves.txt","a+");
   	//This keeps track of saved games so that the *games can be reallocated after each loop iteartion.
   	int savedGameNum = 0;
   	int lineCount = 0;
   	int boardRow = 0;
   	char *endChar;
   	if (file == NULL){
   		//Failed to open the saves file.
   		return 0;
   	}
   	while((fgets(buffer, BUFFER_SIZE, file)) != NULL){
   		lineCount++;
   		if(strcmp("\n", buffer) == 0){
   			break;
   		}
   		if (lineCount == 1){
   			//Just do the string to int conversion.
   			games[savedGameNum].gameID = strtol(buffer, &endChar, 10);
   		}
   		else if (lineCount == 2){
   			strcpy(games[savedGameNum].player1, buffer);
   		}
   		else if(lineCount == 3){
   			strcpy(games[savedGameNum].player2, buffer);
   		}
   		else if(lineCount >= 4){
   			for (int i=0; i<BOARD_COLS; i++){
   				//Converting all the 0's (because they are char) to int.
   				//Try and replace this with strtol.
   				board[boardRow][i] = charToInt(buffer[i]);
   			}
   			boardRow++;
   			if (boardRow == 6){
   				boardRow = 0;
   				//We need to reset the line count so we can read the next save if it exists.
   				lineCount = 0;
   				memcpy(games[savedGameNum].board, board, (sizeof games[savedGameNum].board));
   				savedGameNum++;
   				games = (Game*)realloc(games, sizeof(Game) * (savedGameNum+1));
   			}
   		}
   	}
   	//Adding an empty game object with the id of 0 at the end, so we know where the end of pointnr is.
   	games = (Game*)realloc(games, (sizeof(Game) * (savedGameNum+1)));
    Game emptyGame;
    emptyGame.gameID = 0;
    games[savedGameNum] = emptyGame;
   	fclose(file);
	return games;
}

int main() {
	int startChoice;
	int playingBoard[BOARD_ROWS][BOARD_COLS];
	int (*playingBoardPtr)[BOARD_ROWS][BOARD_COLS] = &playingBoard;
	char playableCols[BOARD_COLS] = {'A', 'B', 'C', 'D', 'E', 'F', 'G'};
	int turn=1;
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
			//AKA. Fill it up with zeros.
			memset(playingBoard, 0, sizeof(playingBoard));
			printBoard(playingBoard, playableCols);
			printf("\n");
			char colChoice;
			int winner;
			while (1){
				if (turn == 1){
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
							if (winner != 0){
								if (winner == 1){
									printf("%s won!\n", playerOne);
								}
								else if (winner == 2){
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
								turn = 2;
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
							if (winner != 0){
								if (winner == 1){
									printf("%s won!\n", playerOne);
								}
								else if (winner == 2){
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
								turn = 1;
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