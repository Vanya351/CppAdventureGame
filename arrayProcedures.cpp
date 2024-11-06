#include "arrayProcedures.h"

bool isIn(char* arr, unsigned short size, char value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(unsigned char* arr, unsigned short size, unsigned char value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(char** arr, unsigned short size, char* value, unsigned short valueSize) {
    bool cond;
    for (unsigned short i = 0; i < size; i++) {
        cond = true;
        for (int j = 0; j < valueSize; ++j) {
            cond = cond && (arr[i][j] == value[j]);
        }
        if (cond) return true;
    }
    return false;
}

bool isIn(char** arr, unsigned short size, const char* value, unsigned short valueSize) {
    bool cond;
    for (unsigned short i = 0; i < size; i++) {
        cond = true;
        for (int j = 0; j < valueSize; ++j) {
            if (arr[i][j] == '\0') {
                break;
            }
            cond = cond && (arr[i][j] == value[j]);
        }
        if (cond) return true;
    }
    return false;
}

bool isIn(char arr[][44], unsigned short size, const char* value, unsigned short valueSize) {
    bool cond;
    for (unsigned short i = 0; i < size; i++) {
        cond = true;
        for (int j = 0; j < valueSize; ++j) {
            cond = cond && (arr[i][j] == value[j]);
        }
        if (cond) return true;
    }
    return false;
}

bool isIn(wchar_t* arr, unsigned short size, wchar_t value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}


unsigned short posIn(char** arr, unsigned short size, char* value, unsigned short valueSize) {
    bool cond;
    for (unsigned short i = 0; i < size; i++) {
        cond = true;
        for (int j = 0; j < valueSize; ++j) {
            cond = cond && (arr[i][j] == value[j]);
        }
        if (cond) return i;
    }
    return 64464;
}

unsigned short posIn(char arr[][44], unsigned short size, char* value, unsigned short valueSize) {
    bool cond;
    for (unsigned short i = 0; i < size; i++) {
        cond = true;
        for (int j = 0; j < valueSize; ++j) {
            cond = cond && (arr[i][j] == value[j]);
        }
        if (cond) return i;
    }
    return 64464;
}


char* Trim(char* line, char symbol) {
    short i = 0, pos = 0;
    while (line[i] != '\0') {
        if (line[i] != symbol) {
            pos = i + 1;
        }
        i++;
    }

    char *newLine = new char[pos + 1];
    for (i = 0; i < pos; i++) {
        newLine[i] = line[i];
    }
    newLine[pos] = '\0';

    return newLine;
}

unsigned short sizeOfCString(char* line) {
    short i = 0;
    while (line[i] != '\0') {
        i++;
    }
    return i;
}

unsigned short sizeOfCString(const char* line) {
    short i = 0;
    while (line[i] != '\0') {
        i++;
    }
    return i;
}

unsigned short sizeOfCString(wchar_t* line) {
    short i = 0;
    while (line[i] != L'\0') {
        i++;
    }
    return i;
}

unsigned short sizeOfCString(const wchar_t* line) {
    short i = 0;
    while (line[i] != L'\0') {
        i++;
    }
    return i;
}

bool isSameStrings(char* line1, char* line2) {
    unsigned short size1, size2;
    size1 = sizeOfCString(line1);
    size2 = sizeOfCString(line2);
    bool cond = true;
    if (size1 == size2) {
        for (short i = 0; i < size1; i++) {
            cond = cond && (line1[i] == line2[i]);
            if (!cond) break;
        }
    } else {
        cond = false;
    }
    return cond;
}

bool isSameStrings(char* line1, const char* line2) {
    unsigned short size1, size2;
    size1 = sizeOfCString(line1);
    size2 = sizeOfCString(line2);
    bool cond = true;
    if (size1 == size2) {
        for (short i = 0; i < size1; i++) {
            cond = (line1[i] == line2[i]);
            if (!cond) break;
        }
    } else {
        cond = false;
    }
    return cond;
}

void insertToString(char* line, char* value, unsigned short inputPos) {
    unsigned short sizeLine = sizeOfCString(line), sizeValue = sizeOfCString(value), inputSize = 0, i;

    for (i = sizeLine; i >= inputPos; i--) {
        line[i + sizeValue] = line[i];
    }

    for (i = inputPos; i < sizeValue + inputPos; i++) {
        line[i] = value[i - inputPos];
    }
}


void insertToString(char* line, const char* value, unsigned short inputPos) {
    unsigned short sizeLine = sizeOfCString(line), sizeValue = sizeOfCString(value), inputSize = 0, i;

    for (i = sizeLine; i >= inputPos; i--) {
        line[i + sizeValue] = line[i];
    }

    for (i = inputPos; i < sizeValue + inputPos; i++) {
        line[i] = value[i - inputPos];
    }
}

void replaceInColorizedString(char* line, char* value, unsigned short inputPos, unsigned wchars, char colorDeterminant) {
    short shift = wchars;
    unsigned short i, sizeLine = sizeOfCString(line), sizeValue = sizeOfCString(value);
    char colorSet[] = {"0123456789ABCDEF"};

    for (i = 0; i < sizeValue; i++) {
        if (value[i] == colorDeterminant && isIn(colorSet, 16, value[i + 1])) {
            shift += 3;
            i += 2;
        }
    }

    for (i = sizeLine; i >= inputPos; i--) {
        line[i + shift] = line[i];
    }

    for (i = inputPos; i < inputPos + sizeValue; i++) {
        line[i] = value[i - inputPos];
    }
}

void replaceInColorizedString(char* line, const char* value, unsigned short inputPos, unsigned wchars, char colorDeterminant) {
    short shift = wchars;
    unsigned short i,sizeLine = sizeOfCString(line), sizeValue = sizeOfCString(value) ;
    char colorSet[] = {"0123456789ABCDEF"};

    for (i = 0; i < sizeValue; i++) {
        if (value[i] == colorDeterminant && isIn(colorSet, 16, value[i + 1])) {
            shift += 3;
            i += 2;
        }
    }

    for (i = sizeLine; i >= inputPos; i--) {
        line[i + shift] = line[i];
    }

    for (i = inputPos; i < inputPos + sizeValue; i++) {
        line[i] = value[i - inputPos];
    }
}