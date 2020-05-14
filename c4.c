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
"Please choose operation[1 - 6]:";

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
const char * expired_date_check = "\nWhat date you want to check[dd/mm/yy]:";
const char * expired_products = "\n~~~~~~~~~~~~~~~Expired Products~~~~~~~~~~~~~~~\n";
const char * expired_product_name = "Product name: ";
const char * expired_product_barcode = "\nProduct barcode: ";
const char * expired_product_date = "\nProduct expiration date: ";


//operation 4 constant strings
const char * print_no_products = "\nNo products in the store!\n";
const char * print_products = "\n----------";
const char * print_product_name = "\nProduct name: ";
const char * print_product_barcode = "\nProduct barcode: ";
const char * print_product_category = "\nProduct category: ";
const char * print_product_number = "\nProduct available quantity: ";
const char * print_product_price = "\nProduct price: ";
const char * print_product_expireDate = "\nProduct expiration date: ";
const char * print_total_number = "\nTotal number of products: ";

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

int main();
int addproduct();
int remproduct();
int checkexpertionproduct();
int printallproduct();
int updateproduct();
void exitsystem();
void read_barcode(char barcode_str[BARCODE_LENGTH + 1], int max);


int main()
{
	int choice = 0;
	super_market *themarket;

	if (NULL == (themarket = calloc(MAX_NUM_PRODUCTS, sizeof(product))))
		exit(1);
	while (1)
	{
		printf("\n");
		printf("%s", main_interface);
		scanf("%d", &choice);
		switch (choice)
		{
		case 1:
			addproduct();
			break;
		case 2:
			remproduct();
			break;
		case 3:
			checkexpertionproduct();
			break;
		case 4:
			printallproduct();
			break;
		case 5:
			updateproduct();
			break;
		case 6:
			exitsystem();
			break;
		default:
			break;
		}
	}
}


int addproduct()
{
	char barcode[BARCODE_LENGTH + 1] = { 0 };
	printf("%s", adding_product_barcode);
	read_barcode(barcode, BARCODE_LENGTH + 1);
	printf("%s", barcode);

	return 0;

}
int remproduct()
{
	char barcode[BARCODE_LENGTH + 1] = { 0 };
	printf("%s", delete_barcode);
	read_barcode(barcode, BARCODE_LENGTH + 1);
	printf("%s", barcode);

	return 0;
}
int checkexpertionproduct()
{
	printf("%s", expired_date_check);

	return 0;
}
int printallproduct()
{
	printf("%s", print_products);

	return 0;
}
int updateproduct()
{
	char barcode[BARCODE_LENGTH + 1] = { 0 };
	printf("%s", update_barcode);
	read_barcode(barcode, BARCODE_LENGTH + 1);
	printf("%s", barcode);
	return 0;
}
void exitsystem()
{
	//free(*marketforfree);
	printf("%s", exitProgram);
	exit(0);
}


//the function gets input from the user up until max size of the char array

	void  read_barcode(char barcode_str[], int max)
	{
		// read input from the user
		scanf("%s", barcode_str);
		int k;
		// remove '\n' and empty the input buffer
		for (k = 0; k < max; k++)
		{
			if (barcode_str[k] == '\n')
			{
				barcode_str[k] = '\0';	// remove '\n'
				break;
			}
		}
		return 0;
	}
