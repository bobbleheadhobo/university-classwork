import sys
from timeit import timeit
import random

def main():
    sys.setrecursionlimit(1500)
    size = 1000
    test = list(random.randint(0, 100) for i in range(size))
    best = sorted(test)
    worst = sorted(test, reverse=True)

    numRuns = 10
    first = 0
    last = size-1


    verify(test, best, worst)

    best = sorted(test)
    worst = sorted(test, reverse=True)
        
    print(f"Size = {size}\nTesting each function {numRuns} times\n")

    # SORTED
    last = len(best)-1
    total_time = timeit(lambda: quickSort(best, first, last), number=numRuns) / numRuns
    print(f"Best Case       AVG TIME: {total_time * 1e6:.2f} micro seconds")

    # DIFFERENT PIVOT AND SORTED
    last = len(best)-1
    total_time = timeit(lambda: quickSort2(best, first, last), number=numRuns) / numRuns
    print(f"Median pivot    AVG TIME: {total_time * 1e6:.2f} micro seconds") 

    # REVERSE SORTED
    last = len(worst)-1
    total_time = timeit(lambda: quickSort(worst, first, last), number=numRuns) / numRuns
    print(f"Worst Case      AVG TIME: {total_time * 1e6:.2f} micro seconds") 


    

def quickSort(A:list, first, last):

    if(first < last):
        q = partition(A, first, last)
        quickSort(A, first, q-1)
        quickSort(A, q+1, last)
    
    return A


def partition(A:list, first, last):
    pivot = A[last]
    i = first - 1


    for k in range(first, last):
        if(A[k] <= pivot):
            i += 1

            # swap 
            (A[i], A[k]) = (A[k], A[i])
    
    # swap
    (A[i+1], A[last]) = (A[last], A[i+1])

    return i+1









# uses a partition with a median pivot
def quickSort2(A:list, first, last):

    if(first < last):
        q = partition2(A, first, last)
        quickSort2(A, first, q-1)
        quickSort2(A, q+1, last)
    
    return A


# uses the median as the pivot
def partition2(A:list, first, last):
    # implementation of median(A[0], A[b(n−1)/2c], A[n −1])
    B = [A[first], A[(last-1)//2], A[last-1]]
    B = sorted(B)
    pivot = B[1]

    index = A.index(pivot)
 
    (A[index], A[last]) = (A[last], A[index])

    
    i = first - 1
    for k in range(first, last):
        if(A[k] <= pivot):
            i += 1
            (A[i], A[k]) = (A[k], A[i])
    
    (A[i+1], A[last]) = (A[last], A[i+1])

    return i+1




def findMedian(A, first, last):
    mid = (first + last) // 2

    if A[first] > A[last]:
        (A[first], A[last]) = (A[last], A[first])
    if A[mid] > A[last]:
        (A[mid], A[last]) = (A[last], A[mid])
    if A[first] > A[mid]:
        (A[first], A[mid]) = (A[mid], A[first])
        
    return A[mid]



def verify(test, best, worst):
    count = 0;
    first = 0;
    last = len(test) - 1

    print("Verifying sorted lists:")

    result = quickSort(best, first, last)
    if(result == best):
        print("✅ Best Case")
        count += 1
    else:
        print("❌ Best Case")
        print(result)
        print(f"{best} (python sort)")
        
    result = quickSort2(test, first, last)
    if(result == best):
        print("✅ Median Pivot")
        count += 1
    else:
        print("❌ Median Pivot")
        print(result)
        print(f"{best} (python sort)")

    result = quickSort(worst, first, last)
    if(result == best):
        print("✅ Worst Case")
        count += 1
    else:
        print("❌ Worst Case")
        print(result)
        print(f"{best} (python sort)")

    print()
    if(count == 4):
        return True
    
    return False


main()