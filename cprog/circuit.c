#include <stdio.h>
#include <string.h>

int main(void) {
    char str[100];
    
    gets(str);
    int i;
    char res[256];
    for(i = 0; i < strlen(str); i++) {
       printf("%c\n - %c", str[i], conv(str[i]));
    }
    return 0;
}

char * conv(char x) {
    
    if (isupper(x)) {
        printf("This letter is upper case: %c", x);
        char *cp;
        cp = &x;
        return cp;
    } else {
        printf("This letter is not upper case: %c", x);
        char *res = malloc(sizeof(char)*6);
        res[0] = 'N';
        res[1] = 'O';
        res[2] = 'T';
        res[3] = ' ';
        res[4] = x;
        res[5] = '\0';
        return res; 
    }  
}
