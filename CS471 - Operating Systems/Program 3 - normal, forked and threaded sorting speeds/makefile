# Joey Troyer
# 10/13/23

# compiles shared, normal and thread files
all: shared normal thread

shared:
	gcc shared.c -o shared 

normal:
	gcc normal.c -o normal

thread:
	gcc thread.c -lpthread -o thread


clean:
	rm -f shared
	rm -f normal
	rm -f thread