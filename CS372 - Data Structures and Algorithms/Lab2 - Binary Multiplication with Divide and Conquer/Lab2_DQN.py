# Joey Troyer
# Lab2
# 02/23/23
# Purpose: Multiply binary string using recurive divide and conquer algorithm without the Gaussion trick

import time


def main():


    x = "1111"
    y = "1011"
    

    start_time = time.time()
    multiply(x,y)
    end_time = time.time()
    total_time = (end_time - start_time) * 1000000

    print(f"N = {len(x)}  TIME: {total_time} micro seconds")


    # TEST 2
    x = "1111001101"
    y = "1011110001"
    

    start_time = time.time()
    multiply(x,y)
    end_time = time.time()
    total_time = (end_time - start_time) * 1000000

    print(f"N = {len(x)}  TIME: {total_time} micro seconds")


    # TEST 3
    x = "1111010111001100110100101"
    y = "1011010101011011111011001"
    

    start_time = time.time()
    multiply(x,y)
    end_time = time.time()
    total_time = (end_time - start_time) * 1000000

    print(f"N = {len(x)}  TIME: {total_time} micro seconds")


    # TEST 4
    x = "111100110101011111101001111101001001010101010101110010111010"
    y = "101111000001111010101010111101011010101010110110000011010101"
    

    start_time = time.time()
    multiply(x,y)
    end_time = time.time()
    total_time = (end_time - start_time) * 1000000

    print(f"N = {len(x)}  TIME: {total_time} micro seconds")


    # TEST 5
    x = "1111000011111111111110000111100101011101011110101011110101011111111111111111100011010101101011111011101110101101001101101110111111"
    y = "1011110010000000111101110101011100110010110001101011010111101001100000110010110100010110001100011000100011001010110111101001100111"
    

    start_time = time.time()
    multiply(x,y)
    end_time = time.time()
    total_time = (end_time - start_time) * 1000000

    print(f"N = {len(x)}  TIME: {total_time} micro seconds")




# Takes in two bit strings and preforms binary addition
# return one string of the sum
def addBinary(x, y):
    n = max(len(x), len(y))

    # #make them the same size
    x = x.zfill(n)
    y = y.zfill(n)

    size = len(x)
    binary = [x, y]
    
    sum = 0
    carryNum = 0
    result = [0] * size;


    #add the number in each collum
    #go through each digit in the string
    for j in range (size-1, -1, -1):
        
        #go through each string in the array
        for i in range(2):
            sum = sum + int(binary[i][j])


        #add result into array
        result[j] += sum


        #carry over remainder
        if(result[j] > 1 and j != 0):
            if(result[j] % 2 == 0):
                result[j] = 0;
                result[j-1] = result[j-1] + 1;
            else:
                result[j] = 1;
                result[j-1] = result[j-1] + 1;

        #check if you need a final carry
        if(result[0] > 1 and j == 0):
            carryNum = result[0]
            if(result[0] % 2 == 0):
                result[0] = 0
            else:
                result[0] = 1

        sum = 0

    #convert array to str
    finalResult = ''.join([str(ch) for ch in result])

    # shrink the result to match the correct size when adding the last carry
    if(carryNum > 0):
        for i in range(carryNum // 2):
            finalResult = '1' + finalResult


    # print(f"finalResult: {finalResult}")
    return(finalResult)

    
# Takes in two bit strings and preforms binary subtraction
# return one string of the difference
def subtractBinary(x, y):
    n = max(len(x), len(y))

    # #make them the same size
    x = x.zfill(n)
    y = y.zfill(n)

    # flip all the bits
    oneComp = ""
    n = len(y)
    for i in range(n):
        if(y[i] == '0'):
            oneComp += '1'
        else:
            oneComp += '0'
    
    one = "1"
    one = str(one.zfill(n))

    #add one to the ones comp of x to get the two comp(subtraction)
    twoComp = addBinary(oneComp, one)


    final = addBinary(x, twoComp)

    #if bigger than x remove the first bit
    if len(final) > len(x):
        final = final[1:]


    return final



def multiply(x:str, y:str):

    n = max(len(x), len(y))


    # #make them the same size
    if(n != 1):
        if(n % 2 != 0):
            n += 1
        x = x.zfill(n)
        y = y.zfill(n)

    #base case
    if n == 1: 
        return int(x[0])*int(y[0])

    fh = n//2  # integer division
    sh = n - fh  # Second half of string

    # split the string in two halves
    xFirst = x[:fh]  
    xSecond = x[sh:]  

    yFirst = y[:fh]
    ySecond = y[sh:]



    #Recursively calculate the three products of inputs of size n/2
    P1 = str(multiply(xFirst, yFirst))

    P2 = str(multiply(xFirst, ySecond))
    P3 = str(multiply(xSecond, yFirst))

    P4 = str(multiply(xSecond, ySecond))


    #shift P1 to left n (P1 * 2^n)
    T1 = str(P1)
    for i in range(n): 
        T1 = T1 + '0'

    T2 = addBinary(P2, P3)

    #shift P2 to left n/2 (P2 * 2^n/2)
    for i in range(n//2): 
        T2 = T2 + '0'


    T3 = str(addBinary(T1, T2))

    final = str(addBinary(T3, P4))


    return final


main()