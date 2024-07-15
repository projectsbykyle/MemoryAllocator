#include "vm.h"
#include "vmlib.h"
#include <stdio.h> 
#define MAX (2147483647) 
typedef struct block_header block_header; 

/**
 * The malloc() function allocates size bytes and returns a pointer
 * to the allocated memory (payload). The memory is not initialized.
 * If size is 0, or if no available heap memory could be allocated,
 * malloc returns NULL.
 */

//Check if we are at last block
inline int isEndMark(const block_header* block){
    return (block->size_status == VM_ENDMARK); 
}

//Get size of current block
unsigned int getSize(const block_header* block){
    return BLKSZ(block); 
}

//Set a block to its next block
block_header* nextBlock(block_header* block){
    const unsigned int size = getSize(block); 
    char* b = (char*) block; 
    char* next = (char*) b + size; 
    return (block_header*) next; 
}

//Set block size of current block (to be called inside markSizeStatus)
void setBlockSize(block_header* block, const size_t size, int prev, const int thisTaken){
    const int status = (prev << 1) | thisTaken;
    block->size_status = size | status; 
}

//Mark the size and status of current block, split if necessary
void markSizeStatus(block_header* block, int prevTaken, const size_t size){
    char* n = ((char*) block) + size; 
    block_header* next = (block_header*) n; 
    const size_t nextBlockSize = (getSize(block) > size) ? getSize(block) - size : getSize(next); 
    if(!isEndMark(next))
        setBlockSize(next, nextBlockSize, 1, (next->size_status & 1)); 
    setBlockSize(block, size, prevTaken, 1);
}

//Check if current block is used
inline int inUse(block_header* block){
    return (block->size_status & 1); 
}

//Check if previous block is used
inline int getPrevStatus(block_header* block){
    return (block->size_status & 2) >> 1; 
}

void *vmalloc(size_t size)
{
    if(size == 0)
        return NULL; 
    /* TODO: PA 5 */
    //Round size to nearest multiple of 8 
    size = size + 4; 
    const size_t blockSize = ROUND_UP(size, 8);

    //Start at first block header
    block_header* curr = heapstart, *result = NULL; 
    unsigned int max = MAX, prevStatus = 1; 

    //Loop through list, find best fit block; 
    while(!isEndMark(curr)){
        //Only check if block is free
        if(!inUse(curr)){
            const unsigned int size = getSize(curr); 
            if(size >= blockSize && size < max){
                result = curr; 
                prevStatus = getPrevStatus(curr); 
                max = size; 
            }
        }
        curr = nextBlock(curr); 
    }

    //If no blocks are found, return NULL
    if(result == NULL)
        return NULL; 
    else
        markSizeStatus(result, prevStatus, blockSize); 
  
    //Return 
    char* n = (char*) result; 
    n += 4; 
    void* finalPtr = (void*) n; 

    return finalPtr; 
}
