#include <stdio.h>
#include <stdlib.h>

typedef struct node {
  char letter;
  struct node *next;
} node;

// Returns the number of nodes in the linkedList.
int length(node *head) {
  int count = 0;
  while (head != NULL) {
    count++;
    head = head->next;
  }
  return count;
}

// Parses the string in the linkedList.
// If the linked list is head -> |a|->|b|->|c|,
// then toCString function will return "abc".
char *toCString(node *head) {
  int len = length(head);
  char *str =
      (char *)malloc((len + 1) * sizeof(char)); // +1 for null terminator
  if (str == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }

  int i = 0;
  while (head != NULL) {
    str[i++] = head->letter;
    head = head->next;
  }
  str[i] = '\0'; // Null-terminate the string
  return str;
}

// Inserts character to the linkedlist at the end.
void insertChar(node **pHead, char c) {
  node *newNode = (node *)malloc(sizeof(node));
  if (newNode == NULL) {
    fprintf(stderr, "Memory allocation failed.\n");
    exit(EXIT_FAILURE);
  }
  newNode->letter = c;
  newNode->next = NULL;

  // If the list is empty, make the new node the head
  if (*pHead == NULL) {
    *pHead = newNode;
  } else {
    // Otherwise, find the last node and append the new node
    node *current = *pHead;
    while (current->next != NULL) {
      current = current->next;
    }
    current->next = newNode;
  }
}

// Deletes all nodes in the linkedList.
void deleteList(node **pHead) {
  while (*pHead != NULL) {
    node *temp = *pHead;
    *pHead = (*pHead)->next;
    free(temp);
  }
}

int main(void) {
  int i, strLen, numInputs;
  node *head = NULL;
  char *str;
  char c;
  FILE *inFile = fopen("input.txt", "r");

  if (inFile == NULL) {
    fprintf(stderr, "Failed to open input.txt\n");
    return EXIT_FAILURE;
  }

  fscanf(inFile, " %d\n", &numInputs);

  while (numInputs-- > 0) {
    fscanf(inFile, " %d\n", &strLen);

    for (i = 0; i < strLen; i++) {
      fscanf(inFile, " %c", &c);
      insertChar(&head, c);
    }

    str = toCString(head);
    printf("String is: %s\n", str);
    free(str);

    deleteList(&head);
    if (head != NULL) {
      fprintf(stderr, "deleteList is not correct!\n");
      break;
    }
  }

  fclose(inFile);

  return 0;
}
