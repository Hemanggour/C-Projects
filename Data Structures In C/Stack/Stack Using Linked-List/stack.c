// Stack implementation using singly linked list.

#include <stdio.h>
#include <stdlib.h>

struct node
{
    int data;
    struct node *next;
} *temp, *newnode;
struct node *top = NULL;

void push()
{
    newnode = (struct node *)malloc(sizeof(struct node));
    newnode->next = NULL;
    printf("Enter data :- ");
    scanf("%d", &newnode->data);

    if (top == NULL)
    {
        top = newnode;
    }
    else
    {
        temp = top;
        top = newnode;
        newnode->next = temp;
    }
}

void pop()
{
    if (top == NULL)
    {
        printf("UNDER FLOW!!\n");
        return;
    }

    temp = top;
    top = top->next;
    printf("Poped Element :- %d\n", temp->data);
    free(temp);
}

void peek()
{
    if (top == NULL)
    {
        printf("UNDER FLOW!!\n");
        return;
    }

    printf("Top Element :- %d\n", top->data);
}

void count_size()
{
    if (top == NULL)
    {
        printf("UNDER FLOW!!\n");
        return;
    }

    int count = 0;

    for (temp = top; temp != NULL; temp = temp->next)
    {
        count++;
    }
    printf("Total elements in stack :- %d\n", count);
}

void display()
{
    if (top == NULL)
    {
        printf("UNDER FLOW!!\n");
        return;
    }

    for (temp = top; temp != NULL; temp = temp->next)
    {
        printf("%d\n", temp->data);
    }
}

int main()
{
    int ch = 1;

    printf("Enter choice :-\n0. EXIT\n1. PUSH\n2. POP\n3. PEEK\n4. Display\n5. Count\n");

    while (ch != 0)
    {
        printf("Select :- ");
        scanf("%d", &ch);

        switch (ch)
        {
        case 0:
        {
            break;
        }

        case 1:
        {
            push(); // To push element in stack.
            break;
        }

        case 2:
        {
            pop(); // To Delete element from stack;
            break;
        }

        case 3:
        {
            peek(); // To display top most element in stack.
            break;
        }

        case 4:
        {
            display(); // To display whole stack.
            break;
        }

        case 5:
        {
            count_size();
            break;
        }

        default:
        {
            printf("Invalid Choice!!\n");
            break;
        }
        }
    }

    return 0;
}
