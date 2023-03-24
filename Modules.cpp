// #pragma warning(disable:4996)
#include <iostream>
#include <fstream>
#include "Modules.h"
#define MAX 200

std::istream &readFile (std::istream &inFile, char *buffer) {
    return inFile.read(buffer, MAX);
}


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
    size_t remainByte = 0;

    // Tranh ham inFile.read(buffer, MAX_COPY) khi MAX_COPY == 0 --> sinh ra vong lap vo han
    while (inFile.read(buffer, MAX_COPY) && MAX_COPY != 0) {
        sizeReaded = inFile.gcount();
        outFile.write(buffer, sizeReaded);

        process += sizeReaded;
        percent = process * 100 / totalSize;
        remainByte = totalSize - process;
        MAX_COPY = (MAX_COPY < remainByte) ? MAX_COPY : remainByte;

        if (percent - previousPer > 10) {
            displayProcessBar(percent);
            previousPer = percent;
        }

    }
    /*
        Giai thich:
            process: bien luu tru tong so luong byte da duoc copy
            sizeReaded: bien luu tru so byte copy duoc trong 1 vong lap
            percent = process / totalSize
            previousPer : percent luu tru truoc do, dung de tao process bar
            remainByte : so byte con lai chua copy*

            Ta can bien remainByte la de tranh truong hop ham inFile.read(buffer, MAX_COPY) 
                khi doc thi lieu byte con lai < MAX_COPY --> sinh ra loi, cho nen co the
                xay ra loss data o cuoi file.
    */

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

