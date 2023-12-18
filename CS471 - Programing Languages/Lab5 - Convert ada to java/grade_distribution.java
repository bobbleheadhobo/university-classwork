//Name: Joey Troyer
//Date: 10/04/22
//input: Zero or more numbers as a grade
//output: The frequency that numbers in 8 different ranges were typed.
//problem: The problem was to convert ada code to java code with one change. The change that we had to 
//         implement was that we were only allowed to update the value of the freq array inside the 
//         catch part of the second half of the first loop.

import java.util.Scanner;

public class grade_distribution {

    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int[] freq = new int[11];
        int index = 0;
        int limit_1;
        int limit_2;

        //loops until user enters a number less than 0
        while(true) {
            int grade = scan.nextInt();

            //if user input is below zero break out of while loop
            try {
                if(grade < 0)
                    throw new Exception();
            }
            catch(Exception e) {
                break;
            }

            index = (grade/10) + 1;

            try {  
                throw new Exception("Error -- new grade " + grade + " is out of range\n");
            }
            catch(Exception e) {
                //fills array with user input if values are valid
                if(grade < 100)
                    freq[index] = freq[index] + 1;
                else if(grade == 100)
                        freq[10] = freq[10] + 1;
                        else
                            System.out.print(e.getMessage());
            }
        }//end while

        System.out.print("\nLimits       Frequency\n ");

        //assigns values to limit_1 and limit_2
        //prints the range of values and frequency they occured
        for(index = 0; index <= 9; index++) {
            limit_1 = 10 * index;
            limit_2 = limit_1 + 9;

            if(index == 9)
                limit_2 = 100;
            
            System.out.printf("%1d", limit_1);
            System.out.printf("%10d",limit_2);
            System.out.printf("%10d\n", freq[index + 1]);
        }//end for
    }//end main
}//end class