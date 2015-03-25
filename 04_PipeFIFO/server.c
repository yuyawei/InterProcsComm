#include "../lib/unpipc.h"


void server(int readfd, int writefd)
{
	int fd;
	ssize_t n;
	char buff[MAXLINE+1];
	
	if( (n = Read(readfd, buff, MAXLINE)) == 0)
		err_quit("end-of-line while reading pathname");
	
	buff[n] = '\0';
	if((fd = open(buff, O_RDONLY)) < 0)
	{
		snprintf(buff+n, sizeof(buff)-n, ":can't open, %s\n", strerror(errno));
		n = strlen(buff);
		if(write(writefd, buff, n) != n)
		{
			err_sys("write error");
		}
	}
	else
	{
		while((n = Read(fd, buff, MAXLINE)) > 0)
		{
			Write(writefd, buff, n);
		}
		Close(fd);
	}
}
