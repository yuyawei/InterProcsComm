#include "../lib/unpipc.h"

int main(int argc, char **argv)
{
	int c, oflag, semid, nsems;
	key_t key;

	oflag = SVSEM_MODE | IPC_CREAT;
	while((c = Getopt(argc, argv, "e")) != -1){
		switch(c){
		case 'e':
			oflag |= IPC_EXCL;
			break;
		}
	}
	if(optind != argc - 2)
		err_quit("usage: semcreate [ -e ] <pathname><nsems>");
	nsems = atoi(argv[optind + 1]);
	
	key = ftok(argv[optind], 0);
	if(key == -1)
	{
		err_sys("ftok error");
		return (key);
	}
	semid = semget(key, nsems, oflag);
	if(semid == -1)
	{
		err_sys("semget error");
		return (semid);
	}
	exit(0);
}
