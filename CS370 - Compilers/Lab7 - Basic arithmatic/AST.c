/**
 * @file AST.c
 * @author Joey Troyer
 * @brief Implementation of ast function. yacc file sends this one
 *        nodes and then this prints the case and the output 
 *        from the abstract syntax tree until null 
 * @date 2022-04-06
 */
#include <stdlib.h>
#include <stdio.h>
#include "AST.h"



//prototypes
void Print_Declared_Type(enum AST_Declared_Type DeclType);
void Print_Operator_Type(enum AST_Operator_Type operator);
void Print_Spaces(int indent);


//PRE: AST_Node_Type
//POST: ptr to ASTnode from head
struct ASTnode *AST_Create_Node(enum AST_Node_Type my_type) {
    
    struct ASTnode *p;
    p = (struct ASTnode *)malloc(sizeof(struct ASTnode));
    p->MyType = my_type;
    p->s1=NULL;
    p->s2=NULL;
    p->next=NULL;
    
};

//PRE: ptr to ASTnode
//POST: recursivly moves down the tree and prints formatted output to AST
void AST_Print (struct ASTnode *p, int indent) {
    return;//ADDED FOR TESTING

    if (p == NULL)
       return;
    
    //at this point we know there is more to p and it is healthy
    switch (p->MyType)
    {

    case A_VARDEC:
        Print_Spaces(indent);
        if(p->size == 1) { //if size is greater than 1 it's an array
            printf("Variable: ");
            Print_Declared_Type(p->DeclType);
            printf("%s\n", p->name);
            AST_Print(p->s1, indent);
            AST_Print(p->next, indent);
        }//end if
        else {
           printf("Array: ");
           Print_Declared_Type(p->DeclType);
           printf("%s[%d]\n", p->name, p->size);
           AST_Print(p->s1, indent);
           AST_Print(p->next, indent);
        }//end else
        break;

    case A_FUNDEC:
        Print_Spaces(indent);
        printf("Fundec: ");
        Print_Declared_Type(p->DeclType);
        printf("%s \n", p->name);
        AST_Print(p->s1, indent + 1); //for params
        AST_Print(p->s2, indent + 1); //compound stmt
        AST_Print(p->next, indent);
        break;

    case A_PARAM:
        Print_Spaces(indent);
        printf("Param: ");
        Print_Declared_Type(p->DeclType);
        printf("%s \n", p->name);
        AST_Print(p->next, indent);
        break;

    case A_BLOCK:
        Print_Spaces(indent);
        printf("BEGIN\n");
        AST_Print(p->s1, indent + 1);
        AST_Print(p->s2, indent + 1);
        Print_Spaces(indent);
        printf("END\n");
        break;

    case A_EXPRSTMT:
        if(p->s1 != NULL) { //if null there was just only ;;;;
            Print_Spaces(indent);
            printf("EXPRESSION Statement\n");
            AST_Print(p->s1, indent + 1);
        }
        AST_Print(p->next, indent);
        break;

    case A_EXPR:
         Print_Spaces(indent);
         printf("Expression: ");
         Print_Operator_Type(p->operator);
         printf("\n");
         AST_Print(p->s1, indent + 1);
         AST_Print(p->s2, indent + 1);
         break;

    case A_NUMBER:
         Print_Spaces(indent);
         printf("Number with value: %d\n", p->size);
         break;

    case A_BOOLEAN:
        Print_Spaces(indent);
        if(p->size == 1)
            printf("TRUE\n");
        else
            printf("FALSE\n");
        break;

    case A_IF: 
        Print_Spaces(indent);
        if(p->s2->s2 == NULL){ //if p->s2->s2 is NULL means there is no else
           printf("IF Statement\n");
           AST_Print(p->s1, indent + 1);
           Print_Spaces(indent);
           printf("THEN\n");
           AST_Print(p->s2->s1, indent + 1);
           AST_Print(p->next, indent);
        }
        else {
           printf("IF Statement\n");
           AST_Print(p->s1, indent + 1);
           Print_Spaces(indent);
           printf("THEN\n");
           AST_Print(p->s2->s1, indent + 1);
           Print_Spaces(indent);
           printf("ELSE\n");
           AST_Print(p->s2->s2, indent + 1);
           AST_Print(p->next, indent);
        }
        break;

    case A_WHILE:
        Print_Spaces(indent);
        printf("WHILE Statment\n");
        AST_Print(p->s1, indent + 1);
        Print_Spaces(indent);
        printf("DO\n");
        AST_Print(p->s2, indent + 1);
        AST_Print(p->next, indent);
        break;

    case A_RETURN:
        Print_Spaces(indent);
        printf("Return\n");
        AST_Print(p->s1, indent + 1);
        AST_Print(p->next, indent);
        break;

    case A_ASSIGN:
        Print_Spaces(indent);
        printf("ASSIGNMENT Statement\n");
        AST_Print(p->s1, indent + 1);
        AST_Print(p->s2, indent + 1);
        AST_Print(p->next, indent);
        break;

    case A_IDENT:
        Print_Spaces(indent);
        if(p->s1 == NULL) { //if s1 is not null it means it is an array
        printf("Identifier: %s\n", p->name);
        } 
         else {
        printf("Array: %s [\n", p->name);
        AST_Print(p->s1, indent + 1); //var
        Print_Spaces(indent);
        printf("] end Array\n");
        }
        break;

    case A_CALL:
        Print_Spaces(indent);
        printf("Call: ");
        printf("%s\n", p->name);
        AST_Print(p->s1, indent + 1);
        break;

    case A_ARGSLIST:
    Print_Spaces(indent);
    if(p->next != NULL){ //if its null there is no next
        printf("Args List\n");
        AST_Print(p->s1, indent + 1);
        AST_Print(p->next, indent);
    }
    else {
        printf("Args List\n");
        AST_Print(p->s1, indent + 1);
    }
        break;

    case A_READ:
        Print_Spaces(indent);
        printf("READ Statement\n");
        AST_Print(p->s1, indent + 1); //var
        AST_Print(p->next, indent);// because statment is next connected
        break;

    case A_WRITE:
        Print_Spaces(indent);
        printf("WRITE Statement\n");
        AST_Print(p->s1, indent + 1);
        AST_Print(p->next, indent);
        break;

    default: fprintf(stderr, "WARNING UNKNOWN type in AST_print\n");
             fprintf(stderr, "WARNING FIX FIX FIX\n");
        break;
    }
}

//PRE: enum AST_Declared_Type
//POST: Prints corresponding declared type from the parameter
void Print_Declared_Type(enum AST_Declared_Type DeclType) {
    switch (DeclType)
    {
    case A_INT_TYPE: 
        printf("INT ");
        break;

    case A_BOOLEAN_TYPE:
        printf("BOOLEAN ");
        break;

    case A_VOID_TYPE:
        printf("VOID ");
        break;
    
    default: fprintf(stderr, "WARNING UNKNOWN type in Print_Declared_Type\n");
             fprintf(stderr, "WARNING FIX FIX FIX\n");
        break;
    }
}//end Print_Declared_Type


//PRE: enum AST_Operator_Type
//POST: prints the corresponding operator from the parameter
void Print_Operator_Type(enum AST_Operator_Type operator) {
    switch (operator)
    {
    case A_EQ:
        printf(" == ");
        break;

    case A_LT:
        printf(" < ");
        break;

    case A_GT:
        printf(" > ");
        break; 

    case A_LE:
        printf(" <= ");
        break;

    case A_GE:
        printf(" >= ");
        break;

    case A_NE:
        printf(" != ");
        break;

    case A_PLUS:
        printf(" + ");
        break;

    case A_MINUS:
        printf(" - ");
        break;

    case A_TIMES:
        printf(" * ");
        break;

    case A_DIVIDE:
        printf(" / ");
        break;

    case A_AND:
        printf(" AND ");
        break;

    case A_OR:
        printf(" OR ");
        break;

    case A_NOT:
        printf(" NOT ");
        break;
    
    default: fprintf(stderr, "WARNING UNKNOWN type in Print_Operator_Type\n");
             fprintf(stderr, "WARNING FIX FIX FIX\n");
        break;
    }//end switch
}//end Print_Operator_Type


//PRE: int variable indent
//POST: prints two spaces indent amount of times
void Print_Spaces(int indent) {
    for(int i = 0; i < indent; i++)
        printf("  ");
}//end print_spaces


//PRE: two pointers to ASTnode
//POST: returns 1 if both pointers types are the same. Returns 0 if not the same.
int CompareFormals(struct ASTnode *p, struct ASTnode *q) {
    if((p == NULL) && (q == NULL)) {
        return 1;}

        else if((p == NULL) || (q == NULL)) {
            return 0;}

           else if(p->calculated_type == q->s1->calculated_type)
                   CompareFormals(p->next, q->next);

              else{
                 printf("comparing p %d and q %d\n", p->calculated_type, q->calculated_type);
                 return(0);
              }
}//end compareFormals