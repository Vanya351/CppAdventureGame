#include "arrayProcedures.h"

bool isIn(short* arr, unsigned short size, short value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(unsigned short* arr, unsigned short size, unsigned short value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(int* arr, unsigned short size, int value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(unsigned int* arr, unsigned short size, unsigned int value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(long int* arr, unsigned short size, long int value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(unsigned long int* arr, unsigned short size, unsigned long int value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(long long int* arr, unsigned short size, long long int value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(unsigned long long int* arr, unsigned short size, unsigned long long int value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(float* arr, unsigned short size, float value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(double* arr, unsigned short size, double value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

bool isIn(long double* arr, unsigned short size, long double value) {
    for (unsigned short i = 0; i < size; i++) {
        if (arr[i] == value) return true;
    }
    return false;
}

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
            cond = cond && (line1[i] == line2[i]);
            if (!cond) break;
        }
    } else {
        cond = false;
    }
    return cond;
}