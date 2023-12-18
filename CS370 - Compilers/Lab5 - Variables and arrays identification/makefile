# lab5
# makefile
# Joey Troyer
# 02/22/22
# purpose: To perform the steps to lex, yacc, gcc and compile all files into a single executable 
# named lab5. Run function to easily compile and run the file. Clean function to easily 
# clean the old executable and .c files


all:	lab5

lab5:  lab5.y lab5.l
		yacc -d lab5.y
		lex lab5.l
		gcc -o lab5 y.tab.c lex.yy.c


run:	lab5
		./lab5
clean: 
		rm -f lab5
		rm -f *.c
