#include <stdio.h>
#include <stdlib.h>

typedef struct entry
{
  char character;
  struct entry *next;
} entry;
typedef struct list
{
  entry *first, *last;
} list;

list *newList()
{
  list *result = malloc(sizeof(list));
  result->first = result->last = NULL;
  return result;
}

void append(list *l, char c)
{
  entry *e = malloc(sizeof(entry));
  e->character = c;
  e->next = NULL;
  if(l->first == NULL)
  {
    l->first = e;
  }
  else l->last->next = e;
  l->last = e;
}

list *makeWord()
{
  char c;
  list *result = newList();
  while((c = getchar()))
  {
    append(result, c);
    if(c == '\n' || c == '.') break; //Full-stop on its own line is just one character.
  }
  return result;
}

list *makeList()
{
  list *word;
  list *result = newList();
  while((word = makeWord()))
  {
    word->last->next = result->first;
    result->first = word->first;
    if(word->last->character == '.')
    {
      if(word->last == word->first)
      {
        word->last->character = '\0'; //Replace with end of string characer because we will already be on a new line
      }
      else
      {
        word->last->character = '\n'; //Replace full-stop with newline character
      }
      break;
    }
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
}
int main(void)
{
  list *cs = makeList();
  printList(cs);
}