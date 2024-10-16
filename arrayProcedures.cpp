#include "arrayProcedures.h"

bool isIn(short* arr, unsigned short* size, short* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(unsigned short* arr, unsigned short* size, unsigned short* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(int* arr, unsigned short* size, int* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(unsigned int* arr, unsigned short* size, unsigned int* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(long int* arr, unsigned short* size, long int* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(unsigned long int* arr, unsigned short* size, unsigned long int* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(long long int* arr, unsigned short* size, long long int* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(unsigned long long int* arr, unsigned short* size, unsigned long long int* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(float* arr, unsigned short* size, float* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(double* arr, unsigned short* size, double* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(long double* arr, unsigned short* size, long double* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(char* arr, unsigned short* size, char* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}

bool isIn(unsigned char* arr, unsigned short* size, unsigned char* value) {
    for (int i = 0; i < *size; i++) {
        if (arr[i] == *value) return true;
    }
    return false;
}