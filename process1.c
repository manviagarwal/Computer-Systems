#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int min=INT_MAX;
int max=INT_MIN;
int sum=0;


void process(int start, int min,int max,int sum, int chunksize) 
{
	// fork here
	// create a process
        printf("\nhi,I am process %d and my parent is %d ",getpid(),getppid());

        int end= start + chunksize;
	
	pid_t pid;

	pid = fork();
	
	int num_processes = 0;

	if(pid == -1)
	{
		printf("Error in forking\n");
		exit(1);
	}

	if(pid == 0)  // child process
	{
	process(end,min,max,sum,chunksize);
 	}
	
	else
	{
	  for(int i=start;i<end;i++)
	  {
           if (elem[i]<min) min=elem[i];
           if (elem[i]>max) max=elem[i];
           sum=sum+elem[i];
	   }
	waitpid(pid);
	}
}

int main(int argc, char *argv[])
{

	FILE *fp;
	FILE *fptr;
	char ch;
	int num_elements = 0;
        int *elem;

	
	

// GET THE NUMBER OF ELEMENTS FROM FILE

	fptr = fopen(argv[1],"r");
	if(fptr == NULL)
		printf("File cannot be opened\n");

	else
	{
		ch = fgetc(fptr);
		while(ch!= EOF )
		{
			if(ch == '\n')
			{
				num_elements++;
				//printf("%c is the character\n",ch);
			}
			ch = fgetc(fptr);
		}	
	}

	fclose(fptr);
	

// SHARED MEMORY 

	
	/* create a shared memory segment for the array */	

	// ftok to generate unique key 
	key_t key = ftok("shmfile",65); 

	// shmget returns an identifier in shmid 
	int shmid = shmget(key,num_elements*sizeof(int),0666|IPC_CREAT); 
	
	if (shmid == -1)
	{
		perror("shmget : ");
		exit(1);
	}
  
	// shmat to attach to shared memory 
	elem = (int*) shmat(shmid,(void*)0,0);
	
	if(!elem)
	{
		perror("shmat: ");
		exit(1);
	} 

// GET THE ELEMENTS INTO AN ARRAY

	int arr[num_elements+1];
	char buff[num_elements+1];
	int i=0;

	fp = fopen(argv[1],"r");
	while( fscanf(fp,"%s",buff) ==1)
	{
		arr[i] = atoi(buff);
		elem[~i] = arr[i];
		i++;
	}

	int n = sizeof(arr);

	for(int i = 0;i<n/sizeof(int)-1;i++)
	{
		printf("elem array: %d\t",elem[i]);
	}



       process(0,min,max,sum,3);
       printf("\n Max = %d ",max);
       printf("\n Max = %d ",min);
       printf("\n Max = %d ",sum);
	
	
return 0;
 	
}
