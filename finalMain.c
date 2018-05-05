/*
  Name: Dan Hope and Paul van Roosendaal
  Date:
  Filename:
  Description: Train ticket application that "sells" a ticket to the user and allows the user to view who's on the train
               with different data structures i.e. stack, queue, and tree.

/*------------------------
       Trees
--------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include "stack.h"
#include "queues.h"
#include "trees.h"

#define MAXSIZE 20

void printMainMenu();



int main(){

	char sChoice[MAXSIZE];
	int choice;
	
	
	printMainMenu();
	
	fgets(sChoice, MAXSIZE, stdin);
	choice = (int) strtol(sChoice, NULL, 10);

	while(choice !=  4){
		
		switch (choice){
			case 1:
				stackMain();
				break;
			
			case 2:
				queueMain();
				break;
				
			case 3: 
				treeMain();
				break;
				
			case 4:
			
				break;
				
			default:
			
				break;
		}

		for (int i = 0; i < 10; i++){
			puts("----------------------------------\n");
		}

		printMainMenu();
	
		fgets(sChoice, MAXSIZE, stdin);
		choice = (int) strtol(sChoice, NULL, 10);

	}
    		
	puts ("----------------------------------\n\n"
	      "      Thank you for using our\n"
	      "          test environment\n");
}
   

void printMainMenu(){
	puts (
		  "----------------------------------\n"
		  "      Grand Central Station\n"
		  "       Passenger Manifest\n"
		  "   Developer Test Environment\n"
		  "----------------------------------\n\n"
		  "Please select an option below: \n"
		  "1. Stack Operations\n"
		  "2. Queue Operations\n"
		  "3. Tree Operations\n"
		  "4. Exit Application\n"
	);


}

