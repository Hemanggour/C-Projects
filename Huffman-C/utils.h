#include "utils.c"

void huffmanPreOrder(HuffmanTree *);
void huffmanInOrder(HuffmanTree *);
void huffmanPostOrder(HuffmanTree *);
void traverseEncodeList(HuffmanTree *);
HuffmanTree *getHuffmanTreeNode(void);
HuffmanTree *getMinimumFreqNode(HuffmanTree *);
HuffmanTree *getSumParentNode(HuffmanTree *, HuffmanTree *);
HuffmanTree *checkCharInList(HuffmanTree *, char);
HuffmanTree *createListForEncode(char *);
HuffmanTree *removeNode(HuffmanTree *, HuffmanTree *);
HuffmanTree *createHuffmanTree(HuffmanTree *);
void traverseEncodeString(EncodedStringList *);
EncodedStringList *getEncodeStringNode(void);
void insertInEncodeStringNode(EncodedStringList *, char);
void findCharacterPath(HuffmanTree *, char, char *, int *, bool *);
void addCharacterEncoding(HuffmanTree *, char, EncodedStringList *);
int getInputBufferSize(char *);
char *input(void);
void checkAndResizeInputBuffer(char *);