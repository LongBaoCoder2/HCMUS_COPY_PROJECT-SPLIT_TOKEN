#include <string.h>
#include <iostream>
#include "token.h"
//#define _CRT_SECURE_NO_WARNINGS

namespace {

    // Delim la chuoi chua cac dau cau va dau cach, tuc chua ky tu tach token
    char delim[] = " ,.;?!\n";
    size_t sizeDelim = strlen(delim);

    // Bien luu tru de dung lai qua trinh tach token
    const int INITIALIZE_SLICE = -1;
}

// Kiem tra ki tu c co trong delim khong
inline bool findSpan(char c)
{
    for (int i = 0; i < sizeDelim; i++) {
        if (c == delim[i])
            return true;
    }
    return false;
}

// Ham tach tung` token
int handleToken(char* params, char* &tokenInArray) {
    size_t size = strlen(params);

    // Bien luu tru vi tri tim thay delim
    int sliceIndex = INITIALIZE_SLICE;

    if (size == 1 && findSpan(params[0])) {
        return INITIALIZE_SLICE;
    }

    for (int i = 0; i < size; i++) {
        const bool check = findSpan(params[i]);
        if (check) {
            sliceIndex = i;
            break;
        }
    }


    if (sliceIndex == 0) {
        // Neu tim thay delim o index 0
        return 1;
    }
    else if (sliceIndex == -1) {
        tokenInArray = new char[size + 1];
        if (tokenInArray == nullptr) {
            std::cout << "Out of memory.\n";
            exit(1);
        }

        memcpy(tokenInArray, params, size + 1);
        // Khong can phai split token
        return INITIALIZE_SLICE;
    }
    else {
        tokenInArray = new char[sliceIndex + 1];
        if (tokenInArray == nullptr) {
            std::cout << "Out of memory.\n";
            exit(1);
        }

        memcpy(tokenInArray, params, sliceIndex);
        tokenInArray[sliceIndex] = '\0';
        return sliceIndex + 1;
    }

}


char** token::splitTokens(char* params, int& n) {
    char* listToken[100];

    // Tao mot ban sao cho doan van
    size_t size = strlen(params) + 1;
    char* temp = new char[size];
    if (temp == nullptr) {
        std::cout << "Out of memory.\n";
        exit(1);
    }

    memcpy(temp, params, size);

    // Bien dem so luong token lay duoc
    int currentToken = 0;
    
    /* Trang thai cua qua trinh cat
     Co 3 gia tri ham handleToken tra ve
        + INITIALIZE_SLICE (hang so) la trang thai de dung` qua trinh cat
        + 1 : delim tim duoc o index 0
        + Gia tri index tim thay delim
    */
    int statusProcess = handleToken(temp, listToken[currentToken]);
    
    // Luu vi tri token duoc cat den dau trong doan van
    int process = 0;
    while (statusProcess != INITIALIZE_SLICE) {
        process += statusProcess;

        if (statusProcess != 1)
            currentToken++;
        statusProcess = handleToken(&temp[process], listToken[currentToken]);
    }

    // Ket qua tra ve so luong token thu duoc cung tuc la tong so tu
    n = currentToken;

    char** list = new char* [n];
    if (list == nullptr) {
        std::cout << "Out of memory.\n";
        exit(1);
    }

    memcpy(list, listToken, n * sizeof(char*));
    return list;
}
