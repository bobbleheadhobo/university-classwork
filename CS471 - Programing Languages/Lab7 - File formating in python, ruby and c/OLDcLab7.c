#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{

  // Open File
  const char fname[] = "ConvertCSVinput.txt";

  FILE *fp = fopen(fname, "r");

  if( !fp )
    printf("Error Opening file");

  printf("Opened file: %s\n", fname); 

  // Count Lines
  char cr;
  size_t lines = 0;

  while( cr != EOF ) {
    if ( cr == '\n' ) {
      lines++;
    }
    cr = getc(fp);
  }
  printf("Number of lines: %ld\n", lines); 
  rewind(fp);

  // Read data
  // 'goto' + data[lines] causes error, introduce block as a workaround
    char *data[lines][2];
    size_t n;
    size_t i = 0;
    int x = 0;
    char *line;
    char *token;

    while(i < lines) {
      data[i][x] = NULL;
      size_t n = 0;
      //printf("i=%d  x=%d\n", i,x);
      getline(&line, &n, fp);

      printf("%s\n\n", line);
      token = strtok(line, ",");
      while( token != NULL) {
      
      //printf("%s\n",data[i][x]);
      //data[i][x] = line;
      printf("%s\n",line);
      token = strtok(NULL, ",");
      }

      x++;

      
      if(x > 2) {
        x = 0;
        i++;
      }

      
    }

    // for (size_t i = 0; i < lines; i++) {
    //   for(int x = 0; x < 3; x++)
    //   printf("%s\n", data[i][x]);
    // }
  

  //printf("\n%s",data[2][0]);

  // Close File
  fclose(fp);

  return 0;
}