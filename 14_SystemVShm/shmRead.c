#include "../lib/unpipc.h"

int main(int argc, char **argv)
{
	int i, id;
	struct shmid_ds buff;
	unsigned char *ptr, c;
	key_t key;
	int ret;

	if(argc != 2)
		err_quit("usage shmWrite <pathname>");


	key = ftok(argv[1], 0);
	if(key == -1)
	{
		err_sys("ftok error\n");
		return key;
	}

	id = shmget(key, 0, SVSHM_MODE);
	if(id == -1)
	{
		err_sys("shmget error");
		return id;
	}

	ptr = shmat(id, NULL, 0);
	if(ptr == (void *)-1)
	{
		err_sys("shmat error");
		return (ptr);
	}
	
	ret = shmctl(id, IPC_STAT, &buff);
	if(ret == -1)
	{
		err_sys("shmctl error");
		return (ret);
	}

	for(i = 0; i < buff.shm_segsz; i++)
	{
		if((c = *ptr++) != (i%256))
			err_ret("ptr[%d] = %d", i, c);
	}

	exit(0);
}





























