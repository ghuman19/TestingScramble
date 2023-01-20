/*
 * Testing loadUsersFromFile from scoreboard.c
 */

#include <string.h>

#include "scoreboard.h"

// To run, use:
// make clean && make test && ./test

#define NORMAL "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW  "\x1B[33m"

typedef struct TestSummary {
  int failCount;
  int passCount;
} TestSummary;

/**
 * Returns a string that is either green or red, depending on the value of the parameter
 *
 * @param checkValue The value to check.
 * @return A pointer to a string.
 */
char *trueFalseColouredString(int checkValue) {
  if (checkValue == 1) {
    return GREEN "True" NORMAL;
  } else {
    return RED "False" NORMAL;
  }
}

/**
 * Prints out the test number, the result of the test, and increments the pass (1) or fail (0) count
 *
 * @param testResult This is the result of the test. It should be either 1 or 0.
 * @param summary A pointer to a TestSummary struct.
 */
void handleTestResult(int testResult, TestSummary *summary) {
  int testNumber = summary->failCount + summary->passCount + 1;

  printf("\tTest Number %d results: ", testNumber);
  if (testResult == 1) {
    printf("%sTest Passed%s\n", GREEN, NORMAL);
    summary->passCount++;
  } else if (testResult == 0) {
    printf("%sTest Failed%s\n", RED, NORMAL);
    summary->failCount++;
  }
  printf("\n");
}

/**
 * Tests that the function returns NULL if the file does not exist
 *
 * @return A pointer to the head of the linked list of users.
 */
int TEST_fileDNE() {
  User *head = NULL;
  head = loadUsersFromFile("testingFiles/nonexistantFile.txt", head);
  printf("Test 1: Returns Null if file does not exist\n");
  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\thead == NULL: %s\n", trueFalseColouredString(head == NULL));
  return (head == NULL);
}

/**
 * Tests that the function returns NULL if the file is empty
 *
 * @return The number of tests that passed.
 */
int TEST_fileEmpty() {
  User *head = NULL;
  head = loadUsersFromFile("testingFiles/emptyfile.txt", head);
  printf("Test 2: Returns Null if file empty\n");
  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\tgetLength(head) == 0: %s\n", trueFalseColouredString(getLength(head) == 0));
  return (getLength(head) == 0);
}

/**
 * Tests that the program ignores users with invalid name lengths
 *
 * @return The number of users in the list.
 */
int TEST_checkUserNameLength() {
  User *head = NULL;
  head = loadUsersFromFile("testingFiles/nametoolong.txt", head);
  printf("Test 3: Loads 2 users with valid length usernames, ignores user with invalid name length\n");
  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\tgetLength(head) == 2: %s\n", trueFalseColouredString(getLength(head) == 2));
  return (getLength(head) == 2);
}

/**
 * Tests that the function `loadUsersFromFile` only loads users with 3 numbers, not less
 *
 * @return The number of users in the list.
 */
int TEST_notEnoughNumbersInFile() {
  User *head = NULL;
  head = loadUsersFromFile("testingFiles/notenoughnumbers.txt", head);
  printf("Test 4: Only loads users with 3 numbers, not less\n");
  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\tgetLength(head) == 2: %s\n", trueFalseColouredString(getLength(head) == 2));
  return (getLength(head) == 2);
}

/**
 * Tests that the function only loads the first 3 numbers of a line, and ignores the rest of the line
 *
 * @return The number of tests that passed.
 */
int TEST_tooManyNumbersInFile() {
  User *head = NULL;
  head = loadUsersFromFile("testingFiles/toomanynumbers.txt", head);
  printf("Test 5: Only loads first 3 numbers of users, ignores rest of line\n");
  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\tgetLength(head) == 3: %s\n", trueFalseColouredString(getLength(head) == 3));
  return (getLength(head) == 3);
}

/**
 * Tests that the program skips empty lines at the start of the file, and reads the first user after
 *
 * @return The number of users in the list.
 */
int TEST_emptyLineAtStart() {
  User *head = NULL;
  head = loadUsersFromFile("testingFiles/emptylineatstart.txt", head);
  printf("Test 6: Skips empty line at start of file, and reads 1 user after\n");
  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\tgetLength(head) == 1: %s\n", trueFalseColouredString(getLength(head) == 1));
  return (getLength(head) == 1);
}

/**
 * Tests that the program can read a file with an empty line in the middle of it
 *
 * @return The number of users in the list.
 */
int TEST_emptyLineInMiddle() {
  User *head = NULL;
  head = loadUsersFromFile("testingFiles/emptylineinmiddle.txt", head);
  printf("Test 7: Reads 1 user, skips empty line, and reads 1 user after\n");
  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\tgetLength(head) == 2: %s\n", trueFalseColouredString(getLength(head) == 2));
  return (getLength(head) == 2);
}

/**
 * Tests that the program can load a file with one user, then an empty line
 *
 * @return The number of users in the list.
 */
int TEST_emptyLineAtEnd() {
  User *head = NULL;
  head = loadUsersFromFile("testingFiles/emptylineatend.txt", head);
  printf("Test 8: Reads 1 user, then skips the empty last line\n");
  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\tgetLength(head) == 1: %s\n", trueFalseColouredString(getLength(head) == 1));
  return (getLength(head) == 1);
}

/*STRUCTURED BASIS TESTING*/

/**
 * Tests if the userFile is NULL
 * 
 * @return the value of the userFile variable.
 */
int TEST_userFileNull(){
  User *head = NULL;
  head = loadUsersFromFile("nonexistentfile.txt", head);
  printf("Test 9: Creates User variable that is NULL, checks if we go into if statement\n");

  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\thead == NULL: %s\n", trueFalseColouredString(head == NULL));
  return (head == NULL);
}

/**
 * It creates a FILE variable that isn't NULL, checks if it doesn't go into while loop
 * 
 * @return The return value of the function.
 */
int TEST_checkingWhileStatement(){
  User *head = NULL;
  head = loadUsersFromFile("testingFiles/fgetsemptyfile.txt", head);
  printf("Test 10: Creates User variable that isn't NULL, checks if it doesn't go into while loop\n");

  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\tgetLength(head) == 0: %s\n", trueFalseColouredString(getLength(head) == 0));
  return (getLength(head) == 0);
}

/**
 * It tests the ScanReturnVal if statement in loadUsersFromFile.
 * 
 * @return The length of the linked list
 */
int TEST_checkScanReturnValue(){
  User *head = NULL;
  head = loadUsersFromFile("testingFiles/checkScanReturnVal.txt", head);
  printf("Test 11: File is formatted correctly, therefore if statement for ScanReturnVal is not entered\n");

  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\tgetLength(head) == 2: %s\n", trueFalseColouredString(getLength(head) == 2));
  return (getLength(head) == 2);
}

/**
 * It checks if the head is null
 * 
 * @return The length of the linked list.
 */
int TEST_checkIfHeadisNull(){
  User *temp;

  temp = (User *)calloc(1, sizeof(User));
  strcpy(temp->name, "\0");
  temp->highScore = 0;
  temp->totalGames = 0;
  temp->totalScore = 0;
  temp->next = NULL;

  temp = loadUsersFromFile("testingFiles/checkIfHeadisNull.txt", temp);
  printf("Test 12: This function check's if the head is NULL, doesn't go into if statement if it is\n");

  printf("\tReturned: ");
  printUserListAsArray(temp);
  printf("\tgetLength(temp) == 2: %s\n", trueFalseColouredString(getLength(temp) == 2));
  return (getLength(temp) == 2);
}

int TEST_nominalCase(){
User *head = NULL;
  head = loadUsersFromFile("testingFiles/nominalCase.txt", head);
  printf("Test 13: File is formatted correctly, therefore all conditions are true except first file = NULL if statement\n");

  printf("\tReturned: ");
  printUserListAsArray(head);
  printf("\tgetLength(head) == 2: %s\n", trueFalseColouredString(getLength(head) == 2));
  return (getLength(head) == 2);
}


/**
 * Runs all the tests, and prints out a summary of the results
 *
 * @param argc The number of arguments passed to the program.
 * @param argv The command line arguments.
 * @return The number of tests that failed.
 */
int main(int argc, char const *argv[]) {
  TestSummary summary;
  summary.failCount = 0;
  summary.passCount = 0;

  printf("\n");

  printf("========== Testing %sloadUsersFromFile()%s from %sscoreboard.c%s ============\n\n", YELLOW, NORMAL, YELLOW, NORMAL);

  printf("%sBoundary Analysis Tests%s\n\n", YELLOW, NORMAL);

  handleTestResult(TEST_fileDNE(), &summary);
  handleTestResult(TEST_fileEmpty(), &summary);
  handleTestResult(TEST_checkUserNameLength(), &summary);
  handleTestResult(TEST_notEnoughNumbersInFile(), &summary);
  handleTestResult(TEST_tooManyNumbersInFile(), &summary);
  handleTestResult(TEST_emptyLineAtStart(), &summary);
  handleTestResult(TEST_emptyLineInMiddle(), &summary);
  handleTestResult(TEST_emptyLineAtEnd(), &summary);

  printf("%sStructured Basis Testing%s\n\n", YELLOW, NORMAL);

  handleTestResult(TEST_userFileNull(), &summary);
  handleTestResult(TEST_checkingWhileStatement(), &summary);
  handleTestResult(TEST_checkScanReturnValue(), &summary);
  handleTestResult(TEST_checkIfHeadisNull(), &summary);
  handleTestResult(TEST_nominalCase(), &summary);

  printf("%sData Flow Tests%s\n\n", YELLOW, NORMAL);

  printf("Tests summary:\n");
  printf("\t%s%d tests passed%s\n", GREEN, summary.passCount, NORMAL);
  printf("\t%s%d tests failed%s\n", RED, summary.failCount, NORMAL);
  printf("\t%d tests run\n", summary.passCount + summary.failCount);
  return 0;
}
