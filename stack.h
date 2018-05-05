// Assignment#4 
// Paul van Roosendaal & Dan Hope
// Passengers on a train StackProgam
// March 21, 2018


#include<stdio.h>
#include<stdlib.h>
#include <string.h>

//Create passenger structure with a self referencing pointer
struct spassenger{
	int ticketnumber;
	char name[20];
	float price;
	struct spassenger *nextPtr;
};

//change type definition of struct Passenger and struct passenger pointer
typedef struct spassenger SPassenger;
typedef struct spassenger *SPassengerPtr;

//Method prototypes
SPassengerPtr push(SPassengerPtr topPtr, char name[], float price);
SPassengerPtr pop(SPassengerPtr topPtr);
void topOfStack(SPassengerPtr topPtr);
void printStack(SPassengerPtr topPtr);
int isStackEmpty(SPassengerPtr topPtr);
void instructions();
int isTaken(SPassengerPtr topPtr, int ticketnumber);
void stackMain();

//Start of main method
void stackMain(){

	//Create required variables
	SPassengerPtr stackPtr = NULL;
	int choice;
	int ticketnumber;
	char name[20];
	float price;
	
	//Print instructions and await user choice
	instructions();
	printf("> ");
	scanf("%d", &choice);
	
	//Enter switch case with user choice
	while(choice != 5) {
	   switch(choice) {

		//print the top of the stack
		case 1:
			topOfStack(stackPtr);
			break;

		//enter a new passenger into the stack, request passenger name 
 		// and enter a ticket price
		//run push method and print the stack
		case 2:
			printf("Enter passenger's name: ");
			scanf("%s", name);
			printf("Enter ticket price: $");
			scanf("%f", &price);
			stackPtr = push(stackPtr, name, price);
			printStack(stackPtr);
			break;

		//pop the top ticket from the stack
		//and print thes tack
		case 3:
			stackPtr = pop(stackPtr);
			printStack(stackPtr);
			break;
		//print all elements in the stack
		case 4:
			printStack(stackPtr);
			break;

		//Feedback to user if the option entered is not 1, 2, 3, 4, 5
		default:
			printf("Invalid choice.\n\n");
			break;
		}

		//print the instructions again
		instructions();
	        printf("> ");
		//await user choice
		scanf("%d", &choice);
	}
	
	printf("\n-----------\nApplication Exit\n-----------\n");
	
}

//Push Method (Creates memory space, creates a new passenger structure and adds 
//it to the stack
SPassengerPtr push(SPassengerPtr topPtr, char name[], float price){
	
	
//Declare new Passenger Pointer
	SPassengerPtr newPtr;

//Create memory space the size of the passenger struct
	newPtr = (SPassengerPtr)malloc(sizeof(SPassenger));

//Check if memory was created
	if(newPtr != NULL){ 
 		
//Assign a ticket number to the new Passenger structure	
		if (topPtr == NULL){ //If it is the first element in the stack
			newPtr->ticketnumber = 1;//Ticket# is 1		
		}
		else{//If not the first element, ticket # is the current top
                     // pointer incremented by 1
		newPtr->ticketnumber = (topPtr->ticketnumber) + 1;
		}
		strcpy(newPtr->name, name); //Assign name
		newPtr->price = price; //Assign ticket pirce
		newPtr->nextPtr = topPtr;//Redirect pointers
		topPtr = newPtr;
			
	}else{//If memory was not created output this message
		puts("Memory full. Passenger not added.\n");
	}
	return topPtr;//Return the new top pointer
}

//Pop Function - removes the top element from the stock
SPassengerPtr pop(SPassengerPtr topPtr){
	int popValue; //Declare variable to store the ticketNumber to be popped
	SPassengerPtr tempPtr;//Declare a new temporary passenger pointer
	if(topPtr == NULL){//Check if the stack is empty
		puts("The passenger list is empty\n"); 

	//If not empty
	}else{
		tempPtr = topPtr;//Assign the temporary pointer to equal the top
		popValue = tempPtr->ticketnumber;//Assign Ticket# to popValue
		topPtr = topPtr->nextPtr;//Point the top to the previous item
		free(tempPtr);//Release memory space for the temporary pointer
		printf("\nThe Popped ticket number is %d \n\n", popValue);
	}
	return topPtr;//Return the new top pointer
}

//Function prints the element at the top of the stack
void topOfStack(SPassengerPtr topPtr){
	SPassengerPtr tempPtr = topPtr;
	if(tempPtr == NULL){//Check if stack is empty
		puts("Passenger list is empty");
	}else{	//if not print the values of the first element
		printf("\nTicket# is %d\nPassenger name is %s\nTicket price is $%.2f\n\n", tempPtr->ticketnumber, tempPtr->name, tempPtr->price);
			tempPtr = tempPtr->nextPtr;
	}
}

int isStackEmpty(SPassengerPtr topPtr){
	return topPtr == NULL;
}
//Print the data for every element in the stack
void printStack(SPassengerPtr topPtr){
	SPassengerPtr tempPtr = topPtr;
	if(tempPtr == NULL){//Check if the stack is empty
		puts("Passenger List is Empty");
	}else{
		while(tempPtr != NULL){	//While the next pointer in the stack
                                        // is not null, print the data
			printf("\nTicket# is %d\nPassenger name is %s\nTicket price is %.2f\n\n", tempPtr->ticketnumber, tempPtr->name, tempPtr->price);
			tempPtr = tempPtr->nextPtr;//Update the poiner to the
                                                   // next element
		}
	}
}

void instructions(){
	printf("1: Top\n2: Push\n3: Pop\n4: Print all the data items\n5: Exit Stack Application\n>");
}


