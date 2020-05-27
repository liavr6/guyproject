#define MAX_NUM_PRODUCTS 20
#define MAX_PRODUCT_NAME_LENGTH 20
#define MAX_CATEGORY_LENGTH 10
#define BARCODE_LENGTH 12
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const char * main_interface = "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Welcome to CORONA market!\n"\
"~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n"\
"Manage market menu :\n"\
"	1. Add product\n"\
"	2. Remove product\n"\
"	3. Check which products are expired\n"\
"	4. Print all the products\n"\
"	5. Update product\n"\
"	6. EXIT SYSTEM\n"\
"Please choose operation [1-6]:";

//operation 1 constant strings

const char *  adding_product_barcode = "Please enter product barcode:";
const char * barcode_already_exist = "This product already exist, please enter the number of products to add:";
const char * too_much_products = "Can't add more products, not enough space";
const char * adding_product_name = "Please enter product name:";
const char * adding_product_category = "Please enter product category:";
const char * adding_product_number = "Please enter number of products to add:";
const char * adding_product_price = "Please enter the price of the product:";
const char * adding_product_date = "Please enter expiration date of the product[dd/mm/yy]:";
typedef struct date { int year; int month; int day; } date;
typedef struct product { char * product_name; char * product_category; char * barcode; int available; double price; date * expire_date; } product;
typedef struct super_market { product ** product_list; int number_of_products; } super_market;
//operation 2 constant strings
const char * store_empty = "\nThe store is empty!";
const char * delete_barcode = "\nPlease enter product barcode you want to delete:";
const char * delete_barcode_cant_find = "\nCouldn't find the product barcode, try again...";
const char * delete_barcode_succeed = "\nThe product deleted successfully!";


//operation 3 constant strings
const char * expired_date_check = "What date you want to check[dd/mm/yy]:";
const char * expired_products = "~~~~~~~~~~~~~~~Expired Products~~~~~~~~~~~~~~~\n";
const char * expired_product_name = "Product name: ";
const char * expired_product_barcode = "\nProduct barcode: ";
const char * expired_product_date = "\nProduct expiration date: ";


//operation 4 constant strings
const char * print_products_head = "~~~~~~~~~~~~~~~All Products~~~~~~~~~~~~~~~\n";
const char * print_no_products = "No products in the store!\n";
const char * print_products = "----------";
const char * print_product_name = "Product name: ";
const char * print_product_barcode = "Product barcode: ";
const char * print_product_category = "Product category: ";
const char * print_product_number = "Product available quantity: ";
const char * print_product_price = "Product price: ";
const char * print_product_expireDate = "Product expiration date: ";
const char * print_total_number = "Total number of products: ";

//operation 5 constant strings
const char * update_barcode = "\nPlease enter product barcode you want to update:";
const char * update_barcode_notFound = "\nCouldn't find the product barcode, try again...";
const char * update_interface_string = ("\nWhat do you want to update?\n"\
	"	1. Product name\n"\
	"	2. Product category\n"\
	"	3. Product quantity\n"\
	"	4. Product price\n"\
	"	5. Product expiration date\n"\
	"Please choose operation [1-5]:");
const char * update_product_name = "\nPlease enter new product name:";
const char * update_product_category = "\nPlease enter new product category:";
const char * update_product_number = "\nPlease enter new product quantity:";
const char * update_product_price = "\nPlease enter new product price:";
const char * update_product_date = "\nPlease enter new product expiration date[dd/mm/yy]:";

//operation 6 constant strings
const char * exitProgram = "\nexit...";

void main();
int addproduct(super_market *themarket);
int remproduct(super_market *themarket);
int checkexpirationproduct(super_market *themarket);
int printallproduct(super_market *themarket);
int updateproduct(super_market *themarket);
void exitsystem(super_market *themarket);
char *read_barcode(int max);



/*Inputs:(while intilizing the function doesn't recive input, but while running it recives an int which manages the next operations until termination)
Return parameter:None
Function functionality: manages the interface of the program by reciving an int and activating the chosen sequnce of functions by a switch in a while loop,
only exists when the right function is activated*/

void main()
{
	int choice = 0;
	super_market *themarket = NULL;
	product **pro_list = NULL;

	if (NULL == (themarket = malloc(sizeof(super_market))))
		exit(1);
	if (NULL == (pro_list = malloc(MAX_NUM_PRODUCTS * sizeof(product))))
		exit(1);
	themarket->product_list = pro_list;
	themarket->number_of_products = 0;

	while (1)
	{
		printf("\n");
		printf("%s", main_interface);
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			addproduct(themarket);
			break;
		case 2:
			remproduct(themarket);
			break;
		case 3:
			checkexpirationproduct(themarket);
			break;
		case 4:
			printallproduct(themarket);
			break;
		case 5:
			updateproduct(themarket);
			break;
		case 6:
			exitsystem(themarket);
			break;
		default:
			break;
		}
	}
}

/*Inputs:(recives a supermarket pointer) Return parameter:int which specfice success or failure
Function functionality: the function adds a product to the supermarket list and updates the quantity of an exisiting one if asked,
it recives the new product data from the user,
it can add products untill a defined limit*/
int addproduct(super_market *themarket)
{
	if (themarket->number_of_products == MAX_NUM_PRODUCTS)
	{
		printf("%s", too_much_products);
		return 0;
	}
	char *barcode = NULL, *product_name = NULL, *product_category = NULL, *datestirng = NULL, *bar = NULL, day[3] = { 0 }, month[3] = { 0 }, year[3] = { 0 };
	int available = 0, exist = 0, i = 0, numpro = themarket->number_of_products;
	double price = 0;
	date *expire_date = NULL;
	product *prod = NULL;
	if (NULL == (prod = malloc(sizeof(product))))
		return 1;
	if (NULL == (expire_date = malloc(sizeof(date))))
		return 1;
	printf("%s", adding_product_barcode);
	barcode = read_barcode(BARCODE_LENGTH);
	for (i = 0; i < numpro; i++)
	{
		bar = themarket->product_list[i]->barcode;
		if (strcmp(bar, barcode) == 0)
		{
			exist = 1;
			break;
		}
	}
	if (exist)
	{
		printf("%s", barcode_already_exist);
		scanf("%d", &available);
		themarket->product_list[i]->available += available;
		printf("Additional %d products of %s added", available, themarket->product_list[i]->product_name);
		exist = 0;
	}
	else
	{
		printf("%s", adding_product_name);
		product_name = read_barcode(MAX_PRODUCT_NAME_LENGTH);
		printf("%s", adding_product_category);
		product_category = read_barcode(MAX_CATEGORY_LENGTH);
		printf("%s", adding_product_number);
		scanf("%d", &available);
		printf("%s", adding_product_price);
		scanf("%lf", &price);
		printf("%s", adding_product_date);
		datestirng = read_barcode(10);
		strncpy(day, datestirng, 2);
		strncpy(month, datestirng + 3, 2);
		strncpy(year, datestirng + 6, 2);

		expire_date->day = atoi(day);
		expire_date->month = atoi(month);
		expire_date->year = atoi(year);

		prod->barcode = barcode;
		prod->product_name = product_name;
		prod->product_category = product_category;
		prod->available = available;
		prod->price = price;
		prod->expire_date = expire_date;
		printf("The product %s - barcode:%s, added successfully", product_name, barcode);
		themarket->product_list[themarket->number_of_products] = prod;
		themarket->number_of_products += 1;
	}
	exist = 0;
	return 0;
}
int remproduct(super_market *themarket)
{
	char *barcode = NULL;
	int i, bar, numpro = themarket->number_of_products;
	product *temp = NULL;
	// Check if the store is empty
	if (numpro == 0)
	{
		printf("%s", store_empty);
		return 0;
	}
	// While a product was not deleted
	while (1)
	{
		printf("%s", delete_barcode);
		barcode = read_barcode(BARCODE_LENGTH + 1);
		// Check all of the products
		for (i = 0; i < numpro; i++)
		{
			bar = themarket->product_list[i]->barcode;
			// If the barcode is the same delete the product
			if (strcmp(bar, barcode) == 0)
			{
				temp = themarket->product_list[i];
				free(temp);
				while (themarket->product_list[i + 1] != NULL)
				{
					themarket->product_list[i] = themarket->product_list[i + 1];
					i++;
				}
				themarket->product_list[i] = NULL;
				themarket->number_of_products--;
				printf("%s", delete_barcode_succeed);
				return 0;
			}
		}
		printf("%s", delete_barcode_cant_find);
	}
	return 0;
}
int checkexpirationproduct(super_market *themarket)
{
	int i, numpro = themarket->number_of_products, day[3] = { 0 }, month[3] = { 0 }, year[3] = { 0 };
	char datestring[9] = { 0 }, *comp_date = NULL;
	date *check_date = NULL;
	if (NULL == (check_date = malloc(sizeof(date))))
		return 1;

	printf("%s", expired_date_check);
	comp_date = read_barcode(10);
	strncpy(day, comp_date, 2);
	strncpy(month, comp_date + 3, 2);
	strncpy(year, comp_date + 6, 2);

	check_date->day = atoi(day);
	check_date->month = atoi(month);
	check_date->year = atoi(year);
	for (i = 0; i < numpro; i++)
	{
		if (themarket->product_list[i]->expire_date->year < check_date->year)
		{
			printf("%s", expired_products);
			printf("%s%s", expired_product_name, themarket->product_list[i]->product_name);
			printf("%s%s", expired_product_barcode, themarket->product_list[i]->barcode);
			sprintf(datestring, "%d/%d/%d", themarket->product_list[i]->expire_date->day, themarket->product_list[i]->expire_date->month, themarket->product_list[i]->expire_date->year);
			printf("%s%s", expired_product_date, datestring);
			continue;
		}
		if (themarket->product_list[i]->expire_date->year > check_date->year)
			continue;
		if (themarket->product_list[i]->expire_date->year == check_date->year)
		{
			if (themarket->product_list[i]->expire_date->month < check_date->month)
			{
				printf("%s", expired_products);
				printf("%s%s", expired_product_name, themarket->product_list[i]->product_name);
				printf("%s%s", expired_product_barcode, themarket->product_list[i]->barcode);
				sprintf(datestring, "%d/%d/%d", themarket->product_list[i]->expire_date->day, themarket->product_list[i]->expire_date->month, themarket->product_list[i]->expire_date->year);
				printf("%s%s", expired_product_date, datestring);
				continue;
			}
			if (themarket->product_list[i]->expire_date->month > check_date->month)
				continue;
			if (themarket->product_list[i]->expire_date->month == check_date->month)
			{
				if (themarket->product_list[i]->expire_date->day < check_date->day)
				{
					printf("%s", expired_products);
					printf("%s%s", expired_product_name, themarket->product_list[i]->product_name);
					printf("%s%s", expired_product_barcode, themarket->product_list[i]->barcode);
					sprintf(datestring, "%d/%d/%d", themarket->product_list[i]->expire_date->day, themarket->product_list[i]->expire_date->month, themarket->product_list[i]->expire_date->year);
					printf("%s%s", expired_product_date, datestring);
					continue;
				}
				else
					continue;
			}
		}
	}
	return 0;
}/*Inputs:(recives a supermarket pointer) Return parameter:int which specfice success or failure
Function functionality: the function prints all the prodacts and values by order, if the supermarket is empty it declares it with a special message*/
int printallproduct(super_market *themarket)
{
	int index = themarket->number_of_products;
	if (index == 0)
	{
		printf("%s", print_no_products);
		return 0;
	}
	else
	{
		printf("%s", print_products_head);
		for (int i = 0; i < index; i++)
		{


			char datestring[9] = { 0 };
			sprintf(datestring, "%d/%d/%d", themarket->product_list[i]->expire_date->day, themarket->product_list[i]->expire_date->month, themarket->product_list[i]->expire_date->year);

			printf("%s\n", print_products);
			printf(print_product_name);
			printf("%s\n", themarket->product_list[i]->product_name);
			printf(print_product_barcode);
			printf("%s\n", themarket->product_list[i]->barcode);
			printf(print_product_category);
			printf("%s\n", themarket->product_list[i]->product_category);
			printf(print_product_number);
			printf("%d\n", themarket->product_list[i]->available);
			printf(print_product_price);
			printf("%g\n", themarket->product_list[i]->price);
			printf(print_product_expireDate);
			printf("%s\n", datestring);
		}
		printf(print_total_number);
		printf("%d\n", themarket->number_of_products);

	}

	return 0;
}
int updateproduct(super_market *themarket)
{
	int i, bar, choice, num, numpro = themarket->number_of_products;
	char *barcode = NULL;
	// Check if the store is empty
	if (numpro == 0)
	{
		printf("%s", print_no_products);
		return 0;
	}
	while (1)
	{
		printf("%s", update_barcode);
		barcode = read_barcode(BARCODE_LENGTH + 1);
		for (i = 0; i < numpro; i++)
		{
			bar = themarket->product_list[i]->barcode;
			if (strcmp(bar, barcode) == 0)
			{
				printf("%s", update_interface_string);
				scanf("%d", &choice);
				switch (choice)
				{
				case 1:
					printf("%s", update_product_name);
					themarket->product_list[i]->product_name = read_barcode(MAX_PRODUCT_NAME_LENGTH);
					return 0;
				case 2:
					printf("%s", update_product_category);
					themarket->product_list[i]->product_category = read_barcode(MAX_CATEGORY_LENGTH);
					return 0;
				case 3:
					printf("%s", update_product_number);
					scanf("%d", &num);
					themarket->product_list[i]->available = num;
					return 0;
				case 4:
					printf("%s", update_product_price);
					scanf("%d", &num);
					themarket->product_list[i]->price = num;
					return 0;
				case 5:
					printf("%s", update_product_date);
					int day[3] = { 0 }, month[3] = { 0 }, year[3] = { 0 };
					char *new_date = NULL;
					new_date = read_barcode(10);
					strncpy(day, new_date, 2);
					strncpy(month, new_date + 3, 2);
					strncpy(year, new_date + 6, 2);
					themarket->product_list[i]->expire_date->day = atoi(day);
					themarket->product_list[i]->expire_date->month = atoi(month);
					themarket->product_list[i]->expire_date->year = atoi(year);
					return 0;
				default:
					break;
				}
			}
		}
		printf("%s", update_barcode_notFound);
	}
	return 0;
}
/*Inputs:(recives a supermarket pointer) Return parameter:None, but exists while returning exit code 0
Function functionality: the function frees the specified allocated memory by the pointer, prints a success message and terminates the program*/
void exitsystem(super_market *marketforfree)
{
	free(marketforfree);
	printf("%s", exitProgram);
	exit(0);
}

/*Inputs:(int which represents the maximal possible size of the return char array) Return parameter:pointer to a char array
Function functionality: the function gets input from the user up until max size of the char array, filters it, and returns a pointer to the string*/

char *read_barcode(int max)
{
	char format[] = "10000000000000000";
	char *temp = NULL;
	if (NULL == (temp = malloc(max * sizeof(char) + 1)))
		return 1;
	// read input from the user

	sprintf(format, "\n%%%d[^\n]s", max);
	scanf(format, temp);
	return temp;
}
