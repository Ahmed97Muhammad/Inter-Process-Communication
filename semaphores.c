#include <unistd.h>
#include <sys/types.h>  
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>

#define KEY 1000


sem_t sema;
int n=50000;


int main()
{

sem_init(&sema,0,1);


int shm_id;
shm_id = shmget(KEY, 50000*4 , IPC_CREAT | 0666);


 if (shm_id< 0) 
 {
  printf("shmget error\n"); 
 }

pid_t process=fork();


if( process == 0 ) //Child Process reads the data from shared memory and sorts the data using insertion sort
{

   if( sem_wait(&sema) == 0)
   {    

int *shm_ptr,i,j,var,temp,c;
int arr[50000];

shm_ptr=  shmat(shm_id, NULL, 0);


clock_t st = clock();

   for ( c = 0 ; c < n  ; c++ )
  	{
        arr[c]=*shm_ptr;    //reading the data from shared memory
        shm_ptr++;
   }


 
// insertion sort algorithm starts

for(i=1;i<n;i++)  
{
var=arr[i];
temp=i;
	
for(j=i-1;j>=0;j--)
{
			
  if(arr[j]>var)
  {
  arr[temp]=arr[j];
  arr[j]=var;  
  temp--;		
   }
 }
 
}

// insertion sort algorithm ends
                                   
 	for( c = 0 ; c < n  ; c++ )
          printf("%d \t",arr[c]);
        
printf("\n\nhere");
clock_t et = clock();
clock_t ctt = et - st;
double tis = ctt / (double) CLOCKS_PER_SEC;


//writing the sorted data in shared.txt file
FILE *fp;

fp = fopen("shared.txt","w");

for( c = 0 ; c < n ; c++)
   fprintf(fp,"%d ", arr[c]);


printf("\n\ntotal time is: %lf\n\n",tis);

}

sem_post(&sema);

}


else   //parent prrocess reads the data from file and writes it in to shared memory
{

   if( sem_wait(&sema) == 0)
  {
  	
int *shm_ptr,i,c,num;

shm_ptr =  shmat(shm_id, NULL, 0);

FILE *ff;
ff = fopen("numbers.txt","r"); //open the file in which numbers are stored

for ( c = 0 ; c < n  ; c++ )
  	{
                fscanf(ff, "%d", &num);
		*shm_ptr = num;      //adding the data in shared memory
		*shm_ptr++;
  	}

}
sem_post(&sema);
}


}
