#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <errno.h>

#include "win.h"

#ifdef WIN32
#include <Windows.h>
#elif __linux__
#include <sys/mman.h>
#endif

int getFileSize(int fd)
{
	off_t old = lseek(fd, 0, SEEK_CUR);
	off_t size = lseek(fd, 0, SEEK_END);
	lseek(fd, old, SEEK_SET);
	return size;
}

void releaseMappedMemory(void* ptr, unsigned int len)
{
#ifdef WIN32
	VirtualFree(ptr, 0, MEM_RELEASE);
#elif __linux__
	munmap(ptr, len);
#endif
}

void* readFileToMemory(int fd)
{
	long filesize = getFileSize(fd);
#ifdef WIN32
	void* fptr = VirtualAlloc(NULL, filesize, MEM_COMMIT, PAGE_READWRITE);
#elif __linux__
	void* fptr = mmap(NULL, filesize, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
#endif
	if(fptr == NULL)
	{
#ifdef WIN32
		fprintf(stderr, "Unable to allocate memory: %d\n", GetLastError());
#elif __linux__
		fprintf(stderr, "Unable to allocate memory: %s\n", strerror(errno));
#endif
		return NULL;
	}

#ifdef WIN32
	if(read(fd, fptr, filesize) != filesize)
	{
		fprintf(stderr, "Unable to read file into memory\n");
		releaseMappedMemory(fptr, filesize);
		return NULL;
	}
#endif

	return fptr;
}