/*                 Small LEX routine which returns two formal tokens (INTEGER and VARIABLE)
                   along with single string elements like '+'.
 
                   This LEX definition is the companion to the lab4docalc.y YACC routine which
                   is a simple calculator

                   Shaun Cooper
                   January 2015

        ------------------------------------------------------------------------
            Joey troyer
            2/13/22
            Purpose: It scans each character such as variable names or newline characters and 
            preforms the appropriate action depending on the input.
            
            
*/

%{

int mydebug=1;
#include "y.tab.h"
%}


%%

int         {if (mydebug) fprintf(stderr, "INT found\n");
             return(INT);}

[a-zA-Z][a-zA-Z0-9]*		{if (mydebug) fprintf(stderr,"VARIABLE found\n");  // changed to work with longer variable names
                       yylval.ID=strdup(yytext); return(VARIABLE);}
[0-9][0-9]*	{if (mydebug) fprintf(stderr,"Digit found\n");  
                       yylval.value=atoi((const char *)yytext); return(INTEGER);}
[ \t]		{if (mydebug) fprintf(stderr,"Whitespace found\n");}
[;()=\-+*/%&|] 	{ if (mydebug) fprintf(stderr,"return a token %c\n",*yytext);  
                       return (*yytext);}
\n 		{ if (mydebug) fprintf(stderr,"cariage return %c\n",*yytext); 
                       return (*yytext);}

%%

int yywrap(void)
{ return 1;}


