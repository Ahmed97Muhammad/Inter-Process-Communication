#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<sys/shm.h>
#include<signal.h>
#include<sys/ipc.h>
#define KEY 9999


int main()
{

printf("reading and sorting the data....\n");

int arr[50000],n=10000,i,j,var,temp;
clock_t st;

FILE *fp,*fr;
fp = fopen("shared.txt","r"); // opens the shared file


st = clock();   //time starts

for(i=0;i<n;i++)  // loop for reading the file and storing data
{
fscanf(fp, "%d", &arr[i]);

}
fclose(fp); // close the shared file



// insertion sort algorithm starts

for(i=1;i<n;i++)  
{
var=arr[i];
temp=i;
	
for(j=i-1;j>=0;j--)
{
			
if(arr[j]>var){
arr[temp]=arr[j];
arr[j]=var;  
temp--;		
}
}}

// insertion sort algorithm ends



fr = fopen("shared.txt","w");  // open the shared file again for writing sorted data

for(i=0;i<n;i++) // loop for writing sorted data into the shared file
{

fprintf(fr,"%d ",arr[i]);
printf("%d \t",arr[i]);

}

fclose(fr); // close the shared file

printf("sorting complete....\n");

clock_t et = clock();
clock_t ctt = et - st;
double tis = ctt / (double) CLOCKS_PER_SEC;


printf("\n\ntotal time is: %lf",tis);
                

system("pkill filewrite");  //sends the signal pkill to filewrite.c to terminate
}
