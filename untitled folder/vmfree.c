#include <assert.h>
#include <stdint.h> 
#include <stdio.h> 
#include "vm.h"
#include "vmlib.h"
typedef struct block_header (block_header); 
typedef struct block_footer (block_footer); 

/**
 * The vmfree() function frees the memory space pointed to by ptr,
 * which must have been returned by a previous call to vmmalloc().
 * Otherwise, or if free(ptr) has already been called before,
 * undefined behavior occurs.
 * If ptr is NULL, no operation is performed.
 * vmfree() asserts that ptr is 8-byte aligned.
 */

inline int getSizeOf(const block_header* header){
    return BLKSZ(header); 
}

block_header* setPrev(const block_header* header){
    char* block = (char*) header; 
    const block_footer* footer = (block_footer*) (block - 4); 
    block -= footer->size; 
    return (block_header*) block; 
}

block_header* setNext(const block_header* header){
    char* block = (char*) header;
    block += getSizeOf(header); 
    return (block_header*) block; 
}

inline unsigned int prevIsFree(const block_header* header){
    return !(header->size_status & (1 << 1)); 
}

inline unsigned int isFree(const block_header* header){
    return !(header->size_status & 1); 
} 

void setFooter(const block_header* header){
    char* block = (char*) header;  
    block += (getSizeOf(header) - 4); 
    block_footer* footer = (block_footer*) block;
    footer->size = getSizeOf(header); 
}

void setBlockStatus(block_header* header, const unsigned int size, unsigned int prevTaken, const unsigned int thisTaken){
    const unsigned int status = (prevTaken << 1) | thisTaken; 
    const unsigned int size_status = size | status; 
    header->size_status = size_status; 
}

void vmfree(void *ptr)
{
    /* TODO: PA 6 */
    //CHECK STUFF
    printf("Freeing... \n"); 
    assert(((uint32_t) ptr) % 8 == 0); 
    if(ptr == NULL)
        return; 
    ptr -= 4; 
    block_header* header = (block_header*) ptr; 
    if(isFree(header))
        return; 
    
    //BEGIN COLLECTING SIZES
    unsigned int size = getSizeOf(header);    
    //GET NEXT BLOCK 
    block_header* next = setNext(header); 

    //GET PREVIOUS BLOCK IF NECESSARY
    if(prevIsFree(header)){
        header = setPrev(header); 
        size += getSizeOf(header); 
    }

    //GET NEW NEXT BLOCK IF NECESSARY
    if(isFree(next)){
        size += getSizeOf(next); 
        next = setNext(next); 
    }
    //SAVE HEADER'S PREVIOUS STATUS 
    const unsigned int prevStatus = prevIsFree(header); 

    //SET STATUS 
    setBlockStatus(header, size, prevStatus, 0); 

    //SET FOOTER
    setFooter(header); 
}
