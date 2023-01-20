#include "wordChecker.h"

#include <ctype.h>
#include <stdio.h>
#include <string.h>

/**
 * Gets the character at the given position from gameBoard
 *
 * @param i the row of the gameBoard
 * @param j the column of the board
 * @param gameBoard the game board
 *
 * @return The character at the given position.
 */
char getLetter(int i, int j, struct rolledDice** gameBoard) { return gameBoard[i][j].character; }

/**
 * Checks if the word passed in as a parameter is a valid word on the game board
 *
 * @param i the x coordinate of the current cell
 * @param j the y coordinate of the current cell
 * @param word the word we're trying to find
 * @param gameBoard the game board
 * @param subLen the length of the substring of the word that we've already
 * found
 * @param visited a 2D array that keeps track of which cells have been visited.
 *
 * @return a boolean value.
 */
int abidesRules(int i, int j, char* word, struct rolledDice** gameBoard, int subLen, int** visited) {
  int adjCell;

  if (subLen == (strlen(word) - 1)) {
    return 1;
  }

  // right, digUpRight, up, digUpLeft, left, digDownLeft, down, digDownRight
  int allX[] = {0, -1, -1, -1, 0, 1, 1, 1};
  int allY[] = {1, 1, 0, -1, -1, -1, 0, 1};

  int newX;
  int newY;

  char findLetter;
  findLetter = word[subLen + 1];
  int result = 0;

  for (adjCell = 0; adjCell < 8; adjCell++) {
    newX = i + allX[adjCell];
    newY = j + allY[adjCell];
    if ((newX >= 0) && (newX < 4) && (newY >= 0) && (newY < 4) && toupper(findLetter) == getLetter(newX, newY, gameBoard) && !visited[newX][newY]) {
      visited[newX][newY] = 1;
      ++subLen;
      result = abidesRules(newX, newY, word, gameBoard, subLen, visited);
      if (result) {
        return 1;
      } else {
        --subLen;
      }
    }
  }

  return 0;
}

/**
 * Checks if a word is on the board
 *
 * @param gameBoard the game board
 * @param word the word to be checked
 * @return a boolean value.
 */
int wordChecker(struct rolledDice** gameBoard, char* word) {
  int row, col, m, n;
  int** visited;
  visited = malloc(sizeof(int*) * 4);

  visited[0] = malloc(sizeof(int) * 4);
  visited[1] = malloc(sizeof(int) * 4);
  visited[2] = malloc(sizeof(int) * 4);
  visited[3] = malloc(sizeof(int) * 4);

  for (m = 0; m < 4; m++) {
    for (n = 0; n < 4; n++) {
      if (m == 0 && n == 0) {
        visited[m][n] = 1;
      } else {
        visited[m][n] = 0;
      }
    }
  }

  for (row = 0; row < 4; row++) {
    for (col = 0; col < 4; col++) {
      if (abidesRules(row, col, word, gameBoard, 0, visited)) {
        free(visited[0]);
        free(visited[1]);
        free(visited[2]);
        free(visited[3]);
        return 1;
      }
    }
  }

  free(visited[0]);
  free(visited[1]);
  free(visited[2]);
  free(visited[3]);

  return 0;
}

// int getwordCount(FILE* Dictionary, struct rolledDice **GameBoard){
//       char tempWord[100];
//       int wordNum=0;
//       int count=0;
//       fseek(Dictionary, 0, SEEK_SET);
//       for (int i =0;i>=235886; i++){
//         fgets(tempWord,100,Dictionary);
//         count+=1;
//         if (wordChecker(GameBoard, tempWord)){
//           wordNum+=1;
//         }
//         if (count%1000==0){
//           printf("%d == %s\n", count, tempWord);
//         }
//       }

//       return wordNum;

// }
