#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int WriteInFile (int fd, const char *buff, int len)
{	
	int bytes;
	bytes = write(fd,buff,len);
	return bytes;
}

void CopyFile (int fd, const char *file_in)
{
	return;
}

int check_file_exists(const char *file_name)
{
	int check_flag;

	printf("\n *******inside the function******\n");
	printf("File name %s\n",file_name);

	check_flag = access(file_name, F_OK );
// returns 0 or -1. if 0 then success and if -1 then error

	printf("Output file flag %d\n",check_flag);
	return check_flag;
}


int main(int argc, char *argv[])
{	
	int n;
	int file_counter;
	int check_file_flag;
	n = argc;

	// NOTE 1
	printf("%s \t %s \t %s \t", argv[0], argv[1], argv[2]);
	if((argc!=3)&&(argc!=4)) 
	printf("Usage: ./myfiles file_in_1 file_in_2 [file_out (default:myfile.out)] \n ");

	// check if file exists

	
	for(int i = 1;i<argc;i++)
	{	
		printf(" this is the file name %s\n", argv[i]);
		check_file_flag = check_file_exists(argv[i]);
		if(check_file_flag == -1)
		{
			file_counter++;
			printf("File with file name %s does not exist ",argv[i]);
		}
		if(check_file_flag == 0)
		{
			printf("File Exists");
		}
	}
	
	if((file_counter==0):
	{
	
		// your program starts here;
	}
	
	
	
	return 0;

}

