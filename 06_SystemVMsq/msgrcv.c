#include	"../lib/unpipc.h"
#define MAXMSG (8192 + sizeof(long))

int main(int argc, char **argv)
{
	int c, flag, mqid;
	long type;
	ssize_t n;
	struct msgbuf *buff;

	type = flag = 0;
	while( (c = Getopt(argc, argv, "nt:")) != -1)
	{
		switch(c){
		case 'n':
			flag |= IPC_NOWAIT;
			break;
		case 't':
			type = atol(optarg);
			break;
		}
	}
	if(optind != argc -1)
		err_quit("usage: msgrcv [ -n ][ -t type ] <pathname>");

	mqid = msgget(Ftok(argv[optind], 0), MSG_R);
	if(mqid == -1){
		err_sys("msgget error\n");
		return (mqid);	
	}

	buff = (struct msgbuf *)malloc(MAXMSG);
	if(buff == NULL){
		err_sys("malloc error\n");
		return (buff);
	}

	n = msgrcv(mqid, buff, MAXMSG, type, flag);
	if(n == -1){
		err_sys("msgrcv error\n");
		return (n);
	}
	printf("read %d bytes, type = %ld\n", n, buff->mtype);

	exit(0);
}
