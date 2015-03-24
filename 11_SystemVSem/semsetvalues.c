#include "../lib/unpipc.h"

int main(int argc, char **argv)
{
	int semid, nsems, i;
	int rc;
	struct semid_ds seminfo;
	unsigned short *ptr;
	union semun arg;
	key_t key;

	if(argc < 2)
		err_quit("usage: semsetvalues <pathname> [ values ... ]");

	key = ftok(argv[1], 0);
	if(key == -1)
	{
		err_sys("ftok error");
		return (key);
	}

	semid = semget(key, 0, 0);
	if(semid == -1)
	{
		err_sys("semid error");
		return (semid);
	}
	
	arg.buf = &seminfo;
	rc = semctl(semid, 0, IPC_STAT, arg);
	if(rc == -1)
	{
		err_sys("semctl error");
		return (rc);
	}
	
	nsems = arg.buf->sem_nsems;

	if(argc != nsems + 2)
		err_quit("%d sem in set, %d values specified", nsems, argc-2);

	ptr = Calloc(nsems, sizeof(unsigned short));
	arg.array = ptr;
	for(i = 0; i < nsems; i++)
	{
		ptr[i] = atoi(argv[i+2]);
	}
	
	rc = semctl(semid, 0, SETALL, arg);
	if(rc == -1)
	{
		err_sys("semctl SETALL error");
		return (rc);
	}

	exit(0);
}







