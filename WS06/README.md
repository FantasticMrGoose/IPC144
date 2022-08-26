1. The “ReportData” structure has three int variables, taking up 4 bytes each, and six double variables, taking up 8 bytes each. This means that in total, the “ReportData” structure takes up a total of 60 bytes of memory. We can improve the passing of information to functions by using pointers, which passes the address of the variable which usually takes up 4 bytes. Contrasting this to pass by value, which makes a copy of the value of the variable and then passes it to the function, pointers reduce the memory requirement and takes out the extra step of having to make copies.  Using the “displayReportData” function as an example, currently the workshop’s instructions are pass by value meaning another 60 bytes of memory are allocated to store the copies of the variables in “ReportData”. If we were to pass by address using pointers, only the address of the structure would be passed, saving us memory and computing power. While this may not seem significant to modern computers, when a computer runs thousands of lines of code, it begins to add up.  

2. The “ReportData” structure can be improved by nesting the “CatFoodInfo” structure into the “ReportData” structure since some members are the same in both structures while keeping "CatFoodInfo" as a separate structure. For example:

struct CatFoodInfo
{
	int SKU;
	double price;
	int calories;
	double weight_pounds;
};

struct ReportData
{
	struct CatFoodInfo food;
	double weight_kg;
	int weight_grams;
	double total_servings;
	double cost_per_serving;
	double cal_cost_per_serve;
};

The variables from “CatFoodInfo” are nested within “ReportData” meaning they won’t have to be initialized again. 

Alternatively, we can also do an embedded structure and forgo the "CatFoodInfo" structure as a separate structure. For example:

struct ReportData
{
	struct CatFoodInfo
	{
		int SKU;
		double price;
		int calories;
		double weight_pounds;
	} food;
	double weight_kg;
	int weight_grams;
	double total_servings;
	double cost_per_serving;
	double cal_cost_per_serve;
};

Certain printf statement in the “displayReportData” function would also change to call the variables in “CatFoodInfo”. For example:

printf("...", report.SKU) into printf("...", report.food.SKU)
printf("...", report.price) into printf("...", report.food.price)
printf("...", report.weight_pounds) into printf("...", report.food.weight_pounds)
printf("...", report.calories) into printf("...", report.food.calories)

These changes would call the variables of “CatFoodInfo” structure, nested inside the “ReportData” structure. 
