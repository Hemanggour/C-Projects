#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

char *str = NULL;
char *str2 = NULL;
int size, count = 7;
int size_cpy;

void print_stick()
{
    for (int i = 0; i < count; i++)
        printf("|\n");
}

void display_hangman()
{
    printf("|------\n");
    if (count == 6)
    {
        print_stick();
        return;
    }
    printf("|     |\n");
    if (count == 5)
    {
        print_stick();
        return;
    }
    printf("|   (* *)\n");
    if (count == 4)
    {
        print_stick();
        return;
    }
    printf("|     |  \n");
    if (count == 3)
    {
        print_stick();
        return;
    }
    printf("|   --|--\n");
    if (count == 2)
    {
        print_stick();
        return;
    }
    printf("|     |\n");
    if (count == 1)
    {
        print_stick();
        return;
    }
    printf("|    / \\\n");
    printf("|\n");
}

void print_guess_line()
{
    for (int i = 0; i < size; i++)
    {
        if (str[i] == str2[i] || str[i] == str2[i] + 32 || str[i] == str2[i] - 32)
            printf("%c ", str2[i]);
        else
            printf("_ ");
    }
    printf("\n");
}

int check_ch(char ch)
{
    int flag = 0;
    for (int i = 0; i < size; i++)
    {
        if ((str[i] == ch || str[i] == ch + 32 || str[i] == ch - 32) && (ch != str2[i] && ch != str2[i] + 32 && ch != str2[i] - 32))
        {
            str2[i] = ch;
            size_cpy--;
            flag = 1;
        }
        else if (ch == str2[i] || ch == str2[i] + 32 || ch == str2[i] - 32)
        {
            return -1;
        }
    }
    return flag;
}

void hangman()
{
    while (count && size_cpy)
    {
        char ch;
        print_guess_line();
        printf("\nGuess character :- ");
        fflush(stdin);
        scanf("%c", &ch);

        int check = check_ch(ch);
        if (check)
        {
            if (check == 1)
                printf("You guessed it right!!\n");
            else
                printf("Already inserted!!\n");
        }
        else
        {
            printf("You guessed it wrong!!\n");
            count--;
            display_hangman();
        }
    }

    if (!count || !size_cpy)
    {
        print_guess_line();
        if (!size_cpy)
            printf("You Win!!\n\n");
        else
            printf("You Lost!!\nThe word is %s\n\n", str);
    }
    count = 7;
}

void input_string()
{
    printf("Enter string :- ");
    fflush(stdin);
    scanf("%[^\n]", str);
    size = strlen(str);
    size_cpy = size;
    str = (char *)realloc(str, sizeof(char) * size);
    str2 = (char *)malloc(sizeof(char) * size);
}

int main()
{
    str = (char *)malloc(sizeof(char) * 51);
    char choice;

    while (choice != '0')
    {
        printf("(0) Quit\n(1) Play!!\nSelect :- ");
        scanf("%c", &choice);
        switch (choice)
        {
        case '0':
            break;

        case '1':
            input_string();
            hangman();
            break;
        default:
            printf("Invalid input!!\n");
            break;
        }
        fflush(stdin);
    }

    free(str);
    free(str2);

    return 0;
}