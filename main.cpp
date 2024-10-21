#include <iostream>
#include <fstream>
#include <OpenXLSX.hpp>
#include <windows.h>

#include "arrayProcedures.h"

using namespace std;
using namespace OpenXLSX;

CONSOLE_SCREEN_BUFFER_INFOEX ConsoleInfo;
HANDLE hConsole = CreateConsoleScreenBuffer(GENERIC_READ | GENERIC_WRITE, 0, NULL, CONSOLE_TEXTMODE_BUFFER, NULL);

char** LocationInfo = new char*[0];
unsigned short LocationInfoSize = 0;
char* Planet = new char[11] {"Paradarium"};
char* Location = new char[5] {"CK25"};

const short ItemNameLength = 44, MaxInventorySize = 14;
char Inventory[MaxInventorySize][ItemNameLength] = {{""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}};
unsigned short InventoryCounts[MaxInventorySize] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
short InventorySize = 6;

// head, body, legs, feet, right hand, left hand, hold in right hand, hold in left hand
char EquipmentInventory[8][ItemNameLength] = {{""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}};

unsigned short getEquipId(char* name) {
    // I can't use switch case with char arrays, so I forced to use if :(

    const char head[] = {"head"}, body[] = {"body"}, legs[] = {"legs"}, feet[] = {"feet"},
        rhand[] = {"right hand"}, lhand[] = {"left hand"}, rhandh[] = {"hold in right hand"}, lhandh[] = {"hold in left hand"};
    if (isSameStrings(name, head)) {
        return 0;
    } else if (isSameStrings(name, body)) {
        return 1;
    } else if (isSameStrings(name, legs)) {
        return 2;
    } else if (isSameStrings(name, feet)) {
        return 3;
    } else if (isSameStrings(name, rhand)) {
        return 4;
    } else if (isSameStrings(name, lhand)) {
        return 5;
    } else if (isSameStrings(name, rhandh)) {
        return 6;
    } else if (isSameStrings(name, lhandh)) {
        return 7;
    }
}


void ChangeColorSet(short number) {
    // Changes current 4-bit color set of windows console

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
    // simplifies output of colored text. you need determinant and to hex numbers after it - foreground and background
    // uses 16 colors from color set of windows console

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
                cout << line[i];
            }
        } else {
            cout << line[i];
        }
    }
}


char** LoadLocationInfo(char location[], char world[]) {
    short i;
    for (i = 0; i < LocationInfoSize; i++) {
        delete[] LocationInfo[i];
    }
    delete[] LocationInfo;

    XLDocument doc;
    doc.open("map.xlsx");
    auto wks = doc.workbook().worksheet(world);

    string line = wks.cell(location).getString();

    short counter = 0;
    i = 0;
    while (line[i] != '\0') {
        if (line[i] == ';') {
            counter++;
        }
        i++;
    }

    char** li = new char*[counter];
    LocationInfoSize = counter;

    short pos = 0, opos = 0;
    for (i = 0; i < counter; i++) {
        while (line[pos] != ';') {
            pos++;
        }

        pos++;
        li[i] = new char[pos - opos];

        for (short j = 0; j < pos - opos; j++) {
            if (j != pos - opos - 1) {
                li[i][j] = line[opos + j];
            } else {
                li[i][j] = '\0';
            }
        }

        opos = pos;
    }

    doc.close();
    return li;
}


void useItem(char Item[]) {

}

void displayInventory() {
    bool itemChosen = false;
    short number = 0, item = 0;

    do {
        system("cls");
        for (short i = 0; i < MaxInventorySize - InventorySize; i++) {
            cout << endl;
        }
        for (short i = InventorySize; i > 0; i -= 2) {
            cout << i - 1 << ". ";
            if (InventoryCounts[i - 1] > 0) {
                cout << Inventory[i - 1] << " x " << InventoryCounts[i - 1];
            } else {
                for (short j = 0; j < ItemNameLength + 3; j++) {
                    cout << ' ';
                }
            }

            cout << i << ". ";
            if (InventoryCounts[i] > 0) {
                cout << Inventory[i] << " x " << InventoryCounts[i];
            } else {
                for (short j = 0; j < ItemNameLength + 3; j++) {
                    cout << ' ';
                }
            }
            cout << "\n" << endl;
        }

        char text[] = {"$10"};
        printColorizedText(text, sizeOfCString(text));
        cout << "\n\nголова: " << EquipmentInventory[0] << "     тело: " << EquipmentInventory[1] << endl;
        cout << "ноги: " << EquipmentInventory[2] << "     стопы: " << EquipmentInventory[3] << endl;
        cout << "на правой руке: " << EquipmentInventory[4] << "     на левой руке: " << EquipmentInventory[5] << endl;
        cout << "предмет в правой руке: " << EquipmentInventory[6] << "     предмет в левой руке: " << EquipmentInventory[7] << endl;
        text[1] = '7';
        printColorizedText(text, sizeOfCString(text));

        cout << "\n\nВаш инвентарь.\nДоступные действия (введите число): 1 выбрать предмет, 2 выйти.\n>>";
        cin >> number;

        if (number < 1 || number > 2) {
            cout << "\nКакая-то туманность в мыслях, не могу понять чего же я сам хочу";
            Sleep(3500);
        } else if (number == 1) {
            cout << "Какой предмет взять?\n(номер слота. индексы для оборудования: голова 15, тело 16, ноги 18, стопы 19, "
                    "правая рука 20, левая рука 21, предмет в правой руке 22, предмет в левой руке 23)\n>>";
            cin >> item;
            if (item < 1 || item > 23) {
                cout << "";
            }
        }
    } while (number != 2);
}


int main() {
    SetConsoleOutputCP(CP_UTF8);

    HWND hwConsole = GetConsoleWindow();
    ShowWindow(hwConsole, SW_HIDE);

    ConsoleInfo.cbSize = sizeof(ConsoleInfo);

    GetConsoleScreenBufferInfoEx(hConsole, &ConsoleInfo);
    SetWindowPos(hwConsole, HWND_TOP, 0, 0, 0, 0, SWP_FRAMECHANGED | SWP_NOMOVE | SWP_NOSIZE| SWP_SHOWWINDOW);

    ChangeColorSet(1);

    displayInventory();


    while (1) {

    }

    return 0;
}
