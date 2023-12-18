# Name: Joey Troyer
# Date: 10/19/22
# input: file "control-char.txt"
# output: Prints non-corrupt content from file to terminal
# problem: Read in a txt file and print only the characters before ^C aka (control C) and after ^B aka (control B) . 
#          All characters inbetween ^C and ^B are skipped

$flag = 0;
open (fp, "control-char.txt");

#read char by char until end of file
until (eof(fp)) {
    $char = getc(fp);
  
    #check if char is ^C
    if($char eq '' && $flag == 0) {
       $flag = 1;
    }

    #check if char is ^B
    if($char eq '' && $flag == 1) {
       $flag = 0;
    }

    #if char is not in between ^C and ^B print to screen
    if($flag == 0) {
       print "$char";
    }

}#end while

