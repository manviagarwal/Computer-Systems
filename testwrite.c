#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>

int WriteInFile (int fd, const char *buff, int len)
{	
	int bytes;
	bytes = write(fd,buff,len);
        return bytes; 	
}

void CopyFile (int fd, const char *file_in)
{
	char buff[100];
	size_t nbytes;
	ssize_t bytes_read;
	ssize_t bytes_written;
	nbytes = sizeof(buff);

	int ifd;
	
	ifd = open(file_in,O_RDONLY);
	bytes_read = read(ifd, buff, nbytes);

	bytes_written = WriteInFile(fd, buff, nbytes);
	
}


int main(int argc, char *argv[])
{	
	int ofd;
	ofd = open(argv[2],O_WRONLY);
	CopyFile(ofd,argv[1]);
	return 0;


}

