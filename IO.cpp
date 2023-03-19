#include "IO.h"
#include "token.h"
#include <iostream>
#define MAX 200

// Nhap doan van ban
void inputParams(char *&params) {
    char temp[MAX];
    int n = 0;
    char buffer;
    
    std::cin.get(temp[0]);
    while (std::cin.get(buffer) && n < MAX) {
        if (temp[n] == '.' && buffer == '\n') {
            break;
        }
        temp[++n] = buffer;
    }
    temp[n + 1] = '\0';

    int size = n + 2;
    params = new char[size];

    if (params == nullptr) {
        std::cout << "Out of memory\n";
        exit(1);
    }
    memcpy(params, temp, size);
}

// Xuat ket qua
void outputRes(int count, char *paramsNormalize ) {
    std::cout << "So luong tu trong doan van la :" << count << std::endl;
    std::cout << "Doan van duoc chuan hoa : \n" << paramsNormalize << std::endl;
}

// Khoi phuc du lieu
void getFreeMemory(char* &params, char** &listToken, char* &normalizeParams, int count)
{
    delete[] normalizeParams;
    for (int i = 0; i < count; i++) {
        delete[] listToken[i];
        listToken[i] = nullptr;
    }
    delete[] listToken;
    delete[]params;
    normalizeParams = nullptr;
    listToken = nullptr;
    params = nullptr;

}



