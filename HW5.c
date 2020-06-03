#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define _CRT_SECURE_NO_WARNINGS
# define NAME_LENGTH 200
# define LINE_LENGTH 400

char *readLine(FILE *fPtrRead, char tav);
int rename_func(HW_component* list, char oldname[NAME_LENGTH], char newname[NAME_LENGTH]);
int returnd_from_cos_func();
int production_func();
int fatal_func();
int fire_func();
char *split(char *buf);
HW_component *createinlist(char *name, int copynum, int grade, HW_component *newlist);
HW_component *add_cmp(HW_component *head, HW_component *cmp);
HW_component* new_cmp(char *name, int copynum, int grade);
void free_list(HW_component *head);
// define struct
typedef struct hw_component
{
	char name[NAME_LENGTH];
	int copies;
	struct hw_component *next;
}HW_component;


int rename_func(HW_component* list, char oldname[NAME_LENGTH], char newname[NAME_LENGTH])
{
	HW_component* nodetochange = NULL;
	nodetochange = find(list, oldname);
	if (nodetochange != NULL)
	{
		strcpy(nodetochange->name, newname);
	}
	sort_alpha(list);
}
int returnd_from_cos_func()
{

}
int production_func()
{

}
int fatal_func()
{

}
int fire_func()
{

}

int main(int argc, char* argv[])
{
	FILE	*fPtrRead = NULL,
		*fPtrWrite = NULL;
	char	tav = '0';
	char *nextline = NULL;
	char *laststring = "Finalize";
	fPtrRead = fopen("input.txt", "r");//update file paths
	fPtrWrite = fopen("output.txt", "w");
	if (fPtrRead == NULL || fPtrWrite == NULL) { printf("File did not open. Exit..\n"); }

	fscanf(fPtrRead, "%c", &tav);
	char *nextorder = NULL;
	nextline = readLine(fPtrRead, tav);
	nextorder = split(readLine)[0];
	while (!feof(fPtrRead))
	{

		if (strcmp(nextorder, "Initialize") == 0)
		{
			nextline = readLine(fPtrRead, tav);
			nextorder = split(readLine)[0];
			continue;
			// do something
		}
		else if (strcmp(nextorder, "Finalize") == 0)
		{
			//print a sorted list to the components file by format $$$
			//free memory
			//free_list();
			break;
			// do something else
		}
		else if (strcmp(nextorder, "Rename") == 0)
		{
			char oldname[NAME_LENGTH];//get from file
			char newname[NAME_LENGTH];
			rename(oldname,newname);
			// do something else
		}
		else if (strcmp(nextorder, "Returned_from_customer") == 0)
		{
			// do something else
		}
		else if (strcmp(nextorder, "Production") == 0)
		{
			// do something else
		}
		else if (strcmp(nextorder, "Fatal_malfunction") == 0)
		{
			// do something else
		}
		else if (strcmp(nextorder, "Fire") == 0)
		{
			// do something else
		}
		/* more else if clauses */
		else /* default: */
		{
			break;
		}

		nextline = readLine(fPtrRead, fPtrWrite, tav);
		nextorder = split(readLine)[0];

	}
	fclose(fPtrRead);
	fclose(fPtrWrite);
}

char *readLine(FILE *fPtrRead, char tav)
{
	char *temp = NULL;
	if (NULL == (temp = malloc(LINE_LENGTH * sizeof(char) + 1)))
		exit(1);
	int len = 0;
	while (tav != '\n' && !feof(fPtrRead) && len < LINE_LENGTH)
	{
		temp[len] += tav;
		fscanf(fPtrRead, "%c", &tav);
		len++;
	}
	return temp;
}

HW_component* sort_alpha(HW_component *head)
{
	HW_component *iter = head, *prev = NULL;
	if (head == NULL)
		return NULL;
	for (HW_component *iter = head; iter != NULL; iter = iter->next) {
		prev = iter; iter = iter->next;
		while (iter != NULL)
		{

			prev->next = iter->next;
			add_and_sort_alpha(head, iter);
			prev = iter;
			iter = iter->next;
		}
		return head;
	}

}
HW_component* add_and_sort_alpha(HW_component *head, HW_component *new_node) {
	HW_component* iter, *prev = NULL;
	//HW_component* new_node = create_node(data);

	/* incomplete, must check for failure */
	if (head == NULL)
		return new_node;

	if (strcmp(new_node->name,head->name)<0) {
		new_node->next = head;
		return new_node;
	}

	iter = head;
	while (iter != NULL && strcmp(new_node->name, iter->name) >= 0) {
		prev = iter;
		iter = iter->next;
	}

	prev->next = new_node;
	new_node->next = iter;

	return head;
}

HW_component *delete(HW_component *head,  char *val)
{
	HW_component *iter = head, *prev = NULL;

	if (head == NULL)
		return head;

	if (head->name == val)
	{
		iter = head->next;
		free(head);
		return iter;
	}
	prev = iter; iter = iter->next;
	while (iter != NULL)
	{
		if (iter->name == val)
		{
			prev->next = iter->next;
			free(iter);
			break;
		}
		prev = iter;
		iter = iter->next;
	}
	return head;
}

HW_component* find(HW_component *head, char *val) {
	while (head != NULL && strcmp(head->name,val)!=0)
		head = head->next;    
	return head;
}

/* Free a list of comps */
void free_list(HW_component *head)
{
	if (head != NULL)
	{
		free_list(head->next);
		free(head);
	}
}

/* Allocate a new comps */
HW_component* new_cmp(char *name, int copynum, int grade)
{
	HW_component *std = NULL;

	std = (HW_component*)malloc(sizeof(HW_component));
	if (std == NULL)
	{
		printf("Memory allocation error!\n");
		return NULL;
	}

	strcpy(std->name, name);
	strcpy(std->copies, copynum);
	std->next = NULL;

	return std;
}
HW_component *add_cmp(HW_component *head, HW_component *cmp)
{
	HW_component *tail;
	if (cmp == NULL)
		return NULL;

	if (head == NULL)
		return cmp;

	tail = head;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = cmp;

	return head;
}

HW_component *createinlist(char *name, int copynum, int grade, HW_component *newlist)
{
	return add_cmp(newlist,new_cmp(name, copynum, grade));
}

char *split(char *buf)
{
	int i = 0;
	char *p = strtok(buf, "$$$");
	char *array[LINE_LENGTH];

	while (p != NULL && *p !='\n')
	{
		array[i++] = p;
		p = strtok(NULL, "$$$");
	}

	return array;
}
