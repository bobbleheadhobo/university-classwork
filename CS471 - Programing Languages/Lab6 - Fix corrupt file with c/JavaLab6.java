// Name: Joey Troyer
// Date: 10/19/22
// input: file "control-char.txt"
// output: Prints non-corrupt content from file to terminal
// problem: Read in a txt file and print only the characters before ^C aka (control C) and after ^B aka (control B) . 
//          All characters inbetween ^C and ^B are skipped

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;

public class JavaLab6 {

    public static void main(String[] args) throws IOException {

        //open file
        File f=new File("control-char.txt");     
        FileReader fr=new FileReader(f);   
        BufferedReader br = new BufferedReader(fr);

        int c = 0;
        int flag = 0;

        //read in int by int and cast to a character
        while((c = br.read()) != -1) {
            Character chars = (char) c;
            
            //check if character is ^C
            if (chars.equals('') && flag == 0)
                flag = 1;

            //check if character is ^B
            if (chars.equals('') && flag == 1) 
                flag = 0;

            //if character not inbetween ^C and ^B print to screen 
            if(flag == 0)
                System.out.print(chars);
        }//end while

    }//end main
}//end class

