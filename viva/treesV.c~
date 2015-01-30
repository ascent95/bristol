//Part 4
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct entry
{
    char number[20];
    struct entry *next;
} Entry;

typedef struct list
{
    Entry *first, *last;
} List;

typedef struct tree 
{
    char name[100];
    List *numberList;
    struct tree *l, *r;

} Tree;

List *newList()
{
    List *result = malloc(sizeof(List));
    result->first = result->last = NULL;
    return result;
}


void append(List *l, char *number)
{
    Entry *e = malloc(sizeof(Entry));
    //e->number = number;
    strncpy(e->number,number,20);
    e->next = NULL;
    if(l->first == NULL)
    {
        l->first = e;
    }
    else l->last->next = e;
    l->last = e;
}

int strnCaseCmp(char *str1, char *str2)
{
    char s1,s2;
    while(1)
    {
        s1 = tolower(*str1);
        s2 = tolower(*str2);
        if(s1 == s2 && *str1 != 0 && *str2 != 0)
        {
            str1++;
            str2++;
        }
        else{break;}
    }
    return(s1-s2);
}

Tree *newNode(char *name, char *number, Tree *left, Tree *right)
{
    Tree *newTree = malloc(sizeof(Tree));
    strncpy(newTree->name, name, 20);
    //strncpy(newTree->number, number, 20);
    newTree->numberList = newList(); //Make a new empty phone number list.
    append(newTree->numberList, number);
    newTree->l = left;
    newTree->r = right;
    return newTree;
}

void insert(char *name, char *number, Tree *node)
{
    int x = strnCaseCmp(name,node->name);
    if(x<0)
    {
        if(node->l == NULL) node->l = newNode(name,number,NULL,NULL);
        else insert(name,number,node->l);
    }
    else if (x>0)
    {
        if(node->r == NULL) node->r = newNode(name,number,NULL,NULL);
        else insert(name,number,node->r);
    }
    else
    {
        append(node->numberList, number);
    }
}

void lookUp(char *name, Tree *node)
{
    int x = strnCaseCmp(name,node->name);
    if(x<0)
    {
        if(node->l == NULL) printf("NOT FOUND\n");
        else lookUp(name,node->l);
    }
    else if (x>0)
    {
        if(node->r == NULL) printf("NOT FOUND\n");
        else lookUp(name,node->r);
    }
    else //The names are the same.
    {
        Entry *e = node->numberList->first;
        while(e) //While not null.
        {
            printf("%s\n", e->number);
            e = e->next;
        }
    }
}

int textInput(char *name, char *number)
{
    char temp[120];
    fgets(temp, 120, stdin);
    if(temp[0] == '.') return 0;
    else
    {
        sscanf(temp,"%s %s",name,number);
    }
    return 1;
}

Tree *fillTree(void)
{
    char name[100], number[20];
    if(!textInput(name, number)) return NULL; //If first input is a dot.
    Tree *phoneBook = newNode(name,number,NULL,NULL);
    while(textInput(name, number))
    {
        insert(name,number,phoneBook);
        name[0] = '\0'; //In case no name or number is input. This effectively clears the array for the next iteration. 
        number[0] = '\0';
    }
    return phoneBook;
}


void freeListMem(Entry *node)
{
    if(node->next) freeListMem(node->next);
    free(node);
}
void freeMem(Tree *node)
{
    if(node->l) freeMem(node->l);
    if(node->r) freeMem(node->r);
    freeListMem(node->numberList->first); //Frees entry memory
    free(node->numberList); //Frees list memory
    free(node);
}

int main(void)
{
    Tree *phoneBook = fillTree();
    char name[100];
    while(textInput(name,NULL)) //I re-used textInput to reduce code.
    {      
        lookUp(name,phoneBook);
        *name = 0; //Needed in case no name is input in the next iteration. 
    }
    freeMem(phoneBook);
    return 1;
}
