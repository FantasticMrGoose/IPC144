#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define min_numItem 1
#define max_numItem 10

int main()
{

	const double max_income = 400000, min_income = 500, min_itemPrice = 100;
	const int min_priority = 1, max_priority = 3;
	double net_income, total_cost = 0, select_cost = 0;
	int num_item, count_item, choice, total_month, 
		remaining_month, total_year, pick_priority,
		stop = 0, check = 1, finan_opt = 0;

	double cost[max_numItem];
	int priority[max_numItem];

	//char arrays require 1 extra space for terminator element
	char finance[max_numItem + 1]; 

	printf("+--------------------------+\n");
	printf("+   Wish List Forecaster   |\n");
	printf("+--------------------------+\n");

	do //asks for income
	{
		printf("\nEnter your monthly NET income: $");
		scanf("%lf", &net_income);

		if ((net_income < min_income))
		{
			printf("ERROR: You must have a consistent monthly income of at least $%.2lf\n", min_income);
		}
		else if (net_income > max_income)
		{
			printf("ERROR: Liar! I'll believe you if you enter a value no more than $%.2lf\n", max_income);
		}
	}
	//keeps the net income between 500 and 400,000
	while (net_income < min_income || net_income > max_income);

	do //asks for # of items
	{
		printf("\nHow many wish list items do you want to forecast?: ");
		scanf("%d", &num_item);

		if (((num_item < min_numItem) || (num_item > max_numItem)))
		{
			printf("ERROR: List is restricted to between %d and %d items.\n", min_numItem, max_numItem);
		}
	} while ((num_item < min_numItem) || (num_item > max_numItem)); //keeps number of wishes between 1 and 10

	//Iterates number of times based on the number of items entered
	for (count_item = 0; count_item < num_item; count_item++)
	{
		printf("\nItem-%d Details:\n",
			count_item + 1); //+1 to display the item ID starting at 1

		do //asks for price 
		{
			printf("   Item cost: $");
			scanf("%lf", &cost[count_item]);

			if (cost[count_item] < min_itemPrice) 
			{
				printf("      ERROR: Cost must be at least $%.2lf\n", min_itemPrice);
			}
		} while (cost[count_item] < min_itemPrice);//asks price again if under $100

		
		do //asks for priority
		{
			printf("   How important is it to you? [1=must have, 2=important, 3=want]: ");
			scanf("%d", &priority[count_item]);

			if ((priority[count_item] < min_priority) || (priority[count_item] > max_priority))
			{
				printf("      ERROR: Value must be between %d and %d\n", min_priority, max_priority);
			}
		}
		//asks for priority again if not between 1-3
		while ((priority[count_item] < min_priority) || (priority[count_item] > max_priority));

		
		do //asks for finance option 
		{
			printf("   Does this item have financing options? [y/n]: ");
			scanf(" %c", &finance[count_item]);

			if ((finance[count_item] != 'y') && (finance[count_item] != 'n'))
			{
				printf("      ERROR: Must be a lowercase 'y' or 'n'\n");
			}

			//asks for finance option if anything else besides 'y' or 'n' is entered 
		} while ((finance[count_item] != 'y') && (finance[count_item] != 'n'));

	}

	printf("\nItem Priority Financed        Cost\n");
	printf("---- -------- -------- -----------\n");

	//cycles through all items to display
	for (count_item = 0; count_item < num_item; count_item++)
	{
		printf("%3d  %5d    %5c    %11.2lf\n", count_item + 1,
			priority[count_item], finance[count_item], cost[count_item]);

		total_cost += cost[count_item]; //gives total cost of everything
	}
	printf("---- -------- -------- -----------\n");
	printf("                      $%11.2lf\n", total_cost);

	while (stop == 0) // continues program until user prompts exit
	{
		do
		{
			printf("\nHow do you want to forecast your wish list?\n");
			printf(" 1. All items (no filter)\n");
			printf(" 2. By priority\n");
			printf(" 0. Quit/Exit\n");
			printf("Selection: ");
			scanf("%d", &choice);
			printf("\n");

			if ((choice < 0) || (choice > 2)) //gives error if choice isn't 0-2
			{
				printf("ERROR: Invalid menu selection.\n");
			}
		} while ((choice < 0) || (choice > 2));
		
		if (choice == 1) 
		{
			//calculate and round months. Since we are paying monthly, 
			//if (total cost / net income) is not a whole number, we must count
			//the decimal as a whole month, thus we add 0.99 to round everything up.
			total_month = (total_cost / net_income) + 0.99;

			//calculate years and remaining months
			total_year = (total_month / 12);
			remaining_month = (total_month % 12);
			

			printf("====================================================\n");
			printf("Filter:   All items\n");
			printf("Amount:   $%1.2lf\n", total_cost);
			printf("Forecast: %d years, %d months\n", total_year, remaining_month);

			//checks each item in array for finance option
			for (count_item = 0; (count_item < num_item) && (check == 1); count_item++) // || might be better
			{
				if (finance[count_item] == 'y')
				{
					finan_opt = 1;
					check = 0; //stops check after finding the first 'y' for finance 
				}
				else
				{
					finan_opt = 0;;
				}
			}

			if (finan_opt == 1) 
			{
				printf("NOTE: Financing options are available on some items.\n"
					"      You can likely reduce the estimated months.\n");
			}
			printf("====================================================\n");
		}


		else if (choice == 2) 
		{
			do
			{
				printf("What priority do you want to filter by? [1-3]: ");
				scanf("%d", &pick_priority);
				printf("\n");

				if ((pick_priority < min_priority) || (pick_priority > max_priority))
				{
				printf("   ERROR: Invalid menu selection.\n");
				}
			} while ((pick_priority < min_priority) || (pick_priority > max_priority));

			//reset variables for each iteration
			select_cost = 0; 
			finan_opt = 0;

			//initiates process to tally cost based on priority
			if ((pick_priority >= min_priority) && (pick_priority <= max_priority))
			{
				for (count_item = 0; count_item < num_item; count_item++)
				{
					//only adds costs of the selected priority
					if (priority[count_item] == pick_priority)
					{
						select_cost += cost[count_item];

						if (finance[count_item] == 'y')
						{
							finan_opt = 1;
						}

					}
				}

				total_month = (select_cost / net_income) + 0.99;
				total_year = (total_month / 12);
				remaining_month = (total_month % 12);
				

				printf("====================================================\n");
				printf("Filter:   by priority (%d)\n", pick_priority);
				printf("Amount:   $%1.2lf\n", select_cost);
				printf("Forecast: %d years, %d months\n", total_year, remaining_month);

				if (finan_opt == 1)
				{
					printf("NOTE: Financing options are available on some items.\n"
						"      You can likely reduce the estimated months.\n");
				}
				printf("====================================================\n");
			}

			
		}
		else if (choice == 0) //exits program as per user input 
		{
			printf("\nBest of luck in all your future endeavours!\n");
			stop = 1;
		}
	};
	return 0;
}