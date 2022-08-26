1.	The value 10.12 does not display as expected because when the processor calculates decimal points, it converts them to 	binary. However, most decimal points (base 10) when converted to binary (base 2), continues to go on forever therefore 	requiring an infinite size of RAM to store it, which is not possible. To overcome the issue of requiring infinite 	storage, the decimal point is rounded to the bit size specified by the format (float, double, etc.) (Source: 	https://www.youtube.com/watch?v=PZRI1IfStY0). Therefore, when we type “printf("10.12 = %.15lf\n", 10.12);” we are 	specifying the program to show us up to 15 decimal points, which rounds up to the 15th decimal point, but the actual 	value stored is dependent on what format specifier was used (double, float). 

2.	All possible values:
	a.	intValue % 2 = {0,1}
	b.	intValue % 3 = {0,1,2} 
	c.	intValue % 100 = {0…99}

3.	int totalSlices = 11 * 12;
	int estimatedSlicesConsumed = 21 * 3;
	int wholePizzasEaten = estimatedSlicesConsumed / 12; 
	int extraSlicesNeeded = estimatedSlicesConsumed % 12; 

	5 whole pizzas will be consumed, and 3 extra slices of a 6th pizza will be consumed.

4.	It is best to convert to integers when performing arithmetic operations because of the precisions of integers. Integers keep the exact value of the number since they do not have decimal points. Floats on the other hand while only showing up to a specified decimal point, continue to hold decimal points beyond what is displayed or used. Therefore, when doing arithmetic operations, the distant decimal points are bound to be lost when using floats which may lead to rounding errors. However, because integers are exact due to their lack of decimals, nothing is lost, therefore does not cause rounding errors. Additionally, the modulus operation is only available with integers, which allows for certain arithmetic operations to be performed faster (Source: IPC144 Week 3 Lecture). 
