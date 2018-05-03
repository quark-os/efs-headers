#ifndef __EFS_FREESPACE_NODE
#define __EFS_FREESPACE_NODE

/**
 * A strucutre storing the size of a region of available space on the
 * disk (including the structure itself), and the location of the next
 * region of available space;
 */
typedef struct efs_freespacenode
{
	/**
	 * The location in pages, relative to the beginning of the 
	 * partition, of the next region of available space.
	 */
	uint64_t next;
	
	/**
	 * The size of the current region in pages, including the page
	 * storing this structure.
	 */
	uint64_t size;
	
	/**
	 * Reserved for future use.
	 */
	char reserved[4096 - 16];
	
} EFSFreeSpaceNode;

#endif
