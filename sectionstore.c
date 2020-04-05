#include <stdlib.h>
#include <string.h>
#include "sectionstore.h"
#include <stdio.h>

SectionStore *createSectionStore()
{
    SectionStore *store = malloc(sizeof(SectionStore));
    store->numberOfElements = 0;
    store->maxNumberOfElement = 10;
    store->sections = malloc(sizeof(Section) * store->maxNumberOfElement);
}

Section *addSection(SectionStore *store, char *name)
{
    printf("adding section \n");
    if (store->numberOfElements == store->maxNumberOfElement)
    {
        store->maxNumberOfElement *= 2;
        store->sections = realloc(store->sections, sizeof(Section) * store->maxNumberOfElement);
    }

    Section *section = (store->sections + store->numberOfElements);
    section->name = strdup(name);
    section->numberOfElements = 0;
    section->maxNumberOfElement = 10;
    section->keyValuePairs = malloc(sizeof(KeyValue) * section->maxNumberOfElement);
    store->numberOfElements++;
    return section;
}

KeyValue *addKeyValuePair(Section *section, char *key, char *value)
{
    if (section->numberOfElements == section->maxNumberOfElement)
    {
        section->maxNumberOfElement *= 2;
        section->keyValuePairs = realloc(section->keyValuePairs, sizeof(KeyValue) * section->maxNumberOfElement);
    }

    KeyValue *keyValue = (section->keyValuePairs + section->numberOfElements);
    keyValue->key = strdup(key);
    keyValue->value = strdup(value);
    section->numberOfElements++;
    return keyValue;
}

void deleteKeyValue(KeyValue *keyValue)
{
    free(keyValue->key);
    free(keyValue->value);
    //free(keyValue);
}

void deleteSection(Section *section)
{
    for (int i = 0; i < section->numberOfElements; i++)
    {
        deleteKeyValue(&(section->keyValuePairs[i]));
    }
    free(section->keyValuePairs);
    free(section->name);
    //free(section);
}

void deleteSectionStore(SectionStore *sectionStore)
{
    for (int i = 0; i < sectionStore->numberOfElements; i++)
    {
        deleteSection(&(sectionStore->sections[i]));
    }
    free(sectionStore->sections);
    free(sectionStore);
}

char* findValueByKey(SectionStore *store, char *sectionName, char *key)
{
    for (int i = 0; i < store->numberOfElements; i++)
    {
        if (strcmp(store->sections[i].name, sectionName) == 0)
        {
            for (int j = 0; j < store->sections[i].numberOfElements; j++)
            {
                if (strcmp(store->sections[i].keyValuePairs[j].key, key) == 0)
                {   
                    return strdup((store->sections[i].keyValuePairs[j].value));
                }
            }
            return NULL;
        }
    }
    return NULL;
}