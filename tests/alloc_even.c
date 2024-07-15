/* a few allocations of even sizes */
#include "vmlib.h"
#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h> 

int main()
{
    vminit(1024);

    int *ptr[5];

    //printf("1\n"); 
    ptr[0] = (int *)vmalloc(2);
        
    //printf("2\n"); 
    ptr[1] = (int *)vmalloc(6);
        
    //printf("3\n"); 
    ptr[2] = (int *)vmalloc(900);
       
    //printf("4\n"); 
    ptr[3] = (int *)vmalloc(80);
        
    //printf("5\n"); 
    ptr[4] = (int *)vmalloc(12);

    for (int i = 0; i < 5; i++) {
        assert(ptr[i] != NULL);
        assert(((uint32_t)ptr[i]) % 8 == 0);
    }
    vminfo(); 
    vmdestroy();
}
