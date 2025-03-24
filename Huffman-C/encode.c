void encode(HuffmanTree *encodeHuffmanTreeHead, char *inputBuffer)
{
    EncodedStringList *stringNodeHead = getEncodeStringNode();

    printf("\nEncoding input: %s\n", inputBuffer);
    printf("Character encodings:\n");
    printf("-----------------\n");

    for (size_t i = 0; inputBuffer[i]; i++)
    {
        printf("%c: ", inputBuffer[i]);
        size_t beforeSize = stringNodeHead->encodeStringSize;
        addCharacterEncoding(encodeHuffmanTreeHead, inputBuffer[i], stringNodeHead);

        for (size_t j = beforeSize; j < stringNodeHead->encodeStringSize; j++)
            printf("%c", stringNodeHead->encodeString[j]);
        printf("\n");
    }

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