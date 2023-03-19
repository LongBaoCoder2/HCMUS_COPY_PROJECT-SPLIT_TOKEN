#include <string.h>
#include "Modules.h"
#include "Interface.h"
#include "Command.h"
#include <stdlib.h>
#define INVALID_COMMAND 0
#define COMMAND_ONE 1
#define COMMAND_TWO 2
#define COMMAND_THREE 3
#define COMMAND_FOUR 4

// Phan loai cac cu phap
int dispatchAction(int argc, char** argv) {
    switch (argc) {
    case 2:
        if (strcmp(argv[1], "-?") == 0 || strcmp(argv[1], "--help") == 0)
            return COMMAND_FOUR;
        else
            return INVALID_COMMAND;

    case 3:
        if (argv[2][strlen(argv[2]) - 1] == '/')
            return COMMAND_TWO;
        else
            return COMMAND_ONE;

    case 5:
        if (strcmp(argv[2], "+") == 0)
            return COMMAND_THREE;
        else
            return INVALID_COMMAND;
    default:
        return INVALID_COMMAND;
    }
}


// Xu li (Reducer) cho action
void interfaceCopy(int argc, char** argv) {
    const int action = dispatchAction(argc, argv);
    switch (action) {
        case COMMAND_ONE:
            command::commandOne(argv);
            break;

        case COMMAND_TWO:
            command::commandTwo(argv);
            break;

        case COMMAND_THREE:
            command::commandThree(argv);
            break;

        case COMMAND_FOUR:
            command::commandFour();
            break;

        case INVALID_COMMAND:
            command::commandInvalid();
            break;
    }
}