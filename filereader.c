#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


bool readLine(FILE* file, char** line){
    char c;
    if((c = fgetc(file)) == EOF){
        return false;
    }
    char* newLine = malloc(sizeof(char));
    size_t maxLength=1;
    size_t n = 0;
    do
    {
        newLine[n++] = c;
        if (n>=maxLength){
            maxLength*=2;
            newLine=realloc(newLine,sizeof(char)*maxLength);
        }
    }while((c = fgetc(file)) != EOF && c != '\n');
    newLine[n++]= '\n';
    if (n>=maxLength){
        maxLength*=2;
        newLine=realloc(newLine,sizeof(char)*maxLength);
    }
    newLine[n++]= '\0';
    *line=newLine;
    return true;
}