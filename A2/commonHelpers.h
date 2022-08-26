#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

//function prototypes

int currentYear(void); //get current year

void clearStandardInputBuffer(void); //clears the standard input buffer

int getInteger(void); //get an integer from user

int getPositiveInteger(void); //get a positive integer from user

//get an interger from a user defined range
int getIntFromRange(int lower_bound, int upper_bound); 

double getDouble(void); //get a double from user

double getPositiveDouble(void); //get a positive double from user

char getCharOption(const char test_letters[]); // get a letter from user

//get a string from user within a user defined size
void getCString(char* test_word, int min_char, int max_char); 

#endif 

