#ifndef SORTING_H_
#define SORTING_H_

//function prototypes


//sort by call duration
void sortByDuration(struct phoneData* phone, struct tempStorage* temp_phone, 
	const int num_phones);

//sort by data usage
void sortByData(struct phoneData* phone, struct tempStorage* temp_phone, 
	const int num_phones);

//sort by screen time
void sortByScreen(struct phoneData* phone, struct tempStorage* temp_phone, 
	const int num_phones);

#endif !SORTING_H_
