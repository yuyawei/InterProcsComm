#include "../lib/unpipc.h"

int main(int argc, char **argv)
{
	int c, i, flag, semid, nops;
	struct sembuf *ptr;
	flag = 0;
	key_t key;
	int rc;

	while((c = Getopt(argc, argv, "nu")) != -1)
	{
		switch(c){
		case 'n':
			flag |= IPC_NOWAIT;
			break;

		case 'u':
			flag |= SEM_UNDO;
			break;
		}
	}
	if(argc - optind < 2)
		err_quit("usage: semops [-n][-u] <pathname> operations ...");
	
	key = ftok(argv[optind], 0);
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
	optind++;
	nops = argc - optind;
	
	ptr = Calloc(nops, sizeof(struct sembuf));
	for(i = 0; i < nops; i++)
	{
		ptr[i].sem_num = i;
		ptr[i].sem_op = atoi(argv[optind+i]);
		ptr[i].sem_flg = flag;
	}
	
	rc = semop(semid, ptr, nops);
	if(rc == -1)
	{
		err_sys("semop error");
		return (rc);
	}
	exit(0);
}
