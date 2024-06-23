#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<time.h>

char ply1[51], ply2[51];
int ply1Points = 0, ply2Points = 0, dice;

void saveGame(void);
void displayRecord(void);
void resetGame(void);
void rollDice(void);
int checkSnakeLadder(int);
void game(void);
void getName(void);

int main()
{
    int choice = 0;

    do
    {
        printf("0) Quit!!\n1) Play!!\n2) Record!!\nSelect:- ");
        fflush(stdin);
        scanf("%d", &choice);
        switch (choice)
        {
        case 0:
            break;
        case 1:
            getName();
            game();
            saveGame();
            resetGame();
            break;
        case 2:
            displayRecord();
            break;
        default:
            printf("Invalid Choice!!\n");
            break;
        }
    } while (choice);

    return 0;
}

void saveGame()
{
    FILE* file = fopen("SnakeLadderRecord.txt", "a");
    if (!file)
    {
        printf("File Open Error!!\n");
        return;
    }
    time_t t;
    time(&t);
    fprintf(file, "Date & Time:- %s%s:- %d | %s:- %d\n\n", ctime(&t), ply1, ply1Points, ply2, ply2Points);
    fclose(file);
}

void displayRecord()
{
    FILE* file = fopen("SnakeLadderRecord.txt", "r");
    if (!file)
    {
        printf("File Open Error!!\n");
        return;
    }
    printf("Game History!!\n");
    char data[100];
    while (fgets(data, 100, file))
        printf("%s", data);
    fclose(file);
}

void game()
{
    int chance = 1;
    while (ply1Points != 100 && ply2Points != 100)
    {
        //First Player Chance!!
        printf("%s Chance!!\n(Press Any key to Roll Dice!!)\n", ply1);
        getch();
        rollDice();
        printf("Dice: %d\n", dice);
        if (dice + ply1Points <= 100)
            ply1Points += dice;
        if (dice == 6)
        {
            printf("Got Six!!\n(Extra Chance Roll Again!!)\n");
            getch();
            rollDice();
            printf("Dice: %d\n", dice);
            if (dice + ply1Points <= 100)
                ply1Points += dice;
        }
        ply1Points = checkSnakeLadder(ply1Points);
        printf("Your Points:- %d\n\n", ply1Points);
        if (ply1Points == 100)
            break;
        //Second Player Chance!!
        printf("%s Chance!!\n(Press Any key to Roll Dice!!)\n", ply2);
        getch();
        rollDice();
        printf("Dice: %d\n", dice);
        if (dice + ply2Points <= 100)
            ply2Points += dice;
        if (dice == 6)
        {
            printf("Got Six!!\n(Extra Chance Roll Again!!)\n");
            getch();
            rollDice();
            printf("Dice: %d\n", dice);
            if (dice + ply2Points <= 100)
                ply2Points += dice;
        }
        ply2Points = checkSnakeLadder(ply2Points);
        printf("Your Points:- %d\n\n", ply2Points);
        if (ply2Points == 100)
            break;
    }
    printf("%s Wins!!\n\n", ((ply1Points > ply2Points) ? ply1 : ply2));
}

int checkSnakeLadder(int point)
{
    switch (point)
    {
    case 2:
        printf("Ladder Up!!\n");
        return 39;  //Ladder
    case 7:
        printf("Ladder Up!!\n");
        return 29;  //Ladder
    case 22:
        printf("Ladder Up!!\n");
        return 41;  //Ladder
    case 27:
        printf("Snake Bite!!\n");
        return 7;   //Snake
    case 28:
        printf("Ladder Up!!\n");
        return 77;  //Ladder
    case 30:
        printf("Ladder Up!!\n");
        return 32;  //Ladder
    case 35:
        printf("Snake Bite!!\n");
        return 5;   //Snake
    case 39:
        printf("Snake Bite!!\n");
        return 3;   //Snake
    case 44:
        printf("Ladder Up!!\n");
        return 58;  //Ladder
    case 50:
        printf("Snake Bite!!\n");
        return 34;  //Snake
    case 54:
        printf("Ladder Up!!\n");
        return 69;  //Ladder
    case 59:
        printf("Snake Bite!!\n");
        return 46;  //Snake
    case 66:
        printf("Snake Bite!!\n");
        return 24;  //Snake
    case 70:
        printf("Ladder Up!!\n");
        return 90;  //Ladder
    case 73:
        printf("Snake Bite!!\n");
        return 12;  //Snake
    case 76:
        printf("Snake Bite!!\n");
        return 63;  //Snake
    case 80:
        printf("Ladder Up!!\n");
        return 83;  //Ladder
    case 87:
        printf("Ladder Up!!\n");
        return 93;  //Ladder
    case 89:
        printf("Snake Bite!!\n");
        return 67;  //Snake
    case 97:
        printf("Snake Bite!!\n");
        return 86;  //Snake
    case 99:
        printf("Snake Bite!!\n");
        return 26;  //Snake
    default:
        return point;
    }
}

void rollDice()
{
    srand(time(NULL));
    dice = (rand() % 6) + 1;
}

void getName()
{
    printf("Enter First Player Name:- ");
    fflush(stdin);
    gets(ply1);
    printf("Enter Second Player Name:- ");
    fflush(stdin);
    gets(ply2);
}

void resetGame()
{
    ply1Points = ply2Points = 0;
}