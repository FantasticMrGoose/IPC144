#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define MIN_YEAR 2010
#define MAX_YEAR 2021
#define LOG_DAYS 3

int main(void)
{
	const int JAN = 1, DEC = 12;
	int year, month,
		stop = 0, day;
	double mor_rating, eve_rating,
		mor_total = 0, eve_total = 0,
		avg_mor, avg_eve, avg_total;
	

	printf("General Well-being Log\n");
	printf("======================\n");

	while (stop == 0) // program continues as long as stop is equal to 0
	{
		printf("Set the year and month for the well-being log (YYYY MM): ");
		scanf("%d %d", &year, &month);

		// if both year and month are out of range, displays both messages
		if ((year < MIN_YEAR || year > MAX_YEAR) && (month < JAN || month > DEC))
		{
			printf("   ERROR: The year must be between 2010 and 2021 inclusive\n");
			printf("   ERROR: Jan.(1) - Dec.(12)\n");
		}

		// if only the year is out of range, display this message
		else if (year < MIN_YEAR || year > MAX_YEAR)
		{
			printf("   ERROR: The year must be between 2010 and 2021 inclusive\n");
		}

		// if only month is out of range, display the following message 
		else if (month < JAN || month > DEC)
		{
			printf("   ERROR: Jan.(1) - Dec.(12)\n");
		}
		else
		{
			printf("\n"); // formatting 
			printf("*** Log date set! ***\n");
			printf("\n");

			stop = 1; // program stops asking once correct date is set
		}
	}

	// ensures the log continues for specified # of log days
	for (day = 1; day <= LOG_DAYS; day++)
	{

		switch (month) // converts the month integer to month name
		{
		case 1:
			printf("%d-JAN-%02d\n", year, day);
			break;
		case 2:
			printf("%d-FEB-%02d\n", year, day);
			break;
		case 3:
			printf("%d-MAR-%02d\n", year, day);
			break;
		case 4:
			printf("%d-APR-%02d\n", year, day);
			break;
		case 5:
			printf("%d-MAY-%02d\n", year, day);
			break;
		case 6:
			printf("%d-JUN-%02d\n", year, day);
			break;
		case 7:
			printf("%d-JUL-%02d\n", year, day);
			break;
		case 8:
			printf("%d-AUG-%02d\n", year, day);
			break;
		case 9:
			printf("%d-SEP-%02d\n", year, day);
			break;
		case 10:
			printf("%d-OCT-%02d\n", year, day);
			break;
		case 11:
			printf("%d-NOV-%02d\n", year, day);
			break;
		case 12:
			printf("%d-DEC-%02d\n", year, day);
			break;
		}

		printf("   Morning rating (0.0-5.0): ");
		scanf("%lf", &mor_rating);

		// repeats prompt until input is within range
		while (mor_rating < 0 || mor_rating > 5)
		{
			printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!\n");
			printf("   Morning rating (0.0-5.0): ");
			scanf("%lf", &mor_rating);
		}

		mor_total += mor_rating; // tracks total morning rating

		printf("   Evening rating (0.0-5.0): ");
		scanf("%lf", &eve_rating);

		while (eve_rating < 0 || eve_rating > 5)
		{
			printf("      ERROR: Rating must be between 0.0 and 5.0 inclusive!\n");
			printf("   Evening rating (0.0-5.0): ");
			scanf("%lf", &eve_rating);
		}

		eve_total += eve_rating; // tracks total evening rating
		printf("\n");
	}
	printf("Summary\n");
	printf("=======\n");

	printf("Morning total rating: %.3lf\n", mor_total);
	printf("Evening total rating: %.3lf\n", eve_total);
	printf("---------------------------\n");
	printf("Overall total rating: %.3lf\n", mor_total + eve_total);
	printf("\n");

	//calculates average of ratings
	avg_mor = mor_total / LOG_DAYS;
	avg_eve = eve_total / LOG_DAYS;
	avg_total = (mor_total + eve_total) /
		((double)LOG_DAYS * 2); //cast LOG_DAYs as a double to avoid overflow

	printf("Average morning rating: %.1lf\n", avg_mor);
	printf("Average evening rating: %.1lf\n", avg_eve);
	printf("---------------------------\n");
	printf("Average overall rating: %.1lf\n", avg_total);

	return 0;
}
