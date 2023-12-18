# lab6
# makefile
# Joey Troyer
# 04/06/22
# purpose: To perform the steps to lex, yacc, gcc and compile all files into a single executable 
# named lab6. Run function to easily compile and run the file. Clean function to easily 
# clean the old executable file


all:	lab7

lab7:  lab7.y lab7.l AST.c AST.h symtable.c symtable.h
		yacc -d lab7.y
		lex lab7.l
		gcc -o lab7 y.tab.c lex.yy.c AST.c symtable.c


run:	lab7
		./lab7
clean: 
		rm -f lab7
