#include <stdio.h>
#include <stdlib.h>

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

int main () {
	int startChoice = 1;
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
		printf("%s, %s\n", playerOne, playerTwo);
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