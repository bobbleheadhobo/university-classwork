# lab3
# makefile
# Joey Troyer
# 01/25/22
# purpose: To perform the steps to and compile the .c and .h files into a single executable 
# named lab3. Run function to easily compile and run the file. Clean function to easily 
# clean the old executable and .o files

all:	lab3

lab3:	symtable.c
	gcc -c symtable.c
	gcc symtable.c -o lab3

run:	lab3
	./lab3

clean:
	rm -f lab3
	rm -f *.o