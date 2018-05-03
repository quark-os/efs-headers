#ifndef __EFS_FILEDESCRIPTOR_NODE
#define __EFS_FILEDESCRIPTOR_NODE

#include <stdint.h>

#include "config.h"

/**
 * The header for each node in the file descriptor list. File descriptors
 * are stored in an unrolled linked list. The fist element in each node
 * should contain this structure, and the rest should contain
 * EFSFileDescriptor structures.
 */
typedef struct efs_filedescriptornode
{
	/**
	 * The page at which the next node in the list is located.
	 */
	uint64_t next;
	
	/**
	 * The number of file descriptors being used in the array. The number
	 * of availabel spaces for new descriptors is
	 * (255 - numFileDescriptors).
	 */
	uint64_t numFileDescriptors;
	
	/**
	 * Reserved for future use. Ensures that the data structure matches
	 * what will be stored on disk.
	 */
	char reserved[4096 - 16];
	
} EFSFileDescriptorNode;

_Static_assert(sizeof(EFSFileDescriptorNode) == PAGE_SIZE, 
	"The file descriptor node data structure's size does not match the size of a page!");

#endif
