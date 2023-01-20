#include <assert.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "boardGenerator.h"
#include "dictionary.h"
#include "menu.h"
#include "scoreboard.h"
#include "wordChecker.h"

#define MAX_LINE 100

/**
 * It frees the memory
 * allocated to the game board, and then re-rolls the dice
 *
 * @param gameBoard a 2D array of structs that holds the dice and their values
 * @param inputArrayOfDice This is the array of preset dice that the user has
 * inputted.
 */
void freeAndResetBoard(struct rolledDice **gameBoard, struct presetDice *inputArrayOfDice) {
  for (int i = 0; i < 4; i++) {
    free(gameBoard[i]);
  }
  rollDice(gameBoard, inputArrayOfDice);
}

/**
 * Convert a string to uppercase.
 *
 * @param upper a pointer to a pointer to a char
 * @return A pointer to the first element of the array.
 */
char *convertToUpper(char (*upper)[]) {
  char *upperDeref = *upper;

  for (int i = 0; upperDeref[i]; i++) {
    upperDeref[i] = toupper(upperDeref[i]);
  }
  return upperDeref;
}

/**
 * Adds to the players score based on the length of the word passed
 *
 * @param userScore the user's current score
 * @param word the word that the user entered
 */
void incrementTotalScore(int *userScore, char *word) {
  int wordLength = strlen(word);
  if (wordLength == 3 || wordLength == 4) {
    *userScore += 1;
  } else if (wordLength == 5) {
    *userScore += 2;
  } else if (wordLength == 6) {
    *userScore += 3;
  } else if (wordLength == 7) {
    *userScore += 5;
  } else if (wordLength >= 8) {
    *userScore += 11;
  }
  printf("\nCorrect! %s's word length is %d, so your current score is now: %d \n", word, wordLength, *userScore);
}

/**
 * Main function of the program. It is the
 * function that is called when the program is run. It is responsible for
 * initializing the game, and running the game.
 *
 * @param argc The number of arguments passed to the program.
 * @param argv an array of strings, each string is a command line argument
 * @return the number of words in the file.
 */
int main(int argc, char **argv) {
  /* Declaring all the variables that will be used in the program. */
  char capInputWord[100];
  char inputWord[100];
  char inputName[100];

  FILE *dictFile;
  char line[MAX_LINE];

  const char *dictFilename = "resourceFiles/EnglishWords.txt";
  const char *userFilename = "resourceFiles/users.txt";
  Node *checkEnglish;
  Node *checkSubmitted;
  static Node *englishDictionary[BIG_HASH_SIZE];
  static Node *guessedWords[SMALL_HASH_SIZE];

  int currentScore = 0;
  int turnCount = 0;

  User *head = NULL;
  head = loadUsersFromFile(userFilename, head);

  PresetDice globalDice[16];
  RolledDice *gameBoard[4];

  // Ensures that the final "free"'s have something to free
  initializePresetDice(globalDice);
  rollDice(gameBoard, globalDice);

  if (!(dictFile = fopen(dictFilename, "r"))) {
    fprintf(stderr, "Could not open file \"%s\" for reading dictionary words\n", dictFilename);
    return 1;
  }

  while (fgets(line, MAX_LINE, dictFile) != NULL) {
    /* Remove the newline character from the end of the line. */
    line[strcspn(line, "\r\n")] = '\0';
    /* Insert the line into the englishDictionary. */
    insert(englishDictionary, BIG_HASH_SIZE, convertToUpper(&line));
  }
  fclose(dictFile);

  bool in_menu = true;
  while (in_menu) {
    switch (getMenuSelection()) {
      /* Play the game. */
      case 1:
        currentScore = 0;
        turnCount = 0;

        printf("What is your username? (case-sensitive)\n");
        scanf("%s", inputName);
        clearInput();

        if (userIsInList(head, inputName)) {
          printf("Welcome back %s\n", inputName);
          currentScore = getUserWithName(head, inputName)->totalScore;
        } else {
          printf("First time %s? We hope you enjoy!\n", inputName);
        }

        printf("Press enter to continue");
        getchar();

        strcpy(inputWord, "");

        initializePresetDice(globalDice);
        rollDice(gameBoard, globalDice);

        while (turnCount >= 0) {
          clearTerminal();

          printGameBoard(gameBoard);

          strcpy(capInputWord, inputWord);

          convertToUpper(&capInputWord);

          checkEnglish = lookup(englishDictionary, BIG_HASH_SIZE, capInputWord);
          checkSubmitted = lookup(guessedWords, SMALL_HASH_SIZE, capInputWord);

          if (capInputWord[0] == 'Q') {
            break;
          } else if (turnCount == 0) {
          } else if (checkEnglish == NULL) {
            printf("\nIncorrect word: \'%s\' is not in the English Dictionary. Try again!\n", inputWord);
            /* This is checking if the word has already been submitted. */
          } else if (checkSubmitted != NULL) {
            printf("\nYou have already submitted the word: \'%s\' Try again!\n", inputWord);
            /* This is checking if the word is at least 3 letters long. */
          } else if (strlen(capInputWord) <= 2) {
            printf("\nThe submitted word: \'%s\' must be at least 3 letters long. Try again!\n", inputWord);
            /* Checking if the word is valid. */
          } else if (wordChecker(gameBoard, capInputWord)) {
            insert(guessedWords, SMALL_HASH_SIZE, capInputWord);
            incrementTotalScore(&currentScore, capInputWord);
          } else {
            printf("\nThe submitted word: \'%s\' does not abide game rules. Try again!\n", inputWord);
          }

          printf("\n%s's current score: %d\n", inputName, currentScore);
          printf("Submit a word you found, or enter q to quit to main menu:\n\n");
          scanf("%s", inputWord);
          clearInput();

          turnCount++;
        }

        if (userIsInList(head, inputName)) {
          updateNodeWithName(head, inputName, currentScore);
        } else {
          addNode(head, inputName, currentScore);
        }

        saveUsersToFile(userFilename, head);

        break;

      /* Printing the game rules to the screen. */
      case 2:
        printFile("resourceFiles/gameRules.txt");
        getchar();
        break;
      /* Printing the high scores to the screen. */
      case 3:
        printFile("resourceFiles/highScores.txt");
        printScoreboard(head);
        getchar();
        break;
      /* Printing the top 5 scores to the screen. */
      case 4:
        printTops(&head);
        getchar();
        break;
      /* Exiting the program. */
      case 5:
        in_menu = false;
        break;

      default:
        break;
    }
  }

  saveUsersToFile(userFilename, head);

  // free memory at the end of the program
  for (int i = 0; i < 4; i++) {
    free(gameBoard[i]);
  }
  freeAll(head);

  freeDictionary(englishDictionary, BIG_HASH_SIZE);
  freeDictionary(guessedWords, SMALL_HASH_SIZE);

  return 0;
}
