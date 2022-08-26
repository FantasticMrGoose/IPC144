#ifndef PHONE_DATA_H
#define PHONE_DATA_H

// Structures
struct phoneData
{
	char name[31];
	long long callNumber;
	double callTime;
	int callMinutes;
	int callSeconds;
	int dataBytes;
	double screenTime;
	int screenMinutes;
	int screenSeconds;
	int shown;
};

struct tempStorage
{
	char name[31];
	long long callNumber;
	double callTime;
	int callMinutes;
	int callSeconds;
	int dataBytes;
	double screenTime;
	int screenMinutes;
	int screenSeconds;
};

//function prototype
//read in data from text
void loadPhoneInfo(struct phoneData* phone);

//show all user data
void showAllData(struct phoneData* phone, int num_phones);

// converts decimal time to minutes and seconds
int convertMinutes(double time);

int convertSeconds(double time, int minute);
#endif ! PHONE_DATA_H