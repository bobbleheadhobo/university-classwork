#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    //1
    FILE *fp;
    char ch;

    //2
    fp = fopen("ConvertCSVinput.txt", "r");

    //3
    if (fp == NULL)
    {
        printf("File is not available \n");
    }
    

    //char cr;
    char cr[2];
    cr[1] = '\0';
    char str[30];
    size_t lines = 0;

    while( cr[0] != EOF ) {
      if ( cr[0] == '\n' ) {
        lines++;
      }
      cr[0] = getc(fp);

      if(cr[0] = ','){
        for(int i = 0; i < 3; i)
      }
      strcat(str,cr);
      printf("%c",str);
    }
    printf("Number of lines: %ld\n", lines); 
    // rewind(fp);



    // char* data[lines];
    // char str[] = "x";
    // char x;

    //     //4
    // while ((ch = fgetc(fp)) != EOF)
    // {       
    //         printf("%c", str);
    //     }

    // //5
    // fclose(fp);

    return 0;
}