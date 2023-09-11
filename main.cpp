// Movie ticket booking using C
#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //for sleep function
struct record
{
	char name[50];
	int code;
	int price;
} addlist, test;

int ch = 0;
int oldtotal;
char choice;
char re_add[1];

int i = 0;
int n = 0;

int main()
{
	FILE *fp, *fs;
label:
	// displaying the menu
	printf("\t************************************\n");
	printf("\t\t====================\n");
	printf("\t\tMOVIE TICKET BOOKING\n");
	printf("\t\t====================\n");
	printf("\t************************************\n");
	printf("\n\tPress 1 for Admin");
	printf("\n\tPress 2 to View Movie List");
	printf("\n\tPress 3 to Book Ticket");
	printf("\n\tPress 4 to Cancel Ticket");
	printf("\n\tPress 5 to Exit");
	printf("\n\nEnter your choice : ");
	scanf("%d", &ch);
	switch (ch)
	{
	case 1:
		fp = fopen("Password.txt", "r");
		if (fp == NULL)
		{
			printf("\nError! File not found");
		}
		char uname[30], pwd[25], un[30], pw[25];
		char x;
		fscanf(fp, "%s%s", uname, pwd);
	flag:
		fflush(stdin);
		printf("\n\tEnter username : ");
		gets(un);
		fflush(stdin);
		printf("\n\tEnter password : ");
		gets(pw);
		// comparing the username and password given by the user
		if ((strcmp(uname, un) == 0) && (strcmp(pwd, pw) == 0))
		{
			printf("\n\tLogin Successful!!!");
			sleep(2);
			system("cls");
		// Displaying the admin's portal
		retry:
			printf("\n");
			printf("\t\tADMIN OPTIONS\n");
			printf("\nPress A. to add movie");
			printf("\nPress B. to show movie list");
			printf("\nPress C. to delete movie ");
			printf("\nPress D. to edit movie details ");
			printf("\nPress E. to return back to main menu ");
			printf("\nPress F. to exit ");
			fflush(stdin);
			printf("\n\nEnter your choice : ");
			scanf("%c", &choice);
			;
			switch (choice)
			{
			case 'A':
			re_movie:
				fs = fopen("Details.txt", "a+");
				if (fs == NULL)
				{
					printf("\nError! File not found");
					exit(0);
				}

				fflush(stdin);
				printf("Enter movie name: ");
				gets(addlist.name);
				fflush(stdin);
				printf("Enter movie code: ");
				scanf("%d", &addlist.code);
				printf("Enter movie ticket price: ");
				scanf("%d", &addlist.price);
				fflush(stdin);
				printf("\n");
				fwrite(&addlist, sizeof(struct record), 1, fs);
				fclose(fs);
				printf("\nMovie added successfully.");

				printf("\nDo you want to add another movie?[Y/N]");
				strlwr(re_add);
				scanf("%c", &re_add);
				if (strcmp(re_add, "y") == 0)
				{
					goto re_movie;
				}
				else
				{
					sleep(2);
					goto retry;
				}
				break;
			case 'B':
				fs = fopen("Details.txt", "r");
				if (fs == NULL)
				{
					printf("\nError! File not found");
					exit(0);
				}

				system("cls");
				printf("\n");
				printf("List of ongoing movies details:\n\n ");
				printf("Movie name\t\tMovie code\t\tMovie ticket price");
				printf("\n");
				while (fread(&test, sizeof(struct record), 1, fs))
				{
					printf("\n");
					printf(" %s\t\t\t%d\t\t\t%d\n", test.name, test.code, test.price);
					printf("____________________________________________________________________");
				}
				fclose(fs);
				fflush(stdin);
				getchar();
				system("cls");
				goto retry;
				break;
			case 'E':
				goto label;
				break;
			case 'F':
				exit(0);
			default:
				printf("\nInvalid input");
				goto retry;
			}
		}
		else
		{
			printf("\n\tWrong username or password");
			printf("\n\nDo you want to try again?");
			fflush(stdin);
			printf("\nPress 'Y' to continue or 'N' to exit.\n");
			x = getchar();
			{
				if (x == 'y' || x == 'Y')
				{
					system("cls");
					goto flag;
				}
				else
				{
					exit(0);
				}
			}
		}
		break;
	case 2:
		fs = fopen("Details.txt", "r");
		if (fs == NULL)
		{
			printf("\nError! File not found");
			exit(0);
		}
		system("cls");
		printf("\n");
		printf("List of ongoing movies details:\n\n ");
		printf("Movie name\t\tMovie code\t\tMovie ticket price");
		printf("\n");
		while (fread(&test, sizeof(addlist), 1, fs))
		{
			printf("\n");
			printf(" %s\t\t\t%d\t\t\t%d\n", test.name, test.code, test.price);
			printf("____________________________________________________________________");
		}
		fclose(fs);
		fflush(stdin);
		getchar();
		system("cls");
		goto label;
		break;
	case 5:
		exit(0);
		break;
	default:
		printf("\nInvalid input.");
		printf("\nEnter between 1-5\n\n");
		goto label;
		break;
	}
	return 0;
}
