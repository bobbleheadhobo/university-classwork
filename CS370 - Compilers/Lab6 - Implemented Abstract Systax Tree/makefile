# lab6
# makefile
# Joey Troyer
# 02/22/22
# purpose: To perform the steps to lex, yacc, gcc and compile all files into a single executable 
# named lab6. Run function to easily compile and run the file. Clean function to easily 
# clean the old executable file


all:	lab6

lab6:  lab6.y lab6.l AST.c AST.h
		yacc -d lab6.y
		lex lab6.l
		gcc -o lab6 y.tab.c lex.yy.c AST.c


run:	lab6
		./lab6
clean: 
		rm -f lab6
