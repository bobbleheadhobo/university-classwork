// Name: Joey Troyer
// Date: 10/31/22
// input: file "ConvertCSVinput.txt"
// output: write formatted output to a "C_Output.txt" from the "ConvertCSVinput.txt"
// problem: Read in a txt with each word seperated by a coma and format it and write it to a different file
// algorithm: Read in file line by line int a char[]. Use a for loop to fill a different char[] character by 
//            character while replacing ; and capitalizing the proper letters. Write out both char[] to file
//            line by line.


#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char line[256];
    FILE* readFile = fopen("ConvertCSVinput.txt", "r");
    FILE* writeFile = fopen("C_Output.txt", "w");
    int flag = 0;

    //read in file line by line and stores in var "line"
    while (fgets(line, sizeof(line), readFile)) {

        //different iterator variable for edit array
        //to handle different string sizes
        int x = 0;

        //char array to fill with formated data
        //initalizes a new char array every loop to get rid of previous data
        char edit[256] = "";

        //removes all new lines from var "line"
        line[strcspn(line, "\n")] = 0;

        //captializes first char in edit
        edit[x++] = toupper(line[0]);

        //for loop that fills edit char by char
        //iterates through the length of line minus 5 so we dont copy over ".jpg"
        for(int i = 1; i <= (strlen(line) - 5); i++ ) {

            //if theres a coma add " ", ";", " " to each next array index of edit
            //set flag = 1 because we know the next char needs to be capitlaized
            if(line[i] == ',') {
                edit[x++] = ' ';
                edit[x++] = ';';
                edit[x++] = ' '; 
                flag = 1;
            }

            //Set incoming char to uppercase
            else if(flag == 1) {
                    edit[x++] = toupper(line[i]);
                    flag = 0;
            }
            else {
            //just copy data from line into next index of edit
                edit[x++] = line[i];
            }
        }//end for

        //write to file the formated data line by line
        fprintf(writeFile,"%s ; %s ;\n",line, edit);

    }//end while
    return 0;

}//end main
