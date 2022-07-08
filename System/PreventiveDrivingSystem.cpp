#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define L 20
#define N 5

struct person** buildArray(int* size);
struct person** increaseArray(struct person* arr[], int* size);
int check_input(int n, char* s);
int check_name(char* str);
void add(struct person* arr[], int size);
void _delete_(struct person* arr[], int size);
void _print_(struct person* arr[], int size);
void shrink(struct person* arr[], int size);
void swap(struct person* a, struct person* b);
char* decoded(unsigned int arr[]);
unsigned int* coded(char* str);
void sort_by_points(struct person* arr[], int size);
void sort_by_names(struct person* arr[], int size);
bool str_greater_than(char* s1, char* s2);



struct person
{
	unsigned int* name;
	int points;
};

void main()
{
	int option = 0;
	struct person** arr;
	char welcome[] = { 
		"####################################\n"
		"Welcome to Driving Prevention System\n"
		"####################################\n" };
	printf("%s", welcome);
	char menu[] = {
		"1.Add Name\n2.Delete\n3.Print\n"
		"4.Increase\n5.Shrink\n6.Sort By Points\n"
		"7.Sort By Names\n8.Exit\nEnter your choice:" };
	int* size = (int*)malloc(sizeof(int));
	arr = buildArray(size);
	do
	{
		printf("%s", menu);
		option = check_input(option, menu);
		if (option == 1)
			add(arr, *size);
		else if (option == 2)
			_delete_(arr, *size);
		else if (option == 3)
			_print_(arr, *size);
		else if (option == 4)
			arr = increaseArray(arr, size);
		else if (option == 5)
			shrink(arr, *size);
		else if (option == 6)
			sort_by_points(arr, *size);
		else if (option == 7)
			sort_by_names(arr, *size);
		printf("\n");
	} while (option != 8);
	for (int i = 0; i < *size; i++)
	{
		if (arr[i] != NULL)
			free(arr[i]->name);
		free(arr[i]);
	}
	free(arr);
	free(size);
}

//6 rows of commands
/*Creates an array of person*/
struct person** buildArray(int* size)
{
	char msg[] = "Enter Number of Participants:\n";
	printf("%s", msg);
	*size = check_input(*size, msg);
	struct person** persons = (struct person**)malloc((*size) * sizeof(struct person*));
	for (int i = 0; i < *size; i++)
	{
		persons[i] = NULL; //Initializing the pointers to zero
	}
	return persons;
}

struct person** increaseArray(struct person* arr[], int* size)
{
	int i = 0;
	char msg[] = {"Enter the number of additional participants you would like to add:\n"};
	printf("%s", msg);
	int add =  check_input(*size, msg);
	struct person** new_persons = (struct person**)malloc(((*size)+add) * sizeof(struct person*));
	for (; i < *size; i++)
	{
		new_persons[i] = arr[i];
	}
	*size += add;
	for (; i < *size; i++) {
		new_persons[i] = NULL;
	}
	printf("The array size Increased!\n");
	return new_persons;
}

//5 rows of commands
/*Checks if input type matches what is required*/
int check_input(int n, char* msg)
{
	while (!scanf("%d", &n))
	{
		getchar();
		system("cls");
		printf("$$$ - ERROR INPUT! - $$$\n");
		printf("%s", msg);
	}
	return n;
}

//4 rows of commands
/*Checks if the name is valid*/
int check_name(char* str)
{
	for (int i = 0; i < strlen(str); i++)
	{
		if (((str[i] < 'a') || (str[i] > 'z')) && (str[i] != '-'))
		{
			printf("Invalid Name\n");
			return 1;
		}
	}
	return 0;
}

//13 rows of commands
/*Adds a name and points to person*/
void add(struct person* arr[], int size)
{
	getchar();
	int i = 0;
	char msg[] = "Enter Points:\n";
	for (i = 0; i < size; i++)
	{
		if (arr[i] == NULL)
		{
			char* str = (char*)malloc(L * sizeof(char));
			do
			{
				printf("Enter a Name:\n");
				gets_s(str, L * sizeof(char));
			} while (check_name(str));
			arr[i] = (struct person*)malloc(sizeof(struct person));
			arr[i]->name = coded(str);
			printf("%s", msg);
			arr[i]->points = check_input(i, msg);
			free(str);
			break;
		}
	}
	if (i == size)
		printf("The array is full!\n");
}

//17 rows of commands
/*Delete person from array*/
void _delete_(struct person* arr[], int size)
{
	getchar();
	int i = 0;
	char* str_dec;
	char* name = (char*)malloc(L * sizeof(char));
	do
	{
		printf("Enter a Name to delete: ");
		gets_s(name, L * sizeof(char));
	} while (check_name(name));
	for (i = 0; i < size; i++)
	{
		if (arr[i] == NULL)
			continue;
		str_dec = decoded(arr[i]->name);
		if (0 == strcmp(str_dec, name))
		{
			printf("%s has been removed from the array!\n", name);
			free(arr[i]->name);
			free(arr[i]);
			free(name);
			free(str_dec);
			arr[i] = NULL;
			break;
		}
		free(str_dec);
	}
	if (i == size)
		printf("The Name does not exist!\n");
}

//5 rows of commands
/*Print All the data in person array(names and points)*/
void _print_(struct person* arr[], int size)
{
	int cnt = 0;
	for (int i = 0; i < size; i++)
	{
		if (arr[i] == NULL)
		{
			cnt++;
			continue;
		}
		printf("[%d]Name: %s      Points: %d\n", i + 1,
			decoded(arr[i]->name), arr[i]->points);
	}
	if (cnt == size)
		printf("The array is ampty!\n");
}

//11 rows of commands
/*Minimizes array spaces*/
void shrink(struct person* arr[], int size)
{
	for (int i = 0; i < size; i++)
	{
		int check = 0;
		for (int j = 0; j < size - i; j++)
		{
			if (arr[j] == NULL) //Find the first empty person and put it at the end
			{
				arr[j] = (struct person*)malloc(sizeof(struct person));
				if (arr[size - 1 - i] == NULL)
				{
					arr[size - 1 - i] = (struct person*)malloc(sizeof(struct person));
					check = 1;
				}
				swap(arr[j], arr[size - 1 - i]);
				free(arr[size - 1 - i]);
				arr[size - 1 - i] = NULL;
				if (check == 1)
				{
					free(arr[j]);
					arr[j] = NULL;
				}
				break;
			}
		}
	}
	printf("The array has Shrinked!\n");
}

//4 rows of commands
/*Swap places between two person*/
void swap(struct person* a, struct person* b)
{
	struct person temp = *a;
	temp = *a;
	*a = *b;
	*b = temp;
}

//12 rows of commands
/*Converts an encrypted name to a string*/
char* decoded(unsigned int arr[])
{
	int letter, j = 0;
	char* str = (char*)malloc(L * sizeof(char));
	for (int i = 0; i < N; i++)
	{
		unsigned mask = 0xff000000, mov = 24;
		while (mov != -8)
		{
			letter = arr[i] & mask;
			letter >>= mov;
			mask >>= 8;
			mov -= 8;
			if (letter == '-')
				str[j] = '-';
			else
				str[j] = 'a' + (letter - 'a');
			j++;
		}
	}
	str[strlen(str) + 1] = '\0';
	return str;
}

//13 rows of commands
/*Encrypts name to HEX*/
unsigned int* coded(char* str)
{
	int i = 0, cnt = 0, mov = 24;
	unsigned int letter;
	unsigned int* name = (unsigned int*)calloc(N, sizeof(unsigned int));
	do
	{
		if (cnt != 0)
		{
			if (cnt % 4 == 0)
			{
				i++;
				mov = 24;
			}
			str++;
		}
		letter = (*str);
		letter <<= mov;
		name[i] += letter;
		mov -= 8;
		cnt++;
	} while (*str != 0);
	return name;
}


void sort_by_points(struct person* arr[], int size)
{
	for (int i = 0; i < size; i++) {
		if (arr[i] == NULL)
			continue;
		for (int j = i+1; j < size; j++) {
			if (arr[j] == NULL)
				continue;
			if (arr[i]->points > arr[j]->points)
				swap(arr[i], arr[j]);
		}
	}
	printf("The array has been Sorted by points!\n");
}

void sort_by_names(struct person* arr[], int size)
{
	for (int i = 0; i < size; i++) {
		if (arr[i] == NULL)
			continue;
		for (int j = i + 1; j < size; j++) {
			if (arr[j] == NULL)
				continue;
			if (str_greater_than(decoded(arr[i]->name), decoded(arr[j]->name)))
				swap(arr[i], arr[j]);
		}
	}
	printf("The array has been Sorted by name!\n");
}

bool str_greater_than(char* s1, char* s2)
{
	int i = 0;
	while (s1[i] != NULL && s2[i] != NULL)
	{
		if (s1[i] > s2[i])
			return true;
		else if (s1[i] < s2[i])
			return false;
		i++;
	}
	if (s1[i] == NULL)
		return false;
	return true;
}









