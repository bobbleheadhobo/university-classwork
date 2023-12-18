// Joey Troyer
// 10/13/23
//purpose: To perform merge sort on 8 different threads

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>





int *in;
int *out;

// struct for the thread
typedef struct {
    int beg; 
    int end;
} ThreadData;

/* subroutine which takes locations and merges the results into "out[]"
   and then places the result into "in[]".  Note that this routine uses
   two global vectors and this routine assumes that it can work with
   both of them 
*/

void merge(int loc1,int loc2,int loc3,int loc4)
{
   /* variable i is used to index in the first half
      variable j is used to index the second half 
      variable insert is used to keep track in the out[] vector in inserts
   */

   int i,j,k,insert;

   insert=loc1;
   i=loc1;
   j=loc3;

   /* merge the two sub arrays -- we assume the lists are contiguous */
   while ( (i <= loc2) && ( j <= loc4))
     {
         if ( in[i] > in[j])
	   out[insert++]=in[j++];
	 else
	   out[insert++]=in[i++];
     }

   /* take care of any of the remainder in first segment */
   for(k=i;k<=loc2;k++)
      out[insert++]=in[k];

   /* take care of any of the remainder in second segment */
   for(k=j;k<=loc4;k++)
      out[insert++]=in[k];

   /* transfer the merged data back to the original vector */
   for(i=loc1;i<=loc4;i++)
      in[i]=out[i];


}


/* recursive calls to sort: break the vector up into single units.
   subroutine merge is then used to place the results back together
*/

void sort(int loc1, int loc2)
{ int mid;

  /* base case */
  if (loc1 >=loc2) return;

  /* recursive call, calculate mid point, and bisect the segment */
  else

    {  mid=((loc1 + loc2)/2);
       sort(loc1,mid);
       sort(mid+1,loc2);
       merge(loc1,mid,mid+1,loc2);
    }

}


/* helper subroutine to print out the results of the in[] vector,
   one line at a time */

void printar(int NUM)
{
   int i;

   for(i=0;i<NUM;i++)
     printf("%d\n",in[i]);

  printf("\n");

}

// function that the threads will run and sort their part of the array
void* thread_sort(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    int beg = data->beg;
    int end = data->end;

    sort(beg, end);

    return NULL;
}

int main(int argc, char *argv[])
{
  int i;
  struct timespec starttimer, endtimer;
  int segments = 8;
  pthread_t threads[segments];
  ThreadData threadData[segments];



   if(argv[1] == NULL){
      printf("Please input size of the array\n");
      exit(1);
   }

   i = atoi(argv[1]);



   // Dynamically allocate memory for 'in' the array
   in = (int *)malloc(i * sizeof(int));
   if (in == NULL) {
       perror("Memory allocation failed!\n");
       return 1;
   }

   // Dynamically allocate memory for 'out' the array
   out = (int *)malloc(i * sizeof(int));
   if (out == NULL) {
       perror("Memory allocation failed!\n");
       return 1;
   }

   // make random number actually random
   srand(time(NULL));

    // Fill the array with random integers between 0 and 99 inclusive
    for (int x = 0; x < i; x++) {
        in[x] = rand() % 100;
    }

   printf("Randomly generator %d numbers\n", i);

   // start timer
   if(clock_gettime(CLOCK_MONOTONIC, &starttimer) != 0){
   perror("Error starting timer!");
   exit (1);
   }


  /* too few items, no need to fork */
  if ( i <= 8 )
   {
     sort(0,i);
   }

  else {
        // divide array size in to 8 segements
        int segment_size = i / segments;

        for (int k = 0; k < segments; k++) {

        //give thread k it start point
        threadData[k].beg = k * segment_size;
        if(k == segments - 1) // if on the last thread give rest of array
            threadData[k].end = i;
        else
            threadData[k].end = threadData[k].end + segment_size; //give thread k the end of it segment

        // create the threads and have them run thread sort
        pthread_create(&threads[k], NULL, thread_sort, &threadData[k]);
    }

    // wait for the threads to finish
    for (int k = 0; k < segments; k++) {
        pthread_join(threads[k], NULL);
    }


    int end2, beg2;
    //merge the array together
    for (int k = 1; k < segments; k++) {
        int beg = 0; // start of the merged result always begins from 0
        int end = k * segment_size - 1; // end of the already merged result

        beg2 = k * segment_size; // start of the new segment to merge
        if (k == segments - 1)
            end2 = i - 1; // if on last segment, use the rest of the array
        else
            end2 = (k + 1) * segment_size - 1; // end of the new segment to merge

        merge(beg, end, beg2, end2);
    }


   }
   // end timer
   if(clock_gettime(CLOCK_MONOTONIC, &endtimer) != 0){
   perror("Error ending timer!");
   exit (1);
   }

   free(in);
   free(out);

      
   // calculate the nanosecond between start and stop
   long long seconds = endtimer.tv_sec - starttimer.tv_sec;
   long long nanoseconds = endtimer.tv_nsec - starttimer.tv_nsec;
   nanoseconds = seconds * 1000000000 + nanoseconds;

   printf("Sorted in %lld nanoseconds\n", nanoseconds);

}




