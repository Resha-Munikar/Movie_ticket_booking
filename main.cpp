// Movie ticket booking using C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //for sleep function
struct record
{
	char name[50];
	char genre[10];
	int code;
	int price;
} addlist;
struct oldrecord 
{
	char person_name[50];
	long long int mobile_number;
	int seat_reserved;
	int total_ticketprice;
	char movie_name[50];
	int price_per;
}test;
char ch;
char choice;
char re_add[1];
char re_delete[1];
int select = 0;
void add_movie();
void view();
void book();
void reserved_list();
char a; 
int movie_code; 
void delete_movie();
int code_exists(FILE *fs, int code);
	FILE *fp, *fs,*ufp;
int main()
{
retry:
	system("COLOR 09");
	printf("\t\t\t\t**************************************************\n");
	printf("\t\t\t\t\t\t====================\n");
	printf("\t\t\t\t\t\tMOVIE TICKET BOOKING\n");
	printf("\t\t\t\t\t\t====================\n");
	printf("\t\t\t\t**************************************************\n");
	printf("\n\t\t\t\t1. Admin");
	printf("\n\t\t\t\t2. User");
	printf("\n\n\t\tEnter your choice : ");
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
		printf("\n\t\tEnter username : ");
		gets(un);
		fflush(stdin);
		printf("\n\t\tEnter password : ");
		gets(pw);
		// comparing the username and password given by the user
		if ((strcmp(uname, un) == 0) && (strcmp(pwd, pw) == 0))
		{
			//printf("\n\t\tLogin successful!!!");
			printf("\n");
			printf("\n\t\t\t\t\t\tLogging in . . . .");
			sleep(3);
			system("cls");
		menu:
			printf("\n");
			printf("\t\t\t\t\t__________ADMIN OPTIONS__________\n");
			printf("\n");
			printf("\n\t\t\t\tPress A. to add movie");
			printf("\n\t\t\t\tPress B. to show movie list");
			printf("\n\t\t\t\tPress C. to delete movie ");
			printf("\n\t\t\t\tPress D. to view reserved movie details ");
			printf("\n\t\t\t\tPress E. to go back to main menu");
			printf("\n\t\t\t\tPress F. to exit ");
		again:
			fflush(stdin);
			printf("\n\n\t\tEnter your choice : ");
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
				reserved_list();
				goto menu;
			case 'E':
				system("cls");
				goto retry;
				break;
			case 'F':
				exit(0);
			default:
				printf("\n\t\tWrong choice.");
				printf("\n\t\tEnter correct choice.");
				goto again;
			}
		}
		else
		{
			printf("\n\t\tWrong username or password.");
			printf("\n\n\t\tDo you want to try again?");
			fflush(stdin);
			printf("\n\t\tPress 'Y' to continue or 'N' to exit : ");
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
		printf("\n\t\t\t\t\t__________USER OPTIONS__________");
		printf("\n");
		printf("\n\t\t\t\tPress A. to View Movie List");
		printf("\n\t\t\t\tPress B. to Book Ticket");
		printf("\n\t\t\t\tPress C. to Cancel Ticket");
		printf("\n\t\t\t\tPress D. to Go Back to Main Menu");
		printf("\n\t\t\t\tPress E. to Exit");
		fflush(stdin);
		printf("\n\n\t\tEnter your choice : ");
		scanf("%c", &ch);
		switch (ch)
		{
		case 'A':
			view();
			goto label;
			break;
		case 'B':
			book();
			goto label;
			break;
		case 'C':
			break;
		case'D':
			system("cls");
			goto retry;
			break;
			
		case 'E':
			exit(0);
		default:
			printf("\n\t\tWrong choice.");
			printf("\n\t\tEnter correct choice.");
			goto label;
		}
	default:
		printf("\n\t\tInvalid input.");
		printf("\n\t\tEnter the correct choice.");
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
	printf("\n\t\tEnter movie name: ");
	gets(addlist.name);
	fflush(stdin);
	printf("\n\t\tEnter movie genre: ");
	gets(addlist.genre);
	fflush(stdin);
re_code:
	printf("\n\t\tEnter movie code: ");
	scanf("%d", &addlist.code);
	if (code_exists(fs, addlist.code))
	{
		printf("\n\t\tThe movie with code %d already exists. Try another code.", addlist.code);
		sleep(2);
		goto re_code;
	}
	printf("\n\t\tEnter movie ticket price: ");
	scanf("%d", &addlist.price);
	fflush(stdin);
	printf("\n");
	fseek(fs, 0, SEEK_END);
	fwrite(&addlist, sizeof(struct record), 1, fs);
	fclose(fs);
	printf("\n\t\tMovie added successfully.");
	sleep(2);
	printf("\n");
	printf("\n\t\tDo you want to add another movie?[Y/N] : ");
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
		printf("\n\t\tError! File not found");
		exit(0);
	}
	system("cls");
	printf("\n");
	printf("\t\t\t\t______________List of ongoing movies details______________\n\n ");
	printf("\t\t%-55s %-15s %-15s %-15s\n\n", "Movie Name", "Movie Genre", "Movie Code", "Ticket Price");
	printf("\n");
	printf("\t\t________________________________________________________________________________________________");
	printf("\n");
	while (fread(&addlist, sizeof(struct record), 1, fs) == 1)
	{
		printf("\t\t %-55s %-15s %-15d %-15d", addlist.name, addlist.genre,addlist.code, addlist.price);
		printf("\n");
		printf("\t\t_________________________________________________________________________________________________");
		printf("\n");
	}
	fclose(fs);
	fflush(stdin);
	getchar();
	system("cls");
}
void delete_movie()
{
	int found = 0, search =0;
	FILE *fp, *fs;
	printf("\n\t\tEnter the code of movie you want to delete : ");
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
		printf("\n\t\tMovie with code %d is deleted successfully.", search);
	}
	else
	{
		printf("\n\t\tMovie with code %d not found.", search);
	}
	found=0;
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
void book()
{
	FILE *fs;
	fs = fopen("Details.txt", "r");
	if (fs == NULL)
	{
		printf("\n\t\tError! File not found");
		exit(0);
	}
	system("cls");
	printf("\n");
	printf("\t\t\t\t______________List of ongoing movies details______________\n\n ");
	printf("\t\t%-55s %-15s %-15s %-15s\n\n", "Movie Name", "Movie Genre", "Movie Code", "Ticket Price");
	printf("\n");
	printf("\t______________________________________________________________________________________________________");
	printf("\n");
	while (fread(&addlist, sizeof(struct record), 1, fs) == 1)
	{
		printf("\t %-55s %-15s %-15d %-15d", addlist.name, addlist.genre, addlist.code, addlist.price);
		printf("\n");
		printf("\t______________________________________________________________________________________________________");
		printf("\n");
	}
	fclose(fs);
	
	FILE *fp;
	
	printf("\n\n\t Enter movie code you want to book ticket for :");
	scanf("%d",&movie_code);
	fp = fopen("Details.txt","r");
	if(fp == NULL)
	{
		printf("Error! File does not found !");
		exit(0);

	}
	else
	{	while (fread(&addlist, sizeof(struct record), 1, fp) == 1)
		{
			if(addlist.code==movie_code)
			{	
				printf("\n Record Found\n");
				printf("\n\t\tCode ::%d",addlist.code);
				printf("\n\t\tMovie name ::%s",addlist.name);
				printf("\n\t\tMovie genre ::%s",addlist.genre);
				printf("\n\t\tPrice of ticket::%d",addlist.price);
			}
		}
	}
	fclose(fp);
	ufp=fopen("oldTransaction.txt","r+");
		if(ufp == NULL)
		{
			printf("FIle not Found");
		}
	printf("\n\n\t\t\t\t* _________________Fill Your Deatails_______________  *\n");
		fflush(stdin);
		printf("\n\t\t Name :");
		gets(test.person_name);
		fflush(stdin);
		printf("\n\t\t Mobile number :");
		scanf("%lld",&test.mobile_number);
		ticketrewind:
		printf("\n\t\t Total number of tickets :");
		scanf("%d",&test.seat_reserved);
		if(test.seat_reserved>10)
		{
			printf("\n\t->Sorry! You can't reserve above 10tickets at once. Try again.");
			goto ticketrewind;
		}
		
		test.total_ticketprice = addlist.price * test.seat_reserved;

		printf("\n\t\tYour total expense for %d ticket is %d.",test.seat_reserved,test.total_ticketprice);
		
		strcpy(test.movie_name,addlist.name);
		test.price_per=addlist.price;
		fseek(fs, 0, SEEK_END);
		fwrite(&test, sizeof(struct oldrecord), 1, ufp);
		printf("\n\t\t ***YOUR SEATS ARE RESERVED! ENJOY YOUR MOVIE!!*** \n");
		fclose(ufp);
		printf("\n\t\t Record insert Sucessfull to the old record file");
	
		printf("\n");
		fflush(stdin);
	getchar();
}
void reserved_list()
{
	FILE *fp;

	fp = fopen("oldTransaction.txt","r");
	if(fp == NULL)
	{
		printf("File does not found !");
		exit(0);

	}
	
		system("cls");
		printf("\n");
		printf("\t\t\t\t______________List of reserved movies details______________\n\n ");
		printf("\t\t%-10s %-25s %-22s %-15s %-20s %-15s\n\n", "Customer Name", " Customer Phone Number", "Total Seats Reserved", "Total price","Movie Name","Ticket price per seat");
		printf("\n");
		while (fread(&test, sizeof(struct oldrecord), 1, fp) == 1)
		{
			printf("\t\t %-15s %-25lld %-20d %-13d %-22s %-15d", test.person_name, test.mobile_number,test.seat_reserved, test.total_ticketprice,test.movie_name,test.price_per);
			printf("\n");
			printf("\t\t_________________________________________________________________________________________________________________________");
			printf("\n");
		}
	
	fclose(fp);
	getchar();
}
