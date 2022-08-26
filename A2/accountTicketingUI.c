#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "account.h"  
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#include "ticket.h"

#define MIN_CHAR 1
#define MAX_DISPLAY 30
#define MAX_SIZE 101
#define MAX_PWD 8
#define MAX_NUM_MSG 20

//function definitions

void displayAccountSummaryHeader(void)
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
	return;
}

void displayAccountDetailHeader(void)
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
	return;
}

void displayAccountSummaryRecord(const struct Account* account)
{
	char acc_typeA[9] = "AGENT", acc_typeC[9] = "CUSTOMER";

	printf("%05d ", account->acc_num);

	//prints one option based on previous user selection
	if (account->acc_type == 'A')
	{
		printf("%-9s ", acc_typeA);
	}
	else
	{
		printf("%-9s ", acc_typeC);
	}
	printf("%5d", account->demo.birth_year);

	printf("\n");
	return;
}

void displayAccountDetailRecord(const struct Account* account)
{
	int i, n = 0;
	char acc_typeA[9] = "AGENT", acc_typeC[9] = "CUSTOMER";

	//counts the number of letters in password
	n = strlen(account->login.password);

	printf("%05d ", account->acc_num);

	//prints one option based on previous user selection
	if (account->acc_type == 'A')
	{
		printf("%-9s ", acc_typeA);
	}
	else
	{
		printf("%-9s ", acc_typeC);
	}

	printf("%5d $%10.2lf %-10s %-15s %-10s ", account->demo.birth_year,
		account->demo.income, account->demo.country, account->login.acc_name,
		account->login.login_name);
	for (i = 0; i < n; i++)
	{
		if (i%2 != 0)
		{
			printf("*");
		}
		else
		{
			printf("%c", account->login.password[i]);
		}
	}
	printf("\n");
	return;
}

void applicationStartup(struct AccountTicketingData* tkting_data)//Account account[], int num_acc) 
{
	int acc_index, stop = 0;
	
	do
	{
		acc_index = menuLogin(tkting_data->accounts, tkting_data->ACCOUNT_MAX_SIZE);
		if (acc_index != -1)
		{
			if (tkting_data->accounts[acc_index].acc_type == 'A')
			{
				printf("\n");
				menuAgent(tkting_data, &tkting_data->accounts[acc_index]);
			}
			else
			{
				printf("\n");
				menuCustomer(&tkting_data->accounts[acc_index], tkting_data->tickets,
					tkting_data->TICKET_MAX_SIZE);
			}
		}
		else if (acc_index == -1)
		{
			printf("==============================================\n");
			printf("Account Ticketing System - Terminated\n");
			printf("==============================================\n\n");
			stop = 1;
		}
	} while (stop == 0);
	return;
}

int menuLogin(const struct Account account[], int num_acc)
{
	int choice, acc_index, stop = 0;
	char option;
	do
	{
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n");
		printf("0) Exit application\n");
		printf("----------------------------------------------\n\n");
		printf("Selection: ");
		choice = getIntFromRange(0, 1);

		//user decides to login
		if (choice == 1)
		{
			acc_index = stop = userLoginEntry(account, num_acc);
		}
		//user decides to exit
		else if (choice == 0)
		{
			printf("\nAre you sure you want to exit? ([Y]es|[N]o): ");
			option = getCharOption("yYnN");
			if (option == 'y' || option == 'Y')
			{
				acc_index = -1;
				stop = 1; //exits the login
			}
			printf("\n");
		}
	} while (stop == 0);
	return acc_index;
}

void menuAgent(struct AccountTicketingData* tkting_data, 
	const struct Account* current_acc)
{
	int i, j, choice, acc_num = 0, acc_index, full_storage, stop = 0, num_tickets,
		no_error = 0, largest_acc = 0, ticket_num;
	char remove_acc, option;
	do
	{
		printf("AGENT: %s (%d)\n", current_acc->login.acc_name, current_acc->acc_num);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n\n");
		printf("Selection: ");
		choice = getIntFromRange(0, 12);

		if (choice == 0)
		{
			printf("\nSaving session modifications...\n");
			saveAllAccounts(tkting_data->accounts, tkting_data->ACCOUNT_MAX_SIZE);
			saveAllTickets(tkting_data->tickets, tkting_data->TICKET_MAX_SIZE);
			printf("### LOGGED OUT ###\n\n");
			stop = 1;
		}
		else if (choice == 1)
		{
			full_storage = 1;
			//checks for free space in account array
			for (i = 0; i < tkting_data->ACCOUNT_MAX_SIZE && full_storage == 1; i++)
			{
				//finds the largest account number
				if (tkting_data->accounts[i].acc_num > largest_acc)
				{
					largest_acc = tkting_data->accounts[i].acc_num;
				}
			}
			for (i = 0; i < tkting_data->ACCOUNT_MAX_SIZE; i++)
			{
				if (tkting_data->accounts[i].acc_num == 0) // search for empty slot
				{
					//auto generates an account number
					tkting_data->accounts[i].acc_num = largest_acc + 1;
					printf("\n");
					//calls respective function to add new account
					getAccount(&tkting_data->accounts[i]);
					getUserLogin(&tkting_data->accounts[i]);
					getDemographic(&tkting_data->accounts[i]);
					printf("*** New account added! ***\n\n");
					full_storage = 0; //space still available, no error condition
					pauseExecution();
				}
			}
			if (full_storage == 1)
			{
				printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}
		}
		else if (choice == 2)
		{
			printf("\n");
			// get the account index using function
			acc_index = findAccountIndexByAcctNum(acc_num, tkting_data->accounts, 
				tkting_data->ACCOUNT_MAX_SIZE, choice);
			updateAccount(&tkting_data->accounts[acc_index]);
			printf("\n");
		}
		else if (choice == 3)
		{
			printf("\n");
			acc_index = findAccountIndexByAcctNum(acc_num, tkting_data->accounts, 
				tkting_data->ACCOUNT_MAX_SIZE, choice);
			
			//prevents removal of own account
			if (tkting_data->accounts[acc_index].acc_num == current_acc->acc_num)
			{
				printf("\nERROR: You can't remove your own account!\n\n");
				pauseExecution();
			}
			else if (tkting_data->accounts[acc_index].acc_num != 0) //if the account exists
			{
				no_error = 1;
				displayAccountDetailHeader();
				displayAccountDetailRecord(&tkting_data->accounts[acc_index]);
				printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");
				remove_acc = getCharOption("YN");
				if (remove_acc == 'Y')
				{

					for (i = 0; i < tkting_data->TICKET_MAX_SIZE; i++)
					{
						//looks for closed tickets matching the account number
						if (tkting_data->tickets[i].ticket_status == 0 && 
							tkting_data->tickets[i].acc_number == 
							tkting_data->accounts[acc_index].acc_num) 
							//sends only matching CLOSED tickets to be archived
							archiveClosedTickets(&tkting_data->tickets[i]);
			
						// set ticket element to empty state if matches account number
						if (tkting_data->tickets[i].acc_number ==
							tkting_data->accounts[acc_index].acc_num)
						{
							tkting_data->tickets[i].ticket_num = 0;
							tkting_data->tickets[i].acc_number = 0;
							tkting_data->tickets[i].ticket_status = -1;
							tkting_data->tickets[i].subject_line[0] = '\0';
							
							for (j = 0; j < tkting_data->tickets[i].num_message; j++)
							{
								tkting_data->tickets[i].message[j].acc_type = '\0';
								tkting_data->tickets[i].message[j].display_name[0] = '\0';
								tkting_data->tickets[i].message[j].message[0] = '\0';
							}
							tkting_data->tickets[i].num_message = 0;
						}
					}
					archiveClosedAccounts(&tkting_data->accounts[acc_index], 
						tkting_data->ACCOUNT_MAX_SIZE);
					printf("\n*** Account Removed! ***\n\n");
					pauseExecution();
				}
				else if (remove_acc == 'N')
				{
					printf("\n*** No changes made! ***\n\n");
					pauseExecution();
				}
			}
			//wrong account number entered
			else if (no_error == 0)
			{
				printf("\nERROR Account does not exist!\n");
				printf("\n");
				pauseExecution();
			}
		}
		else if (choice == 4)
		{
			displayAllAccountSummaryRecords(tkting_data->accounts, 
				tkting_data->ACCOUNT_MAX_SIZE);
			pauseExecution();
		}
		else if (choice == 5)
		{
			displayAllAccountDetailRecords(tkting_data->accounts, 
				tkting_data->ACCOUNT_MAX_SIZE);
			pauseExecution();
		}
		else if (choice == 6)
		{
			printf("\n");
			displayNewMessage(tkting_data, current_acc);
		}
		else if (choice == 7)
		{
			printf("\n");
			displaySelectedMessage(tkting_data, current_acc, 1);
		}
		else if (choice == 8)
		{
			printf("\n");
			displaySelectedMessage(tkting_data, current_acc, 0);
		}
		else if (choice == 9)
		{
			printf("\nEnter ticket number: ");
			ticket_num = getPositiveInteger();
			for (i = 0; i < tkting_data->TICKET_MAX_SIZE; i++)
			{
				//if a ticket number is valid
				if (ticket_num == tkting_data->tickets[i].ticket_num)
				{
					modifyAllTickets(&tkting_data->tickets[i], current_acc);
				}
			}
		}
		else if (choice == 10)
		{
			printf("\nAre you sure? This action cannot be reversed. ([Y]es|[N]o): ");
			option = getCharOption("YN");
			if (option == 'Y')
			{
				num_tickets = 0;
				//sends all closed tickets to be archived 
				for (i = 0; i < tkting_data->TICKET_MAX_SIZE; i++)
				{
					if (tkting_data->tickets[i].ticket_status == 0)
					{
						archiveClosedTickets(&tkting_data->tickets[i]);
						//set ticket elements to empty state
						tkting_data->tickets[i].ticket_num = 0;
						tkting_data->tickets[i].acc_number = 0;
						tkting_data->tickets[i].ticket_status = -1;
						tkting_data->tickets[i].subject_line[0] = '\0';
						num_tickets++;

						for (j = 0; j < tkting_data->tickets[i].num_message; j++)
						{
							tkting_data->tickets[i].message[j].acc_type = '\0';
							tkting_data->tickets[i].message[j].display_name[0] = '\0';
							tkting_data->tickets[i].message[j].message[0] = '\0';
						}
						tkting_data->tickets[i].num_message = 0;
					}
				}
				printf("\n*** %d tickets archived ***\n\n", num_tickets);
				pauseExecution();
			}
			else
			{
				printf("Ticket archiving cancelled.");
				pauseExecution();
			}
		}
		else if (choice == 11)
		{
			archivedAccountStats(tkting_data->ACCOUNT_MAX_SIZE);
			pauseExecution();

		}
		else if (choice == 12)
		{
			archivedTicketStats(tkting_data->TICKET_MAX_SIZE);
			pauseExecution();
		}
	} while (stop == 0);
	return;
}

void menuCustomer(const struct Account* current_acc, 
	struct Ticket tickets[], int max_tickets)
{
	int i, stop = 0, choice, full_storage, highest_ticket_num = 0, ticket_num, 
		invalid_acc, invalid_ticket;

	do
	{
		printf("CUSTOMER: %s (%d)\n", current_acc->login.acc_name, current_acc->acc_num);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n");
		printf("\nSelection: ");
		choice = getIntFromRange(0, 4);
		if (choice == 0)
		{
			printf("\nSaving session modifications...\n");
			saveAllTickets(tickets, max_tickets);
			printf("### LOGGED OUT ###\n\n");
			stop = 1;
		}
		else if (choice == 1)
		{
			printf("\n");
			displayAccountDetailHeader();
			displayAccountDetailRecord(current_acc);
			printf("\n");
			pauseExecution();
		}
		else if (choice == 2)
		{
			full_storage = 1;
			//checks for free space in ticket array
			for (i = 0; i < max_tickets; i++)
			{
				//finds the highest ticket number
				if (tickets[i].ticket_num > highest_ticket_num)
				{
					highest_ticket_num = tickets[i].ticket_num;
				}
				if (tickets[i].ticket_num == 0)
				{
					//auto generates a ticket number
					tickets[i].ticket_num = highest_ticket_num + 1;
					printf("\n");
					//calls respective function to make new ticket
					createNewTicket(&tickets[i], current_acc);
					full_storage = 0;
				}
			}
			if (full_storage == 1)
			{
				printf("\nERROR: Ticket listing is FULL, call ITS Support!\n\n");
				pauseExecution();
			}
		}
		else if (choice == 3)
		{
			invalid_ticket = 1, invalid_acc = 1;
			printf("\nEnter ticket number: ");
			ticket_num = getPositiveInteger();
			for (i = 0; i < max_tickets; i++)
			{
				//if a ticket number is valid
				if (ticket_num == tickets[i].ticket_num)
				{
					invalid_ticket = 0;
					// if the ticket belongs to the current user
					if (tickets[i].acc_number == current_acc->acc_num)
					{
						// if the ticket is active
						if (tickets[i].ticket_status == 1)
						{
							invalid_acc = 0;
							modifyActiveTicket(&tickets[i], current_acc);
						}
						else
						{
							invalid_acc = 0;
							printf("\nERROR: Ticket is closed - changes are not permitted.\n\n");
							pauseExecution();
						}
					}
				}
			}
			if (invalid_ticket == 1)
			{
				printf("\nERROR: Invalid ticket number - Ticket does not exist.\n\n");
				pauseExecution();
			}
			if (invalid_ticket == 0 && invalid_acc == 1)
			{
				printf("\nERROR: Invalid ticket number - "
					"you may only modify your own ticket.\n\n");
				pauseExecution();
			}
		}
		else if (choice == 4)
		{
			printf("\n");
			displayCustTicketRecord(tickets, max_tickets, current_acc);
		}
	} while (stop == 0);
}

int findAccountIndexByAcctNum(int acc_num, const struct Account account[], int num_acc, int user_select)
{
	int i, acc_index = -1, stop = 0, no_error = 0;
	do
	{
		if (user_select == -1)
		{
			acc_index = user_select;
			stop = 1;
			no_error = 1;
		}
		else if (user_select == 0)
		{
			for (i = 0; i < num_acc || account[i].acc_num != 0; i++)
			{
				//exits and return account index if there is a match
				if (account[i].acc_num == acc_num)
				{
					acc_index = i;
					stop = 1;
					no_error = 1;
				}
			}
		}
		else if (user_select > 0)
		{
			printf("Enter the account#: ");
			acc_num = getInteger();
			for (i = 0; i < num_acc || account[i].acc_num != 0; i++)
			{
				//exits and return account index if there is a match
				if (account[i].acc_num == acc_num)
				{
					acc_index = i;
					stop = 1;
					no_error = 1;
				}
			}
		}
		//wrong account number entered
		if (no_error == 0)
		{
			printf("\nERROR: Access Denied.\n");
			printf("\n");
			pauseExecution();
		}
	} while (stop == 0);

	return acc_index;
}

void displayAllAccountSummaryRecords(const struct Account account[], int num_acc)
{
	int i;
	printf("\n");
	displayAccountSummaryHeader();
	for (i = 0; i < num_acc; i++)
	{
		if (account[i].acc_num != 0)
		{
			displayAccountSummaryRecord(&account[i]);
		}
	}
	printf("\n");
	return; 
}

void displayAllAccountDetailRecords(const struct Account account[], int num_acc)
{
	int i;
	printf("\n");
	displayAccountDetailHeader();
	for (i = 0; i < num_acc; i++)
	{
		if (account[i].acc_num != 0)
		{
			displayAccountDetailRecord(&account[i]);
		}
	}
	printf("\n");
	return;
}

void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStandardInputBuffer();
	putchar('\n');
}

void updateAccount(struct Account* account)
{
	int stop = 0, choice;

	printf("\n");
	do
	{
		printf("Account: %d - Update Options\n", account->acc_num);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->acc_type);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		choice = getIntFromRange(0, 3);

		if (choice == 0)
		{
			stop = 1;
		}
		else if (choice == 1)
		{
			printf("\nEnter the account type (A=Agent | C=Customer): ");
			account->acc_type = getCharOption("AC");
		}
		else if (choice == 2)
		{
			updateUserLogin(&account->login);
			printf("\n");
		}
		else if (choice == 3)
		{
			updateDemographic(&account->demo);
			printf("\n");
		}
	} while (stop == 0);
	return;
}

void updateUserLogin(struct UserLogin* login)
{
	int i, stop = 0, is_update = 0, choice , uppercase, lowercase, symbols, digit;

	do
	{
		printf("\nUser Login: %s - Update Options\n", login->login_name); 
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", login->acc_name);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		choice = getIntFromRange(0, 2);

		if (choice == 0)
		{
			stop = 1;
		}
		else if (choice == 1)
		{
			printf("\nEnter the display name (%d chars max): ", MAX_DISPLAY);
			getCString(login->acc_name, MIN_CHAR, MAX_DISPLAY);
		}
		else if (choice == 2)
		{
			do
			{
				printf("\nEnter the password (must be %d chars in length): ", MAX_PWD);

				getCString(login->password, MAX_PWD, MAX_PWD);
				uppercase = 0, lowercase = 0, symbols = 0, digit = 0;

				//checks for special characters
				for (i = 0; login->password[i] != '\0'; i++)
				{
					if (isupper(login->password[i]))
					{
						uppercase++;
					}
					else if (islower(login->password[i]))
					{
						lowercase++;
					}
					else if (isdigit(login->password[i]))
					{
						digit++;
					}
					else if (login->password[i] == '!' || login->password[i] == '@' || 
						login->password[i] == '#' || login->password[i] == '$' || 
						login->password[i] == '%' || login->password[i] == '^' ||
						login->password[i] == '&' || login->password[i] == '*')
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
					printf("          symbol character: !@#$%%^&*");
				}
				else
				{
					is_update = 1;
				}
			} while (is_update == 0);
		}
	} while (stop == 0);
}

void updateDemographic(struct Demographic* demo)
{
	int i, stop = 0, choice;

	do
	{
		printf("\nDemographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%0.2lf)\n", demo->income);
		printf("2) Country (current value: %s)\n", demo->country);
		printf("0) Done\n");
		printf("Selection: ");
		choice = getIntFromRange(0, 2);
		if (choice == 0)
		{
			stop = 1;
		}
		else if (choice == 1)
		{
			printf("\nEnter the household Income: $");
			demo->income = getPositiveDouble();
		}
		else if (choice == 2)
		{
			printf("\nEnter the country (%d chars max.): ", MAX_DISPLAY);
			getCString(demo->country, MIN_CHAR, MAX_DISPLAY);
			// converts lowercase into uppercase
			for (i = 0; demo->country[i] != '\0'; i++)
			{
				if (demo->country[i] >= 'a' && demo->country[i] <= 'z')
				{
					demo->country[i] = demo->country[i] - 32;
				}
			}
		}
	} while (stop == 0);
}

void displayCustTicketRecord(const struct Ticket tickets[], int max_tickets,
	const struct Account* current_acc)
{
	int i, stop = 0;
	char active[7] = "ACTIVE", closed[7] = "CLOSED";

	do
	{
		printf("------ ------ ------------------------------ --------\n");
		printf("Ticket Status Subject                        Messages\n");
		printf("------ ------ ------------------------------ --------\n");
		for (i = 0; i < max_tickets && tickets[i].acc_number > 0; i++)
		{
			if (tickets[i].acc_number == current_acc->acc_num)
			{
				printf("%06d ", tickets[i].ticket_num);
				if (tickets[i].ticket_status == 1)
				{
					printf("%-7s", active);
				}
				else
				{
					printf("%-7s", closed);
				}
				printf("%-30s %5d\n", tickets[i].subject_line,
					tickets[i].num_message);
			}
		}
		printf("------ ------ ------------------------------ --------\n\n");
		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");

		stop = viewMessageOption(tickets, max_tickets, current_acc);

	} while (stop == 0);
	return;
}

int viewMessageOption(const struct Ticket* tickets, int max_tickets,
	const struct Account* current_acc)
{
	int i, choice, stop = 0, found = 0, invalid_acc = 1;
	choice = getInteger();
	while (choice < 0)
	{
		printf("ERROR: Value must be positive or zero: ");
		choice = getInteger();
	}
	for (i = 0; i < max_tickets; i++)
	{ 
		if (choice == tickets[i].ticket_num && tickets[i].ticket_num > 0)
		{
			found = 1;
			//only the ticket's creator or an agent can access
			if (tickets[i].acc_number == current_acc->acc_num 
				|| current_acc->acc_type == 'A') 
			{
				displayTicketMessage(&tickets[i], current_acc);
				invalid_acc = 0;
			}
		}
	}
	if (choice == 0)
	{
		printf("\n");
		stop = 1;
	}
	else if (found == 0)
	{
		printf("\nERROR: Invalid ticket number.\n\n");
		pauseExecution();
	}
	else if (found == 1 && invalid_acc == 1)
	{
		printf("\nERROR: Invalid ticket number - you may only access your own tickets.\n\n");
		pauseExecution();
	}
	return stop;
}

void displayTicketMessage(const struct Ticket* tickets,
	const struct Account* account)
{
	int i;
	char active[7] = "ACTIVE", closed[7] = "CLOSED",
		acc_typeA[9] = "AGENT", acc_typeC[9] = "CUSTOMER";

	printf("\n================================================================================\n");
	printf("%06d ", tickets->ticket_num);
	if (tickets->ticket_status == 1)
	{
		printf("(%s) ", active);
	}
	else
	{
		printf("(%s) ", closed);
	}
	printf("Re: %s\n", tickets->subject_line);
	printf("================================================================================\n");
	for (i = 0; i < tickets->num_message; i++)
	{
		if (i%5 == 0 && i != 0)
		{
			pauseExecution();
		}
		if (tickets->message[i].acc_type == 'A')
		{
			printf("%s ", acc_typeA);
		}
		else
		{
			printf("%s ", acc_typeC);
		}
		printf("(%s):\n", tickets->message[i].display_name);
		printf("   %s\n\n", tickets->message[i].message);

	}
	pauseExecution();
	return;
}

void displayNewMessage(const struct AccountTicketingData* tkting_data,
	const struct Account* current_acc)
{
	int i, stop = 0;
	char active[7] = "ACTIVE", closed[7] = "CLOSED";
	do
	{
		printf("------ ----- --------------- ------ ------------------------------ --------\n");
		printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
		printf("------ ----- --------------- ------ ------------------------------ --------\n");
		//Looks for messages that are open and has 1 message
		for (i = 0; i < tkting_data->TICKET_MAX_SIZE; i++)
		{
			if (tkting_data->tickets[i].num_message == 1 &&
				tkting_data->tickets[i].ticket_status == 1)
			{
				printf("%06d %5d ", tkting_data->tickets[i].ticket_num,
					tkting_data->tickets[i].acc_number);
				printf("%-15s ", tkting_data->tickets[i].message[0].display_name);
				if (tkting_data->tickets[i].ticket_status == 1)
				{
					printf("%-7s", active);
				}
				else
				{
					printf("%-7s", closed);
				}
				printf("%-30s %5d\n", tkting_data->tickets[i].subject_line,
					tkting_data->tickets[i].num_message);
				//finds the corrosponding display name
			}
		}
		printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");

		//get options to view messages
		stop = viewMessageOption(tkting_data->tickets, tkting_data->TICKET_MAX_SIZE, current_acc);
	} while (stop == 0);
	return;
}

void displaySelectedMessage(const struct AccountTicketingData* tkting_data,
	const struct Account* current_acc, int ticket_type_choice)
{
	int i, stop = 0;
	char active[7] = "ACTIVE", closed[7] = "CLOSED";
	do
	{
		printf("------ ----- --------------- ------ ------------------------------ --------\n");
		printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
		printf("------ ----- --------------- ------ ------------------------------ --------\n");
		// if the agent chose to display active messages
		if (ticket_type_choice == 1)
		{
			//Looks for messages that are open
			for (i = 0; i < tkting_data->TICKET_MAX_SIZE; i++)
			{
				if (tkting_data->tickets[i].ticket_status == 1 &&
					tkting_data->tickets[i].ticket_num > 0)
				{
					printf("%06d %5d ", tkting_data->tickets[i].ticket_num,
						tkting_data->tickets[i].acc_number);
					//finds the corrosponding display name
					printf("%-15s ", tkting_data->tickets[i].message[0].display_name);
					if (tkting_data->tickets[i].ticket_status == 1)
					{
						printf("%-7s", active);
					}
					else
					{
						printf("%-7s", closed);
					}
					printf("%-30s %5d\n", tkting_data->tickets[i].subject_line,
						tkting_data->tickets[i].num_message);
				}
			}
		}
		// if the agent chose to display closed messages
		else if (ticket_type_choice == 0)
		{
			//Looks for messages that are open
			for (i = 0; i < tkting_data->TICKET_MAX_SIZE; i++)
			{
				if (tkting_data->tickets[i].ticket_status == 0 &&
					tkting_data->tickets[i].ticket_num > 0)
				{
					printf("%06d %5d ", tkting_data->tickets[i].ticket_num,
						tkting_data->tickets[i].acc_number);
					//finds the corrosponding display name
					printf("%-15s ", tkting_data->tickets[i].message[0].display_name);
					if (tkting_data->tickets[i].ticket_status == 1)
					{
						printf("%-7s", active);
					}
					else
					{
						printf("%-7s", closed);
					}
					printf("%-30s %5d\n", tkting_data->tickets[i].subject_line,
						tkting_data->tickets[i].num_message);
				}
			}
		}
		printf("------ ----- --------------- ------ ------------------------------ --------\n\n");
		printf("Enter the ticket number to view the messages or\n");
		printf("0 to return to previous menu: ");

		stop = viewMessageOption(tkting_data->tickets, tkting_data->TICKET_MAX_SIZE, current_acc);
	} while (stop == 0);
	return;
}

//loads the account data from a file
int loadAccounts(struct Account* accounts, int acc_size)
{
	int i = 0;

	FILE* fp = NULL;
	fp = fopen("accounts.txt", "r"); //opens the file to be read

	if (fp != NULL)
	{
		for (i = 0; i < acc_size; i++)
		{
			//reads the respective data into their respective variables
			fscanf(fp, "%d~%c~%[^~]~%[^~]~%[^~]~%d~%lf~%[^\n]",
				&accounts[i].acc_num,
				&accounts[i].acc_type,
				accounts[i].login.acc_name,
				accounts[i].login.login_name,
				accounts[i].login.password,
				&accounts[i].demo.birth_year,
				&accounts[i].demo.income,
				accounts[i].demo.country
			);
		}
		fclose(fp);
	}
	else
	{
		printf("ERROR: File not found!\n");
	}
	return i;
}

//loads the ticket data from a file
int loadTickets(struct Ticket* tickets, int ticket_size)
{
	int i = 0, j = 0;

	FILE* fp = NULL;
	fp = fopen("tickets.txt", "r"); 

	if (fp != NULL)
	{
		for (i = 0; i < ticket_size && !feof(fp); i++)
		{
			//scans the desired number of tickets into variables, pipe delimited
			fscanf(fp, "%d|%d|%d|%[^|]|%d|",
				&tickets[i].ticket_num,
				&tickets[i].acc_number,
				&tickets[i].ticket_status,
				tickets[i].subject_line,
				&tickets[i].num_message
			);
			for (j = 0; j < tickets[i].num_message; j++)
			{
				//scan the messages based on # of messages
				fscanf(fp, "%c|%[^|]|%[^|]|",
					&tickets[i].message[j].acc_type,
					tickets[i].message[j].display_name,
					tickets[i].message[j].message
				);
			}
		}
		fclose(fp);
	}
	else
	{
		printf("ERROR: File not found!\n");
	}
	// 'i' will increment in order to check if 'feof' is true, 
	// thus we must subtract 1 from 'i' to return the proper value
	return --i;
}