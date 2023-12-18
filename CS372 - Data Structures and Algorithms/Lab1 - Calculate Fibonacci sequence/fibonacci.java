// Joey Troyer
//02/01/23
//Lab1

import java.util.Scanner;

class fibonacci {
    public static void main(String[] args) {
        int result = 0;
        long begin = 0;
        long end = 0;
        long firstTime = 0;
        long secondTime = 0;
        
        System.out.println("index     First     Second");
        for(int n = 0; n <= 20; n++) {

        //First Attempt
        begin = System.nanoTime();
        fib1(n);
        end = System.nanoTime();

        firstTime = end-begin;

        //Second attempt
        begin = System.nanoTime();
        fib2(n);
        end = System.nanoTime();

        secondTime = end-begin;

        System.out.printf("%5d %8d %8d\n", n, firstTime, secondTime);
        }//end for
    
    }//end main
    

    public static int fib1(int n){
        if(n == 0) 
            return 0;

        if(n == 1)
            return 1;

        return (fib1(n-1) + fib1(n-2));
        
    }//end fib1


    public static int fib2(int n) {
        if(n == 0)
            return 0;
        
        int[] f = new int[n+1];
        f[0] = 0;
        f[1] = 1;

        for(int i = 2; i <= n; i++) {
            f[i] = f[i-1] + f[i-2];
        }

        return f[n];
    }//end fib2

}//end class