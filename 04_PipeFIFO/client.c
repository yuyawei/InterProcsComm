#include "../lib/unpipc.h"


void client(int readfd, int writefd)
{
	size_t len;
	ssize_t n;
	char buf[MAXLINE];
	char *ptr;

	ptr = fgets(buf, MAXLINE, stdin);
	if(ptr == NULL && ferror(stdin))
	{
		err_sys("fgets error");
	}

	len = strlen(buf);
	if(buf[len-1] == '\n')
		len--;

	if(write(writefd, buf, len) != len)
	{
		err_sys("write error");
	}

	n = read(readfd, buf, MAXLINE);
	while(n > 0)
	{
		if(write(STDOUT_FILENO, buf, n) != n)
			err_sys("write STDOUT_FILENO error");
		n = read(readfd, buf, MAXLINE);
	}
	
	exit(0);
}
