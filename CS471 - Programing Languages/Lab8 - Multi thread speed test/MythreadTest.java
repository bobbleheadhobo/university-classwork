// // from http://www.letmeknows.com/2017/04/24/wait-for-threads-to-finish-java/ //
// This is a very small set up to get people started on using threads
//
//
//  Adopted by Shaun Cooper
//  last updated November 2020
//
//  We need static variable pointers in the main class so that
//  we can share these values with the threads.
//  the threads are address separate from us, so we need to share
//  pointers to the objects that we are sharing and updating
//
//* Edited by Joey Troyer
//* 11/10/22
//* Lab8
//* Input:  Take in an integer from the user
//* Output: The Min, Max, avg and time it took to run the threads and preform calculation on the matrix.
//* Program: This program take in an integer as N from user input and creates a N * N matrix and fills it with random values. 
//*          We start the timer and then create a thread for every row. Each thread is responisble for finding the Min, Max and sum
//*          for the entire row, we save these calculations in results array. Once the thread end we return to main and use the results
//*          array to find to max and min for the entire matrix. We also add all of the sums of each row and divide it by N * N to get 
//*          the average of the entire matrix. We then stop the time and print to the screen the max, min, average and the time it to 
//*          run the threads and preform the other calculations.


import java.util.ArrayList;

public class MythreadTest {
    
    private static ArrayList<Thread> arrThreads = new ArrayList<Thread>();

    // we use static variables to help us connect the threads
    // to a common block
    public static int N=0;

    //stores the matrix
    public static int[][] A;

    //store the max,min and sum of each row
    public static int[][] results;

    //main entry point for the process
    public static void main(String[] args) {
        try {
		int size = Integer.parseInt(args[0]);
		// create the array from input
		A = new int[size][size];
        results = new int[size][3];


		// fill array with random values
		for(int i = 0; i < size; i++)
            for(int x = 0; x < size; x++) {
                A[i][x] = (int) Math.floor(((Math.pow(2, (32-size)) - Math.pow(2, (31-size))) * Math.random() + Math.pow(2,(31-size))));
            }//end for


        //start time
        long startTime = System.nanoTime();

		// create N threads to work on each row
            for (int i = 0; i < size; i++) 
            {
                Thread T1 = new Thread(new ThreadTest(i));                
                T1.start();                 // standard thread start
                arrThreads.add(T1);
            } 
            
	    // wait for each thread to complete
            for (int i = 0; i < arrThreads.size(); i++) 
            {
                arrThreads.get(i).join(); 
            } 

	    // all the threads are done
	    // do final calculations
	    System.out.println("Main Thread has N as value " + N) ;
            
            int finalmax = results[0][0];
            int finalmin = results[0][0];
            int avg = 0;

            //find the max and min for whole matrix
            //and adds up the sum of each row in matrix into avg
            for(int i = 0; i < size; i++){
                finalmax = Math.max(finalmax, results[i][0]);
                finalmin = Math.min(finalmin, results[i][1]);
                avg =+ results[i][2];
            }//end for

            //divide total sum by number of elements in the matrix to get average
            avg = avg / (size * size);

            //end time
            long endTime = System.nanoTime();
            long timeElapsed = endTime - startTime;

            //prints final calculations
            System.out.printf("max: %-8d\n", finalmax);
            System.out.printf("min: %-8d\n", finalmin);
            System.out.printf("average: %d\n", avg);

            System.out.println("Execution time in milliseconds: " + timeElapsed / 1000000);
            
            System.out.println("Main thread exiting ");
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }//end main
}//end class

// each thread should access its row based on "ind"
// and leave results I would suggest in a static array that you need
// to create  in MythreadTest
class ThreadTest implements Runnable {
     private int i;
     ThreadTest(int ind) 
     {
        i = ind;
     }
     public void run() {
        try
        {
    	    MythreadTest.N += i ; // this is a global variable in MythreadTest we add stuff together;

            //initalizing max, min with first value of row to keep data integerity
            int size = MythreadTest.A[i].length;
            int max = MythreadTest.A[i][0];
            int min = MythreadTest.A[i][0];
            int sum = 0;

            //find min, max and sum of matrix row
            for(int x = 0; x < size; x++){
                max = Math.max(max, MythreadTest.A[i][x]);
                min = Math.min(min, MythreadTest.A[i][x]);
                sum += MythreadTest.A[i][x];
            }//end for

            //save calulations into results array
            MythreadTest.results[i][0] = max;
            MythreadTest.results[i][1] = min;
            MythreadTest.results[i][2] = sum;

            Thread.sleep(1000);
            System.out.println("Thread is exiting " + i);
        }
        catch (Exception e) {
            System.out.println(e.getMessage());
        }     }//end run
}//end class
