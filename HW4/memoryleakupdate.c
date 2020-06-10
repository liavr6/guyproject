
# define NAME_LENGTH 200
# define LINE_LENGTH 400
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crtdbg.h>///////////////////////////////////////////////////

// define struct
typedef struct hw_component { char name[NAME_LENGTH]; int copies; struct hw_component *next; }HW_component;


char *readLine(FILE *fPtrRead, char tav);
int rename_func(HW_component *list, char oldname[NAME_LENGTH], char newname[NAME_LENGTH]);
int returnd_from_cos_func(HW_component *list, char name[NAME_LENGTH], int copiestoreturn);
int production_func(HW_component *list, char name[NAME_LENGTH], int copies);
int fatal_func(HW_component *list, char name[NAME_LENGTH], int mal_num);
int fire_func(HW_component *list, char name[NAME_LENGTH], int mal_num);
char *split(char *buf, int iter);
HW_component *createinlist(char *name, int copynum, HW_component *newlist);
HW_component *new_cmp(char *name, int copynum);
void free_list(HW_component *head);
HW_component* find(HW_component *head, char *val);
HW_component* add_and_sort_alpha(HW_component *head, HW_component *new_node);
void printlisttofile(HW_component *list, FILE *fPtrWrite);
void trimTrailing(char * str);
void trimLeading(char * str);
int length(const HW_component *head);

int main(int argc, char* argv[])
{
	FILE	*orderfileread = NULL, *fPtrWrite = NULL, *compfileread = NULL;
	HW_component *compnodelist = NULL;
	char	tav = '0';
	char *nextline = NULL;
	//char orderfile = argv[2], compfile = argv[1], fPtr = argv[3];
	char orderfile[100] = "C:\\Users\\Liav\\Desktop\\txtfiles\\actions.txt";
	char compfile[100] = "C:\\Users\\Liav\\Desktop\\txtfiles\\hw_components.txt";
	char fPtr[100] = "C:\\Users\\Liav\\Desktop\\txtfiles\\updated222_components.txt";
	orderfileread = fopen(orderfile, "r");
	compfileread = fopen(compfile, "r");
	fPtrWrite = fopen(fPtr, "w");
	if (orderfileread == NULL || fPtrWrite == NULL) { printf("File did not open. Exit..\n"); }

	char *nextorder = NULL;
	char line[LINE_LENGTH], name[NAME_LENGTH];
	while (fgets(line, LINE_LENGTH, orderfileread) != NULL)
	{
		nextorder = split(line, 0);
		//trimTrailing(nextorder);
		//_CrtDumpMemoryLeaks();


		HW_component* last = NULL;

		if (strstr(nextorder, "Initialize") != NULL)
		{
	
			int nextcopies = 0;
			char linecomp[LINE_LENGTH], namecomp[NAME_LENGTH];
			while (fgets(linecomp, LINE_LENGTH, compfileread) != NULL)
			{
				//_CrtDumpMemoryLeaks();

				strcpy(namecomp, split(linecomp, 0));////////////////////////check if 0 and 1
				nextcopies = atoi(split(linecomp, 1));
				compnodelist = createinlist(namecomp, nextcopies, compnodelist);
				//free(tempdata);
			}
			fclose(compfileread);
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
			char newname[NAME_LENGTH];/////////check this
			strcpy(newname, split(line, 2));

			rename_func(compnodelist, oldname, newname);

		}
		else if (strstr(nextorder, "Returned_from_customer") != NULL)
		{
			char name[NAME_LENGTH];
			strcpy(name, split(line, 1));
			int copiestoreturn = atoi(split(line, 2));
			returnd_from_cos_func(compnodelist, name, copiestoreturn);

		}
		else if (strstr(nextorder, "Production") != NULL)
		{
			char name[NAME_LENGTH];
			strcpy(name, split(line, 1));
			int copiestoreturn = atoi(split(line, 2));
			production_func(compnodelist, name, copiestoreturn);

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
		//if (nextorder != NULL)
		//{
		//	free(nextorder);
		//	_CrtDumpMemoryLeaks();

		//}
	}
	fclose(orderfileread);
	fclose(fPtrWrite);
}

HW_component *find(HW_component *head, char *val)
{
	while (head != NULL && strcmp(head->name, val) != 0) {
		head = head->next;
		//printf("%s\n",head->name);
	}
	return head;
}

int rename_func(HW_component *list, char oldname[NAME_LENGTH], char newname[NAME_LENGTH])
{
	HW_component *iter = list, *prev = NULL;

	if (list == NULL)
		return list;
	iter = list;
	while(iter !=NULL && strcmp(iter->name, newname) !=0)
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
int returnd_from_cos_func(HW_component *list, char name[NAME_LENGTH], int copiestoreturn)
{
	HW_component *nodetochange = NULL;
	nodetochange = find(list, name);
	if (nodetochange != NULL)
	{
		nodetochange->copies += copiestoreturn;
	}
	else
	{

		createinlist(name, copiestoreturn, list);
	}

	return 0;
}
int production_func(HW_component *list, char name[NAME_LENGTH], int copies)
{
	returnd_from_cos_func(list, name, copies);
	return 0;
}
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
int fire_func(HW_component *list, char name[NAME_LENGTH], int mal_num)
{
	fatal_func(list, name, mal_num);
}


int length(const HW_component *head) {
	int count = 0;
	HW_component *iter;
	for (iter = head; iter != NULL; iter = iter->next) { count++; }
	return count;
}
/* Allocate a new comps */
HW_component* new_cmp(char *name, int copynum)
{
	HW_component *std = NULL;

	std = (HW_component*)malloc(sizeof(HW_component));
	if (std == NULL)
	{
		printf("Memory allocation error!\n");
		return NULL;
	}

	strcpy(std->name, name);
	std->copies = copynum;
	std->next = NULL;

	return std;
}

void printlisttofile(HW_component *list, FILE *fPtrWrite)
{
	HW_component *iter=list;
	while (iter != NULL)
	{
		fprintf(fPtrWrite, "%s $$$ %d\n", iter->name, iter->copies);
		iter = iter->next;
	}
}
HW_component* add_and_sort_alpha(HW_component *head, HW_component *new_node)
{
	HW_component* iter, *prev = NULL;
	/* incomplete, must check for failure */
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
	_CrtDumpMemoryLeaks();

}


HW_component *createinlist(char *name, int copynum, HW_component *newlist)
{

	HW_component *toreturn = add_and_sort_alpha(newlist, new_cmp(name,copynum));
	return toreturn;
}
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
//char *split(char *buf, int iter)
//{
//	int i = 0;
//	int dollar = 0;
//	if (strchr(buf, '$')) { dollar = 1; }
//
//	char *temp = NULL;
//	if (NULL == (temp = malloc(LINE_LENGTH * sizeof(char) + 1)))
//		exit(1);
//
//	strcpy(temp, buf);
//
//	char *p = strtok(temp, "$$$");
//
//	if (dollar) {
//		while (p != NULL && *p != '\n' && i < iter)
//		{
//			//array[i++] = p;
//			p = strtok(NULL, "$$$");
//			i++;
//		}
//		if (p != NULL)
//		{
//
//			trimLeading(p);
//			trimTrailing(p);
//		}
//	}
//
//	else
//		p = strtok(p, "\n");
//
//	//strcpy(buf, temp);
//	//free(p);
//	return p;
//}
/**
 * Remove trailing white space characters from string
 */
void trimTrailing(char * str)
{
	int index, i;

	/* Set default index */
	index = -1;

	/* Find last index of non-white space character */
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] != ' ' && str[i] != '\t' && str[i] != '\n')
		{
			index = i;
		}

		i++;
	}

	/* Mark next character to last non-white space character as NULL */
	str[index + 1] = '\0';
}
void trimLeading(char * str)
{
	int index, i, j;

	index = 0;

	/* Find last index of whitespace character */
	while (str[index] == ' ' || str[index] == '\t' || str[index] == '\n' || str[index] == NULL)
	{
		index++;
	}


	if (index != 0)
	{
		/* Shit all trailing characters to its left */
		i = 0;
		while (str[i + index] != '\0')
		{
			str[i] = str[i + index];
			i++;
		}
		str[i] = '\0'; // Make sure that string is NULL terminated
	}
}
