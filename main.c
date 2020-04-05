#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sectionstore.h"
#include "parameters.h"


int main(int argc, char **argv) {
    if (argc != 4){
        printf("Wrong number of parameters\n");
        return 1;
    }
    Parameters* params = getParameters(argc,argv);
    SectionStore* store = createSectionStore();
    //Structure test 600MB RAM
    // for(int i=0;i<10000;i++){
    //     Section* section = addSection(store,params->filename);
    //     for(int j=0;j<1000;j++){
    //         KeyValue* keyValue = addKeyValuePair(section,params->firstKey,params->firstValue);
    //     }
    // }
    printf("%d\n",store->numberOfElements);

    
    deleteSectionStore(store);
    deleteParameters(params);
    return 0;

}