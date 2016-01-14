#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trimarea.h"
#include "trimareainfo.h"
#include "utility.h"

void TAReadUnit(unsigned char* ptr, unsigned int len, unsigned int unitNumber, int partition, int outputMode)
{
	struct TAUnitHdr* hdr = NULL;
	unsigned int i = 0;
	if(unitNumber == 0)
		return;

	if(ParseTAImage(ptr, len) != 0)
		return;

	hdr = findTAUnit(unitNumber, partition);
	if(hdr == NULL)
		return;

	printf("Unit Size is %d\n", hdr->length);
	printf("Partition is %s\n", getTAPartitionName(getPartitionFromUnit(hdr)));

	switch (outputMode)
	{
	case OUTPUT_BYTE:
	default:
		for (i = 0; i < hdr->length; i++)
		{
			//if (i > 0) printf(":");
			printf("%02X", ((unsigned char*)(hdr + 1))[i]);
		}
		break;
	case OUTPUT_CHAR:
		{
			char* strbuf = (char*)malloc(hdr->length + 1);
			strbuf[hdr->length] = 0;
			memcpy(strbuf, hdr + 1, hdr->length);
			printf(strbuf);
			free(strbuf);
		}
		break;
	}

	printf("\n");
}

void TAPrintCommonInfo(unsigned char* ptr, unsigned int len)
{
	int partition = TRIMAREA_PARTITION_TRIM;
	int part = 0;
	int partcount = 0;
	struct TAPartitionHdr* phdr = NULL;
	if(ParseTAImage(ptr, len) != 0)
		return;

	for( ; partition < TRIMAREA_PARTITION_ENDMARKER; partition++)
	{
		partcount = getTAPartitionPartCount(partition);
		if(partcount == 0)
			continue;

		printf("Name:			%s\n", getTAPartitionName(partition));
		printf("Parts:			%d\n", partcount);
		for(part = 0; part < partcount; part++)
		{
			phdr = getTAPartitionHeader(partition, part);
			if(phdr == NULL)
				continue;
			printf("Part [%d]\n", part);
			printf("Size:			%d\n", getTAPartitionSize(phdr));
			printf("Saved checksum:		%#010X\n", phdr->hash);
			printf("Calculated checksum:	%#010X\n", calcTAPartitionHash(phdr));
			printf("\n");
		}
	}
}

char* getTAPartitionName(int partitionType)
{
	switch (partitionType)
	{
	case TRIMAREA_PARTITION_TRIM:
		return "Trim";
	case TRIMAREA_PARTITION_MISC:
		return "Misc";
	default:
		return NULL;
	}
}