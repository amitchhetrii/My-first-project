#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket
{
    int ticketNo;
    char name[50];
    int age;
    char gender[10];
    char train[50];
    char source[50];
    char destination[50];
};

void bookTicket();
void viewTickets();
void cancelTicket();
void searchTicket();

int main()
{
    int choice;

    while (1)
    {
        printf("\n====================================");
        printf("\n RAILWAY RESERVATION MANAGEMENT ");
        printf("\n====================================");

        printf("\n1. Book Ticket");
        printf("\n2. View All Tickets");
        printf("\n3. Search Ticket");
        printf("\n4. Cancel Ticket");
        printf("\n5. Exit");

        printf("\n\nEnter Your Choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid Input!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice)
        {
            case 1:
                bookTicket();
                break;

            case 2:
                viewTickets();
                break;

            case 3:
                searchTicket();
                break;

            case 4:
                cancelTicket();
                break;

            case 5:
                printf("\nThank You!\n");
                exit(0);

            default:
                printf("\nInvalid Choice!\n");
        }
    }

    return 0;
}

void bookTicket()
{
    FILE *fp;
    struct Ticket t;

    fp = fopen("tickets.dat", "ab");

    if (fp == NULL)
    {
        printf("File Error!\n");
        return;
    }

    printf("\nEnter Ticket Number: ");
    scanf("%d", &t.ticketNo);

    if (t.ticketNo <= 0)
    {
        printf("Ticket Number must be positive!\n");
        fclose(fp);
        return;
    }

    printf("Enter Passenger Name: ");
    scanf(" %[^\n]", t.name);

    if (strlen(t.name) > 50)
    {
        printf("Name too long!\n");
        fclose(fp);
        return;
    }

    printf("Enter Age: ");
    scanf("%d", &t.age);

    if (t.age < 18 || t.age > 60)
    {
        printf("Age must be between 18 and 60!\n");
        fclose(fp);
        return;
    }

    printf("Enter Gender: ");
    scanf("%s", t.gender);

    printf("Enter Train Name: ");
    scanf(" %[^\n]", t.train);

    printf("Enter Source Station: ");
    scanf(" %[^\n]", t.source);

    printf("Enter Destination Station: ");
    scanf(" %[^\n]", t.destination);

    
    if (strlen(t.destination) > 50)
    {
        printf("Destination name too long!\n");
        fclose(fp);
        return;
    }

    fwrite(&t, sizeof(t), 1, fp);

    fclose(fp);

    printf("\nTicket Booked Successfully!\n");
}

void viewTickets()
{
    FILE *fp;
    struct Ticket t;

    fp = fopen("tickets.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Ticket Records Found!\n");
        return;
    }

    printf("\n================ TICKET RECORDS ================\n");

    while (fread(&t, sizeof(t), 1, fp))
    {
        printf("\nTicket No      : %d", t.ticketNo);
        printf("\nPassenger Name : %s", t.name);
        printf("\nAge            : %d", t.age);
        printf("\nGender         : %s", t.gender);
        printf("\nTrain Name     : %s", t.train);
        printf("\nFrom           : %s", t.source);
        printf("\nTo             : %s", t.destination);

        printf("\n-----------------------------------------------\n");
    }

    fclose(fp);
}

void searchTicket()
{
    FILE *fp;
    struct Ticket t;
    int ticketNo, found = 0;

    fp = fopen("tickets.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    printf("\nEnter Ticket Number to Search: ");
    scanf("%d", &ticketNo);

    while (fread(&t, sizeof(t), 1, fp))
    {
        if (t.ticketNo == ticketNo)
        {
            found = 1;

            printf("\n=========== TICKET FOUND ===========");

            printf("\nTicket No      : %d", t.ticketNo);
            printf("\nPassenger Name : %s", t.name);
            printf("\nAge            : %d", t.age);
            printf("\nGender         : %s", t.gender);
            printf("\nTrain Name     : %s", t.train);
            printf("\nFrom           : %s", t.source);
            printf("\nTo             : %s", t.destination);

            printf("\n====================================\n");
        }
    }

    if (!found)
    {
        printf("\nTicket Not Found!\n");
    }

    fclose(fp);
}

void cancelTicket()
{
    FILE *fp, *temp;
    struct Ticket t;
    int ticketNo, found = 0;

    fp = fopen("tickets.dat", "rb");

    if (fp == NULL)
    {
        printf("\nNo Records Found!\n");
        return;
    }

    temp = fopen("temp.dat", "wb");

    printf("\nEnter Ticket Number to Cancel: ");
    scanf("%d", &ticketNo);

    while (fread(&t, sizeof(t), 1, fp))
    {
        if (t.ticketNo == ticketNo)
        {
            found = 1;
            printf("\nTicket Cancelled Successfully!\n");
        }
        else
        {
            fwrite(&t, sizeof(t), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("tickets.dat");
    rename("temp.dat", "tickets.dat");

    if (!found)
    {
        printf("\nTicket Not Found!\n");
    }
}