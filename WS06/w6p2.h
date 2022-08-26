#define MAX_PRODUCT 3
#define NUM_GRAMS 64
#define LBS_PER_KG 2.20462
#define KG_PER_GRAM 1000

// structures
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

// function prototypes
//Get user input of integer type and validate for a positive non-zero number
int getIntPositive(int* positive_num);

//Get user input of double type and validate for a positive non-zero number
double getDoublePositive(double* positive_num);

//Opening Message (include the number of products that need entering)
void openingMessage(const int num_product);

//Get user input for the details of cat food product
struct CatFoodInfo getCatFoodInfo(const int product_sequence);

//Display the formatted table header
void displayCatFoodHeader(void);

//Display a formatted record of cat food data
void displayCatFoodData(const int SKU, const double* price, const int calories,
	const double* weight_pounds);

//convert lbs: kg
double convertLbsKg(const double* pounds, double* kg);

//convert lbs: g
int convertLbsG(const double* pounds, int* grams);

//convert lbs: kg / g
void convertLbs(const double* pounds, double* kg, int* grams);

//calculate: servings based on gPerServ
double calculateServings(const int serving_size_g, const int total_grams, 
	double* total_servings);

//calculate: cost per serving
double calculateCostPerServing(const double* price, 
	const double* total_servings, double* cost_per_serving);

//calculate: cost per calorie
double calculateCostPerCal(const double* price, const double* total_calorie, 
	double* cost_per_calorie);

//Derive a reporting detail record based on the cat food product data
struct ReportData calculateReportData(const struct CatFoodInfo food); 

//Display the formatted table header for the analysis results
void displayReportHeader(void);

//Display the formatted data row in the analysis table
void displayReportData(const struct ReportData report, const int cheapest_option);

//Display the findings (cheapest)
void displayFinalAnalysis(const struct CatFoodInfo food);

//Logic entry point
void start(void);
