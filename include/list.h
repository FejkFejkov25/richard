#ifndef LIST_H_
#define LIST_H_
#define SIZE 1024

typedef struct {
  char *word;
  int count;
  void *next;
} Node;

Node *add_item(const char *word);
Node *lookup(char *word);
Node *get_head(void);
void sort_list(void);
void cleanlist(void);

#endif
