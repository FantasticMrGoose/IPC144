1. Arrays store information in elements that is identified by a unique index which starts at zero.  For example, the first element in an array is identified by the index ‘0’, and the second element by index ‘1’, and so on. If we call index ‘0’ of three different (parallel) arrays, each array will provide the data stored in the first element. If we call index ‘6’ of three parallel arrays, we are provided with the data stored in the 7th element of each array. In this case, the ‘key’ to link related data in different arrays would be the index. To link related data for any given item, we specify what index we wish to store the related data in. By specifying index ‘0’, we can say that we want to store “800” in the first element of the cost array, “3” in the first element of the priority array, and “Y” in the first element of the finance array. This way, the related data is now linked by their position in the array, referenced by the index number. When we want to display the related data of an item, we simply refer to the index of the parallel arrays at which the item was stored, keeping in mind the numbering system of arrays.  

2.It is common practice to set the iterator variable to zero because the variable is used to specify what index we want to store our data on. Since the index that identifies the first element in an array begins at zero, if we want to store data at the first element we must begin the iterator variable, and subsequently the index at zero. Using the following code as an example: 


double cost[max_numItem]; //the array

for (count_item = 0; count_item < num_item; count_item++)

    do 
	{
	    printf("   Item cost: $");
	    scanf("%lf", &cost[count_item]);
        } while (cost[count_item] < min_itemPrice);


The variable for ‘count_item’ begins with a zero because we want to store the cost of our first item in the first element. Since ‘count_item = 0’, “scanf("%lf", &cost[count_item]);” becomes “scanf("%lf", &cost[0]);” thus storing the user input into the first element of the ‘cost’ array. Unless the programmer wants to leave the first or subsequent positions of an array unchanged, this is why it is common practice to set the iterator variable to zero. 

3. An array is something that helps you store items in order so that when you need it later, you can easily find it if you know what you are looking for. That knowledge is the ‘key’ to finding something in an array.  Think of bookshelves in a library. When the librarian put away books, they are usually sorted by the author’s last name in alphabetical order A to Z. This means that every book is organized and has a position in the bookshelf. If the author’s last name started with an ‘A’, their book would most likely take up the first position on the bookshelf. Now if you know the last name of the author of the book you wanted to find, you now have the ‘key’. If the author’s last name started with a ‘M’, you would look through the bookshelf until you reached the ‘M’ section and select the book matches the name. You could also find the book if you knew exactly which position it was in. Arrays work in a similar way. Items are stored in things called elements. These elements are organized by first come first server. If you put a book, then a pencil, then a crayon into an array, they will be arranged in that position. If you wanted to take out the crayon, you must know what position it is placed in, which is position 3. 
