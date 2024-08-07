#include "csock.h"

void funerror(const char* errorMsg){
    perror(errorMsg);
    exit(0);
}

