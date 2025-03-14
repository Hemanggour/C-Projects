HuffmanTree *getHuffmanTreeNode()
{
    HuffmanTree *node = (HuffmanTree *)MMalloc(sizeof(HuffmanTree));
    if (!node)
        return NULL;
    node->left = node->right = NULL;
    return node;
}

HuffmanTree *checkCharInList(HuffmanTree *encodeListHead, char character)
{
    for (HuffmanTree *tempNode = encodeListHead; tempNode; tempNode = tempNode->right)
    {
        if (tempNode->data == character)
            return tempNode;
    }
    return NULL;
}

void traverseEncodeList(HuffmanTree *encodeListHead)
{
    int i = 1;
    for (HuffmanTree *tempNode = encodeListHead; tempNode; tempNode = tempNode->right, i++)
        printf("%d. %c: %d\n", i, tempNode->data, tempNode->freq);
}

HuffmanTree *createListForEncode(char *inputBuffer)
{
    HuffmanTree *encodeListHead = NULL, *tailNode = NULL, *prevNode = NULL, *tempNode = NULL;

    for (size_t index = 0; inputBuffer[index]; index++)
    {
        if (tempNode = checkCharInList(encodeListHead, inputBuffer[index]))
            tempNode->freq++;
        else
        {
            HuffmanTree *newNode = getHuffmanTreeNode();
            if (!newNode)
            {
                printf("Error Creating Encode List!!");
                exit(EXIT_FAILURE);
            }
            newNode->data = inputBuffer[index];
            newNode->freq = 1;
            if (!encodeListHead)
                encodeListHead = tailNode = newNode;
            else
            {
                tailNode->right = newNode;
                tailNode->left = prevNode;
                prevNode = tailNode;
                tailNode = newNode;
            }
        }
    }
    return encodeListHead;
}

int countInputBufferFreq(HuffmanTree *encodeHuffmanTreeHead, char *inputBuffer)
{
}

int getInputBufferSize(char *inputBuffer)
{
    if (!inputBuffer)
        return 0;
    size_t size = 0;
    for (size_t i = 0; inputBuffer[i]; i++, size++)
        ;
    return size;
}

char *input()
{
    char *inputBuffer = (char *)MMalloc(BUFFER_SIZE);
    fflush(stdin);
    if (fgets(inputBuffer, BUFFER_SIZE, stdin) != NULL)
        return inputBuffer;
    return NULL;
}

void checkAndResizeInputBuffer(char *inputBuffer)
{
    if (!inputBuffer)
    {
        printf("Input Error!\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        size_t inputBufferSize = getInputBufferSize(inputBuffer);
        inputBuffer[--inputBufferSize] = '\0';
        inputBuffer = (char *)MRealloc(inputBuffer, inputBufferSize);
    }
}