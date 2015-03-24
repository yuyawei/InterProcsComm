#include "../lib/unpipc.h"

int main(int argc, char **argv)
{
	int semid, nsems, i;
	struct semid_ds seminfo;
	unsigned short *ptr;
	union semun arg;
	key_t key;
	int rc;

	if(argc != 2)
		err_quit("usage: SemGetVal <pathname>");
	
	key = ftok(argv[1], 0);
	if(key == -1)
	{
		err_sys("ftok error");
		return (key);
	}
	
	semid = semget(key, 0, 0);
	if(semid == -1)
	{
		err_sys("semget error");
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
	ptr = calloc(nsems, sizeof(unsigned short));
	if(NULL == ptr)
	{
		err_sys("calloc error");
		return (ptr);
	}

	arg.array = ptr;
	rc = semctl(semid, 0, GETALL, arg);
	if(rc == -1)
	{
		err_sys("semctl error");
		return (rc);
	}
	
	for(i = 0; i < nsems; i++)
		printf("semval[%d] = %d\n", i, ptr[i]);
	exit(0);
}
