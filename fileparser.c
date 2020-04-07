#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "filereader.h"
#include "sectionstore.h"
#include "utils.h"


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
                printf("Forbiden character in section name\n");
                free(line);
                deleteSectionStore(store);
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
            if(!is_alphanumerical(trimmedKey)){
                printf("Forbiden character in key name\n");
                free(line);
                deleteSectionStore(store);
                free(trimmedKey);
                return NULL;
            }
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