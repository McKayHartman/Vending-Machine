// Guards
#ifndef VENDING_LIB
#define VENDING_LIB

// Header files
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

// Constants
#define ABORT -1
#define MAX_NUM_PRODUCTS 100


extern const int *ProductLabels[MAX_NUM_PRODUCTS];
// constants
enum ProductType
{
	CHOCOLATE_BAR,
	CHIPS,
	CHEWING_GUM,
	PEPSI,
	NUM_PRODUCTS
};
enum Menu
{
	CANCEL,
	CHECKOUT,
	CONTINUE
};

enum Payment
{
	CASH,
	CREDIT,
	CONTACTLESS
};

enum CreditCard
{
	MASTERCARD,
	VISA,
	DISCOVER,
	AMERICAN_EXPRESS
};

enum Contactless
{
	GOOGLE_WALLET,
	APPLE_PAY
};

struct Product
{
	enum ProductType food;
	double price;
	double quantityInStock;
};

struct CartItem
{
	struct Product prod;
};

struct ShoppingCart
{
	int cart[MAX_NUM_PRODUCTS];
};

// Function prototypes

/**
 * Name: stockMachine
 * Process: fills up an array with products
 * Function input/parameters: array
 * Function output/parameters: array    
 * Function output/returned: none
 * Dependencies: none
 **/
void stockMachine(double array[][3]);

/**
 * Name: displayProducts
 * Process: displays the availible products in the vending machine
 * Function input/parameters: array
 * Function output/parameters: none    
 * Function output/returned: none
 * Dependencies: none
 **/
void displayProducts(double array[][3]);

/**
 * Name: getProduct
 * Process: reads a product from user input
 * Function input/parameters: array
 * Function output/parameters: none    
 * Function output/returned: code
 * Dependencies: none
 **/
int getProduct();

/**
 * Name: getQuantity
 * Process: reads a quantity from the and determines if the product
 * 		is availible in the requested quantity
 * Function input/parameters: code, quantity
 * Function output/parameters: none    
 * Function output/returned: quantity
 * Dependencies: none
 **/
int getQuantity(int Code, double array[][3]);

/**
 * Name: selectItem
 * Process: builds and returns a variable of type struct cartItem 
 * Function input/parameters: code, quantity, array
 * Function output/parameters: none    
 * Function output/returned: struct
 * Dependencies: none cartItem
 **/
struct CartItem selectItem(int code, double array[][3], int quantity);

/**
 * Name: addToCart
 * Process: update the shopping cart with the new cart item
 * Function input/parameters: array, code
 * Function output/parameters: array
 * Function output/returned: true or false
 * Dependencies: cartItem
 **/
bool addToCart(struct CartItem cart[MAX_NUM_PRODUCTS], struct CartItem a);

/**
 * Name: cancelPurchase
 * Process: empties the shopping cart and returns the selected items
 * 		to the shelf by making them availible
 * Function input/parameters: cart, array
 * Function output/parameters: cart, array
 * Function output/returned: none
 * Dependencies: none
 **/
void cancelPurchase(double array[][3], struct CartItem cart[MAX_NUM_PRODUCTS], int numOfProducts);

/**
 * Name: generateBill
 * Process: prints the bill
 * Function input/parameters: cart
 * Function output/parameters: cart
 * Function output/returned: none
 * Dependencies: none
 **/
double generateBill(struct CartItem cart[MAX_NUM_PRODUCTS], double array[4][3], int numOfProducts);

/**
 * Name: pay
 * Process: proceeds with payment and generates the receipt
 * Function input/parameters: cart
 * Function output/parameters: cart
 * Function output/returned: none
 * Dependencies: none
 **/
bool pay(struct CartItem cart[MAX_NUM_PRODUCTS], int numOfProducts, double array[][3]);

#endif
