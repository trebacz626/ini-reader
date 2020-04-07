#ifndef PARAMETERS_H
#define PARAMETERS_H


typedef struct Parameters{
    char * filename;
    char * firstKey;
    char * firstValue;
    char * secondKey;
    char * secondValue;
    char operation;
} Parameters;

Parameters* getParameters(int argc, char**argv);

void deleteParameters(Parameters* params);


#endif