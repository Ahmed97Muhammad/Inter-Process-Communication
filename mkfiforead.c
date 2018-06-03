#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>
#include<time.h>

#define n 50000

int main()
{
   
   int pipe;
   int arr[50000];


clock_t st = clock();
   
   // open a named pipe
   pipe = open("/tmp/myfifo", O_RDONLY);

   // actually read out the data and close the pipe
   read(pipe,arr,sizeof(arr));


// insertion sort algorithm starts

for(int i=1;i<n;i++)  
{
int var=arr[i];
int temp=i;	
for(int j=i-1;j>=0;j--)
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
                                   
 	for (int c = 0 ; c < n  ; c++ )
        printf("%d \t",arr[c]);	

       
clock_t et = clock();
clock_t ctt = et - st;
double tis = ctt / (double) CLOCKS_PER_SEC;


//writing the sorted data in shared.txt file
FILE *fp;

fp = fopen("shared.txt","w");

for(int c = 0 ; c < n ; c++)
   fprintf(fp,"%d ", arr[c]);


printf("\n\ntotal time is: %lf\n\n",tis);

    // close the pipe
   close(pipe);
   return 0;
}
