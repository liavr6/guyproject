
# define NAME_LENGTH 200
# define LINE_LENGTH 400
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


// define struct
typedef struct hw_component { char name[NAME_LENGTH]; int copies; struct hw_component *next; }HW_component;


char *readLine(FILE *fPtrRead, char tav);
HW_component *rename_func(HW_component *list, char oldname[NAME_LENGTH], char newname[NAME_LENGTH]);
HW_component *returnd_from_cos_func(HW_component *list, char name[NAME_LENGTH], int copiestoreturn);
HW_component *production_func(HW_component *list, char name[NAME_LENGTH], int copies);
int fatal_func(HW_component *list, char name[NAME_LENGTH], int mal_num);
int fire_func(HW_component *list, char name[NAME_LENGTH], int mal_num);
char *split(char *buf, int iter);
HW_component *createinlist(char *name, int copynum, HW_component *newlist);
HW_component *new_cmp(char *name, int copynum);
void free_list(HW_component *head);
HW_component* find(HW_component *head, char *val);
HW_component* add_and_sort_alpha(HW_component *head, HW_component *new_node);
void printlisttofile(HW_component *list, FILE *fPtrWrite);
int length(const HW_component *head);



//Input:recives input values from the command line from user
//return parameter:int for success and creats files of lists
//Function functionality : it reads the orders file and acts accordingly with the right actions activating the right functions, finally after all the updates it creates and updated componnent file
int main(int argc, char* argv[])
{
	FILE	*orderfileread = NULL, *fPtrWrite = NULL, *compfileread = NULL;
	HW_component *compnodelist = NULL;
	char	tav = '0';
	char *nextline = NULL;
	int flag = 0;
	char *orderfile = argv[2], *compfile = argv[1], *fPtr = argv[3];
	if (sizeof(argv) != 4) {
		printf("Error: invalid number of arguments (<%d> instead of 3)\n", sizeof(argv));
		exit(1);
	}

	orderfileread = fopen(orderfile, "r");
	if (orderfileread == NULL) {  printf("Error: opening %s failed\n", orderfile); exit(1);}
	compfileread = fopen(compfile, "r");
	if (compfileread == NULL) {  printf("Error: opening %s failed\n", compfile); exit(1);}
	fPtrWrite = fopen(fPtr, "w");
	if (fPtrWrite == NULL) { printf("Error: opening %s failed\n", fPtr);  exit(1);}

		char *nextorder = NULL;
		char line[LINE_LENGTH], name[NAME_LENGTH];
		while (fgets(line, LINE_LENGTH, orderfileread) != NULL)
		{
			nextorder = split(line, 0);
			HW_component* last = NULL;

			if (strstr(nextorder, "Initialize") != NULL)
			{

				int nextcopies = 0;
				char linecomp[LINE_LENGTH], namecomp[NAME_LENGTH];
				while (fgets(linecomp, LINE_LENGTH, compfileread) != NULL)
				{

					strcpy(namecomp, split(linecomp, 0));
					nextcopies = atoi(split(linecomp, 1));
					compnodelist = createinlist(namecomp, nextcopies, compnodelist);
				}
				last = compnodelist;

			}
			else if (strstr(nextorder, "Finalize") != NULL)
			{
				printlisttofile(compnodelist, fPtrWrite);
				free_list(compnodelist);
				break;
			}
			else if (strstr(nextorder, "Rename") != NULL)
			{
				char oldname[NAME_LENGTH];
				strcpy(oldname, split(line, 1));
				char newname[NAME_LENGTH];
				strcpy(newname, split(line, 2));

				compnodelist = rename_func(compnodelist, oldname, newname);

			}
			else if (strstr(nextorder, "Returned_from_customer") != NULL)
			{
				char name[NAME_LENGTH];
				strcpy(name, split(line, 1));
				int copiestoreturn = atoi(split(line, 2));
				compnodelist = returnd_from_cos_func(compnodelist, name, copiestoreturn);

			}
			else if (strstr(nextorder, "Production") != NULL)
			{
				char name[NAME_LENGTH];
				strcpy(name, split(line, 1));
				int copiestoreturn = atoi(split(line, 2));
				compnodelist = production_func(compnodelist, name, copiestoreturn);

			}
			else if (strstr(nextorder, "Fatal_malfunction") != NULL)
			{
				char name[NAME_LENGTH];
				strcpy(name, split(line, 1));
				int mal_num = atoi(split(line, 2));
				fatal_func(compnodelist, name, mal_num);

			}
			else if (strstr(nextorder, "Fire") != NULL)
			{
				char name[NAME_LENGTH];
				strcpy(name, split(line, 1));
				int mal_num = atoi(split(line, 2));
				fire_func(compnodelist, name, mal_num);

			}
			/* more else if clauses */
			else /* default: */
			{
				break;
			}

		}
		fclose(orderfileread);
		fclose(fPtrWrite);
		fclose(compfileread);
	}

//Input:recives a node of the begining of the list and a name to look for
//return parameter:returns a HW_component pointer of the location of wanted value or null if not found
//Function functionality : iterates over the list and comparing the names to the wanted value
HW_component *find(HW_component *head, char *val)
{
	while (head != NULL && strcmp(head->name, val) != 0) {
		head = head->next;
	}
	return head;
}
//Input:recives a pointer to a list and two strings, one to change and one to change to.
//return parameter:returns a HW_component pointer of the list
//Function functionality : finds the relevant node in the list by name and updates its values
HW_component *rename_func(HW_component *list, char oldname[NAME_LENGTH], char newname[NAME_LENGTH])
{
	HW_component *iter = list, *prev = NULL;

	if (list == NULL)
		return list;
	iter = list;
	while(iter !=NULL && strcmp(iter->name, oldname) !=0)
	{
		prev = iter;
		iter = iter->next;
	}
	if (iter != NULL)
	{
		strcpy(iter->name, newname);
		if (iter == list)
			list = list->next;
		else
			prev->next = iter->next;
		list = add_and_sort_alpha(list, iter);
	}
	return list;
}
//Input:recives a pointer to a list and a string of name and an int to update the relevant node with
//return parameter:returns a HW_component pointer of the list
//Function functionality : finds the relevant node in the list by name and updates its values
HW_component *returnd_from_cos_func(HW_component *list, char name[NAME_LENGTH], int copiestoreturn)
{
	HW_component *nodetochange = NULL;
	nodetochange = find(list, name);
	if (nodetochange != NULL)
	{
		nodetochange->copies += copiestoreturn;
	}
	else
	{

		list = createinlist(name, copiestoreturn, list);
	}

	return list;
}
//Input::recives a pointer to a list and a string of name and an int to update the relevant node with
//return parameter:returns a HW_component pointer of the list
//Function functionality : recives a list and adds a component to it or updates the values of a corresponding existing one
HW_component *production_func(HW_component *list, char name[NAME_LENGTH], int copies)
{
	list = returnd_from_cos_func(list, name, copies);
	return list;
}
//Input:
//return parameter:returns an int for success condition
//Function functionality : 
int fatal_func(HW_component *list, char name[NAME_LENGTH], int mal_num)
{
	int i;
	HW_component *nodetochange = NULL;
	nodetochange = find(list, name);
	if (nodetochange != NULL)
	{
		if (mal_num > nodetochange->copies)
			nodetochange->copies = 0;
		else
			nodetochange->copies -= mal_num;
	}
}
//Input:
//return parameter:returns an int for success condition
//Function functionality : 
int fire_func(HW_component *list, char name[NAME_LENGTH], int mal_num)
{
	fatal_func(list, name, mal_num);
}
//Input:recives a pointer to a list
//return parameter:returns the size of the list
//Function functionality : iterates over the list and counts each node, returns the counter value
int length(const HW_component *head) {
	int count = 0;
	HW_component *iter;
	for (iter = head; iter != NULL; iter = iter->next) { count++; }
	return count;
}
//Input:a pointer to a char array which is the name and int which is the copies number
//return parameter:HW_component pointer
//Function functionality : creats a new struct and returns it pointer
/* Allocate a new comps */
HW_component* new_cmp(char *name, int copynum)
{
	HW_component *std = NULL;

	std = (HW_component*)malloc(sizeof(HW_component));
	if (std == NULL)
	{
		printf("Error: memory allocation failed\n");
		exit(1);
	}

	strcpy(std->name, name);
	std->copies = copynum;
	std->next = NULL;

	return std;
}
//Input:recives a pointer to a list and a file address 
//return parameter:None
//Function functionality:iterates over the list and prints it in a specified format to the file
void printlisttofile(HW_component *list, FILE *fPtrWrite)
{
	HW_component *iter=list;
	while (iter != NULL)
	{
		fprintf(fPtrWrite, "%s $$$ %d", iter->name, iter->copies);
		iter = iter->next;
		if (iter != NULL)
			fprintf(fPtrWrite,"\n");
	}
}
//Input: two pointers. one for a list and one for a node
//return parameter:HW_component pointer
//Function functionality : iterates over the list and compares its string values until it finds the right place, then changes the pointers in the list to add it there
HW_component* add_and_sort_alpha(HW_component *head, HW_component *new_node)
{
	HW_component* iter, *prev = NULL;
	 
	if (head == NULL)
		return new_node;

	if (strcmp(new_node->name, head->name) < 0) {
		new_node->next = head;
		return new_node;
	}

	iter = head;
	while (iter != NULL && iter->name != NULL && strcmp(new_node->name, iter->name) >= 0) {
		prev = iter;
		iter = iter->next;
	}

	prev->next = new_node;
	new_node->next = iter;

	return head;
}
//Input:pointer to a list of HW_component
//return parameter: None
//Function functionality : iterates over the list and frees its pointer's allocations
/* Free a list of comps */
void free_list(HW_component *head)
{
	HW_component *temp = NULL;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp);
	}


}
//Input:recives a pointer to a list and a file address 
//return parameter:returns a pointer to the top of the list with the added node to it
//Function functionality : creates a new node by another function and changes the pointers of the list to add the new one in a sorted way
HW_component *createinlist(char *name, int copynum, HW_component *newlist)
{

	HW_component *toreturn = add_and_sort_alpha(newlist, new_cmp(name,copynum));
	return toreturn;
}
//Input:pointer to a char array and int for seperated value which to return
//return parameter: returns a char pointer to a wanted place in a string
//Function functionality : iterates over a string and seperates it by a relevant delimiter and returns the wanted iteration
char *split(char *buf, int iter)
{
	int i, partlen;
	char *endbit, res[NAME_LENGTH];
	for (i = 0; i < iter; i++)
	{
		buf = strstr(buf, " $$$ ");
		if (buf == NULL)
		{
			return NULL;
		}
		buf += strlen(" $$$ ");
	}
	endbit = strstr(buf, " $$$ ");
	if (endbit != NULL)
		partlen = strlen(buf) - strlen(endbit);
	else
		partlen = strlen(buf);

	strncpy(res, buf, partlen);
	if (res[partlen - 1] == '\n')
		partlen--;
	res[partlen] = '\0';

	return res;
}
