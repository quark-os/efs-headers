#ifndef __EFS_FILEDESCRIPTOR
#define __EFS_FILEDESCRIPTOR

#include <stdint.h>
#include <stddef.h>

#include "fragment_descriptor.h"
#include "config.h"

/**
 * A file descriptor, which provides all relevant information pertaining
 * to a single file, including where to find it within the filesystem. This
 * structure must have the same format as a file descriptor as it is
 * stored on disk.
 */
typedef struct efs_filedescriptor
{
	/**
	 * The page index this descriptor is located at.
	 */
	uint64_t descriptorLocation;
	
	/**
	 * A 64 bit integer uniquely identifying the file. Must be nonzero.
	 */
	uint64_t fileID;
	
	/**
	 * 1 if this is a real file; 0 if it is a directory. For symlinks,
	 * describes the file being linked to.
	 */
	uint64_t isFile : 1;
	
	/**
	 * 1 if this is a symlink. 0 otherwise.
	 */
	uint64_t isLink : 1;
	
	/**
	 * Read permission for the file owner.
	 */
	uint64_t ownerRead : 1;
	
	/**
	 * Write permisison for the file owner.
	 */
	uint64_t ownerWrite : 1;
	
	/**
	 * Execute permission for the file owner.
	 */
	uint64_t ownerExecute : 1;
	
	/**
	 * Read permission for the file's group.
	 */
	uint64_t groupRead : 1;
	
	/**
	 * Write permission for the file's group.
	 */
	uint64_t groupWrite : 1;
	
	/**
	 * Execute permission for the file's group.
	 */
	uint64_t groupExecute : 1;
	
	/**
	 * Read permission for all other users.
	 */
	uint64_t othersRead : 1;
	
	/**
	 * Write permission for all other users.
	 */
	uint64_t othersWrite : 1;
	
	/**
	 * Execute permission for all other users.
	 */
	uint64_t othersExecute : 1;
	
	/**
	 * Reserved space for future file attributes. Should just pad the
	 * attribute structure with zeroes so that it is exactly 8 bytes in
	 * size.
	 */
	uint64_t reserved_1 : 53;
	
	/**
	 * The parent of this file. Strictly speaking, this could be any file
	 * whatsoever, but a good implementation will ensure that only
	 * directories can be parents. If this is set to zero, the file is
	 * located in the root directory.
	 */
	uint64_t parentID;
	
	/**
	 * The size of the file in bytes. Must be zero for directories.
	 */
	uint64_t filesize;
	
	/**
	 * The time that this file was last accessed. Zero if unknown.
	 */
	uint64_t lastAccessed;
	
	/**
	 * The time that this file was last modified. Zero if unknown.
	 */
	uint64_t lastModified;
	
	/**
	 * UUID of the file's owner.
	 */
	uint64_t ownerUUID;
	
	/**
	 * UUID of the file's group.
	 */
	uint64_t groupUUID;
	
	/**
	 * Reserved for future use. Should pad to 1024 bytes into the
	 * structure.
	 */
	char reserved_2[1024 - (9*8)];
	
	/**
	 * A null-terminated string containing the name of the file,
	 * containing up to 1024 characters.
	 */
	char filename[1024];
	
	/**
	 * A sorted array containing every fragment of the file in order of
	 * where they appear in the file.
	 */
	EFSFragmentDescriptor fragments[128];
	
} EFSFileDescriptor;

/**
 * A file descriptor, which provides all relevant information pertaining
 * to a single file, including where to find it within the filesystem. In
 * contrast to \link efs_filedescriptor \endlink, this structure does not match its
 * corresponding page on disk, and arrays are not allocated within the
 * structure itself.
 */
typedef struct efs_compact_filedescriptor
{
	/**
	 * The page index this descriptor is located at.
	 */
	uint64_t descriptorLocation;
	
	/**
	 * A 64 bit integer uniquely identifying the file. Must be nonzero.
	 */
	uint64_t fileID;
	
	/**
	 * 1 if this is a real file; 0 if it is a directory.
	 */
	uint64_t isFile : 1;
	
	/**
	 * 1 if this is a symlink. 0 otherwise.
	 */
	uint64_t isLink : 1;
	
	/**
	 * Read permission for the file owner.
	 */
	uint64_t ownerRead : 1;
	
	/**
	 * Write permisison for the file owner.
	 */
	uint64_t ownerWrite : 1;
	
	/**
	 * Execute permission for the file owner.
	 */
	uint64_t ownerExecute : 1;
	
	/**
	 * Read permission for the file's group.
	 */
	uint64_t groupRead : 1;
	
	/**
	 * Write permission for the file's group.
	 */
	uint64_t groupWrite : 1;
	
	/**
	 * Execute permission for the file's group.
	 */
	uint64_t groupExecute : 1;
	
	/**
	 * Read permission for all other users.
	 */
	uint64_t othersRead : 1;
	
	/**
	 * Write permission for all other users.
	 */
	uint64_t othersWrite : 1;
	
	/**
	 * Execute permission for all other users.
	 */
	uint64_t othersExecute : 1;
	
	/**
	 * The parent of this file. Strictly speaking, this could be any file
	 * whatsoever, but a good implementation will ensure that only
	 * directories can be parents. If this is set to zero, the file is
	 * located in the root directory.
	 */
	uint64_t parentID;
	
	/**
	 * The size of the file in bytes. Must be zero for directories.
	 */
	uint64_t filesize;
	
	/**
	 * The time that this file was last accessed.
	 */
	uint64_t lastAccessed;
	
	/**
	 * The time that this file was last modified.
	 */
	uint64_t lastModified;
	
	/**
	 * UUID of the file's owner.
	 */
	uint64_t ownerUUID;
	
	/**
	 * UUID of the file's group.
	 */
	uint64_t groupUUID;
	
	/**
	 * A C-style strict containing the name of the file.
	 */
	char* filename;
	
	/**
	 * A sorted array containing every fragment of the file in order of
	 * where they appear in the file.
	 */
	EFSFragmentDescriptor* fragments;
	
	/**
	 * The number of elements stored in \link fragments \endlink.
	 */
	size_t numFragments;
	
} EFSCompactFileDescriptor;

_Static_assert(sizeof(EFSFileDescriptor) == PAGE_SIZE, 
	"The file descriptor data structure's size does not match the size of a page!");

#endif
