#include "boardGenerator.h"

/**
 * Initializes the dice in the list of pre-set dice. Call once at program start.
 *
 * @param inputArrayOfDice the array of presetDice structs that we want to
 * initialize
 */
void initializePresetDice(struct presetDice* inputArrayOfDice) {
  for (int i = 0; i < 16; i++) {
    inputArrayOfDice[i].position = 0;
  }

  // initializes individual potential chars for each dice
  inputArrayOfDice[0].configurations = "RIFOBX";
  inputArrayOfDice[1].configurations = "IFEHEY";
  inputArrayOfDice[2].configurations = "DENOWS";
  inputArrayOfDice[3].configurations = "UTOKND";
  inputArrayOfDice[4].configurations = "HMSRAO";
  inputArrayOfDice[5].configurations = "LUPETS";
  inputArrayOfDice[6].configurations = "ACITOA";
  inputArrayOfDice[7].configurations = "YLGKUE";
  inputArrayOfDice[8].configurations = "QBMJOA";
  inputArrayOfDice[9].configurations = "EHISPN";
  inputArrayOfDice[10].configurations = "VETIGN";
  inputArrayOfDice[11].configurations = "BALIYT";
  inputArrayOfDice[12].configurations = "EZAVND";
  inputArrayOfDice[13].configurations = "RALESC";
  inputArrayOfDice[14].configurations = "UWILRG";
  inputArrayOfDice[15].configurations = "PACEMD";
}

/**
 * This function rolls the dice, but does not shuffle them
 *
 * @param gameDice This is the array of structs that holds the dice
 * @param inputArrayOfDice This is the array of dice that we're going to roll.
 */
void rollButNotShuffleDice(struct rolledDice* gameDice, struct presetDice* inputArrayOfDice) {
  srand(time(NULL));
  for (int i = 0; i < 16; i++) {
    int r = rand() % 6;
    gameDice[i].character = inputArrayOfDice[i].configurations[r];
  }
}

/**
 * It takes a struct array of rolledDice and shuffles the positions of the dice
 *
 * @param gameDice This is the array of structs that contains the dice.
 */
void shuffleRolledDicePositions(struct rolledDice* gameDice) {
  struct rolledDice newGameDice[16];

  int r = 0;
  for (int i = 0; i < 16; i++) {
    srand(time(NULL));
    // this is somewhat inefficient. Using it for now.
    while (gameDice[r].position == -1) {
      r = (int)(rand() % 16);
    }
    newGameDice[i] = gameDice[r];
    gameDice[r].position = -1;
  }

  for (int i = 0; i < 16; i++) {
    gameDice[i] = newGameDice[i];
    gameDice[i].position = i + 1;
  }
}

/**
 * Rolls the dice to be used at the start of the game and shuffles them, putting
 * the dice into the 2D array gameDice. Call once at the start of every game.
 *
 * @param gameBoard a 2D array of structs that will be filled with the rolled
 * dice.
 * @param inputArrayOfDice This is the array of dice that the user has inputted.
 */
void rollDice(struct rolledDice** gameBoard, struct presetDice* inputArrayOfDice) {
  gameBoard[0] = malloc(sizeof(struct rolledDice) * 4);
  gameBoard[1] = malloc(sizeof(struct rolledDice) * 4);
  gameBoard[2] = malloc(sizeof(struct rolledDice) * 4);
  gameBoard[3] = malloc(sizeof(struct rolledDice) * 4);

  // temporary array of structs to contain adjusted 1D array of dice.
  struct rolledDice adjustedDiceArray[16];

  rollButNotShuffleDice(adjustedDiceArray, inputArrayOfDice);
  shuffleRolledDicePositions(adjustedDiceArray);

  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      gameBoard[i][j] = adjustedDiceArray[i * 4 + j];
    }
  }
}

/**
 * This function prints the game board
 *
 * @param gameBoard This is the game board that we are printing.
 */
void printGameBoard(struct rolledDice** gameBoard) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (j != 3) {
        printf("%c \t", gameBoard[i][j].character);
      } else {
        printf("%c \n", gameBoard[i][j].character);
      }
    }
  }
}

/**
 * It takes a string of 16 characters and converts it into a 2D array of 4x4
 *
 * @param letters a string of 16 characters, each of which is either a letter or a 'Q'
 * @param board a pointer to a pointer to a char. This is a pointer to a 2D array of chars.
 */
void convertToBoard(char* letters, char*** board) {
  // allocate space for boggle board on heap in order to access it in main.
  int i, j, t = 0;

  *board = malloc(sizeof(char*) * 4);
  char** boardDeref = *board;

  boardDeref[0] = malloc(sizeof(char) * 4);
  boardDeref[1] = malloc(sizeof(char) * 4);
  boardDeref[2] = malloc(sizeof(char) * 4);
  boardDeref[3] = malloc(sizeof(char) * 4);

  for (i = 0; i < 4; i++) {
    for (j = 0; j < 4; j++) {
      if (j != 3) {
        boardDeref[i][j] = letters[t];
        t++;

      } else {
        boardDeref[i][j] = letters[t];
        t++;
      }
    }
  }
}
