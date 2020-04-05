#ifndef SECTIONSTORE_H
#define SECTIONSTORE_H

typedef struct KeyValue{
    char * key;
    char * value;
} KeyValue;


typedef struct Section{
    int numberOfElements;
    int maxNumberOfElement;
    char * name;
    KeyValue * keyValuePairs;
} Section;

typedef struct SectionStore{
    int numberOfElements;
    int maxNumberOfElement;
    Section * sections; 

}SectionStore;

SectionStore * createSectionStore();

Section * addSection(SectionStore * store, char * name);

KeyValue * addKeyValuePair(Section *section, char * key, char * value);

void deleteKeyValue(KeyValue *keyValue);

void deleteSection(Section * section);

void deleteSectionStore(SectionStore * sectionStore);

char *findValueByKey(SectionStore *store, char *sectionName, char *key);


#endif