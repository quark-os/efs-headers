#ifndef __EFS_SUPERBLOCK
#define __EFS_SUPERBLOCK

#include <stdint.h>

#include "config.h"

/**
 * All of the data contained in the superblock of the filesystem. This
 * structure must have the same format as the superblock as it is stored
 * on the disk.
 */
typedef struct efs_superblock
{
	/**
	 * A magic number used to verify that this is actually a valid EFS.
	 * Should contain "E- FILESYSTEM SB".
	 */
	char magicNumber[16];
	
	/**
	 * A unique identifier for this filesystem. Should match the UUID
	 * stored in the partition table.
	 */
	char uuid[16];
	
	/**
	 * The first page (relative to the beginning of the partition) of the
	 * first node in the file descriptor table. This list is NOT sorted,
	 * so there may be nodes located before this one in the partition.
	 */
	uint64_t fileDescriptorTable;
	
	/**
	 * The first page (relative to the beginning of the partition) of the
	 * first node in the free space table. This list IS sorted, so they
	 * appear in the list in ascending order of their location in the
	 * partition.
	 */
	uint64_t freeSpaceTable;
	
	/**
	 * The size of the filesystem in units of pages.
	 */
	uint64_t filesystemSize;
	
	/**
	 * Reserved for future use.
	 */
	char reserved_1[1024 - 56];
	
	/**
	 * A null-terminated string containing the name of the filesystem.
	 * This should match what is stored in the partition table.
	 */
	char filesystemName[1024];
	
	/**
	 * Reserved for future use.
	 */
	char reserved_2[2048];
	
} EFSSuperblock;

/**
 * All of the data contained in the superblock of the filesystem. In
 * contrast to \link efs_superblock \endlink, this structure does not 
 * match its corresponding page on disk, and the filesystem name is not
 * allocated within the structure itself. This structure does NOT
 * contain the EFS magic number, because it is a constant.
 */
typedef struct efs_compact_superblock
{
	
	/**
	 * A unique identifier for this filesystem. Should match the UUID
	 * stored in the partition table.
	 */
	char uuid[16];
	
	/**
	 * The first page (relative to the beginning of the partition) of the
	 * first node in the file descriptor table. This list is NOT sorted,
	 * so there may be nodes located before this one in the partition.
	 */
	uint64_t fileDescriptorTable;
	
	/**
	 * The first page (relative to the beginning of the partition) of the
	 * first node in the free space table. This list IS sorted, so they
	 * appear in the list in ascending order of their location in the
	 * partition.
	 */
	uint64_t freeSpaceTable;
	
	/**
	 * The size of the filesystem in units of pages.
	 */
	uint64_t filesystemSize;
	
	/**
	 * A C-style string containing the name of the filesystem. This 
	 * should match what is stored in the partition table.
	 */
	char* filesystemName;
	
} EFSCompactSuperblock;

_Static_assert(sizeof(EFSSuperblock) == PAGE_SIZE, 
	"The superblock data structure's size does not match the size of a page!");

#endif
