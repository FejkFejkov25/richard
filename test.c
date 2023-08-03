#include "list.h"
#include <stdio.h>
#include <stdlib.h>

char *arr[] = {"qwerty", "qwerty", "qwerty", "Hello", "Hello", "world"};

int main(void) {
  for (int i = 0; i < 6; i++) {
    Node *item = lookup(arr[i]);
    if (item != NULL)
      item->count++;
    else {
      item = add_item(arr[i]);
      item->count++;
    }
  }

  sort_list();
  // world->hello
  // all ok
  // but memory don't freed. Luckily it's make init command
  for (Node *c = get_head(); c != NULL; c = c->next) {
    printf("%s->%d\n", c->word, c->count);
  }
  return 0;
}
