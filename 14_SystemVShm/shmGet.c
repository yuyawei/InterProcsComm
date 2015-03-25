#include "../lib/unpipc.h"

int main(int argc, char **argv)
{
	int c,id,oflag;
	char *ptr;
	size_t length;
	key_t key;

	oflag = SVSHM_MODE|IPC_CREAT;
	while((c = Getopt(argc, argv,"e")) != -1)
	{
		switch(c){
		case 'e':
			oflag |= IPC_EXCL;
			break;
		}
	}
	if(optind != argc -2)
		err_quit("usage: shmGet [-e] <pathname> <length>");
	length = atoi(argv[optind + 1]);
	
	key = ftok(argv[optind],0);
	if(key == -1)
	{
		err_sys("ftok error\n");
		return (key);
	}

	id = shmget(key, length, oflag);
	ptr = shmat(id, NULL, 0);
	if(ptr == (void *)-1)
	{
		err_sys("shmat error\n");
		return (ptr);
	}
	
	exit(0);
}
