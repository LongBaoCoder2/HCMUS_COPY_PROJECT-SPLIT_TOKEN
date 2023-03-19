#include "token.h"
#include <string.h>
#include <iostream>
#define MAX 200

inline void token::normalizeToken(char* token) {
    size_t size = strlen(token);
    
    token[0] = toupper(token[0]);
    for (int i = 1; i < size; i++) {
        token[i] = tolower(token[i]);
    }
}



char* token::normalizeParams(char** listToken, int n) {
    char temp[MAX];
    temp[0] = '\0';

    for (int i = 0; i < n; i++) {
        size_t sizeCopy = strlen(listToken[i]) + 1;

        normalizeToken(listToken[i]);
        memcpy(&temp[strlen(temp)], listToken[i], sizeCopy);

        temp[strlen(temp) + 1] = '\0';
        temp[strlen(temp)] = ' ';
    }

    size_t size = strlen(temp) + 1;
    char* paramsNormalize = new char[size];
    if (paramsNormalize == nullptr) {
        std::cout << "Out of memory.\n";
        exit(1);
    }
    memcpy(paramsNormalize, temp, size);
    return paramsNormalize;
}
