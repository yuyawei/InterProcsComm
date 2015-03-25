#include "../lib/unpipc.h"
#define MAX_NIDS 4096
#define MAX_VALUE 1024*1024
#define MAX_MEMBERS 4096
#define MAX_NOPS 4096
#define MAX_NPROC Sysconf(_SC_CHILD_MAX)

int main(int argc, char **argv)
{
	int i,j,semid,sid[MAX_NIDS],pipefd[2];
	int semmni,semvmx,semmsl,semmns,semopn,semaem,semume,semmnu;
	pid_t *child;
	union semun arg;
	struct sembuf ops[MAX_NOPS];

	for(i = 0; i <= MAX_NIDS; i++)
	{
		sid[i] = semget(IPC_PRIVATE, 1, SVSEM_MODE|IPC_CREAT);
		if(sid[i] == -1)
		{
			semmni = i;
			printf("%d identifiers open at once\n", semmni);
			break;
		}
	}

	for(j = 7; j<MAX_VALUE; j+=8)
	{
		arg.val = j;
		if(semctl(sid[0], 0, SETVAL, arg) == -1)
		{
			semvmx = j-8;
			printf("max sem value = %d\n", semvmx);
			break;
		}
	}

	for(j = 0; j < i; j++)
	{
		Semctl(sid[j], 0, IPC_RMID);
	}

	for(i = 1; i <= MAX_MEMBERS; i++)
	{
		semid = semget(IPC_PRIVATE, i, SVSEM_MODE | IPC_CREAT);
		if(semid == -1)
		{
			semmsl = i - 1;
			printf("max of %d members per set\n", semmsl);
			break;
		}
		Semctl(semid, 0, IPC_RMID);
	}

	semmns = 0;
	for(i = 0; i < semmni; i++)
	{
		sid[i] = semget(IPC_PRIVATE, semmsl, SVSEM_MODE|IPC_CREAT);
		if(sid[i] == -1)
		{
			for(j = semmsl - 1; j>0; j--)
			{
				sid[i] = semget(IPC_PRIVATE, j, SVSEM_MODE|IPC_CREAT);
				if(sid[i] != -1)
				{
					semmns += j;
					printf("max of %d semaphores\n", semmns);
					Semctl(sid[i], 0, IPC_RMID);
					goto DONE;
				}
			}
			err_quit("j reached 0, semms = %d", semmns);
		}
		semmns+=semmsl;
	}
	printf("max of %d semaphores\n", semmns);
DONE:
	for(j = 0; j < i; j++)
	{
		Semctl(sid[j], 0, IPC_RMID);
	}
	
	semid = Semget(IPC_PRIVATE, semmsl, SVSEM_MODE|IPC_CREAT);
	for(i = 1; i <= MAX_NOPS; i++)
	{
		ops[i-1].sem_num = i-1;
		ops[i-1].sem_op = 1;
		ops[i-1].sem_flg = 0;
		if(semop(semid, ops, i) == -1)
		{
			if(errno != E2BIG)
				err_sys("expected E2BIG for semop");
			semopn = i-1;
			printf("max of %d operatios per semop()\n", semopn);
			break;
		}
	}
	Semctl(semid, 0, IPC_RMID);
	
	semid = Semget(IPC_PRIVATE, 1, SVSEM_MODE|IPC_CREAT);
	arg.val = semvmx;
	Semctl(semid, 0, SETVAL, arg);
	for(i = semvmx-1; i>0; i--)
	{
		ops[0].sem_num = 0;
		ops[0].sem_op = -i;
		ops[0].sem_flg = SEM_UNDO;
		if(semop(semid, ops, 1) != -1)
		{
			semaem = i;
			printf("max value of adjust-on-exit = %d\n", semaem);
			break;
		}
	}
	Semctl(semid, 0, IPC_RMID);
	
	/*待续*/














	exit(0);
}

























