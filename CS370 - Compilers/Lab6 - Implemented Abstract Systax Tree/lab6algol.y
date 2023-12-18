%{
/*
 *			**** CMINUS ****
 *
 *
 */

/* 
   This lab is designed for you to create YACC directives using the EBNF description of Cminus.

   You are to take the EBNF of ALGOL and create YACC rules that will syntically check if an input
   program is syntactically correct.  You DO NOT have to do any type checking or any checking if an ID 
   has been defined.  

   The nice part of YACC is that it will do the checking for you as long as you define things correctly.
   You will need to report any syntax errors on the appropriate line.  If possible, you should have YACC
    continue with the parsing until end of file

   You will need to ensure that you define your tokens properly and with the correct return values.

   Shaun Cooper
    January 2015
    January 2019
    January 2022


   THIS IS A TRUNCATED VERSION OF THE ALGOL EBNF in YACC

*/


	/* begin specs */
#include <stdio.h>
#include <ctype.h>
#include "ast.h"


extern int linecount; // set by LEX routine

void yyerror (s)  /* Called by yyparse on error */
     char *s;
{
  printf ("%s on line %d\n", s, linecount);
}



%}
/*  defines the start symbol, what values come back from LEX and how the operators are associated  */

%start P

%union {
      int value;
      char * string;
      ASTnode * node;
      enum OPERATORS operator;
      
}



%token <value> T_NUM T_INT T_VOID T_WHILE T_DO T_IF T_THEN T_ELSE T_READ T_WRITE T_FOR T_RETURN T_LE T_GE T_EQ T_NE T_LT T_GT
%token  <string> T_ID 
%token T_MYBEGIN T_MYEND T_OF T_BOOLEAN
%token T_AND T_OR T_NOT T_MYTRUE 
%type <operator> relop addop 



%%	/* end specs, begin rules */

P	:	DL   /* PRogram -> Declartion-list */
                {program=$1;}
	;

DL	:	DEC  { $$=$1;}   /*  Declaration-list -> Declaration { Declaration} */
        |      DEC DL   {$1->next=$2; $$= $1; /*next connect declarations */
                        if (mydebug)  ASTprint(0,$1);
                        if (mydebug) ASTprint(0,$2);
                       }
        ;

DEC	: VARDEC  {$$=$1;} 
        | FUNDEC  {$$=$1;} /*  Declaration -> Variable-Declaration | Function-Declaration */
        ;

VARDEC	: typespec varlist  ';' {$$ = $2; 
                                //we need to go through the entire varlist and set the type of variable using $1 
                                }  ;
       


varlist: T_ID   { /* search symbol table for ID
                              insert if OK, then add the pointer from 
                              insertion into the  ASTnode to have reference
                              to the symbol table entry */
                            $$=ASTCreateNode(A_VARDEC); 
        
                            $$->name=$1; /* this changes to symbol table*/
                           } 
 	|  T_ID  '[' T_NUM ']' 
                  { /* search symbol table for ID, if not, place in there with size of array*/

                            $$=ASTCreateNode(A_VARDEC); 
                            $$->name=$1; /* this changes to symbol table*/
                            $$->value=$3; /* remember dimension*/
                            printf("found an array declaration \n");
                  }
        | T_ID ',' varlist 
 	|  T_ID  '[' T_NUM ']'  ',' varlist
                         
        ;

typespec	: T_INT  {$$=INTTYPE;}
                | T_VOID 
                | T_BOOLEAN 
                ;

FUNDEC	:  typespec T_ID '(' params ')' compoundstmt
                         { /* search symbol table for ID
                              insert if OK, then add the pointer from 
                              insertion into the  ASTnode to have reference
                              to the symbol table entry */

                            /* need to add paramater listing */
                            $$=ASTCreateNode(A_FUNCTIONDEC); 
                            $$->name=$2; /* this changes to symbol table*/
                            $$->operator=$1; /* remember the declaration type */
                           } 

                   
        ;

params	: VOID  { $$=NULL; /*no paramater list */}
        |  paramlist { $$= $1;}
        ;

 
/*  Parmlist is a next list of parameters, name and type are the node itself no s1 parameter */

paramlist	: param  { $$ = $1;}
                | param ', paramlist 
              	;

param	:	typespec T_ID { /* symbol table function level add/check */
                              $$=ASTCreateNode(A_PARAM);
                              $$->name=$2; 
                              $$->operator=$1;
                              $$->value=0; /* not an array */
                            }
	|	typespec T_ID '[' ']'
	;

   /* need to fix this to include local declarations into symbol table*/
compoundstmt : T_MYBEGIN localdeclarations statementlist T_MYEND  
                      {  $$=ASTCreateNode(A_BLOCK);
                             $$->s1=$2;
                             $$->s2=$3;
                       }
 	      ;

localdeclarations :  VARDEC localdeclarations {$1->next=$2; $$=$1;}
                  | /* empty */ { $$=NULL;}
                   ;

/* for statements , next is the next statement, s1 is what this statement is */
statementlist :  /* empty */ {$$=NULL;}
              | statement statementlist 
              ;

statement : 	expressionstmt  
		| compoundstmt	
		| selectionstmt	
		| iterationstmt	
		| assignmentstmt
		| returnstmt	
		| readstmt	
		| writestmt     
                ;

expressionstmt : expression ';'  { $$=ASTCreateNode(A_EXPRSTMT);
                                  $$->s1=$1;}
		| ';'  { $$=NULL;}
 		;

assignmentstmt : var '=' expressionstmt 
                      {$$=ASTCreateNode(A_ASSIGN);
                          /* Assignment statement  we leave next alone so that
                             it can be strung with other statements	*/ 
                      }
               ;




selectionstmt : T_IF  expression T_THEN statement 
               | T_IF  expression T_THEN statement T_ELSE statement 
               ;

iterationstmt : T_WHILE  expression T_DO statement
                               {$$=ASTCreateNode(WHILESTMT);
                                $$->s1=$2;
                                $$->s2=$4;}
               ;

returnstmt : T_RETURN ';'  { $$=ASTCreateNode(A_MYRETURN);}
            |  T_RETURN expression  ';'  { $$=ASTCreateNode(A_MYRETURN);
                                         $$->s1=$2;}
            ;

readstmt : T_READ var ';' { /* make sure variable is in symbol table */
                        }
          ;


writestmt : T_WRITE expression ';' 
          ;


expression :   simpleexpression {$$=$1;}
           ;


var	: T_ID   
                /* we want to create a NODE called IDENTIFIER with a pointer to the SYMBOL table */
               { $$=ASTCreateNode(A_IDENT);
	         $$->name=$1; /*change this to pointer to symbol table */
		 }
                 
	| T_ID  '[' expression ']'
    	;


simpleexpression : additiveexpression  {$$=$1;}
                  | additiveexpression relop additiveexpression 
                       {$$=ASTCreateNode(A_EXPR);
                        $$->s1=$1;
                        $$->s2=$3;
                        $$->operator=$2;}
        
                  ;


relop : T_LE {$$=LESSTHANEQUAL;}
      ;

additiveexpression : term  {$$=$1;}
                    | additiveexpression addop term  
                    ;

addop : '+'  {$$=PLUS;}
      | '-'  {$$=MINUS;}
      ;

term : factor  {$$=$1;}
     | term  multop factor 
     | term  T_AND factor 
     | term  T_OR factor 
     ;

multop : '*' {$$=TIMES;}
       ;

factor : '(' expression ')'  {$$=$2;}
       | T_NUM  
               { $$=ASTCreateNode(A_NUMBER);
                $$->value=$1;
		 }
       | var  
       | call 
       | T_NOT factor 
               { $$=ASTCreateNode(A_EXPR);
                $$->operator=MYNOT;
                $$->s1=$2;
		 }
       | T_MYTRUE
               { $$=ASTCreateNode(A_NUMBER);
                $$->value=1;
	       }
       | T_MYFALSE
       ;

call : T_ID '(' args ')' 
          { $$=ASTCreateNode(A_CALL);
            $$->s1=$3;
            $$->name=$1;  /*symbol table check */
          }
     ;

args : arglist {$$=$1;}
      | {$$=NULL;} /* empty */
     ;

arglist : expression  
         | expression ',' arglist 
         ;



%%	/* end of rules, start of program */
int main(int argv, char * argc[])
{ 
  if (argv > 2) mydebug=1;
  yyparse();
  fprintf(stderr,"the input has been syntactically checked\n");
  ASTprint(0,program);
}
