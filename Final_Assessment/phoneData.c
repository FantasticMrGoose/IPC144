#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "phoneData.h"

void loadPhoneInfo(struct phoneData* phone)
{
	int i;

	FILE* fp = NULL;
	fp = fopen("phoneIn.txt", "r"); 

	if (fp != NULL)
	{
		for (i = 0; !feof(fp); i++)
		{
			fscanf(fp, "%[^|]|%lld|%lf|%d|%lf\n", phone[i].name, &phone[i].callNumber, 
				&phone[i].callTime, &phone[i].dataBytes, &phone[i].screenTime);

			//convert call time to minutes and seconds
			phone[i].callMinutes = convertMinutes(phone[i].callTime);
			phone[i].callSeconds = convertSeconds(phone[i].callTime, 
				phone[i].callMinutes);

			//convert screen time to minutes and seconds
			phone[i].screenMinutes = convertMinutes(phone[i].screenTime);
			phone[i].screenSeconds = convertSeconds(phone[i].screenTime, 
				phone[i].screenMinutes);
		}
	}

	return;
}

void showAllData(struct phoneData* phone, int num_phones)
{
	int i, j;

	//used to prevent the same name from being displayed again
	for (i = 0; i < num_phones; i++)
	{
		phone[i].shown = 0;
	}

	for (i = 0; i < num_phones; i++)
	{
		if (phone[i].shown == 0) //only display names once
		{
			printf("---------------------------------------------\n");
			printf("User: %s\n", phone[i].name);
			printf("   Number Called  Duration\n");
			for (j = 0; j < num_phones; j++)
			{
				if (strcmp(phone[j].name, phone[i].name) == 0) //searches for the same name
				{
					phone[j].shown = 1;
					if (phone[j].callNumber != 0)
					{
						printf("%16lld  %d:%02d\n", phone[j].callNumber, phone[j].callMinutes,
							phone[j].callSeconds);
					}
				}
			}
			printf("Bytes Transferred\n");
			for (j = 0; j < num_phones; j++)
			{
				if (strcmp(phone[j].name, phone[i].name) == 0 && phone[j].dataBytes != 0)
				{
					printf("%18d\n", phone[j].dataBytes);
				}
			}
			printf("Screen Minutes\n");
			for (j = 0; j < num_phones; j++)
			{
				if (strcmp(phone[j].name, phone[i].name) == 0 && phone[j].screenTime != 0)
				{
					printf("%12d:%02d\n", phone[j].screenMinutes,
						phone[j].screenSeconds);
				}
			}
		}
	}
	printf("\n");
	return;
}

int convertMinutes(double time)
{
	int minute;

	minute = (time * 60) / 60;
	return minute;
}

int convertSeconds(double time, int minute)
{
	int second;

	second = (time * 60) - (minute * 60) + 0.001;
	return second;
}