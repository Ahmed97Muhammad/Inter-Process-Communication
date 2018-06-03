#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include<sys/shm.h>
#include<signal.h>
#include<sys/ipc.h>
#define KEY 9999

void func(int signalNo)
{
printf("Terminating%d \n",signalNo);
}

int main()
{

int num,i,n=20000;


FILE *ff,*fp,*fw;
ff = fopen("numbers.txt","r"); //open the file in which numbers are stored

fp = fopen("shared.txt","w"); // open the shared file and clear all data
fclose(fp); // close shared file


fw = fopen("shared.txt","w");

for(i=0;i<n;i++) // this loop writes the number one by one into shared file
{
fscanf(ff, "%d", &num);
fprintf(fw,"%d ",num);


}

fclose(fw);
fclose(ff);

printf("writing complete, waiting for second process....\n");

signal(SIGUSR1,func);//waiting for the signal of second process

while(1)
{  }

printf("Terminating\n");

}
