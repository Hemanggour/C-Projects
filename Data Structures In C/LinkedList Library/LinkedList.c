#include <stdlib.h>

char *help()
{
    return "head = createLL(size);\nnode = createNode(data);\nnode = insertLL(node, data);\nhead = insertAtFirst(head, data);\nhead = insertAtLast(head, data);\nhead = insertAtPosition(head, position, data);\nhead = deleteAtFirst(head);\nhead = deleteAtLast(head);\nhead = deleteAtPosition(head, position);\nhead = deleteLL(head);\nhead = reverseLL(head);\n\n--\"nodeCount\" Is a Variable Which Store's How Much Nodes is in the List. (Updates Automatically)!!\n\n--You Can Use \"tail\" Pointer To Get The Last Node Of The List\n\n--\"nextNode = insertLL(node, data);\"\n--\"insertLL()\" returns the \"nextnode\" of the given \"node\" You Can use this code:\n\nint data;\nlist* node = head;\nfor (list* temp = head; temp; temp=temp->next) {\n\tprintf(\"Enter Data: \");\n\tscanf(\"\%d\", &data);\n\tnode = insertLL(node, data);\n}\n\n--To Display List Use This Code:\nfor (list* temp = head; temp; temp = temp->next)\n\tprintf(\"\%d \", temp->data);\n\n";
}

int nodeCount = 0;

typedef struct Linked_list
{
    int data;
    struct Linked_list *next;
} list;
list *head = NULL;
list *tail = NULL;

list *createNode(int data)
{
    list *newnode = (list *)malloc(sizeof(list));
    newnode->data = data;
    newnode->next = NULL;
    nodeCount++;
    return newnode;
}

list *createLL(int size)
{
    for (int i = 1; i <= size; i++)
    {
        list *newnode = createNode(0);

        if (!head)
            head = tail = newnode;
        else
            tail = tail->next = newnode;
    }
    return head;
}

list *insertAtFirst(list *head, int data)
{
    if (!head)
        return head;
    list *newnode = createNode(data);
    newnode->next = head;
    head = newnode;
    return head;
}

list *insertAtLast(list *head, int data)
{
    if (!head)
        return head;
    list *newnode = createNode(data);
    tail = tail->next = newnode;
    return head;
}

list *insertAtPosition(list *head, int pos, int data)
{
    if (!head)
        return head;
    if (pos <= 0 || pos > nodeCount + 1)
        return head;
    else if (pos == 1 || pos == nodeCount + 1)
    {
        if (pos == 1)
            head = insertAtFirst(head, data);
        else
            head = insertAtLast(head, data);
        return head;
    }
    list *newnode = createNode(data);
    list *temp = head;
    for (int i = 1; i < pos - 1; i++)
        temp = temp->next;
    newnode->next = temp->next;
    temp->next = newnode;
    return head;
}

list *deleteAtFirst(list *head)
{
    if (!head)
        return head;
    list *temp = head;
    head = head->next;
    free(temp);
    nodeCount--;
    return head;
}

list *deleteAtLast(list *head)
{
    if (!head)
        return head;
    list *temp = head;
    while (temp->next != tail)
        temp = temp->next;
    free(tail);
    tail = temp;
    tail->next = NULL;
    nodeCount--;
    return head;
}

list *deleteAtPosition(list *head, int pos)
{
    if (!head)
        return head;
    if (pos < 1 || pos > nodeCount)
        return head;
    else if (pos == 1 || pos == nodeCount)
    {
        if (pos == 1)
            head = deleteAtFirst(head);
        else
            head = deleteAtLast(head);
        return head;
    }
    list *temp = head;
    list *prev;
    for (int i = 1; i < pos - 1; i++)
        temp = temp->next;
    prev = temp;
    temp = temp->next;
    prev->next = temp->next;
    free(temp);
    nodeCount--;
    return head;
}

list *deleteLL(list *head)
{
    if (!head)
        return head;
    while (head)
    {
        list *temp = head;
        head = head->next;
        free(temp);
    }
    nodeCount = 0;
    return head;
}

list *reverseLL(list *head)
{
    list *temp, *prev, *nextnode;
    prev = NULL;

    for (temp = nextnode = head; nextnode != NULL;)
    {
        temp = nextnode;
        nextnode = nextnode->next;
        temp->next = prev;
        prev = temp;
    }
    head = prev;
    return head;
}

list *insertLL(list *node, int data)
{
    if (!node)
        return node;
    node->data = data;
    return node->next;
}
