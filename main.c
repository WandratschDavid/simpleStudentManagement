//*********************************************************************
//
//                  H T L - W E L S  /  Klasse 3BHIT
//
//---------------------------------------------------------------------
// Programm           : simpleStudentManagement
//
// Ersteller          : David Wandratsch
//
// Erstelldatum       : 2021-05-27
//
// Abgabedatum        : 2021-06-01
//
// Kurzbeschreibung   : Programm zum Erstellen einer Schülerliste und
//                   dem Anzeigen verschiedener Informationen über ihn
//
// GitHub Repository  : https://github.com/WandratschDavid/simpleStudentManagement
//*********************************************************************

// including standard librarys
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

// global variable definition
#define MAXLENGTH 150
char filePath[] = "D:\\Schuljahr 2020_21\\SEW\\Exercises\\simpleStudentManagement\\database\\database.sew";

// defining a struct for the student
typedef struct
{
    int catNum;
    char name[50];
    int grade;
} STUDENT;

// first declaration of the functions
void createFile();
void getInfo();
void getAvgGrade();

// main program
int main()
{
    bool exitProgram = 0;
    char userInput;

    do
    {
        printf("Please choose one of the following options!:\n");
        printf("Create (c)\n");
        printf("Info (i)\n");
        printf("Average (a)\n");
        printf("Exit (e)\n");
        fflush(stdin);
        scanf("%c", &userInput);

        switch (userInput)
        {
            case 'c':
                createFile();
                break;

            case 'i':
                getInfo();
                break;

            case 'a':
                getAvgGrade();
                break;

            case 'e':
                exitProgram = 1;
                break;

            default:
                printf("\nPlease only enter a single letter from one of the brackets above!\n");
        }
    }
    while (!exitProgram);

    return 0;
}


//********************************************************************
// Funktion        : createFile
//
// Kurzbeschreibung: creates a file and writes all the students to it
//********************************************************************
void createFile()
{
    STUDENT database[512];
    FILE *file = fopen(filePath, "wb");
    int count = 0;
    char* firstName = malloc(MAXLENGTH);
    char* surName = malloc((2 * MAXLENGTH) + 1);
    int grade;
    bool finishedInput = 0;

    do
    {
        printf("Bitte geben Sie 'e' ein um die Eingabe zu beenden!\n");

        printf("Vorname: ");
        fflush(stdin);
        gets(firstName);

        if(strcmp(firstName, "e") == 0)
        {
            finishedInput = 1;
        }
        else
        {
            printf("Nachname: ");
            fflush(stdin);
            gets(surName);

            strcat(surName, " ");
            strcat(surName, firstName);

            printf("Note: ");
            fflush(stdin);
            scanf("%i", &grade);

            database[count].catNum = count + 1;
            strcpy(database[count].name, surName);
            database[count].grade = grade;
        }
        count++;
    }
    while (!finishedInput);

    fwrite(database, sizeof (STUDENT), count - 1, file);
    fclose(file);
}


//********************************************************************
// Funktion        : getInfo
//
// Kurzbeschreibung: searches for the given student
//                   and prints the details about him
//********************************************************************
void getInfo()
{
    FILE *file = fopen(filePath, "rb");
    int catNum = 0;
    STUDENT student;

    if(file == NULL)
    {
        printf("Error opening the file!\n");
    }
    else
    {
        printf("Please enter the catalog number of the student you are looking for!\n");
        fflush(stdin);
        scanf("%d", &catNum);

        fseek(file, (catNum - 1) * sizeof (STUDENT), 0);
        fread(&student, sizeof (STUDENT), 1, file);

        printf("Student found!\n");
        printf("Catalog Number: %d\n", student.catNum);
        printf("Name: %s\n", student.name);
        printf("Grade: %d\n", student.grade);
    }
    fclose(file);
}


//********************************************************************
// Funktion        : getAvgGrade
//
// Kurzbeschreibung: calculates the average grade of all students
//********************************************************************
void getAvgGrade()
{
    FILE *file = fopen(filePath, "rb");
    STUDENT students[512];
    int count = 0;
    double sum;
    double avg;

    if(file == NULL)
    {
        printf("Error opening the file!\n");
    }
    else
    {
        while ((fread(&students[count], sizeof (STUDENT), 1, file)) != 0)
        {
            count++;
        }

        for(int i = 0; i < count; i++)
        {
            sum = sum + students[i].grade;
        }

        avg = sum / count;

        printf("Average grade of all students: %f\n", avg);
    }
}