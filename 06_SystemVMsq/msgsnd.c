#include	"../lib/unpipc.h"

int main(int argc, char **argv)
{
	int mqid;
	size_t len;
	long type;
	struct msgbuf *ptr;
	key_t key;

	if(argc!=4) err_quit("usage: msgsnd <pathname> <#bytes> <type>");
	len = atoi(argv[2]);
	type = atoi(argv[3]);
	key = ftok(argv[1], 0);
	if(key == -1)
		err_quit("ftok error\n");
	mqid = msgget(key, MSG_W);
	if(mqid == -1)
		err_quit("msgget error\n");

	ptr = calloc(sizeof(long) + len, sizeof(char));
	if(ptr == NULL)
		err_sys("calloc error\n");
	ptr->mtype = type;

	if(msgsnd(mqid, ptr, len, 0) == -1)
		err_quit("msgsnd error\n");

	exit(0);
}
