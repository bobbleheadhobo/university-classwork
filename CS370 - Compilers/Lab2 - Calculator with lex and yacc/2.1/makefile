# lab2.1
# makefile
# Joey Troyer
# 01/21/22
# purpose: To perform the steps to lex and compile the file into an executable named lab2.1. Run
# function has a predetermined file path to feed into the program. Clean function to easily
# clean the old executable and .c files



all:	lab2.1

lab2.1: 	lab2remove.l
	lex lab2remove.l
	gcc lex.yy.c -o lab2.1

run:	lab2.1
	./lab2.1 < comment.tst

clean: 
	rm -f lab2.1
	rm -f lex.yy.c