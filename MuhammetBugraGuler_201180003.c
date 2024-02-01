// Name and Surname: Muhammet Bugra Guler --- Number: 201180003 
// Sort linked list by name and gender

#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Define string library for use strcmp function.

struct Student { // Create struct
	char name[50];
	char gender;
	struct Student *next;
};

struct Student *insertNode(char *name, char gender, struct Student *list) { // Insert node function for insert new variables.
	struct Student *s;
	s = malloc (sizeof (struct Student)); // //Allocate memory for node (malloc operation)
	if (s == NULL) {
		printf("Memory allocation failed.");
		return list;
	}
	else {
		strcpy(s->name, name);
		s->gender = gender;
		s->next = list; // List is the start of the list.
		list = s;
		return list;
	}
}

// Define gender sort function help with this site: https://www.interviewkickstart.com/problems/sort-list
struct Student *sortGender(struct Student *list, struct Student *current) { // This function sorting to bring female first.
	struct Student *temp; // create Student temp pointer
	if (list == NULL || list->gender >= current->gender) { // Related conditions are checked.
		current->next = list;
		list = current;
	}
	else { // Else command runs if conditions are not met.
		temp = list;
		while (temp->next != NULL && temp->next->gender <= current->gender) {
			temp = temp->next;
		}
		current->next = temp->next;
		temp->next = current;
	}
	return list; // Returns the sorted list.
}

// Define name sort function help with this site: https://www.interviewkickstart.com/problems/sort-list
struct Student *sortName(struct Student *list, struct Student *current) { // This function sorts in reverse alphabetical order.
	struct Student *temp; // create Student temp pointer
	if (list == NULL || strcmp(list->name, current->name) < 0) { // Related conditions are checked.
		current->next = list;
		list = current;
	}
	else { // Else command runs if conditions are not met.
		temp = list;
		while (temp->next != NULL && strcmp(temp->next->name, current->name) > 0) { // strcmp function is used for comparison.
			temp = temp->next;
		}
		current->next = temp->next;
		temp->next = current;
	}
	return list; // Returns the sorted list.
}

struct Student *sortList(struct Student *list) {
	struct Student *currentName, *currentGender, *next, *tempName, *tempGender; // Creating an Initial Temp Node Variables.
	tempName = NULL;
	tempGender = NULL;
	for (currentName = list; currentName != NULL; currentName = next) { // First the name sort function works and is sorted in alphabetical order.
	    next = currentName->next;
		tempName = sortName(tempName, currentName); // Call name sort function.
	}
	currentGender = tempName;
	for (currentGender = tempName; currentGender != NULL; currentGender = next) { // Then sorted by gender.
		next = currentGender->next;
		tempGender = sortGender(tempGender, currentGender); // Call gender sort function.
	}
	list = tempGender;
	return list; // Returns the sorted list.
}

void printList(struct Student *list) { // Printing function
	while (list != NULL) {
		printf("%s\t%c\n", list->name, list->gender);
		list = list->next;
	}
}

void main() {
    struct Student *head = NULL; // Creating an Initial Node Variable
	head = insertNode("Cenk", 'M', head); // Call to functions
    head = insertNode("Ceyda", 'F', head);
    head = insertNode("Esra", 'F', head);
    head = insertNode("Okan", 'M', head);
    head = insertNode("Tugce", 'F', head);
    head = insertNode("Mehmet", 'M', head);
    head = insertNode("Ayse", 'F', head);
    head = insertNode("Merve", 'F', head);
    head = insertNode("Sedat", 'M', head);
    head = insertNode("Ahmet", 'M', head);
	head = sortList(head); // Call to sorting function
	printList(head);	// Call to print function
}
