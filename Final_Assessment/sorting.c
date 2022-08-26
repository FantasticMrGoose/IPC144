#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include "sorting.h"
#include "phoneData.h"

//sort by call duration
void sortByDuration(struct phoneData* phone, struct tempStorage* temp_phone, 
	const int num_phones)
{
	int i, j, m;
	double temp;
	char name[31] = { '\0' };

	//reset variables
	for (i = 0; i < num_phones; i++)
	{
		phone[i].shown = 0;
		temp_phone[i].name[0] = '\0';
		temp_phone[i].callTime = 0;
	}

	// aggregate all phone duration into respective accounts
	for (i = 0; i < num_phones; i++)
	{
		if (phone[i].shown == 0)
		{
			for (j = 0; j < num_phones; j++)
			{
				if (strcmp(phone[j].name, phone[i].name) == 0)
				{
					phone[j].shown = 1;
					strcpy(temp_phone[i].name, phone[j].name);
					temp_phone[i].callTime += phone[j].callTime;

				}
			}
		}
	}

	//sort phone time by ascending order. 
	for (i = 0; i < num_phones; i++)
	{
		m = i;
		for (j = i + 1; j < num_phones; j++)
			if (temp_phone[j].callTime < temp_phone[m].callTime)
			{
				m = j;
			}
		if (m != i)
		{
			temp = temp_phone[i].callTime;
			strcpy(name, temp_phone[i].name);
			temp_phone[i].callTime = temp_phone[m].callTime;
			strcpy(temp_phone[i].name, temp_phone[m].name);
			temp_phone[m].callTime = temp;
			strcpy(temp_phone[m].name, name);
		}
	}
	
	printf("                          User  Call Duration");
	for (i = 0; i < num_phones; i++) 
	{
		if (temp_phone[i].callTime > 0)
		{
			temp_phone[i].callMinutes = convertMinutes(temp_phone[i].callTime);
			temp_phone[i].callSeconds = convertSeconds(temp_phone[i].callTime, 
				temp_phone[i].callMinutes);
			printf("\n%30s %11d:%02d", temp_phone[i].name, temp_phone[i].callMinutes, 
				temp_phone[i].callSeconds);
		}	
	}
	printf("\n\n");
	return;
}

//sort by data usage
void sortByData(struct phoneData* phone, struct tempStorage* temp_phone, 
	int num_phones)
{
	int i, j, m, temp;
	char name[31] = { '\0' };

	for (i = 0; i < num_phones; i++)
	{
		phone[i].shown = 0;
		temp_phone[i].name[0] = '\0';
		temp_phone[i].dataBytes = 0;
	}

	for (i = 0; i < num_phones; i++)
	{
		if (phone[i].shown == 0)
		{
			for (j = 0; j < num_phones; j++)
			{
				if (strcmp(phone[j].name, phone[i].name) == 0)
				{
					phone[j].shown = 1;
					strcpy(temp_phone[i].name, phone[j].name);
					temp_phone[i].dataBytes += phone[j].dataBytes;

				}
			}
		}
	}

	//sort phone time by ascending order. 
	for (i = 0; i < num_phones; i++)
	{
		m = i;
		for (j = i + 1; j < num_phones; j++)
			if (temp_phone[j].dataBytes < temp_phone[m].dataBytes)
			{
				m = j;
			}
		if (m != i)
		{
			temp = temp_phone[i].dataBytes;
			strcpy(name, temp_phone[i].name);
			temp_phone[i].dataBytes = temp_phone[m].dataBytes;
			strcpy(temp_phone[i].name, temp_phone[m].name);
			temp_phone[m].dataBytes = temp;
			strcpy(temp_phone[m].name, name);
		}
	}

	printf("                          User     Data Usage");
	for (i = 0; i < num_phones; i++)
	{
		if (temp_phone[i].name[0] != '\0')
		{
			printf("\n%30s %14d", temp_phone[i].name, temp_phone[i].dataBytes);
		}
	}
	printf("\n\n");
}

//sort by screen time
void sortByScreen(struct phoneData* phone, struct tempStorage* temp_phone, 
	int num_phones)
{
	int i, j, m;
	double temp;
	char name[31] = { '\0' };

	for (i = 0; i < num_phones; i++)
	{
		phone[i].shown = 0;
		temp_phone[i].name[0] = '\0';
		temp_phone[i].screenTime = 0;
	}

	// aggregate all phone duration into respective accounts
	for (i = 0; i < num_phones; i++)
	{
		if (phone[i].shown == 0)
		{
			for (j = 0; j < num_phones; j++)
			{
				if (strcmp(phone[j].name, phone[i].name) == 0)
				{
					phone[j].shown = 1;
					strcpy(temp_phone[i].name, phone[j].name);
					temp_phone[i].screenTime += phone[j].screenTime;

				}
			}
		}
	}

	//sort phone time by ascending order. 
	for (i = 0; i < num_phones; i++)
	{
		m = i;
		for (j = i + 1; j < num_phones; j++)
			if (temp_phone[j].screenTime < temp_phone[m].screenTime)
			{
				m = j;
			}
		if (m != i)
		{
			temp = temp_phone[i].screenTime;
			strcpy(name, temp_phone[i].name);
			temp_phone[i].screenTime = temp_phone[m].screenTime;
			strcpy(temp_phone[i].name, temp_phone[m].name);
			temp_phone[m].screenTime = temp;
			strcpy(temp_phone[m].name, name);
		}
	}

	printf("                          User    Screen Time");
	for (i = 0; i < num_phones; i++)
	{
		if (temp_phone[i].screenTime > 0)
		{
			temp_phone[i].screenMinutes = convertMinutes(temp_phone[i].screenTime);
			temp_phone[i].screenSeconds = convertSeconds(temp_phone[i].screenTime,
				temp_phone[i].screenMinutes);
			printf("\n%30s %11d:%02d", temp_phone[i].name, temp_phone[i].screenMinutes,
				temp_phone[i].screenSeconds);
		}
	}
	printf("\n\n");
	return;
}

