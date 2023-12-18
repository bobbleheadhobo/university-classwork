# Name: Joey Troyer
# Date: 10/19/22
# input: file "control-char.txt"
# output: Prints non-corrupt content from file to terminal
# problem: Read in a txt file and print only the characters before ^C aka (control C) and after ^B aka (control B) . 
#          All characters inbetween ^C and ^B are skipped

#open file as an object
with open('control-char.txt', "r") as openfileobject:
        flag = 0;

        #gets each line from object then gets each char from line
        for line in openfileobject:
            for char in line:

                #check if char is ^C
                if (char == '') and flag == 0:
                    flag = 1

                #check if char is ^B
                if (char == '') and flag == 1: 
                    flag = 0

                #if char not inbetween ^C and ^B print to screen 
                if(flag == 0):
                    print(f"{char}",end='')

                    