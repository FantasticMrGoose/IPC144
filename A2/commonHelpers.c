#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "commonHelpers.h"

#define MAX_SIZE 101

//function definitions

int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

void clearStandardInputBuffer(void)
{
	while (getchar() != '\n')
		;
	return;
}

int getInteger(void)
{
	int i, stop = 0, r_value;
	char newline;
	while (stop == 0)
	{
		do // scanf continue until new line is detected
		{
			r_value = scanf("%d%c", &i, &newline);
			if (r_value < 2) //if scanf < 2, it means bad format
			{
				clearStandardInputBuffer();
				printf("ERROR: Value must be an integer: ");
			}
			else
			{
				stop = 1;
			}
		} while (newline != '\n');
	}
	return i;
}

int getPositiveInteger(void)
{
	int i, stop = 0;
	char newline;
	while (stop == 0)
	{
		do
		{
			scanf("%d%c", &i, &newline);
			if (i > 0)
			{
				stop = 1;
			}
			else
			{
				printf("ERROR: Value must be a positive integer greater than zero: ");
			}
		} while (newline != '\n');
	}
	return i;
}

int getIntFromRange(int lower_bound, int upper_bound)
{
	int i, stop = 0, r_value;
	char newline;
	while (stop == 0)
	{
		do
		{
			r_value = scanf("%d%c", &i, &newline);
			if (r_value < 2) //if scanf < 2, it means bad format
			{
				clearStandardInputBuffer();
				printf("ERROR: Value must be an integer: ");

			}
			else if ((i < lower_bound) || (i > upper_bound))
			{
				printf("ERROR: Value must be between %d and %d inclusive: ", lower_bound, upper_bound);
			}
			else
			{
				stop = 1;
			}
		} while (newline != '\n');
	}
	return i;
}

double getDouble(void)
{
	int stop = 0, r_value;
	double i;
	char newline;
	while (stop == 0)
	{
		do
		{
			r_value = scanf("%lf%c", &i, &newline);
			if ((r_value < 2) || (newline != '\n'))
			{
				clearStandardInputBuffer();
				printf("ERROR: Value must be a double floating-point number: ");
			}
			else
			{
				stop = 1;
			}
		} while (newline != '\n');
	}
	return i;
}

double getPositiveDouble(void)
{
	int stop = 0;
	double i;
	char newline;
	do
	{
		do
		{
			scanf("%lf%c", &i, &newline);

			if (newline != '\n')
			{
				clearStandardInputBuffer();
				printf("ERROR: Value must be a double floating-point number: ");
			}
			else if (i > 0)
			{
				stop = 1;
			}
			else
			{
				printf("ERROR: Value must be a positive double floating-point number: ");
			}
		} while (newline != '\n');
	} while (stop == 0);
	return i;
}

char getCharOption(const char test_letters[])
{
	int i, stop = 0, size;
	char letter;

	// used to prevent corruption of variable if user enters more than 1 letter
	char buffer[11] = { '\0' };;
	do
	{
		size = 0;
		scanf("%10s", buffer);
		size = strlen(buffer);
		//loops through string to find a match
		for (i = 0; test_letters[i] != '\0'; i++)
		{
			//makes sure only 1 char is entered
			if ((test_letters[i] == buffer[0]) && (size == 1))
			{
				letter = buffer[0];
				stop = 1;
			}
			
		}
		if (stop == 0)
		{
			clearStandardInputBuffer();
			printf("ERROR: Character must be one of [%s]: ", test_letters);
		}
	} while (stop == 0);
	clearStandardInputBuffer(); // clears any residual input 
	return letter;
}
void getCString(char* test_word, int min_char, int max_char)
{
	int num_letter, stop = 0;
	
	char buffer[MAX_SIZE] = { '\0' }; // used to prevent corruption of 1st parameter

	while (stop == 0)
	{
		scanf("%100[^\n]", buffer);
		
		//counts num of letters in string
		num_letter = strlen(buffer);

		//exits if num letters match
		if ((num_letter >= min_char) && (num_letter <= max_char)) 
		{
			stop = 1;
		}
		else if ((num_letter != max_char) && (min_char == max_char))
		{
			clearStandardInputBuffer();
			printf("ERROR: String length must be exactly %d chars: ", max_char);
		}
		else if (num_letter > max_char)
		{
			clearStandardInputBuffer();
			printf("ERROR: String length must be no more than %d chars: ", max_char);
		}
		else if (num_letter < min_char)
		{
			clearStandardInputBuffer();
			printf("ERROR: String length must be between %d and %d chars: ",
				min_char, max_char);
		}
	}
	// transfers the content of buffer (back) to 1st parameter
	strncpy(test_word, buffer, max_char);
	clearStandardInputBuffer(); // clears any residual input
	return;
}
