#include "IO.h"
#include "token.h"


int main() {
    // Khai bao
    // Bien input
    char* params = nullptr;
    // Bien output
    char** listToken = nullptr;
    int count = 0;
    char* normalizeParams = nullptr;

    // Nhap du lieu
    inputParams(params);

    // Token Handle
    listToken = token::splitTokens(params, count); // -> tra ve con tro cap 2
    normalizeParams = token::normalizeParams(listToken, count); // -> tra ve con tro cap 1

    // Output
    outputRes(count, normalizeParams);

    // Khoi phuc du lieu
    getFreeMemory(params, listToken, normalizeParams, count);
}