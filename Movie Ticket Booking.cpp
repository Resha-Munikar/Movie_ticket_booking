//Movie ticket booking using C
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>//for sleep function
struct record{
	char name[50];
	int code;
	int price;
}addlist[50],test;
int i=0,n=0;
int ch=0;
int oldtotal;
char choice;
void menu();
void secondmenu();
void signin();
void add();
void listing();
int main()
{
	label:
		menu();
	switch(ch)
	{
		case 1:
			signin();
			secondmenu();	
			switch(choice)
			{
				fflush(stdin);
				case 'A':
					add();
					break;
				case 'B':
					listing();
					break;
				case 'C':
					menu();
					break;
			}
		case 2:
			listing();
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
void menu()
{
	printf("\t************************************\n");
	printf("\t\t====================\n");
	printf("\t\tMOVIE TICKET BOOKING\n");
	printf("\t\t====================\n");
	printf("\t************************************\n");
	printf("\n\tPress 1 to Sign In");
	printf("\n\tPress 2 to View Movie List");
	printf("\n\tPress 3 to Book Ticket");
	printf("\n\tPress 4 to Cancel Ticket");
	printf("\n\tPress 5 to Exit");
	printf("\n\nEnter your choice : ");
	scanf("%d",&ch);
}
void secondmenu()
{
	printf("\t\tADMIN OPTIONS\n");
	printf("\nPress A. to add movie");
	printf("\nPress B. to show movie list");
	printf("\nPress C. to delete movie ");		
	printf("\nPress D. to edit movie details ");
	printf("\nPress E. to return back to main menu ");
	printf("\nPress F. to exit ");
	printf("\n\nEnter your choice : ");
	scanf("%c",&choice);
				
}
void signin()
{
	FILE *fp;
	fp=fopen("Password.txt","r");
	if(fp==NULL)
	{
		printf("\nError! File not found");
		exit(0);
	}
	char uname[30],pwd[25],un[30],pw[25];
	char x;
	fscanf(fp,"%s%s",uname,pwd);
	flag:
	fflush(stdin);
	printf("\n\tEnter username : ");
	gets(un);
	fflush(stdin);
	printf("\n\tEnter password : ");
	gets(pw);
	//comparing the username and password given by the user 
	if((strcmp(uname,un)==0)&&(strcmp(pwd,pw)==0))
	{
		printf("\n\t\tLogin Successful!!!\n");
		sleep(2);
		system ("cls");
	}
	else
	{
		printf("\n\tWrong username or password");
		printf("\n\nDo you want to try again?");
		fflush(stdin);
		printf("\nPress 'Y' to continue or 'N' to exit.\n");
		x=getchar();
		{
			if(x=='y'||x=='Y')
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
	fclose(fp);
}
void add()
{
	FILE *fs;
	fs=fopen("Details.txt","a+");
	if(fs==NULL)
		{
			printf("\nError! File not found");
		}
	printf("How many records do you want to add? \n");
	scanf("%d",&n);
	oldtotal=n;
	for(i=0;i<n;i++)
	{
		fflush(stdin);
		printf("Enter movie name: ");
		gets(addlist[i].name);
		fflush(stdin);
		printf("Enter movie code: ");
		scanf("%d",&addlist[i].code);
		printf("Enter movie ticket price: ");
		scanf("%d",&addlist[i].price);
		fflush(stdin);
		printf("\n");
		fwrite(&addlist[i],sizeof (addlist),1,fs);
	}
	fclose(fs);
}
void listing()
{
	FILE *fs;
	fs=fopen("Details.txt","r");
	if(fs==NULL)
	{
		printf("\nError! File not found");
	}
	rewind(fs);
	system("cls");
	printf("\n");
	printf("List of ongoing movies details:\n\n ");
	printf("Movie name\t\tMovie code\t\tMovie ticket price");
	printf("\n");
	while(fread(&test, sizeof (addlist),1,fs))
	{
		printf("\n");
		printf(" %s\t\t\t%d\t\t\t%d\n",test.name,test.code,test.price);
		printf("____________________________________________________________________");
	}
	fclose(fs);
}  
