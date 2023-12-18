# lab4
# makefile
# Joey Troyer
# 02/13/22
# purpose: To perform the steps to lex, yacc, gcc and compile all files into a single executable 
# named lab4. Run function to easily compile and run the file. Clean function to easily 
# clean the old executable and .c files


all:	lab4

lab4:  lab4docalc.y lab4docalc.l symtable.c symtab.h
		yacc -d lab4docalc.y
		lex lab4docalc.l
		gcc -o lab4 y.tab.c symtable.c lex.yy.c


run:	lab4
		./lab4
clean: 
		rm -f lab4
		rm -f lex.yy.c
