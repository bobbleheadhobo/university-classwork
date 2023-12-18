/** 
 * lab4
 * @file   symtable.c
 * @author Joey Troyer
 * @brief  Creates a symbol table that stores symbols and corresponding addresses sent from lab4docalc. 
 *         Will insert variable names and address values from the caclulator into the symbol table
 * @date   2022-02-13
 * 
 */


#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include "symtab.h"

int size = 0;


//PRE: PTR to symbol
//POST: Searches through the symbol table for mySymbol. 
//      If it is found it will return the address value from 
//      the pointer or barf
int FetchAddress(char* mySymbol) {
    struct SymbTab *n;
    n = Search(mySymbol);
    //if mySymbol found it will return the address value from it
    if(n != NULL)
        return (n->addr);

    //if not found return null
	return(0);
}//end fetch address



// PRE:  PTR to character string and symbol pointer and address
// POST: Searches symbtab to preven duplicates from being inserted. 
//       If its not a duplicate it creates PTR structure to the new symbol
// Error message and exit if already present.
struct SymbTab *Insert(char *symbol, int address) {
    // struct SymbTab *n;
    // n = Search(symbol);
    // if (n != NULL)
    //     printf("\n\tThe symbol exists already in the symbol table\n\tDuplicate can.t be inserted\n");
    // else {

        //creates a node for a PTR character string
        struct SymbTab *p;
        p = malloc(sizeof(struct SymbTab));
        
        //puts symbol and address in the list
        p->symbol = strdup(symbol);
        p->addr = address;
        &p->addr;
        p->next = NULL;

        //creating head and tail for new linked list
        if (size == 0) {
            first = p;
            last = p;
        }
        //preparing the list for more data to be added
        else {
            last->next = p;
            last = p;
        }
        size++;

     printf("\tSymbol inserted\n");
    //}
}//end insert


// PRE:  A PTR character string
// POST: Prints the collected user input symbol and address stored PTR character string to the screen.
//       if no data is in the linked list it will display the header and exit out.
void Display() {
    int i;
    //initalized symbtab node
    struct SymbTab *p;
    p = first;
    //header displayed for data
    printf("\t\tSYMBOL\t\tADDRESS\n");

    //goes through each node in the PTR character string and prints the symbol and address
    for (i = 0; i < size; i++) {
        printf("\t\t%s\t\t%d\n", p->symbol, p->addr);
        p = p->next;
    }//end for
}//end display


//PRE:  Ptr character string and a mySymbol pointer
//POST: It goes through the entire PTR character string comparing mySymbol to the symbol already in the list for duplicates
//      Creates PTR to matching structure if duplicate is found or NULL if not found
struct SymbTab *Search(char *mySymbol ) {
    int i;
    struct SymbTab *p;
    p = first;

    //goes through the PTR character string and searches for mySymbol
    for (i = 0; i < size; i++) {
        //compares symbol to mySymbol character by character to see if they're the same
        //if a match is found immedietly returns the node that matched mySymbol
        if (strcmp(p->symbol, mySymbol) == 0)
            return p;
        p = p->next;
    }//end for
    return NULL;
}//end search


// PRE: PTR character string
// POST: Asks what the user wants to change. Sends them into the corresponding case. Gets user input for the symbol they want to change
//       and the new data to replace the old data with. After the data is changes it displays the new data in Symbtab.
// Error message and exit if symbol does not exist
void Modify() {
    char l[10], nl[10];
    int add, choice, i;
    struct SymbTab *p, *s;
    p = first;
    printf("\n\tWhat do you want to modify?\n");
    printf("\n\t1.Only the symbol\n\t2.Only the address\n\t3.Both the symbol and address\n");
    printf("\tEnter your choice: ");

    // reads in a number to call the corresponding function
    scanf("%d", &choice);
    switch (choice) {
    case 1:
        //reads in a symbol and makes sure it exists
        printf("\n\tEnter the old symbol : ");
        scanf("%s", l);
        s = Search(l);
        if (s == 0)
            printf("\n\tSymbol not found\n");
        else {
            //reads in the new symbol
            printf("\n\tEnter the new Symbol: ");
            scanf("%s", nl);

            //searches for the old symbol
            for (i = 0; i < size; i++) {
                if (strcmp(p->symbol, l) == 0)
                    //replaces old symbol with the new symbol
                    p->symbol = strdup(nl);
                p = p->next;
            }
            //shows changes
            printf("\n\tAfter Modification:\n");
            Display();
        }
        break;

    case 2:
        //reads in a symbol and makes sure it exists
        printf("\n\tEnter the symbol of the address you want modify: ");
        scanf("%s", l);
        s = Search(l);
        if (s == NULL)
            printf("\n\tSymbol not found\n");
        else {
            //reads in new address for the symbol
            printf("\n\tEnter the new address: ");
            scanf("%d", &add);
            //searches for symbol
            for (i = 0; i < size; i++) {
                //compares symbols lexically
                if (strcmp(p->symbol, l) == 0)
                    //replaces old address with new address
                    p->addr = add;
                //moves to the next node
                p = p->next;
            }
            //shows changes
            printf("\n\tAfter Modification:\n");
            Display();
        }
        break;
    case 3:
        //reads in a symbol and makes sure it exists
        printf("\n\tEnter the old Symbol : ");
        scanf("%s", l);
        s = Search(l);
        if (s == NULL)
            printf("\n\tSymbol not found\n");
        else {
            //reads in new symbol and new address
            printf("\n\tEnter the new Symbol : ");
            scanf("%s", nl);
            printf("\n\tEnter the new address : ");
            scanf("%d", &add);
            //searches for old symbol
            for (i = 0; i < size; i++) {
                if (strcmp(p->symbol, l) == 0) {
                    //when found replaces both the old symbol and address with the new ones
                    p->symbol = strdup(nl);
                    p->addr = add;
                }
                //moves to the next node
                p = p->next;
            }
            //shows changes
            printf("\n\tAfter Modification:\n");
            Display();
        }
        break;
    }
}//end modify

// PRE:  PTR character string and data in the symbtab
// POST: Scans in the symbol to delete. Makes sure that symbol exists in the linked list.
//       Depending on the location of the symbol it will go to one of three snippets of code to properly delete the node.
// error message and exit if symbol does not exist
void Delete() {
    char l[10];
    struct SymbTab *p, *q, *a;
    p = first;
    //read in symbol to delete
    printf("\n\tEnter the Symbol to be deleted : ");
    scanf("%s", l);
    a = Search(l);
    if (a == NULL)
        printf("\n\tSymbol not found\n");
    else {
        //if the front node has the symbol to be deleted then it moves front up one node. 
        //The new front is now disconected from the previous front node
        if (strcmp(first->symbol, l) == 0)
            first = first->next;
        
        //If the last node is the one to be deleted
        else if (strcmp(last->symbol, l) == 0) {
            //copies p->next into q
            q = p->next;
            //While the node to be deleted is not found in q it will keep moving through p and q
            while (strcmp(q->symbol, l) != 0) {
                p = p->next;
                q = q->next;
            }
            p->next = NULL;
            last = p;
        }
        //if node to be deleted is not at front or last
        else {
            //copies p->next into q
            q = p->next;
            //While the node to be deleted is not found in q it will keep moving through p and q
            while (strcmp(q->symbol, l) != 0) {
                p = p->next;
                q = q->next;
            }
            //set p->next equal to q->next
            p->next = q->next;
        }
        size--;
        //show changes made
        printf("\n\tAfter Deletion:\n");
        Display();
    }
}//end delete
