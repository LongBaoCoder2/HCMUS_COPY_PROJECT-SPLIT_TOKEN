#pragma once

namespace token {
    char* normalizeParams(char** listToken, int n);
    // void splitTokens(char* params, char** listToken, int& n);
    char** splitTokens(char* params, int& n);
    inline void normalizeToken(char* token);
}

// void splitToken(char* params, char** listToken, int& n);

// char* normalizeParams(char** listToken, int& n);