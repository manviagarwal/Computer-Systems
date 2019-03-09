#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
int main(){


printf("I am Process A with PID %d\n", getpid());

pid_t process_C;
process_C = fork();
int status;



if(process_C < 0) {
	printf("Error in creating process\n");
}
else if(process_C == 0) {
	printf("My name is Process C, my PID is %d, and my parents PID is %d\n", getpid(), getppid());
	sleep(10);
	exit(6);
}
else
{
	pid_t process_B = fork();
	if(process_B < 0) {
		printf("Error creating process B\n");
		}
	else if(process_B == 0)
	{
		printf("My name is process B, my PID is %d, and my parents PID is %d\n", getpid(), getppid());
		pid_t process_D = fork();
		
		if(process_D < 0){
			printf("Error creating process D\n");
		}
		else if(process_D == 0){
				printf("My name is Process D, my PID is %d, and my parents PID is %d\n", getpid(), getppid());
				sleep(10);
				exit(10);
		}
		else
		{
				sleep(10);
				waitpid(process_D, &status, 0);
				int return_value_D = WEXITSTATUS(status);
				printf("Process B knows process D with PID %d has finished with a return value of %d\n", process_D,return_value_D);
			}
			exit(4);
		}
		sleep(10);
		waitpid(process_B, &status, 0);
		int return_value_B = WEXITSTATUS(status);
		printf("Process A knows process B with PID %d has finished with a return value of %d\n", process_B, return_value_B);
		
		waitpid(process_C, &status, 0);
		int return_value_C = WEXITSTATUS(status);
		printf("Process A knows Process C with PID %d has finished with a return value of %d\n", process_C, return_value_C);
	}
	
	
}
