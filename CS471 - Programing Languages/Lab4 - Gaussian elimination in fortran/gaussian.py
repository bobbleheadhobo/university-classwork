# Name: Joey Troyer
# Date: 09/26/22
# input: a number to determine the size of the matrix
# output: the time it take to preform gaussian elimination on the matrix
# problem: The task is to create a program that can generate an matrix with random entires
#           and preform gaussian elimination and backsubstitution on the matrix. The goal
#           was to time how long it would take to solve the matrix for each increase in size

import math
import random as rand
import time

#gets input from user and casts it as an int
size = int(input())

#creates the matrixs
matrix = [[0] * (size + 1) for i in range(0, size)]
b = [0] * size
x = [0] * size

#loop to fill the matrix with random float numbers from range 10 to 100000
for col in range(0, size):
    for row in range(0, size+1):
        matrix[col][row] = float(math.floor(rand.uniform(10.0, 10000.0)))

#function to make it easy to perform the operation
def gauss(matrix, x):

    #loops to perform gaussian elimination
    for k in range(size - 1):
        for i in range(k+1, size):
            factor = matrix[i][k] / matrix[k][k]
            for j in range(k, size):
                matrix[i][j] = matrix[i][j] - factor * matrix[k][j]
            b[i] = b[i] - factor * b[k]

    #back tracing
    for i in range(size-1, -1, -1):
        sum = matrix[i][size]
        for j in range(i+1, size):
            sum = sum - matrix[i][j] * x[j]
        x[i] = sum/matrix[i][i]

#logs time at start
start = time.time()

#call the function
gauss(matrix, x)

#logs time at end
finish = time.time()

#subtracts finish by start time to get the time it took to run the function
total = (finish - start)

print(f"{total} in seconds")
