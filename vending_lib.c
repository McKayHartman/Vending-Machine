// Header files
#include "vending_lib.h"

// Initialzie product list
char productList[4][100] = {"Hershey's Milk Chocolate Bar 1.55oz", "Pepsi Soda 20oz Bottle", "Extra Gum", "Doritos Chips"};

void stockMachine(double array[][3])
{
	// create temp
	double temp;
	// open file
	FILE *file = fopen("products.csv", "r");
	// loop rows
	for(int i = 0; i < 4; i++)
	{
		// loop products
		for(int j = 0; j < 3; j++)
		{
			// read item 
			fscanf(file, "%lf,", &temp);
			// store item
			array[i][j] = temp;
		}
	}
	
}

void displayProducts(double array[][3])
{
	// print labels
	printf("Code | Product Description");
	printf("| Available Quantity | Unit Price\n");
	printf("-----|--------------------------");
	printf("-----------|--------------------|------------\n");
	// loop through products
	for(int i = 0; i < 4; i++)
	{
		// display products
		printf("   %.0lf | %36s|      ", array[i][0], productList[i]);
		printf("           %2.0lf | %.2lf\n", array[i][2], array[i][1]);
	}
}

int getProduct()
{
	// initialize code
	int Code;
	// print message
	printf("Enter the code of product: ");
	// store input
	scanf("%d", &Code);
	// return code
	return Code;
}

int getQuantity(int Code, double array[][3])
{
	// initialize quant
	int quantity;
	// print message
	printf("Enter the quantity of product: ");
	// read input
	scanf("%d", &quantity);
	// while loop
	while(quantity > array[Code][2])
	{
		// print message
		printf("Not enough in stock.\n");
		printf("Enter the quantity of product: ");
		// read input
		scanf("%d", &quantity);
	}
	// return quant
	return quantity;
}

struct CartItem selectItem(int code, double array[][3], int quantity)
{
	// initialize struct
	struct CartItem item;
	// get type
	item.prod.food = array[code][0];
	// get price
	item.prod.price =  array[code][1];
	// get quant
	item.prod.quantityInStock =  array[code][2];
	// remove from vending machine
	array[code][2] -= quantity;
	// return struct
	return item;
}

bool addToCart(struct CartItem cart[MAX_NUM_PRODUCTS], struct CartItem a)
{
	// loop through current array
	for(int i = MAX_NUM_PRODUCTS; i >= 0; i--)
	{
		// move over 1
		cart[i] = cart[i-1];
	}
	// input item
	cart[0] = a;
	// return true
	return true;
}

void cancelPurchase(double array[][3], struct CartItem cart[MAX_NUM_PRODUCTS], int numOfProducts)
{
	// loop through products
	for(int i = 0; i < numOfProducts; i++)
	{
		// increment each
		(array[cart[i].prod.food][2])++;

	}
	// reset number of products
	numOfProducts = 0;
}

double generateBill(struct CartItem cart[MAX_NUM_PRODUCTS], double array[][3], int numOfProducts)
{
	// print column labels
	printf("Product             ");
	printf("                    | Unit Price | Product total\n");
	printf("----------------------------");
	printf("------------|------------|--------------\n");
	// initialize total order
	double order = 0;
	// initialize code 0
	int num0 = 0;
	// initialize code 1
	int num1 = 0;
	// initialize code 2
	int num2 = 0;
	// initialize code 3
	int num3 = 0;
	// loop through all products
	for(int i = 0; i < numOfProducts; i++)
	{
		// check if code 0
		if(cart[i].prod.food == 0)
			// increment count
			num0++;
		// check if code 1
		if(cart[i].prod.food == 1)
			// increment count
			num1++;
		// check if code 2
		if(cart[i].prod.food == 2)
			// increment count
			num2++;
		// check if code 3
		if(cart[i].prod.food == 3)
			// increment count
			num3++;
	}
	
	// check if any 0s
	if(num0 > 0)
	{
		// calculate local total
		double total = array[0][1] * num0;
		// add to total
		order += total;
		// print message
		printf("%d x %35s | %d x %.2lf   |%.2lf      \n", 
			num0, productList[0], num0, array[0][1], total);
	}
	// check if any 1s
	if(num1 > 0)
	{
		// calculate local total
		double total = array[1][1] * num1;
		// add to total
		order += total;
		// print message
		printf("%d x %35s | %d x %.2lf   |%.2lf      \n", 
			num1, productList[1], num1, array[1][1], total);
	}
	// check if any 2s
	if(num2 > 0)
	{
		// calculate local total
		double total = array[2][1] * num2;
		// add to total
		order += total;
		// print message
		printf("%d x %35s | %d x %.2lf   |%.2lf      \n", 
			num2, productList[2], num2, array[2][1], total);
	}
	// check if any 3s
	if(num3 > 0)
	{
		// calculate local total
		double total = array[3][1] * num3;
		// add to total
		order += total;
		// print message
		printf("%d x %35s | %d x %.2lf   |%.2lf      \n", 
			num3, productList[3], num3, array[3][1], total);
	}
	// print total
	printf("Order Total: %.2lf\n", order);
	// return total
	return order;
}

bool pay(struct CartItem cart[MAX_NUM_PRODUCTS], int numOfProducts, double array[][3])
{
	// initialize total cost and get bill
	double totalCost = generateBill(cart, array, numOfProducts);
	printf("--\n");
	// initialize method
	char method;
	// print message
	printf("How would you like to pay ");
	printf("Cash = 's', Card = 'c', Contactless Payment = 'q')\n");
	printf("0.02%% charge for card, 0.01%% charge");
	printf("for contactless payment: ");
	// read input
	scanf(" %c", &method);
	// check if cash
	if(method == 's')
	{
		// initialize amount
		double payment;
		// ask for input
		printf("Payment amount: ");
		// read input
		scanf("%lf", &payment);
		// print message
		printf("Paid by: Cash\n");
		printf("Service Fee: 0.00\n");
		printf("Paid amount: %.2lf\n", payment);
		// calcualte change
		double change = payment - totalCost;
		// print message
		printf("Change: %.2lf", change);
	}
	// if card
	else if(method == 'c')
	{
		// initialze card
		int card;
		// create cards
		char cardArr[4][100] = {"Mastercard", "Visa", "Discover", 
		"American Express"};
		// print message
		printf("Card type(Mastercard = 1, Visa = 2, ");
		printf("Discover = 3, American Express = 4): ");
		// read input
		scanf("%d", &card);
		// print message
		printf("Paid by: Credit Card (%s)\n", cardArr[card - 1]);
		// create fee
		double fee;
		// calculate fee
		fee = 0.02 * totalCost;
		// print message
		printf("Service Fee: %.2lf\n", fee);
		printf("Paid amount: %.2lf\n", (totalCost + fee));
		printf("Change = 0.00\n");
	}
	// if contactless payment
	else if(method == 'q')
	{
		// initialize type
		int phone;
		// create types
		char phoneArr[2][100] = {"Google Wallet","Apple Pay"};
		// print message
		printf("Payment method(Google Wallet = 1, Apple Pay = 2): ");
		// read input
		scanf("%d", &phone);
		// print message
		printf("Paid by: Contactless Payment (%s)\n", phoneArr[phone - 1]);
		// initialize fee
		double fee;
		// calculate fee
		fee = 0.01 * totalCost;
		// print message
		printf("Service Fee: %.2lf\n", fee);
		printf("Paid amount: %.2lf\n", (fee + totalCost));
		printf("Change = 0.00\n");
	}
	// else
	else
	{
		// print message
		printf("error");
		// return false
		return false;
	}
	// return true
	return true;



}