#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <Windows.h>


//Structures
struct SUPPLIERSTRUCT
{

	int supplierID;
	char supplierName[31];
	char supplierTeleNo[14];
	char supplierEmail[254];
	char supplierContact[25];

};

struct PRODUCTSTRUCT
{

	char productID[9];
	char productDesc[50];
	char productType;
	float unitSalesPrice, unitCostPrice;
	int productQuantity, productStockLimit;

};

struct ORDERSTRUCT
{

	int orderID, orderAmount, houseNum;
	char dateCreated[10];
	char dateModified[10];
	char orderProductID[9];
	char postCode[8];
	float orderTotal;

};


//Prototypes
int FileToSupplierArray(struct SUPPLIERSTRUCT *); //Written by Michael McCormick
int FileToProductArray(struct PRODUCTSTRUCT *); //Written by Michael McCormick
int FileToOrderArray(struct ORDERSTRUCT *); //Written by Michael McCormick
void SupplierArrayToFile(int numSuppliers, struct SUPPLIERSTRUCT *); //Written by Michael McCormick
void ProductArrayToFile(int numCourses, struct PRODUCTSTRUCT *); //Written by Michael McCormick
void OrderArrayToFile(int numOrders, struct ORDERSTRUCT *); //Written by Michael McCormick
int ResetSupplierFile(struct SUPPLIERSTRUCT *); //Written by Michael McCormick
int ResetProductFile(struct PRODUCTSTRUCT *); //Written by Michael McCormick
int ResetOrderFile(struct ORDERSTRUCT *); //Written by Michael McCormick
void DrawMainMenu(int numSuppliers, int numProducts, int numOrders, struct SUPPLIERSTRUCT *, struct PRODUCTSTRUCT *, struct ORDERSTRUCT *); //Written by Michael McCormick
char MainMenuChoice(); //Written by Michael McCormick
void DrawSupplierMenu(int numSuppliers, int numProducts, int numOrders, struct SUPPLIERSTRUCT *, struct PRODUCTSTRUCT *, struct ORDERSTRUCT *);  //Written by Dominic Lewis
char SupplierMenuChoice();  //Written by Dominic Lewis
void DrawProductMenu(int numProducts, int numSuppliers, int numOrders, struct PRODUCTSTRUCT *, struct SUPPLIERSTRUCT *, struct ORDERSTRUCT *);  //Written by Dominic Lewis
char ProductMenuChoice();  //Written by Dominic Lewis
void DrawOrderMenu(int numOrders, int numProducts, int numSuppliers, struct ORDERSTRUCT *, struct PRODUCTSTRUCT *, struct SUPPLIERSTRUCT *); //Written by Michael McCormick
char OrderMenuChoice(); //Written by Michael McCormick
int AddSupplier(int numSuppliers, struct SUPPLIERSTRUCT *); //Written by Adam Stock
void EnterSupplier(int numSuppliers, struct SUPPLIERSTRUCT *); //Written by Adam Stock
int AddProduct(int numProducts, struct PRODUCTSTRUCT *); //Written by Adam Stock
void EnterProduct(int numProducts, struct PRODUCTSTRUCT *); //Written by Adam Stock
int AddOrder(int numOrders, int numProducts, struct ORDERSTRUCT *, struct PRODUCTSTRUCT *products); //Written by Adam Stock
void EnterOrder(int numOrders, int numProducts, struct ORDERSTRUCT *, struct PRODUCTSTRUCT *); //Written by Adam Stock
void ShowAllSuppliers(int numSuppliers, struct SUPPLIERSTRUCT *); //Written by Adam Stock
void ShowOneSupplier(struct SUPPLIERSTRUCT suppliers); //Written by Adam Stock
void ShowAllProducts(int numProducts, struct PRODUCTSTRUCT *); //Written by Adam Stock
void ShowOneProduct(struct PRODUCTSTRUCT products); //Written by Adam Stock
void ShowAllOrders(int numOrders, int numProducts, struct ORDERSTRUCT *, struct PRODUCTSTRUCT *); //Written by Adam Stock
void ShowOneOrder(struct ORDERSTRUCT products); //Written by Adam Stock
void ShowProductID(int numProducts, struct PRODUCTSTRUCT *); //Written by Michael McCormick
float CalculateOrderTotal(int numProducts, int numOrders, struct PRODUCTSTRUCT *, struct ORDERSTRUCT *); //Written by Michael McCormick
int DeleteSupplier(int numSuppliers, struct SUPPLIERSTRUCT *); //Written by Michael McCormick
int DeleteProduct(int numProducts, struct PRODUCTSTRUCT *); //Written by Michael McCormick
int DeleteOrder(int numOrders, struct ORDERSTRUCT *); //Written by Michael McCormick
void EditSupplier(int numSuppliers, struct SUPPLIERSTRUCT *); //Written by Michael McCormick
void EditProduct(int numProducts, struct PRODUCTSTRUCT *); //Written by Michael McCormick
void EditOrder(int numOrders, int numProducts, struct ORDERSTRUCT *, struct PRODUCTSTRUCT *); //Written by Michael McCormick
void SupplierSearch(int numSuppliers, struct SUPPLIERSTRUCT *); //Written by Adam Stock
void ProductSearch(int numProducts, struct PRODUCTSTRUCT *); //Written by Adam Stock
void OrderSearch(int numOrders, struct ORDERSTRUCT *); //Written by Adam Stock
int ValidInt(int min, int max); //Written by Dominic Lewis
float ValidFloat(float min, float max); //Written by Dominic Lewis
char *ValidStringLength(int MinLength, int MaxLength, char *String1); //Written by Dominic Lewis
void GetUserEmail(char* userEmail); //Written by Dominic Lewis
int ValidSupplierID(int min, int max, int numSuppliers, struct SUPPLIERSTRUCT *); //Written by Dominic Lewis
char *ValidProductID(int MinLength, int MaxLength, char *String1, int numProducts, struct PRODUCTSTRUCT *); //Written by Michael McCormick
char *ValidOrderProductID(int numProducts, struct PRODUCTSTRUCT *, int MinLength, int MaxLength, char *String1); //Written by Michael McCormick
char *ValidPostCode(int MinLength, int MaxLength, char *String1); //Written by Michael McCormick
char ValidType(); //Written by Dominic Lewis 
void ValidTeleNo(char* numberStoredHere); //Written by Dominic Lewis
int PlusNumValid(char* userEntry); //Written by Dominic Lewis
int NonPlusValid(char* userEntry); //Written by Dominic Lewis
void QuitProgram(int numSuppliers, int numProducts, int numOrders, struct SUPPLIERSTRUCT *, struct PRODUCTSTRUCT *, struct ORDERSTRUCT *);  //Written by Michael McCormick

//Global Constants
#define TRUE 1
#define FALSE 0
#define POUNDSIGN 156
#define CLEARSCREEN system ("cls")
#define SUPPLIERFN "Suppliers"
#define PRODUCTFN "Products"
#define ORDERFN "Orders"
#define MINSUPPLIERID 101
#define MAXSUPPLIERID 149
#define MAXSUPPLIERAMOUNT 12
#define MAXPRODUCTAMOUNT 100
#define MAXORDERAMOUNT 999


void main() {

	//Defines sizes of structures
	struct SUPPLIERSTRUCT suppliers[MAXSUPPLIERAMOUNT];
	struct PRODUCTSTRUCT products[MAXPRODUCTAMOUNT];
	struct ORDERSTRUCT orders[MAXORDERAMOUNT];
	//Sets amount of records held in all structures to 0
	int numSuppliers = 0;
	int numProducts = 0;
	int numOrders = 0;

	//Loads records from files into structures
	numSuppliers = FileToSupplierArray(suppliers);
	numProducts = FileToProductArray(products);
	numOrders = FileToOrderArray(orders);

	CLEARSCREEN;

	//Displays the main menu
	DrawMainMenu(numSuppliers, numProducts, numOrders, suppliers, products, orders);

	Sleep(1000);

	//Loads records from structures into files
	SupplierArrayToFile(numSuppliers, suppliers);
	ProductArrayToFile(numProducts, products);
	OrderArrayToFile(numOrders, orders);

	system("pause");
	exit(0);

}

void DrawMainMenu(int numSuppliers, int numProducts, int numOrders, struct SUPPLIERSTRUCT *suppliers, struct PRODUCTSTRUCT *products, struct ORDERSTRUCT *orders) {

	char menuchoice, reply;

	do
	{

		//Displays main menu UI and gets a choice from the user
		menuchoice = MainMenuChoice();

		switch (menuchoice)
		{

			//Opens Supplier Submenu
		case 'S': CLEARSCREEN;
			DrawSupplierMenu(numSuppliers, numProducts, numOrders, suppliers, products, orders);
			break;

			//Opens Product Submenu
		case 'P': CLEARSCREEN;
			DrawProductMenu(numProducts, numSuppliers, numOrders, products, suppliers, orders);
			break;

			//Opens Order Submenu
		case 'O': CLEARSCREEN;
			DrawOrderMenu(numOrders, numProducts, numSuppliers, orders, products, suppliers);
			break;

			//Save Files
		case 'B':
			SupplierArrayToFile(numSuppliers, suppliers);
			ProductArrayToFile(numProducts, products);
			OrderArrayToFile(numOrders, orders);

			Sleep(300);

			CLEARSCREEN;
			printf("The files have been saved.\n\n");
			break;

			//Reset Files
		case 'R':
			printf("Are you sure you would like to reset the files for this system?[Y/N]\n");
			scanf_s("%c", &reply, 1);
			fflush(stdin);
			reply = toupper(reply);

			if (reply == 'Y')
			{
				numSuppliers = ResetSupplierFile(suppliers);
				numProducts = ResetProductFile(products);
				numOrders = ResetOrderFile(orders);
				CLEARSCREEN;
				printf("The files have been reset.\n\n");
			}

			else if (reply == 'N')
			{
				CLEARSCREEN;
				printf("The files will not be reset.\n\n");
			}
			break;

			//End the program
		case 'Q': QuitProgram(numSuppliers, numProducts, numOrders, suppliers, products, orders);
			break;
		}

	} while (menuchoice != 'Q');

}

//Get Main Menu Choice
char MainMenuChoice()
{

	char choice;

	do
	{
		//Displays main menu interface
		printf("	Hardwicke's DIY Supplies - Product System\n--------------------------------------\nChoose from the following options:\nS - Supplier Options Menu\nP - Product Options Menu\nO - Order Options Menu\n\nB - Save Files\nR - Reset Files\n\nQ - Save & Quit Program\n\n");

		scanf_s("%c", &choice, 1);
		fflush(stdin);
		choice = toupper(choice);

		//Gets users choice
		if ((choice != 'S') && (choice != 'P') && (choice != 'O') && (choice != 'B') && (choice != 'R') && (choice != 'Q'))
		{
			CLEARSCREEN;
			printf("Error. The character you entered is not assigned to a function. Please choose one from the options listed below.\n\n");
		}

	} while ((choice != 'S') && (choice != 'P') && (choice != 'O') && (choice != 'B') && (choice != 'R') && (choice != 'Q'));

	return choice;
}

//This function draws the supplier sub menu
void DrawSupplierMenu(int numSuppliers, int numProducts, int numOrders, struct SUPPLIERSTRUCT *suppliers, struct PRODUCTSTRUCT *products, struct ORDERSTRUCT *orders) {

	char menuchoice;

	do
	{

		//Displays supplier menu UI and gets a users choice
		menuchoice = SupplierMenuChoice();

		switch (menuchoice)
		{

			//Add a new supplier
		case 'A': numSuppliers = AddSupplier(numSuppliers, suppliers);
			break;

			//Displays all stored suppliers
		case 'D': ShowAllSuppliers(numSuppliers, suppliers);
			break;

			//Edit a supplier
		case 'E': EditSupplier(numSuppliers, suppliers);
			break;

			//Delete a supplier
		case 'X': numSuppliers = DeleteSupplier(numSuppliers, suppliers);
			break;

			//Search for a supplier
		case 'S': SupplierSearch(numSuppliers, suppliers);
			break;

			//Returns user to main menu
		case 'B': CLEARSCREEN;
			DrawMainMenu(numSuppliers, numProducts, numOrders, suppliers, products, orders);
			break;

			//End the program
		case 'Q': QuitProgram(numSuppliers, numProducts, numOrders, suppliers, products, orders);
			break;
		}
		//Loops while Q is not entered. 
	} while (menuchoice != 'Q');
}

//Get Supplier Menu Choice
char SupplierMenuChoice() {

	char choice;
	//Post conditioned loop to ensure validation
	do {

		//Displays the supplier menu interface
		printf("	Hardwicke's DIY Supplies - Product System\n--------------------------------------\nChoose from the following options:\nA - Add a new Supplier\nD - Display all Currently Stored Suppliers\nS - Search for a Supplier\nE - Edit a Supplier\nX - Delete a Supplier\n\nB - Return to the Main Menu\n\nQ - Save & Quit Program\n\n");

		//Gets user input
		scanf_s("%c", &choice, 1);
		fflush(stdin);
		choice = toupper(choice);

		//Validates user entry
		if ((choice != 'A') && (choice != 'D') && (choice != 'X') && (choice != 'E') && (choice != 'S') && (choice != 'B') && (choice != 'Q'))
		{
			CLEARSCREEN;
			printf("Error. The character you entered is not assigned to a function. Please choose one from the options listed below.\n\n");
		}
		//Loops whille choice is not one of these entries 
	} while ((choice != 'A') && (choice != 'D') && (choice != 'X') && (choice != 'E') && (choice != 'S') && (choice != 'B') && (choice != 'Q'));
	//Returns user entry
	return choice;
}

//This function draws the product sub menu
void DrawProductMenu(int numProducts, int numSuppliers, int numOrders, struct PRODUCTSTRUCT *products, struct SUPPLIERSTRUCT *suppliers, struct ORDERSTRUCT *orders) {

	char menuchoice;

	//Loops to ensure user does not accidently quit out of menu
	do
	{
		//Set menuchoice to whatever ProductMenuchoice returns, this function returns the validated option which will be used in the switch statement below 
		menuchoice = ProductMenuChoice();
		//Selects the relevant function to call based on the value stored inside menuchoice
		switch (menuchoice)
		{

			//Add a new product
		case 'A': numProducts = AddProduct(numProducts, products);
			break;

			//Displays all stored products
		case 'D': ShowAllProducts(numProducts, products);
			break;

			//Edit a product
		case 'E': EditProduct(numProducts, products);
			break;

			//Delete a product
		case 'X': numProducts = DeleteProduct(numProducts, products);
			break;

			//Search for a product
		case 'S': ProductSearch(numProducts, products);
			break;

			//Returns user to main menu
		case 'B': CLEARSCREEN;
			DrawMainMenu(numSuppliers, numProducts, numOrders, suppliers, products, orders);
			break;

			//End the program
		case 'Q': QuitProgram(numSuppliers, numProducts, numOrders, suppliers, products, orders);
			break;
		}

		//Loops while the quit entry isn't the quit value.
	} while (menuchoice != 'Q');
}

//Get users Product Menu Choice
char ProductMenuChoice() {

	char choice;

	//Loops
	do {

		//Displays product menu interface
		printf("	Hardwicke's DIY Supplies - Product System\n--------------------------------------\nChoose from the following options:\nA - Add a new Product\nD - Display all Currently Stored Products\nS - Search for a Product\nE - Edit a Product\nX - Delete a Product\n\nB - Return to the Main Menu\n\nQ - Save & Quit Program\n\n");

		scanf_s("%c", &choice, 1);
		fflush(stdin);
		choice = toupper(choice);

		//Gets users choice
		if ((choice != 'A') && (choice != 'D') && (choice != 'X') && (choice != 'E') && (choice != 'S') && (choice != 'B') && (choice != 'Q'))
		{
			CLEARSCREEN;
			printf("Error. The character you entered is not assigned to a function. Please choose one from the options listed below.\n\n");
		}
		//Loops while entry is not correct 
	} while ((choice != 'A') && (choice != 'D') && (choice != 'X') && (choice != 'E') && (choice != 'S') && (choice != 'B') && (choice != 'Q'));

	return choice;
}

//This function draws the Order sub menu
void DrawOrderMenu(int numOrders, int numProducts, int numSuppliers, struct ORDERSTRUCT *orders, struct PRODUCTSTRUCT *products, struct SUPPLIERSTRUCT *suppliers) {

	char menuchoice;

	do
	{

		menuchoice = OrderMenuChoice();

		switch (menuchoice)
		{

			//Add a new Order
		case 'A': numOrders = AddOrder(numOrders, numProducts, orders, products);
			break;

			//Displays all stored Orders
		case 'D': ShowAllOrders(numOrders, numProducts, orders, products);
			break;

			//Edit a Order
		case 'E': EditOrder(numOrders, numProducts, orders, products);
			break;

			//Delete a Order
		case 'X': numOrders = DeleteOrder(numOrders, orders);
			break;

			//Search for a Order
		case 'S': OrderSearch(numOrders, orders);
			break;

			//Returns user to main menu
		case 'B': CLEARSCREEN;
			DrawMainMenu(numSuppliers, numProducts, numOrders, suppliers, products, orders);
			break;

			//End the program
		case 'Q': QuitProgram(numOrders, numProducts, numSuppliers, suppliers, products, orders);
			break;
		}

	} while (menuchoice != 'Q');
}

//Get users Order Menu Choice
char OrderMenuChoice() {

	char choice;

	do {

		//Displays order menu interface
		printf("	Hardwicke's DIY Supplies - Order System\n--------------------------------------\nChoose from the following options:\nA - Add a new Order\nD - Display all Currently Stored Orders\nS - Search for a Order\nE - Edit a Order\nX - Delete a Order\n\nB - Return to the Main Menu\n\nQ - Save & Quit Program\n\n");

		scanf_s("%c", &choice, 1);
		fflush(stdin);
		choice = toupper(choice);

		//Gets users choice
		if ((choice != 'A') && (choice != 'D') && (choice != 'X') && (choice != 'E') && (choice != 'S') && (choice != 'B') && (choice != 'Q'))
		{
			CLEARSCREEN;
			printf("Error. The character you entered is not assigned to a function. Please choose one from the options listed below.\n\n");
		}

	} while ((choice != 'A') && (choice != 'D') && (choice != 'X') && (choice != 'E') && (choice != 'S') && (choice != 'B') && (choice != 'Q'));

	return choice;
}

//Uses enter supplier to struct 
int AddSupplier(int numSuppliers, struct SUPPLIERSTRUCT *suppliers)
{
	//Add main fields for supplier to supplierstruct
	EnterSupplier(numSuppliers, suppliers);
	CLEARSCREEN;
	printf("New Supplier successfully added.\n\n");
	//Increment numebr of suppliers
	numSuppliers++;
	//Pass back number of suppliers 
	return numSuppliers;

}

//Works with addsupplier and validation to input data to struct 
void EnterSupplier(int numSuppliers, struct SUPPLIERSTRUCT *suppliers)
{
	//Add data to various fields in the struct with validation for each 
	printf("Please enter a supplier ID number between 101 and 149 : ");
	suppliers[numSuppliers].supplierID = ValidSupplierID(101, 149, numSuppliers, suppliers);

	printf("Please enter the suppliers company name[Max 30 Characters]:");
	strcpy_s(suppliers[numSuppliers].supplierName, 31, ValidStringLength(1, 30, suppliers[numSuppliers].supplierName));

	printf("Please enter the suppliers telephone number with a maximum of 12 numbers :");
	ValidTeleNo(&suppliers[numSuppliers].supplierTeleNo);

	printf("Please enter the suppliers Email address :");
	GetUserEmail(&suppliers[numSuppliers].supplierEmail);

	printf("Please enter the name of our contact at the supplier[Max 25 Characters]:");
	strcpy_s(suppliers[numSuppliers].supplierContact, 25, ValidStringLength(1, 25, suppliers[numSuppliers].supplierContact));
}

//Uses enterproduct to add to the struct 
int AddProduct(int numProducts, struct PRODUCTSTRUCT *products)
{
	//Enter product information into structures
	EnterProduct(numProducts, products);
	CLEARSCREEN;
	printf("The product was successfully added to the system.\n\n");
	//Increment number of products
	numProducts++;
	//return number of products 
	return numProducts;
}

//Uses addsupplier and validation to add correct data to struct 
void EnterProduct(int numProducts, struct PRODUCTSTRUCT *products)
{
	//Add data to product fields in struct including validation 
	printf("\nPlease enter a product code [3 letters followed by 5 numbers]: ");
	strcpy_s(products[numProducts].productID, 9, ValidProductID(1, 8, products[numProducts].productID, numProducts, products));

	printf("\nPlease enter a product description this can be up to 50 characters :");
	gets_s(products[numProducts].productDesc, 50);

	printf("\nPlease enter the product type -\n");
	products[numProducts].productType = ValidType();

	printf("\nPlease enter a retail price[%c1.99 - %c250.00]: ", POUNDSIGN, POUNDSIGN);
	products[numProducts].unitSalesPrice = ValidFloat(1.99, 250.00);

	printf("\nPlease enter a cost price[%c1.99 - %c200.00]: ", POUNDSIGN, POUNDSIGN);
	products[numProducts].unitCostPrice = ValidFloat(1.99, 200.00);

	printf("\nPlease enter a stock level[0-20]: ");
	products[numProducts].productQuantity = ValidInt(0, 20);

	printf("\nPlease enter a minimum stock level[5-15]: ");
	products[numProducts].productStockLimit = ValidInt(5, 15);

}

//Uses enter order to add orders to struct 
int AddOrder(int numOrders, int numProducts, struct ORDERSTRUCT *orders, struct PRODUCTSTRUCT *products)
{
	//Add main fields for Order to Orderstruct
	EnterOrder(numOrders, numProducts, orders, products);
	CLEARSCREEN;
	printf("The order has been sucessfully added to the system.\n\n");
	//Increment numebr of Orders
	numOrders++;
	//returns number of orders 
	return numOrders;

}

//Uses addorder and validation to add items to order struct 
void EnterOrder(int numOrders, int numProducts, struct ORDERSTRUCT *orders, struct PRODUCTSTRUCT *products)
{

	//Temporary store for postcode (see testing documentation for reasoning)
	char tempString[8];

	//gets time and adds to temporary string
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	//Add data to various fields in the struct with validation for each 
	printf("Please enter a Order ID number between 101 and 999 : ");
	orders[numOrders].orderID = ValidInt(101, 999);
	//Prints time string 
	printf("The date is:");
	printf("%d/%d/%d\n", str_t.wDay, str_t.wMonth, str_t.wYear);

	sprintf_s(orders[numOrders].dateCreated, 11, ("%d/%d/%d"), str_t.wDay, str_t.wMonth, str_t.wYear);

	strcpy_s(orders[numOrders].dateModified, 11, orders[numOrders].dateCreated);

	printf("Please enter a postcode for this order[No Spaces]:");
	strcpy_s(orders[numOrders].postCode, 8, ValidPostCode(5, 7, orders[numOrders].postCode));

	//Copies postcode into temp store
	strcpy_s(tempString, 8, orders[numOrders].postCode);

	printf("Please enter a house or building number :");
	orders[numOrders].houseNum = ValidInt(1, 2679);

	printf("Please enter the quantity of the product being ordered (1-999):");
	orders[numOrders].orderAmount = ValidInt(1, 999);
	//displays potential product ids for choice 
	ShowProductID(numProducts, products);

	printf("Please enter the the product code for the product being ordered[Chosen from the available products listed above]:");
	strcpy_s(orders[numOrders].orderProductID, 9, ValidOrderProductID(numProducts, products, 1, 8, orders[numOrders].orderProductID));

	//Retrieves postcode from temp store
	strcpy_s(orders[numOrders].postCode, 8, tempString);

	//calculates order total
	orders[numOrders].orderTotal = CalculateOrderTotal(numProducts, numOrders, products, orders);

}

//Displays all stored suppliers
void ShowAllSuppliers(int numSuppliers, struct SUPPLIERSTRUCT *suppliers)
{

	int i;

	CLEARSCREEN;

	printf("	Display all Suppliers\n--------------------------------------\n");
	//cycles and prints every supplier from 1 to numsuppliers
	for (i = 0; i < numSuppliers; i++)
	{
		ShowOneSupplier(suppliers[i]);
	}

	printf("\n");
	system("pause");
	CLEARSCREEN;

}

//Displays one supplier
void ShowOneSupplier(struct SUPPLIERSTRUCT suppliers)
{
	printf("SupplierID: %d\nSupplier Name: %s\nSupplier Telephone Number: %s\nSupplier Email: %s\nSupplier Contact Name: %s\n\n", suppliers.supplierID, suppliers.supplierName, suppliers.supplierTeleNo, suppliers.supplierEmail, suppliers.supplierContact);
}

//Displays all stored products
void ShowAllProducts(int numProducts, struct PRODUCTSTRUCT *products)
{

	int i;

	CLEARSCREEN;

	printf("	Display all Products\n--------------------------------------\n");
	//prints all products from 0 to numproducts
	for (i = 0; i < numProducts; i++)
	{
		ShowOneProduct(products[i]);
	}

	printf("\n");
	system("pause");
	CLEARSCREEN;

}

//Displays one product
void ShowOneProduct(struct PRODUCTSTRUCT products)
{
	printf("ProductID: %s\nProduct Description: %s\nProduct Type: %c\nUnit Sales Price: %c%1.2f\nUnit Cost Price: %c%1.2f\nProduct Quantity: %d\nProduct Stock Limit: %d\n\n", products.productID, products.productDesc, products.productType, POUNDSIGN, products.unitSalesPrice, POUNDSIGN, products.unitCostPrice, products.productQuantity, products.productStockLimit);
}


//Displays all stored orders
void ShowAllOrders(int numOrders, int numProducts, struct ORDERSTRUCT *orders, struct PRODUCTSTRUCT *products)
{

	int i;

	CLEARSCREEN;

	printf("	Display all Orders\n--------------------------------------\n");
	//prints all orders from 0 to numorders
	for (i = 0; i < numOrders; i++)
	{
		ShowOneOrder(orders[i]);
	}

}

//Displays one product
void ShowOneOrder(struct ORDERSTRUCT orders)
{
	printf("OrderID: %d\nDelivery House Number: %d\nDelivery Postcode: %s\nOrder Created On: %s\nOrder Last Modified On: %s\nOrder Quantity: %d\nOrder Total: %c%1.2f\n\n", orders.orderID, orders.houseNum, orders.postCode, orders.dateCreated, orders.dateModified, orders.orderAmount, POUNDSIGN, orders.orderTotal);
}

//Displays all stored product ID's
void ShowProductID(int numProducts, struct PRODUCTSTRUCT *products)
{
	int i;

	printf("	\n--All Stored Product ID's--\n");

	//Loops through all product records held in the structure and displays their ID's
	for (i = 0; i < numProducts; i++)
	{
		printf("- %s\n", products[i].productID);
		printf("\n\n");
	}

}

//Links the product with the order so the order total may be calculated
float CalculateOrderTotal(int numProducts, int numOrders, struct PRODUCTSTRUCT *products, struct ORDERSTRUCT *orders)
{

	int i;
	float orderTotal = 0.0;

	//Loops through all stored product records to find the one that associates with the entered Order Product ID
	for (i = 0; i < numProducts; i++)
	{

		int match = strcmp(orders[i].orderProductID, products[i].productID);

		//Calculates the order total if a match is found
		if (match == 0)
		{
			orderTotal = (products[i].unitSalesPrice * orders[i].orderAmount);
		}

	}

	return orderTotal;
}

//Delete a Supplier from the system
int DeleteSupplier(int numSuppliers, struct SUPPLIERSTRUCT *suppliers)
{

	int found, delID, i = 0;
	char reply;
	char emptyString[10] = "\0";

	printf("	Delete a Supplier\n--------------------------------------\n");

	//Gets the ID of the supplier record that the user wishes to delete
	printf("Please enter the Supplier ID that corresponds with the supplier you wish to delete.\n");
	delID = ValidInt(MINSUPPLIERID, MAXSUPPLIERID);

	found = FALSE;

	//Loops through all stored supplier records to find a match
	while ((i < numSuppliers) && (found == FALSE))
	{

		if (delID == suppliers[i].supplierID)
		{
			//Displays the found supplier record
			ShowOneSupplier(suppliers[i]);

			//Confirms if the user wants to delete the found supplier record
			printf("Are you sure you would like to delete this supplier from the system?[Y/N]\n");
			scanf_s("%c", &reply, 1);
			fflush(stdin);
			reply = toupper(reply);

			//Deletes supplier record if confirmed
			if (reply == 'Y')
			{

				suppliers[i].supplierID = 0;
				strcpy_s(suppliers[i].supplierName, 30, emptyString);
				strcpy_s(suppliers[i].supplierTeleNo, 12, emptyString);
				strcpy_s(suppliers[i].supplierEmail, 254, emptyString);
				strcpy_s(suppliers[i].supplierContact, 25, emptyString);

				numSuppliers--;

				CLEARSCREEN;
				printf("The supplier has been deleted.\n\n");
			}

			else if (reply == 'N')
			{
				CLEARSCREEN;
				printf("This supplier will not be deleted.\n\n");
			}

		}

		else
		{
			printf("The supplier was not found.\n");
		}

		i++;
	}

	return numSuppliers;

}

//Delete a Product from the system
int DeleteProduct(int numProducts, struct PRODUCTSTRUCT *products)
{

	int found, i = 0;
	char reply;
	char delID[21];
	char emptyString[10] = "\0";

	printf("	Delete a Product\n--------------------------------------\n");

	//Displays all stored product IDs
	ShowProductID(numProducts, products);

	//Gets user input
	printf("Please enter the Product ID that corresponds with the product you wish to delete from the list above: \n");
	strcpy_s(delID, 9, ValidOrderProductID(numProducts, products, 1, 8, delID));

	int match = strcmp(delID, products[i].productID);

	found = FALSE;

	//Loops through all stored products IDs to find a match
	while ((i < numProducts) && (found == FALSE))
	{

		if (match == 0)
		{
			//Displays found product record
			ShowOneProduct(products[i]);

			//Confirms if the user wants to delete the found record
			printf("Are you sure you would like to delete this product from the system?[Y/N]\n");
			scanf_s("%c", &reply, 1);
			fflush(stdin);
			reply = toupper(reply);

			if (reply == 'Y')
			{

				//Deletes product record if confirmed
				strcpy_s(products[i].productID, 8, emptyString);
				strcpy_s(products[i].productDesc, 50, emptyString);
				products[i].productType = "";
				products[i].unitSalesPrice = 0;
				products[i].unitCostPrice = 0;
				products[i].productQuantity = 0;
				products[i].productStockLimit = 0;

				numProducts--;

				CLEARSCREEN;
				printf("The product has been deleted.\n\n");
			}

			else if (reply == 'N')
			{
				CLEARSCREEN;
				printf("This product will not be deleted.\n\n");
			}

		}
		i++;
	}

	return numProducts;

}

//Delete an Order from the system
int DeleteOrder(int numOrders, struct ORDERSTRUCT *orders)
{

	int found, i = 0;
	char reply;
	int delID;
	char emptyString[10] = "\0";

	printf("	Delete an Order\n--------------------------------------\n");

	//Gets user input
	printf("Please enter the Order ID that corresponds with the order you wish to delete.\n");
	delID = ValidInt(1, 999);

	found = FALSE;

	//Loops through all stored order records
	while ((i < numOrders) && (found == FALSE))
	{

		if (delID == orders[i].orderID)
		{
			//Displays the found order record
			ShowOneOrder(orders[i]);

			//Confirms if the user wants to delete the found order
			printf("Are you sure you would like to delete this product from the system?[Y/N]\n");
			scanf_s("%c", &reply, 1);
			fflush(stdin);
			reply = toupper(reply);

			if (reply == 'Y')
			{

				//Deletes the found order record if confirmed
				strcpy_s(orders[i].orderProductID, 8, emptyString);
				strcpy_s(orders[i].dateCreated, 10, emptyString);
				strcpy_s(orders[i].dateModified, 10, emptyString);
				orders[i].orderID = 0;
				orders[i].orderAmount = 0;
				orders[i].orderTotal = 0.0;

				numOrders--;

				CLEARSCREEN;
				printf("The order has been deleted.\n\n");
			}

			else if (reply == 'N')
			{
				CLEARSCREEN;
				printf("This order will not be deleted.\n\n");
			}

		}
		i++;
	}

	return numOrders;

}

//Edit a specific suppliers information
void EditSupplier(int numSuppliers, struct SUPPLIERSTRUCT *suppliers)
{

	int editID;
	int found = FALSE;
	int i = 0;

	//Checks that there are suppliers to edit
	if (numSuppliers == 0)
	{
		printf("There are no products to find.\n\n");
	}

	else {

		printf("	Edit a Supplier\n--------------------------------------\n");

		//Gets user input
		printf("Enter the ID of the Supplier you want to edit (101 - 149): ");
		editID = ValidInt(MINSUPPLIERID, MAXSUPPLIERID);

		//Loops through all stored ID's until search entry is found
		while ((i < numSuppliers) && (found == FALSE))
		{
			if (editID == suppliers[i].supplierID)
			{
				//Display record found
				ShowOneSupplier(suppliers[i]);
				found = TRUE;

				//Allows user to change the suppliers previously stored information
				printf("Please enter the suppliers changed telephone number with a maximum of 12 numbers :");
				ValidTeleNo(&suppliers[i].supplierTeleNo);

				printf("Please enter the suppliers changed Email address :");
				GetUserEmail(&suppliers[i].supplierEmail);

				printf("Please enter the name of our changed contact at the supplier :");
				strcpy_s(suppliers[i].supplierContact, 25, ValidStringLength(1, 25, suppliers[i].supplierContact));

				numSuppliers = i;

				CLEARSCREEN;
				//Displays the updated record
				printf("The record has been updated.\n\n");

				ShowOneSupplier(suppliers[i]);
			}

			else
			{
				CLEARSCREEN;
				printf("Supplier not found.\n");
			}

			i++;
		}

	}
}

//Edit a specific products information
void EditProduct(int numProducts, struct PRODUCTSTRUCT *products)
{

	char editID[21];
	int found = FALSE;
	int i = 0;

	//Checks that there are product records to edit
	if (numProducts == 0)
	{
		printf("There are no products to find.\n\n");
	}

	else {

		printf("	Edit a Product\n--------------------------------------\n");

		//Displays all sotred Product IDs
		ShowProductID(numProducts, products);

		//Gets user input
		printf("Enter the ID of the Product you want to edit from the list above: ");
		strcpy_s(editID, 9, ValidOrderProductID(numProducts, products, 1, 8, editID));

		int match = strcmp(editID, products[i].productID);

		//Loops through all stored ID's until search entry is found
		while ((i < numProducts) && (found == FALSE))
		{

			if (match == 0)
			{
				//Display record found
				ShowOneProduct(products[i]);
				found = TRUE;

				//Allows user to change the products previously stored information
				printf("Please enter the products changed unit sales price:");
				products[i].unitSalesPrice = ValidFloat(1.99, 250.00);

				printf("Please enter the products changed unit cost price:");
				products[i].unitCostPrice = ValidFloat(1.99, 200.00);

				printf("Please enter the products changed quantity:");
				products[i].productQuantity = ValidInt(0, 20);

				printf("Please enter the products changed stock limit:");
				products[i].productStockLimit = ValidInt(5, 15);


				numProducts = i;

				//Displays the updated record
				printf("The record has been updated.\n\n");

				ShowOneProduct(products[i]);
			}

			i++;
		}

	}

}

//Edit a specific orders information
void EditOrder(int numOrders, int numProducts, struct ORDERSTRUCT *orders, struct PRODUCTSTRUCT *products)
{

	//Gets the current date & time
	SYSTEMTIME str_t;
	GetSystemTime(&str_t);

	int editID;
	int found = FALSE;
	int i = 0;

	//Checks if there are order records to edit
	if (numOrders == 0)
	{
		printf("There are no products to find.\n\n");
	}

	else {

		printf("	Edit an Order\n--------------------------------------\n");

		//Gets user input
		printf("Enter the ID of the Order you want to edit: ");
		editID = ValidInt(1, 999);

		//Loops through all stored ID's until search entry is found
		while ((i < numOrders) && (found == FALSE))
		{
			if (editID == orders[i].orderID)
			{
				//Display record found
				ShowOneOrder(orders[i]);
				found = TRUE;

				//Allows user to change the suppliers previously stored information
				printf("Please enter the orders changed amount:");
				orders[i].orderAmount = ValidInt(1, 999);

				//Combines multiple strings into one (in this case the Day, Month and Year combined to be stored in a standard date format)
				sprintf_s(orders[i].dateModified, 10, ("%d/%d/%d"), str_t.wDay, str_t.wMonth, str_t.wYear);

				numOrders = i;

				//Updates the order total
				orders[numOrders].orderTotal = CalculateOrderTotal(numProducts, numOrders, products, orders);

				//Displays the updated record
				printf("The order has been updated.\n\n");

				ShowOneOrder(orders[i]);
			}

			i++;
		}

	}

}

//Searches for a supplier
void SupplierSearch(int numSuppliers, struct SUPPLIERSTRUCT *suppliers)
{
	int searchID; //ID to search for
	int found = FALSE;
	int i = 0;

	if (numSuppliers == 0)
		//prints error if no suppliers to be searched
	{
		printf("There are no suppliers to find.\n\n");
	}
	else
	{
		//takes use input of supplier 
		printf("Enter the ID of the supplier you want to display (101 - 999): ");
		searchID = ValidInt(101, 149);

		//Loop while there are records in the file and supplier not found
		do
		{
			if (searchID == suppliers[i].supplierID)
			{
				CLEARSCREEN;
				//Display supplier record
				ShowOneSupplier(suppliers[i]);
				found = TRUE;

			}
			i++;//increments i 
		} while ((i < numSuppliers) && (found == FALSE));

		if (found == FALSE)//displays message if no supplier found 
		{
			CLEARSCREEN;
			printf("Supplier %d is not on file\n\n", searchID);//error for if not found 
		}
	}

	printf("\n");
	system("pause");
}

//Searches for a product
void ProductSearch(int numProducts, struct PRODUCTSTRUCT *products)
{
	char searchID[21]; //ID to search for
	int found = FALSE;
	int i = 0;

	if (numProducts == 0)
	{
		printf("There are no products to find.\n\n");//error for if no products to search 
	}
	else
	{

		ShowProductID(numProducts, products);//lists product ids in use 

		printf("Enter the ID of the product you want to display from the list above: ");
		strcpy_s(searchID, 9, ValidOrderProductID(numProducts, products, 1, 8, searchID));

		int match = strcmp(searchID, products[i].productID);

		//Loop while there are records in the file and product not found
		do
		{
			if (match == 0)
			{
				//Display product record
				ShowOneProduct(products[i]);
				found = TRUE;

			}
			i++;
		} while ((i < numProducts) && (found == FALSE));

		if (found == FALSE)//displays message if no product found 
		{
			printf("Product %s is not on file\n", searchID);
		}
	}

	printf("\n\n");
	system("pause");
	CLEARSCREEN;
}

//Searches for a product
void OrderSearch(int numOrders, struct ORDERSTRUCT *orders)
{
	int searchID; //ID to search for
	int found = FALSE;
	int i = 0;

	if (numOrders == 0)
	{
		printf("There are no orders to find.\n\n");//error if not orders to be found 
	}
	else
	{
		printf("Enter the ID of the order you want to display (101 - 999): ");
		searchID = ValidInt(101, 149);//validates input 

		//Loop while there are records in the file and product not found
		do
		{
			if (searchID == orders[i].orderID)
			{
				//Display product record
				ShowOneOrder(orders[i]);
				found = TRUE;

			}
			i++;
		} while ((i < numOrders) && (found == FALSE));

		if (found == FALSE)//displays message if no product found 
		{
			printf("Order %d is not on file\n", searchID);
		}
	}

	printf("\n\n");
	system("pause");
}

//Enter and validate an integer
int ValidInt(int min, int max)
{
	int entry;

	//Loop 
	do
	{
		//Accept input 
		scanf_s("%d", &entry);
		fflush(stdin);

		//Checks if the entered integer is outside the valid range
		if ((entry < min) || (entry > max))
		{
			printf("Error. Entered value is outside of the valid range. Please re-enter: \n");
		}
		//loops if entry is outside the valid range
	} while ((entry < min) || (entry > max));
	//returns entry 
	return entry;
}

//Enter a string and validate its length
char *ValidStringLength(int MinLength, int MaxLength, char *String1)
{

	int i, invalid;
	//Loops 
	do
	{

		invalid = FALSE;
		//Accepts input  from the user
		gets_s(String1, 80);

		//Checks if the entered string is too long
		if (strlen(String1) > MaxLength)
		{
			printf("Error. Entered string is too long. Please re-enter: \n");
		}

		//Checks if anything was entered
		else if (strlen(String1) < MinLength)
		{
			printf("Error. Nothing was entered. Please re-enter: \n");
		}

		//Checks for invalid symbols in string
		for (i = 0; i < strlen(String1); i++)
		{
			//Only checks if invalid has not been set to true 
			if (invalid == FALSE)
			{
				//Checks each individual character in the string for valid characters 
				if ((String1[i] >= 'a' && String1[i] <= 'z') || (String1[i] >= 'A' && String1[i] <= 'Z') || (String1[i] == '-'))
				{

				}
				//else set invalid to false
				else
				{
					printf("Error. Invallid Symbol entered in string. Please re-enter:");

					invalid = TRUE;
				}
				//check next character
			}

		}
		//Loops while length is invalid or string set as invalid
	} while ((strlen(String1) > MaxLength) || (strlen(String1) < MinLength) || (invalid == TRUE));

	//return string 
	return String1;
}


//Checks too see if ID is already being used
int ValidSupplierID(int min, int max, int numSuppliers, struct SUPPLIERSTRUCT *suppliers)
{

	int entry, i, found;
	//Loop
	do
	{

		found = FALSE;
		//Accept entry
		scanf_s("%d", &entry);
		fflush(stdin);

		//Checks if the ID is in the valid range
		if ((entry < min) || (entry > max))
		{
			printf("Error. ID is outside of the valid range. Please re-enter: \n");
		}

		//Loops through all stored ID's too see if it is already being used
		for (i = 0; i < numSuppliers; i++)
		{
			//Id is in use 
			if (entry == suppliers[i].supplierID)
			{
				printf("Error. ID is already in use. Please re-enter: \n");

				found = TRUE;
			}

		}
		//Loops while invalid
	} while ((entry < min) || (entry > max) || (found == TRUE));
	//returns entry 
	return entry;
}


//Validates a product ID
char *ValidProductID(int MinLength, int MaxLength, char *String1, int numProducts, struct PRODUCTSTRUCT *products)
{

	int i, invalid;

	do
	{

		invalid = FALSE;

		//Gets user input
		gets_s(String1, 20);

		//Checks if the entered string is too long
		if (strlen(String1) > MaxLength)
		{
			printf("Error. The product ID you just entered is too long. Please re-enter: \n");
		}

		//Checks if anything was entered
		else if (strlen(String1) < MinLength)
		{
			printf("Error. Nothing was entered. Please re-enter: \n");
		}

		//Checks that the first 3 characters entered are letters
		for (i = 0; i < 3; i++)
		{

			if (invalid == FALSE)
			{

				if ((String1[i] >= 'a' && String1[i] <= 'z') || (String1[i] >= 'A' && String1[i] <= 'Z'))
				{

				}

				else
				{
					printf("Error. Invallid Symbol entered in string. Please re-enter:");

					invalid = TRUE;
				}

			}

		}

		//Checks that the following 5 characters are numbers
		for (i = i; i < 8; i++)
		{

			if (invalid == FALSE)
			{

				if ((String1[i] >= '0' && String1[i] <= '9'))
				{

				}

				else
				{
					printf("Error. Invallid Symbol entered in string. Please re-enter:");

					invalid = TRUE;
				}

			}

		}

		//Loops through all stored ID's too see if it is already being used
		for (i = 0; i < numProducts; i++)
		{

			if (String1 == products[i].productID)
			{
				printf("Error. ID is already in use. Please re-enter: \n");

				invalid = TRUE;
			}

		}

	} while ((strlen(String1) > MaxLength) || (strlen(String1) < MinLength) || (invalid == TRUE));

	return String1;
}


//Validate the Order Product ID
char *ValidOrderProductID(int numProducts, struct PRODUCTSTRUCT *products, int MinLength, int MaxLength, char *String1)
{

	int i, invalid, found;

	do
	{

		invalid = FALSE;

		found = FALSE;

		//Gets user input
		gets_s(String1, 20);

		//Checks if the entered string is too long
		if (strlen(String1) > MaxLength)
		{
			printf("Error. The product ID you just entered is too long. Please re-enter: \n");
		}

		//Checks if anything was entered
		else if (strlen(String1) < MinLength)
		{
			printf("Error. Nothing was entered. Please re-enter: \n");
		}

		//Checks that the first 3 characters are letters
		for (i = 0; i < 3; i++)
		{

			if (invalid == FALSE)
			{

				if ((String1[i] >= 'a' && String1[i] <= 'z') || (String1[i] >= 'A' && String1[i] <= 'Z'))
				{

				}

				else
				{
					printf("Error. Invallid Symbol entered in string. Please re-enter:");

					invalid = TRUE;
				}

			}

		}

		//Checks that the following 5 characters are numbers
		for (i = i; i < 8; i++)
		{

			if (invalid == FALSE)
			{

				if ((String1[i] >= '0' && String1[i] <= '9'))
				{

				}

				else
				{
					printf("Error. Invallid Symbol entered in string. Please re-enter:");

					invalid = TRUE;
				}

			}

		}

		//Loops through all stored ID's too ensure it exists
		
		i = -1;

		while ((found == FALSE) && (i < numProducts)) {

			i++;

			int stringValid = strcmp(products[i].productID, String1);

			if (stringValid == 0)
			{
				invalid = FALSE;
				found = TRUE;
			}

			else
			{
				invalid = TRUE;
				found = FALSE;

				printf("This ID does not belong to an existing product. Please re-enter: \n");
			}
			
		}
		
	} while ((strlen(String1) > MaxLength) || (strlen(String1) < MinLength) || (invalid == TRUE));

	return String1;
}

//Enter and validate a float
float ValidFloat(float min, float max)
{

	float entry;
	//Post conditioned loop 
	do
	{
		//Accepts another input
		scanf_s("%f", &entry);
		fflush(stdin);

		//Checks if the entered float is in the valid range
		if ((entry < min) || (entry > max))
		{
			printf("Error. Entered value is outside of the valid range. Please re-enter: \n");
		}
		//Checks if outside range
	} while ((entry < min) || (entry > max));
	//Returns entry 
	return entry;
}

//Enter a post code and validate it
char *ValidPostCode(int MinLength, int MaxLength, char *String1)
{

	int i, invalid;
	int length;

	do
	{

		invalid = FALSE;

		//Gets user input
		gets_s(String1, 21);
		length = strlen(String1);

		//Checks if the entered string contains any spaces
		for (i = 0; i <= length; i++) {

			if (String1[i] == ' ') {

				printf("This postcode contains spaces , please re-enter without spaces : \n");

				invalid = TRUE;
			}

		}

		//Checks if the entered string is too long
		if ((strlen(String1) > MaxLength) && (invalid == FALSE))
		{
			printf("Error. The post code you just entered is too long. Please re-enter: \n");
		}

		//Checks if anything was entered
		else if ((strlen(String1) < MinLength) && (invalid == FALSE))
		{
			printf("Error. Nothing was entered. Please re-enter: \n");
		}

		//Checks that the first two characters are either letters or numbers
		for (i = 0; i < 2; i++)
		{

			if (invalid == FALSE)
			{

				if ((String1[i] >= 'a' && String1[i] <= 'z') || (String1[i] >= 'A' && String1[i] <= 'Z') || (String1[i] >= '0' && String1[i] <= '9'))
				{

				}

				else if (invalid == FALSE)
				{
					printf("Error. Invallid Symbol entered in string. Please re-enter:");

					invalid = TRUE;
				}

			}

		}

		//If second character in post code is a number
		if (String1[1] >= '0' && String1[1] <= '9')
		{

			//If there should be two or three numbers that follow
			if (strlen(String1) == 5)
			{

				//Checks following 2 characters to ensure that they are numbers
				for (i = 1; i < 3; i++)
				{

					if (String1[i] >= '0' && String1[i] <= '9')
					{

					}

					else if (invalid == FALSE)
					{

						printf("Error. Invallid Symbol entered in string. Please re-enter:");

						invalid = TRUE;

					}

				}

				//Checks that final 2 characters are letters
				for (i = 3; i < 5; i++)
				{

					if ((String1[i] >= 'a' && String1[i] <= 'z') || (String1[i] >= 'A' && String1[i] <= 'Z'))
					{

					}

					else if (invalid == FALSE)
					{

						printf("Error. Invallid Symbol entered in string. Please re-enter:");

						invalid = TRUE;

					}

				}



			}

			//Else there are three numbers that should follow
			else {

				//Checks following 3 characters to ensure that they are numbers
				for (i = 2; i < 4; i++)
				{

					if (String1[i] >= '0' && String1[i] <= '9')
					{

					}

					else if (invalid == FALSE)
					{

						printf("Error. Invallid Symbol entered in string. Please re-enter:");

						invalid = TRUE;

					}

				}

				//Checks that final 2 characters are letters
				for (i = 4; i < 6; i++)
				{

					if ((String1[i] >= 'a' && String1[i] <= 'z') || (String1[i] >= 'A' && String1[i] <= 'Z'))
					{

					}

					else if (invalid == FALSE)
					{

						printf("Error. Invallid Symbol entered in string. Please re-enter:");

						invalid = TRUE;

					}

				}

			}

		}

		//If second character in the post code is a letter
		else
		{

			//If there should be two or three numbers that follow
			if (strlen(String1) == 6)
			{

				//Checks that the following 2 characters are numbers
				for (i = 2; i < 4; i++)
				{

					if (String1[i] >= '0' && String1[i] <= '9')
					{

					}

					else if (invalid == FALSE)
					{

						printf("Error. Invallid Symbol entered in string. Please re-enter:");

						invalid = TRUE;

					}

				}

				//Checks that the final 2 characters are numbers
				for (i = 4; i < 6; i++)
				{

					if ((String1[i] >= 'a' && String1[i] <= 'z') || (String1[i] >= 'A' && String1[i] <= 'Z'))
					{

					}

					else if (invalid == FALSE)
					{

						printf("Error. Invallid Symbol entered in string. Please re-enter:");

						invalid = TRUE;

					}

				}

			}

			else
			{

				//Checks that the following 3 characters are numbers
				for (i = 2; i < 5; i++)
				{

					if (String1[i] >= '0' && String1[i] <= '9')
					{

					}

					else if (invalid == FALSE)
					{

						printf("Error. Invallid Symbol entered in string. Please re-enter:");

						invalid = TRUE;

					}

				}

				//Checks that the final 2 characters are numbers
				for (i = 5; i < 7; i++)
				{

					if ((String1[i] >= 'a' && String1[i] <= 'z') || (String1[i] >= 'A' && String1[i] <= 'Z'))
					{

					}

					else if (invalid == FALSE)
					{

						printf("Error. Invallid Symbol entered in string. Please re-enter:");

						invalid = TRUE;

					}

				}

			}

		}

	} while ((strlen(String1) > MaxLength) || (strlen(String1) < MinLength) || (invalid == TRUE));

	return String1;
}

//Copy faculty file to array and return number of faculties copied
int FileToSupplierArray(struct SUPPLIERSTRUCT *suppliers)
{
	FILE *fp;
	struct SUPPLIERSTRUCT Supplier;
	char reply;
	int numSuppliers = 0;

	fopen_s(&fp, SUPPLIERFN, "rb");
	if (fp == NULL)
	{
		printf("Existing supplier file not found. Do you want to create a new file? Y/N: ");
		scanf_s("%c", &reply, 1);
		fflush(stdin);
		reply = toupper(reply);

		if (reply == 'N')
		{
			exit(0);
		}
	}
	else

	{
		//Read first record
		fread(&Supplier, sizeof(struct SUPPLIERSTRUCT), 1, fp);

		//Keep going up to end of file marker
		while (!(feof(fp)))
		{
			//Copy borrower read from file to array
			suppliers[numSuppliers] = Supplier;
			//Move to next borrower in array
			numSuppliers++;

			//Read subsequent borrower records
			fread(&Supplier, sizeof(struct SUPPLIERSTRUCT), 1, fp);
		}
		fclose(fp);
	}

	return numSuppliers; //Pass number of records found back to main function
}

//Copy faculty file to array and return number of faculties copied
int FileToProductArray(struct PRODUCTSTRUCT *products)
{
	FILE *fp;
	struct PRODUCTSTRUCT Product;
	char reply;
	int numProducts = 0;

	fopen_s(&fp, PRODUCTFN, "rb");
	if (fp == NULL)
	{
		printf("Existing product file not found. Do you want to create a new file? Y/N: ");
		scanf_s("%c", &reply, 1);
		fflush(stdin);
		reply = toupper(reply);

		if (reply == 'N')
		{
			exit(0);
		}
	}
	else

	{
		//Read first record
		fread(&Product, sizeof(struct PRODUCTSTRUCT), 1, fp);

		//Keep going up to end of file marker
		while (!(feof(fp)))
		{
			//Copy borrower read from file to array
			products[numProducts] = Product;
			//Move to next borrower in array
			numProducts++;

			//Read subsequent borrower records
			fread(&Product, sizeof(struct PRODUCTSTRUCT), 1, fp);
		}
		fclose(fp);
	}

	return numProducts; //Pass number of records found back to main function
}


//Copy faculty file to array and return number of faculties copied
int FileToOrderArray(struct ORDERSTRUCT *orders)
{
	FILE *fp;
	struct ORDERSTRUCT Order;
	char reply;
	int numOrders = 0;

	fopen_s(&fp, ORDERFN, "rb");
	if (fp == NULL)
	{
		printf("Existing order file not found. Do you want to create a new file? Y/N: ");
		scanf_s("%c", &reply, 1);
		fflush(stdin);
		reply = toupper(reply);

		if (reply == 'N')
		{
			exit(0);
		}
	}
	else

	{
		//Read first record
		fread(&Order, sizeof(struct ORDERSTRUCT), 1, fp);

		//Keep going up to end of file marker
		while (!(feof(fp)))
		{
			//Copy borrower read from file to array
			orders[numOrders] = Order;
			//Move to next borrower in array
			numOrders++;

			//Read subsequent borrower records
			fread(&Order, sizeof(struct ORDERSTRUCT), 1, fp);
		}
		fclose(fp);
	}

	return numOrders; //Pass number of records found back to main function
}

//Copy Supplier Array to File
void SupplierArrayToFile(int numSuppliers, struct SUPPLIERSTRUCT *suppliers)
{
	FILE *fp;
	struct SUPPLIERSTRUCT Supplier;
	int i;

	fopen_s(&fp, SUPPLIERFN, "wb");
	if (fp == NULL)
	{
		printf("Cannot open file\n");
		return;
	}

	for (i = 0; i < numSuppliers; i++)
	{
		//Write borrower record in array to file
		fwrite(&suppliers[i], sizeof(struct SUPPLIERSTRUCT), 1, fp);
	}

	fclose(fp);
}

//Copy Product Array to File
void ProductArrayToFile(int numProducts, struct PRODUCTSTRUCT *products)
{
	FILE *fp;
	struct PRODUCTSTRUCT Product;
	int i;

	fopen_s(&fp, PRODUCTFN, "wb");
	if (fp == NULL)
	{
		printf("Cannot open file\n");
		return;
	}

	for (i = 0; i < numProducts; i++)
	{
		//Write borrower record in array to file
		fwrite(&products[i], sizeof(struct PRODUCTSTRUCT), 1, fp);
	}

	fclose(fp);
}

//Copy Order Array to File
void OrderArrayToFile(int numOrders, struct ORDERSTRUCT *orders)
{
	FILE *fp;
	struct ORDERSTRUCT Order;
	int i;

	fopen_s(&fp, ORDERFN, "wb");
	if (fp == NULL)
	{
		printf("Cannot open file\n");
		return;
	}

	for (i = 0; i < numOrders; i++)
	{
		//Write borrower record in array to file
		fwrite(&orders[i], sizeof(struct ORDERSTRUCT), 1, fp);
	}

	fclose(fp);
}

//Delete all records stored in the Supplier array and reset it to a blank structure
int ResetSupplierFile(struct SUPPLIERSTRUCT *suppliers)
{
	char emptyString[10] = "\0";
	int i, numSuppliers = 0;

	//Loops through all stored supplier records and deletes them
	for (i = numSuppliers; i > 0; i--)
	{
		suppliers[i].supplierID = 0;
		strcpy_s(suppliers[i].supplierName, 30, emptyString);
		strcpy_s(suppliers[i].supplierTeleNo, 12, emptyString);
		strcpy_s(suppliers[i].supplierEmail, 254, emptyString);
		strcpy_s(suppliers[i].supplierContact, 25, emptyString);
	}

	numSuppliers = 0;

	return numSuppliers;
}

//Delete all records stored in the Product array and reset it to a blank structure
int ResetProductFile(struct PRODUCTSTRUCT *products)
{
	char emptyString[10] = "\0";
	int i, numProducts = 0;

	//Loops through all stored product records and deletes them
	for (i = numProducts; i > 0; i--)
	{
		strcpy_s(products[i].productID, 8, emptyString);
		strcpy_s(products[i].productDesc, 50, emptyString);
		products[i].productType = "";
		products[i].unitSalesPrice = 0;
		products[i].unitCostPrice = 0;
		products[i].productQuantity = 0;
		products[i].productStockLimit = 0;
	}

	numProducts = 0;

	return numProducts;
}

//Delete all records stored in the Order array and reset it to a blank structure
int ResetOrderFile(struct ORDERSTRUCT *orders)
{
	char emptyString[10] = "\0";
	int i, numOrders = 0;

	//Loops through all stored order records and deletes them
	for (i = numOrders; i > 0; i--)
	{
		strcpy_s(orders[i].orderProductID, 8, emptyString);
		strcpy_s(orders[i].dateCreated, 10, emptyString);
		strcpy_s(orders[i].dateModified, 10, emptyString);
		orders[i].orderID = 0;
		orders[i].orderAmount = 0;
		orders[i].orderTotal = 0.0;
	}

	numOrders = 0;

	return numOrders;
}

//Validate a product type
char ValidType() {
	int validEntry = FALSE;
	char userChar[40];
	//Loop
	do {

		int size = 0;
		validEntry = FALSE;
		printf("\nEnter a product type:\nP. Paint\nB. Brushes\nW. Wallpaper\nS. Sundries\nEnter Here: ");
		//Get inout
		gets_s(userChar, 39);

		//Set size variable 
		size = strlen(userChar);

		//Covert first character to upper as we are only checking that one 
		userChar[0] = toupper(userChar[0]);
		//Checks if valid 
		if ((userChar[0] == 'B') || (userChar[0] == 'P') || (userChar[0] == 'W') || (userChar[0] == 'S')) {
			validEntry = TRUE;
		}
		//else invalid
		else {
			validEntry = FALSE;
			printf("\nInvalid entry, try again");
		}
		//checks if size is correct
		if (validEntry == TRUE) {
			if (size > 1) {
				validEntry = FALSE;
				printf("\nInvalid Size, try again");
			}
		}
		//Loops while invalid
	} while (validEntry == FALSE);

	char toBeReturned = userChar[0];
	//returns only the char
	return toBeReturned;

}

//This function will take an input from the user 
void GetUserEmail(char* userEmail) {

	//Local Variables
	char userEntry[400];
	int validChar = TRUE, validLen = FALSE, validAt = FALSE, validDot = FALSE, length, i, validPreAt = FALSE;
	int amDots, amAts, testDone = 0;
	//Loops
	do {

		amDots = 0;
		amAts = 0;
		validLen = FALSE;
		validAt = FALSE;
		validDot = FALSE;
		validChar = TRUE;
		validPreAt = FALSE;
		//Checks the stdin stream is clear 
		fflush(stdin);
		//Gets input
		gets_s(userEntry, 399);

		//Sets length to be the length of userEntry
		length = strlen(&userEntry);
		//check size first
		if ((length > 254) || (length == 0) || (length == 1) || (length == 2) || (length == 3)) {
			validLen = FALSE;
			//Size is incorrect
		}
		//Size is correct
		else {
			//For loop to search for invalid chars looking for @ and . 
			validLen = TRUE;
			for (i = 0; i <= length; i++) {
				//find @
				if ((validAt == FALSE) && (i < length)) {
					if (userEntry[i] == '@') {
						validAt = TRUE;
						//Nested if
					}
					//End of if
				}
				//Check for fullstop
				if ((validAt == TRUE) && (i < length))
				{
					//dot found
					if (userEntry[i] == '.') {
						validDot = TRUE;
					}


				}
			}


			//check for character before @ 
			if (validAt == TRUE) {
				testDone = 0;

				for (i = 0; i < length; i++) {
					//@ is found
					//find i value where @ is
					if ((userEntry[i] == '@') && (testDone == 0)) {
						testDone++;
						i--;
						//Check what's before that, is it a-z
						if ((userEntry[i] >= 'a') && (userEntry[i] <= 'z')) {
							validPreAt = TRUE;
							i++;
						}
						//Check if A-Z
						else if ((userEntry[i] >= 'A') && (userEntry[i] <= 'Z')) {
							validPreAt = TRUE;
							i++;
						}
						//Check if - or _
						else if ((userEntry[i] == '-') || (userEntry[i] == '_')) {
							validPreAt = TRUE;
							i++;
						}
						//Check if 1-9
						else if ((userEntry[i] >= '1') && (userEntry[i] <= '9')) {
							validPreAt = TRUE;
							i++;
						}
						//Else input is invalid
						else {
							validPreAt = FALSE;
							i++;
						}
					}

				}

			}

			//Count how many @'s there are
			if (validAt == TRUE) {

				amAts = 0;
				//for every @ found amAts is incremented
				for (i = 0; i <= length; i++) {
					if (userEntry[i] == '@') {
						amAts++;
					}
					//if more than one @ sign then invalid
					if (amAts > 1) {
						validAt = FALSE;
					}
				}

			}


			//check multiple dots aren't following each other 
			if (validDot == TRUE) {

				for (i = 0; i <= length; i++) {
					//finds where the first . is 
					if (userEntry[i] == '.') {
						i++;
						//checks the position after the . for another.
						if (userEntry[i] == '.') {
							validDot = FALSE;
						}
						//then checks position before .	
						i = i - 2;
						if (userEntry[i] == '.') {
							validDot = FALSE;
						}
						//checks if @. next to each other
						if (userEntry[i] == '@') {
							validDot = FALSE;
						}
						//move i back to correct value
						i++;
					}
				}

			}

		}
		//If invalid error message
		if ((validDot != TRUE) || (validAt != TRUE) || (validLen != TRUE) || (validPreAt != TRUE))
		{
			printf("\nInvalid Email address. Please re-enter: \n ");
		}
		//Loop while error 
	} while ((validDot != TRUE) || (validAt != TRUE) || (validLen != TRUE) || (validPreAt != TRUE));

	//Move userEntry to user email
	for (i = 0; i < 255; i++) {
		userEmail[i] = userEntry[i];
	}
}

//Validates telephone number 
void ValidTeleNo(char* numberStoredHere) {
	//Local Variables
	char userEntry[101];
	int i, valid = FALSE, length;
	//Loops 
	do {
		//Accepts userEntry 
		fflush(stdin);
		gets_s(userEntry, 100);
		//Switch's depending on the first character 
		switch (userEntry[0]) {
			//If + number 
		case '+':
			//Sets valid to be the returned value which PlusNumValid returns 
			valid = PlusNumValid(&userEntry);
			//Sets the length to be the value of userEntry
			length = strlen(&userEntry);
			//If length is incorrect value set as invalid 
			if (length != 13) {
				valid = FALSE;
			}
			break;
			// 0 number 
		case '0':
			//valid is set to whatever NonPlusValid teturns 
			valid = NonPlusValid(&userEntry);
			//sets length to the length of userEntry
			length = strlen(&userEntry);
			//Checks if valid length
			if (length != 11) {
				valid = FALSE;
			}
			break;
		}

		//Check what valid has returned
		if (valid == FALSE) {
			printf("\nInvalid number. Please re-enter: \n");
		}
		else {
			//Valid entry 
		}
		//Loops while valid is invalid
	} while (valid == FALSE);


	//Move the string entered into the string in the main function
	for (i = 0; i <= 13; i++) {
		numberStoredHere[i] = userEntry[i];
	}
}

//This function checks whether or not a plus number is valid 
int PlusNumValid(char* userEntry) {

	//Local variables
	int i, valid = TRUE;
	//For loop to check every char except the first one
	for (i = 1; i <= 11; i++) {

		//This only continue if the number hasn't be ruled to be incorrect, if not it skips it.
		if (valid == TRUE) {

			if ((userEntry[i] >= '0') && (userEntry[i] <= '9')) {
				//Valid Number 
			}
			else {
				valid = FALSE;
			}
			//End of initial if 
		}
		//End of for
	}
	return valid;
}

//This checks a number that just has 0 in it 
int NonPlusValid(char* userEntry) {
	//Local Variables
	int i, valid = TRUE;

	//For loop to check every char except the first one
	for (i = 1; i <= 9; i++) {

		//This only continue if the number hasn't be ruled to be incorrect, if not it skips it.
		if (valid == TRUE) {

			if ((userEntry[i] >= '0') && (userEntry[i] <= '9')) {
				//Valid Number 
			}
			else {
				valid = FALSE;
			}
			//End of initial if 


		}


	}
	return valid;
}

//This Function quits the program
void QuitProgram(int numSuppliers, int numProducts, int numOrders, struct SUPPLIERSTRUCT *suppliers, struct PRODUCTSTRUCT *products, struct ORDERSTRUCT *orders) {

	//Copies records held in structures to files
	SupplierArrayToFile(numSuppliers, suppliers);
	ProductArrayToFile(numProducts, products);
	OrderArrayToFile(numOrders, orders);

	printf("Files successfully saved...\n");
	printf("Quitting program...\n\n");
	system("pause");
	printf("\n\n");
	exit(0);

}
