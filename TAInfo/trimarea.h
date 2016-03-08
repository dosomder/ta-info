#ifndef TA_TRIMAREA_H
#define TA_TRIMAREA_H

#define TA_MAGIC 0x3BF8E9C1 
#define TA_FILE_BLOCK_SIZE 128 //128kb
#define TA_PARTITION_MAX_SIZE 0x20000 //same as TA_FILE_BLOCK_SIZE
#define TA_PARTITION_BLOCK_SIZE 2048

//partition types
#define TRIMAREA_PARTITION_TRIM 1
#define TRIMAREA_PARTITION_MISC 2
#define TRIMAREA_PARTITION_ENDMARKER 3

//TA units
//When a modem is flashed, nv units are read from trim partition
//most of nv units are overwritten by the baseband config located in amss_fsg or in system/etc/customization/modem/
#define TA_UNIT_1_RF_BC_CFG 0x755
#define TA_UNIT_1_LTE_BC_CFG 0x1AAC

#define TA_UNIT_2_FLA_FLA 0x7D2 //what is flafla?
#define TA_UNIT_2_S1_LDR 0x7D3 //hw conf
#define TA_UNIT_2_SENS_DATA 0x7DA //simlock / bootloader unlock allowed, etc.
#define TA_UNIT_2_DRM_KEY_STATUS 0x7E5
#define TA_UNIT_2_BLOB_0 0x7E6 //marlin
#define TA_UNIT_2_BLOB_1 0x7E7 //ckb
#define TA_UNIT_2_BLOB_2 0x7E8 //widevine
#define TA_UNIT_2_BLOB_3 0x7E9
#define TA_UNIT_2_BLOB_4 0x7EA
#define TA_UNIT_2_BLOB_5 0x7EB
#define TA_UNIT_2_BLOB_6 0x7EC
#define TA_UNIT_2_BLOB_7 0x7ED
#define TA_UNIT_2_BLOB_8 0x7EE
#define TA_UNIT_2_BLOB_9 0x7EF
#define TA_UNIT_2_BLOB_A 0x7F0
#define TA_UNIT_2_BLOB_B 0x7F1
#define TA_UNIT_2_BLOB_C 0x7F2
#define TA_UNIT_2_BLOB_D 0x7F3
#define TA_UNIT_2_BLOB_E 0x7F4
#define TA_UNIT_2_SRM 0x7F8
#define TA_UNIT_2_LAST_BOOT_LOG 0x802
#define TA_UNIT_2_MACHINE_ID 0x85D
#define TA_UNIT_2_SW_VER 0x89A
#define TA_UNIT_2_CUST_VER 0x89D
#define TA_UNIT_2_FS_VER 0x89E
#define TA_UNIT_2_S1_BOOT_VER 0x89F
#define TA_UNIT_2_BUILD_TYPE 0x8A1
#define TA_UNIT_2_PHONE_NAME 0x8A2
#define TA_UNIT_2_AC_VER 0x8A4 //cust-reset.ta zeroes this
#define TA_UNIT_2_BL_UNLOCKCODE 0x8B2
#define TA_UNIT_2_STARTUP_SHUTDOWNRESULT 0x8B3
#define TA_UNIT_2_STARTUP_REASON 0x8FD //"override unit"
#define TA_UNIT_2_DISABLE_CHARGE_ONLY 0x907
#define TA_UNIT_2_OSV_RESTRICTION 0x91A
#define TA_UNIT_2_MODEM_CUST_CFG 0x964 //FOTA_INTERNAL ?? cfg located in system/etc/customization/modem/ -> fota-reset.ta zeroes this
#define TA_UNIT_2_FLASH_LOG 0x9AB
#define TA_UNIT_2_ENABLE_NONSECURE_USB_DEBUG 0x9B6
#define TA_UNIT_2_CREDMGR_KEYTABLE_PRESET 0x9C4
#define TA_UNIT_2_BASEBAND_CFG 0x9F7 //cfg located in the modem
#define TA_UNIT_2_WIFI_MAC 0xA00
#define TA_UNIT_2_BLUETOOTH_MAC 0xA08
#define TA_UNIT_2_SERIAL_NO 0x1324
#define TA_UNIT_2_PBA_ID 0x1325
#define TA_UNIT_2_PBA_ID_REV 0x1326
#define TA_UNIT_2_PP_SEMC_ITP_PRODUCT_NO 0x132C
#define TA_UNIT_2_PP_SEMC_ITP_REV 0x132D
#define TA_UNIT_2_DEVICE_KEY 0x1046B
#define TA_UNIT_2_REMOTE_LOCK 0x1046C //a sin file

struct TAUnitHdr
{
	unsigned int unitNumber;
	unsigned int length;
	unsigned int magic;
	unsigned int unknown; //mostly 0xFFFFFFFF
	//if the unit is modified with the same size, the last byte is set to 0x11
	//if the unit is newly added, last byte is set to 0x14
	//if a unit is deleted, all is set to 0x15151515
};

struct TAPartitionHdr
{
	unsigned int magic;
	unsigned int hash;
	char unknown; //seems to be the same as partitionnumber
	char partnumber;
	char partitionnumber;
	unsigned char numblocks;
};

unsigned int getTAPartitionPartSize(struct TAPartitionHdr* hdr);
int getPartitionFromUnit(struct TAUnitHdr* hdr);
unsigned int calcTAPartitionHash(struct TAPartitionHdr* hdr);
int getTAUnitCount(struct TAPartitionHdr* hdr);
int getTAPartitionPartCount(int partitionType);
struct TAPartitionHdr* getTAPartitionHeader(int partitionType, int partcount);
struct TAUnitHdr* findTAUnit(unsigned int unitNum, int partition);
int ParseTAImage(unsigned char* ptr, unsigned int len);

#endif /* TA_TRIMAREA_H */
