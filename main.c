#include "colors.h"
#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#define SIZE 1024
#define PATH 128
#define DELIM " \n\t"

char *shell = "bash";
int amount = 3;

void usage(void) {
  printf("Usage of richard: -s - specify your shell(default: bash)\n");
  printf("                  -a - amount of lines in top(default: 3)\n");
  printf("                  -h - show this message\n");
  _exit(0);
}

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

  for (int i = 1; i < argc; i++) {
    if ((argv[i][0] == '-') && (argv[i][1] == 's'))
      shell = argv[++i];
    if ((argv[i][0] == '-') && (argv[i][1] == 'a'))
      amount = atoi(argv[++i]);
    if ((argv[i][0] == '-') && (argv[i][1] == 'h'))
      usage();
  }

  char filename[PATH];
  char *buffer = malloc(SIZE);
  if (buffer == NULL)
    return -2;

  sprintf(filename, "%s/.%s_history", getenv("HOME"), shell);
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

  for (int i = 0; i < amount; head = head->next, i++) {
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
