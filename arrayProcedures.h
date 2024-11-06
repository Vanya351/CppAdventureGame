// isIn - check if there is a value in the array
bool isIn(char* arr, unsigned short size, char value);
bool isIn(unsigned char* arr, unsigned short size, unsigned char value);
bool isIn(char** arr, unsigned short size, char* value, unsigned short valueSize);
bool isIn(char** arr, unsigned short size, const char* value, unsigned short valueSize);
bool isIn(char arr[][44], unsigned short size, char* value, unsigned short valueSize);

bool isIn(wchar_t* arr, unsigned short size, wchar_t value);

// posIn - to get position of element in array
unsigned short posIn(char** arr, unsigned short size, char* value, unsigned short valueSize);
unsigned short posIn(char arr[][44], unsigned short size, char* value, unsigned short valueSize);

// Trim - to trim whitespace at end of C-style string
char* Trim(char* line, char symbol = ' ');

// sizeOfCString - to get size of C-style string
unsigned short sizeOfCString(char* line);
unsigned short sizeOfCString(const char* line);
unsigned short sizeOfCString(wchar_t* line);
unsigned short sizeOfCString(const wchar_t* line);

bool isSameStrings(char* line1, char* line2);
bool isSameStrings(char* line1, const char* line2);

void insertToString(char* line, char* value, unsigned short inputPos);
void insertToString(char* line, const char* value, unsigned short inputPos);

void replaceInColorizedString(char* line, char* value, unsigned short inputPos, unsigned wchars = 0, char colorDeterminant = '$');
void replaceInColorizedString(char* line, const char* value, unsigned short inputPos, unsigned wchars = 0, char colorDeterminant = '$');