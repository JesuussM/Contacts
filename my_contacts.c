/*
  Program Name: my_contacts.c
  Description: A contact book that you can add/delete/remove/print entries
  Author: Jesus Miranda
  Changes Made: 
	1. Made search isnt case sensitive, returns multiple searches, and lets the user choose which one. 
	2. Created a modify function to modify created entries
	3. Delete method now deletes selected entry
*/

// Includes
#include <stdio.h>   
#include <string.h>
#include <ctype.h>

// Constants
#define MAX 100

struct contact {
   char	name[30];
   int	phone;
   char	email[30];
};

struct contact contactbook[MAX];  // an array of structures with MAX entries
int tail = 0;

void branching(char c);
int insertion();
int modify();
int search();
int delete();
void printall();

void main() {
	char ch = 'i';

	while (ch != 'q') {
		printf("\n");
		printf("Enter your selection\n");
		printf("	i: insert a new entry\n");
		printf("        m: modify an entry\n");
		printf("	d: delete an entry\n");
		printf("	s: search an entry\n");
		printf("	p: print all entries\n");
		printf("	q: quit \n");

		scanf(" %c",&ch);
		branching(ch);
	}
}

void branching(char c) {    // branch to different tasks
	switch(c)  {
		case 'i': insertion(); break;
		case 'm': modify();    break;
		case 's': search();    break;
		case 'd': delete();    break;
		case 'p': printall();  break;
		case 'q': break;
		default : printf("Invalid input %d\n", c); break;
	}
}

int insertion() {    // insert a new entry at the end
	if (tail == MAX) {
		printf("\n");
		printf("There are no more places to insert.\n");
		return -1; 
	}
	else {
		printf("\n");
		printf("Enter name, phone, email:\n");
		scanf("%s", contactbook[tail].name);
		scanf("%d", &contactbook[tail].phone);
		scanf("%s", contactbook[tail].email);
		tail++;
		printf("\n");
		printf("The number of entries = %d\n", tail);
		return 0;
	}
}

// Created Modify method
int modify() {
	// Gets index from search for selected entry
	int chosen = search();
	
	if (chosen != -1) {
		// Overwrites the selected entry with new data
		printf("\n");
                printf("Enter name, phone, email:\n");
                scanf("%s", contactbook[chosen].name);
                scanf("%d", &contactbook[chosen].phone);
                scanf("%s", contactbook[chosen].email);
                printf("The entry was successfully modified!\n");
        }
}

int search() {    // print phone and email via name
	char sname[30]; 
	int  i;
	
	printf("\n");
	printf("Enter the name to be searched for:\n");
	scanf("%s", sname); 	//sname is an array, no &
	printf("\n");
	
	// Turns input to all lowercase
	for (int j = 0; j < strlen(sname); j++) {
        	sname[j] = tolower(sname[j]);
   	}

	int searchCount[MAX];
	int index = 0;

	for (i=0; i<tail; i++) {
       		// Create char array to get the contactbook name to lowercase
		char lowerCaseName[50];
        	strcpy(lowerCaseName, contactbook[i].name);
        	for (int j = 0; j < strlen(lowerCaseName); j++) {
            		lowerCaseName[j] = tolower(lowerCaseName[j]);
        	}

		// Puts index into searchCount
        	if (strcmp(sname, lowerCaseName)== 0) {
            		searchCount[index++] = i;
        	}
    	}
	
	// Prints the search results
    	for (int k = 0; k < index; k++) {
        	printf("index = %d\n", searchCount[k]);
        	printf("name = %s\n", contactbook[searchCount[k]].name);
  		printf("phone = %d\n", contactbook[searchCount[k]].phone);
        	printf("email = %s\n", contactbook[searchCount[k]].email);
		printf("\n");
    	}

	// Asks user to select one
    	if (index > 0) {
        	printf("Select by index which entry you want: \n");
        	scanf("%d", &index);
		printf("\n");
        	printf("You selected:\n");
        	printf("name = %s\n", contactbook[index].name);
        	printf("phone = %d\n", contactbook[index].phone);
        	printf("email = %s\n", contactbook[index].email);
		printf("\n");
    	} else {
        	printf("The name does not exist.\n");
		return -1;
   	}

	return index;
}

int delete() {  	
	int i, k;

	k = search();

	if (k != -1) {
		for (i=k; i<tail; i++) {
			strcpy(contactbook[i].name, contactbook[i+1].name);
			contactbook[i].phone = contactbook[i+1].phone;
			strcpy(contactbook[i].email, contactbook[i+1].email);
		}
		printf("\n");
	 	printf("The index deleted is: %d\n", k);
		tail--;
		return k;
	}
}

void printall() {
	int i;

	for (i=0; i < tail; i++) {
		printf("\n");
		printf("%2d) Name : %s\n", i+1, contactbook[i].name);
		printf("    Phone: %d\n", contactbook[i].phone);
		printf("    Email: %s\n", contactbook[i].email);
	}
}

