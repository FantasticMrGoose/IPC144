//structures

struct Account
{
	int acc_num;
	char acc_type;
};

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

//function prototypes
void account_input(struct Account* account);

void user_login(struct UserLogin* login);

void demographic_input(struct Demographic* demographic);



