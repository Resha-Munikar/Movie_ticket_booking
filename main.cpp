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
} addlist;

char ch;
char choice;
char re_add[1];
int search = 0;
int found;
int i = 0;
int n = 0;
int select = 0;
void add_movie();
void view();
void delete_movie();
int code_exists(FILE *fs, int code);
int main()
{
	FILE *fp, *fs;
retry:
	printf("\t************************************\n");
	printf("\t\t====================\n");
	printf("\t\tMOVIE TICKET BOOKING\n");
	printf("\t\t====================\n");
	printf("\t************************************\n");
	printf("\n\t1. Admin");
	printf("\n\t2. User");
	printf("\n\nEnter your choice : ");
	scanf("%d", &select);
	switch (select)
	{
	case 1:
		char uname[30], pwd[25], un[30], pw[25];
		char x;
		fp = fopen("Password.txt", "r");
		if (fp == NULL)
		{
			printf("\nError! File not found");
		}
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
			printf("\n\tLogging in . . . .");
			sleep(3);
			system("cls");
			printf("\n\t\tLogin successful!!!");
			printf("\n");
			printf("\n");
		menu:
			printf("\n");
			printf("\t_______ADMIN OPTIONS_______\n");
			printf("\n");
			printf("\n\tPress A. to add movie");
			printf("\n\tPress B. to show movie list");
			printf("\n\tPress C. to delete movie ");
			printf("\n\tPress D. to edit movie details ");
			printf("\n\tPress E. to exit ");
			fflush(stdin);
			printf("\n\nEnter your choice : ");
			scanf("%c", &choice);
			switch (choice)
			{
			case 'A':
				add_movie();
				goto menu;
				break;
			case 'B':
				view();
				goto menu;
				break;
			case 'C':
				delete_movie();
				goto menu;
				break;
			case 'D':
				break;
			case 'E':
				exit(0);
			default:
				printf("\nWrong choice.");
				printf("\nEnter correct choice.");
				goto menu;
			}
		}
		else
		{
			printf("\n\tWrong username or password.");
			printf("\n\nDo you want to try again?");
			fflush(stdin);
			printf("\nPress 'Y' to continue or 'N' to exit : ");
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
	label:
		printf("\n\t_______USER OPTIONS_______");
		printf("\n");
		printf("\n\tPress A. to View Movie List");
		printf("\n\tPress B. to Book Ticket");
		printf("\n\tPress C. to Cancel Ticket");
		printf("\n\tPress D. to Exit");
		fflush(stdin);
		printf("\n\nEnter your choice : ");
		scanf("%c", &ch);
		switch (ch)
		{
		case 'A':
			view();
			goto label;
			break;
		case 'B':
			break;
		case 'C':
			break;
		case 'D':
			exit(0);
		default:
			printf("\nWrong choice.");
			printf("\nEnter correct choice.");
			goto label;
		}
	default:
		printf("\nInvalid input.");
		printf("\nEnter the correct choice.");
		printf("\n\n");
		goto retry;
	}
	return 0;
}
void add_movie()
{
	FILE *fs;
re_movie:
	fs = fopen("Details.txt", "r+");
	if (fs == NULL)
	{
		printf("\nError! File not found");
		exit(0);
	}
	fflush(stdin);
	printf("Enter movie name: ");
	gets(addlist.name);
	fflush(stdin);
re_code:
	printf("Enter movie code: ");
	scanf("%d", &addlist.code);
	if (code_exists(fs, addlist.code))
	{
		printf("\nThe movie with code %d already exists. Try another code.", addlist.code);
		sleep(2);
		goto re_code;
	}
	printf("Enter movie ticket price: ");
	scanf("%d", &addlist.price);
	fflush(stdin);
	printf("\n");
	fseek(fs, 0, SEEK_END);
	fwrite(&addlist, sizeof(struct record), 1, fs);
	fclose(fs);
	printf("\nMovie added successfully.");
	sleep(2);
	printf("\n");
	printf("\nDo you want to add another movie?[Y/N] : ");
	scanf("%c", &re_add);
	strlwr(re_add);
	if (strcmp(re_add, "y") == 0)
	{
		goto re_movie;
	}
	sleep(1);
	system("cls");
}
void view()
{
	FILE *fs;
	fs = fopen("Details.txt", "r");
	if (fs == NULL)
	{
		printf("\nError! File not found");
		exit(0);
	}
	system("cls");
	printf("\n");
	printf("___________List of ongoing movies details___________\n\n ");
	printf("%-20s %-15s %-15s\n\n", "Movie Name", "Movie Code", "Ticket Price");
	printf("__________________________________________________________");
	while (fread(&addlist, sizeof(struct record), 1, fs) == 1)
	{
		printf("\n %-20s %-15d %-15d", addlist.name, addlist.code, addlist.price);
		printf("\n");
		printf("__________________________________________________________");
	}
	fclose(fs);
	fflush(stdin);
	getchar();
	system("cls");
}
void delete_movie()
{
	FILE *fp, *fs;
	printf("\nEnter the code of movie you want to delete : ");
	scanf("%d", &search);
	fp = fopen("Details.txt", "r");
	if (fp == NULL)
	{
		printf("\nFile not found.");
		exit(0);
	}
	fs = fopen("Temp.txt", "w+");
	if (fs == NULL)
	{
		printf("\nFile not found.");
		exit(0);
	}
	while (fread(&addlist, sizeof(struct record), 1, fp))
	{
		if (addlist.code != search)
		{
			fwrite(&addlist, sizeof(struct record), 1, fs);
		}
		else
		{
			found = 1;
		}
	}
	fclose(fp);
	fclose(fs);
	remove("Details.txt");
	rename("temp.txt", "Details.txt");
	if (found == 1)
	{
		printf("\nMovie with code %d is deleted successfully.", search);
	}
	else
	{
		printf("\nMovie with code %d not found.", search);
	}
	found = 0;
	sleep(3);
	system("cls");
}

int code_exists(FILE *fs, int code)
{
	struct record read_record;
	int code_found = 0;
	while (fread(&read_record, sizeof(struct record), 1, fs))
	{
		if (read_record.code == code)
		{
			code_found = 1;
			rewind(fs);
			return code_found;
		}
	}

	return code_found;
}
