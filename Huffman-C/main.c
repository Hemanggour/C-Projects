#include <stdio.h>

#include "../Memory-Manager/memoryManager.h"

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

    size_t leakCount = 0;
    LeakInfo *leaks = getLeaks(&leakCount);

    if (leaks)
    {
        for (size_t i = 0; i < leakCount; i++)
        {
            printf("Leak %zu: Address = %p, Size = %zu bytes\n",
                i + 1, leaks[i].address, leaks[i].size);
        }

        MFreeLeakInfo(leaks);
    }
    else
    {
        printf("No memory leaks detected.\n");
    }

    return EXIT_SUCCESS;
}