#include <stdio.h>
#include <stdlib.h>

typedef struct entry
{
  char character;
  struct entry *next;
} entry;
typedef struct list
{
  entry *first;
} list;

list *makeList()
{
  char c = '\0';
  list *result = malloc(sizeof(list));
  result->first = NULL;
  while(c != '.')
  {
    c = getchar(); //Must be placed inside loop so that last full-stop can be processed.
    entry *e = malloc(sizeof(entry));
    e->character = c;
    e->next = result->first;
    result->first = e;
  }
  return result;
}

void printList(list *cs)
{
  entry *current = cs->first;
  while(current != NULL)
  {
    printf("%c", current->character);
    current = current->next;
  }
  printf("\n");
}
int main(void)
{
  list *cs = makeList();
  printList(cs);
}