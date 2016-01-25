#ifndef TA_UTILITY_H
#define TA_UTILITY_H

#define OUTPUT_BYTE 1
#define OUTPUT_CHAR 2

int getFileSize(int fd);
void releaseMappedMemory(void* ptr, unsigned int len);
void* readFileToMemory(int fd);

#endif /* TA_UTILITY_H */
