#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

char p1[20], p2[20];
int *bullet = NULL;
int *ply_1_ability = NULL;
int *ply_2_ability = NULL;
int empty = 0;
int ch = 1;
int ply_1_win = 0, ply_2_win = 0;

void display_name()
{
    printf("                    {} {}     {}        {}  {}}}}}}}}}  {}      }}                {}}}}}}}}}  {}      {}   {}{}{}{}{}   {}{{{{}}}}{}\n");
    printf("                    {}   {}   {}        {}  {}          {}     }}                 {}          {}      {}  {}        {}       {}     \n");
    printf("                    {}    {}  {}        {}  {}          {}    }}                  {}          {}      {}  {}        {}       {}     \n");
    printf("                    {}    {}  {}        {}  {}          {}   }}                   {}          {}      {}  {}        {}       {}     \n");
    printf("                    {}  {}    {}        {}  {}          {}  }}                    {}          {}      {}  {}        {}       {}     \n");
    printf("                    {}{}      {}        {}  {}          {} }}       }}}}}}}}}}}}  {}}}}}}}}}  {}{{{}}}{}  {}        {}       {}     \n");
    printf("                    {}  {}    {}        {}  {}          {}  }}      }}}}}}}}}}}}          {}  {}      {}  {}        {}       {}     \n");
    printf("                    {}    {}  {}        {}  {}          {}   }}                           {}  {}      {}  {}        {}       {}     \n");
    printf("                    {}    {}  {}        {}  {}          {}    }}                          {}  {}      {}  {}        {}       {}     \n");
    printf("                    {}   {}   {}        {}  {}          {}     }}                         {}  {}      {}  {}        {}       {}     \n");
    printf("                    {} {}      {}}}}}}}{}   {}}}}}}}}}  {}      }}                {{{{{{{{{}  {}      {}   {}{}{}{}{}        {}     \n");
    printf("                        R           O           U           L                          E           T           T             E\n");
}

void saveGame()
{
    FILE *file = fopen("BuckShotRecord.txt", "a");
    if (!file)
        return;
    time_t t;
    time(&t);
    fprintf(file, "Date & Time %s\n%s:- %d | %s:- %d\n\n", ctime(&t), p1, ply_1_win, p2, ply_2_win);
    printf("Game saved!!");
    fclose(file);
}

void displayGameRecord()
{
    FILE *file = fopen("BuckShotRecord.txt", "r");
    if (!file)
    {
        printf("File Open Error!!\n");
        return;
    }
    char data[100];
    printf("Game History!!\n");
    while (fgets(data, 100, file) != NULL)
        printf("%s", data);
    fclose(file);
}

int random_gen(int num)
{
    srand(time(NULL));
    return rand() % num;
}

void gen_ability(int num)
{
    printf("\nGenerating abilities for %s!!\n\n", p1);
    ply_1_ability = (int *)realloc(ply_1_ability, sizeof(int) * num);
    ply_2_ability = (int *)realloc(ply_2_ability, sizeof(int) * num);
    empty = 0;
    for (int i = 0; i < num; i++)
    {
        ply_1_ability[i] = random_gen(4);
        if (ply_1_ability[i] == 0)
            printf("-Knife\n");
        else if (ply_1_ability[i] == 1)
            printf("-Cigarette\n");
        else if (ply_1_ability[i] == 2)
            printf("-Beer\n");
        else if (ply_1_ability[i] == 3)
            printf("-Magnifying glass\n");
        sleep(1);
    }
    printf("\nAbilities generated for %s!!\n", p1);
    printf("\nGenerating abilities for %s!!\n\n", p2);

    for (int i = 0; i < num; i++)
    {
        ply_2_ability[i] = random_gen(4);
        if (ply_2_ability[i] == 0)
            printf("-Knife\n");
        else if (ply_2_ability[i] == 1)
            printf("-Cigarette\n");
        else if (ply_2_ability[i] == 2)
            printf("-Beer\n");
        else if (ply_2_ability[i] == 3)
            printf("-Magnifying glass\n");
        sleep(1);
    }
    printf("\nAbilities generated for %s!!\n", p2);
}

void load_bullet(int num)
{
    printf("\nLoading Bullets!!\n");
    bullet = (int *)realloc(bullet, sizeof(int) * num);
    empty = 0;
    for (int i = 0; i < num; i++)
    {
        bullet[i] = random_gen(2);
        if (bullet[i] == 0)
            empty++;
        sleep(1);
    }
    printf("Bullets Loaded!!\n");
    printf("Empty Shell :- %d\nBullets :- %d\n\n", empty, num - empty);
}

void print_round_winner(int chance)
{
    if (chance == 1)
        printf("\n%s Wins :- %d\n%s Lose :- %d\n", p1, ply_1_win, p2, ply_2_win);
    else if (chance == 2)
        printf("\n%s Wins :- %d\n%s Lose :- %d\n", p2, ply_2_win, p1, ply_1_win);
}

void print_winner()
{
    if (ply_1_win > ply_2_win)
        print_round_winner(1);
    else if (ply_1_win < ply_2_win)
        print_round_winner(2);
}

void print_ability(int chance, int num)
{
    if (chance == 1)
    {
        for (int i = 0; i < num; i++)
        {
            if (ply_1_ability[i] == 0)
                printf("(K) Knife\n");
            else if (ply_1_ability[i] == 1)
                printf("(C) Cigarette\n");
            else if (ply_1_ability[i] == 2)
                printf("(B) Beer\n");
            else if (ply_1_ability[i] == 3)
                printf("(M) Magnifying glass\n");
        }
        printf("(E) Exit ability!!\n");
    }
    else if (chance == 2)
    {
        for (int i = 0; i < num; i++)
        {
            if (ply_2_ability[i] == 0)
                printf("(K) Knife\n");
            else if (ply_2_ability[i] == 1)
                printf("(C) Cigarette\n");
            else if (ply_2_ability[i] == 2)
                printf("(B) Beer\n");
            else if (ply_2_ability[i] == 3)
                printf("(M) Magnifying glass\n");
        }
        printf("(E) Exit ability!!\n");
    }
}

void print_chance_and_ability(int chance, int num)
{
    if (chance == 1)
    {
        printf("\n%s chance!!\n(0) Shoot Yourself or (1) Shoot %s or (2) Use ability\nSelect :- ", p1, p2);
    }
    else if (chance == 2)
    {
        printf("\n%s chance!!\n(0) Shoot Yourself or (1) Shoot %s or (2) Use ability\nSelect :- ", p2, p1);
    }
}

void print_chance(int num)
{
    if (num == 1)
    {
        printf("\n\n%s chance\n(0) Shoot Yourself or (1) Shoot %s\nSelect :- ", p1, p2);
    }
    else
    {
        printf("\n\n%s chance\n(0) Shoot Yourself or (1) Shoot %s\nSelect :- ", p2, p1);
    }
}

int check_ability(int chance, int choice, int num)
{
    if (chance == 1)
    {
        for (int i = 0; i < num; i++)
        {
            if (choice == ply_1_ability[i])
            {
                return 1;
            }
        }
        return 0;
    }
    else if (chance == 2)
    {
        for (int i = 0; i < num; i++)
        {
            if (choice == ply_2_ability[i])
            {
                return 1;
            }
        }
        return 0;
    }
}

void remove_ability(int chance, int choice, int num)
{
    if (chance == 1)
    {
        for (int i = 0; i < num; i++)
        {
            if (ply_1_ability[i] == choice)
            {
                ply_1_ability[i] = -1;
                return;
            }
        }
    }
    else if (chance == 2)
    {
        for (int i = 0; i < num; i++)
        {
            if (ply_2_ability[i] == choice)
            {
                ply_2_ability[i] = -1;
                return;
            }
        }
    }
}

void level_1()
{
    printf("\n!! Welcome to level-1 !!\n\n");
    int ply_1_ch = 2, ply_2_ch = 2;
    int bul = 0, choice, chance = 1;

    load_bullet(3);

    printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);
    while (bul < 3 && ply_1_ch > 0 && ply_2_ch > 0)
    {
        print_chance(chance);
        scanf("%d", &choice);
        if (choice == 1 || choice == 0)
        {
            if (chance == 1)
            {
                if (choice == 0 && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_1_ch != 0)
                    {
                        printf("You are safe!!\n");
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_1_ch != 0)
                    {
                        printf("You Shot Yourself!!\n");
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, --ply_1_ch, p2, ply_2_ch);
                        chance = 2;
                        bul++;
                    }
                    if (bul == 3 || ply_1_ch == 0)
                    {
                        if (ply_1_ch == 0)
                        {
                            ply_2_win++;
                            print_round_winner(2);
                            return;
                        }
                        if (bul == 3)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(3);
                            bul = 0;
                        }
                    }
                }
                else if (choice == 1 && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_2_ch != 0)
                    {
                        printf("%s are safe!!\n", p2);
                        chance = 2;
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_2_ch != 0)
                    {
                        printf("You shot %s\n", p2);
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, --ply_2_ch);
                        chance = 2;
                        bul++;
                    }
                    if (bul == 3 || ply_2_ch == 0)
                    {
                        if (ply_2_ch == 0)
                        {
                            ply_1_win++;
                            print_round_winner(1);
                            return;
                        }
                        if (bul == 3)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(3);
                            bul = 0;
                        }
                    }
                }
            }
            else if (chance == 2)
            {
                if (choice == 0 && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_2_ch != 0)
                    {
                        printf("You are safe!!\n");
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_2_ch != 0)
                    {
                        printf("You Shot Yourself!!\n");
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, --ply_2_ch);
                        chance = 1;
                        bul++;
                    }
                    if (bul == 3 || ply_2_ch == 0)
                    {
                        if (ply_2_ch == 0)
                        {
                            ply_1_win++;
                            print_round_winner(1);
                            return;
                        }
                        if (bul == 3)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(3);
                            bul = 0;
                        }
                    }
                }
                else if (choice == 1 && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_1_ch != 0)
                    {
                        printf("%s are safe!!\n", p1);
                        chance = 1;
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_1_ch != 0)
                    {
                        printf("You shot %s\n", p1);
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, --ply_1_ch, p2, ply_2_ch);
                        chance = 1;
                        bul++;
                    }
                    if (bul == 3 || ply_1_ch == 0)
                    {
                        if (ply_1_ch == 0)
                        {
                            ply_2_win++;
                            print_round_winner(2);
                            return;
                        }
                        if (bul == 3)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(3);
                            bul = 0;
                        }
                    }
                }
            }
        }
        else
        {
            printf("invalid Choice!!\n");
        }
    }
}

void level_2()
{
    printf("\n!! Welcome to level-2 !!\n\n");
    int ply_1_ch = 4, ply_2_ch = 4;
    int bul = 0, chance = 1, knife = 0;
    char choice;
    load_bullet(8);

    printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);

    gen_ability(3);

    while (bul < 8 && ply_1_ch > 0 && ply_2_ch > 0)
    {
        print_chance_and_ability(chance, 3);
        fflush(stdin);
        scanf("%c", &choice);
        if (choice == '1' || choice == '0')
        {
            if (chance == 1)
            {
                if (choice == '0' && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_1_ch != 0)
                    {
                        printf("You are safe!!\n");
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_1_ch != 0)
                    {
                        printf("You Shot Yourself!!\n");
                        if (knife)
                        {
                            if (ply_1_ch == 1)
                                ply_1_ch--;
                            else
                                ply_1_ch -= 2;
                        }
                        else
                        {
                            ply_1_ch--;
                        }
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);
                        chance = 2;
                        bul++;
                    }
                    if (bul == 8 || ply_1_ch == 0)
                    {
                        if (ply_1_ch == 0)
                        {
                            ply_2_win++;
                            print_round_winner(2);
                            return;
                        }
                        if (bul == 8)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(8);
                            gen_ability(3);
                            bul = 0;
                        }
                    }
                }
                else if (choice == '1' && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_2_ch != 0)
                    {
                        printf("%s is safe!!\n", p2);
                        chance = 2;
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_2_ch != 0)
                    {
                        printf("You shot %s\n", p2);
                        if (knife)
                        {
                            if (ply_2_ch == 1)
                                ply_2_ch--;
                            else
                                ply_2_ch -= 2;
                        }
                        else
                        {
                            ply_2_ch--;
                        }
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);
                        chance = 2;
                        bul++;
                    }
                    if (bul == 8 || ply_2_ch == 0)
                    {
                        if (ply_2_ch == 0)
                        {
                            ply_1_win++;
                            print_round_winner(1);
                            return;
                        }
                        if (bul == 8)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(8);
                            gen_ability(3);
                            bul = 0;
                        }
                    }
                }
            }
            else if (chance == 2)
            {
                if (choice == '0' && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_2_ch != 0)
                    {
                        printf("You are safe!!\n");
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_2_ch != 0)
                    {
                        printf("You Shot Yourself!!\n");
                        if (knife)
                        {
                            if (ply_2_ch == 1)
                                ply_2_ch--;
                            else
                                ply_2_ch -= 2;
                        }
                        else
                        {
                            ply_2_ch--;
                        }
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);
                        chance = 1;
                        bul++;
                    }
                    if (bul == 8 || ply_2_ch == 0)
                    {
                        if (ply_2_ch == 0)
                        {
                            ply_1_win++;
                            print_round_winner(1);
                            return;
                        }
                        if (bul == 8)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(8);
                            gen_ability(3);
                            bul = 0;
                        }
                    }
                }
                else if (choice == '1' && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_1_ch != 0)
                    {
                        printf("%s is safe!!\n", p1);
                        chance = 1;
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_1_ch != 0)
                    {
                        printf("You shot %s\n", p1);
                        if (knife)
                        {
                            if (ply_1_ch == 1)
                                ply_1_ch--;
                            else
                                ply_1_ch -= 2;
                        }
                        else
                        {
                            ply_1_ch--;
                        }
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);
                        chance = 1;
                        bul++;
                    }
                    if (bul == 8 || ply_1_ch == 0)
                    {
                        if (ply_1_ch == 0)
                        {
                            ply_2_win++;
                            print_round_winner(2);
                            return;
                        }
                        if (bul == 8)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(8);
                            gen_ability(3);
                            bul = 0;
                        }
                    }
                }
            }
            knife = 0;
        }
        else if (choice == '2')
        {
            char ability_ch;
            print_ability(chance, 3);
            printf("Select ability :- ");
            fflush(stdin);
            scanf("%c", &ability_ch);
            if (ability_ch == 'k' || ability_ch == 'K') // Knife
            {
                if (check_ability(chance, 0, 3))
                {
                    printf("Using Knife!!\n");
                    knife = 1;
                    remove_ability(chance, 0, 3);
                }
                else
                    printf("Ability Unavailable!!\n");
            }
            else if (ability_ch == 'c' || ability_ch == 'C') // Cigarette
            {
                if (check_ability(chance, 1, 3))
                {
                    printf("Smoking Cigarette!!\n");
                    if (chance == 1)
                    {
                        if (ply_1_ch < 4)
                        {
                            printf("%s charges :- %d\n%s charges :- %d\n", p1, ++ply_1_ch, p2, ply_2_ch);
                        }
                    }
                    else
                    {
                        if (ply_2_ch < 4)
                        {
                            printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ++ply_2_ch);
                        }
                    }
                    remove_ability(chance, 1, 3);
                }
                else
                    printf("Ability Unavailable!!\n");
            }
            else if (ability_ch == 'b' || ability_ch == 'B') // Beer
            {
                if (check_ability(chance, 2, 3))
                {
                    printf("Drinking Beer!!\n");
                    if (bul != 8)
                    {
                        if (bullet[bul])
                        {
                            printf("Bullet!!\n");
                            bul++;
                        }
                        else
                        {
                            printf("Empty Shell!!\n");
                            bul++;
                        }
                        remove_ability(chance, 2, 3);
                    }
                }
                else
                    printf("Ability Unavailable!!\n");
            }
            else if (ability_ch == 'm' || ability_ch == 'M') // Magnifying glass
            {
                printf("Using Magnifying glass!!\n");
                if (check_ability(chance, 3, 3))
                {
                    if (bul != 8)
                    {
                        if (bullet[bul])
                        {
                            printf("Bullet!!\n");
                        }
                        else
                        {
                            printf("Empty Shell!!\n");
                        }
                        remove_ability(chance, 3, 3);
                    }
                }
                else
                    printf("Ability Unavailable!!\n");
            }
            else if (ability_ch == 'e' || ability_ch == 'E')
                ;
            else
                printf("Invalid Ability!!\n");
        }
        else
        {
            printf("invalid Choice!!\n");
        }
    }
}

void level_3()
{
    printf("\n!! Welcome to level-3 !!\n\n");
    int ply_1_ch = 2, ply_2_ch = 2;
    int bul = 0, chance = 1, knife = 0;
    char choice;
    load_bullet(4);

    printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);

    gen_ability(1);

    while (bul < 4 && ply_1_ch > 0 && ply_2_ch > 0)
    {
        print_chance_and_ability(chance, 3);
        fflush(stdin);
        scanf("%c", &choice);
        if (choice == '1' || choice == '0')
        {
            if (chance == 1)
            {
                if (choice == '0' && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_1_ch != 0)
                    {
                        printf("You are safe!!\n");
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_1_ch != 0)
                    {
                        printf("You Shot Yourself!!\n");
                        if (knife)
                        {
                            if (ply_1_ch == 1)
                                ply_1_ch--;
                            else
                                ply_1_ch -= 2;
                        }
                        else
                        {
                            ply_1_ch--;
                        }
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);
                        chance = 2;
                        bul++;
                    }
                    if (bul == 4 || ply_1_ch == 0)
                    {
                        if (ply_1_ch == 0)
                        {
                            ply_2_win++;
                            print_round_winner(2);
                            return;
                        }
                        if (bul == 4)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(4);
                            gen_ability(1);
                            bul = 0;
                        }
                    }
                }
                else if (choice == '1' && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_2_ch != 0)
                    {
                        printf("%s is safe!!\n", p2);
                        chance = 2;
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_2_ch != 0)
                    {
                        printf("You shot %s\n", p2);
                        if (knife)
                        {
                            if (ply_2_ch == 1)
                                ply_2_ch--;
                            else
                                ply_2_ch -= 2;
                        }
                        else
                        {
                            ply_2_ch--;
                        }
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);
                        chance = 2;
                        bul++;
                    }
                    if (bul == 4 || ply_2_ch == 0)
                    {
                        if (ply_2_ch == 0)
                        {
                            ply_1_win++;
                            print_round_winner(1);
                            return;
                        }
                        if (bul == 4)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(4);
                            gen_ability(1);
                            bul = 0;
                        }
                    }
                }
            }
            else if (chance == 2)
            {
                if (choice == '0' && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_2_ch != 0)
                    {
                        printf("You are safe!!\n");
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_2_ch != 0)
                    {
                        printf("You Shot Yourself!!\n");
                        if (knife)
                        {
                            if (ply_2_ch == 1)
                                ply_2_ch--;
                            else
                                ply_2_ch -= 2;
                        }
                        else
                        {
                            ply_2_ch--;
                        }
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);
                        chance = 1;
                        bul++;
                    }
                    if (bul == 4 || ply_2_ch == 0)
                    {
                        if (ply_2_ch == 0)
                        {
                            ply_1_win++;
                            print_round_winner(1);
                            return;
                        }
                        if (bul == 4)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(4);
                            gen_ability(1);
                            bul = 0;
                        }
                    }
                }
                else if (choice == '1' && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_1_ch != 0)
                    {
                        printf("%s is safe!!\n", p1);
                        chance = 1;
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_1_ch != 0)
                    {
                        printf("You shot %s\n", p1);
                        if (knife)
                        {
                            if (ply_1_ch == 1)
                                ply_1_ch--;
                            else
                                ply_1_ch -= 2;
                        }
                        else
                        {
                            ply_1_ch--;
                        }
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);
                        chance = 1;
                        bul++;
                    }
                    if (bul == 4 || ply_1_ch == 0)
                    {
                        if (ply_1_ch == 0)
                        {
                            ply_2_win++;
                            print_round_winner(2);
                            return;
                        }
                        if (bul == 4)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(4);
                            gen_ability(1);
                            bul = 0;
                        }
                    }
                }
            }
            knife = 0;
        }
        else if (choice == '2')
        {
            char ability_ch;
            print_ability(chance, 1);
            printf("Select ability :- ");
            fflush(stdin);
            scanf("%c", &ability_ch);
            if (ability_ch == 'k' || ability_ch == 'K') // Knife
            {
                if (check_ability(chance, 0, 1))
                {
                    printf("Using Knife!!\n");
                    knife = 1;
                    remove_ability(chance, 0, 1);
                }
                else
                    printf("Ability Unavailable!!\n");
            }
            else if (ability_ch == 'c' || ability_ch == 'C') // Cigarette
            {
                if (check_ability(chance, 1, 1))
                {
                    printf("Smoking Cigarette!!\n");
                    if (chance == 1)
                    {
                        if (ply_1_ch < 2)
                        {
                            printf("%s charges :- %d\n%s charges :- %d\n", p1, ++ply_1_ch, p2, ply_2_ch);
                        }
                    }
                    else
                    {
                        if (ply_2_ch < 2)
                        {
                            printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ++ply_2_ch);
                        }
                    }
                    remove_ability(chance, 1, 1);
                }
                else
                    printf("Ability Unavailable!!\n");
            }
            else if (ability_ch == 'b' || ability_ch == 'B') // Beer
            {
                if (check_ability(chance, 2, 1))
                {
                    printf("Drinking Beer!!\n");
                    if (bul != 4)
                    {
                        if (bullet[bul])
                        {
                            printf("Bullet!!\n");
                            bul++;
                        }
                        else
                        {
                            printf("Empty Shell!!\n");
                            bul++;
                        }
                        remove_ability(chance, 2, 1);
                    }
                }
                else
                    printf("Ability Unavailable!!\n");
            }
            else if (ability_ch == 'm' || ability_ch == 'M') // Magnifying glass
            {
                printf("Using Magnifying glass!!\n");
                if (check_ability(chance, 3, 1))
                {
                    if (bul != 4)
                    {
                        if (bullet[bul])
                        {
                            printf("Bullet!!\n");
                        }
                        else
                        {
                            printf("Empty Shell!!\n");
                        }
                        remove_ability(chance, 3, 1);
                    }
                }
                else
                    printf("Ability Unavailable!!\n");
            }
            else if (ability_ch == 'e' || ability_ch == 'E')
                ;
            else
                printf("Invalid Ability!!\n");
        }
        else
        {
            printf("invalid Choice!!\n");
        }
    }
}

void death_round()
{
    char death_ch;
    printf("%s Do You Want To play Death Round!! (Y/N) ? :- ", p1);
    fflush(stdin);
    scanf("%c", &death_ch);
    if (death_ch == 'y' || death_ch == 'Y')
    {
        printf("%s Do You Want To play Death Round!! (Y/N) ? :- ", p2);
        fflush(stdin);
        scanf("%c", &death_ch);
        if (death_ch == 'y' || death_ch == 'Y')
        {
            printf("\n\n!! Welcome To Death Round !!\n");
        }
        else
            return;
    }
    else
        return;

    int ply_1_ch = 1, ply_2_ch = 1;
    int bul = 0, choice, chance = 1;

    load_bullet(2);
    printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, ply_2_ch);
    while (bul < 2 && ply_1_ch > 0 && ply_2_ch > 0)
    {
        print_chance(chance);
        scanf("%d", &choice);
        if (choice == 1 || choice == 0)
        {
            if (chance == 1)
            {
                if (choice == 0 && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_1_ch != 0)
                    {
                        printf("You are safe!!\n");
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_1_ch != 0)
                    {
                        printf("You Shot Yourself!!\n");
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, --ply_1_ch, p2, ply_2_ch);
                        chance = 2;
                        bul++;
                    }
                    if (bul == 2 || ply_1_ch == 0)
                    {
                        if (ply_1_ch == 0)
                        {
                            ply_2_win += 2;
                            print_winner();
                            return;
                        }
                        if (bul == 2)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(2);
                            bul = 0;
                        }
                    }
                }
                else if (choice == 1 && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_2_ch != 0)
                    {
                        printf("%s are safe!!\n", p2);
                        chance = 2;
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_2_ch != 0)
                    {
                        printf("You shot %s\n", p2);
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, --ply_2_ch);
                        chance = 2;
                        bul++;
                    }
                    if (bul == 2 || ply_2_ch == 0)
                    {
                        if (ply_2_ch == 0)
                        {
                            ply_1_win += 2;
                            print_winner();
                            return;
                        }
                        if (bul == 2)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(2);
                            bul = 0;
                        }
                    }
                }
            }
            else if (chance == 2)
            {
                if (choice == 0 && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_2_ch != 0)
                    {
                        printf("You are safe!!\n");
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_2_ch != 0)
                    {
                        printf("You Shot Yourself!!\n");
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, ply_1_ch, p2, --ply_2_ch);
                        chance = 1;
                        bul++;
                    }
                    if (bul == 2 || ply_2_ch == 0)
                    {
                        if (ply_2_ch == 0)
                        {
                            ply_1_win += 2;
                            print_winner();
                            return;
                        }
                        if (bul == 2)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(2);
                            bul = 0;
                        }
                    }
                }
                else if (choice == 1 && ply_1_ch != 0 && ply_2_ch != 0)
                {
                    if (bullet[bul] == 0 && ply_1_ch != 0)
                    {
                        printf("%s are safe!!\n", p1);
                        chance = 1;
                        bul++;
                    }
                    else if (bullet[bul] == 1 && ply_1_ch != 0)
                    {
                        printf("You shot %s\n", p1);
                        printf("%s charges :- %d\n%s charges :- %d\n", p1, --ply_1_ch, p2, ply_2_ch);
                        chance = 1;
                        bul++;
                    }
                    if (bul == 2 || ply_1_ch == 0)
                    {
                        if (ply_1_ch == 0)
                        {
                            ply_2_win += 2;
                            print_winner();
                            return;
                        }
                        if (bul == 2)
                        {
                            printf("No more bullets!!\n");
                            load_bullet(2);
                            bul = 0;
                        }
                    }
                }
            }
        }
        else
        {
            printf("invalid Choice!!\n");
        }
    }
}

void select_round()
{
    static int level = 1;
    while (level < 4)
    {
        switch (level)
        {
        case 1:
            level_1();
            level++;
            break;

        case 2:
            level_2();
            level++;
            break;

        case 3:
            level_3();
            level++;
            break;

        default:
            break;
        }
    }
    level = 1;
    sleep(1);
    death_round();
    // print_winner();
}

int main()
{
    display_name();
    bullet = (int *)malloc(sizeof(int));
    ply_1_ability = (int *)malloc(sizeof(int));
    ply_2_ability = (int *)malloc(sizeof(int));

    while (ch != 0)
    {
        printf("\nSelect player\n(0) Quit\n(1) Play!!\n(2) Record!!");
        printf("\nSelect :- ");
        fflush(stdin);
        scanf("%d", &ch);
        switch (ch)
        {
        case 0:
            break;

        case 1:
            printf("Enter first player name :- ");
            fflush(stdin);
            gets(p1);
            printf("Enter second player name :- ");
            fflush(stdin);
            gets(p2);
            select_round();
            saveGame();
            break;
        case 2:
            displayGameRecord();
            break;
        default:
            printf("invalid input\n");
            break;
        }
    }
    free(bullet);
    free(ply_1_ability);
    free(ply_2_ability);

    return 0;
}