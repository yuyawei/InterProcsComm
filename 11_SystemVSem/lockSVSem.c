#include "../lib/unpipc.h"

#define LOCK_PATH "/tmp/svsemlock"
#define MAX_TRIES 10
int semid, initflag;
struct sembuf postop, waitop;

void my_lock(int fd)
{
	int oflag, i;
	union semun arg;
	struct semid_ds seminfo;
	
	if(initflag == 0)
	{
		oflag = IPC_CREAT | IPC_EXCL | SVSEM_MODE;
		if( (semid = semget(Ftok(LOCK_PATH, 0), 1, oflag)) >= 0)
		{
			arg.val = 1;
			Semctl(semid, 0, SETVAL, arg);
		}
		else if(errno == EEXIST)
		{
			semid = Semget(Ftok(LOCK_PATH, 0), 1, SVSEM_MODE);
			arg.buf = &seminfo;
			for(i = 0; i < MAX_TRIES; i++)
			{
				Semctl(semid, 0, IPC_STAT, arg);
				if(arg.buf->sem_otime != 0)
					goto init;
				sleep(1);
			}		
			err_quit("semget OK, but semaphore not initialized");
		}
		else
		{
			err_sys("semget error");
		}

	init:
		initflag = 1;
		postop.sem_num = 0;
		postop.sem_op = 1;
		postop.sem_flg = SEM_UNDO;
		waitop.sem_num = 0;
		waitop.sem_op = -1;
		waitop.sem_flg = SEM_UNDO;
	}
	Semop(semid, &waitop, 1);
}

void my_unlock(int fd)
{
	Semop(semid, &postop, 1);
}


