#include <stdio.h>
# define NAME_LENGTH 200
# define LINE_LENGTH 400

char *readLine(FILE *fPtrRead, FILE *fPtrWrite, char tav);
int rename_func();
int returnd_from_cos_func();
int production_func();
int fatal_func();
int fire_func();
HW_component* add_last(char *name, int copy);
HW_component* create_node(char *name, int copy);
//int createlist(char name, int copy);

// define struct
typedef struct hw_component
{
	char name[NAME_LENGTH];
	int copies;
	struct hw_component *next;
}HW_component;

typedef struct node
{
	int data;
	struct node *next;
} node_t;


char *readLine(FILE *fPtrRead, FILE *fPtrWrite, char tav)
{
	char *temp = NULL;
	if (NULL == (temp = malloc(LINE_LENGTH * sizeof(char) + 1)))
		return 1;
	int len = 0;
	while (tav != '\n' && !feof(fPtrRead) && len<LINE_LENGTH)
	{
		temp[len] += tav;
		//fprintf(fPtrWrite, "%c", tav);
		fscanf(fPtrRead, "%c", &tav);
		len++;
	}
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
	nextline = readLine(fPtrRead, fPtrWrite, tav);
	while (!feof(fPtrRead) || strcmp(nextline, laststring)) {
		switch (3)//substring nextline
		{
		case 1:
			add_last(nextline,nextline);//substring here
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:
			
			break;
		case 5:
			
			break;
		case 6:
			

			break;
		default:
			break;
		}
		//readLine(fPtrRead, fPtrWrite, tav);
		//fprintf(fPtrWrite, "\n\n");
		//fscanf(fPtrRead, "%c", &tav);
		nextline = readLine(fPtrRead, fPtrWrite, tav);
	}
	fclose(fPtrRead);
	fclose(fPtrWrite);
}

//int createlist(char *name,int copy)
//{
//	int value = 0;
//	HW_component *list = NULL, *new_node = NULL;
//
//	//printf("enter values (negative to stop)\n");
//	//scanf("%d", &value);
//	while (value >= 0) {
//		new_node = (HW_component*)malloc(sizeof(HW_component));
//		if (new_node == NULL)
//		{ 
//			printf("Fatal error: memory allocation failed!\n");           
//		return 1; 
//		}   
//		
//		strcpy(new_node->name,name);
//		new_node->copies = copy; 
//		new_node->next=list;
//		list = new_node;
//
//		//scanf("%d", &value);
//	}
//
//	/* print the number of input values */
//
//	/* free list */
//	return 0;
//}
HW_component* create_node(char *name, int copy)
{
	int value = 0;
	HW_component *list = NULL, *new_node = NULL;
	new_node = (HW_component*)malloc(sizeof(HW_component));

	node_t *new_node = (node_t*)malloc(sizeof(node_t));
	if (new_node != NULL) {
		strcpy(new_node->name, name);
		new_node->copies = copy;
		new_node->next = list;
	}
	return new_node;
}
HW_component* add_last(char *name, int copy)
{
	HW_component *tail;
	HW_component *list = NULL, *new_node = NULL;

	HW_component *new_node = create_node(name,copy);
	if (new_node == NULL)
		return NULL;

	if (list == NULL)
		return new_node;

	tail = list;
	while (tail->next != NULL)
		tail = tail->next;
	tail->next = new_node;

	return list;
}
