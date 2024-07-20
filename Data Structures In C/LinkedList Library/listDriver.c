#include"LinkedList.c"
#include<stdio.h>

int input()
{
    int data;
    printf("Enter Data: ");
    scanf("%d", &data);
    return data;
}

int inputPos()
{
    int pos;
    printf("Enter Position: ");
    scanf("%d", &pos);
    return pos;
}

int main()
{
    int choice, size = 0;
    list* head = NULL, * node;

    do
    {
        printf("0) Exit\n1) Define List Size\n2) Insert In List\n3) Insert At First\n4) Insert At Last\n5) Insert At Position\n6) Delete List\n7) Delete At First\n8) Delete At Last\n9) Delete At Position\n10) Reverse List\n11) Display List\n12) Display Node Count\n13) Help\nSelect: ");
        fflush(stdin);
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            break;
        case 1:
            head = deleteLL(head);
            printf("Enter List Size: ");
            scanf("%d", &size);
            head = createLL(size);
            break;
        case 2:
            node = head;
            int data;
            for (int i = 1; i <= size; i++) {
                printf("Enter Data: ");
                scanf("%d", &data);
                node = insertLL(node, data);
            }
            break;
        case 3:
            head = insertAtFirst(head, input());
            break;
        case 4:
            head = insertAtLast(head, input());
            break;
        case 5:
            head = insertAtPosition(head, inputPos(), input());
            break;
        case 6:
            head = deleteLL(head);
            break;
        case 7:
            head = deleteAtFirst(head);
            break;
        case 8:
            head = deleteAtLast(head);
            break;
        case 9:
            head = deleteAtPosition(head, inputPos());
            break;
        case 10:
            head = reverseLL(head);
            break;
        case 11:
            for (list* temp = head; temp; temp = temp->next)
                printf("%d ", temp->data);
            printf("\n");
            break;
        case 12:
            printf("%d Nodes is in the list!!\n", nodeCount);
            break;
        case 13:
            printf("%s", help());
            break;
        default:
            printf("Invalid Choice!!\n");
            break;
        }
    } while (choice);


    return 0;
}