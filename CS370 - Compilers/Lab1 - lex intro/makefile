# lab1
# makefile
# Joey Troyer
# 01/14/22
# purpose: To perform the steps to lex and compile the file into an executable named lab1. Run
# function has a predetermined file path to feed into the program. Clean function to easily
# clean the old executable files



all:	lab1

lab1: 	wordlengthlab1.l
	lex wordlengthlab1.l
	gcc lex.yy.c -o lab1

run:	lab1
	./lab1 < /etc/passwd

clean: 
	rm -f lab1




