#include "../lib/unpipc.h"

int main(int argc, char **argv)
{
	key_t key;
	int rc, semid;

	if(argc != 2)
		err_quit("usage: semrmid <pathname>");

	key = ftok(argv[1], 0);
	if(key == -1)
	{
		err_sys("ftok error");
		return (key);
	}

	semid = semget(key, 0, 0);
	if(semid == -1)
	{
		err_sys("error semget");
		return (semid);
	}

	rc = semctl(semid, 0, IPC_RMID);
	if(rc == -1)
	{
		err_sys("semctl error");	
		return (rc);
	}	
	exit(0);
}
