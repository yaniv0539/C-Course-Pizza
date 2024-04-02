// Yaniv Zamir
// 206593444

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>

#define BasicPLen 40 // Basic pizza length
#define BasicPWidth 50 // Basic pizza width
#define BasicPPrice 70.0// Basic pizza price
#define OlivesPrice 10 // Standard price for olives on whole pizza
#define MushroomsPrice 12 // Standard price for mushrooms on whole pizza
#define TomatoesPrice 9 // Standard price for mushrooms on whole pizza
#define PineapplePrice 14 // Standard price for mushrooms on whole pizza
#define RegularPrice 0 // Price for regular dough
#define VeganPrice 5 // Price for vagen dough
#define WholeWheatPrice 3 // Price for whole wheat dough
#define GlutenFreePrice 4 // Price for gluten free dough
#define MaxIDdigits 9 // Maximum ID digits

typedef struct Pizza {
	int length; // Pizza length (cm)
	int width; // Pizza width (cm)
	char doughType; // Dough type ('r'/'v'/'w'/'f')
	double olives; // Olives amount (0/1/0.5/0.25)
	double mushrooms; // Mushrooms amount (0/1/0.5/0.25)
	double tomatoes; // Tomatoes amount (0/1/0.5/0.25)
	double pineapple; // Pineapple amount (0/1/0.5/0.25)
	char q1; // Topping type on first quarter ('O'/'M'/'T'/'P')
	char q2; // Topping type on second quarter ('O'/'M'/'T'/'P')
	char q3; // Topping type on third quarter ('O'/'M'/'T'/'P')
	char q4; // Topping type on fourth quarter ('O'/'M'/'T'/'P')
	double sumToppings; // Sum Topping ratio
	double price; // Pizza price (without tax)
	double ratio; // Ratio between this pizza and basic pizza
} PIZZA;

int getIDNumber();
bool validIDLen(int long id);
bool checkDigit(int long id);
void printMenu();
int getNumOfPizzas();
PIZZA getPizzaDimensions();
PIZZA getDoughType(PIZZA pizza);
PIZZA getToppings(PIZZA pizza);
PIZZA fullPizza(PIZZA pizza, char c, double ratio);
PIZZA addTopping(PIZZA pizza, char c);
double switchChoice(double userChoice);
void printPizzaDetails(PIZZA pizza, int i);
void printPizza(PIZZA pizza);
void firstAndLastRow(PIZZA pizza);
int getDelivery();
void getPayment(int totalPrice);

// MTA-Pizza Program
void main() {

	int long id;
	int numOfPizzas;
	int delivery; // 1 - Delivery. 0 - Pick-up.
	int totalPriceAT; // Total price after tax
	double totalPriceBT = 0; // Total price before tax
	
	// Welcome message
	printf("Welcome to MTA-Pizza! \n\n"

		"*****\n"
		" ***\n"
		"  *  \n\n");


	id = getIDNumber(); // Customer ID
	printMenu();
	numOfPizzas = getNumOfPizzas(); // Number of Pizzas the customer orders

	// Loop for each pizza...
	for (int i = 1; i <= numOfPizzas; i++)
	{
		printf("\n*************************************************\n"
			"Pizza #%d\n\n", i
		);

		PIZZA p = getPizzaDimensions();
		
		p = getDoughType(p);

		p = getToppings(p);

		printPizzaDetails(p, i);

		// Add pizza price to total price (without tax)
		totalPriceBT += p.price;
	}

	printf("\n\n*************************************************\n");

	delivery = getDelivery();

	// Add delivery price (if needed) to total price (without tax)
	totalPriceBT += delivery * 15;

	// Calculate total price with tax
	totalPriceAT = (int)(totalPriceBT * 1.17);

	// Order summary
	printf("\nYour order details:\n");
	printf("*******************\n");
	printf("ID number: %09ld\n", id);
	printf("Number of pizzas: %d\n", numOfPizzas);
	delivery ? printf("Delivery\n") : printf("Pick-up\n");
	printf("Total price: %.2lf\n", totalPriceBT);
	printf("Total price with tax (rounded down): %d\n\n", totalPriceAT);

	getPayment(totalPriceAT);

	printf("Thank you for your order!\n");
}

// Get ID from User, Check if validate and return currect ID 
int getIDNumber()
{
	int long id;

	printf("Please enter your ID number:\n");
	scanf("%ld", &id);
	
	while (!(validIDLen(id) && checkDigit(id)))
	{
		printf("Please enter your ID number:\n");
		scanf("%ld", &id);
	}
	return id;
}

// Check if the ID Length valid
bool validIDLen(int long id)
{
	int num = 1;
	
	for (int i = 1; i <= MaxIDdigits; i++)
		num *= 10;

	if (id < num && id > 0)
		return true;

	printf("Invalid ID number! Try again\n");
	return false;
}

// Check the ID "check digit"
bool checkDigit(int long id) 
{
	int num;
	int sum = 0;
	bool even = true;

	int checkDig = id % 10;
	id /= 10;
	
	while (id != 0)
	{
		num = id % 10;
		if (even)
		{
			num *= 2;
			if (num >= 10)
				num = 1 + (num % 10);
		}
		
		sum += num;
		even = !even;
		id /= 10;
		
	}

	if ((10 - (sum % 10)) == checkDig)
		return true;

	printf("Invalid check digit! Try again.\n");
	return false;
}

// Present the Menu
void printMenu() {
	// MTA-Pizza's menu
	printf("\nOur menu:\n"
		"*********\n"
		"Basic pizza: %.2lf NIS for %dx%d size pizza\n\n"

		"Toppings for basic size pizza:\n"
		"Olives: %d NIS\n"
		"Mushrooms: %d NIS\n"
		"Tomatoes: 9 NIS\n"
		"Pineapple: 14 NIS\n\n"

		"Dough type for basic size pizza:\n"
		"Regular: %d NIS\n"
		"Vegan: %d NIS\n"
		"Whole wheat: %d NIS\n"
		"Gluten free: %d NIS\n\n"

		, BasicPPrice, BasicPLen, BasicPWidth
		, OlivesPrice, MushroomsPrice
		, RegularPrice, VeganPrice, WholeWheatPrice, GlutenFreePrice
	);
}

// Check the input - number of pizzas - and return the valid number
int getNumOfPizzas()
{
	int numOfPizzas;

	// Gets how many pizzas the customer wants
	printf("How many pizzas would you like to order? ");
	scanf("%d", &numOfPizzas);

	while (numOfPizzas < 1)
	{
		printf("\nInvalid choice! Try again.\n");
		printf("How many pizzas would you like to order? ");
		scanf("%d", &numOfPizzas);
	}
	return numOfPizzas;
}

// Create Pizza by the dimensions the user entered and return it
PIZZA getPizzaDimensions()
{
	PIZZA p;
	p.price = 0;

	// Get pizza's length
	printf("Please enter your pizza's length (cm): ");
	scanf("%d", &p.length);

	// Check if the length valid
	while (p.length % 2 == 1 || p.length > 40 || p.length < 10)
	{
		printf("Invalid length! Try again.\n");
		printf("Please enter your pizza's length (cm): ");
		scanf("%d", &p.length);
	}

	// Get pizza's width
	printf("\nPlease enter your pizza's width (cm): ");
	scanf("%d", &p.width);

	// Check if the width valid
	while (p.width % 2 == 1 || p.width > 80 || p.width < 10)
	{
		printf("\nInvalid width! Try again.\n\n");
		printf("Please enter your pizza's width (cm): ");
		scanf("%d", &p.width);
	}

	// Calculate pizza's ratio
	p.ratio = (double)(p.length * p.width) / (BasicPLen * BasicPWidth);

	// Calculate pizza's starting price by ratio and add it to pizza's price
	p.price += (p.ratio * BasicPPrice);

	return p;
}

// Get the dough type and return pizza with it
PIZZA getDoughType(PIZZA pizza)
{
	bool validDough = false;

	while (!validDough)
	{
		// Pizza's dough
		printf("\nPlease enter the pizza's dough type:\n"
			"r - for regular\n"
			"v - for vegan\n"
			"w - for whole wheat\n"
			"f - for gluten-free\n"
		);
		scanf(" %c", &pizza.doughType);

		// Calculate (dough price * pizza's ratio), and add it to pizza's price
		switch (pizza.doughType)
		{
			case 'r':
			{
				pizza.price += (RegularPrice * pizza.ratio);
				validDough = true;
				break;
			}
			case 'v':
			{
				pizza.price += (VeganPrice * pizza.ratio);
				validDough = true;
				break;
			}
			case 'w':
			{
				pizza.price += (WholeWheatPrice * pizza.ratio);
				validDough = true;
				break;
			}
			case 'f':
			{
				pizza.price += (GlutenFreePrice * pizza.ratio);
				validDough = true;
				break;
			}
			default:
			{
				printf("\nInvalid choice! Try again.\n");
				break;
			}
		}
	}
	return pizza;
}

// Get the toppings and return pizza with them
PIZZA getToppings(PIZZA pizza)
{
	pizza.sumToppings = 0;

	printf("Please choose the toppings:\n\n");

	printf("Olives (choose 0-3):\n");
	pizza = addTopping(pizza, 'O'); // Olives ratio on pizza
	pizza.price += pizza.ratio * (pizza.olives * OlivesPrice);

	if (pizza.sumToppings < 1)
	{
		printf("Mushrooms (choose 0-3):\n");
		pizza = addTopping(pizza, 'M'); // Mushrooms ratio on pizza
		pizza.price += pizza.ratio * (pizza.mushrooms * MushroomsPrice);

		if (pizza.sumToppings < 1)
		{
			printf("Tomatos (choose 0-3):\n");
			pizza = addTopping(pizza, 'T'); // Tomatos ratio on pizza
			pizza.price += pizza.ratio * (pizza.tomatoes * TomatoesPrice);
			
			if (pizza.sumToppings < 1)
			{
				printf("Pineapple (choose 0-3):\n");
				pizza = addTopping(pizza, 'P'); // Pineapple ratio on pizza
				pizza.price += pizza.ratio * (pizza.pineapple * PineapplePrice);
			}
		}
	}

	if (pizza.sumToppings != 1)
	{
		pizza = fullPizza(pizza, ' ', 1 - pizza.sumToppings);
	}
	
	return pizza;
}

// Add specific topping and return the pizza with the topping
PIZZA addTopping(PIZZA pizza, char c)
{
	double ratio = -1;
	while (ratio == -1)
	{
		printf("0. None\n"
			"1. Whole pizza\n"
			"2. Half pizza\n"
			"3. Quarter pizza\n"
		);
		scanf("%lf", &ratio);
		ratio = switchChoice((int)ratio);

		if (ratio == -1)
			printf("Invalid choice! Try again.\n");
		
		else if (pizza.sumToppings + ratio > 1)
		{
			ratio = -1;
			printf("You have exceeded the maximum amount of toppings allowed on one pizza! Try again.\n");
		}
	}

	switch (c)
		{
			case 'O':
			{
				pizza.olives = ratio;
				break;
			}
			case 'M': 
			{
				pizza.mushrooms = ratio;
				break;
			}	
			case 'T':
			{
				pizza.tomatoes = ratio;
				break;
			}
			case 'P':
			{	
				pizza.pineapple = ratio;
				break;
			}
			default:
				break;
		}

	return fullPizza(pizza, c, ratio);
}

// Switch user choice to the right topping ratio and return it
double switchChoice(double userChoice)
{
	// Switch the customer choice to actual topping ratio (0/0.25/0.5/1)
	switch ((int)userChoice)
	{
		case 0: {
			userChoice = 0;
			break;
		}
		case 1: {
			userChoice = 1;
			break;
		}
		case 2: {
			userChoice = 0.5;
			break;
		}
		case 3: {
			userChoice = 0.25;
			break;
		}
		default: {
			userChoice = -1;
			break;
		}
	}

	return userChoice;
}

// Full the pizza quarters with the right toppings and return the pizza
PIZZA fullPizza(PIZZA pizza, char c, double ratio)
{
	if (pizza.sumToppings == 0 && ratio > 0)
	{
		pizza.q1 = c;
		ratio -= 0.25;
		pizza.sumToppings += 0.25;
	}
	if (pizza.sumToppings == 0.25 && ratio > 0)
	{
		pizza.q2 = c;
		ratio -= 0.25;
		pizza.sumToppings += 0.25;
	}
	if (pizza.sumToppings == 0.5 && ratio > 0)
	{
		pizza.q3 = c;
		ratio -= 0.25;
		pizza.sumToppings += 0.25;
	}
	if (pizza.sumToppings == 0.75 && ratio > 0)
	{
		pizza.q4 = c;
		ratio -= 0.25;
		pizza.sumToppings += 0.25;
	}

	return pizza;
}

// Print the i'th pizza details
void printPizzaDetails(PIZZA pizza, int i) 
{
	// Pizza's summary
	printf("\n\nPizza #%d details:\n"
		"*******************\n"
		"Pizza size: %dx%d\n"
		"Pizza price (without tax): %.2lf\n"
		, i, pizza.length, pizza.width, pizza.price
	);

	printPizza(pizza);
}

// Print draw of the pizza
void printPizza(PIZZA pizza)
{
	firstAndLastRow(pizza);
	for (int i = 0; i < ((pizza.length - 2) / 2); i++)
	{
		printf("%c", pizza.doughType);
		for (int j = 0; j < ((pizza.width - 2) / 2); j++)
		{
			printf("%c", pizza.q4);
		}
		for (int j = 0; j < ((pizza.width - 2) / 2); j++)
		{
			printf("%c", pizza.q1);
		}
		printf("%c", pizza.doughType);
		printf("\n");
	}
	for (int i = 0; i < ((pizza.length - 2) / 2); i++)
	{
		printf("%c", pizza.doughType);
		for (int j = 0; j < ((pizza.width - 2) / 2); j++)
		{
			printf("%c", pizza.q3);
		}
		for (int j = 0; j < ((pizza.width - 2) / 2); j++)
		{
			printf("%c", pizza.q2);
		}
		printf("%c", pizza.doughType);
		printf("\n");
	}
	firstAndLastRow(pizza);
}

// Draw the first and last line of the draw
void firstAndLastRow(PIZZA pizza)
{
	for (int i = 0; i < pizza.width; i++)
	{
		printf("%c", pizza.doughType);
	}
	printf("\n");
}

// Check the delivery input - return 0 or 1
int getDelivery() {
	int delivery;

	printf("Do you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up: ");
	scanf("%d", &delivery);

	while (!(delivery == 0 || delivery == 1))
	{
		printf("Invalid choice! Try again.");
		printf("Do you want delivery for the price of 15 NIS? Enter 1 for delivery or 0 for pick-up: ");
		scanf("%d", &delivery);
	}
	return delivery;
}

// Ask payment and give back change 
void getPayment(int totalPrice)
{
	int payment;
	// Requires payment while there's still remaining balance
	while (totalPrice > 0)
	{
		printf("Please enter your payment: ");
		scanf("%d", &payment);

		totalPrice -= payment;

		if (totalPrice > 0)
			printf("Your remaining balance is: %d\n\n", totalPrice);
	}

	// Calulate the change after the bill (give the minimum coins as much as possible)
	if (totalPrice != 0)
	{
		totalPrice *= -1;

		printf("\nYour change is %d NIS using:\n", totalPrice);
		if (totalPrice / 10 != 0)
			printf("%d coin(s) of ten\n", totalPrice / 10);
		totalPrice %= 10;
		if (totalPrice / 5 != 0)
			printf("%d coin(s) of five\n", totalPrice / 5);
		totalPrice %= 5;
		if (totalPrice / 2 != 0)
			printf("%d coin(s) of two\n", totalPrice / 2);
		totalPrice %= 2;
		if (totalPrice != 0)
			printf("%d coin(s) of one\n", totalPrice);
		totalPrice = 0;
	}
}