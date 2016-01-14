#define OUTPUT_BYTE 1
#define OUTPUT_CHAR 2

void releaseMappedMemory(void* ptr, unsigned int len);
void* readFileToMemory(int fd);