void startEncode(char *inputBuffer)
{
    HuffmanTree *encodeListHead = createListForEncode(inputBuffer);
    traverseEncodeList(encodeListHead);
}

void encode(HuffmanTree *encodeHuffmanTree)
{
}