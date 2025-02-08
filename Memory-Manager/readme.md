# Memory Management System

## Overview
This project implements a simple memory management system in C, providing custom memory allocation and deallocation functions to track allocated memory blocks. It includes the following functionalities:

- `MMalloc(size_t size)`: Allocates memory and tracks it.
- `MFree(void* ptr)`: Frees a specific allocated memory block.
- `MFreeAll()`: Frees all allocated memory blocks.

## File Structure
```
Memory-Manager/
│── memoryManager.c     # Contains memory management functions
│── tests.c             # Contains test cases for memory management
│── main.c              # (Optional) Entry point for testing
│── README.md           # Documentation
```

## Implementation Details
### memoryManager.c
This file contains the implementation of memory management functions:
- `MemoryBlock` struct: Stores metadata about allocated memory.
- `getMemoryBlock()`: Allocates memory for a new block.
- `MMalloc(size_t size)`: Custom memory allocation function.
- `MFree(void* ptr)`: Frees a specific memory block.
- `MFreeAll()`: Frees all allocated memory blocks.

### tests.c
This file contains test cases to validate the functionality of the memory manager.

## Usage
To use the memory manager, include `memoryManager.c` in your program:
```c
#include "memoryManager.c"
```
Compile and run:
```sh
gcc tests.c -o tests
./tests
```

## Example Usage
```c
#include "memoryManager.c"

int main() {
    int* arr = (int*)MMalloc(5 * sizeof(int));
    if (arr) {
        for (int i = 0; i < 5; i++)
            arr[i] = i;
    }
    MFree(arr);
    MFreeAll();
    return 0;
}
```

## Notes
- Ensure proper use of `MFree()` and `MFreeAll()` to prevent memory leaks.
- The `MFree()` and `MFreeAll()` functions returns a status code __0__ and __1__.
- _0_ for Failed to free memory and _1_ for successfully freed memory.

## License
This project is open-source and free to use under the MIT License.