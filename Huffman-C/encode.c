void encode(HuffmanTree *encodeHuffmanTreeHead, char *inputBuffer)
{
    EncodedStringList *stringNodeHead = getEncodeStringNode();
    for(size_t i = 0; inputBuffer[i]; i++) {
        char currentChar = inputBuffer[i];
        // Find and encode each character using the Huffman tree
        // Add encoded bits to stringNodeHead
    }
}

void startEncode(char *inputBuffer)
{
    HuffmanTree *encodeListHead = createListForEncode(inputBuffer);
    traverseEncodeList(encodeListHead);
    HuffmanTree *encodeHuffmanTreeHead = createHuffmanTree(encodeListHead);
    encodeListHead = NULL;
    huffmanPreOrder(encodeHuffmanTreeHead);
    // encode(encodeHuffmanTreeHead, inputBuffer);
    MFree(inputBuffer);
}