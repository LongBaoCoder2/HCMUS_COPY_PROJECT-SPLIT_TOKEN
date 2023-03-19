#pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include "Modules.h"
#define MAX 100

// Tra ve kich thuoc file
long long fileSize(const char* filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cout << "File not found\n";
        return 0;
    }
    file.seekg(0, std::ios::end);
    long long size = (long long)file.tellg();
    file.close();

    return size;
}

// Tao process bar khi copy
void displayProcessBar(size_t percent) {
    const size_t sizeBar = 100;
    std::cout << "[ ";
    for (int i = 0; i < sizeBar; i++) {
        std::cout << (i < percent ? "#" : " ");
    }
    std::cout << " ] " << percent << "%\n";
}

// Ham copy
bool COPY(const char* fileSrc, const char* fileDest, char mode) {
    std::ifstream inFile(fileSrc, std::ios::in | std::ios::binary);
    std::ofstream outFile;

    // Lua chon che do mo -> mo kieu append hoac overriding
    if (mode == 'w') {
        outFile.open(fileDest, std::ios::out | std::ios::binary);
    }
    else {
        outFile.open(fileDest, std::ios::binary |  std::ios::app );
        outFile.seekp(0, std::ios::end);
    }


    // Kiem tra file da mo chua
    if (!inFile.is_open() || !outFile.is_open()) {
        std::cout << "File not found\n";
        return false;
    }

    // Khai bao cac tham so
    size_t totalSize = fileSize(fileSrc);

    // Lay ra gia tri lon nhat co the copy
    // Trach truong hop file_size < MAX  ---> sinh ra loi
    size_t MAX_COPY = ( MAX > totalSize ) ? totalSize : MAX;
    char *buffer = new char[MAX_COPY];

    size_t process = 0;
    size_t sizeReaded = 0;
    size_t percent = 0;
    size_t previousPer = 0;

    while (inFile.read(buffer, MAX_COPY)) {
        sizeReaded = inFile.gcount();
        outFile.write(buffer, sizeReaded);

        process += sizeReaded;
        percent = process * 100 / totalSize;
        if (percent - previousPer > 10) {
            displayProcessBar(percent);
            previousPer = percent;
        }
    }

    // Kiem tra loi ghi doc
    if (inFile.bad() || outFile.bad()) {
        std::cout << "Error copy file!\n";
        return false;
    }

    std::cout << "\nCopy already!\n";
    delete[]buffer;

    inFile.close();
    outFile.close();

    return true;
}

