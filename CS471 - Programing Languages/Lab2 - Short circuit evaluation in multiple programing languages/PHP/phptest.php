<?php
// file phptest.php
// author Joey Troyer
// date 2022-09-01
// pre none
// post output to the terminal


        // test function to be called
        function func() {
            echo "I have been evaluated!!!\n";
            return 1;
        }//end func

        //start of short circuit operators
        $var = 1;
        
        echo "AND evaluation using &&\n";
        for($i = 0; $i < 2; $i++) {
            //left hand side starts false then next loop is true
            if( $i == 1 && func()) 
                echo "true\n";
            else
                echo "false\n";

            echo "  next\n";
        }//end for

        echo "\n";

        echo "OR evaluation using ||\n";
        for($i = 0; $i < 2; $i++) {
            //left hand side starts false then next loop is true
            if( $i == 1 || func()) 
                echo "true\n";
            else 
                echo "false\n";

            echo "  next\n";
        }//end for


        //start of other short circuit operators
        $var = 1;
        
        echo "AND evaluation using and\n";
        for($i = 0; $i < 2; $i++) {
            //left hand side starts false then next loop is true
            if( $i == 1 and func()) 
                echo "true\n";
            else
                echo "false\n";

            echo "  next\n";
        }//end for

        echo "\n";

        echo "OR evaluation using ||\n";
        for($i = 0; $i < 2; $i++) {
            //left hand side starts false then next loop is true
            if( $i == 1 or func()) 
                echo "true\n";
            else 
                echo "false\n";

            echo "  next\n";
        }//end for


        //start of eager operators
        $var = 1;
        
        echo "AND evaluation using &\n";
        for($i = 0; $i < 2; $i++) {
            //left hand side starts false then next loop is true
            if( $i == 1 & func()) 
                echo "true\n";
            else
                echo "false\n";

            echo "  next\n";
        }//end for

        echo "\n";

        echo "OR evaluation using |\n";
        for($i = 0; $i < 2; $i++) {
            //left hand side starts false then next loop is true
            if( $i == 1 | func()) 
                echo "true\n";
            else 
                echo "false\n";

            echo "  next\n";
        }//end for
?>


