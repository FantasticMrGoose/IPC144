#ifndef TICKET_H_
#define TICKET_H_

struct Message
{
	char acc_type;
	char display_name[31];
	char message[151];
};

struct Ticket
{
	int ticket_num;
	int acc_number;
	int ticket_status;
	char subject_line[31];
	int num_message;
	struct Message message[20];
};

//function prototypes

// creates a new ticket
void createNewTicket(struct Ticket* newticket, const struct Account* cur_acc);

// modify the current user's existing tickets
void modifyActiveTicket(struct Ticket* ticket, const struct Account* cur_acc);

// allows the agent to modify any ticket
void modifyAllTickets(struct Ticket* ticket, const struct Account* cur_acc);

// saves ticket info to file
void saveAllTickets(const struct Ticket* tickets, int max_tickets);

// archive closed tickets to file
void archiveClosedTickets(const struct Ticket* tickets);

// view the statistics of archived tickets
void archivedTicketStats(int max_size);

#endif 