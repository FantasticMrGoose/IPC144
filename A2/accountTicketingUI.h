#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_

#include <stdio.h>
#include "account.h"  
#include "ticket.h"

struct AccountTicketingData
{
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array
};

// function prototypes

void displayAccountSummaryHeader(void); //display a formatted table header

void displayAccountDetailHeader(void); //display a formatted table header

//display formatted user info
void displayAccountSummaryRecord(const struct Account* account); 

//display formatted user info
void displayAccountDetailRecord(const struct Account* account);

//logic entry point
void applicationStartup(struct AccountTicketingData* tkting_data);

//Display login menu
int menuLogin(const struct Account account[], int num_acc);

//Display menu options for agents
void menuAgent(struct AccountTicketingData* tkting_data, 
	const struct Account* current_acc);

//Display menu options for customer
void menuCustomer(const struct Account* current_acc, 
	struct Ticket tickets[], int max_tickets);

//Searches for desired account
int  findAccountIndexByAcctNum(int acc_num, const struct Account account[], 
	int num_acc, int user_select);

//displays summary of valid accounts
void displayAllAccountSummaryRecords(const struct Account account[], 
	int num_acc);
//displays detailed view of valid accounts
void displayAllAccountDetailRecords(const struct Account account[], 
	int num_acc);

//pauses application
void pauseExecution(void);

//displays update options
void updateAccount(struct Account* account);

//display login update options
void updateUserLogin(struct UserLogin* login);

//display demographic update options
void updateDemographic(struct Demographic* demo);

//displays the customer's ticket
void displayCustTicketRecord(const struct Ticket tickets[], int max_tickets,
	const struct Account* current_acc);

//options to view messages
int viewMessageOption(const struct Ticket* tickets, int max_tickets,
	const struct Account* account);

//display the ticket content
void displayTicketMessage(const struct Ticket* tickets,
	const struct Account* account);

//displays new messages only
void displayNewMessage(const struct AccountTicketingData* tkting_data,
	const struct Account* current_acc);

//displays all open messages
void displaySelectedMessage(const struct AccountTicketingData* tkting_data,
	const struct Account* current_acc, int ticket_type_choice);

//loads the account data from a file
int loadAccounts(struct Account* accounts, int acc_size);

//loads the ticket data from a file
int loadTickets(struct Ticket* tickets, int ticket_size);


#endif 
