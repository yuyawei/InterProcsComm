#include "../lib/unpipc.h"

int main(int argc, char **argv)
{
	int id;
	int rc;
	key_t key;

	if(argc != 2)
		err_quit("usage:shmrmid <pathname>");
	
	key = ftok(argv[1], 0);
	if(key == -1)
	{
		err_sys("ftok error");
		return (key);
	}
	
	id = shmget(key, 0, SVSHM_MODE);
	if(id == -1)
	{
		err_sys("shmget error");
		return (id);
	}	
	
	rc = shmctl(id, IPC_RMID, NULL);
	if(rc == -1)
	{
		err_sys("shmctl error");
		return (rc);
	}

	exit(0);
}
