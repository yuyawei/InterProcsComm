#include "../lib/unpipc.h"

void client(int,int), server(int, int);

int main(int argc, char **argv)
{
	int pipe1[2], pipe2[2];
	pid_t pid, ret;

	if(pipe(pipe1) < 0)
		err_sys("pipe pipe1 error");
	if(pipe(pipe2) < 0)
		err_sys("pipe pipe2 error");

	if((pid = fork()) == -1)
	{
		err_sys("fork error");
		return pid;
	}
	if(pid == 0)		   			/*子进程*/
	{
		if(close(pipe1[1]) == -1)
			err_sys("close pipe1[1] error");
		if(close(pipe2[0]) == -1)
			err_sys("close pipe2[0] error");	
		
		server(pipe1[0], pipe2[1]);
		exit(0);
	}
	else				  	       /*父进程*/
	{
		if(close(pipe1[0]) == -1)
			err_sys("close pip1[0] error");
		if(close(pipe2[1]) == -1)
			err_sys("close pip2[1] error");

		client(pipe2[0], pipe1[1]);
		if((ret = waitpid(pid, NULL, 0)) == -1)
		{
			err_sys("waitpid error");
			return (ret);
		}

		exit(0);
	}
	exit(0);
}
