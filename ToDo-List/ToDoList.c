#include <stdio.h>
#include <time.h>
#define SIZE 1000

char data[SIZE];

void saveData(void)
{
    FILE *file = fopen("ToDoList.txt", "a");
    time_t t = time(NULL);
    printf("Enter Task: ");
    fflush(stdin);
    gets(data);
    fputs(ctime(&t), file);
    fputs(data, file);
    fprintf(file, "\n");
    printf("Task Saved!!\n");
    fclose(file);
}

void removeTask(void)
{
    return;
}

void getData(void)
{
    FILE *file = fopen("ToDoList.txt", "r");
    if (!file)
    {
        printf("First Create Your Task!!\n");
        return;
    }
    while (fgets(data, 1000, file))
    {
        printf("%s", data);
        fgets(data, 1000, file);
        printf("%s\n", data);
    }
    fclose(file);
}

int main()
{
    int choice = 0;

    do
    {
        printf("0) Exit!!\n1) Save Task!!\n2) Show All Tasks!!\nSelect: ");
        fflush(stdin);
        scanf("%d", &choice);

        switch (choice)
        {
        case 0:
            break;
        case 1:
            saveData();
            break;
        case 2:
            getData();
            break;
        default:
            printf("Inalid Input!!\n");
            break;
        }
    } while (choice);

    return 0;
}