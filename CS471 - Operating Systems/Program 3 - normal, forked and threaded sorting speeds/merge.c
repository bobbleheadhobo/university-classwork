/*  Shaun Cooper
    September 2, 2000

    simple implementation of mergesort.

    Input:  from STDIN, integers in unsorted fashion.  Data
       ends when a 0 (zero) is read.

    Output: the data in sorted order

    Notes:  Since mergesort actually relies upon external storage to
       store the merge of two segments, we use an additional array to
       store the merge called "out[]" and then place the results
       back into "in[]" for subsequent merges.


*/

#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>





/* value to size the arrays */

#define MAXNUM 10000

/* define the two arrays */

/* a pointer to the shared memory segment */
int *in;

/* the internal array for merging */
int out[MAXNUM];

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

   for(i=0;i<=NUM;i++)
     printf("%d\n",in[i]);

  printf("\n");

}

int main()
{
  int i,j;
  int done;
  int beg,end;
  int level;
  int share_key_in;
  int share_key_out;
  struct shmid_ds item;
  pid_t children[8];
  int status[8];
  int segments = 8;



   /* define shared memory */

   if ( (share_key_in=shmget(IPC_PRIVATE,MAXNUM * 4 , IPC_CREAT|0666)) < 0)
      perror("Cannot get shared memory\n");


   printf("How big do you want the array: ");
   scanf("%d", &i);

   // Dynamically allocate memory for the array
   in = (int *)malloc(i * sizeof(int));
   if (in == NULL) {
       perror("Memory allocation failed!\n");
       return 1;
   }

   /* attach shared memory segment */
   if ( (in=shmat(share_key_in,(void *) 0, SHM_RND)) == (void *) -1)
     perror("cannot attach to shared memory\n");

   // make random number actually random
   srand(time(NULL));

    // Fill the array with random integers between 0 and 99 inclusive
    for (int x = 0; x < i; x++) {
        in[x] = rand() % 100;
    }

   printf("Randomly generator numbers:\n");
   printar(i);

  /* too few items, no need to fork */
  if ( i <= 8 )
   {
     sort(0,i);
     printar(i);
     shmctl(share_key_in,IPC_RMID,&item);
   }

  /* we need to fork processes and then do the work.  
     STUDENTS: This is where you will make changes to support
     8 processes */
  else {
      int segment_size = i / segments;

      for (int k = 0; k < segments; k++) {
         if ((children[k] = fork()) == 0) {
               // This is a child process
               beg = k * segment_size; //starts at 1/8, 2/8, 3/8...etc

               //if at last index set end to size of array
               if(k == segments - 1)
                  end = i;
               else
                  end = beg + segment_size;

               sort(beg, end - 1); // -1 because end is exclusive

               // Printing the sorted segment for this child test
               printf("Child %d sorted segment:\n", k);
               for (int x = beg; x < end; x++) {
                     printf("%d   | %d\n", in[x], k);
               }
               printf("\n");
               exit(0); //end the children
            }
        }


      /* parent process */
      for (int k = 0; k < 8; k++) {
         waitpid(children[k], &status[k], 0);
      }

      //merge the sorted array
      int end2, beg2;
      for (int k = 1; k < segments; k++) {
         beg = 0; // start of the merged result always begins from 0
         end = k * segment_size - 1; // end of the merged result, which grows with each merge

         beg2 = k * segment_size; // start of the next segment to merge
         if (k == segments - 1)
            end2 = i - 1;
         else
            end2 = (k + 1) * segment_size - 1; // end of the next segment to merge

         merge(beg, end, beg2, end2);
      }
      

      printar(i);
      shmctl(share_key_in,IPC_RMID,&item); // delete shared memory
	  }
	}




