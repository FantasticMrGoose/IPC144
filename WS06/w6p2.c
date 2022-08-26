/*
	==================================================
	Workshop #6 (Part-2):
	==================================================
	Name   :Ziran Jeffrey Zhou
	ID     :145117206
	Email  :zjzhou2@myseneca.ca
	Section:NNN
*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include "w6p2.h"


//Get user input of integer type and validate for a positive non-zero number
int getIntPositive(int* positive_num)
{
	int x;

	do // continues to scan for input until conditions are met
	{
		scanf("%d", &x);
		if (x <= 0)
		{
			printf("ERROR: Enter a positive value: ");
		}
	} while (x <= 0);

	// assigns entered value to input if pointer is not null
	if (positive_num != NULL)
	{
		*positive_num = x;
	}
	return x;
}

//Get user input of double type
double getDoublePositive(double* positive_num)
{
	double x;
	do
	{
		scanf("%lf", &x);
		if (x <= 0)
		{
			printf("ERROR: Enter a positive value: ");
		}
	} while (x <= 0);
	if (positive_num != NULL)
	{
		*positive_num = x;
	}
	return x;
}

//Opening Message (include the number of products that need entering)
void openingMessage(const int num_product)
{
	printf("Cat Food Cost Analysis\n");
	printf("======================\n\n");
	printf("Enter the details for %d dry food bags of product data for analysis.\n",
		num_product);
	printf("NOTE: A 'serving' is %dg\n", NUM_GRAMS);

	return;
}

//Get user input for the details of cat food product
struct CatFoodInfo getCatFoodInfo(const int product_sequence)
{
	int j, k;
	struct CatFoodInfo food;

	printf("\nCat Food Product #%d\n", product_sequence + 1);
	printf("--------------------\n");
	printf("SKU           : ");
	food.SKU = getIntPositive(&j); //different ways to call helper function
	printf("PRICE         : $");
	food.price = getDoublePositive(NULL);
	printf("WEIGHT (LBS)  : ");
	food.weight_pounds = getDoublePositive(NULL);
	printf("CALORIES/SERV.: ");
	food.calories = getIntPositive(&k);

	return food;
}

//Display the formatted table header
void displayCatFoodHeader(void)
{
	printf("\nSKU         $Price    Bag-lbs Cal/Serv\n");
	printf("------- ---------- ---------- --------\n");
	return;
}

//Display a formatted record of cat food data
void displayCatFoodData(const int SKU, const double* price, const int calories,
	const double* weight_pounds)
{
	printf("%07d %10.2lf %10.1lf %8d\n", SKU, *price, *weight_pounds, calories);
	return;
}

//convert lbs: kg 
double convertLbsKg(const double* pounds, double* kg)
{
	double x;
	x = *pounds / LBS_PER_KG; //dereferenced before doing calc

	if (kg != NULL)
	{
		*kg = x;
	}
	return x;
}

//convert lbs: g 
int convertLbsG(const double* pounds, int* grams)
{
	double i;
	int x;
	i = convertLbsKg(pounds, NULL);
	x = i * KG_PER_GRAM;

	if (grams != NULL)
	{
		*grams = x;
	}
	return x;
}

//convert lbs: kg and g
void convertLbs(const double* pounds, double* kg, int* grams)
{
	double i;
	int x;
	i = convertLbsKg(pounds, NULL);
	*kg = i;
	x = convertLbsG(pounds, NULL);
	*grams = x;
	return;
}

//calculate: servings based on gPerServ
double calculateServings(const int serving_size_g, const int total_grams, double* total_servings)
{
	double i;
	i = (total_grams / (double)serving_size_g);
	if (total_servings != NULL)
	{
		*total_servings = i;
	}
	return i;
}

//calculate: cost per serving
double calculateCostPerServing(const double* price, const double* total_servings, double* cost_per_serving)
{
	double i;
	i = (*price / *total_servings);
	if (cost_per_serving != NULL)
	{
		*cost_per_serving = i;
	}
	return i;
}

//calculate: cost per calorie
double calculateCostPerCal(const double* price, const double* total_calorie,
	double* cost_per_calorie)
{
	double i;
	i = (*price / *total_calorie); 
	if (cost_per_calorie != NULL)
	{
		*cost_per_calorie = i;
	}
	return i;
}

//Derive a reporting detail record based on the cat food product data
struct ReportData calculateReportData(const struct CatFoodInfo food)
{
	double i;
	struct ReportData report;
	printf("\nThe size of report is %d\n", sizeof(food));

	report.weight_kg = convertLbsKg(&food.weight_pounds, NULL);
	report.weight_grams = convertLbsG(&food.weight_pounds, NULL);
	report.total_servings = calculateServings(NUM_GRAMS, 
		report.weight_grams, NULL);
	report.cost_per_serving = calculateCostPerServing(&food.price, 
		&report.total_servings, NULL);

	i = report.total_servings * food.calories; //calculates total calories

	report.cal_cost_per_serve = calculateCostPerServing(&food.price, 
		&i, NULL);

	return report;
}

//Display the formatted table header for the analysis results
void displayReportHeader(void)
{
	printf("\nAnalysis Report (Note: Serving = %dg\n", NUM_GRAMS);
	printf("---------------\n");
	printf("SKU         $Price    Bag-lbs     Bag-kg     Bag-g Cal/Serv Servings  $/Serv   $/Cal\n");
	printf("------- ---------- ---------- ---------- --------- -------- -------- ------- -------\n");
	return;
}

//Display the formatted data row in the analysis table
void displayReportData(const struct ReportData report, const int cheapest_option)
{
	


	if (cheapest_option == 0)
	{
		printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf\n",
			report.food.SKU, report.food.price, report.food.weight_pounds, report.weight_kg,
			report.weight_grams, report.food.calories, report.total_servings,
			report.cost_per_serving, report.cal_cost_per_serve);
	}
	else
	{
		printf("%07d %10.2lf %10.1lf %10.4lf %9d %8d %8.1lf %7.2lf %7.5lf ***\n",
			report.food.SKU, report.food.price, report.food.weight_pounds, report.weight_kg,
			report.weight_grams, report.food.calories, report.total_servings,
			report.cost_per_serving, report.cal_cost_per_serve);
	}
	return;
}

//Display the findings (cheapest)
void displayFinalAnalysis(const struct CatFoodInfo food)
{
	printf("\nFinal Analysis\n");
	printf("--------------\n");
	printf("Based on the comparison data, the PURRR-fect economical option is:\n");
	printf("SKU:%07d Price: $%.2lf\n\n", food.SKU, food.price);
	printf("Happy shopping!\n");
}

//Logic entry point
void start(void)
{
	int i;
	double n, get_lowest;
	int econ_option[MAX_PRODUCT] = { 0, 0, 0 };

	// create array 
	struct CatFoodInfo food[MAX_PRODUCT] = { { 0 } };
	struct ReportData report[MAX_PRODUCT] = { { 0 } };

	openingMessage(MAX_PRODUCT);

	//iterate necessary # of time to get user input for cat food info and report
	for (i = 0; i < MAX_PRODUCT; i++)
	{
		food[i] = getCatFoodInfo(i);
	}
	for (i = 0; i < MAX_PRODUCT; i++)
	{
		report[i] = calculateReportData(food[i]); // sends food array to function
	}

	get_lowest = report[0].cost_per_serving; // placeholder price for comparison 

	//finds the cheapest food
	for (i = 0; i < MAX_PRODUCT; i++)
	{
		n = report[i].cost_per_serving;
		if (n < get_lowest)
		{
			get_lowest = n;
		}
	}

	//sets the array index of the cheapest food to 1
	for (i = 0; i < MAX_PRODUCT; i++)
	{
		if (report[i].cost_per_serving == get_lowest)
		{
			econ_option[i] = 1;
		}
	}

	displayCatFoodHeader();

	for (i = 0; i < MAX_PRODUCT; i++)
	{
		displayCatFoodData(food[i].SKU, &food[i].price, food[i].calories, &food[i].weight_pounds);
	}

	displayReportHeader();
	
	for (i = 0; i < MAX_PRODUCT; i++)
	{
		displayReportData(report[i], econ_option[i]);
	}

	for (i = 0; i < MAX_PRODUCT; i++)
	{
		if (econ_option[i] == 1)
		{
			displayFinalAnalysis(food[i]);
		}
	}
	return;
}
