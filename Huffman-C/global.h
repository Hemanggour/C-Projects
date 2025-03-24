#define BUFFER_SIZE 1000
#define ENCODE_STRING_SIZE 50

typedef enum bool
{
    false,
    true
} bool;

typedef struct HuffmanTree
{
    char data;
    int freq;
    struct HuffmanTree *left;
    struct HuffmanTree *right;
} HuffmanTree;

typedef struct EncodedStringList
{
    char *encodeString;
    size_t encodeStringSize;
    struct EncodedStringList *next;
} EncodedStringList;