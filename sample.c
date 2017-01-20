#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct account{
	char name[30];
	char userid[30];
	char password[20];
	long double money;
	char carno[20];
	int trans;
	long double transaction[10];
}account;

typedef struct Admin{
    	char password[20];
    	char userid[30];
	int cars;
	long double balance;
	long double transaction[200];
	char carno[200][20];
}Admin;

void user_prof(account *x,FILE *f1);
void admin_prof(Admin *y,FILE *f1);
void admin_login();
void user_login();
void user_signup();
void transact();

int main()
{
	/*FILE *f1;
	f1=fopen("admin.txt","wb+");
	Admin *y=malloc(sizeof(Admin));
	strcpy(y->userid,"tanay_97");
	strcpy(y->password,"123456");
	y->cars=0;
	y->balance=0;
	fwrite(y,sizeof(Admin),1,f1);
	fclose(f1);
	//main();*/
	int choice,choice1,count=0,d;
	char ch;	
	printf("Welcome to Toll Plaza.\n");
	printf("Do you have an account(Press '1' if yes, else press '2') : ");
	scanf("%d",&d);
	if(d == 1)
	{
		printf("Choose an alternative. \n");
		printf("1. Do transaction. \n");
		printf("2. Login. \n");
		printf("3. Exit. \n");
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
				exit(0);
				break;
			default:
				printf("Wrong Choice.\nTry again.\n");
				main();
				break;
		}
	}
	else if(d == 2)
	{
		printf("Choose an alternative.\n");
		printf("1. Sign-up. \n");
		printf("2. Exit. \n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				user_signup();
				break;
			case 2:
				exit(0);
				break;
			default:
				printf("Wrong choice.\n Choose Again.\n");
				main();
				break;	
		}
	}
	else
	{
		printf("Wrong Choice.\nTry Again.\n");
		main();
	}
	return 0;
}

void user_signup()
{
	FILE *f1;
	account *x=malloc(sizeof(account));
	account *y=malloc(sizeof(account));
	char temp[30],*A,*B;
	f1=fopen("name.txt","rb+");
	printf("Enter a UserId(No spaces):");
	scanf("%s",x->userid);
	printf("Car Number: ");
	scanf("%s",x->carno);
	fseek(f1,0,SEEK_SET);
	while(!feof(f1))
	{
		fread(y,sizeof(account),1,f1);
		if(strcmp(y->userid,x->userid) == 0)
		{
			printf("Username already exists. Please try again.\n");
			user_signup();
		}
		if(strcmp(y->carno,x->carno) == 0)
		{
			printf("Car already registered. Try with another car.\n");
			user_signup();
		}
	}
	fclose(f1);
	printf("Your Name: ");
	getchar();
	fflush(stdin);
	scanf("%[^\n]s",x->name);
	fflush(stdin);
	f1 = fopen("name.txt","rb+");
	A=getpass("Password : ");
	B=getpass("Confirm Password : ");
	while(strcmp(A,B) != 0)
	{
		printf("Passwords don't match. Try again. \n");
		A=getpass("Password : ");
		B=getpass("Confirm Password : ");
	}
	strcpy(x->password,A);
	printf("Enter money to be added in your wallet:");
	scanf("%Lf",&(x->money));
	x->trans=0;
	fwrite(x,sizeof(account),1,f1);
	fclose(f1);
	printf("You are successfully registered.\n");
	main();
}

void admin_login()
{
	FILE *f1;
	Admin *y=malloc(sizeof(Admin));
	char tempname[30],temppass[30],*A;
	int count=0;
	printf("Enter Userid:");
	scanf("%s",tempname);
	fflush(stdin);
	A=getpass("Password : ");
	strcpy(temppass,A);
	fflush(stdin);
	f1=fopen("admin.txt","ab+");
	fseek(f1,0,SEEK_SET);
	while(!feof(f1))
	{
		fread(y,sizeof(Admin),1,f1);
		if(strcmp(tempname,y->userid)==0 && strcmp(temppass,y->password) == 0)
		{
			admin_prof(y,f1);
			break;
		}
		else
		{
			printf("Wrong Credentials.\nTry Again.\n");
			admin_login();
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
	printf("3. Logout. \n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("Total income is: %Lf\n",y->balance);
			admin_prof(y,f1);
			break;
		case 2:
			printf("Transactions of the day are: \n");
			for(i=0;i<y->cars;i++)
			{
				printf("%d. %Lf from Car NO. : %s \n",i+1,y->transaction[i],y->carno[i]);
			}
			admin_prof(y,f1);
			break;
		case 3:
			main();
			break;
		default:
			printf("Wrong choice.\nTry Again.\n");
			admin_prof(y,f1);
			break;
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
	{
		printf("Username or password wrong.\nTry Again.\n");
		user_login();
	}
	else
	{
		user_prof(x,f1);
	}
	fclose(f1);
}

void user_prof(account *x,FILE *f1)
{
	int choice,i;
	long double amnt,temp,temp1;
	printf("Enter your choice: \n");
	printf("1. Check Total Balance. \n");
	printf("2. Add money to the wallet. \n");
	printf("3. View last 10 transactions. \n");
	printf("4. View your profile. \n");
	printf("5. Logout. \n");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("Your total balance is: %Lf\n",x->money);
			user_prof(x,f1);
			break;
		case 2:
			printf("Enter amount to be added: ");
			scanf("%Lf",&amnt);
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
			user_prof(x,f1);
			break;
		case 3:
			printf("Your last transactions are: \n");
			for(i=0;i<x->trans;i++)
			{
				printf("%d. %Lf \n",i+1,x->transaction[i]);
			}
			user_prof(x,f1);
			break;
		case 4:
			printf("Name : %s \n",x->name);
			printf("Car No. : %s \n",x->carno);
			printf("Total balance : %Lf \n",x->money);
			user_prof(x,f1);
			break;

		case 5:
			main();
			break;
		default:
			printf("Wrong Choice.\nTry Again.\n");
			user_prof(x,f1);
			break;
	}
}

void transact()
{
	FILE *f1,*f2;
	char car[20],tempc[20],tempc1[20];
	int count=0,i;
	long double amnt,temp,temp1;
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
	if(count == 0)
		printf("Invalid car details. \n");
	else
	{
		f2=fopen("admin.txt","wb+");
		printf("Enter Amount to be deducted: ");
		scanf("%Lf",&amnt);
		if(x->money >= amnt)
		{
			x->money = x->money - amnt;
			temp1 = -amnt;
			x->trans += 1;
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
		fclose(f2);
	}
	fclose(f1);
	main();
}

/*void options()
{
	int choice,choice1,count=0;
	char ch;
	printf("Welcome to Toll Plaza.\n");
	printf("Choose an alternative: \n");
	printf("1. Do transaction. \n");
	printf("2. Login. \n");
	printf("3. Sign-up. \n");
	printf("4. Exit. \n");
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
		case 4:
			return;
			break;
		default:
			printf("Wrong choice.\n Choose Again.\n");
			main();
			break;
	}
}*/

