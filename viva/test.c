#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/*int strncasecmp(char *str1, char *str2, int n)
{
    char *str1copy = malloc (1 + strlen(str1)); //Make new copies so we can change to lower case.
    char *str2copy = malloc (1 + strlen(str2));
    strcpy(str1copy, str1);
    strcpy(str2copy, str2);
    int i, comp;
    for(i = 0; i<sizeof(str1copy); i++)
    {
        str1copy[i] = tolower(str1copy[i]);
    }
    for(i = 0; i<sizeof(str2copy); i++)
    {
        str2copy[i] = tolower(str2copy[i]);
    }
    comp = strncmp(str1copy, str2copy,n);
    free(str1copy); //Free the previously allocated memory. 
    free(str2copy);
    return comp;
}*/

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

int main(void)
{
    Tree *phoneBook = fillTree();
    char name[100];
    while(textInput(name,NULL))
    {      
        lookUp(name,phoneBook);
    }
    freeMem(phoneBook);
    return 1;
}
