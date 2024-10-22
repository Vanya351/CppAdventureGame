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
char Inventory[MaxInventorySize][ItemNameLength] = {{"Титан"}, {"a"}, {"шлем"}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}, {""}};
unsigned long long int InventoryCounts[MaxInventorySize] = {1, 3, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
short InventorySize = 6;

// head, body, legs, feet, right hand, left hand, hold in right hand, hold in left hand
char EquipmentInventory[8][ItemNameLength] = {{"шлем"}, {""}, {""}, {""}, {""}, {""}, {""}, {""}};

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

void printColorizedText(char line[], unsigned short size, char colorDeterminant = '$') {
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

void printColorizedText(const char line[], unsigned short size, char colorDeterminant = '$') {
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

void itemInfo(char Item[]) {

}

void displayInventory() {
    bool invAvailable, bpR = false, bpL = false, enterPressed = false, bwpR = false, bwpL = false, enterWasPressed = false;
    short menu = 1, number = 1, prevNumber = 1, item = 30, count = 0;
    const char clrsbs[] = {"$70"};   // color string base
    const char clrsci[] = {"$68"};   // color string current item
    const char clrsbut[] = {"$07"};  // color string button
    const char clrseq[] = {"$10"};   // color string equipment
    const char equipmentSlotNames[8][ItemNameLength] = {{"голова"}, {"тело"}, {"ноги"}, {"стопы"}, {"на правой руке"},
                                                        {"на левой руке"}, {"предмет в правой руке"}, {"предмет в левой руке"}};

    do {
        system("cls");
        for (short i = 0; i < MaxInventorySize - InventorySize; i++) {
            cout << endl;
        }
        for (short i = InventorySize; i > 0; i -= 2) {
            if (item == i - 1) printColorizedText(clrsci, 3);
            cout << i - 1 << ". ";
            if (InventoryCounts[i - 2] > 0) {
                cout << Inventory[i - 2] << " x " << InventoryCounts[i - 2];
                printColorizedText(clrsbs, 3);
                char* itemName = Trim(Inventory[i - 2]);
                for (short j = 0; j < ItemNameLength - sizeOfCString(itemName); j++) {
                    cout << ' ';
                }
                delete[] itemName;
            } else {
                for (short j = 0; j < ItemNameLength + 3; j++) {
                    cout << ' ';
                }
            }
            printColorizedText(clrsbs, 3);

            if (item == i) printColorizedText(clrsci, 3);
            cout << i << ". ";
            if (InventoryCounts[i - 1] > 0) {
                cout << Inventory[i - 1] << " x " << InventoryCounts[i - 1];
                printColorizedText(clrsbs, 3);
                char* itemName = Trim(Inventory[i - 1]);
                for (short j = 0; j < ItemNameLength - sizeOfCString(itemName); j++) {
                    cout << ' ';
                }
                delete[] itemName;
            } else {
                for (short j = 0; j < ItemNameLength + 3; j++) {
                    cout << ' ';
                }
            }
            printColorizedText(clrsbs, 3);
            cout << "\n" << endl;
        }

        printColorizedText(clrseq, 3);

        for (short i = 0; i < 8; i++) {
            if (item == MaxInventorySize + 1 + i) printColorizedText(clrsci, 3);
            cout << equipmentSlotNames[i] << ": " << EquipmentInventory[i];
            printColorizedText(clrseq, 3);
            short sz = ItemNameLength / 2 - sizeOfCString(EquipmentInventory[0]);
            if (sz > 0) for (short j = 0; j < sz; j++) {
                cout << ' ';
            }
            if (i % 2 == 0) {
                cout << "     ";
            } else {
                cout << endl;
            }
        }

        printColorizedText(clrsbs, 3);

        switch (menu) {
            case 1: {
                printColorizedText(clrsbs, 3);
                cout << "\n\nВаш инвентарь.\n" << endl;

                if (number == 1) printColorizedText(clrsbut, 3);
                cout << " выйти ";
                printColorizedText(clrsbs, 3);
                cout << "     ";

                if (number == 2) printColorizedText(clrsbut, 3);
                cout << " выбрать предмет ";
                printColorizedText(clrsbs, 3);
                cout << endl;

                do {
                    prevNumber = number;

                    if ((GetKeyState(VK_RIGHT) & 0x8000) && !bpR && !bpL && !bwpR && number < 2) {
                        bpR = true;
                        bwpR = true;
                        number++;
                    } else if (!(GetKeyState(VK_RIGHT) & 0x8000)) {
                        bpR = false;
                        bwpR = false;
                    }

                    if ((GetKeyState(VK_LEFT) & 0x8000) && !bpR && !bpL && !bwpL  && number > 1) {
                        bpL = true;
                        bwpL = true;
                        number--;
                    } else if (!(GetKeyState(VK_LEFT) & 0x8000)) {
                        bpL = false;
                        bwpL = false;
                    }

                    if ((GetKeyState(VK_RETURN) & 0x8000) && !enterPressed && !enterWasPressed) {
                        enterPressed = true;
                        enterWasPressed = true;
                    } else if (!(GetKeyState(VK_RETURN) & 0x8000)) {
                        enterPressed = false;
                        enterWasPressed = false;
                    }

                    Sleep(30);
                } while (!enterPressed && (prevNumber == number));


                if (number == 2 && enterPressed) {
                    menu = 2;
                    number = 2;
                    enterPressed = false;
                }
                break;
            }
            case 2: {
                cout << "\n\nКакой предмет выбрать?\n(номер слота. индексы для оборудования: голова 15, тело 16, ноги 17, стопы 18, "
                        "правая рука 19, левая рука 20, предмет в правой руке 21, предмет в левой руке 22. 25 для выхода)\n>>";
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                if (!(cin >> item)) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                if (item == 25) {
                    menu = 1;
                } else if (item < 1 || item > 23) {
                    enterPressed = false;
                    item = 30;

                    cout << "'Что-то я такого номера не нахожу'" << endl;

                    printColorizedText("\n   $07 ок $70\n", 15);

                    do {
                        if ((GetKeyState(VK_RETURN) & 0x8000) && !enterPressed && !enterWasPressed) {
                            enterPressed = true;
                            enterWasPressed = true;
                        } else if (!(GetKeyState(VK_RETURN) & 0x8000)) {
                            enterPressed = false;
                            enterWasPressed = false;
                        }

                        Sleep(30);
                    } while (!enterPressed);
                    enterPressed = false;
                } else if ((item < MaxInventorySize + 1 && InventoryCounts[item - 1] == 0) ||
                           (item >= MaxInventorySize + 1 && EquipmentInventory[item - (MaxInventorySize + 1)] == 0)) {
                    enterPressed = false;
                    cout << "Тут пусто. Лучше поискать в другом слоте" << endl;

                    printColorizedText("\n   $07 ок $70\n", 15);

                    item = 30;

                    do {
                        if ((GetKeyState(VK_RETURN) & 0x8000) && !enterPressed && !enterWasPressed) {
                            enterPressed = true;
                            enterWasPressed = true;
                        } else if (!(GetKeyState(VK_RETURN) & 0x8000)) {
                            enterPressed = false;
                            enterWasPressed = false;
                        }

                        Sleep(30);
                    } while (!enterPressed);
                    enterPressed = false;
                } else {
                    menu = 3;
                    enterPressed = false;
                }
                break;
            }
            case 3: {
                cout << "\n\nВы выбрали " << (item < MaxInventorySize + 1 ? Inventory[item - 1] : EquipmentInventory[item -  (MaxInventorySize + 1)])
                     << '\n' << endl;

                if (number == 2) printColorizedText(clrsbut, 3);
                cout << " отпустить ";
                printColorizedText(clrsbs, 3);
                cout << "     ";

                if (number == 3) printColorizedText(clrsbut, 3);
                if (item < MaxInventorySize + 1) {
                    cout << " использовать ";
                } else {
                    cout << " снять ";
                }
                printColorizedText(clrsbs, 3);
                cout << "     ";

                if (number == 4) printColorizedText(clrsbut, 3);
                cout << " выкинуть ";
                printColorizedText(clrsbs, 3);
                cout << "     ";

                if (number == 5) printColorizedText(clrsbut, 3);
                cout << " о предмете ";
                printColorizedText(clrsbs, 3);
                cout << endl;

                do {
                    prevNumber = number;

                    if ((GetKeyState(VK_RIGHT) & 0x8000) && !bpR && !bpL && !bwpR && number < 5) {
                        bpR = true;
                        bwpR = true;
                        number++;
                    } else if (!(GetKeyState(VK_RIGHT) & 0x8000)) {
                        bpR = false;
                        bwpR = false;
                    }

                    if ((GetKeyState(VK_LEFT) & 0x8000) && !bpR && !bpL && !bwpL && number > 2) {
                        bpL = true;
                        bwpL = true;
                        number--;
                    } else if (!(GetKeyState(VK_LEFT) & 0x8000)) {
                        bpL = false;
                        bwpL = false;
                    }

                    if ((GetKeyState(VK_RETURN) & 0x8000) && !enterPressed && !enterWasPressed) {
                        enterPressed = true;
                        enterWasPressed = true;
                    } else if (!(GetKeyState(VK_RETURN) & 0x8000)) {
                        enterPressed = false;
                        enterWasPressed = false;
                    }

                    Sleep(30);
                } while (!enterPressed && (prevNumber == number));

                if (number == 2 && enterPressed) {
                    enterPressed = false;
                    item = 30;
                    number = 1;
                    menu = 1;
                } else if (number == 3 && enterPressed && item < MaxInventorySize + 1) {
                    useItem(Inventory[item - 1]);
                    enterPressed = false;
                } else if (number == 3 && enterPressed && item >= MaxInventorySize + 1) {
                    invAvailable = false;
                    enterPressed = false;
                    unsigned short pos = posIn(Inventory, InventorySize, EquipmentInventory[item - (MaxInventorySize + 1)],
                                               sizeOfCString(EquipmentInventory[item - (MaxInventorySize + 1)]));
                    if (pos != 64464) {
                        InventoryCounts[pos]++;
                        for (short j = 0; j < sizeOfCString(EquipmentInventory[item - (MaxInventorySize + 1)]); j++) {
                            EquipmentInventory[item - (MaxInventorySize + 1)][j] = ' ';
                        }
                        invAvailable = true;

                        enterPressed = false;
                        item = 30;
                        number = 1;
                        menu = 1;
                    } else {
                        for (short i = 0; i < MaxInventorySize - InventorySize; i++) {
                            if (InventoryCounts[i] == 0) {
                                InventoryCounts[i]++;
                                for (short j = 0;
                                     j < sizeOfCString(EquipmentInventory[item - (MaxInventorySize + 1)]); j++) {
                                    Inventory[i][j] = EquipmentInventory[item - (MaxInventorySize + 1)][j];
                                    EquipmentInventory[item - (MaxInventorySize + 1)][j] = ' ';
                                }
                                invAvailable = true;

                                enterPressed = false;
                                item = 30;
                                number = 1;
                                menu = 1;

                                break;
                            }
                        }
                    }
                    if (!invAvailable) {
                        cout << "В инвентаре нет мест, складывать некуда\n" << endl;

                        printColorizedText("\n   $07 ок $70\n", 15);

                        do {
                            if ((GetKeyState(VK_RETURN) & 0x8000) && !enterPressed && !enterWasPressed) {
                                enterPressed = true;
                                enterWasPressed = true;
                            } else if (!(GetKeyState(VK_RETURN) & 0x8000)) {
                                enterPressed = false;
                                enterWasPressed = false;
                            }

                            Sleep(30);
                        } while (!enterPressed);
                        enterPressed = false;
                    }

                } else if (number == 4 && enterPressed) {
                    menu = 4;
                    enterPressed = false;
                } else if (number == 5 && enterPressed) {
                    itemInfo(item < MaxInventorySize + 1 ? Inventory[item - 1] : EquipmentInventory[item - (MaxInventorySize + 1)]);
                }
                break;
            }
            case 4: {
                cout << "\n\nСколько выкидывать? (0 или меньше для отмены; максимум или больше, чтобы выкинуть всё)\n>>";
                FlushConsoleInputBuffer(GetStdHandle(STD_INPUT_HANDLE));
                if (!(cin >> count)) {
                    cin.clear();
                    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                }

                if (count <= 0) {
                    number = 2;
                    enterPressed = false;
                    menu = 3;
                } else {
                    enterPressed = false;

                    if (item >= MaxInventorySize + 1) {
                        cout << "предмет '" << EquipmentInventory[item - (MaxInventorySize + 1)] << "' выкинут" << endl;
                        for (short i = 0; i < sizeOfCString(EquipmentInventory[item - (MaxInventorySize + 1)]); i++) {
                            EquipmentInventory[item - (MaxInventorySize + 1)][i] = ' ';
                        }
                        item = 30;
                    } else if (count >= InventoryCounts[item - 1]) {
                        cout << "все предметы '" << Inventory[item - 1] << "' выкинуты" << endl;
                        for (short i = 0; i < sizeOfCString(Inventory[item - 1]); i++) {
                            Inventory[item - 1][i] = ' ';
                        }
                        InventoryCounts[item - 1] = 0;
                        item = 30;
                    } else {
                        cout << "предмет '" << Inventory[item - 1] << "' x " << count << " выкинут" << endl;
                        InventoryCounts[item - 1] -= count;
                    }

                    printColorizedText("\n   $07 ок $70\n", 15);


                    do {
                        if ((GetKeyState(VK_RETURN) & 0x8000) && !enterPressed && !enterWasPressed) {
                            enterPressed = true;
                            enterWasPressed = true;
                        } else if (!(GetKeyState(VK_RETURN) & 0x8000)) {
                            enterPressed = false;
                            enterWasPressed = false;
                        }

                        Sleep(30);
                    } while (!enterPressed);

                    enterPressed = false;
                    if (item != 30) {
                        number = 2;
                        menu = 3;
                    } else {
                        number = 1;
                        menu = 1;
                    }
                }
                break;
            }
        }
    } while (number != 1 || !enterPressed);
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
