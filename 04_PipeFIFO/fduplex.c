#include "../lib/unpipc.h"

int main(int argc, char **argv)
{
	int fd[2], n;
	char c;
	pid_t childpid;

	if(pipe(fd) < 0)
		err_sys("pipe error");




	/*待续*/

}
