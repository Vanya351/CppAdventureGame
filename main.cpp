#include <iostream>
#include <fstream>
#include <OpenXLSX.hpp>
#include <windows.h>

#include "arrayProcedures.h"

using namespace std;
using namespace OpenXLSX;

CONSOLE_SCREEN_BUFFER_INFOEX ConsoleInfo;
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

/*
    XLDocument doc;
    doc.open("map.xlsx");
    auto wks = doc.workbook().worksheet("Paradarium");

    cout << wks.cell("BW7").value();

    doc.save();

    return 0;
*/


void ChangeColorSet(short number) {
    const COLORREF set1[16] = {
            0x000C0C0C,
            0x00468A25,
            0x000EA113,
            0x00DD963A,
            0x001F0FC5,
            0x00981788,
            0x00009CC1,
            0x00B4B4B4,
            0x00767676,
            0x00FA5514,
            0x00074D73,
            0x00D6D661,
            0x0004B5F7,
            0x009E00B4,
            0x0032F1F9,
            0x00F5F5F5
    };

    const COLORREF* curSet;

    switch (number) {
        default: curSet = set1; break;
    }

    for (short i = 0; i < 16; i++) {
        ConsoleInfo.ColorTable[i] = curSet[i];
    }

    SetConsoleScreenBufferInfoEx(hConsole, &ConsoleInfo);
}

void printColorizedText(char* line, unsigned short size, char colorDeterminant = '$') {
    HANDLE hOutputConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    char colorSet[] = {"0123456789ABCDEF"};
    short back, fore;

    for (unsigned short i = 0; i < size; i++) {
        if (line[i] == colorDeterminant) {
            if (isIn(colorSet, 16, line[i + 1])) {
                switch (line[i + 1]) {
                    case 'A': fore = 10; break;
                    case 'B': fore = 11; break;
                    case 'C': fore = 12; break;
                    case 'D': fore = 13; break;
                    case 'E': fore = 14; break;
                    case 'F': fore = 15; break;
                    default: fore = (short)line[i + 1];
                }

                switch (line[i + 2]) {
                    case 'A': back = 10; break;
                    case 'B': back = 11; break;
                    case 'C': back = 12; break;
                    case 'D': back = 13; break;
                    case 'E': back = 14; break;
                    case 'F': back = 15; break;
                    default: back = (short)line[i + 2];
                }

                SetConsoleTextAttribute(hOutputConsole, fore + back * 16);
                i += 2;
            } else {
                cout << line[i];
            }
        } else {
            cout << line[i];
        }
    }
}


int main() {
    HWND hwConsole = GetConsoleWindow();
    ShowWindow(hwConsole, SW_HIDE);

    ConsoleInfo.cbSize = sizeof(ConsoleInfo);

    GetConsoleScreenBufferInfoEx(hConsole, &ConsoleInfo);
    SetWindowPos(hwConsole, HWND_TOP, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE| SWP_SHOWWINDOW);

    ChangeColorSet(1);



    cout << 'a';
    int a;
    cin >> a;


    while (1) {

    }

    return 0;
}
