#include "colors.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 1024
#define PATH 128
#define DELIM " \n\t"

/* parse string for first word and return it
 * if it is sudo/doas - skip*/
char *parse_string(char *str) {
  if (*str == '\n')
    return NULL;

  char *command = malloc(SIZE);
  if (command == NULL)
    return NULL;

  char *temp = strtok(str, DELIM);
  strncpy(command, temp, SIZE);
  return command;
}

int main(int argc, char *argv[]) {
  char filename[PATH];
  char *buffer = malloc(SIZE);
  if (buffer == NULL)
    return -2;

  sprintf(filename, "%s/.%s_history", getenv("HOME"), "bash");
  FILE *file = fopen(filename, "r");
  if (file == NULL) {
    perror("opening file");
    return -1;
  }

  while (feof(file) == 0) {
    fgets(buffer, SIZE, file);
    if (buffer[0] == '#')
      continue;

    char *temp = parse_string(buffer);
    if (temp == NULL)
      continue;

    Node *item = lookup(temp);
    if (item != NULL)
      item->count++;
    else
      item = add_item(temp);
    free(temp);
  }

  sort_list();
  int total = 0;
  for (Node *cur = get_head(); cur != NULL; cur = cur->next) {
    total += cur->count;
  }

  Node *head = get_head();
  printf(PURPLE "Total commands entered: %d\n", total);
  printf(CYAN "Most used commands:\n");

  for (int i = 0; i < 3; head = head->next, i++) {
    if (head == NULL)
      break;
    double percent = (double)head->count / (double)total * 100;
    printf(GREEN "%s -> %d(%.2f%%)\n", head->word, head->count, percent);
  }
  printf(CLEAN);

  fclose(file);
  free(buffer);
  return 0;
}
