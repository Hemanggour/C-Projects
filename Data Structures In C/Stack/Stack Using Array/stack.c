#include <stdio.h>
#include <stdlib.h>

void push(int *stack, int size, int *top)
{
    if ((*top) >= size - 1)
    {
        printf("Over Flow!!\n");
        return;
    }

    printf("Enter Element :- ");
    scanf("%d", &stack[++(*top)]);
}

void pop(int *stack, int size, int *top)
{
    if ((*top) < 0)
    {
        printf("Under Flow!!\n");
        return;
    }

    printf("Poped element :- %d\n", stack[(*top)--]);
}

void peek(int *stack, int top)
{
    printf("Top Element: %d\n", stack[top]);
}

void display(int *stack, int size, int top)
{
    if (top < 0)
    {
        printf("Under Flow!!\n");
        return;
    }
    for (int i = top; i >= 0; i--)
    {
        printf("%d\n", stack[i]);
    }
}

int main()
{
    int size, choice, top = -1;

    printf("Enter size :- ");
    scanf("%d", &size);

    int *stack = (int *)malloc(sizeof(int) * size);

    printf("0) Exit\n1. Push\n2. Pop\n3. Display\n4) Peek\n");

    do
    {
        printf("Select :- ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            break;
        case 1:
        {
            push(stack, size, &top);
            break;
        }
        case 2:
        {
            pop(stack, size, &top);
            break;
        }
        case 3:
        {
            display(stack, size, top);
            break;
        }
        case 4:
        {
            peek(stack, top);
            break;
        }
        default:
        {
            printf("\nInvalid Choice!!\n");
            break;
        }
        }
    } while (choice);

    return 0;
}
