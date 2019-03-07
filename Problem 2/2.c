#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	FILE *fp;
	FILE *fptr;
	char ch;
	int num_elements = 0;
	

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
	// printf("\n%d \t is the number of elements\n",num_elements);

// GET THE ELEMENTS INTO AN ARRAY

	int arr[num_elements+1];
	char buff[num_elements+1];
	int i=0;

	fp = fopen(argv[1],"r");
	while( fscanf(fp,"%s",buff) ==1)
	{
		arr[i] = atoi(buff);
		i++;
	}
	

// FIND THE MIN MAX AND SUM
	

	int min = arr[0];
	int max = arr[0];
	int sum = 0;
	int n = sizeof(arr);

	for(int i=0;i<n/sizeof(int)-1;i++)
	{
	printf("%d\t",arr[i]);
	if(min>arr[i])
		min = arr[i];
	if(max<arr[i])
		max = arr[i];
	sum = sum + arr[i];
	
	}
	
	printf("\nMinimum is %d\t",min);
	printf("\nMaximum is %d\t",max);
	printf("\n Sum is %d\t",sum);
 
return 0;
 	
}

