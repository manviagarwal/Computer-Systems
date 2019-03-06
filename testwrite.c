#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

void WriteInFile (int fd, const char *buff, int len)
{	
	int bytes;
	write(fd,buff,len);	
}

void CopyFile (int fd, const char *file_in)
{
	char buff[100];
	char opbuff[100];
	size_t nbytes;
	ssize_t bytes_read;
	ssize_t bytes_read_from_op_file;
	ssize_t bytes_written;
	nbytes = sizeof(buff);

	int ifd;
	
	ifd = open(file_in,O_RDONLY);
	bytes_read = read(ifd, buff, nbytes);

// CHECK IF THE OUTPUT FILE IS EMPTY OR NOT

	bytes_read_from_op_file = read(fd,opbuff, sizeof(opbuff));
	if(bytes_read_from_op_file == 0)
	{
		WriteInFile(fd, buff, bytes_read);
	}
	close(ifd);
	return;
	
}

int check_file_exists(const char *file_name)
{
	int check_flag;

	check_flag = access(file_name, F_OK );

// returns 0 or -1. if 0 then success and if -1 then error

	return check_flag;
}


int main(int argc, char *argv[])
{	
	int ofd;
	int ofd2;

	int n;
	int file_counter = 0;
	int check_file_flag;
	n = argc;
	char *OUTPUT_FILENAME;

// NOTE 1

	if((argc!=3)&&(argc!=4)) 
	printf("Usage: ./myfiles file_in_1 file_in_2 [file_out (default:myfile.out)] \n ");

// CHECK IF FILE EXISTS

	
	for(int i = 1;i<argc-1;i++)
	{	

		check_file_flag = check_file_exists(argv[i]);
		if(check_file_flag == -1)
		{
			file_counter++;
			printf("%s : No such file or directory\n", argv[i]);
		}
		if(check_file_flag == 0)
		{
			// FILE EXISTS -- DON'T DO ANYTHING
		}
	}
	
// IF NO OUTPUT FILE WAS GIVEN
	if(argc == 3)
		OUTPUT_FILENAME = "myfile.out" ;
	if(argc == 4)
		OUTPUT_FILENAME = argv[3] ;

	if((file_counter==0))
	{

		//ofd = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
		//ofd = open(argv[3], O_RDWR | O_APPEND | O_TRUNC | O_CREAT, 0664);

		ofd = open(OUTPUT_FILENAME, O_RDWR | O_APPEND | O_TRUNC | O_CREAT, 0664);

		if(ofd == 0)
		{
			printf("output file is successfully created or opened");
		}
		CopyFile(ofd,argv[1]);

		// ofd2  = open(argv[3],O_RDWR | O_APPEND | O_TRUNC, 0664);
		CopyFile(ofd,argv[2]);
		close(ofd);
	}
	return 0;


}

