#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int randomGen(void)
{
    srand(time(NULL));
    return rand() % 3;
}

void input(int *user)
{
    while (1)
    {
        printf("1) Rock\n2) Paper\n3) Scissor\nSelect: ");
        fflush(stdin);
        scanf("%d", user);
        if ((*user) == 1 || (*user) == 2 || (*user) == 3)
            break;
        else
            printf("Invalid Choice!!\n");
    }
    (*user)--;
}

void game(void)
{
    int user, comp, userPoint = 0, compPoint = 0;
    enum
    {
        rock,
        paper,
        scissor
    };
    while (userPoint < 3 && compPoint < 3)
    {
        input(&user);
        comp = randomGen();
        if ((user == rock && comp == scissor) || (user == paper && comp == rock) || (user == scissor && comp == paper))
        {
            printf("User Win This Round!!\n");
            userPoint++;
        }
        else if ((comp == rock && user == scissor) || (comp == paper && user == rock) || (comp == scissor && user == paper))
        {
            printf("Computer Win This Round!!\n");
            compPoint++;
        }
        else
            printf("Same!!\n");
    }
    if (userPoint > compPoint)
        printf("User Won!!\n");
    else
        printf("Computer Won!!\n");
    userPoint = compPoint = 0;
}

int main()
{
    int choice = 0;
    do
    {
        printf("0) Exit\n1) Play\nSelect: ");
        fflush(stdin);
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            break;
        case 1:
            game();
            break;
        default:
            printf("Invalid Input!!\n");
            break;
        }
    } while (choice);

    return 0;
}
