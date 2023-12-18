# Joey Troyer
# Lab2
# 02/23/23
# Purpose: Multiply binary string using long-hand multiplication algorithm

import time


def main():
    x = [1,1,1,1]
    y = [1,0,1,1]
    


    start_time = time.time()
    answer = multiply(x,y)
    end_time = time.time()
    total_time = (end_time - start_time) * 1000000

    print(f"N = {len(x)}  TIME: {total_time} micro seconds")


    # TEST 2
    x = [1,1,1,1,0,0,1,1,0,1]
    y = [1,0,1,1,1,1,0,0,0,1]
    


    start_time = time.time()
    answer = multiply(x,y)
    end_time = time.time()
    total_time = (end_time - start_time) * 1000000

    print(f"N = {len(x)}  TIME: {total_time} micro seconds")


    # TEST 3
    x = [1,1,1,1,0,1,0,1,1,1,0,0,1,1,0,0,1,1,0,1,0,0,1,0,1]
    y = [1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,1,1,1,1,0,1,1,0,0,1]
    


    start_time = time.time()
    answer = multiply(x,y)
    end_time = time.time()
    total_time = (end_time - start_time) * 1000000

    print(f"N = {len(x)}  TIME: {total_time} micro seconds")


    # TEST 4
    x = [1,1,1,1,0,0,1,1,0,1,0,1,0,1,1,1,1,1,1,0,1,0,0,1,1,1,1,1,0,1,0,0,1,0,0,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,1,0,1,1,1,0,1,0]
    y = [1,0,1,1,1,1,0,0,0,0,0,1,1,1,1,0,1,0,1,0,1,0,1,0,1,1,1,1,0,1,0,1,1,0,1,0,1,0,1,0,1,0,1,1,0,1,1,0,0,0,0,0,1,1,0,1,0,1,0,1]
    


    start_time = time.time()
    answer = multiply(x,y)
    end_time = time.time()
    total_time = (end_time - start_time) * 1000000

    print(f"N = {len(x)}  TIME: {total_time} micro seconds")


    # TEST 5
    x = [1,1,1,1,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,1,1,1,0,0,1,0,1,0,1,1,1,0,1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,0,1,0,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,1,0,1,0,1,0,1,1,0,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,1,1,0,1,1,0,1,1,1,0,1,1,1,1,1,1]
    y = [1,0,1,1,1,1,0,0,1,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,0,1,0,1,0,1,1,1,0,0,1,1,0,0,1,0,1,1,0,0,0,1,1,0,1,0,1,1,0,1,0,1,1,1,1,0,1,0,0,1,1,0,0,0,0,0,1,1,0,0,1,0,1,1,0,1,0,0,0,1,0,1,1,0,0,0,1,1,0,0,0,1,1,0,0,0,1,0,0,0,1,1,0,0,1,0,1,0,1,1,0,1,1,1,1,0,1,0,0,1,1,0,0,1,1,1]    


    start_time = time.time()
    answer = multiply(x,y)
    end_time = time.time()
    total_time = (end_time - start_time) * 1000000

    print(f"N = {len(x)}  TIME: {total_time} micro seconds")





def multiply(x,y):
    xSize = len(x)
    ySize = len(y)
    strResult = ""
    result = [0] * xSize 
    finalSize = len(x) + len(y)


    #math time
    for j in range(ySize):
        for i in range(xSize):
            #multiply each value to each value
            strResult = strResult + str(x[i] * y[j])


        #back padding
        for k in range  ((finalSize//2 - j)):
            strResult = strResult + "0"


        #front padding
        for k in range(j):
            strResult = "0" + strResult

        #implicit cast to str
        result[j] = strResult
        strResult = ""
        j = j + 1


    #sum the result
    sum = 0
    finalResult = [0] * finalSize
    
    #add the number in each collum
    #go through each digit in the string
    for j in range (finalSize-1, -1, -1):
        #go through each string in the array
        for i in range(ySize):
            sum = sum + int(result[i][j])
            
        
        finalResult[j] += sum

        carryNum = 0


        #carry over remainder
        if(finalResult[j] > 1 and j != 0):
                if(finalResult[j] % 2 == 0):
                    finalResult[j-1] = finalResult[j] // 2
                    finalResult[j] = 0
                else:
                    finalResult[j-1] = finalResult[j] // 2
                    finalResult[j] = 1

        #check if you need a final carry
        if(finalResult[0] > 1 and j == 0):
            carryNum = finalResult[0]
            if(finalResult[0] % 2 == 0):
                finalResult[0] = 0
            else:
                finalResult[0] = 1

        sum = 0

        strResult = ''.join([str(ch) for ch in finalResult])

        # shrink the result to match the correct size when adding the last carry
        if(carryNum > 0):
            for i in range(carryNum // 2):
                strResult = '1' + strResult
            
            strResult = strResult[:len(strResult) - (carryNum//2)]

        

    return(strResult)
    


main()