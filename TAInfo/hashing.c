#include <stdio.h>

//from zlib
#define BASE 65521
#define NMAX 5552
unsigned int CalcAdler32(unsigned char* buffer, unsigned int len)
{
	int k = 0;
	unsigned int s1 = 1;
	unsigned int s2 = 0;

	while(len)
	{
		k = len > NMAX ? NMAX : len;
		len -= k;

		if(k != 0)
		do
		{
			s1 += *buffer++;
			s2 += s1;
		} while(--k);

		s1 %= BASE;
        s2 %= BASE;
	}

	return (s2 << 16) | s1;
}