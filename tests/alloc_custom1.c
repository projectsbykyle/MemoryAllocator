#include "vmlib.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    vmload("../dumps/ref_image4");
    vminfo(); 

    void *ptr = vmalloc(300);
   void *ptr2 = vmalloc(512);
    void *ptr3 = vmalloc(400);
    void *ptr4 = vmalloc(160);

    //assert(ptr != NULL && ptr2 != NULL && ptr3 != NULL && ptr4 != NULL);

    // check pointer offsets
    printf("PTR: %d\n", (uint32_t)(ptr2 - ptr)); 
    //printf("PTR2: %d\n", (uint32_t)(ptr2)); 
    //printf("PTR3: %d\n", (uint32_t)(ptr3)); 
    //printf("PTR4: %d\n", (uint32_t)(ptr4)); 
    //vmdump("dumps/out"); 
    vminfo(); 
   // assert((uint32_t)(ptr2-ptr) == 1512);
    //assert((uint32_t)(ptr3-ptr) == 2032);
    //assert((uint32_t)(ptr4-ptr) == 304);

 //   vminfo(); 
    vmdestroy();
}
