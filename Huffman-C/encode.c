void encode(HuffmanTree *encodeHuffmanTreeHead)
{
    EncodedStringList *stringNodeHead = getEncodeStringNode();

    
}

void startEncode(char *inputBuffer)
{
    HuffmanTree *encodeListHead = createListForEncode(inputBuffer);
    traverseEncodeList(encodeListHead);
    MFree(inputBuffer);
    HuffmanTree *encodeHuffmanTreeHead = createHuffmanTree(encodeListHead);
    encodeListHead = NULL;
    // MFree(encodeListHead);
    huffmanPreOrder(encodeHuffmanTreeHead);
    // huffmanInOrder(encodeHuffmanTreeHead);
    // encode(encodeHuffmanTreeHead);
}