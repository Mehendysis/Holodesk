#pragma once
#include <iostream>
using namespace std;

#ifndef _DEBUG
#define DEBUG_MSG(x)
#else
void DEBUG_MSG(const char* message);
#endif

int getColorCode(char color) {
    switch (toupper(color)) {
    case 'R':
        return 31;
    case 'G':
        return 32;
    case 'B':
        return 34;
    case 'Y':
        return 33;
    case 'P':
        return 35;
    default:
        return 37;
    }
}

#ifdef _DEBUG
void DEBUG_MSG(const char* message) {
    char color = '\0';
    const char* text = message;
    if (message[0] == '¢' && isalpha(message[1])) {
        color = message[1];
        text = message + 2;
    }
    cerr << "\033[1;" << getColorCode(color) << "m" << text << "\033[0m" << endl;
}
#endif
