#include <stdlib.h>
#ifndef DICTIONARY_H
#define DICTIONARY_H

#define BIG_HASH_SIZE 20000
#define SMALL_HASH_SIZE 100

typedef struct theNode {
  char *key;
  struct theNode *next;
} Node;

char *copystr(const char *);
unsigned hash(const char *s);

Node *lookup(Node **dictionary, int hashSize, const char *key);

Node *insert(Node **dictionary, int hashSize, const char *key);

void freeDictionary(Node **dictionary, int hashSize);

#endif
