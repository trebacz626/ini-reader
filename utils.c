#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

bool is_alphanumerical(char* text){
    for(int i=0;i<strlen(text);i++){
        if(!isalnum(text[i])){
            return false;
        }
    }
    return true;
}

bool is_a_number(char* text){
    for(int i=0;i<strlen(text);i++){
        if(!isdigit(text[i])){
            return false;
        }
    }
    return true;
}