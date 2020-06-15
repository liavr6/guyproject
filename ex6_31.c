#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>



#define ENTERING_QUESTION "Please choose a question by entering 1-5 (enter 0 to exit):" 
#define DYNAMIC_ALLOCATION_FAILED "dynamic allocation failed"

//Q1//
#define MAX_SIZE_INPUT 31
#define QUESTION1_INPUT_MESSAGE "Please enter binary number input:"
#define QUESTION1_OUTPUT_MESSAGE_DECIMAL "to decimal is:"
#define QUESTION1_OUTPUT_MESSAGE_HEXADECIMAL "to hexadecimal is:"
#define QUESTION1_ERROR_MESSAGE "invalid input, please try again."

//Q2//
#define QUESTION2_INPUT1_MESSAGE "Please enter num1 value:"
#define QUESTION2_INPUT2_MESSAGE "Please enter num2 value:"
#define QUESTION2_OUTPUT_MESSAGE "After swapping:"

//Q3//
#define QUESTION3_INPUT1_MESSAGE "Please enter an integer:"
#define QUESTION3_OUTPUT_MESSAGE "Output:"

//Q4//
#define QUESTION4_INPUT1_MESSAGE "Please enter an integer:"
#define QUESTION4_OUTPUT1_MESSAGE "in binary is a palindrome"
#define QUESTION4_OUTPUT0_MESSAGE "in binary is not a palindrome"

//Q5//
#define QUESTION5_INPUT1_MESSAGE "Please enter an integer:"
#define QUESTION5_OUTPUT1_MESSAGE "Output of Q5:"
/////////////////////moved the first define up

void bin2hexanddec(char *bin_str)
{
	//int num = returnbinaryint(bin_str);
	//Question 1 
	char hexString[MAX_SIZE_INPUT]; // long enough for any 32-bit value, 4-byte aligned
	int dec=bstringtoint(bin_str);
	sprintf(hexString, "%x", dec);
	printf("%s %s %d", bin_str, QUESTION1_OUTPUT_MESSAGE_DECIMAL, dec);
	printf("%s", "\n");
	printf("%s %s %s", bin_str, QUESTION1_OUTPUT_MESSAGE_HEXADECIMAL, hexString);
	printf("%s", "\n");
	}


void swap(int* xp, int* yp)
{
	//Question 2
	*xp = *xp ^ *yp;
	*yp = *xp ^ *yp;
	*xp = *xp ^ *yp;
	printf("%s num1=%d num2=%d", QUESTION2_OUTPUT_MESSAGE,*xp, *yp);
	printf("%s", "\n");

}

int minPowerOf2(int num)
{
	int bin = 1;
	while (bin < num)
		bin <<= 1;
	return bin;
}

int isPalindrome(int num)
{
		 int rev = 0;
		 int n = num;
		// traversing bits of 'n' from the right 
		while (n > 0) {
			// bitwise left shift 'rev' by 1 
			rev <<= 1;
			// if current bit is '1' 
			if (n & 1 == 1)
				rev ^= 1;
			// bitwise right shift 'n' by 1 
			n >>= 1;
		}
	// function to check whether binary representation 
	// of a number is palindrome or not 
		// get the number by reversing bits in the 
		// binary representation of 'n' 
		return (num == rev);
	}


int swap_even_odd(int num)
{
	//Question 5
	int tmp = 0, ind;
	for (ind = 1; ind; ind <<= 2)
		tmp |= (num & ind) << 1 | (num & ind << 1) >> 1;
	return tmp;
}


int bstringtoint(char *bstring)
{
	int sum = 0;
	while (*bstring)
	{
		sum <<= 1;
		sum += *bstring - '0';
		bstring++;
	}
	return sum;
}

int checkifbinary(char *binarystr)
{
	int size = sizeof(binarystr);
	for (int i = 0; i < size; i++)
	{
		if (binarystr[i] != '0' && binarystr[i] != '1')
		{
			return 1;
		}

	}
	return 0;
}

int main()
{
	while (1)
	{
		int choice = 0;
		int xp=0, yp=0;
		printf("%s", ENTERING_QUESTION);
		scanf("%d", &choice);
		int input = 0;
		char bin[MAX_SIZE_INPUT];

		switch (choice)
		{
		case 1:
			printf("%s", QUESTION1_INPUT_MESSAGE);
			scanf("%s", &bin);
			while (checkifbinary(bin) != 0)
			{
				printf("%s", QUESTION1_ERROR_MESSAGE);
				printf("%s", "\n");
				printf("%s", QUESTION1_INPUT_MESSAGE);
				scanf("%s", &bin);
			}
				bin2hexanddec(bin);
			break;

		case 2:
			printf("%s", QUESTION2_INPUT1_MESSAGE);
			printf("%s", "\n");
			scanf("%d", &xp);
			printf("%s", QUESTION2_INPUT2_MESSAGE);
			printf("%s", "\n");
			scanf("%d", &yp);
			swap(&xp, &yp);

			break;
		case 3:
			input = 0;
			printf("%s", QUESTION3_INPUT1_MESSAGE);
			printf("%s", "\n");
			scanf("%d", &input);
			printf("%s %d", QUESTION3_OUTPUT_MESSAGE, minPowerOf2(input));
			break;
		case 4:
			printf("%s", QUESTION4_INPUT1_MESSAGE);
			scanf("%d", &input);
			if (isPalindrome(input))
			{
				printf("%d %s", input,QUESTION4_OUTPUT1_MESSAGE);
				printf("%s", "\n");
			}
			else
			{
				printf("%d %s", input, QUESTION4_OUTPUT0_MESSAGE);
				printf("%s", "\n");
			}
			break;
		case 5:
			printf("%s", QUESTION5_INPUT1_MESSAGE);
			scanf("%d", &input);
			printf("%s %d", QUESTION5_OUTPUT1_MESSAGE, swap_even_odd(input));
			printf("%s", "\n");
			break;
		case 0:
			exit(0);
			break;

		default:
			break;
		}
	}
	return 0;
}