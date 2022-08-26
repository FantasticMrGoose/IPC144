#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "account.h"  
#include "commonHelpers.h"
#include "accountTicketingUI.h"
#include "ticket.h"

#define MIN_LETTERS 1
#define MAX_SUBJECT_LEN 30
#define MAX_NUM_MSG 20
#define MAX_MSG_LEN 150

//function defintions

void createNewTicket(struct Ticket* newticket, const struct Account* cur_acc)
{
	newticket->acc_number = cur_acc->acc_num;
	newticket->ticket_status = 1; //new ticket is always active
	newticket->num_message += 1;
	newticket->message->acc_type = cur_acc->acc_type;
	
	printf("New Ticket (Ticket#:0%d)\n", newticket->ticket_num);
	printf("----------------------------------------\n");
	printf("Enter the ticket SUBJECT (%d chars. maximum): ", MAX_SUBJECT_LEN);
	getCString(newticket->subject_line, MIN_LETTERS, MAX_SUBJECT_LEN);
	printf("\n");

	//since this is a new message, we can just set the user input to index 0
	newticket->message[0].acc_type = cur_acc->acc_type;
	strncpy(newticket->message[0].display_name, cur_acc->login.acc_name, 
		MAX_SUBJECT_LEN);
	printf("Enter the ticket message details (%d chars. maximum). ", MAX_MSG_LEN);
	printf("Press the ENTER key to submit:\n");
	getCString(newticket->message[0].message, MIN_LETTERS, MAX_MSG_LEN);

	printf("\n*** New ticket created! ***\n\n");
	pauseExecution();
	return;
}

void modifyActiveTicket(struct Ticket* ticket, const struct Account* cur_acc)
{
	int i, choice, message_full, stop = 0;
	char active[7] = "ACTIVE", closed[7] = "CLOSED", option;

	do
	{
		printf("\n----------------------------------------\n");
		printf("Ticket 0%d - Update Options\n", ticket->ticket_num);
		printf("----------------------------------------\n");
		if (ticket->ticket_status == 1)
		{
			printf("Status  : %s\n", active);
		}
		else
		{
			printf("Status  : %s\n", closed);
		}
		printf("Subject : %s\n", ticket->subject_line);
		printf("----------------------------------------\n");
		printf("1) Modify the subject\n");
		printf("2) Add a message\n");
		printf("3) Close ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		choice = getIntFromRange(0, 3);
		message_full = 1;

		if (choice == 0)
		{
			stop = 1;
			printf("\n");
			pauseExecution();
		}
		else if (choice == 1)
		{
			printf("\nEnter the revised ticket SUBJECT (%d chars. maximum): ", MAX_SUBJECT_LEN);
			getCString(ticket->subject_line, MIN_LETTERS, MAX_SUBJECT_LEN);

		}
		else if (choice == 2)
		{
			for (i = 0; i < MAX_NUM_MSG && message_full == 1; i++)
			{
				// looks for empty space in messages 
				if (ticket->message[i].message[0] == '\0')
				{
					ticket->message[i].acc_type = cur_acc->acc_type;
					strcpy(ticket->message[i].display_name, cur_acc->login.acc_name);
					ticket->num_message += 1;
					printf("\nEnter the ticket message details (%d chars. maximum). ", MAX_MSG_LEN);
					printf("Press the ENTER key to submit:\n");
					getCString(ticket->message[i].message, MIN_LETTERS, MAX_MSG_LEN);
					message_full = 0;
				}
			}
			if (message_full == 1)
			{
				printf("\nERROR: Message limit has been reached, call ITS Support!\n");
			}
		}
		else if (choice == 3)
		{
			printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
			option = getCharOption("YN");
			if (option == 'Y')
			{
				ticket->ticket_status = 0;
				stop = 1;
				for (i = 0; i < MAX_NUM_MSG && message_full == 1; i++)
				{
					// looks for empty space in messages 
					if (ticket->message[i].message[0] == '\0')
					{
						printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
						option = getCharOption("YN");
						if (option == 'Y')
						{
							ticket->message[i].acc_type = cur_acc->acc_type;
							strcpy(ticket->message[i].display_name, cur_acc->login.acc_name);
							ticket->num_message += 1;
							printf("\nEnter the ticket message details (%d chars. maximum). ",
								MAX_MSG_LEN);
							printf("Press the ENTER key to submit:\n");
							getCString(ticket->message[i].message, MIN_LETTERS, MAX_MSG_LEN);
							message_full = 0;
						}
						if (option == 'N')
						{
							message_full = 0;
						}
					}
				}
				printf("\n*** Ticket closed! ***\n\n");
				pauseExecution();
			}
			else
			{
				printf("\n*** No changes made! ***\n");
			}
		}
	} while (stop == 0);

	return;
}

void modifyAllTickets(struct Ticket* ticket, const struct Account* cur_acc)
{
	int i, choice, message_full, stop = 0;
	char active[7] = "ACTIVE", closed[7] = "CLOSED", option;

	do
	{
		printf("\n----------------------------------------\n");
		printf("Ticket 0%d - Update Options\n", ticket->ticket_num);
		printf("----------------------------------------\n");
		if (ticket->ticket_status == 1)
		{
			printf("Status  : %s\n", active);
		}
		else
		{
			printf("Status  : %s\n", closed);
		}
		printf("Subject : %s\n", ticket->subject_line);
		printf("Acct#   : %d\n", ticket->acc_number);
		printf("Customer: %s\n", ticket->message->display_name);
		printf("----------------------------------------\n");
		printf("1) Add a message\n");
		printf("2) Close ticket\n");
		printf("3) Re-open ticket\n");
		printf("0) Done\n");
		printf("Selection: ");
		choice = getIntFromRange(0, 3);
		message_full = 1;

		if (choice == 0)
		{
			stop = 1;
			printf("\n");
		}
		else if (choice == 1)
		{
			if (ticket->ticket_status == 0)
			{
				printf("\nERROR: Ticket is closed - new messages are not permitted.\n");
			}
			else
			{
				for (i = 0; i < MAX_NUM_MSG && message_full == 1; i++)
				{
					if (ticket->message[i].message[0] == '\0')
					{
						ticket->message[i].acc_type = cur_acc->acc_type;
						strcpy(ticket->message[i].display_name, cur_acc->login.acc_name);
						ticket->num_message += 1;
						printf("\nEnter the ticket message details (%d chars. maximum). ", MAX_MSG_LEN);
						printf("Press the ENTER key to submit:\n");
						getCString(ticket->message[i].message, MIN_LETTERS, MAX_MSG_LEN);
						message_full = 0;
					}
				}
				if (message_full == 1)
				{
					printf("\nERROR: Message limit has been reached, call ITS Support!\n");
				}
			}
		}
		else if (choice == 2)
		{
			if (ticket->ticket_status == 0)
			{
				printf("\nERROR: Ticket is already closed!\n");
			}
			else
			{
				printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				option = getCharOption("YN");
				if (option == 'Y')
				{
					ticket->ticket_status = 0;
					for (i = 0; i < MAX_NUM_MSG && message_full == 1; i++)
					{
						if (ticket->message[i].message[0] == '\0')
						{
							printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
							option = getCharOption("YN");
							if (option == 'Y')
							{
								ticket->message[i].acc_type = cur_acc->acc_type;
								strcpy(ticket->message[i].display_name, cur_acc->login.acc_name);
								ticket->num_message += 1;
								printf("\nEnter the ticket message details (%d chars. maximum). ",
									MAX_MSG_LEN);
								printf("Press the ENTER key to submit:\n");
								getCString(ticket->message[i].message, MIN_LETTERS, MAX_MSG_LEN);
								message_full = 0;
							}
							if (option == 'N')
							{
								message_full = 0;
							}
						}
					}	
					printf("\n*** Ticket closed! ***\n");
				}
			}
		}
		else if (choice == 3)
		{
			if (ticket->ticket_status == 1)
			{
				printf("\nERROR: Ticket is already active!\n");
			}
			else
			{
				printf("\nAre you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");
				option = getCharOption("YN");
				if (option == 'Y')
				{
					ticket->ticket_status = 1;
					printf("\n*** Ticket re-opened! ***\n");
				}
			}
		}
	} while (stop == 0);
	return;
}

void saveAllTickets(const struct Ticket* tickets, int max_tickets)
{
	int i, j, num_tickets;
	const char filename[] = "tickets.txt";
	
	FILE* fp = fopen(filename, "w");

	if (fp != NULL)
	{
		num_tickets = 0;
		for (i = 0; i < max_tickets; i++)
		{
			if (tickets[i].ticket_num != 0)
			{
				//saves all variables to file, pipe delimited
				fprintf(fp, "%d|%d|%d|%s|%d|",
					tickets[i].ticket_num,
					tickets[i].acc_number,
					tickets[i].ticket_status,
					tickets[i].subject_line,
					tickets[i].num_message
				);
				for (j = 0; j < tickets[i].num_message; j++)
				{
					//saves the messages based on # of messages
					fprintf(fp, "%c|%s|%s|",
						tickets[i].message[j].acc_type,
						tickets[i].message[j].display_name,
						tickets[i].message[j].message
					);
				}
				// prints a new line (new record) once all messages for that ticket 
				//has been saved
				fprintf(fp, "\n");
				num_tickets++;
			}
		}
		fclose(fp);
		fp = NULL;
		printf("   %d tickets saved.\n", num_tickets);
	}
	else
	{
		printf("ERROR: Unable to open file for writing.\n");
	}
	return; 
}

void archiveClosedTickets(const struct Ticket* tickets)
{
	int i;
	const char filename[] = "tickets_arc.txt";

	FILE* fp = fopen(filename, "a"); //appends to end of file

	if (fp != NULL)
	{
		//saves all variables to file, pipe delimited
		fprintf(fp, "%d|%d|%d|%s|%d|",
			tickets->ticket_num,
			tickets->acc_number,
			tickets->ticket_status,
			tickets->subject_line,
			tickets->num_message
		);
		for (i = 0; i < tickets->num_message; i++)
		{
			//saves the messages based on # of messages
			fprintf(fp, "%c|%s|%s|",
				tickets->message[i].acc_type,
				tickets->message[i].display_name,
				tickets->message[i].message
			);
		}
		// prints a new line (new record) once all messages for that ticket 
		//has been saved
		fprintf(fp, "\n");
		fclose(fp);
		fp = NULL;
	}
	else
	{
		printf("ERROR: Unable to open file for writing.\n");
	}

	return;
}

void archivedTicketStats(int max_size)
{
	int i, j, ticket_num, acc_number, ticket_status, num_message, count_message;
	const char filename[] = "tickets_arc.txt";
	char subject_line[101], acc_type, display_name[101], message[151];

	FILE* fp = fopen(filename, "r");

	if (fp != NULL)
	{
		i = 0;
		count_message = 0;
		// counts the number of records scanned
		while (fscanf(fp, "%d|%d|%d|%[^|]|%d|",
			&ticket_num,
			&acc_number,
			&ticket_status,
			subject_line,
			&num_message
		) != EOF)
		{
			i++;
			count_message += num_message;
			for (j = 0; j < num_message; j++)
			{
				fscanf(fp, "%c|%[^|]|%[^|]|",
					&acc_type,
					display_name,
					message
				);
			}
		}
		fclose(fp);
	}
	else
	{
		i = 0, count_message = 0;
	}
	printf("\nThere are %d ticket(s) and a total of %d message(s) archived.\n\n",
		i, count_message);
	
	return;
}