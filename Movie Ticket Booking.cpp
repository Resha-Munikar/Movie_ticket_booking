//Movie ticket booking using C
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
	int ch;
	FILE *fp;
	label:
	//displaying the menu
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
	scanf("%d",&ch);
	switch(ch)
	{
		case 1:
			fp=fopen("Password.txt","r");
			if(fp==NULL)
			{
				printf("\nError! File not found");
			}
			char uname[30],pwd[25],un[30],pw[25];
			char x;
			fscanf(fp,"%s%s",uname,pwd);
			flag:
			fflush(stdin);
			printf("\nEnter username : ");
			gets(un);
			fflush(stdin);
			printf("\nEnter password : ");
			gets(pw);
			//comparing the username and password given by the user 
			if((strcmp(uname,un)==0)&&(strcmp(pwd,pw)==0))
			{
				printf("\n\tLogin Successful!!!");
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
						goto flag;
					}
					else
					{
						exit(0);
					}
				}
			}
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
