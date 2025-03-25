void encode(HuffmanTree *encodeHuffmanTreeHead, char *inputBuffer)
{
    EncodedStringList *stringNodeHead = getEncodeStringNode();

    printf("\nEncoding input: %s\n", inputBuffer);
    printf("-----------------\n");

    for (size_t i = 0; inputBuffer[i]; i++)
        addCharacterEncoding(encodeHuffmanTreeHead, inputBuffer[i], stringNodeHead);

    huffmanPreOrder(encodeHuffmanTreeHead);

    printf("\nComplete encoded string: ");
    traverseEncodeString(stringNodeHead);
}

void startEncode(char *inputBuffer)
{
    HuffmanTree *encodeListHead = createListForEncode(inputBuffer);
    HuffmanTree *encodeHuffmanTreeHead = createHuffmanTree(encodeListHead);
    encode(encodeHuffmanTreeHead, inputBuffer);
    MFree(inputBuffer);
}