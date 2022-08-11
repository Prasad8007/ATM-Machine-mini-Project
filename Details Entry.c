#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct AccountHolder
{
    char name[50];
    char AccountNumber[50];
    int pin;
    int balance;
} emp;

int main()
{
    FILE *fp;
    struct AccountHolder s;
    fp = fopen("Account_Details.dat", "ab");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    printf("Enter Account Holder's name :\n");
    fflush(stdin);
    gets(s.name);
    printf("Enter Account Number :\n");
	fflush(stdin);
	gets(s.AccountNumber);
	printf("Enter PIN :\n");
    scanf("%d",&s.pin);
    printf("Enter Balance :\n");
    scanf("%d",&s.balance);

    fwrite(&s,sizeof(struct AccountHolder),1,fp);

    fclose(fp);

	return 0;
}
