#include "dictionary.h"

#include <stdio.h>
#include <string.h>

/**
 * "Add up the ASCII values of the characters in the string, multiplying each one by 31 before adding
 * it to the total."
 *
 * @param s The string to be hashed.
 * @return The hash value of the string.
 */
unsigned hash(const char *s) {
  unsigned hashVal;
  for (hashVal = 0; *s != '\0'; s++) hashVal = *s + 31 * hashVal;
  return hashVal;
}

/**
 * "Lookup the key in the dictionary, and return the corresponding node, or NULL if not found."
 *
 * The function starts by computing the hash value of the key. Then it searches the linked list at that
 * hash value for the key. If it finds the key, it returns the node. If it doesn't find the key, it
 * returns NULL
 *
 * @param dictionary The hash table.
 * @param hashSize The size of the hash table.
 * @param key The key to look up.
 * @return A pointer to the node with the key that matches the key passed in.
 */
Node *lookup(Node **dictionary, int hashSize, const char *key) {
  Node *np;
  unsigned int hashVal = hash(key);
  for (np = dictionary[hashVal % hashSize]; np != NULL; np = np->next)
    if (strcmp(key, np->key) == 0) return np;
  return NULL;  // not found
}

/**
 * If the key is not already in the dictionary, then allocate a new node, copy the key into it, and
 * insert it into the dictionary
 *
 * @param dictionary the hash table
 * @param hashSize the size of the hash table
 * @param key the key to be inserted
 * @return A pointer to the node that was just inserted.
 */
Node *insert(Node **dictionary, int hashSize, const char *key) {
  unsigned int hashVal;
  Node *np;

  if ((np = lookup(dictionary, hashSize, key)) == NULL) {  //
    np = (Node *)malloc(sizeof(*np));

    if (np == NULL || (np->key = copystr(key)) == NULL) return NULL;

    hashVal = hash(key) % hashSize;

    np->next = dictionary[hashVal];
    dictionary[hashVal] = np;
  }
  return np;
}

/**
 * For each position in the dictionary, if there is an entry at that position, free all the nodes in
 * the linked list at that position
 *
 * @param dictionary the dictionary to free
 * @param hashSize the size of the hash table
 */
void freeDictionary(Node **dictionary, int hashSize) {
  int i;
  for (i = 0; i < hashSize; i++) {
    if (dictionary[i] != NULL) {
      Node *head = dictionary[i];
      Node *current = head;
      while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
      }
      dictionary[i] = NULL;
    }
  }
}

/**
 * copystr() makes a duplicate of the string s and returns a pointer to the duplicate.
 *
 * @param s The string to be copied.
 * @return A pointer to the first character of the string.
 */
char *copystr(const char *s) {
  char *p;
  int len = strlen(s);

  p = (char *)malloc(len + 1); /* +1 for '\0' */
  if (p != NULL) strncpy(p, s, len);
  p[len] = '\0';

  return p;
}
