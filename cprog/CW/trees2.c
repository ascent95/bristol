//Part 2
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct tree 
{
    char name[20];
    char number[20];
    struct tree *l, *r;

} Tree;

int strncasecmp(char *str1, char *str2, int n)
{
    char *str1copy = malloc (1 + strlen(str1)); //Make new copies so we can change to lower case.
    char *str2copy = malloc (1 + strlen(str2));
    strcpy(str1copy, str1);
    strcpy(str2copy, str2);
    int i;
    for(i = 0; i<sizeof(str1copy); i++)
    {
        str1copy[i] = tolower(str1copy[i]);
    }
    for(i = 0; i<sizeof(str2copy); i++)
    {
        str2copy[i] = tolower(str2copy[i]);
    }
    return strncmp(str1copy, str2copy,n);
}
Tree *newNode(char *name, char *number, Tree *left, Tree *right)
{
    Tree *newTree = malloc(sizeof(Tree));
    strncpy(newTree->name, name, 20);
    strncpy(newTree->number, number, 20);
    newTree->l = left;
    newTree->r = right;
    return newTree;
}

void insert(char *name, char *number, Tree *node)
{
    if(strncmp(name,node->name,20)<0)
    {
        if(node->l == NULL) node->l = newNode(name,number,NULL,NULL);
        else insert(name,number,node->l);
    }
    else if (strncmp(name,node->name,20)>0)
    {
        if(node->r == NULL) node->r = newNode(name,number,NULL,NULL);
        else insert(name,number,node->r);
    }
    else
    {
        printf("This name already exists\n");
    }
}

int textInput(char *name, char *number)
{
    char temp[40];
    fgets(temp, 40, stdin);
    if(temp[0] == '.') return 0;
    else
    {
        sscanf(temp,"%s %s",name,number);
    }
    return 1;
}

Tree *fillTree(void)
{
    char name[20], number[20];
    if(!textInput(name, number)) return NULL; //If first input is a dot.
    Tree *phoneBook = newNode(name,number,NULL,NULL);
    while(textInput(name, number))
    {
        insert(name,number,phoneBook);
    }
    return phoneBook;
}

void lookUp(char *name, Tree *node)
{
    if(strncasecmp(name,node->name,20)<0)
    {
        if(node->l == NULL) printf("NOT FOUND\n");
        else lookUp(name,node->l);
    }
    else if (strncasecmp(name,node->name,20)>0)
    {
        if(node->r == NULL) printf("NOT FOUND\n");
        else lookUp(name,node->r);
    }
    else //The names are the same.
    {
        printf("%s\n", node->number); //Print the phone number.
    }
}

int main(void)
{
    Tree *phoneBook = fillTree();
    char name[20];
    while(1)
    {
        fgets(name, 20, stdin);
        for(int i = 0; i<sizeof(name); i++)
        {
            if (name[i] == '\n') name[i] = '\0';
            if (name[i] == '.') return 1;
        }        
        lookUp(name,phoneBook);
    }
}
