#include <stdio.h>
#include <stdlib.h>
#include <string.h>

# define _CRT_SECURE_NO_WARNINGS
# define NAME_LENGTH 200
# define LINE_LENGTH 400

char *readLine(FILE *fPtrRead, char tav);
int rename_func();
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

int rename_func()
{

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
	nextline = readLine(fPtrRead, fPtrWrite, tav);
	nextorder = split(readLine)[0];
	while (!feof(fPtrRead))
	{
		nextorder = split(readLine)[0];

		if (strcmp(nextorder, "Initialize") == 0)
		{
			continue;
			// do something
		}
		else if (strcmp(nextorder, "Finalize") == 0)
		{
			break;
			// do something else
		}
		else if (strcmp(nextorder, "Rename") == 0)
		{
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
	}
	fclose(fPtrRead);
	fclose(fPtrWrite);
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
