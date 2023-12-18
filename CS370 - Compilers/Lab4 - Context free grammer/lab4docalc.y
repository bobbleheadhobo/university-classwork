%{

/*
 *			**** CALC ****
 *
 * This routine will function like a desk calculator
 * There are 20 integer registers, named 'aA' thru 'zZ' or '0' thru '9'
 *
 */

/* This calculator depends on a LEX description which outputs either VARIABLE or INTEGER.
   The return type via yylval is integer 

   When we need to make yylval more complicated, we need to define a pointer type for yylval 
   and to instruct YACC to use a new type so that we can pass back better values
 
   The registers are based on 0, so we substract 'a' from each single letter we get.

   based on context, we have YACC do the correct memmory look up or the storage depending
   on position

   Shaun Cooper
    January 2015


    ------------------------------------------------------------------------
            Joey troyer
            2/13/22
            Purpose: It reads in characters from user and checks whether its a list, statment or expression or variables.
					 If its a variable then it will check if it already exists in the symbol table if not then it will
					 insert it into the table. If theres a statment it assign user given value to the variables which 
					 are stored in the table. If its an expression it will perform the appropraitate action such as
					 multiplying two expressions, adding or subtracting..etc.
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include "symtab.h"
int yylex(); //prototype to get rid of error

#define MAX 20

int regs[MAX];
int base, debugsw, count;

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s\n", s);
}

%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start P

%union {
	int value;
	char *ID;	
       }//end union

%token <value> INTEGER
%token <ID> VARIABLE
%token INT


%type <value> expr

%left '|'
%left '&'
%left '+' '-'
%left '*' '/' '%'
%left UMINUS


%%	/* end specs, begin rules */

P : DECLS list;

DECLS : DECLS DECL 
	  | /* empty */ ;

DECL :  INT VARIABLE ';' '\n' {
	//if it's not there
	if(Search($2) == NULL) 
	   if(count < MAX) {
	      Insert($2, 1);
	      count++;
	   }//end if
	   else
	      printf("MAX amount of variables reached\n");
	else
	   printf("The variable name is already in use\n");
}
	;



list	:	/* empty */
	|	list stat '\n'
	|	list error '\n'
			{ yyerrok; }
	;

stat	:	expr
			{ fprintf(stderr,"the anwser is %d\n", $1); }
	|	VARIABLE '=' expr
			{ if(Search($1) != NULL)
				regs[FetchAddress($1)] = $3;
			  else
			  	printf("Variable name does not exist\n"); }
	;

expr	:	'(' expr ')'
			{ $$ = $2; }
	|	expr '-' expr
			{ $$ = $1 - $3; }
	|	expr '*' expr 
			{ $$ = $1 * $3; }
	|	expr '+' expr
			{ $$ = $1 + $3; }
	|	expr '/' expr
			{ $$ = $1 / $3; }
	|	expr '%' expr
			{ $$ = $1 % $3; }
	|	expr '&' expr
			{ $$ = $1 & $3; }
	|	expr '|' expr
			{ $$ = $1 | $3; }
	|	'-' expr	%prec UMINUS
			{ $$ = -$2; }
	|	VARIABLE //says if variable exists or not
			{ $$ = regs[FetchAddress($1)];
			  if(Search($1) != NULL) {
			    fprintf(stderr,"found a variable value = %s\n",$1);
			} else 
			  	printf("Variable name does not exist\n"); }

	|	INTEGER {$$=$1; fprintf(stderr,"found an integer\n");}
	;



%%	/* end of rules, start of program */

int main() //added int
{ yyparse();
}
