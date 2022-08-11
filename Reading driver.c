
#include<stdio.h>
#include<stdlib.h>

struct AccountHolder
{
    char name[50] ;
	char AccountNumber[50];
    int pin;
    int balance;
};

int main()
{
    FILE *fp;
    struct AccountHolder s;
	fp = fopen("Account_Details.dat", "rb");

    if(fp == NULL)
    {
        printf("Error opening file\n");
        exit(1);
    }

    while( fread(&s, sizeof(struct AccountHolder), 1, fp) == 1 )
    {
		printf("Name: %s \n", s.name);
        printf("Account Number: %s \n", s.AccountNumber);
        printf("pin: %d \n", s.pin);
        printf("Account Balance: %d \n\n", s.balance);
    }

    fclose(fp);
    return 0;
}

