#include	"../lib/unpipc.h"

int main(int argc, char **argv)
{
	int msqid;
	struct msqid_ds info;
	struct msgbuf buf;

	msqid = msgget(IPC_PRIVATE, SVMSG_MODE | IPC_CREAT);
	if(msqid == -1) 
		err_quit("msgget error\n");

	buf.mtype = 1;
	buf.mtext[0] = 1;


	if(msgsnd(msqid, &buf, 1, 0) == -1) 
		err_quit("msgsnd error\n");

	if(msgctl(msqid, IPC_STAT, &info) == 1)
		err_quit("msgctl error\n");

	printf("read-write: %03o, cbytes = %lu, qnum = %lu, qbytes = %lu\n",
			info.msg_perm.mode &0777, (ulong_t)info.msg_cbytes,
			(ulong_t)info.msg_qnum, (ulong_t)info.msg_qbytes);

	system("ipcs -q");
	if(msgctl(msqid, IPC_RMID, NULL) == -1)
		err_quit("msgctl error\n");

	exit(0);
}
