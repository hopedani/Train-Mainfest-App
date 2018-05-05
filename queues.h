/*
  Name: Paul van Roosendaal and Daniel Hope
  Date: March 28, 2018
  Filename: project_queueImplementation.c
  Description:
  
  	Main Method for part B. Queue Implementation
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_INPUT 20

//Create passenger structure with a self referencing pointer
struct passenger{
	int ticketnumber;
	char name[20];
	float price;
	struct passenger *nextPtr;
};

typedef struct passenger Passenger;
typedef Passenger *PassengerPtr;

//Counter to ensure unique ticket numbers
int currTicketNum = 0;

//Prototypes
void printQueue(PassengerPtr passPtr);

int isEmpty(PassengerPtr hPtr);

void enqueue(PassengerPtr *hPtr, PassengerPtr *tPtr, char name[], float price);

void dequeue (PassengerPtr *hPtr, PassengerPtr *tPtr);

void printMenu(void);

void top(PassengerPtr hPtr);

void tail(PassengerPtr tPtr);
void queueMain();

void queueMain(){

//declare required variables to update the queue
    PassengerPtr hPtr = NULL;
    PassengerPtr tPtr = NULL;
    unsigned int choice;
    char name[20];
    float price;
    
    int valid = 0;

    char sPrice[11];
    char sChoice[MAX_INPUT];

//Print 'decorative title'
	puts("------------------------------------------------------");
	puts("------------------------------------------------------");
	puts("               Grand Central Station");
	puts("             Passenger Manifest System");
    puts("------------------------------------------------------");
	puts("------------------------------------------------------\n");
 //Print menu and wait for user input  
    printMenu();
    fgets(sChoice, MAX_INPUT, stdin);
    puts("------------------------------------------------------");
	puts("------------------------------------------------------\n");
//Convert user choice from a string to an int	
    choice = (int)strtol(sChoice, NULL, 10);

//While loop for program begins	
    while(choice != 6) {
    
    //switch statement begins
       switch(choice) {
       //Display the head of the queue
        case 1:
            top(hPtr);
			puts("------------------------------------------------------\n");
            break;
        //Display the tail of the queye
        case 2:
            tail(tPtr);
            puts("------------------------------------------------------\n");
			break;
			
		//Add a node to the queue (passenger onto the train)
        case 3:
        //Request user input (name, and price)
            printf("Please enter the passenger name\n(Maximum of 20 letters)\n*REQUIRED TO CONTINUE*: \n");
	    valid = 0;
	    while (fgets(name, 20, stdin)){
    		if (!isspace(name[0]))
				break;
		}
		
         printf("Please enter the ticket price\n(Should be a positive number, under 1 million): $");
	    while(valid != 1){
            fgets(sPrice, 11, stdin);
            price = strtof(sPrice, NULL);
            
            //Validate price is a positive number
	    	if(price <= 0) {
		      puts("Please re-enter a ticket price \n (It should be more than 0 dollars and less than 1 million): $");
		      valid = 0;
		    } else {
		      valid = 1;
		    }
		  }
            enqueue(&hPtr, &tPtr, name, price);
            puts("------------------------------------------------------\n");
            printQueue(hPtr);
            puts("------------------------------------------------------\n");
            break;
            
        //Remove the first node in the queue
        case 4:
            dequeue(&hPtr, &tPtr);
            puts("------------------------------------------------------\n");
            printQueue(hPtr);
            puts("------------------------------------------------------\n");
            break;
            
        //Display all data in the queue
        case 5:
            printQueue(hPtr);
            puts("------------------------------------------------------\n");
            break;
            
        //Displays error message in case of wrong input
        default:
            printf("Oh so sorry, that must have been a typo... \nPlease try entering your choice again, thank you so much.\n");
            break;
        }
        
        //Repeat the display of the menu allowing user to make another choice
        puts("------------------------------------------------------");
		puts("------------------------------------------------------\n");
        printMenu();
        fgets(sChoice, MAX_INPUT, stdin);
        puts("------------------------------------------------------");
		puts("------------------------------------------------------\n");
    	choice = (int)strtol(sChoice, NULL, 10);
    }
	//Exit message
    printf("Thank you for using our program. \nIt was a pleasure serving you!\n");
    puts("------------------------------------------------------");
    puts("------------------------------------------------------\n");

}

//Functions

	//printMenu, prints the menu options
	
	void printMenu(void)
	{
		puts("Please select an option from the list below\n\n"
			 "       1. View Details (First on the train)\n"
			 "       2. View Details (Last on the Train)\n"
			 "       3. Embark New Passenger\n"
			 "       4. Disembark First Person on the Train\n"
			 "       5. View Train Manifest\n"
			 "       6. Exit the program\n"
			  );	 
	}
	
	//isEmpty function, checks if the queue is empty. Prints 1 if true.
	
	int isEmpty(PassengerPtr hPtr)
	{
		return hPtr == NULL;
	}
	
	
	//Enqueue function, adds a new node to the queue
	
	void enqueue(PassengerPtr *hPtr, PassengerPtr *tPtr, char name[], float price)
	{
		PassengerPtr newPtr = malloc (sizeof(Passenger));
		
		if (newPtr != NULL)
		{
			newPtr-> price = price;
			strcpy(newPtr-> name, name);
			currTicketNum++;
			newPtr-> ticketnumber = currTicketNum;
			newPtr->nextPtr = NULL;
			printf("\n\nNew passenger embarked the train...\n TicketNumber: %06d\n Name: %s\n Price: $%6.2f\n\n", currTicketNum, name, price);
		
		if (isEmpty(*hPtr) )
			{
				*hPtr = newPtr;
			}
		 	 else
		 	 {
		  		(*tPtr)->nextPtr = newPtr;
		  	 }
		  	 
		  	 *tPtr = newPtr;
		  	 
		}
		else
		{
			puts ("Sorry, there are no more available seats\n");
		}
	}


	//Function dequeue, removes the first node in the queue
	void dequeue (PassengerPtr *hPtr, PassengerPtr *tPtr)
	{
		
		if (*hPtr == NULL){
			return;
		}
		
		PassengerPtr tempPtr;
		char name[20];
		strcpy (name, (*hPtr)->name);
		tempPtr = *hPtr;
		*hPtr = (*hPtr)->nextPtr;
		
		if (*hPtr == NULL)
		{
		 *tPtr == NULL;
		}
		
		printf ("Passenger %s has disembarked the train\n\n", tempPtr->name);
		currTicketNum = currTicketNum - 1;
		free(tempPtr);
		
		
	}
	
	//Function printQueue, prints all data in the queue

		void printQueue(PassengerPtr passPtr)
		{
			if (passPtr == NULL)
			{
				puts ("Nobody on this train, manifest is empty\n");
			}
			
			else
			{
				puts ("The current passengers on the train are: \n");
				
				while (passPtr != NULL)
				{
					printf ("Ticket Number: %06d\nPassenger Name: %s\nTicket Price: $ %4.2f\n\n ~*~\n\n", passPtr->ticketnumber, passPtr->name, passPtr->price);
					
					passPtr = passPtr -> nextPtr;
				}
			}
		}
		
		//Function display top node of the queue
		
		void top (PassengerPtr hPtr)
		{
			if (hPtr != NULL)
			{
				printf ("The first person on the train is: %s\n\n", hPtr->name);
			}
			else
			{
				puts ("This train is empty\n\n");
			}
		}
		
		void tail (PassengerPtr tPtr)
		{
			if (tPtr != NULL)
			{
				printf("The last person on the train is: %s\n\n", tPtr->name);
			}
			else
			{
				puts ("This train is empty\n\n");
			}
		}
		
 