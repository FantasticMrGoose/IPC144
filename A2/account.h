#ifndef ACCOUNT_H_
#define ACCOUNT_H_

//structures

struct UserLogin
{
	char acc_name[31];
	char login_name[11];
	char password[9];
};

struct Demographic
{
	int birth_year;
	double income;
	char country[31];
};

struct Account
{
	int acc_num;
	char acc_type;
	struct UserLogin login;
	struct Demographic demo;
};

//function prototypes

// get user to input account info
void getAccount(struct Account* account); 

// get user to input login info
void getUserLogin(struct Account* account);

// get user to input demographic info 
void getDemographic(struct Account* account);

// user sign in process
int userLoginEntry(const struct Account* account, int max_size);

// saves account info to file
void saveAllAccounts(struct Account* account, int max_size);

// archives closed accounts to file
void archiveClosedAccounts(struct Account* accounts, int max_size);

void archivedAccountStats(int max_size);
#endif 
