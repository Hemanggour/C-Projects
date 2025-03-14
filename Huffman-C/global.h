#define BUFFER_SIZE 1000

typedef enum bool {False, True} bool;

typedef struct HuffmanTree
{
    char data;
    int freq;
    struct HuffmanTree *right;
    struct HuffmanTree *left;
} HuffmanTree;