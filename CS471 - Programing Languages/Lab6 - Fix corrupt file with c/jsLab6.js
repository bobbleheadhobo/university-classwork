// Name: Joey Troyer
// Date: 10/19/22
// input: file "control-char.txt"
// output: Prints non-corrupt content from file to terminal
// problem: Read in a txt file and print only the characters before ^C aka (control C) and after ^B aka (control B). 
//          All characters inbetween ^C and ^B are skipped

const fs = require('fs');

let flag = 0;
let data = fs.readFileSync('control-char.txt', 'utf-8');

//read in file char by char
for (const ch of data) {

    //check if char is ^C
    if (ch == '' && flag == 0)
        flag = 1;
    
    //check if char is ^B
    if (ch == '' && flag == 1)
        flag = 0;

    //if char is not in between ^C and ^B print to screen
    if(flag == 0)
        process.stdout.write(ch);
}//end for
