// isIn - check if there is a value in the array
bool isIn(short* arr, unsigned short size, short value);
bool isIn(unsigned short* arr, unsigned short size, unsigned short value);
bool isIn(int* arr, unsigned short size, int value);
bool isIn(unsigned int* arr, unsigned short size, unsigned int value);
bool isIn(long int* arr, unsigned short size, long int value);
bool isIn(unsigned long int* arr, unsigned short size, unsigned long int value);
bool isIn(long long int* arr, unsigned short size, long long int value);
bool isIn(unsigned long long int* arr, unsigned short size, unsigned long long int value);

bool isIn(float* arr, unsigned short size, float value);
bool isIn(double* arr, unsigned short size, double value);
bool isIn(long double* arr, unsigned short size, long double value);

bool isIn(char* arr, unsigned short size, char value);
bool isIn(unsigned char* arr, unsigned short size, unsigned char value);
bool isIn(char** arr, unsigned short size, char* value, unsigned short valueSize);
bool isIn(char** arr, unsigned short size, const char* value, unsigned short valueSize);
bool isIn(char arr[][44], unsigned short size, char* value, unsigned short valueSize);

// posIn - to get position of element in array
unsigned short posIn(char** arr, unsigned short size, char* value, unsigned short valueSize);
unsigned short posIn(char arr[][44], unsigned short size, char* value, unsigned short valueSize);

// Trim - to trim whitespace at end of C-style string
char* Trim(char* line, char symbol = ' ');

// sizeOfCString - to get size of C-style string
unsigned short sizeOfCString(char* line);
unsigned short sizeOfCString(const char* line);

// isSameStrings (guess what it does)
bool isSameStrings(char* line1, char* line2);
bool isSameStrings(char* line1, const char* line2);