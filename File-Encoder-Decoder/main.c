#include <stdio.h>
#include <string.h>
#define SIZE 101

void encode(char *inputFile)
{
    FILE *input = fopen(inputFile, "r");
    FILE *output = fopen(strcat(inputFile, ".EN"), "w");

    if (input == NULL || output == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char ch;
    while ((ch = fgetc(input)) != EOF)
    {
        for (int i = 7; i >= 0; i--)
        {
            fputc((ch & (1 << i)) ? '1' : '0', output);
        }
    }

    fclose(input);
    fclose(output);
    printf("Encoded Successfully!!\n");
}

void decode(const char *inputFile)
{
    FILE *input = fopen(inputFile, "r");
    char name[50];
    printf("Enter your file name you want with extension: ");
    scanf("%s", name);
    FILE *output = fopen(name, "w");

    if (input == NULL || output == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    char binary[9];
    binary[8] = '\0';
    while (fgets(binary, 9, input))
    {
        char ch = 0;
        for (int i = 0; i < 8; i++)
        {
            ch = ch * 2 + (binary[i] - '0');
        }
        fputc(ch, output);
    }

    fclose(input);
    fclose(output);
    printf("Decoded Successfully!!\n");
}

int main()
{
    char path[SIZE];

    int choice = 0;
    do
    {
        printf("0) EXIT\n1) Encode\n2) Decode\nSelect:- ");
        fflush(stdin);
        scanf("%d", &choice);
        if (choice)
        {
            printf("Enter File Path:- ");
            fflush(stdin);
            gets(path);
        }

        switch (choice)
        {
        case 0:
            break;
        case 1:
            encode(path);
            break;
        case 2:
            decode(path);
            break;
        default:
            printf("Invalid Input!!\n");
            break;
        }
    } while (choice);

    return 0;
}