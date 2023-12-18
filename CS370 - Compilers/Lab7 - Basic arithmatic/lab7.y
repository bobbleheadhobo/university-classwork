%{
/*
            Joey troyer
			Lab7
            4/06/22
            Purpose: Implemention of a context free grammer for the language algol-C. It will handle basic declaration of scalars
					 or arrays, assigning values to those variables, returning those variables and functions declarations. Basic 
					 if then else statments and while do. There is syntax directed symantic action for every line that will create 
					 nodes from AST.c and add them to the abstract syntax tree. Introduced a symbol table which will add symbol to 
					 the table, preform type checking and create temp variable for calculating expressions. Will print the symbol 
					 tables variables along with some attributes during and after parsing.
					 !! WONT WORK lines like "int var = 5;". Variables must be delcared and assigned a value on diffent lines
					 !! For loops are NOT supported
					 !! parameters in functions must be declared like "main(x of int)" NOT "main(int x)"
					 !! 1 shift/reduce conflict with selection_stmt but no need to fix
*/


	/* begin specs */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "symtable.h"
#include "AST.h"

struct ASTnode *program = NULL; 

int yylex(); //prototype to get rid of error


extern int lineno; //global line number
extern int mydebug; //global debug variable
int level = 0; //static scope level
int offset = 0; //offset from declarations
int goffset = 0; //offset from all declaratoins used to hold values when we go in and out of functions
int maxoffset = 0; //keeps track of the size of functions

void yyerror (s)  //barfs if there is an error.
char *s; 
{
  printf ("%s on line number: %d\n", s, lineno); //prints error from yyerror and line that error occurred on
}

%}

/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start program

//connecting link for the c file
%union {
	int value;
	char *ID;
	struct ASTnode *astnode;
	enum AST_Declared_Type DeclType;
	enum AST_Operator_Type operator;
       }//end union

//tokens and types from lex and AST
%token <value> T_NUM T_INT T_VOID T_READ T_WRITE T_RETURN T_IF T_THEN T_ELSE T_WHILE T_DO T_EQ T_LE T_GE T_NE
%token <ID> T_ID
%token T_BOOLEAN T_END T_BEGIN T_OF
%token T_AND T_OR T_TRUE T_FALSE T_NOT
%type<astnode> declaration declaration_list var_declaration var_list fun_declaration param param_list params compound_stmt term factor iteration_stmt assignment_stmt args return_stmt
%type<astnode> local_declarations statment_list statment expression_stmt expression simple_expression additive_expression write_stmt selection_stmt var call args_list read_stmt
%type<DeclType> type_specifier
%type<operator> relop addop multop


%%	/* end specs, begin rules */

// #1
program : declaration_list {program = $1;}
		;

// #2
declaration_list : declaration {$$ = $1;}
		         | declaration declaration_list {
					 							 $$ = $1; 
				 								 $1->next = $2;
												}
				 ;

// #3
declaration : var_declaration {$$ = $1;}
			| fun_declaration {$$ = $1;}
			;

// #4
var_declaration : type_specifier var_list ';' { $$ = $2;
												//need to update type in varlist and pass up to parrent 
												struct ASTnode *p = $$;
			 					  				while(p != 	NULL) {
													  p->DeclType = $1;
													  p->symbol->Type = $1;
													  p = p->s1;
												   }//end while
											  }
				;

// #4a
var_list : T_ID 				{ //Search symbol to make sure variable is not already there then create not and insert into symbtab
								  if(Search($1, level, 0)) {
									 yyerror("error");
								  	 printf("Variable %s already in the symbol table\n", $1);
									 exit(1);
								  }//end if 

								  $$ = AST_Create_Node(A_VARDEC);
								  $$->symbol = Insert($1, 0, 0, level, 1, offset);
								  $$->calculated_type = Search($1, level, 1)->Type; //search symbol table for variable so we can get its type
								  $$->name = $1;
								  $$->size = 1;  
								  offset += 1;
								}

		 | T_ID '[' T_NUM ']'	{ //expl: int a[100];
		 					      //check if $1 is already in the symbol table if it is barf
								  if(Search($1, level, 0)) {
								     yyerror("error");
								  	 printf("Variable %s already in the symbol table\n", $1);
									 exit(1);
								  }//end if

			 					  $$ = AST_Create_Node(A_VARDEC);
								  $$->symbol = Insert($1, 0, 1, level, $3, offset);
								  $$->calculated_type = Search($1, level, 1)->Type;
		 						  $$->name = $1;
								  $$->size = $3;
								  offset += $3;
								}

		 | T_ID ',' var_list	{ //expl: int a, b, c;
		 						   //check if T_ID is already in the symbol table if it is barf
								  if(Search($1, level, 0)) {
								     yyerror("error");
								  	 printf("Variable %s already in the symbol table\n", $1);
									   exit(1);
								  }//end if

			 					  $$ = AST_Create_Node(A_VARDEC);
								  $$->symbol = Insert($1, 0, 0, level, 1, offset);
								  $$->calculated_type = Search($1, level, 1)->Type;
		 						  $$->name = $1;
								  $$->s1 = $3;
								  $$->size = 1;
								  offset += 1;
								}

		 | T_ID '[' T_NUM ']' ',' var_list	{ //expl: int a[100], b[100], c[100];
		 									  //check if T_ID is already in the symbol table if it is barf
								  			 if(Search($1, level, 0)) {
												yyerror("error");
								  	 			printf("Variable %s already in the symbol table\n", $1);
									   			exit(1);
								  			 }//end if

			 								  $$ = AST_Create_Node(A_VARDEC);
											  $$->symbol = Insert($1, 0, 1, level, $3, offset);
								  			  $$->calculated_type = Search($1, level, 1)->Type;
		 						  			  $$->name = $1;
								  			  $$->size = $3;
											  $$->s1 = $6; 
											  offset += $3;
											}
		 ;

// #5
type_specifier : T_INT		 {$$ = A_INT_TYPE;}
			   | T_VOID 	 {$$ = A_VOID_TYPE;}
			   | T_BOOLEAN   {$$ = A_BOOLEAN_TYPE;}
			   ;

// #6
fun_declaration : type_specifier T_ID {		//we need to add the ID into the symbtab before we take in params or compund statments because we may need to know the type and length of it
											if(Search($2, level, 0)) {
					   						   yyerror("error");
											   printf("Function name %s already in use!!!\n", $2);
											   exit(1);
											}//end if

											Insert($2, $1, 2, level, 0, 0);
											goffset = offset;
											offset = 0;
											maxoffset = 0;
									  }
    '(' params ')' {					    //update symbtab to have pointer to formal parameters
											(Search($2, 0, 0)) -> fparams = $5; }

    compound_stmt  { 						 
											$$ = AST_Create_Node(A_FUNDEC);
											$$->DeclType = $1;
											$$->calculated_type = $1;
											$$->name = $2;
											$$->s1 = $5; //params
											$$->s2 = $8; //compund stmt
											$$->symbol = Search($2, 0, 0); //get symbol table enrty 
											$$->symbol->mysize = maxoffset;
											offset = goffset; 
					}
				;

// #7
params : T_VOID     { $$ = NULL; /*no paramater list */}
	   | param_list { $$ = $1;}
	   ;

// #8
// left recursive
/*  Parmlist is a next list of parameters, name and type are the node itself no s1 parameter */
param_list : param 				 { $$ = $1;}
		   | param ',' param_list {
			         				$$ = $1;
			         				$$->next = $3; 
					 			  }
		   ;
	
// #9
param : T_ID T_OF type_specifier {      /* expl: a of int */
										//Make sure variable isnt already in use
										if(Search($1, level + 1, 0)) {
											yyerror("error");
									    	printf("Variable name %s already in use!!!\n", $1);
											exit(1);
										}

                              	 		$$ = AST_Create_Node(A_PARAM);
										$$->symbol = Insert($1, $3, 0, level + 1, 1, offset); //level + 1 because everything in the function will be on the next level
                              	 		$$->name = $1;
										$$->DeclType = $3;
										$$->calculated_type = $3;
                              	 		$$->size = 0; /* not an array */
										offset += 1;

										if(mydebug)
										   printf("Inserted param %s at level %d\n", $1, level + 1);
                           		  }

	  | T_ID '[' ']' T_OF type_specifier { /* expl: a[] of int */
										   if(Search($1, level + 1, 0)) {
										  	  yyerror("error");
									      	  printf("Variable name %s already in use!!!\n", $1);
										  	  exit(1);
										    }

                              	 		   $$ = AST_Create_Node(A_PARAM);
										   $$->symbol = Insert($1, $5, 1, level + 1, 1, offset); //level + 1 because everything in the function will be on the next level
                              	 		   $$->name = $1;
										   $$->DeclType = $5;
										   $$->calculated_type = $5;
                              	 		   $$->size = -1; /* is an array */
										   offset += 1;

										   if(mydebug)
										      printf("Inserted param %s[] at level %d\n", $1, level + 1);
                           		  		 }
	  ;

// #10
compound_stmt : T_BEGIN {//increment level when entering function
						 level++;} 
					local_declarations statment_list T_END
			                     {  /*expl: BEGIN stuff END */
								    $$ = AST_Create_Node(A_BLOCK);
                                    $$->s1 = $3;
                                    $$->s2 = $4;

									if(mydebug)
									   Display();
									
									if(offset > maxoffset) maxoffset = offset;
									offset -= Delete(level); /* remove all the symbols from what we put in from the function call*/
                                    level--; //decrement level when leaving function

									
                                 }
			  ;

// #11
local_declarations : /*empty */    {$$ = NULL;}
				   | var_declaration local_declarations 
				   				  {
									$$ = $1;
					   				$$->next = $2;
								  }
				   ;

// #12
statment_list : /* empty */ 	  {$$ = NULL;}
			  | statment statment_list {
				  						 $$ = $1; 
			  							 $$->next = $2;
									   }
			  ;

// #13
// all stmt are next connected
statment : expression_stmt {$$ = $1;}
		 | compound_stmt   {$$ = $1;}
		 | selection_stmt  {$$ = $1;}
		 | iteration_stmt  {$$ = $1;}
		 | assignment_stmt {$$ = $1;}
		 | return_stmt     {$$ = $1;}
		 | read_stmt       {$$ = $1;}
		 | write_stmt      {$$ = $1;}
		 ;

// #14
expression_stmt : expression ';' { 
								   $$ = AST_Create_Node(A_EXPRSTMT);
                                   $$->s1 = $1; 
								   $$->calculated_type = $1->calculated_type;
								 }
								   
				| ';'			 { //expl: ;;;;;;
								   $$ = AST_Create_Node(A_EXPRSTMT); 
								 }
				;

// #15
selection_stmt : T_IF expression T_THEN statment { //expl: if(x==3) then x+1;
												  $$ = AST_Create_Node(A_IF);
												  $$->s1 = $2;
												  $$->s2 = AST_Create_Node(A_IF);
												  $$->s2->s1=$4;
												  $$->s2->s2=NULL;
												 }

			   | T_IF expression T_THEN statment T_ELSE statment { //expl: if(x==3) then x+1 else x-3;
				   								 $$ = AST_Create_Node(A_IF);
												 $$->s1 = $2;
												 $$->s2 = AST_Create_Node(A_IF);
												 $$->s2->s1=$4;
												 $$->s2->s2=$6;
												 }
			   ;

// #16
iteration_stmt : T_WHILE expression T_DO statment { //expl: while(true) Do x + 3;
												   $$=AST_Create_Node(A_WHILE);
                               					   $$->s1=$2;
                                				   $$->s2=$4;
												  }
			   ;

// #17
return_stmt : T_RETURN ';' 			 { //expl: return
									  $$ = AST_Create_Node(A_RETURN); }
			| T_RETURN expression ';'{//expl: return x-5+6;
									  $$ = AST_Create_Node(A_RETURN);
									  $$->s1 = $2;
									 }
			;

// #18
read_stmt : T_READ var ';' { //expl: READ x;
							$$ = AST_Create_Node(A_READ);
							$$->s1 = $2;
						   }
		  ;

// #19
write_stmt : T_WRITE expression ';' { //expl: Write  x[100] + 200;
									 $$ = AST_Create_Node(A_WRITE);
									 $$->s1 = $2;
									}
		   ;

// #20
assignment_stmt : var '=' simple_expression ';' { //expl: x = 5;
												//type checking
					  							if($1->calculated_type != $3->calculated_type) {
										   			yyerror("error");
								  	       			printf("assignment Type mismatch\n");
									       			exit(1);
												}

												 $$ = AST_Create_Node(A_ASSIGN);
												 $$->s1 = $1;
												 $$->s2 = $3; 
												 $$->name = CreateTemp();
												 $$->symbol = Insert($$->name, $1->calculated_type, 0, level, 1, offset);	
												 offset++;
												}
				;

// #21
expression : simple_expression {$$ = $1;}
		   ;


// #22
var : T_ID 						{ //make sure variable exists on any level
								  struct SymbTab *p;
								  if((p = Search($1, level, 1)) == NULL){
									  yyerror("error");
									  printf("undeclared variable %s \n", $1);
									  exit(1);
								  }

								  //make sure variable is a scalar
								  if(p->IsAFunc != 0){
										 yyerror("error");
									     printf("variable %s not a scalar\n", $1);
									     exit(1);
								  }
								  
								    //create the node
								    $$=AST_Create_Node(A_IDENT);
	         					    $$->name=$1;
									$$->symbol = p;
									$$->calculated_type = p->Type;

								  
		 						}

	| T_ID '[' expression ']'	{ //make sure variable exists on any level
								  struct SymbTab *p;
								  if((p = Search($1, level, 1)) == NULL){
									  yyerror("error");
									  printf("undeclared variable %s \n", $1);
									  exit(1);
								  }

								  //make sure variable is a array
								  if(p->IsAFunc != 1){
										 yyerror("error");
									     printf("variable %s not a array\n", $1);
									     exit(1);
								  }

								  //create the node
								  $$=AST_Create_Node(A_IDENT);
								  $$->name=$1;
								  $$->s1 = $3; 
								  $$->calculated_type = p->Type;
								  $$->symbol = p;

								}
    ; 

// #23	
simple_expression : additive_expression {$$ = $1;}
				  | simple_expression relop additive_expression {
					  					//type checking
					  					if($1->calculated_type != $3->calculated_type) {
										   yyerror("error");
								  	       printf("Simple Type mismatch\n");
									       exit(1);
										}

										 //create the node
					    				 $$ = AST_Create_Node(A_EXPR);
                        				 $$->s1=$1;
										 $$->operator=$2;
										 $$->calculated_type = $3->calculated_type;
                        				 $$->s2=$3;
										 $$->name = CreateTemp();
										 $$->symbol = Insert($$->name, A_BOOLEAN_TYPE, 0, level, 1, offset);
										 offset++;
										}
				  ;

// #22b
//operators
relop : T_EQ {$$ = A_EQ;}
	  | T_LE {$$ = A_LE;}
	  | T_GE {$$ = A_GE;}
	  | T_NE {$$ = A_NE;}
	  | '>'  {$$ = A_GT;}
	  | '<'  {$$ = A_LT;}
	  ;

// #23b
// left recursive
additive_expression : term 							 { $$ = $1; }													
					| additive_expression addop term { 
													   //type checking
													   if($1->calculated_type != $3->calculated_type){
														   yyerror("error");
								  	                       printf("Additive Type mismatch\n");
									                       exit(1);
													   }
													   
													   //create the node
													   $$ = AST_Create_Node(A_EXPR);
													   $$->s1 = $1;
													   $$->operator = $2;
													   $$->s2 = $3;
													   $$->calculated_type = A_INT_TYPE;
													   $$->name = CreateTemp();
													   $$->symbol = Insert($$->name, A_INT_TYPE, 0, level, 1, offset);	
													   offset++;										 
													 }
					;

// #24
addop : '+' {$$ = A_PLUS;}
	  | '-' {$$ = A_MINUS;}
	  ;

// #25
// left recursive
term : factor  {$$=$1;}
	 | term multop factor {
				//type checking
				if($1->calculated_type != $3->calculated_type){
					yyerror("error");
					printf("Term Type mismatch\n");
					exit(1);
			    }
				
				//create the node
		 	    $$ = AST_Create_Node(A_EXPR);
		 		$$->s1 = $1;
				$$->operator = $2;
				$$->s2 = $3;
				$$->calculated_type = A_INT_TYPE;
				$$->name = CreateTemp();
 			    $$->symbol = Insert($$->name, A_INT_TYPE, 0, level, 1, offset);	
				offset++;
	 					  }
	 ;

// #26
multop : '*'   {$$ = A_TIMES;}
	   | '/'   {$$ = A_DIVIDE;}
	   | T_AND {$$ = A_AND;}
	   | T_OR  {$$ = A_OR;}
	   ;

// #27
factor : '(' expression ')' {$$ = $2;}

	   | T_NUM				{$$=AST_Create_Node(A_NUMBER);
                			 $$->size = $1;
							 $$->calculated_type = A_INT_TYPE;}

	   | var				{$$ = $1;}
							
	   | call				{$$ = $1;}

	   | T_TRUE				{$$=AST_Create_Node(A_BOOLEAN);
               				 $$->size = 1;
							 $$->calculated_type = A_BOOLEAN_TYPE;}

	   | T_FALSE		    {$$=AST_Create_Node(A_BOOLEAN);
               				 $$->size = 0;
							 $$->calculated_type = A_BOOLEAN_TYPE;}

	   | T_NOT factor  		{$$=AST_Create_Node(A_EXPR);
                        	 $$->operator = A_NOT;
                        	 $$->s1 = $2;
							 $$->name = CreateTemp();
							 $$->symbol = Insert($$->name, A_BOOLEAN_TYPE, 0, level, 0, offset);
							 offset++;
							 }
	   ;

// #28
call : T_ID '(' args ')' { 

						struct SymbTab *p;
						//make sure the function exists and is an actual function
						if((p = Search($1, 0, 0)) != NULL) { 
							if(p->IsAFunc != 2) {
							   yyerror("error");
							   printf("%s is not a defined function\n", $1);
							   exit(1);
							}

							//Make sure param and argument list is the same
							if(CompareFormals(p->fparams, $3) != 1){
							   yyerror("error");
							   printf("Parameter and argument type or length mismatch\n");
							   exit(1);
							}//end if
						
						   $$=AST_Create_Node(A_CALL);
            			   $$->s1=$3;
						   $$->calculated_type = p->Type;
            			   $$->name=$1;
						   $$->symbol = p;
          				 }//end if
						   else{
							   yyerror("error");
							   printf("Function %s not defined\n", $1);
							   exit(1);
						   }//end else

						if(mydebug)
						   printf("calling function %s\n", $1);
						}//end call
	 ;

// #29
args : args_list { $$ = $1;}
	 | /*empty*/ {$$=NULL;}
	 ;

// #30
args_list : expression   {
						  $$ = AST_Create_Node(A_ARGSLIST);
				  		  $$->s1 = $1;
						  $$->calculated_type = $1->calculated_type;
						  $$->next = NULL;
						  $$->name = CreateTemp();
						  $$->symbol = Insert($$->name, A_INT_TYPE, 0, level, 1, offset);
						  offset++;
		                 }
		  | expression ',' args_list {
			  			  $$ = AST_Create_Node(A_ARGSLIST);
			  			  $$->s1 = $1;
						  $$->calculated_type = $1->calculated_type;
			 		      $$->next = $3;
						  $$->name = CreateTemp();
						  $$->symbol = Insert($$->name, A_INT_TYPE, 0, level, 1, offset);	
						  offset++;
						             }
		  ;

%%	/* end of rules, start of program */

int main() { 
	yyparse();
	// prints to know when parsed the whole program
	printf("PARSING COMPLETE \n");
	//AST_Print(program, 0);
	Display();
}
