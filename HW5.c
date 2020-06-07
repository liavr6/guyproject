
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
char *split(char *buf,int iter);
HW_component *createinlist(char *name, int copynum, HW_component *newlist);
HW_component *add_cmp(HW_component *head, HW_component *cmp);
HW_component *new_cmp(char *name, int copynum);
void free_list(HW_component *head);
HW_component* find(HW_component *head, char *val);
HW_component* sort_alpha(HW_component *head);
HW_component* add_and_sort_alpha(HW_component *head, HW_component *new_node);
void printlisttofile(HW_component *list, FILE *fPtrWrite, int size);

int main(int argc, char* argv[])
{
	FILE	*orderfileread = NULL,*fPtrWrite = NULL,*compfileread = NULL;
	HW_component *compnodelist = NULL;
	char	tav = '0';
	char *nextline = NULL;
	//char orderfile = argv[2], compfile = argv[1], fPtr = argv[3];
	char orderfile[100] = "C:\\Users\\Liav\\Desktop\\txtfiles\\actions.txt";
	char compfile[100] = "C:\\Users\\Liav\\Desktop\\txtfiles\\hw_components.txt";
	char fPtr[100] = "C:\\Users\\Liav\\Desktop\\txtfiles\\updated_components.txt";
	orderfileread = fopen(orderfile, "r");
	compfileread = fopen(compfile, "r");
	fPtrWrite = fopen(fPtr, "w");
	if (orderfileread == NULL || fPtrWrite == NULL) { printf("File did not open. Exit..\n"); }

	//fscanf(orderfileread, "%c", &tav);
	char *nextorder = NULL;
	nextline = readLine(orderfileread, tav);
	nextorder = split(nextline,1);
	int linecounter = 0;
	while (!feof(orderfileread))
	{
		linecounter++;
		if (strcmp(nextorder, "Initialize") == 0)
		{
			char *nextname = NULL;
			int nextcopies = 0;
			nextline = readLine(compfileread, tav);
			while (nextline !=NULL)
			{
				if (NULL == (nextname = malloc(LINE_LENGTH * sizeof(char) + 1)))
					exit(1);
				strcpy(nextname,split(nextline,0));////////////////////////check if 0 and 1
				nextcopies = atoi(split(nextline,1));
				nextline = readLine(compfileread, tav);
				createinlist(nextname, nextcopies, compnodelist);
			}
			continue;///////////////break?/////////////////////
			// do something
		}
		else if (strcmp(nextorder, "Finalize") == 0)
		{
			printlisttofile(compnodelist, fPtrWrite, linecounter);
			free_list(compnodelist);
			break;
		}
		else if (strcmp(nextorder, "Rename") == 0)
		{
			char oldname[NAME_LENGTH];
			strcpy(oldname, split(nextline,2));
			char newname[NAME_LENGTH];/////////check this
			strcpy(newname, split(nextline,3));
			rename(oldname, newname);
			// do something else
		}
		else if (strcmp(nextorder, "Returned_from_customer") == 0)
		{
			char name[NAME_LENGTH];
			strcpy(name, split(nextline,2));
			int copiestoreturn= atoi(split(nextline,3));
			returnd_from_cos_func(compnodelist,name, copiestoreturn);
			// do something else
		}
		else if (strcmp(nextorder, "Production") == 0)
		{
			char name[NAME_LENGTH];
			strcpy(name, split(nextline,2));
			int copiestoreturn = atoi(split(nextline,3));
			production_func(compnodelist, name, copiestoreturn);
			// do something else
		}
		else if (strcmp(nextorder, "Fatal_malfunction") == 0)
		{
			char name[NAME_LENGTH];
			strcpy(name, split(nextline,2));
			int mal_num = atoi(split(nextline,3));
			fatal_func(compnodelist, name, mal_num);
		}
		else if (strcmp(nextorder, "Fire") == 0)
		{
			char name[NAME_LENGTH];
			strcpy(name, split(nextline,2));
			int mal_num = atoi(split(nextline,3));
			fire_func(compnodelist, name, mal_num);
		}
		/* more else if clauses */
		else /* default: */
		{
			break;
		}

		//nextline = readLine(orderfileread, fPtrWrite, tav);
		nextline = readLine(orderfileread, tav);
		nextorder = split(nextline,1);

	}
	fclose(orderfileread);
	fclose(compfileread);
	fclose(fPtrWrite);
}

int rename_func(HW_component *list, char oldname[NAME_LENGTH], char newname[NAME_LENGTH])
{
	HW_component *nodetochange = NULL;
	nodetochange = find(list, oldname);
	if (nodetochange != NULL)
	{
		strcpy(nodetochange->name, newname);
	}
	sort_alpha(list);
	return 0;
}
int returnd_from_cos_func(HW_component *list,char name[NAME_LENGTH], int copiestoreturn)
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
	sort_alpha(list);
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
			nodetochange->copies = nodetochange->copies - mal_num;
	}
}
int fire_func(HW_component *list, char name[NAME_LENGTH], int mal_num)
{
	fatal_func(list, name, mal_num);
}

char *readLine(FILE *fPtrRead, char tav)
{
	char *temp = NULL;

	if (NULL == (temp = malloc(LINE_LENGTH * sizeof(char) + 1)))
		exit(1);
	int len = 0;
	while (tav != '\n' && !feof(fPtrRead) && len < LINE_LENGTH)
	{
		fscanf(fPtrRead, "%c", &tav);
		temp[len] = tav;
		len++;
	}
	return temp;
}


void printlisttofile(HW_component *list, FILE *fPtrWrite,int size)
{
	char *temp = NULL;
	char formated[LINE_LENGTH] = "";
	if (NULL == (temp = malloc(size * LINE_LENGTH * sizeof(char) + 1)))
		exit(1);
	for (HW_component *iter = list; iter != NULL; iter = iter->next)
	{
		sprintf(formated,"\n%s $$$ %d", iter->name, iter->copies);
		strcat(temp, formated);
	}
	strcat(temp, '\0');
	fprintf(fPtrWrite, "%s", temp) ;
	fclose(fPtrWrite);

}
HW_component* sort_alpha(HW_component *head)
{
	HW_component *iter = head, *prev = NULL;
	if (head == NULL)
		return NULL;
	for (HW_component *iter = head; iter != NULL; iter = iter->next)
	{
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
HW_component* new_cmp(char *name, int copynum)
{
	HW_component *std = NULL;

	if(NULL==(std = (HW_component*)malloc(sizeof(HW_component))))
		exit(1);

	strcpy(std->name, name);
	free(name);
	std->copies= copynum;
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

HW_component *createinlist(char *name, int copynum, HW_component *newlist)
{
	return add_cmp(newlist,new_cmp(name, copynum));
}

char *split(char *buf, int iter)
{
	int i = 0;
	int dollar = 0;
	if (strchr(buf, '$')) { dollar = 1; }

	//char *array[LINE_LENGTH];
	char *temp = NULL;
	char newval[LINE_LENGTH];
	if (NULL == (temp = malloc(LINE_LENGTH * sizeof(char) + 1)))
		exit(1);

	strcpy(temp, buf);

	char *p = strtok(buf, "$$$");

	if (dollar) {
		while (p != NULL && *p != '\n' && i < iter)
		{
			//array[i++] = p;
			p = strtok(NULL, " $$$ ");
			i++;
		}
	}


	p = strtok(p, "\n");
	strcpy(newval, p);
	strcpy(buf, temp);
	free(temp);
	return newval;
}
