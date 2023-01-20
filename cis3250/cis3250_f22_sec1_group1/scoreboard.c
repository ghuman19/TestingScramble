#include "scoreboard.h"

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * It takes a pointer to the head of a linked list of users and a string, and
 * returns a pointer to the user with the given name
 *
 * @param head the head of the linked list
 * @param nameToFind The name of the user you want to find.
 *
 * @return A pointer to the user with the name nameToFind.
 */
User *getUserWithName(User *head, char *nameToFind) {
  if (head == NULL) {
    return head;
  }
  User *current = head;
  while (current != NULL) {
    if (strcmp(current->name, nameToFind) == 0) {
      return current;
    }
    current = (current)->next;
  }
  return NULL;
}

/**
 * This function initializes the head of the linked list.
 *
 * @param head the head of the linked list
 */
User *initializeHead(User *head) {
  head = (User *)calloc(1, sizeof(User));
  strcpy(head->name, "\0");
  head->highScore = 0;
  head->totalGames = 0;
  head->totalScore = 0;
  head->next = NULL;
  return head;
}

/**
 * Frees all the memory allocated to the linked list.
 *
 * @param head the head of the linked list
 */
void freeAll(User *head) {
  if (head->next == NULL) {
    free(head);
  } else {
    User *current = head->next;
    User *previous = head;
    while (current != NULL) {
      free(previous);
      previous = current;
      current = (current)->next;
    }
  }
}

/**
 * It returns the user at the given index.
 *
 * @param head The head of the linked list
 * @param index the index of the user you want to get
 * @return The user at the given index.
 */
User *getUserAtIndex(User *head, int index) {
  if (head == NULL) {
    return NULL;
  }
  User *current = head;
  int count = 0;
  while (current != NULL) {
    if (count == index + 1) {
      return current;
    }
    current = (current)->next;
    count++;
  }
  return NULL;
}

/**
 * It returns the index of the user with the name nameToFind.
 *
 * @param head The head of the linked list
 * @param nameToFind The name of the user you want to find.
 * @return The index of the user with the name that is passed in.
 */
int getIndexOfUserWithName(User *head, char *nameToFind) {
  if (head == NULL && head->name != nameToFind) {
    return -1;
  }
  User *current = head;
  int count = 0;
  while (current != NULL) {
    if (strcmp(current->name, nameToFind)) {
      return count;
    }
    current = (current)->next;
    count++;
  }
  return -1;
}

/**
 * Given a list of users, return 1 if the user with the given name is in the
 * list, otherwise return 0.
 *
 * @param head the head of the linked list
 * @param nameToFind The name of the user you want to find.
 * @return 1 if the user with the given name is in the list, otherwise 0
 */
int userIsInList(User *head, char *nameToFind) {
  User *current = head;
  while (current != NULL) {
    if (strcmp(current->name, nameToFind) == 0) {
      return 1;
    }
    current = current->next;
  }
  return 0;
}

/**
 * Returns the length of the linked list.
 *
 * @param head the head of the linked list
 * @return The length of the linked list.
 */
int getLength(User *head) {
  int listLength = 0;
  User *current = head;
  while (current != NULL) {
    listLength++;
    current = current->next;
  }
  return listLength;
}

/**
 * It returns the last node in the linked list.
 *
 * @param head The head of the linked list.
 * @return The last node in the linked list.
 */
User *getLastNode(User *head) {
  if (head == NULL) {
    return head;
  }
  User *current = head;
  while (current != NULL) {
    if (current->next == NULL) {
      return current;
    }
    current = (current)->next;
  }
  return NULL;
}

/**
 * Prints the user list as an array of structs
 *
 * @param head The head of the linked list.
 * @return A pointer to the head of the list.
 */
void printUserListAsArray(User *head) {
  int count = 0;
  if (head == NULL) {
    printf("NULL\n");
    return;
  }

  printf("{");

  while (head != NULL) {
    if (count != 0){
      printf(", ");
    }
    printf("{");
    printf("%s, %d, %d, %d", head->name, head->totalGames, head->totalScore, head->highScore);
    printf("}");
    head = head->next;
    count++;
  }

  printf("}\n");
}

/**
 * It prints the boggle scoreboard
 *
 * @param head The head of the linked list.
 */
void printScoreboard(User *head) {
  if (head == NULL) {
    return;
  }

  User *current = head;

  fprintf(stdout, "\n");
  fprintf(stdout, "---- SCORE BOARD ---- \n");
  if (head != NULL) {
    while (current != NULL) {
      printf("\n");
      printf("Player name: %s \n", current->name);
      printf("High score: %d \n", current->highScore);
      printf("Games played: %d \n", current->totalGames);
      printf("Total score: %d \n", current->totalScore);
      printf("\n");
      printf("--------------------- \n");

      if (current->next == NULL) {
        break;
      }
      current = (current)->next;
    }
  }
}

/**
 * It adds a new node to the linked list
 *
 * @param head the head of the linked list
 * @param name The name of the user
 * @param highScore The score of the user
 */
void addNode(User *head, char *name, int highScore) {
  User *user_ptr;
  if (head != NULL) {
    user_ptr = calloc(1, sizeof(User));
  }
  strcpy(user_ptr->name, name);
  user_ptr->highScore = highScore;
  user_ptr->totalGames = 1;
  user_ptr->totalScore = highScore;
  user_ptr->next = NULL;

  if (head == NULL) {
    head = user_ptr;
  } else {
    getLastNode(head)->next = user_ptr;
  }
}

/**
 * It updates the user's max score, total games, and total score.
 *
 * @param head a pointer to the head of the linked list
 * @param name the name of the user
 * @param current_score the score the user got in the current game
 */
void updateNodeWithName(User *head, char *name, int current_score) {
  if (userIsInList(head, name) == 1) {
    User *user_ptr = getUserWithName(head, name);
    if (current_score > (user_ptr->highScore)) {
      user_ptr->highScore = current_score;
    }
    user_ptr->totalGames += 1;
    user_ptr->totalScore += current_score;
  }
}

/**
 * It opens a file, writes the name, total games, total score, and high score of each user in the
 * linked list to the file, and then closes the file
 *
 * @param filename The name of the file to save the users to.
 * @param head The head of the linked list of users.
 * @return a pointer to the head of the linked list.
 */
void saveUsersToFile(const char *filename, User *head) {
  FILE *userFile = fopen(filename, "w+");

  if (head == NULL) {
    return;
  }

  while (head != NULL) {
    fprintf(userFile, "%s %d %d %d\n", head->name, head->totalGames, head->totalScore, head->highScore);
    head = head->next;
  }
  fclose(userFile);
}

/**
 * It reads the user file and creates a linked list of users
 *
 * @param filename The name of the file to load the users from.
 * @param head The head of the linked list.
 * @return A pointer to the head of the linked list.
 */
User *loadUsersFromFile(const char *filename, User *head) {
  FILE *userFile = fopen(filename, "r");
  char tempName[100], fileBuffer[10000];
  int tempTotalGames, tempTotalScore, tempHighScore;
  int scanReturnVal;

  if (userFile == NULL) {
    return NULL;
  }

  while (fgets(fileBuffer, 10000, userFile)) {
    scanReturnVal = sscanf(fileBuffer, "%s %d %d %d", tempName, &tempTotalGames, &tempTotalScore, &tempHighScore);

    if (scanReturnVal != 4) {
      continue;  // Break loop if read doesn't read enough values
    }
    if (head == NULL) {
      head = initializeHead(head);
    } else {
      addNode(head, "", 0);
    }

    getLastNode(head)->highScore = tempHighScore;
    getLastNode(head)->totalGames = tempTotalGames;
    getLastNode(head)->totalScore = tempTotalScore;

    strcpy(getLastNode(head)->name, tempName);
  }
  fclose(userFile);
  return head;
}

/**
 * Looking through the linked list, the function gathers the highest scoring player in each section and prints out the information.
 *
 * @param head The start of the linked list that must be traversed
 *
 */

void printTops(User **head) {
  // highest single score
  User *dummy = *head;

  User *best = NULL;
  int high = 0;

  while (dummy != NULL) {
    if (dummy->highScore > high) {
      best = dummy;
      high = dummy->highScore;
    }

    dummy = dummy->next;
  }
  // print highest
  printf("Highest single score achieved: \n");
  printf("%s achived a score of %d!\n\n", best->name, high);

  best = NULL;
  dummy = *head;
  high = 0;
  // most games played
  while (dummy != NULL) {
    if (dummy->totalGames > high) {
      best = dummy;
      high = dummy->totalGames;
    }

    dummy = dummy->next;
  }
  printf("Most games played by a single player: \n");
  printf("%s played %d games!\n\n", best->name, high);

  best = NULL;
  dummy = *head;
  high = 0;
  // highest overall score
  while (dummy != NULL) {
    if (dummy->totalScore > high) {
      best = dummy;
      high = dummy->totalScore;
    }

    dummy = dummy->next;
  }
  printf("Highest overall score achieved: \n");
  printf("%s achived scores totalling %d!\n\n", best->name, high);

  printf("Press Enter to return to main menu!");
}
