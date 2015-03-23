#include "../lib/unpipc.h"

int main(int argc, char **argv)
{
	int i, msqid;
	for(i = 0; i < 10; i++)
	{
		msqid = msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
		if(msqid == -1){
			printf("msget error\n");
			exit(-1);
		}
		printf("msqid = %d\n", msqid);

		if(msgctl(msqid, IPC_RMID, NULL) == -1) {
			printf("msgctl error\n");
			exit(-1);
		}
	}
	exit(0);
}
