/*------------------------------------------- 
Weaver
System: VS Code on MacOS
Author: Nuha Abougoash
------------------------------------------- */

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// declare new struct to store the word and its parent index
typedef struct {
    char word[81];
    int parentIndex;
} WordNode;

// declare function prototypes
void getWord(int wordLen, char** wordArray, int *maxSize, int numWords);
int getWordLength();
int getNumWords(int *wordLen, int *maxSize, char ***wordArray);
int validWord(char* word, char** wordArray, int numWords);
int validMove(char* word1, char* word2);
void menu(int numWords, int wordLen, int *maxSize, char** wordArray);
void playGame(char** wordArray, int numWords, int wordLen, int *maxSize, char startWord[81], char endWord[81]);
int findSolution(char *startWord, char *endWord, char **wordArray, int numWords, int wordLen, WordNode *solutionArray);

// print introdcution to the game
void displayIntro() {
	printf("Weaver is a game where you try to find a way to get from the starting word to the ending word.\n");
	printf("You can change only one letter at a time, and each word along the way must be a valid word.\n");
	printf("Enjoy!\n\n");

}

int main() {
	srand(1); // srand(time(0))
    char **wordArray;
    int maxSize = 10;

	displayIntro();

	int wordLen = getWordLength(); //declare length of words by calling getWordLength function
	int numWords = getNumWords(&wordLen, &maxSize,  &wordArray); //declare number of words by calling getNumWords function

	printf("Number of %d-letter words found: %d.\n\n", wordLen, numWords); //print number of words found based on users choice of length
	getWord(wordLen, wordArray, &maxSize, numWords); //play game

	return 0;
}

// prompts user to input the length of the words to use and returns the input value
int getWordLength(){
    int wordLen;
	do {
        printf("How many letters do you want to have in the words? ");
        scanf("%d", &wordLen);
    } while (wordLen <= 0); // while word length is greater than 0
	
    return wordLen;
}

// reads words.txt file and TODO returns size of dynamic array
int getNumWords(int *wordLen, int *maxSize, char ***wordArray) {
    // opens the file
    char filename[] = "words.txt";
    FILE *filePtr  = fopen(filename, "r"); // "r" means we open the file for reading
    
    // check that the file was able to be opened
    if(filePtr == NULL) {
        printf("Error: could not open %s for reading\n", filename);
        exit(-1);
    }

    // allocate dynamic memory  space for the initial array
    *wordArray = malloc(sizeof(char*)*(*maxSize));
    for (int i=0; i < *maxSize; i++){
        (*wordArray)[i] = malloc(sizeof(char) * (*wordLen + 1));
    }

    // read each word from file, and print them one by one
    char index[ 81];
    int numWords = 0;

    while (fscanf(filePtr, "%s", index) != EOF) {
        int input = strlen(index);
        // check if length of word matches wordLen
        if (input == *wordLen) {
            // check if there is enough space to store word
            if (numWords == *maxSize) {
                // double size of array and copy contents of old array into new
                char ** newArray = malloc(sizeof(char*)*(*maxSize*2));
                for (int i=0; i< *maxSize * 2;i++) {
                    newArray[i] = malloc(sizeof(char)* ( * wordLen + 1));
                }
                // copy contents into new array
                for (int j = 0; j < *maxSize; j++){
                    strcpy(newArray[j], (*wordArray)[j]);
                    free((*wordArray)[j]);
                }
                // free memory of old array
                free(*wordArray);
                (*wordArray) = newArray;
                *maxSize *= 2; 
            }
            strcpy((*wordArray)[numWords], index);
            numWords++; // counts number of words in array
        }
    }
    // close the file and return size of array
    fclose(filePtr);
    return numWords;
}

// checks if given word is in the dictionary by loooping through wordArray and returns true if it is, false otherwise
int validWord(char* word, char** wordArray, int numWords) {
    for (int i = 0; i < numWords; i++) {
        // compare input to each word in array
        if (strcmp(word, wordArray[i]) == 0) {
            return 1;
        }
    }
    return 0;
}

// checks if two given words differ by exactly one letter and return true if thye, false if they don't
int validMove(char* word1, char* word2) {
    int count = 0;
    for (int i = 0; i < strlen(word1); i++) { //loop thru each char in word1
        if (word1[i] != word2[i]) { //increment each time a char is diff
            count++;
        }
    }
    if (count == 1) {
        return 1;
    }
    
    return 0;
}

// This function displays the 3 menu options and proceeds based off users input
void menu(int numWords, int wordLen, int *maxSize, char** wordArray) {
	int option = 0;

    // loop for 3 menu options
	while (true) { 
        // display menu options
	    printf("\nEnter: \t1 to play again,\n");
        printf("\t2 to change the number of letters in the words and then play again, or\n");
        printf("\t3 to exit the program.\n");
        printf("Your choice --> ");
        scanf("%d", &option);

        // if user chooses 1, get new starting and ending words
		if (option == 1) {
	
            getWord(wordLen, wordArray, maxSize, numWords);  // get new starting/ ending words from user
        }

		// If the user selects 2, take their input for new wordLen as well as starting and ending words.
		else if (option == 2)  {
            int wordLen = getWordLength(); // get new word lenth from user
            int numWords = getNumWords(&wordLen, maxSize, &wordArray);
            
            printf("Number of %d-letter words found: %d.\n\n", wordLen, numWords);
            getWord(wordLen, wordArray, maxSize, numWords); // get new starting/ ending words from user
		}
		
		// If the user selects 3, the program stops executing.
		else if (option == 3) {
            printf("\n");
            printf("Thanks for playing!\n");
            printf("Exiting...\n");
            exit(0); // exit out of game
        }
    }
}

// Updated playGame function
void playGame(char** wordArray, int numWords, int wordLen, int *maxSize, char startWord[81], char endWord[81]) {
    // Add a new solutionArray to store the solution path
    WordNode *solutionArray = malloc(sizeof(WordNode) * numWords);

    // Call findSolution to get the solution path
    int solutionLen = findSolution(startWord, endWord, wordArray, numWords, wordLen, solutionArray);

    // If solutionLen is -1, then no solution exists
    if (solutionLen == -1) {
        printf("No solution found from '%s' to '%s'.\n", startWord, endWord);
    } else {
        printf("Solution found from '%s' to '%s' in %d moves:\n", startWord, endWord, solutionLen - 1);
        for (int i = 0; i < solutionLen; i++) {
            printf("%d. %s\n", i + 1, solutionArray[i].word);
        }
    }

    // Free the allocated memory for solutionArray
    free(solutionArray);

    // Call menu function
    menu(numWords, wordLen, maxSize, wordArray);
}

// this function prompts user to input starting and ending word or 'r' for a random word
// it checks if the inputted words are valid and continues prompting user until word is valid, then playGame function is called
void getWord(int wordLen, char** wordArray, int *maxSize, int numWords) {
    bool valid = false;
    char startWord[81]; // allocate memory for startWord
    char endWord[81]; // allocate memory for endWord
    
    while(!valid) {

        printf("Enter starting and ending words, or 'r' for either for a random word: ");
        scanf("%s %s", startWord, endWord); // take user input for starting/ending words
        
        if (strcmp(startWord, "r") == 0 ) { 
            // set start and end equal to a rand word
            int index = rand() % numWords;
            strcpy(startWord, wordArray[index]);
        }

        // check if ending word is r, then give a random ending word
        if (strcmp(endWord, "r") == 0) {
            // set start and end equal to a rand word
            int index = rand() % numWords;
            strcpy(endWord, wordArray[index]);
        }

        // check if startWord is the correct length
        if (strlen(startWord) != wordLen ) {
            printf("Your word, '%s', is not a %d-letter word. Try again.\n", startWord, wordLen);
            continue; // start loop again if error occured
        }
        // check if endWord is the correct length
        else if ( strlen(endWord) != wordLen) {
            printf("Your word, '%s', is not a %d-letter word. Try again.\n", endWord, wordLen);
            continue;
        }
        // check if startWord is in the wordArray 
        else if (!validWord(startWord, wordArray, numWords)) {
            printf("Your word, '%s', is not a valid dictionary word. Try again.\n", startWord);
            continue;
        }
        // check if endWord is in the wordArray
        else if (!validWord(endWord, wordArray,  numWords)) {
            printf("Your word, '%s', is not a valid dictionary word. Try again.\n", endWord);
            continue;
        }
        
        valid = true; // if none of these erros occured, then valid is true
        
    } 

    printf("Your starting word is: %s.\n", startWord);
    printf("Your ending word is: %s.\n\n", endWord);

    // call play game function once starting and ending words are valid 
    playGame(wordArray, numWords, wordLen, maxSize, startWord, endWord); 

}
