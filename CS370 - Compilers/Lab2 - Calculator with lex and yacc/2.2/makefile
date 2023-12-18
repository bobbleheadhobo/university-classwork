# lab2.2
# makefile
# Joey Troyer
# 01/22/22
# purpose: To perform the steps to lex, yacc and compile the two files into a single executable 
# named lab2docalc. Run function to easily compile and run the file. Clean function to easily 
# clean the old executable and .c files
#
# List the file names created by YACC: y.tab.c
# List the file names created by LEX: lex.yy.c
# Why do we NOT directly compile LEX output?: We dont compile it directly
#              because we need the yacc counterpart to work with the file

all:	lab2docalc

lab2docalc:	lab2docalc.l lab2docalc.y
		yacc -d lab2docalc.y
		lex lab2docalc.l
		gcc y.tab.c -o lab2docalc

run:	lab2docalc
		./lab2docalc
clean: 
		rm -f lab2docalc
		rm -f lex.yy.c
