<?php

// Name: Joey Troyer
// Date: 10/19/22
// input: file "control-char.txt"
// output: Prints non-corrupt content from file to terminal
// problem: Read in a txt file and print only the characters before ^C aka (control C) and after ^B aka (control B). 
//          All characters inbetween ^C and ^B are skipped

$flag = 0;
$file = fopen("control-char.txt","r");

//while not at end of file
while (!feof($file)) {

   //read file in char by char
   $char = fgetc($file);

   //check if char is ^C
   if($char == '' and $flag == 0)
      $flag = 1;

   //check if char is ^B
   if($char == '' and $flag == 1)
      $flag = 0;

   //if char is not in between ^C and ^B print to screen
   if($flag == 0)
      echo $char;
  }//end while

fclose($file);
?>
