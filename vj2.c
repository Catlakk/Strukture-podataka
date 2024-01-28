/*
Definirati strukturu osoba(ime, prezime, godina roðenja) i napisati program koji :
A.dinamièki dodaje novi element na poèetak liste,
B.ispisuje listu,
C.dinamièki dodaje novi element na kraj liste,
D.pronalazi element u listi(po prezimenu),
E.briše odreðeni element iz liste,
U zadatku se ne smiju koristiti globalne varijable. */

/*
Prethodnom zadatku dodati funkcije :
A.dinamièki dodaje novi element iza odreðenog elementa,
B.dinamièki dodaje novi element ispred odreðenog elementa,
C.sortira listu po prezimenima osoba,
D.upisuje listu u datoteku,
E.èita listu iz datoteke. */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define MAX_SIZE 50
#define EXIT_FILE_ERROR -1
#define SCANF_ERROR -2
#define MALLOC_ERROR -3

struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
}Person;

Position createPerson();
int addToTheBeginning(Position);
int printList(Position);
int addToTheEnd(Position);
Position findPerson(Position, char*);
int printPerson(Position);
int deletePerson(Position, char*);
int addBehind(Position, char*);
int addInFront(Position, char*);
Position findPreviousPerson(Position, char*);
int writeList(Position);
int readList(Position);
int deleteList(Position);

int main() {
	char menu = 0;
	char surname[MAX_SIZE] = { 0 };
	Person head = { .name = {0}, .surname = {0}, .birthYear = 0, .next = NULL };


	printf("a - add to the beginning\nb - print list\nc - add to the end\n d - find person\ne - delete person\n");
	printf("f - add behind\ng - add in front\nh - write list into file\ni - read list from file\n");

	do {
		printf("\nChoose: ");
		if (scanf(" %c", &menu) != 1)
			return SCANF_ERROR;

		switch (menu)
		{
		case 'a':
			addToTheBeginning(&head);
			break;

		case 'b':
			printList(head.next);
			break;

		case 'c':
			addToTheEnd(&head);
			break;

		case 'd':
			if (scanf(" %s", &surname) != 1)
				return SCANF_ERROR;

			if (findPerson(head.next, surname))
				printPerson(findPerson(head.next, surname));
			else
				printf("Not found!\n");
			break;

		case 'e':
			if (scanf(" %s", &surname) != 1)
				return SCANF_ERROR;
			deletePerson(&head, surname);
			break;

		case 'f':
			if (scanf(" %s", &surname) != 1)
				return SCANF_ERROR;
			addBehind(&head, surname);
			break;

		case 'g':
			if (scanf(" %s", &surname) != 1)
				return SCANF_ERROR;
			addInFront(&head, surname);
			break;

		case 'h':
			writeList(head.name);
			break;

		case 'i':
			readList(head.next);
			break;

		default:
			break;
		}

	} while (menu = '0');

	return EXIT_SUCCESS;
}

Position createPerson() {
	Position create = NULL;
	create = (Position)malloc(sizeof(Person));

	if (!create)
		return NULL;

	printf("Name: ");
	if (scanf(" %s", create->name) != 1)
		return SCANF_ERROR;

	printf("\tSurname: ");
	if (scanf(" %s", create->surname) != 1)
		return SCANF_ERROR;

	printf("\tBirth year: ");
	if (scanf(" %d", &create->birthYear) != 1)
		return SCANF_ERROR;

	return create;
}

int addToTheBeginning(Position head) {
	Position newPerson = NULL;
	newPerson = createPerson();
	if (!newPerson) {
		printf("Malloc error!\n");
		return MALLOC_ERROR;
	}
	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int printPerson(Position counter) {
	printf(" %s %s %d\n", counter->name, counter->surname, counter->birthYear);
	return EXIT_SUCCESS;
}

int printList(Position counter) {

	while (counter != NULL) {
		printPerson(counter);
		counter = counter->next;
	}
	printf("print of the list done");
}

int addToTheEnd(Position head) {
	Position newPerson = NULL;
	newPerson = createPerson;
	if (!newPerson) {
		printf("Malloc error!\n");
		return MALLOC_ERROR;
	}

	while (head->next != NULL)
		head = head->next;

	newPerson->next = head->next;
	head->next = head;

	return EXIT_SUCCESS;
}

Position findPerson(Position counter, char* searchBy) {
	while (counter != NULL && strcmp(counter->next, searchBy))
		counter = counter->next;
	return counter;
}

Position findPreviousPerson(Position counter, char* searchBy) {
	while (counter->next != NULL && strcmp(counter->next, searchBy))
		counter = counter->next;

	if (counter->next == NULL)
		return NULL;

	return counter;
}

int deletePerson(Position previous, char* searchBy) {
	Position head = NULL, temp = NULL;
	head = findPreviousPerson(previous, searchBy);

	if (head != NULL) {
		temp = head->next;
		head->next = temp->next;
		free(temp);
	}
	else
		printf("Not found!\n");

	return EXIT_SUCCESS;
}

int addBehind(Position previous, char* searchBy) {
	Position newPerson = NULL, head = NULL;

	head = findPerson(previous, searchBy);
	newPerson = createPerson();

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int addInFront(Position previous, char* searchBy) {
	Position newPerson = NULL, head = NULL;

	head = findPreviousPerson(previous, searchBy);
	newPerson = createPerson();

	newPerson->next = head->next;
	head->next = newPerson;

	return EXIT_SUCCESS;
}

int deleteList(Position head) {
	Position temp = NULL;

	while (head->next != NULL) {
		temp = head->next;
		head->next = temp->next;
	}
	free(temp);
	return EXIT_SUCCESS;
}

int writeList(Position head) {
	FILE* filePointer = NULL;
	filePointer = fopen("students.txt", "w");

	if (filePointer == NULL) {
		printf("file not found!");
		return EXIT_FILE_ERROR;
	}

	while (head != NULL) {
		fprintf(filePointer, "%s %s %d", head->name, head->surname, head->birthYear);
		head = head->next;
	}

	fclose(filePointer);
	return EXIT_SUCCESS;
}

int readLIst(Position head) {
	FILE* filePointer = NULL;
	Position counter = NULL, previous = NULL;
	filePointer = fopen("students.txt", "r");

	if (filePointer == NULL) {
		printf("file not found!");
		return EXIT_FILE_ERROR;
	}

	deleteList(head);
	previous = head;

	while (!feof(filePointer))
	{
		counter = (Position)malloc(sizeof(Person));
		if (!counter) {
			printf("malloc error!");
			return MALLOC_ERROR;
		}
		if (fscanf(filePointer, " %s %s %d", counter->name, counter->surname, &counter->birthYear) != 3)
			return SCANF_ERROR;

		counter->next = previous->next;
		previous->next = counter;

		previous = counter;
	}
	fclose(filePointer);

	return EXIT_SUCCESS;
}
