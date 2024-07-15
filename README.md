# Dynamic Memory Allocation Project

## Description:

This is a basic dynamic memory manager implemented using C. We implement the <ins>malloc</ins> and <ins>free</ins> methods and allow the user to allocate an arbitrary amount of bytes to the heap.
The blocks of available memory are stored as a freelist using a linked list format. We also use techniques such as coalescing and rounding the user specificed memory amount to the next multiple of 8-bytes
to ensure efficient storage and pointer lookup. 
