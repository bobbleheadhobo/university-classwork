#include <stdio.h>

int main() {
    char c;
    int in = 0;

    while (scanf("%c", &c) != EOF) {
        if(c == '') in = 1;
        if(c == '') in = 0;
        if(in == 0) printf("%c", c);

    }

}