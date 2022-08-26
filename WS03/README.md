1. The two selection constructs to convert the month integer to the month name are the “if" and “switch” statements. 

An example of the “if" statement in C follows:
if (month == 1)
{
    month = "JAN";
} 
else if (month == 2)
{
    month = "FEB";
}
printf (“Log starting date: %d-%s-01”, year, month)

An example of the “switch” statement follows: 
switch (month) 
{
    case 1:
	month = "JAN";
	break;

    case 2:
	month = "FEB";
	break;
}
printf (“Log starting date: %d-%s-01”, year, month)

2. The three iteration constructs are the “for”, “while”, and “do while” statement. The construct I used for my validation routine is the “while” statement. I chose this statement because the program required the user to be prompt again if they entered a rating greater than 5 or less than 0. With the “while” statement, if the wrong value was entered, it would make the “while” condition true, which displays the error message and prompts the user for a value again. This process would repeat as long as the value is not in the desired range. If the user entered the value within the correct range, then the “while” condition would be false, thus exiting the loop.  

3. To test and debug my program, I would run the program and enter different values that tests all the possible conditions to see if the proper response is given. I would also run a print statement to see if the variables are correct. For programs with calculations, I also do a manual calculation with a calculator. To go about finding the problems I would check the error and warning messages in the Visual Studio IDE as well as simply reading the code to look for semantic or syntactic errors. As a habit, I tend to test a section of code immediately after writing it to ensure that section is working as intended before moving on. That way, the bugs are fixed as soon as possible, and I won’t always have to comb through the whole section at the end trying to locate the issue.  
