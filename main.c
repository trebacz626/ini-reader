#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sectionstore.h"
#include "parameters.h"
#include "fileparser.h"
#include "utils.h"

void cleanMemory(Parameters *params, SectionStore *store)
{
    deleteSectionStore(store);
    deleteParameters(params);
}

int main(int argc, char **argv)
{
    if (argc != 4)
    {
        printf("Wrong number of parameters: %d\n",argc);
        return 1;
    }
    Parameters *params = getParameters(argc, argv);
    FILE* file = fopen(params->filename,"r");
    if (file==NULL){
        printf("Could not read file\n");
        deleteParameters(params);
        return 1;
    }
    SectionStore *store = parseFile(file);
    fclose(file);
    if(store==NULL){
        deleteParameters(params);
        return 1;
    }

    char* firstValue = findValueByKey(store, params->firstKey, params->firstValue);
    if (firstValue == NULL)
    {
        free(firstValue);
        cleanMemory(params, store);
        return 1;
    }
    char* secondValue = findValueByKey(store, params->secondKey, params->secondValue);
    if (secondValue == NULL)
    {
        free(firstValue);
        free(secondValue);
        cleanMemory(params, store);
        return 1;
    }
    int exitCode=0;
    if(is_a_number(firstValue)&&is_a_number(secondValue)){
        float score;
        switch (params->operation)
        {
        case '*':
            score = atof(firstValue)*atof(secondValue);
            break;
        case '+':
            score = atof(firstValue)+atof(secondValue);
            break;
        case '\\':
            score = atof(firstValue)/atof(secondValue);
            break;
        case '-':
            score = atof(firstValue)-atof(secondValue);
            break;
        }
        
        printf("Result is: %f\n",score);
    }else if(!is_a_number(firstValue)&&!is_a_number(secondValue)){
        if(params->operation=='+'){
            size_t l1 = strlen(firstValue);
            size_t l2 = strlen(secondValue);
            char* result = malloc((l1+l2+1)*sizeof(char));
            memcpy(result,firstValue,l1*sizeof(char));
            memcpy(result+l1,secondValue,l2+1);
            printf("Result is: %s\n",result);
            free(result);
        }else{
            printf("Unsupported operation for strings\n");
            exitCode=1;
        }
    }else{
        printf("Error: Values are of different type\n");
        exitCode=1;
    }

    //final memory freeing
    free(firstValue);
    free(secondValue);
    cleanMemory(params, store);
    exit(exitCode);
}