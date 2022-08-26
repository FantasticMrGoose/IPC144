/*
    ==================================================
    Assignment 2 (Milestone-3+4):
    ==================================================
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "account.h"  
#include "commonHelpers.h"
#include "accountTicketingUI.h"

#define MIN_CHAR 1
#define MAX_LOGIN 10
#define MAX_PWD 8
#define MAX_DISPLAY 30
#define MIN_AGE 18
#define MAX_AGE 110
#define SEC_CHAR 2
#define MAX_SIZE 101

//function definitions

void getAccount(struct Account* account)
{

    printf("New Account Data (Account#:%d)\n", account->acc_num);                   
    printf("----------------------------------------\n");
    printf("Enter the account type (A=Agent | C=Customer): ");
    account->acc_type = getCharOption("AC");

    printf("\n");

    return;
}

void getUserLogin(struct Account* account)
{
    int i, num_letter, stop, white_space, digit, uppercase, lowercase, symbols;

    printf("User Login Data Input\n");
    printf("----------------------------------------\n");
    stop = 0;
    do
    {
        printf("Enter user login (%d chars max): ", MAX_LOGIN);
        getCString(account->login.login_name, MIN_CHAR, MAX_LOGIN);
        white_space = 0;
        for (i = 0; account->login.login_name[i] != '\0'; i++)
        {
            if (isspace(account->login.login_name[i])) //if a white space is found
            {
                printf("ERROR:  The user login must NOT contain whitespace characters.\n");
                white_space = 1;
            }
        }
        if (white_space == 0) //loop ends and no whitespace found
        {
            stop = 1;
        }
    } while (stop == 0);

    printf("Enter the display name (%d chars max): ", MAX_DISPLAY);
    getCString(account->login.acc_name, MIN_CHAR, MAX_DISPLAY);

    stop = 0;
    do
    {
        printf("Enter the password (must be %d chars in length): ", MAX_PWD);
        getCString(account->login.password, MAX_PWD, MAX_PWD);

        num_letter = 0;
        uppercase = 0, lowercase = 0, symbols = 0, digit = 0;

        //checks for special characters
        for (i = 0; account->login.password[i] != '\0'; i++)
        {
            num_letter++;
            if (isupper(account->login.password[i]))
            {
                uppercase++;
            }
            else if (islower(account->login.password[i]))
            {
                lowercase++;
            }
            else if (isdigit(account->login.password[i]))
            {
                digit++;
            }
            else if (account->login.password[i] == '!' || 
                account->login.password[i] == '@' || 
                account->login.password[i] == '#' || 
                account->login.password[i] == '$' || 
                account->login.password[i] == '%' ||
                account->login.password[i] == '^' ||
                account->login.password[i] == '&' || 
                account->login.password[i] == '*')
            {
                symbols++;
            }
        }
        if (uppercase < 2 || lowercase < 2 || digit < 2 || symbols < 2)
        {
            printf("SECURITY: Password must contain 2 of each:\n");
            printf("          Digit: 0-9\n");
            printf("          UPPERCASE character\n");
            printf("          lowercase character\n");
            printf("          symbol character: !@#$%%^&*\n");
        }
        else
        {
            stop = 1;
        }
    } while (stop == 0);

    printf("\n");
    return;
}

void getDemographic(struct Account* account)
{
    int i, time;

    time = currentYear();

    printf("Demographic Data Input\n");
    printf("----------------------------------------\n");
    printf("Enter birth year (current age must be between %d and %d): ", MIN_AGE, MAX_AGE);
    account->demo.birth_year = getIntFromRange(time - MAX_AGE, time - MIN_AGE);

    printf("Enter the household Income: $");
    account->demo.income = getPositiveDouble();

   
    printf("Enter the country (%d chars max.): ", MAX_DISPLAY);
    getCString(account->demo.country, MIN_CHAR, MAX_DISPLAY);
    
    // converts lowercase into uppercase
    for (i = 0; account->demo.country[i] != '\0'; i++)
    {
        if (account->demo.country[i] >= 'a' && account->demo.country[i] <= 'z')
        {
            account->demo.country[i] = account->demo.country[i] - 32;
        }
    }

    printf("\n");
    return;
}

int userLoginEntry(const struct Account* account, int max_size)
{
    int i, acc_num = 0, acc_index, stop = 0, attempt = 3, log, pass, 
        valid_cred;
    char login[101] = { '\0' }, password[101] = { '\0' };
    do
    {
        
        printf("\nEnter the account#: ");
        acc_num = getInteger();
        //temporarily stores user input
        printf("User Login    : ");
        scanf("%100[^\n]", login);
        clearStandardInputBuffer();
        printf("Password      : ");
        scanf("%100[^\n]", password);
        clearStandardInputBuffer();
        valid_cred = 0;
        for (i = 0; i < max_size && valid_cred == 0; i++)
        {
            //exits and return account index if there is a match
            if (account[i].acc_num == acc_num)
            {
                //checks to see if credentials match
                log = strcmp(login, account[i].login.login_name);
                pass = strcmp(password, account[i].login.password);
                if (log == 0 && pass == 0)
                {
                    acc_index = i;
                    stop = 1;
                    valid_cred = 1;
                }
            }
        }
        if (i >= max_size || account[i].acc_num == 0)
        {
            attempt--;
            printf("INVALID user login/password combination! [attempts remaining:%d]\n", attempt);
            acc_index = 0;
        }
    } while (attempt > 0 && stop == 0);
    //no more attempts
    if (attempt == 0)
    {
        printf("\nERROR:  Login failed!\n\n");
        pauseExecution();
    }
    return acc_index;
}

void archiveClosedAccounts(struct Account* account, int max_size)
{
    const char filename[] = "accounts_arc.txt"; 

    FILE* fp = fopen(filename, "a"); //appends to end of file

    if (fp != NULL)
    {
        fprintf(fp, "%d|%c|%s|%s|%s|%d|%lf|%s|\n", 
            account->acc_num,
            account->acc_type,
            account->login.acc_name,
            account->login.login_name,
            account->login.password,
            account->demo.birth_year,
            account->demo.income,
            account->demo.country
        );
        // sets all account variables to NULL
        account->acc_num = 0;
        account->acc_type = '\0';
        account->login.acc_name[0] = '\0';
        account->login.login_name[0] = '\0';
        account->login.password[0] = '\0';
        account->demo.birth_year = 0;
        account->demo.income = 0;
        account->demo.country[0] = '\0';

        fclose(fp);
        fp = NULL;
    }
    else
    {
        printf("ERROR: Unable to open file for writing.\n");
    }

    return;
}

void saveAllAccounts(struct Account* accounts, int max_size)
{
    int i, num_acc;
    const char filename[] = "accounts.txt"; //replace with accounts.txt later

    FILE* fp = fopen(filename, "w");

    if (fp != NULL)
    {
        num_acc = 0;
        for (i = 0; i < max_size; i++)
        {
            if (accounts[i].acc_num != 0)
            {
                fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n",
                    accounts[i].acc_num,
                    accounts[i].acc_type,
                    accounts[i].login.acc_name,
                    accounts[i].login.login_name,
                    accounts[i].login.password,
                    accounts[i].demo.birth_year,
                    accounts[i].demo.income,
                    accounts[i].demo.country
                );
                num_acc++;
            }
        }
        printf("   %d account saved.\n", num_acc);
    }
    else
    {
        printf("ERROR: Unable to open file for writing.\n");
    }
    return;
}

void archivedAccountStats(int max_size)
{
    int i, acc_num, birth_year;
    double income;
    const char filename[] = "accounts_arc.txt"; 
    char acc_type, acc_name[101], login_name[101], password[101], country[101];

    FILE* fp = fopen(filename, "r");

    if (fp != NULL)
    {
        i = 0;
        //counts the number of accounts scanned from file
        while (fscanf(fp, "%d|%c|%[^|]|%[^|]|%[^|]|%d|%lf|%[^\n]",
            &acc_num,
            &acc_type,
            acc_name,
            login_name,
            password,
            &birth_year,
            &income,
            country
        ) != EOF)
        {
            i++;
        }
        
        fclose(fp);
    }
    else //no file exist, meaning nothing archived yet
    {
        i = 0;
    }

    printf("\nThere are %d account(s) currently archived.\n\n", i);
    return;
}