/*
            Joey troyer
            Lab6
            3/17/22
            Purpose: It scans the characters and returns the appropriate tokens. Will either scan for 
                     an exact word or set of characters. Also has the functionality to scan for a range
                     of characters and numbers using regular expressions. If it finds a terminal it will 
                     return the corresponding token.
            
            
*/

%{
int lineno = 1;
int mydebug = 0;
#include "AST.h"
#include "y.tab.h"
%}


%%

int                 {return(T_INT);}
void                {return(T_VOID);}
boolean             {return(T_BOOLEAN);}
begin               {return(T_BEGIN);}
end                 {return(T_END);}
of                  {return(T_OF);}
read                {return(T_READ);}
write               {return(T_WRITE);}
return              {return(T_RETURN);}
"=="                {return(T_EQ);}
"<="                {return(T_LE);}
">="                {return(T_GE);}
"!="                {return(T_NE);}
or                  {return(T_OR);}
and                 {return(T_AND);}
true                {return(T_TRUE);}
false               {return(T_FALSE);}
not                 {return(T_NOT);}
if                  {return(T_IF);}
then                {return(T_THEN);}
else                {return(T_ELSE);}
while               {return(T_WHILE);}
do                  {return(T_DO);}

[a-zA-Z_][a-zA-Z0-9_]*	 {if (mydebug) fprintf(stderr,"ID found\n");  /* find variables names gives a copy to yacc and then returns the T_ID token */
                          yylval.ID=strdup(yytext); return(T_ID);}

[0-9][0-9]*	             {if (mydebug) fprintf(stderr,"Digit found\n");  /* finds numbers gives a copy to yacc and then returns T_NUM token */
                          yylval.value=atoi((const char *)yytext); return(T_NUM);}

[ \t]		             {}
[+\-(),;/[\]*<>=] 	     {return (*yytext);} /*single character tokens*/
\/\/.*                   { /* do nothing */ }
\n 		                 {lineno++;}

%%

int yywrap(void)
{ return 1;}


