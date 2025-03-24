void huffmanPreOrder(HuffmanTree *encodeHuffmanTreeNode)
{
    if (!encodeHuffmanTreeNode)
        return;
    printf("Data: %c, freq: %d\n", encodeHuffmanTreeNode->data, encodeHuffmanTreeNode->freq);
    huffmanPreOrder(encodeHuffmanTreeNode->left);
    huffmanPreOrder(encodeHuffmanTreeNode->right);
    return;
}

void huffmanInOrder(HuffmanTree *encodeHuffmanTreeNode)
{
    if (!encodeHuffmanTreeNode)
        return;
    huffmanPreOrder(encodeHuffmanTreeNode->left);
    printf("Data: %c, freq: %d\n", encodeHuffmanTreeNode->data, encodeHuffmanTreeNode->freq);
    huffmanPreOrder(encodeHuffmanTreeNode->right);
    return;
}

void huffmanPostOrder(HuffmanTree *encodeHuffmanTreeNode)
{
    if (!encodeHuffmanTreeNode)
        return;
    huffmanPreOrder(encodeHuffmanTreeNode->left);
    huffmanPreOrder(encodeHuffmanTreeNode->right);
    printf("Data: %c, freq: %d\n", encodeHuffmanTreeNode->data, encodeHuffmanTreeNode->freq);
    return;
}

void traverseEncodeList(HuffmanTree *encodeListHead)
{
    int i = 1;
    for (HuffmanTree *tempNode = encodeListHead; tempNode; tempNode = tempNode->right, i++)
        printf("%d. Data: %c, Freq: %d\n", i, tempNode->data, tempNode->freq);
}

HuffmanTree *getHuffmanTreeNode(void)
{
    HuffmanTree *node = (HuffmanTree *)MMalloc(sizeof(HuffmanTree));
    if (!node)
        return NULL;
    node->left = NULL;
    node->right = NULL;
    return node;
}

HuffmanTree *getMinimumFreqNode(HuffmanTree *encodeListHead)
{
    HuffmanTree *minNode = encodeListHead;
    for (HuffmanTree *tempNode = encodeListHead; tempNode; tempNode = tempNode->right)
    {
        if (tempNode->freq < minNode->freq)
            minNode = tempNode;
    }
    return minNode;
}

HuffmanTree *getSumParentNode(HuffmanTree *left, HuffmanTree *right)
{
    HuffmanTree *parentNode = getHuffmanTreeNode();
    if (!parentNode)
    {
        printf("Error Creating Parent Node!!");
        MFreeAll();
        exit(EXIT_FAILURE);
    }
    parentNode->data = '\0';
    parentNode->freq = (left->freq) + (right->freq);
    parentNode->left = left;
    parentNode->right = right;
    return parentNode;
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
                MFreeAll();
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

HuffmanTree *removeNode(HuffmanTree *encodeListHead, HuffmanTree *node)
{
    if (encodeListHead == node)
    {
        encodeListHead = encodeListHead->right;
        node->left = NULL;
        node->right = NULL;
        return encodeListHead;
    }
    HuffmanTree *tempNode = encodeListHead;
    while (tempNode->right != node)
        tempNode = tempNode->right;
    tempNode->right = node->right;
    node->left = NULL;
    node->right = NULL;
    return encodeListHead;
}

HuffmanTree *createHuffmanTree(HuffmanTree *encodeListHead)
{
    if (!encodeListHead)
    {
        printf("Error Creating Huffman Tree!!\n");
        printf("encodeListHead is NULL!!\n");
        MFreeAll();
        exit(EXIT_FAILURE);
    }
    HuffmanTree *minNode = getMinimumFreqNode(encodeListHead);
    HuffmanTree *encodeHuffmanTreeHead = getHuffmanTreeNode();
    encodeHuffmanTreeHead->data = minNode->data;
    encodeHuffmanTreeHead->freq = minNode->freq;
    encodeListHead = removeNode(encodeListHead, minNode);
    MFree(minNode);
    while (encodeListHead)
    {
        HuffmanTree *secondMinNode = getMinimumFreqNode(encodeListHead);
        HuffmanTree *newNode = getHuffmanTreeNode();
        newNode->data = secondMinNode->data;
        newNode->freq = secondMinNode->freq;
        encodeListHead = removeNode(encodeListHead, secondMinNode);
        MFree(secondMinNode);
        encodeHuffmanTreeHead = getSumParentNode(newNode, encodeHuffmanTreeHead);
    }
    return encodeHuffmanTreeHead;
}

void traverseEncodeString(EncodedStringList *stringNodeHead)
{
    size_t totalSize = 0;
    for (EncodedStringList *tempNode = stringNodeHead; tempNode; tempNode = tempNode->next)
    {
        for (size_t i = 0; i < tempNode->encodeStringSize; i++)
            printf("%c", tempNode->encodeString[i]);
        totalSize += tempNode->encodeStringSize;
    }
    printf("\nTotal size: %zu bits\n", totalSize);
}

EncodedStringList *getEncodeStringNode(void)
{
    EncodedStringList *stringNode = (EncodedStringList *)MMalloc(sizeof(EncodedStringList));
    if (!stringNode)
        return NULL;
    stringNode->encodeString = (char *)MMalloc(sizeof(char) * ENCODE_STRING_SIZE);
    if (!stringNode->encodeString)
        return NULL;
    stringNode->encodeStringSize = 0;
    stringNode->next = NULL;
    return stringNode;
}

void insertInEncodeStringNode(EncodedStringList *stringNodeHead, char value)
{
    if (!stringNodeHead)
    {
        printf("String List Head Not Exists!!\n");
        MFreeAll();
        exit(EXIT_FAILURE);
    }
    EncodedStringList *tempNode = stringNodeHead;
    while (tempNode->next)
        tempNode = tempNode->next;
    if (tempNode->encodeStringSize >= ENCODE_STRING_SIZE)
    {
        tempNode->next = getEncodeStringNode();
        tempNode = tempNode->next;
    }
    tempNode->encodeString[tempNode->encodeStringSize] = value;
    tempNode->encodeStringSize++;
}

void findCharacterPath(HuffmanTree *root, char character, char *path, int *pathLen, bool *found)
{
    if (!root || *found)
        return;
    if (root->data == character)
    {
        *found = true;
        path[*pathLen] = '\0';
        return;
    }
    if (root->left)
    {
        path[*pathLen] = '0';
        (*pathLen)++;
        findCharacterPath(root->left, character, path, pathLen, found);
        if (!*found)
            (*pathLen)--;
    }
    if (root->right && !*found)
    {
        path[*pathLen] = '1';
        (*pathLen)++;
        findCharacterPath(root->right, character, path, pathLen, found);
        if (!*found)
            (*pathLen)--;
    }
}

void addCharacterEncoding(HuffmanTree *root, char character, EncodedStringList *stringNodeHead)
{
    char path[256] = {0};
    int pathLen = 0;
    bool found = false;
    findCharacterPath(root, character, path, &pathLen, &found);
    if (found)
    {
        for (int i = 0; i < pathLen; i++)
            insertInEncodeStringNode(stringNodeHead, path[i]);
    }
    else
        printf("Error: Character '%c' not found in Huffman tree\n", character);
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

char *input(void)
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
        MFreeAll();
        exit(EXIT_FAILURE);
    }
    else
    {
        size_t inputBufferSize = getInputBufferSize(inputBuffer);
        inputBuffer[--inputBufferSize] = '\0';
        inputBuffer = (char *)MRealloc(inputBuffer, inputBufferSize);
    }
}