#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct entry
{
  char *line;
  struct entry *next;
} entry;
typedef struct list
{
  entry *first;
} list;

void printList(list *cs); //Declaring the function.
void insert(list *result, char *s)
{
  entry *e = malloc(sizeof(entry));
  e->line = s;
  e->next = result->first;
  result->first = e;
}

list *makeList()
{
  int buf = 20;
  char *s = calloc(buf, sizeof(char)), *temp, *end; //*old_s
  list *result = malloc(sizeof(list));
  result->first = NULL;
  printf("Outside: %d\n",buf);
  while(fgets(s, buf, stdin ) != NULL)
  {
    printf("W1: %d\n",buf);
    while(!strchr(s, '\n')) //While we haven't got the whole line.
    {
      buf *= 2;
      //old_s = s;
      printf("Just before realloc\n");
      //s = realloc(old_s, buf * sizeof(char));
      s = (char *) realloc(s, buf * sizeof(char));
      printf("W2: %d\n",buf);
      if(s)
      {
        printf("In if statement\n");
        temp = calloc(buf, sizeof(char));
        fgets(temp,buf,stdin);
        strcat(s,temp);
        printf("After strcat\n");
      }
      else
      {
        printf("Memory reallocation failed, continuing with truncated string.\n");
        //s = old_s;
        break;
      }
    }
    if((end = strchr(s,'.')))
    {
      *end = '\n'; //Replace with newline character.
      *(end + 1) = '\0'; //Add in an end of string character.
      insert(result,s);
      break;
    }
    else
    {
      insert(result,s);
    }
    s = calloc(buf, sizeof(char)); //Allocate new memory for next line.
  }
  return result;
}

void printList(list *cs)
{
  entry *current = cs->first;
  while(current != NULL)
  {
    printf("%s", current->line);
    current = current->next;
  }
  //printf("\n");
}
int main(void)
{
  list *lines = makeList();
  printList(lines);
  return 0;
}