#include <stdio.h>
#include <unistd.h>
#include<time.h>
#include <sys/types.h>

int main(void)
{

int fd[2], nbytes;
pid_t childpid;
int arr[50000],sort[50000],i,var,temp,j,n=30000;
clock_t st;
FILE *ff;
        
pipe(fd); // declares pipe structure
        
  if((childpid = fork()) == -1)
  {
   perror("fork");
  }
 
  if(childpid == 0)
  {

   // Child process closes up input side of pipe 
   close(fd[0]);

ff = fopen("numbers.txt","r");  //open the file in which numbers are stored

for(i=0;i<n;i++){
fscanf(ff, "%d", &arr[i]);
}

fclose(ff);  // close the file

              
/* Send "array" through the output side of pipe */
write(fd[1], &arr, sizeof(arr));
                
}
        

else
{

 st = clock();   //time starts

printf("reading and sorting the data....\n");      
          
/* Parent process closes up output side of pipe */
close(fd[1]);

                
/* Read in a array from the pipe */
nbytes = read(fd[0], &sort, sizeof(sort));


// insertion sort algorithm starts    

for(i=1;i<n;i++)
{
var=sort[i];
temp=i;
	
for(j=i-1;j>=0;j--)
{

if(sort[j]>var){
sort[temp]=sort[j];
sort[j]=var;  
temp--;		
}

	
}}


// insertion sort algorithm ends

for(i=0;i<n;i++)   // print final sorted data
printf("%d \t",sort[i]);

printf("sorting complete....\n");
                
clock_t et = clock();
clock_t ctt = et - st;
double tis = ctt / (double) CLOCKS_PER_SEC;


printf("\n\ntotal time is: %lf",tis);
                
                
}
        
return(0);

}

