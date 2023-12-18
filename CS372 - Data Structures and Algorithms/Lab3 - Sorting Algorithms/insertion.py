from timeit import timeit
import random

def main():
    numRuns = 100
    size = 1000

    # create list of random ints
    test = list(random.randint(0, 1000) for i in range(size))
    best = sorted(test)
    worst = sorted(test, reverse=True)
    fixed = [8] * size

    verify(test, best, worst, fixed)

    best = sorted(test)
    worst = sorted(test, reverse=True)
    fixed = [8] * size

    print(f"Size = {size}\nTesting each function {numRuns} times\n")

    # PRE SORTED
    total_time1 = timeit(lambda: insertionSort(best), number=numRuns) / numRuns
    print(f"Best Case      AVG TIME: {total_time1 * 1e6:.2f} micro seconds")

    # PRE REVERSE SORTED
    total_time = timeit(lambda: insertionSort(worst), number=numRuns) / numRuns
    print(f"Worst Case     AVG TIME: {total_time * 1e6:.2f} micro seconds")  

    # FIXED CASE
    total_time = timeit(lambda: insertionSort(fixed), number=numRuns) / numRuns
    print(f"Fixed Case     AVG TIME: {total_time * 1e6:.2f} micro seconds")  

    # PRE SORTED WILL SORT IN REVERSE
    total_time = timeit(lambda: reverseInsertionSort(best), number=numRuns) / numRuns
    print(f"Reverse Case   AVG TIME: {total_time * 1e6:.2f} micro seconds")



   



def insertionSort(A:list):
    for i in range(1, len(A)):
        key = A[i]

        k = i-1
        while k >= 0 and key < A[k]:
                A[k+1] = A[k]
                k -= 1
        A[k+1] = key

    return A




def reverseInsertionSort(A:list):
    for i in range(1, len(A)):
        key = A[i]

        k = i-1
        while k >= 0 and key > A[k]:
                A[k+1] = A[k]
                k -= 1
        A[k+1] = key

    return A




def verify(test, best, worst, fixed):
    count = 0;

    print("Verifying sorted lists:")


    result = insertionSort(best)
    if(result == best):
        print("✅ Best Case")
        count += 1
    else:
        print("❌ Best Case")
        print(result)
        print(f"{best} (python sort)")


    result = insertionSort(worst)
    if(result == best):
        print("✅ Worst Case")
        count += 1
    else:
        print("❌ Worst Case")
        print(result)
        print(f"{best} (python sort)")


    result = insertionSort(fixed)
    if(result == fixed):
        print("✅ Fixed Case")
        count += 1
    else:
        print("❌ Fixed Case")
        print(result)
        print(f"{fixed} (python sort)")


    result = reverseInsertionSort(best)
    if(result == best):
        print("✅ Reverse Case")
        count += 1
    else:
        print("❌ Reverse Case")
        print(result)
        print(f"{best} (python sort)")

    print()
    if(count == 5):
        return True
    
    return False

main()