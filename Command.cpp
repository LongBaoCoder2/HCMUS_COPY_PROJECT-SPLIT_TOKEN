#include "Command.h"
#include "Modules.h"
#include <string.h>
#include <iostream>

// Cu phap 1
void command::commandOne(char **argv){
    COPY(argv[1], argv[2]);
}

// Cu phap 2
void command::commandTwo(char ** argv) {
    // Tham so thu nhat -> chua ten file
    char *first = argv[1];
    // Tham so thu hai -> chua folder paste
    char *second = argv[2];

    // Tach ten name trong first sau do ghep vao second
    size_t size = strlen(first);
    size_t sliceIndex = -1;
    for (int i = size; i >= 0; i--){
        if (first[i] == '/'){
            sliceIndex = i;
            break;
        }
    }
    char *temp = new char[size - sliceIndex];
    strcpy(temp, &first[sliceIndex + 1]);

    // Tao duong dan moi bang cach cong second voi ten file
    char *newPath = new char[strlen(temp) + strlen(second) + 1];
    strcpy(newPath, second);
    strcpy(&newPath[strlen(newPath)], temp);   

    // Copy tren path moi
    COPY(first, newPath);

    // Khoi phuc du lieu
    delete[] newPath;
    delete [] temp;
}

// Cu phap 3
void command::commandThree(char **argv) {
    COPY(argv[1], argv[4], 'a');
    COPY(argv[3], argv[4], 'a');
}

// Cu phap 4
void command::commandFour() {
    std::cout << "--------- LIST COMMAND ---------\n\n";

    std::cout << "command 1: copy and rename\n";
    std::cout << "     COPY <file source> <file dest>\n";
    std::cout << "command 2: copy and not rename\n";
    std::cout << "     COPY <file source> <file dest>\\\n";
    std::cout << "command 3: concatenate two file\n";
    std::cout << "     COPY <file 1> + <file 2> <file dest>\n";
    std::cout << "command 4: see help\n";
    std::cout << "     COPY -?\n";
    std::cout << "     COPY --help\n";
}

// Cu phap sai
void command::commandInvalid() {
    std::cout << "Bad command! See 'COPY --help' or 'COPY -?'\n";
}