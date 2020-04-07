#include <stdio.h>
#include "parameters.h"
#include <string.h>
#include <stdlib.h>

Parameters* getParameters(int argc, char**argv){
    Parameters *params =malloc(sizeof(struct Parameters));
    params->filename = strdup(argv[1]);
    char * firstVariable = strdup(strtok(argv[3], " "));
    char * operation = strdup(strtok(NULL, " "));
    params->operation = operation[0];
    free(operation);
    char * secondVariable = strdup(strtok(NULL, " "));
    params->firstKey = strdup(strtok(firstVariable, "."));
    params->firstValue = strdup(strtok(NULL, "."));
    params->secondKey = strdup(strtok(secondVariable, "."));
    params->secondValue = strdup(strtok(NULL, "."));
    free(firstVariable);
    free(secondVariable);
    return params;

}

void deleteParameters(Parameters* params){
    free(params->filename);
    free(params->firstKey);
    free(params->firstValue);
    free(params->secondKey);
    free(params->secondValue);
    free(params);
}