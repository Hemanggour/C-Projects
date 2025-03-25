#include <stdio.h>

#include "../Memory-Manager/memoryManager.c"

#include "./global.h"

#include "./utils.h"
#include "./encode.h"
#include "./decode.h"

void driver()
{
    char *inputBuffer = NULL;
    int choice;
    do
    {
        printf("\n0) EXIT\n1) Encode\n2) Decode\nSelect: ");
        fflush(stdin);
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            break;
        case 1:
            if (inputBuffer)
                MFree(inputBuffer);
            printf("Enter String For Encode: ");
            inputBuffer = input();
            checkAndResizeInputBuffer(inputBuffer);
            startEncode(inputBuffer);
            break;
        case 2:
            if (inputBuffer)
                MFree(inputBuffer);
            printf("Enter String For Decode: ");
            inputBuffer = input();
            checkAndResizeInputBuffer(inputBuffer);
            startDecode(inputBuffer);
            break;
        default:
            printf("Invalid choice\n");
            break;
        }
    } while (choice);
    // MFree(inputBuffer);
}

int main()
{
    driver();
    LeakInfo *leaks = MGetLeaks();
    for (size_t i = 0; i < leaks->leakCount; i++)
        printf("%d. addr: %p, size: %zu\n", i + 1, leaks[i].address, leaks[i].size);

    return EXIT_SUCCESS;
}