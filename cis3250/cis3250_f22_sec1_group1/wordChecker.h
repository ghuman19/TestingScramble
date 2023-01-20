#include <stdlib.h>
#include <string.h>

#include "boardGenerator.h"

int wordChecker(struct rolledDice **gameBoard, char *word);
int abidesRules(int i, int j, char *word, struct rolledDice **gameBoard,
                int subLen, int **visited);
char getLetter(int i, int j, struct rolledDice **gameBoard);

// int getwordCount(FILE* Dictionary, struct rolledDice**gameBoard);