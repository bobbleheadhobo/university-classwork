%{
/*
            Joey troyer
			Lab5
            2/22/22
            Purpose: Implemented the context free grammer for the language algol-C. It will handle basic declaration or arrays, 
			         assigning values to those variables, returning those variables and functions declarations. Basic if then 
					 else statments and while do.
					 !! WONT WORK lines like "int var = 5;". Variables must be delcared and assigned a value on diffent lines
					 !! For loops are NOT supported
					 !! parameters in functions must be declared like "main(x of int)" NOT "int a"
					 !! 1 shift/reduce conflict with selection_stmt but no need to fix for now
*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
int yylex(); //prototype to get rid of error

extern int lineno; //global line number
extern int mydebug; //global debug variable

void yyerror (s)  //barfs if there is an error. Prints line number that error occured on 
char *s; 
{
  printf ("%s on line number: %d\n", s, lineno);
}

%}

/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start program

%union {
	int value;
	char *ID;	
       }//end union

%token <value> T_NUM
%token <ID> T_ID
%token T_INT T_VOID T_BOOLEAN T_END T_BEGIN T_OF T_READ T_WRITE T_RETURN T_IF T_THEN T_ELSE T_WHILE T_DO
%token T_EQ T_LE T_GE T_NE T_AND T_OR T_TRUE T_FALSE T_NOT


%%	/* end specs, begin rules */

// #1
program : declaration_list
		;

// #2
declaration_list : declaration 
		         | declaration declaration_list
				 ;

// #3
declaration : var_declaration
			| fun_declaration
			;

// #4
var_declaration : type_specifier var_list ';'
				;

// #4a
var_list : T_ID 				{ printf("[%d] ID Name: %s\n", lineno, $1); }
		 | T_ID '[' T_NUM ']'	{ printf("[%d] ID Name: %s\n", lineno, $1); }
		 | T_ID ',' var_list	{ printf("[%d] ID Name: %s\n", lineno, $1); }
		 | T_ID '[' T_NUM ']' ',' var_list	{ printf("[%d] ID Name: %s\n", lineno, $1); }
		 ;

// #5
type_specifier : T_INT
			   | T_VOID
			   | T_BOOLEAN
			   ;

// #6
fun_declaration : type_specifier T_ID '(' params ')' compound_stmt  { printf("[%d] ID Name: %s\n", lineno, $2); }
				;

// #7
params : T_VOID 
	   | param_list
	   ;

// #8
// left recursive
param_list : param
		   | param ',' param_list
			;
	
// #9
param : T_ID T_OF type_specifier		 { printf("[%d] ID Name: %s\n", lineno, $1); }
	  | T_ID '[' ']' T_OF type_specifier { printf("[%d] ID Name: %s\n", lineno, $1); }
	  ;

// #10
compound_stmt : T_BEGIN local_declarations statment_list T_END
			  ;

// #11
local_declarations : /*empty */
				   | var_declaration local_declarations
				   ;

// #12
statment_list : /* empty */
			  | statment statment_list
			  ;

// #13
statment : expression_stmt
		 | compound_stmt
		 | selection_stmt
		 | iteration_stmt  
		 | assignment_stmt
		 | return_stmt
		 | read_stmt
		 | write_stmt
		 ;

// #14
expression_stmt : expression ';' 
				| ';'
				;

// #15
selection_stmt : T_IF expression T_THEN statment 
			   | T_IF expression T_THEN statment T_ELSE statment
			   ;

// #16
iteration_stmt : T_WHILE expression T_DO statment
			   ;

// #17
return_stmt : T_RETURN ';'
			| T_RETURN expression ';'
			;

// #18
read_stmt : T_READ var ';' 
		  ;

// #19
write_stmt : T_WRITE expression ';'
		   ;

// #20
assignment_stmt : var '=' simple_expression ';'
				;

// #21
expression : simple_expression
		   ;

// #22
var : T_ID 						{ printf("[%d] ID Name: %s\n", lineno, $1); }
	| T_ID '[' expression ']'	{ printf("[%d] ID Name: %s\n", lineno, $1); }
    ; 

// #23	
simple_expression : additive_expression
				  | simple_expression relop additive_expression
				  ;

// #22b
relop : T_EQ
	  | T_LE
	  | T_GE 
	  | T_NE 
	  | '>'
	  | '<'
	  ;

// #23b
// left recursive
additive_expression : term
					| additive_expression addop term
					;

// #24
addop : '+'
	  | '-'
	  ;

// #25
// left recursive
term : factor
	 | term multop factor
	 ;

// #26
multop : '*'
	   | '/'
	   | T_AND
	   | T_OR
	   ;

// #27
factor : '(' expression ')'
	   | T_NUM
	   | var
	   | call
	   | T_TRUE
	   | T_FALSE
	   | T_NOT factor
	   ;

// #28
call : T_ID '(' args ')' { printf("[%d] ID Name: %s\n", lineno, $1); }
	 ;

// #29
args : args_list
	 | /*empty*/
	 ;

// #30
// left recursive
args_list : expression
		  | expression ',' args_list
		  ;

%%	/* end of rules, start of program */

int main() { 
	yyparse();
	//prints to know when reached the end of the program
	printf("parsing complete \n");
}
