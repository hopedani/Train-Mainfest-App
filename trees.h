
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

#define TRUE 1

#define FALSE 0
#define MAX_INPUT 20
// add code for TreeNode structure definition 
struct treeNode {
	int ticketnumber;
	char name[20];
	float price;
    	struct treeNode *leftPtr;
	struct treeNode *rightPtr;
};

typedef struct treeNode TreeNode;
typedef TreeNode *TreeNodePtr;

// function prototypes 
void insertNode(TreeNodePtr *treePtr, char name[20], float price);
void inOrder( TreeNodePtr treePtr );
void preOrder( TreeNodePtr treePtr );
void postOrder( TreeNodePtr treePtr );
void showMenu(void);

void deleteNode( TreeNodePtr *treePtr, int ticketnum );
void searchNode ( TreeNodePtr *treePtr, int ticketnum, TreeNodePtr *parentPtr, TreeNodePtr *tempNodePtr, int *found );
TreeNodePtr binaryTreeSearch (TreeNodePtr treePtr, int ticketnum);
void treeMain();


void treeMain()
{ 
   
   // add code to initialise rootPtr pointer to the root of the tree
	TreeNodePtr rootPtr = NULL;   
    unsigned int choice;
    char name[20];
    float price;
    int valid = 0;
    char sPrice[11];
    char sChoice[MAX_INPUT];

	unsigned int searchKey;		/* value to search for */
	char sSearchKey[MAX_INPUT];
	TreeNodePtr searchResultPtr;	/* pointer to search result */
   
  //Print 'decorative title'
	puts("------------------------------------------------------");
	puts("------------------------------------------------------");
	puts("               Grand Central Station");
	puts("             Passenger Manifest System");
    puts("------------------------------------------------------");
	puts("------------------------------------------------------\n");
 //Print menu and wait for user input  
    showMenu();
    fgets(sChoice, MAX_INPUT, stdin);
    puts("------------------------------------------------------");
	puts("------------------------------------------------------\n");
//Convert user choice from a string to an int	
    choice = (int)strtol(sChoice, NULL, 10);

//While loop for program begins	
    while(choice != 7) {
    
    //switch statement begins
       switch(choice) {
       //Add a node to the tree (passenger onto the train)
        case 1:
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
            insertNode(&rootPtr, name, price);
            break;
		//Remove a node from the tree (delete passenger from the train)
        case 2:
			valid = 0;
            //add code to delete from the tree
			printf("\nPlease enter a ticket number to delete: \n");
			while(valid != 1){
            fgets(sSearchKey, MAX_INPUT, stdin);
            searchKey = (int)strtol(sSearchKey, NULL, 10);
            
            //Validate ticket number is a positive number
	    	if(searchKey < 0) {
		      puts("Please re-enter a ticket number\n(Zero or higher): ");
		      valid = 0;
		    } else {
		      valid = 1;
		    }
		  }
			deleteNode(&rootPtr, searchKey);
			
            puts("------------------------------------------------------\n");
			break;
			
		//Binary search of the tree (find person in the train manifest)
        case 3:
        	valid = 0;
            //add code to delete from the tree
			printf("\nPlease enter a ticket number to search for: \n");
			while(valid != 1){
            fgets(sSearchKey, MAX_INPUT, stdin);
            searchKey = (int)strtol(sSearchKey, NULL, 10);
            
            //Validate ticket number is a positive number
	    	if(searchKey < 0) {
		      puts("Please re-enter a ticket number\n(Zero or higher): ");
		      valid = 0;
		    } else {
		      valid = 1;
		    }
		  }

  			// perform the search
			searchResultPtr = binaryTreeSearch(rootPtr, searchKey);

  			// determine if value is found or not
			if(searchResultPtr == NULL){
				printf("\nTicket number %d was not found\n", searchKey);
			}else{
				printf("\nTicket number %d was found\n", searchResultPtr->ticketnumber);
			}
		
         	puts("------------------------------------------------------\n");
            break;

        //Pre-order Traversal of the tree 
        case 4:
            
            preOrder(rootPtr);
            
            puts("------------------------------------------------------\n");
            break;
            
        //Post-order Traversal of the tree
        case 5:
            
			postOrder(rootPtr);

            puts("------------------------------------------------------\n");
            break;
		
		//In-order Traversal of the tree
		case 6:
            
			inOrder(rootPtr);

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
        showMenu();
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
	
	void showMenu(void)
	{
		puts("Please select an option from the list below\n\n"
			 "       1. Embark New Passenger\n"
			 "       2. Disembark a Person on the Train\n"
			 "       3. Search train for passenger\n"
			 "       4. Fast display manifest (Method 1)\n"
			 "       5. Fast display manifest (Method 2)\n"
			 "       6. View train manifest in ascending order\n"
			 "       7. Exit the program\n"
			  );	 
	}

/* insert a node recursively into the tree */
void insertNode(TreeNodePtr *treePtr, char name[20], float price)
{ 
	int ticketnum = 1 + rand() % 5000;
   /* if treePtr is NULL ... that is if node is a leaf node*/
   if ( *treePtr == NULL ) { 

      // add code to dynamically allocate memory
	*treePtr = (TreeNodePtr)malloc(sizeof(TreeNode));
      
      if ( *treePtr != NULL ) 
      { 
        // add code here to insert node if memory was allocated
 		(*treePtr)->ticketnumber = ticketnum;
		strcpy((*treePtr)->name, name);
		(*treePtr)->price = price;
		(*treePtr)->leftPtr = NULL;
		(*treePtr)->rightPtr = NULL;
      } 
      else {
         printf( "%d not inserted. No memory available.\n", ticketnum );
      } 

      return; 
   } 

   else 
   {   

      /* insert node in left subtree */
      if (ticketnum < (*treePtr)->ticketnumber ) { // add test here 

         // add code to insert into left subtree  
         insertNode(&((*treePtr)->leftPtr), name, price);
      } 
      else if(ticketnum > (*treePtr)->ticketnumber) // add test here
      {  

         // add code to insert into right subtree
          insertNode(&((*treePtr)->rightPtr), name, price);
      } 
      else { // will not all duplicate values to be inserted
		
         printf("\n-duplicate-ticket number not taken\n");  
      }   

   } 

} 

/* traverse the tree inorder */
void inOrder( TreeNodePtr treePtr )
{ 

   if ( treePtr != NULL) { 
      // add code: traverse left , print node, traverse right
        inOrder(treePtr->leftPtr);
		printf("\nTicket number: %d\nCustomer name: %sTicket price: $%.2f\n", treePtr->ticketnumber, treePtr->name, treePtr->price);
		inOrder(treePtr->rightPtr);
   } 

} 

/* traverse the tree preorder */
void preOrder( TreeNodePtr treePtr )
{ 
  
   if ( treePtr != NULL) { 
      // add code: print node, traverse left sub, traverse right subtree 
		
		printf("\nTicket number: %d\nCustomer name: %sTicket price: $%.2f\n", treePtr->ticketnumber, treePtr->name, treePtr->price);
		preOrder(treePtr->leftPtr);
		preOrder(treePtr->rightPtr);
   } 

} 

/* traverse the tree postorder */
void postOrder( TreeNodePtr treePtr )
{ 
 
   if ( treePtr != NULL) { 
     // add code: traverse left sub, traverse right subtree, print node 
		
		postOrder(treePtr->leftPtr);
		postOrder(treePtr->rightPtr);
		printf("\nTicket number: %d\nCustomer name: %sTicket price: $%.2f\n", treePtr->ticketnumber, treePtr->name, treePtr->price);
   } 

} 

/* deletes a node from the binary search tree */
void deleteNode ( TreeNodePtr *treePtr, int ticketnum )
{
    int found ;
    TreeNodePtr parentPtr, tempNodePtr, replacementNodePtr ;
    
    /* if tree is empty */
    if ( *treePtr == NULL )
    {
        printf ( "\nTree is empty\n" ) ;
        return ;
    }
	if((*treePtr)->leftPtr == NULL && (*treePtr)->rightPtr == NULL){
		printf("\nSorry you can not remove the last passenger from the train\n");
		return;
	}
    parentPtr = NULL ;
    tempNodePtr = NULL;

    /* find the node to be deleted */

    searchNode ( treePtr, ticketnum, &parentPtr, &tempNodePtr, &found ) ;

    /* if the node is not found */
    if ( found == FALSE )
    {
        printf ( "\n Data not found\n" ) ;
        return ;
    }

    /* if the node to be deleted has two children */
    if ( tempNodePtr -> leftPtr != NULL && tempNodePtr -> rightPtr != NULL )
    {
        parentPtr = tempNodePtr ;
        replacementNodePtr = tempNodePtr -> rightPtr ;

        while ( replacementNodePtr -> leftPtr != NULL )
        {
            parentPtr = replacementNodePtr ;
            replacementNodePtr = replacementNodePtr -> leftPtr ;
        }

        tempNodePtr -> ticketnumber = replacementNodePtr -> ticketnumber ;
        tempNodePtr = replacementNodePtr ;
		printf("\nTicket %d has been removed from the mainfest\n", ticketnum);
		free ( tempNodePtr ) ;
        return ;
    }

    /* if the node to be deleted has no child */
    if ( tempNodePtr -> leftPtr == NULL && tempNodePtr -> rightPtr == NULL )
    {
        if ( parentPtr -> rightPtr == tempNodePtr )
            parentPtr -> rightPtr = NULL ;
        else
            parentPtr -> leftPtr = NULL ;
		printf("\nTicket %d has been removed from the mainfest\n", ticketnum);
        free ( tempNodePtr ) ;
        return ;
    }

    /* if the node to be deleted has only rightPtr */
   if ( tempNodePtr -> leftPtr == NULL && tempNodePtr -> rightPtr != NULL )
    {
        if ( parentPtr -> leftPtr == tempNodePtr )
            parentPtr -> leftPtr = tempNodePtr -> rightPtr ;
        else
            parentPtr -> rightPtr = tempNodePtr -> rightPtr ;
		printf("\nTicket %d has been removed from the mainfest\n", ticketnum);
        free ( tempNodePtr ) ;
        return ;
    }

    /* if the node to be deleted has only left child */
    if ( tempNodePtr -> leftPtr != NULL && tempNodePtr -> rightPtr == NULL )
    {
        if ( parentPtr -> leftPtr == tempNodePtr )
            parentPtr -> leftPtr = tempNodePtr -> leftPtr ;
        else
            parentPtr -> rightPtr = tempNodePtr -> leftPtr ;
		printf("\nTicket %d has been removed from the mainfest\n", ticketnum);
        free ( tempNodePtr ) ;
        return ;
    }
}

void searchNode ( TreeNodePtr *treePtr, int ticketnum, TreeNodePtr *parentPtr, TreeNodePtr *tempNodePtr, int *found )
{
    TreeNodePtr tempPtr ;
    tempPtr = *treePtr ;
    *found = FALSE ;
    *parentPtr = NULL ;

    while ( tempPtr != NULL )
    {
     if ( tempPtr -> ticketnumber == ticketnum )
     {
       *found = TRUE ;
       *tempNodePtr = tempPtr ;
       return ;
     }

       *parentPtr = tempPtr ;
        if ( tempPtr -> ticketnumber > ticketnum )
            tempPtr = tempPtr -> leftPtr ;
        else
            tempPtr = tempPtr -> rightPtr ;
    }
}

/* search for key in tree */
TreeNodePtr binaryTreeSearch (TreeNodePtr treePtr, int ticketnum)
{
  
  if (treePtr == NULL)
    {
      // add code here to process search key not found
		return NULL;
    }				
  else if (treePtr->ticketnumber == ticketnum)
    {
      // add code here to process search key found
		return treePtr;
    }				
  else if (ticketnum < treePtr->ticketnumber)
    {
      // add code here to search left tree
		binaryTreeSearch(treePtr->leftPtr, ticketnum);
    }				
  else   /* implies (key > treePtr->data) */
    {
      // add code here to search right tree
		binaryTreeSearch(treePtr->rightPtr, ticketnum);
    }				
}				

