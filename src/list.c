#include <list.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *my_strdup(const char *str) {
  size_t l = strlen(str);
  char *dup = malloc(l + 1);
  if (dup == NULL)
    return NULL;
  strncpy(dup, str, l);
  return dup;
}

static Node *head = NULL;

Node *add_item(const char *word) {
  Node *new = malloc(sizeof(Node));
  if (new == NULL)
    return NULL;

  if (head == NULL) {
    new->word = my_strdup(word);
    new->count = 1;
    new->next = NULL;
    head = new;
  } else {
    new->word = my_strdup(word);
    new->count = 1;
    new->next = head;
    head = new;
  }
  return new;
}

Node *lookup(char *word) {
  Node *current = head;

  while (current != NULL) {
    if (strncmp(current->word, word, SIZE) == 0)
      return current;
    current = current->next;
  }
  return NULL;
}

Node *get_head(void) { return head; }

int len_of_list(void) {
  int counter = 0;
  for (Node *cur = head; cur != NULL; cur = cur->next)
    counter++;
  return counter;
}

Node *swap(Node *p1, Node *p2) {
  Node *temp = p2->next;
  p2->next = p1;
  p1->next = temp;
  return p2;
}

void sort_list(void) {
  Node **h;
  int len = len_of_list();

  for (int i = 0; i <= len; i++) {
    h = &head;
    for (int j = 0; j < len - i - 1; j++) {
      Node *p1 = *h;
      Node *p2 = p1->next;
      if (p1->count < p2->count)
        *h = swap(p1, p2);

      h = (Node **)&(*h)->next;
    }
  }
}

void cleanlist() {
  Node *current = head;

  while (head != NULL) {
    head = current->next;
    free(current->word);
    free(current);
    current = head;
  }
}
