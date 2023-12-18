/**
 * @file lab1.c
 * @author Joey Troyer
 * @date 2022-08-23
 * @input A name in decimal ascii code
 * @output A string of a name printed to the terminal
 * @pre An Int array and char pointer and little endian architecture
 * @post A char pointer with the name as a string
 */

#include <stdio.h>
#include <stdlib.h>

int g; //global

int main() {
    char *s;
    int n[100]; 
    //      y                       e                 o           J
    n[0] = 121 * 256 * 256 * 256 + 101 * 256 * 256 + 111 * 256 + 74;
    //      o                       r                T        space
    n[1] = 111 * 256 * 256 * 256 + 114 * 256 * 256 + 84 * 256 + 32;
    //    null                    r                 e           y
    n[2] = 0 * 256 * 256 * 256 + 114 * 256 * 256 + 101 * 256 + 121;
    
    s = (char *) n;

    printf("My name is: %20s\n", s);
    printf("n location %20u\n", &n);
    printf("s location %20u\n", &s);
    printf("g location %20u\n", &g);
    printf("n[2] value %20x\n", n[2]);

}

