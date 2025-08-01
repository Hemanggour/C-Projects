#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>
#include <string.h>

#define MAX_SCORE 100
#define HISTORY_FILE "game_history.txt"
#define HIGH_SCORE_FILE "high_score.txt"
#define BUFFER 100

typedef struct Player
{
    char name[BUFFER];
    int score;
} Player;

int difficulty = INT_MIN;

void display_history()
{
    FILE *file = fopen(HISTORY_FILE, "r");
    char data[BUFFER];
    printf("\n");
    while (fgets(data, BUFFER, file) != NULL)
        printf("%s", data);

    fclose(file);
}

void save_high_score_to_file(int score)
{
    FILE *file = fopen(HIGH_SCORE_FILE, "w");
    char *template = "Date & Time: %sPlayer name: %s | Score: %d";
    time_t t;
    time(&t);

    fprintf(file, template, ctime(&t), score);
    fclose(file);
}

void display_high_score()
{
    FILE *file = fopen(HIGH_SCORE_FILE, "r");
    char data[50];
    fgets(data, BUFFER, file);
    printf("\n%s", data);
    fclose(file);
}

void save_to_file(Player player)
{
    char *template = "Date & Time: %sPlayer name: %s | Score: %d\n\n";

    FILE *file = fopen(HISTORY_FILE, "a");
    time_t t;
    time(&t);

    fprintf(file, template, ctime(&t), player.name, player.score);
    fclose(file);
}

int set_chances(int selected_difficulty)
{
    difficulty = selected_difficulty;

    if (selected_difficulty == 1)
        return 10;
    else if (selected_difficulty == 2)
        return 5;
    else if (selected_difficulty == 3)
        return 3;
    else
        return 0;
}

void setup_player(Player *player)
{
    printf("\n---------- SET PROFILE ----------\n");
    printf("Enter your name: ");
    fflush(stdin);
    scanf("%s", player->name);

    player->score = MAX_SCORE;
}

int set_difficulty()
{
    int selected_difficulty = INT_MIN;

    do
    {
        printf("\n---------- SET DIFFICULTY ----------\n");
        printf("1. Easy (10 chances)\n");
        printf("2. Medium (5 chances)\n");
        printf("3. Hard (3 chances)\n");

        printf("(default: medium) Select: ");
        fflush(stdin);
        scanf("%d", &selected_difficulty);

        if (selected_difficulty < 0 || selected_difficulty > 3)
            printf("Invalid difficulty\nPlease select a valid option");
        else
            return set_chances(selected_difficulty);

    } while (selected_difficulty < 0 || selected_difficulty > 3);
}

int generate_number()
{
    srand(time(NULL));
    return (rand() % MAX_SCORE) + 1;
}

void game(Player *player, int chances)
{
    int choice = 0;
    int number = generate_number();

    do
    {
        printf("\nGuess the number (1-%d): ", MAX_SCORE);
        fflush(stdin);
        scanf("%d", &choice);
        if (choice < 1 || choice > MAX_SCORE)
            printf("Guess between limit (1-%d)!!\n", MAX_SCORE);
        else if (choice == number)
        {
            printf("%s Guessed it!!\n", player->name);
            break;
        }
        else if (choice > number)
        {
            printf("Choose Lower!!\n");
            chances--;
            player->score = (int)((float)MAX_SCORE * (float)chances / (float)difficulty);
        }
        else
        {
            printf("Choose Higher!!\n");
            chances--;
            player->score = (int)((float)MAX_SCORE * (float)chances / (float)difficulty);
        }

    } while (chances);

    if (!chances)
        printf("%s Lost!!\n Number: %d", player->name, number);

    save_to_file(*player);
}

int game_menu(Player player)
{
    int choice = 0;
    printf("\n1. Play\n2. Highest score\n3. History\n4. EXIT\nselect: ");
    fflush(stdin);
    scanf("%d", &choice);
    switch (choice)
    {
    case 1:
    {
        setup_player(&player);
        game(&player, set_difficulty());
        return 1;
    }
    case 2:
        display_high_score();
        return 1;
    case 3:
    {
        display_history();
        return 1;
    }
    case 4:
        return 0;
    default:
    {
        printf("Invalid choice!!\n");
        return 1;
    }
    }
}

int main()
{
    int choice = 0;
    do
    {
        Player player;
        choice = game_menu(player);
    } while (choice);

    return 0;
}