#include "../lib/unpipc.h"
#define MAX_NIDS 4096



int main(int argc, char **argv)
{
	int i,j,shmid[MAX_NIDS];
	void *addr[MAX_NIDS];
	unsigned long size;
	int ret;

	for(i = 0; i<=MAX_NIDS; i++)
	{
		shmid[i] = shmget(IPC_PRIVATE, 1024, SVSHM_MODE|IPC_CREAT);
		if(shmid[i] == -1)
		{
			printf("%d identifiers open at once\n", i);
			break;
		}
	}

	for(j = 0; j < i; j++)
	{
		ret = shmctl(shmid[j], IPC_RMID, NULL);
		if(ret == -1)
		{
			err_sys("shmctl IPC_RMID error");
			return ret;
		}
	}

	for(i = 0; i <= MAX_NIDS; i++)
	{
		shmid[i] = Shmget(IPC_PRIVATE, 1024, SVSHM_MODE|IPC_CREAT);
#if 0
		if(shmid[i] == -1)
		{
			err_sys("shmget error");
			return (shmid[i]);
		}
#endif
		addr[i] = shmat(shmid[i], NULL, 0);
		if(addr[i] == (void *)-1)
		{
			printf("%d shared memory segments attached at once\n", i);
			ret = shmctl(shmid[i], IPC_RMID, NULL);
			if(ret == -1)
			{
				err_sys("shmctl IPC_RMID error");
				return ret;
			}
			break;
		}
	}	
	/*待续*/
	exit(0);
}





























