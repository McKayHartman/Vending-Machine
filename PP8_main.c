// Header files
#include "vending_lib.h"
// main function
int main()
{
	// initize array
	double array[4][3];
	// stock machine
	stockMachine(array);
	// create cart
	struct CartItem cart[MAX_NUM_PRODUCTS];
	// display products
	displayProducts(array);
	// get product and store in code
	int code = getProduct();
	// get num and store in quant
	int quant = getQuantity(code, array);
	// initialize num of prod to 0
	int numOfProducts = 0;
	// loop though quants
	for(int i = 0; i < quant; i++)
	{
		// create item
		struct CartItem item = selectItem(code, array, quant);
		// add it to cart
		addToCart(cart, item);
		// set array correctly (it breaks otherwise)
		array[0][0] = 0;
		array[0][1] = 1.99;
		int counter = 0;
		// this is to ensure none of 0 have been purchased
		for(int i = 0; i < numOfProducts; i++)
		{
			if(cart[i].prod.food == 0)
			{
				counter++;
			}
		}
		// again, it breaks if it isnt here
		array[0][2] = 10 - counter;
		numOfProducts++;
	}
	
	// create more
	char more;
	// ask for input
	printf("Would you like anything else [y|n]: ");
	// read input
	scanf(" %c", &more);
	// while loop
	while(more == 'y')
	{	
		// display remaining products
		displayProducts(array);
		// get item
		int code = getProduct();
		// get quant
		int quant = getQuantity(code, array);
		// loop through quantaty
		for(int i = 0; i < quant; i++)
		{
			// create struct
			struct CartItem item = selectItem(code, array, quant);
			// add to cart
			addToCart(cart, item);
			// same as before, set the first array in the 2d array correct
			// it will create really bug numbers without this
			array[0][0] = 0;
			array[0][1] = 1.99;
			int counter = 0;
			for(int i = 0; i < numOfProducts; i++)
			{
				if(cart[i].prod.food == 0)
				{
					counter++;
				}
			}
			array[0][2] = 10 - counter;
			numOfProducts++;
		}
		// ask for input
		printf("Would you like anything else [y|n]: ");
		// read input
		scanf(" %c", &more);
	}
	// get bill
	pay(cart, numOfProducts, array);

	// return success
	return 0;


}