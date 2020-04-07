#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "sectionstore.h"
#include "parameters.h"
#include "filereader.h"

bool is_alphanumerical(char* text){
    for(int i=0;i<strlen(text);i++){
        if(!is_alphanumerical(text[i])){
            return false;
        }
    }
    return false;
}

SectionStore *parseFile(FILE *file)
{
    char *line;
    
    SectionStore *store = createSectionStore();
    Section *currentSection;
    while (readLine(file,&line))
    {
        if( line[0]==';' || line[0]=='\n'){
            free(line);
            continue;
        }
        if (line[0] == '[')
        {
            char* sectionName = malloc(strlen(line)*sizeof(char));
            strncpy(sectionName,line+1,strlen(line));
            sectionName[strlen(sectionName)-2]='\0';
            if(!is_alphanumerical(sectionName)){
                free(line);
                free(sectionName);
                return NULL;
            }
            currentSection = addSection(store,sectionName);
            free(sectionName);
        }else {
            char* key = strdup(strtok(line, "="));
            char* trimmedKey = malloc(strlen(key)*sizeof(char));
            strncpy(trimmedKey,key,strlen(key));//remove last character
            trimmedKey[strlen(key)-1]='\0';
            free(key);
            char* value = strdup(strtok(NULL,"="));
            char * trimmedValue = malloc(strlen(value)*sizeof(char));
            strncpy(trimmedValue,value+1,strlen(value));//remove first character
            trimmedValue[strlen(value)-2]='\0';
            free(value);
            addKeyValuePair(currentSection,trimmedKey,trimmedValue);
            free(trimmedKey);
            free(trimmedValue);
        }
        free(line);
    }


    return store;
}

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
    if(store=NULL){
        return 1;
    }
    fclose(file);
    printf("%d\n", store->numberOfElements);

    char* firstValue = findValueByKey(store, params->firstKey, params->firstValue);
    if (firstValue == NULL)
    {
        free(firstValue);
        cleanMemory(params, store);
        return 1;
    }
    printf("%s\n",firstValue);
    char* secondValue = findValueByKey(store, params->secondKey, params->secondValue);
    if (secondValue == NULL)
    {
        free(firstValue);
        free(secondValue);
        cleanMemory(params, store);
        exit(1);
    }
    printf("%s\n",secondValue);
    free(firstValue);
    free(secondValue);
    cleanMemory(params, store);
    return 0;
}