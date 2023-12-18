# Name: Joey Troyer
# Date: 09/26/22
# input: a number to determine the size of the matrix
# output: the time it take to preform gaussian elimination on the matrix
# problem: The task is to create a program that can generate an matrix with random entires
#           and preform gaussian elimination and backsubstitution on the matrix. The goal
#           was to time how long it would take to solve the matrix for each increase in size

import time
import numpy as np
import random as rand

size = int(input())

matrix = np.zeros(shape=[size,size])

#fill matrix with random float values from 10 to 10000
for x in range(0, size):
    for y in range(0, size):
        matrix[x,y] = float(rand.uniform(10.0, 10000.0))

#create the indent matrix
x = np.zeros(shape= size, dtype=float)

def gaussElim(a,b):
    n = len(b)
    #Gaussian Elimination phase
    for k in range(0,n-1):
        for i in range(k+1,n):
            if a[i,k] != 0.0:
                #if not null define λ
                lam = a [i,k]/a[k,k]
                #we calculate the new row of the matrix
                a[i,k+1:n] = a[i,k+1:n] - lam*a[k,k+1:n]
                #we update vector b
                b[i] = b[i] - lam*b[k]
    # backward substitution
    for k in range(n-1,-1,-1):
        b[k] = (b[k] - np.dot(a[k,k+1:n],b[k+1:n]))/a[k,k]

    return b


#log the time at start
start = time.time()

#call the function with out matrix
gaussElim(matrix, x)

#log time at finish
finish = time.time()

#subtract them to get the time it took
total = finish - start

print(f"{total} in seconds")



