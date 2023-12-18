# lab9
# makefile
# Joey Troyer
# 04/29/22
# purpose: To perform the steps to lex, yacc, gcc and compile all files into a single executable 
# named lab9. Run function to easily compile and run the file. Clean function to easily. 
# clean the old executable file. Test to easily run and test in mars.


all:	lab9

lab9:  lab9.y lab9.l AST.c AST.h symtable.c symtable.h emit.h emit.c
		yacc -d lab9.y
		lex lab9.l
		gcc -o lab9 y.tab.c lex.yy.c AST.c emit.c symtable.c


run:	lab9
		./lab9 -o foo < test.al

test:	lab9
		./lab9 -o foo < test.al
		java -jar Mars45.jar foo.asm sm

clean: 
		rm -f lab9
		rm -f *.asm
