#include "displayProcedures.h"
#include "arrayProcedures.h"

#include <iostream>
#include <windows.h>

void printColorizedText(char line[], unsigned short size, char colorDeterminant) {
    // simplifies output of colored text. you need determinant and to hex numbers after it - foreground and background
    // uses 16 colors from color set of windows console

    HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char colorSet[] = {"0123456789ABCDEF"};
    short back, fore;

    for (unsigned short i = 0; i < size; i++) {
        if (line[i] == colorDeterminant && isIn(colorSet, 16, line[i + 1])) {
            switch (line[i + 1]) {
                case 'A': fore = 10; break;
                case 'B': fore = 11; break;
                case 'C': fore = 12; break;
                case 'D': fore = 13; break;
                case 'E': fore = 14; break;
                case 'F': fore = 15; break;
                default: fore = (short)(line[i + 1] - '0');
            }

            switch (line[i + 2]) {
                case 'A': back = 10; break;
                case 'B': back = 11; break;
                case 'C': back = 12; break;
                case 'D': back = 13; break;
                case 'E': back = 14; break;
                case 'F': back = 15; break;
                default: back = (short)(line[i + 2] - '0');
            }

            SetConsoleTextAttribute(hOutputConsole, fore + back * 16);
            i += 2;
        } else {
            if (line[i] == '\0') {
                break;
            }
            std::cout << line[i];
        }
    }
}

void printColorizedText(const char line[], unsigned short size, char colorDeterminant) {
    // simplifies output of colored text. you need determinant and to hex numbers after it - foreground and background
    // uses 16 colors from color set of windows console

    HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char colorSet[] = {"0123456789ABCDEF"};
    short back, fore;

    for (unsigned short i = 0; i < size; i++) {
        if (line[i] == colorDeterminant && isIn(colorSet, 16, line[i + 1])) {
            switch (line[i + 1]) {
                case 'A': fore = 10; break;
                case 'B': fore = 11; break;
                case 'C': fore = 12; break;
                case 'D': fore = 13; break;
                case 'E': fore = 14; break;
                case 'F': fore = 15; break;
                default: fore = (short)(line[i + 1] - '0');
            }

            switch (line[i + 2]) {
                case 'A': back = 10; break;
                case 'B': back = 11; break;
                case 'C': back = 12; break;
                case 'D': back = 13; break;
                case 'E': back = 14; break;
                case 'F': back = 15; break;
                default: back = (short)(line[i + 2] - '0');
            }

            SetConsoleTextAttribute(hOutputConsole, fore + back * 16);
            i += 2;
        } else {
            if (line[i] == '\0') {
                break;
            }
            std::cout << line[i];
        }
    }
}