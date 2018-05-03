#ifndef __EFS_FRAGMENTDESCRIPTOR
#define __EFS_FRAGMENTDESCRIPTOR

#define FRAGMENT_DESC_SIZE 16

#include <stdint.h>

/**
 * Stores the location and size of a file fragment in units of pages.
 */
typedef struct efs_fragmentdescriptor
{
	/**
	 * The first page of the fragment, relative to the beginning of the
	 * partition.
	 */
	uint64_t fragmentLocation;
	
	/**
	 * The size of the fragment in pages.
	 */
	uint64_t fragmentSize;
} EFSFragmentDescriptor;

_Static_assert(sizeof(EFSFragmentDescriptor) == 16, 
	"The fragment descriptor data structure's size is wrong!");

#endif
