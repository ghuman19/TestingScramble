#include "menu.h"

#include <stdbool.h>
#include <stdlib.h>

#include "boardGenerator.h"
#include "dictionary.h"
#include "scoreboard.h"
#include "wordChecker.h"

/**
 * It opens a file, reads it character by character, and prints each character
 * to the screen
 */
void printFile(char *filename) {
  FILE *rulesFile = fopen(filename, "r");

  if (rulesFile == NULL) {
    return;
  }

  char c = fgetc(rulesFile);

  while (c != EOF) {
    putc(c, stdout);
    c = fgetc(rulesFile);
  }

  fclose(rulesFile);
}

/**
 * It reads characters from the standard input stream until it encounters a
 * newline character or the end of the file
 */
void clearInput() {
  char c;
  while ((c = getchar()) != '\n' && c != EOF) {
  }
}

/**
 * It clears the terminal
 */
void clearTerminal() { system("clear"); }

/**
 * It gets a menu selection from the user
 *
 * @return The menu selection
 */
int getMenuSelection() {
  int menuSelection = 0;
  bool optionSelected = false;

  clearTerminal();
  while (!optionSelected) {
    printf(
        "\nSection 1 Group 1 Boggle Main Menu\n\n"
        "1 - Single-Player\n"
        "2 - View Game Rules\n"
        "3 - View Users\n"
        "4 - High Scores\n"
        "5 - Exit\n\n");

    scanf("%d", &menuSelection);
    clearInput();

    if (0 < menuSelection && menuSelection < 6) {
      optionSelected = true;
    } else {
      printf("'%d' was not an option, please enter again", menuSelection);
    }
  }

  return menuSelection;
}