#ifndef SCOREBOARD_H
#define SCOREBOARD_H

#include <stdio.h>
#include <stdlib.h>

typedef struct User {
  char name[100];
  int highScore;
  int totalGames;
  int totalScore;
  struct User* next;

} User;

char* getField(char* line, int num);

User* getUserWithName(User* head, char* nameToFind);

User* getUserAtIndex(User* head, int index);

int getIndexOfUserWithName(User* head, char* nameToFind);

int getLength(User* head);

User* getLastNode(User* head);

void printUserListAsArray(User* head);

void printScoreboard(User* head);

void freeAll(User* head);
void addNode(User* head, char* name, int highScore);

int userIsInList(User* head, char* nameToFind);

void updateNodeWithName(User* head, char* name, int currentScore);

void saveUsersToFile(const char* filename, User* head);

User* loadUsersFromFile(const char* filename, User* head);

void printTops(User** head);

#endif
