#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	double money;
	int num_coin, int_money, 
		int_fee, balance; 
	printf("Change Maker Machine\n");
	printf("====================\n");
	printf("Enter dollars and cents amount to convert to coins: $");
	scanf("%lf", &money);

	int_fee = ((money * 0.05) + 0.005) * (int)100; // rounds the fee to 2 decimal place and converts to integer and cents
	int_money = (money * 100) - int_fee; // subtracts fees from money, converts to integer 

	printf("Service fee (5.0 percent): %.2lf\n", (double)int_fee / 100); // prints the fee in double
	printf("Balance to dispense $%.2lf\n", (double)int_money / 100); // prints balance to be exchanged in double
	printf("\n"); // empty line for format

	num_coin = int_money / 200; //divides by 200 cents (2 dollars) to get number of coins
	balance = int_money % 200;  //modulus to calculate change
	printf("$2.00 Toonies  X %d (remaining: $%.2lf)\n", num_coin, (double)balance / 100); //displays change and remaining balance
	
	num_coin = balance / 100; //divides remaining balance by 100 cents to get number of coins
	balance %= 100; //modulus to calculate change
	printf("$1.00 Loonies  X %d (remaining: $%.2lf)\n", num_coin, (double)balance / 100);

	num_coin = balance / 25;
	balance %= 25; //modulus to calculate change
	printf("$0.25 Quarters X %d (remaining: $%.2lf)\n", num_coin, (double)balance / 100);

	num_coin = balance / 10;
	balance %= 10; //modulus to calculate change
	printf("$0.10 Dimes    X %d (remaining: $%.2lf)\n", num_coin, (double)balance / 100);

	num_coin = balance / 5;
	balance %= 5; //modulus to calculate change
	printf("$0.05 Nickels  X %d (remaining: $%.2lf)\n", num_coin, (double)balance / 100);

	num_coin = balance / 1;
	balance %= 1; //modulus to calculate change
	printf("$0.01 Pennies  X %d (remaining: $%.2lf)\n", num_coin, (double)balance / 100);

	printf("\n"); // empty line for format
	printf("All coins dispensed!");
	return 0;
}
