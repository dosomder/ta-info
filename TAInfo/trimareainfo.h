#ifndef TA_TRIMAREAINFO_H
#define TA_TRIMAREAINFO_H

void TAReadUnit(unsigned char* ptr, unsigned int len, unsigned int unitNumber, int partition, int outputMode);
void TAPrintCommonInfo(unsigned char* ptr, unsigned int len);
char* getTAPartitionName(int partitionType);

#endif /* TA_TRIMAREAINFO_H */
