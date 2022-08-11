#include<stdio.h>
#include<stdlib.h>
#include<string.h>


int a=0,b=0,c=0,d=0,Chance=0;
int tempfix=0;

FILE *fp,*ftemp;

struct AccountHolder
{
    char name[50] ;
	char AccountNumber[50];
    int pin;
    int balance;
};
struct AccountHolder s,r;

int MainMenu();
int Withdraw();
int Deposit();
int BalanceInquiry();
int MoneyTransfer();
int SecurityCheck();
int EnhancedSecurity();
int CardVerification();
void update_file(struct AccountHolder);


void update_file(struct AccountHolder a){

	FILE *accounts, *temp;
	struct AccountHolder b;

	accounts = fopen("Account_Details.dat","rb+");
	temp = fopen("temp.dat","wb+");

	while(fread(&b, sizeof(struct AccountHolder), 1, accounts)){
		if(strcmp(b.AccountNumber , a.AccountNumber) != 0){
			fwrite(&b,sizeof(struct AccountHolder),1,temp);
		}
	}
	fwrite(&a,sizeof(struct AccountHolder),1,temp);

	fclose(accounts);
    fclose(temp);
	remove("Account_Details.dat");
    int error = rename("temp.dat","Account_Details.dat");

	if(error)
    tempfix=1;
}

int MainMenu()
{
	int choice;

	printf("\n\n");
	printf("\t\t***************** WELCOME TO ITS ATM *******************\n");
	printf("\t\t*                                                      *\n");
	printf("\t\t*              <1>. WITHDRAW MONEY                     *\n");
	printf("\t\t*              <2>. DEPOSIT MONEY                      *\n");
	printf("\t\t*              <3>. BALANCE ENQUIRY                    *\n");
	printf("\t\t*              <4>. MONEY TRANSFER                     *\n");
	printf("\t\t*                                                      *\n");
	printf("\t\t********************************************************\n\n");

	printf("Enter your choice - ");
	scanf("%d", &choice);

	switch(choice)
	{
		case 1: Withdraw();
		        break;
		case 2: Deposit();
		        break;
		case 3: BalanceInquiry();
		        break;
		case 4: MoneyTransfer();
	            break;
	    default: printf("Wrong Choice , Try Again\n\n");
	             MainMenu();
	}
}

int Withdraw()
{

	int WithdrawalAmount,temp5=0;
	printf("\nEnter amount to be withdrawn\n");
	scanf("%d" , &WithdrawalAmount);


	printf("Are you sure want to withdraw %d Rupee ?\n ", WithdrawalAmount);
	printf("<1>. YES\n <2>. NO\n");
	scanf("%d", &temp5);

	if(temp5==1)
	{

		if(WithdrawalAmount>(s.balance))
		{
			printf("\nCan't Withdraw %d Rupee\n\n",WithdrawalAmount);
		}

		else if(WithdrawalAmount>20000)
		{
			printf("Cannot withdraw more than 10 notes at a time\n");
		}
		else
		{

			s.balance -= WithdrawalAmount;

			update_file(s);

			if(tempfix==1)
			{
				printf("\nTransaction Failed\n");
			}

			else
			{
				printf("\n\n*** Please collect the cash ***\n\n");
				printf("Current account balance is %d \n\n", s.balance);
				printf("**** THANK YOU FOR USING ATM ****\n");
			}
		}
    }
	else if(temp5==2)
	{
		printf("**** THANK YOU FOR USING ATM ****\n");
	}

	else
	{
		a=1;
		EnhancedSecurity();
	}
}

int Deposit()
{

	int temp1 , temp6=0;
	int DepositAmount;
	printf("\nEnter the amount to be deposited\n");
	scanf("%d", &DepositAmount);

	printf("Are you sure , you want to deposit %d amount ?\n", DepositAmount);
	printf("<1>. YES\n<2>. NO\n");
	scanf("%d", &temp6);

	if(temp6==1)
	{
		if(DepositAmount>20000)
		printf("You cannot deposit more than 10 notes at a time\n");

		else
		{


			s.balance = s.balance+DepositAmount;
			update_file(s);

			if(tempfix==1)
			{
				printf("\nTransaction Failed\n");
			}

			else
			{
				printf("Balance has been updated \n\nDo you want the recipt ?\n");
				printf("\n<1>. YES \n<2>. NO\n");
				scanf("%d", &temp1);
				if(temp1==1)
				{
					printf("Please Collect the Recipt\n");
						printf("ABC Bank - \n");
                        printf("Account no.- %c\n",s.AccountNumber);
                        printf("Current account balance is %d \n\n", s.balance);

				}

				else if(temp1==2)
				{
					printf("Thank You for saving paper\n\n");
					printf("**** THANK YOU FOR USING ATM ****\n");
				}
				else
				{
					b=1;
					EnhancedSecurity();
				}
			}
		}
	}

	else if(temp6==2)
	{
		printf("**** THANK YOU FOR USING ATM ****\n");
	}

	else
	{
		b=1;
		EnhancedSecurity();
	}
}

int BalanceInquiry()
{


	int temp2;
	printf("Do you want to check the current balance of your account ?\n");
	printf("\n<1>. YES \n<2>. NO\n");
	scanf("%d",&temp2);

	if(temp2==1)
	{


		printf("Balance - %d\n", s.balance);
	}

	else if(temp2==2)
	{
		printf("**** THANK YOU FOR USING ATM ****\n");
	}

	else
	{
		c=1;
		EnhancedSecurity();
	}
}

int MoneyTransfer()
{


	int TransferAmount=0 , temp3=0 , temp4=0;
	char TransferAccount[50];

	printf("Enter the Account in which you want to transfer the amount\n");
	fflush(stdin);
	gets(TransferAccount);

	printf("\nEnter the amount you want to transfer\n");
	scanf("%d", &TransferAmount);
	if(TransferAmount>40000)
	{


		printf("You cannot transfer %d amount\n", TransferAmount);
	}
	else if(TransferAmount>s.balance)
	{

		printf("Can''t transfer money\n");
	}
	else
	{
		printf("Are you sure you want to transfer %d amount", TransferAmount);
		printf("\n<1>. YES \n<2>. NO\n");
		scanf("%d",&temp3);
		int flg = 0;
		if(temp3==1)
		{
			fp = fopen("Account_Details.dat","rb+");
			while( fread(&r, sizeof(struct AccountHolder), 1, fp))
			{
				if(strcmp(TransferAccount , r.AccountNumber)==0)
				{
					flg = 1;
					break;
				}
			}
			fclose(fp);

			if(flg == 1)
			{
				r.balance = r.balance + TransferAmount;
				s.balance = s.balance - TransferAmount;
				update_file(r);
				update_file(s);

				if(tempfix==1)
				{
					printf("Hitesh\n");
					printf("\nTransaction Failed\n");
				}
				else
				{
					printf("\n%d Amount has been Succesfully Transferred\n",TransferAmount);
					printf("Do you want the recipt?\n");
					printf("<1>. YES \n<2>. NO	 \n");
					scanf("%d",&temp4);
					if(temp4==1)
					{
						printf("Please collect the recipt\n\n");
					}

					else if(temp4==2)
					{
						printf("Thank you for saving paper\n");
					}

					else
					{
						printf(" *** THANKYOU FOR USING ATM ***");
			    	}
				}
			}

			else
			{
				printf("\nTransaction Failed !\n");
			}
		}
		else if(temp3==2)
		{
			printf("Transaction Cancelled\n\n");
			printf(" *** THANKYOU FOR USING ATM ***");
		}

		else
		{
			d=1;
			EnhancedSecurity();
		}

	}
}

int SecurityCheck()
{

	int i=0;
	while(i<3)
	{
		int SecretePIN = 0 , attempt=1;
		printf("Enter your PIN Number - ");
		scanf("%d", &SecretePIN);
		if(SecretePIN == s.pin)
		break;

		else
        {
			printf("\nIncorrect PIN, Please try again\n\n");
			i+=1;

			if(i==3)
			exit(0);
		}
	}

}

int EnhancedSecurity()
{

	Chance++;
	while(Chance!=3)
	{
		printf("\nYou have made a wrong choice , Please try again\n\n ");
		if(a==1)
		{
			Withdraw();
			break;
		}

		else if(b==1)
		{
			Deposit();
			break;
		}

		else if(c==1)
		{
			BalanceInquiry();
			break;
		}

		else if(d==1)
		{
			MoneyTransfer();
			break;
		}
	}

	if(Chance==3)
	{
		printf("Please try again after some time\n\n");
		printf("**** THANKYOU FOR USING ATM ****\n");
	}
}

int CardVerification()
{

    char AcNo[50];
    int pin=0 , flag=0 , count=0  ;

    fp = fopen("Account_Details.dat", "ab+");

    if(fp == NULL)
    {
        exit(1);
    }

	printf("Enter your account number - ");
    fflush(stdin);
    gets(AcNo);


    while( fread(&s, sizeof(struct AccountHolder), 1, fp) == 1 )
    {
		if(strcmp(AcNo , s.AccountNumber)==0)
		{
			flag=1;
			break;
		}
	}

	fclose(fp);

	if(flag==0)
	{
		printf("Please enter a valid card number\n");
	}
	else{

		printf("\nWelcome %s\n",s.name);

		PINMenu:
		printf("\nPlease enter your PIN - ");
		scanf("%d",&pin);

		if(pin==s.pin)
		{
			MainMenu();
		}

		else
		{
			printf("Wrong pin , Please try again\n");
			count++;
			if(count!=3)
				goto PINMenu;
			else
				printf("\nPlease try again after some time.\n");
		}
	}
}

int main()
{
	CardVerification();
	return 0;
}
