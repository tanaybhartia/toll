#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct account{
	char name[30];
	char userid[30];
	char password[20];
	int money;
	char carno[20];
	int transaction[10];
}account;

typedef struct Admin{
    char password[20];
    char userid[30];
	int cars;
	int balance;
	int transaction[200];
	char carno[200][20];
}Admin;

void user_prof(account *x,FILE *f1);
void admin_prof(Admin *y,FILE *f1);
void options();

void user_signup()
{
	FILE *f1;
	account *x=malloc(sizeof(account));
	char temp[30];
	f1=fopen("name.txt","rb+");
	printf("Your Name: ");
	getchar();
	scanf("%[^\n]s",x->name);
	fflush(stdin);
	printf("Enter a UserId(No spaces):");
	scanf("%s",x->userid);
	printf("Password: ");
	scanf("%s",x->password);
	printf("Car Number: ");
	scanf("%s",x->carno);
	printf("Enter amount:");
	scanf("%d",&(x->money));
	fwrite(x,sizeof(account),1,f1);
	fclose(f1);
	options();
}

void admin_login()
{
	FILE *f1;
	Admin *y=malloc(sizeof(Admin));
	char tempname[30],temppass[30];
	int count=0;
	printf("Enter Userid:");
	scanf("%s",tempname);
	fflush(stdin);
	printf("Enter Password:");
	scanf("%s",temppass);
	fflush(stdin);
	f1=fopen("admin.txt","ab+");
	fseek(f1,0,SEEK_SET);
	while(!feof(f1))
	{
		fread(y,sizeof(Admin),1,f1);
		printf("%s %s",y->userid,y->password);
		if(strcmp(tempname,y->userid)==0 && strcmp(temppass,y->password) == 0)
		{
			admin_prof(y,f1);
			break;
		}
		else
		{
			printf("Wrong Credentials.\n");
			break;
		}
	}
	fclose(f1);
}

void admin_prof(Admin *y,FILE *f1)
{
	int i,count,choice;
	printf("Choose an action. \n");
	printf("1. Check total balance. \n");
	printf("2. View all transcations. \n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("Total income is: %d",y->balance);
			break;
		case 2:
			printf("Transactions of the day are: \n");
			for(i=0;i<y->cars;i++)
			{
				printf("%d. %d from Car NO. : %s \n",i+1,y->transaction[i],y->carno[i]);
			}
			break;
		default:
			printf("Wrong choice. \n Press Enter to Exit.");
	}
}

void user_login()
{
	FILE *f1,*f2;
	account *x=malloc(sizeof(account));
	char tempname[30],temppass[30],temp[30],*A;
	int count=0;
	f1 = fopen("name.txt","rb+");
	printf("UserId: ");
	scanf("%s",tempname);
	fflush(stdin);
	A=getpass("Password : ");
	strcpy(temppass,A);
	fseek(f1,0,SEEK_SET);
	while(!feof(f1))
	{
		fread(x,sizeof(account),1,f1);
		if(strcmp(tempname,x->userid) == 0 && strcmp(temppass,x->password) == 0)
		{
			count = 1;
			break;
		}
	}
	if(count == 0)
		printf("Username or password wrong \n");
	else
	{
		user_prof(x,f1);
	}
	fclose(f1);
}

void user_prof(account *x,FILE *f1)
{
	int choice,amnt,i,temp,temp1;
	printf("Enter your choice: \n");
	printf("1. Check Total Balance. \n");
	printf("2. Add money to the wallet. \n");
	printf("3. View last 10 transactions. \n");
	printf("4. View your profile. \n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("Your total balance is: %d",x->money);
			break;
		case 2:
			printf("Enter amount to be added: ");
			scanf("%d",&amnt);
			x->money += amnt;
			temp1 = amnt;
			for(i=0;i<10;i++)
			{
				temp=x->transaction[i];
				x->transaction[i]=temp1;
				temp1=temp;
			}
			fseek(f1,-sizeof(account),SEEK_CUR);
			fwrite(x,sizeof(account),1,f1);
			break;
		case 3:
			printf("Your last transactions are: \n");
			for(i=0;i<10;i++)
			{
				printf("%d. %d \n",i+1,x->transaction[i]);
			}
			break;
		case 4:
			printf("Name : %s \n",x->name);
			printf("Car No. : %s \n",x->carno);
			break;
		default:
			printf("Wrong Choice. \n Press enter to exit.\n");
			break;
	}
}

void transact()
{
	FILE *f1,*f2;
	char car[20],tempc[20],tempc1[20];
	int count=0,i,amnt,temp,temp1;
	account *x=malloc(sizeof(account));
	Admin *y=malloc(sizeof(Admin));
	f1=fopen("name.txt","rb+");
	f2=fopen("admin.txt","rb+");
	printf("Enter Your Car No. : ");
	scanf("%s",car);
	while(!feof(f1))
	{
		fread(x,sizeof(account),1,f1);
		if(strcmp(x->carno,car) == 0)
		{
			count = 1;
			break;
		}
	}
	fseek(f2,0,SEEK_SET);
	fread(y,sizeof(Admin),1,f2);
	fclose(f2);
	f2=fopen("admin.txt","wb+");
	if(count == 0)
		printf("Invalid car details. \n");
	else
	{
		printf("Enter Amount to be deducted: ");
		scanf("%d",&amnt);
		if(x->money >= amnt)
		{
			x->money = x->money - amnt;
			temp1 = -amnt;
			for(i=0;i<10;i++)
			{
				temp=x->transaction[i];
				x->transaction[i]=temp1;
				temp1=temp;
			}
			fseek(f1,-sizeof(account),SEEK_CUR);
			fwrite(x,sizeof(account),1,f1);
			y->balance += amnt;
			y->cars += 1;
			strcpy(tempc1,car);
			temp1 = amnt;
			for(i=0;i<y->cars;i++)
			{
				temp=y->transaction[i];
				y->transaction[i]=temp1;
				temp1=temp;
				strcpy(tempc,y->carno[i]);
				strcpy(y->carno[i],tempc1);
				strcpy(tempc1,tempc);
			}
			fwrite(y,sizeof(Admin),1,f2);
		}
		else
		{
			printf("Not sufficient funds.\n");
		}
	}
	fclose(f1);
	fclose(f2);
	options();
}

void options()
{
	int choice,choice1,count=0;
	char ch;
	printf("Choose an alternative: \n");
	printf("1. Do transaction. \n");
	printf("2. Login. \n");
	printf("3. Sign-up. \n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			transact();
			break;
		case 2:
			printf("Enter your choice of login: \n");
			printf("1. Admin \n");
			printf("2. User \n");
			scanf("%d",&choice1);
			switch(choice1)
			{
				case 1:
					admin_login();
					break;
				case 2:
					user_login();
					break;
				default:
					printf("Wrong choice. \n Press Enter to Exit.");
					break;
			}
			break;
		case 3:
			user_signup();
			break;
		default:
			printf("Wrong choice.\n Choose Again.\n");
			options();
	}
}

int main()
{
	options();
	return 0;
}
