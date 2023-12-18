         /* simple lex program which removes comments from a source program
            The main key is that a variable "comment" is set when the start of a comment
            is seen and then unset when the ending set is seen.  It is possible to have
            two starts closed by on end.

            Shaun Cooper
            January 2015
 

            Joey troyer
            1/21/22
            Problem: The file doesn't show the correct line that contains an error in the error message
            Changes: Created a new variable linecount to count each newline. Will display linecount value 
            in error message each time there is a possible nested comment to help debug the problem.
         */
        int comment = 0;
        int debug = 1;  /* prints out debug statements if desired */
        int linecount = 1; /* stores the number of counted new lines */
%%
"/*"	{
	if (comment && debug) fprintf(stderr,
		" >>>>>>>> line %d: Possible Nested comment <<<<<<<<<<\n", linecount);
	comment = 1;
	}

"*/"	{
          if (!comment) printf("%s",yytext); /*print out if it is not in a comment */
  	  comment = 0;
	}

/* will print a new line and increment linecount when it comes across a newline character */
\n {
    printf ("%s", yytext); //prints outs newlines
    linecount++;   //increments linecount
}

.       { if (!comment) printf("%s",yytext);}

%%

int yywrap(void)
{ return 1;
}

int main()
{
  yylex();
  
}

