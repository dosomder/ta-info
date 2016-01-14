#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <io.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

#include "utility.h"
#include "trimareainfo.h"
#include "win.h"

struct argument
{
	char* inputFile;
	int TAUnit;
	int partition;
	int outputMode;
};
static struct argument args;

void arginit()
{
	args.inputFile = NULL;
	args.TAUnit = 0;
	args.partition = -1;
	args.outputMode = OUTPUT_BYTE;
}

int argparse(int argc, char* argv[])
{
	int i;
	int ret = 1;
	if(argc < 2)
	{
		fprintf(stderr, "Please specify a TA file to open\n");
		return 0;
	}
	arginit();
	args.inputFile = argv[1];

	for(i = 2;i < argc; i++)
	{
		//options
		if(strcmp(argv[i], "-c") == 0 && ret++)
			args.outputMode = OUTPUT_CHAR;

		if(++i == argc)
			break;
		
		//parameters
		if(strcmp(argv[i-1], "-u") == 0 && ret++)
			args.TAUnit = strtol(argv[i], NULL, 0);
		else if(strcmp(argv[i-1], "-p") == 0 && ret++)
			args.partition = strtol(argv[i], NULL, 0);

	}
	return ret;
}

int main(int argc, char* argv[])
{
	int tafd = -1;
	void* fptr = NULL;
	if(argparse(argc, argv) == 0)
		return 1;

	tafd = open(args.inputFile, O_RDONLY | O_BINARY);
	if(tafd < 0)
	{
		perror("Error opening TA file");
		return tafd;
	}
	fptr = readFileToMemory(tafd);
	if(fptr == NULL)
		goto End;

	if(args.TAUnit == 0)
		TAPrintCommonInfo((unsigned char*)fptr, _filelength(tafd));
	else
		TAReadUnit((unsigned char*)fptr, _filelength(tafd), args.TAUnit, args.partition, args.outputMode);


	releaseMappedMemory(fptr, _filelength(tafd));
End:
	close(tafd);
	return 0;
}