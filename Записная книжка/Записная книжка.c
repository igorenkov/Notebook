#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//Структура для даты рождения
struct date {
	int day;
	int month;
	int year;
};
//Структура с информацией о человеке
 typedef struct CPeople {
	char name[20];
	char surname[30];
	char number[25];
	struct date bd;

	struct CPeople *ptr;
} notebook;
//Структура с информацией о записной книжке (указаетель на первый элемент, указатель на последний элемент, длина списка) 
typedef struct CPeople_data {
	notebook *head;
	notebook *tail;
	int size;
} data;
//Функция создания записной книжки
data * create_notebook(void) {
	data *info = (data*)malloc(sizeof(data));

	info->size = 0;
	info->head = NULL;
	info->tail = info->head;

	return info;
}
//Функция добавления пользователя в книжку
void push_in_notebook(data *info) {
	notebook* temp = (notebook*)malloc(sizeof(notebook));
	//Передача информации о пользователе
	printf("Input first person information: \n");
	printf("Name:	");
	gets(temp->name);
	//Проверка на заглавную букву в имени
	if (temp->name[0] >= 'a' && temp->name[0] <= 'z') {
		temp->name[0] = temp->name[0] - 32;
	}
	printf("Surname:	");
	gets(temp->surname);
	//Проверка на заглавную букву в фамилии
	if (temp->surname[0] >= 'a' && temp->surname[0] <= 'z') {
		temp->surname[0] = temp->surname[0] - 32;
	}
	printf("Phone number(like 89930031020):	");
	gets(temp->number);
	printf("Burthday date: \n");
	printf("	Day:		");
	scanf_s("%d", &temp->bd.day);
	getchar();
	printf("	Month:		");
	scanf_s("%d", &temp->bd.month);
	getchar();
	printf("	Year:		");
	scanf_s("%d", &temp->bd.year);
	getchar();
	//Переброс указателя
	temp->ptr = info->head;
	if (info->head == NULL) {
		info->tail = temp;
	}
	info->head = temp;
	info->size++;
}
//Функция чтения пользователей из файла Data.txt
void get_data(data *info) {
	FILE *fp = fopen("Data.txt", "r");
	if (fp == NULL) {
		printf("Can't open the file!\n");
	}
	else {
		while (!feof(fp)) {
			notebook* temp = (notebook*)malloc(sizeof(notebook));
			//Поличение данных из файла
			fgets(temp->name, 20, fp);
			fgets(temp->name, 20, fp);
			temp->name[strlen(temp->name) - 1] = '\0';
			//Проверка на заглавную букву в имени
			if (temp->name[0] >= 'a' && temp->name[0] <= 'z') {
				temp->name[0] = temp->name[0] - 32;
			}
			fgets(temp->surname, 30, fp);
			temp->surname[strlen(temp->surname) - 1] = '\0';
			//Проверка на заглавную букву в фамилии
			if (temp->surname[0] >= 'a' && temp->surname[0] <= 'z') {
				temp->surname[0] = temp->surname[0] - 32;
			}
			fgets(temp->number, 25, fp);
			temp->number[strlen(temp->number) - 1] = '\0';
			fscanf_s(fp, "%d", &temp->bd.day);
			getc(fp);
			fscanf_s(fp, "%d", &temp->bd.month);
			getc(fp);
			fscanf_s(fp, "%d", &temp->bd.year);
			getc(fp);
			getc(fp);
			//Переброс указателя
			temp->ptr = info->head;
			if (info->head == NULL) {
				info->tail = temp;
			}
			info->head = temp;
			info->size++;
		}
	}
	fclose(fp);
}
//Функция удаления пользователя по имени и фамилии
void delete_in_notebook(data *info) {
	char name[20];
	char surname[30];
	notebook *temp = info->head;
	notebook *nextemp = temp->ptr;
	notebook *deltemp;

	printf("Input name of the person you want to delete: \n");
	gets(name);
	printf("Input surname of the person you want to delete: \n");
	gets(surname);
	if ((strcmp(name, temp->name) || strcmp(surname, temp->surname)) && (nextemp != NULL)) {	//Если первый элемент списка не равен искомому и следующий элемент существует
		while (strcmp(name, nextemp->name) || strcmp(surname, nextemp->surname)) {
			temp = temp->ptr;
			nextemp = temp->ptr;
			if (nextemp == NULL) {
				break;
			}
		}

		deltemp = temp->ptr;
		if (deltemp == NULL) {
			printf("Nothing to delete.\n");
		}
		else {
			temp->ptr = deltemp->ptr;
			free(deltemp);
			info->size--;
		}
	}
	else if ((strcmp(name, temp->name) || strcmp(surname, temp->surname)) && (nextemp == NULL)){	//Если первый элемент списка не равен искомому и следующий элемент не существует
		return;
	}
	else {	//Первый элемент списка равен искомому
		info->head = temp->ptr;
		free(temp);
	}

}
//Функция освобождения памяти
void delete_notebook(data *info) {
	notebook *deltemp = info->head;

	while (info->head != NULL) {
		info->head = deltemp->ptr;
		if (info->head == NULL) {
			info->tail = NULL;
		}
		free(deltemp);
		deltemp = info->head;
		info->size--;
	}

	free(info);
}
//Функция вывода книжки в консоль
void show_notebook(data *info) {
	int i = 1;
	notebook *temp = info->head;
	while (temp != NULL) {
		printf("	%d person: \n", i);
		puts(temp->name);
		puts(temp->surname);
		puts(temp->number);
		printf("%d.", temp->bd.day);
		printf("%d.", temp->bd.month);
		printf("%d\n\n", temp->bd.year);

		temp = temp->ptr;
		i++;
	}
}
//Функция записи книжки в файл
void push_to_file(data *info) {
	FILE *fp;
	fp = fopen("Notebook.txt", "w");
	if (fp == NULL) {
		printf("Can't open the file!\n");
	}
	else {
		int i = 1;
		notebook *temp = info->head;
		while (temp != NULL) {
			if (temp == info->head) {	//Для отсутствия отступа у первого элемента
				fprintf(fp, "	%d person: \n", i);
			}
			else {
				fprintf(fp, "\n\n	%d person: \n", i);
			}
			fputs(temp->name, fp);
			fputs("\n", fp);
			fputs(temp->surname, fp);
			fputs("\n", fp);
			fputs(temp->number, fp);
			fputs("\n", fp);
			fprintf(fp, "%d.", temp->bd.day);
			fprintf(fp, "%d.", temp->bd.month);
			fprintf(fp, "%d", temp->bd.year);

			temp = temp->ptr;
			i++;
		}
	}
	fclose(fp);
}
//Функция сравнения по имени
int compare_names(notebook * person) {
	
	int i = 0;
	int booly = 0;

	while (person->name[i] != '\0' && person->ptr->name[i] != '\0') {
		if (person->name[i] < person->ptr->name[i]) {
			booly = 0;
			return booly;
		} else if (person->name[i] > person->ptr->name[i]) {
			booly = 1;
			return booly;
		}
		i++;
	}
	return booly;
}
//функция сравнения по фамилии
int compare_surnames(notebook * person) {
	int i = 0;
	int booly = 0;

	while (person->surname[i] != '\0' && person->ptr->surname[i] != '\0') {
		if (person->surname[i] < person->ptr->surname[i]) {
			booly = 0;
			return booly;
		}
		else if (person->surname[i] > person->ptr->surname[i]) {
			booly = 1;
			return booly;
		}
		i++;
	}
	return booly;
}
//Функция сравнения по фамилии 
int compare_numbers(notebook * person) {
	int i = 0;
	int booly = 0;

	while (person->number[i] != '\0' && person->ptr->number[i] != '\0') {
		if (person->number[i] < person->ptr->number[i]) {
			booly = 0;
			return booly;
		}
		else if (person->number[i] > person->ptr->number[i]) {
			booly = 1;
			return booly;
		}
		i++;
	}
	return booly;
}
//Функция сравнения по датам рождения
int compare_dates(notebook * person) {
	int booly;
	if (person->bd.year < person->ptr->bd.year) {
		booly = 0;
		return booly;
	}
	else if (person->bd.year > person->ptr->bd.year) {
		booly = 1;
		return booly;
	}
	else {
		if (person->bd.month < person->ptr->bd.month) {
			booly = 0;
			return booly;
		}
		else if (person->bd.month > person->ptr->bd.month) {
			booly = 1;
			return booly;
		}
		else {
			if (person->bd.day <= person->ptr->bd.day) {
				booly = 0;
				return booly;
			}
			else if (person->bd.day > person->ptr->bd.day) {
				booly = 1;
				return booly;
			}
		}
	}
}
//Функция возврата 0 (для случая, когда не выбран тип сравнения)
int compare_null(notebook * person) {
	return 0;
}
//Функция сортировки
void sort_in_notebook(data *info) {
	char type;
	notebook *first, *second, *third, *temp;
	int(*operation)(notebook *); //Указатель на выбранный вид сравнения
	printf("Input a catagory:\nN/n - name;\nS/s - surname;\nP/p - phone number;\nD/d - date of burthday;\n	Type of sort: ");
	scanf_s("%c", &type);
	getchar();
	//Выполнение сравнения
	if (type == 'N' || type == 'n') {
		operation = compare_names;
	}
	else if (type == 'S' || type == 's') {
		operation = compare_surnames;
	}
	else if (type == 'P' || type == 'p') {
		operation = compare_numbers;
	}
	else if (type == 'D' || type == 'd') {
		operation = compare_dates;
	}
	else {
		operation = compare_null;
	}
	for (int i = 1; i < info->size; i++) {
		first = NULL;
		second = info->head;
		third = second->ptr;
		for (int j = 1; j < info->size; j++) {
			if (operation(second)) {
				if (second == info->head) {
					info->head = third;
					temp = third->ptr;
					third->ptr = second;
					second->ptr = temp;

					first = info->head;
					second = first->ptr;
					third = second->ptr;
				}
				else {
					first->ptr = third;
					temp = third->ptr;
					third->ptr = second;
					second->ptr = temp;

					first = first->ptr;
					second = first->ptr;
					third = second->ptr;
				}
			}
			else {
				first = second;
				second = third;
				third = second->ptr;
			}
		}
	}


}

int main() {
	data *info;
	info = create_notebook();
	char type;
	//Вопрос о вводе пользователей из файла
	printf("Would you like to take data from file? (y/n)\nYour choice: ");
	scanf_s("%c", &type);
	printf("\n");
	getchar();

	if (type == 'Y' || type == 'y') {
		system("cls");
		get_data(info);
		show_notebook(info);
	}

	do {
		//Ввод типа операции (добавление пользователя, удаление пользователя, сортировка пользователей, выход из программы)
		printf("Input type of the operation: \nA/a - add a new person;\nD/d - delete a person;\nE/e - exit;\nS/s - sort a notebook;\n\n	Type: ");
		scanf_s("%c", &type);
		printf("\n");
		getchar();
		
		if (type == 'A' || type == 'a') {
			push_in_notebook(info);
		}
		else if (type == 'D' || type == 'd') {
			delete_in_notebook(info);
		}
		else if (type == 'S' || type == 's') {
			sort_in_notebook(info);
		}
		else if (type == 'E' || type == 'e') {
			printf("Have a good day!");
		}
		else {
			printf("Try again :)");
		}

		system("cls");

		show_notebook(info);

	} while (type != 'E' && type != 'e');
	
	push_to_file(info);

	delete_notebook(info);

	return 0;
}