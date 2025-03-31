#include <stdio.h>
#include <stdlib.h>

int *inisialise(int size)
{
    int *arr = NULL;
    arr = (int *)malloc(size * sizeof(int));
    return arr;
}

void insert(int arr[], int size)
{
    if (size == 0)
    {
        printf("Please define array size first!!\nPress (11)\n");
    }

    else
    {
        for (int i = 0; i < size; i++)
        {
            printf("Enter element at %d : ", i);
            scanf("%d", &arr[i]);
        }
    }
}

int insert_at_pos(int arr[], int size)
{
    int pos, el;

    if (size == 0)
    {
        printf("Please define array size first!!\nPress (11)\n");
    }

    else
    {
    position:
        printf("Enter position for element : ");
        scanf("%d", &pos);

        if (pos > size || pos <= 0)
        {
            printf("Invalid position!!\n");
            goto position;
        }

        else
        {
            printf("Enter element to be inserted : ");
            scanf("%d", &el);

            size++;

            arr = (int *)realloc(arr, size * sizeof(int));

            for (int i = size - 2; i >= pos - 1; i--)
            {
                arr[i + 1] = arr[i];
            }

            arr[pos - 1] = el;
        }
    }
    return size;
}

int insert_at_first(int arr[], int size)
{
    int el;

    if (size == 0)
    {
        printf("Please define array size first!!\nPress (11)\n");
    }

    else
    {

        printf("Enter element to be inserted at first : ");
        scanf("%d", &el);

        size++;

        arr = (int *)realloc(arr, size * sizeof(int));

        for (int i = size - 2; i >= 0; i--)
        {
            arr[i + 1] = arr[i];
        }

        arr[0] = el;
    }
    return size;
}

int insert_at_last(int arr[], int size)
{
    int el;

    if (size == 0)
    {
        printf("Please define array size first!!\nPress (11)\n");
    }

    else
    {
        printf("Enter element to be inserted at last : ");
        scanf("%d", &el);

        size++;

        arr = (int *)realloc(arr, size * sizeof(int));

        arr[size - 1] = el;
    }
    return size;
}

void traverse(int arr[], int size)
{
    if (size == 0)
    {
        printf("Please define array size first!!\nPress (11)\n");
    }

    else
    {
        for (int i = 0; i < size; i++)
        {
            printf("Element at %d : %d\n", i, arr[i]);
        }
    }
}

void sort(int arr[], int size)
{
    int temp;

    if (size == 0)
    {
        printf("Please define array size first!!\nPress (11)\n");
    }

    else
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size - 1; j++)
            {
                if (arr[j] > arr[j + 1])
                {
                    temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }
}

int deleteall(int arr[], int size)
{
    free(arr);
    printf("Array has been deleted!!\n");
    printf("Please re-enter array size and elements!!\n ");

    return size;
}

int delete_at_pos(int arr[], int size)
{
    int pos;

    if (size == 0)
    {
        printf("Please define array size first!!\nPress (11)\n");
    }

    else
    {
    position:
        printf("Enter position for delete : ");
        scanf("%d", &pos);

        if (pos > size || pos <= 0)
        {
            printf("Invalid position!!\n");
            goto position;
        }

        else
        {
            pos--;
            while (pos <= size - 1)
            {
                arr[pos] = arr[pos + 1];
                pos++;
            }

            size--;

            arr = (int *)realloc(arr, size * sizeof(int));
        }
    }
    return size;
}

int delete_at_first(int arr[], int size)
{
    if (size == 0)
    {
        printf("Please define array size first!!\nPress (11)\n");
    }

    else
    {
        for (int i = 0; i <= size - 1; i++)
        {
            arr[i] = arr[i + 1];
        }

        size--;

        arr = (int *)realloc(arr, size * sizeof(int));
    }
    return size;
}

int delete_at_last(int arr[], int size)
{
    if (size == 0)
    {
        printf("Please define array size first!!\nPress (11)\n");
    }

    else
    {
        size--;

        arr = (int *)realloc(arr, size * sizeof(int));
    }
    return size;
}

int main()
{
    int *arr = NULL;
    int size, op;

arr_intialize:

    printf("Enter size of array: ");
    scanf("%d", &size);

    //    arr = (int*)malloc(size*sizeof(int));

    arr = inisialise(size);

    insert(arr, size);

    printf("\nSelect Operation:-\n0) EXIT!!\n1) Re-Insert elements\n2) Insert at position\n3) Insert at first\n4) Insert at last\n5) Delete at first\n6) Delete at last\n7) Delete at position\n8) Delete array\n9) Sort array\n10) Traverse array\n11) Re-enter array size\n");
    while (1)
    {
        printf("Select:- ");
        fflush(stdin);
        scanf("%d", &op);

        switch (op)
        {
        case 0:
        {
            goto end;
        }

        case 1:
        {
            insert(arr, size);
            break;
        }

        case 2:
        {
            size = insert_at_pos(arr, size);
            break;
        }

        case 3:
        {
            size = insert_at_first(arr, size);
            break;
        }

        case 4:
        {
            size = insert_at_last(arr, size);
            break;
        }

        case 5:
        {
            size = delete_at_first(arr, size);
            break;
        }

        case 6:
        {
            size = delete_at_last(arr, size);
            break;
        }

        case 7:
        {
            size = delete_at_pos(arr, size);
            break;
        }

        case 8:
        {
            size = deleteall(arr, size);
            goto arr_intialize;
            break;
        }

        case 9:
        {
            sort(arr, size);
        }

        case 10:
        {
            traverse(arr, size);
            break;
        }

        case 11:
        {
            free(arr);
            goto arr_intialize;
            break;
        }
        default:
            printf("Invalid Input!!\n");
        }
    }

end:
    free(arr);

    return 0;
}
