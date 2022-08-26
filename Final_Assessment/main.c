#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "phoneData.h"
#include "sorting.h"

#define PHONE_SIZE 7

int main(void)
{
	struct phoneData phone[PHONE_SIZE] = { {0} };
	struct tempStorage temp_phone[PHONE_SIZE] = { {0} };

	int i, choice = -1;

	loadPhoneInfo(phone);

	do
	{
		printf("Select one of the following options: \n");
		printf("0 - Exit\n");
		printf("1 - Show user by call duration\n");
		printf("2 - Show user by data usage\n");
		printf("3 - Show user by screen time\n");
		printf("4 - Show all user data\n");
		scanf("%d", &choice);
		switch (choice)
		{
		case 0:
			printf("Goodbye");
			break;
		case 1:
			sortByDuration(phone, temp_phone, PHONE_SIZE);
			break;
		case 2:
			sortByData(phone, temp_phone, PHONE_SIZE);
			break;
		case 3:
			sortByScreen(phone, temp_phone, PHONE_SIZE);
			break;
		case 4:
			showAllData(phone, PHONE_SIZE);
			break;
		}
	} while (choice != 0);

	return 0;
}