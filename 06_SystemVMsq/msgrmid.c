#include	"../lib/unpipc.h"

int main(int argc, char **argv)
{
	int mqid;
	key_t key;
	int rc;

	if(argc != 2){
		err_quit("usage: msgrmid <pathname>");
	}
	key = ftok(argv[1], 0);
	if(key == -1){
		err_sys("ftok error for file %s\n", argv[1]);
		return (key);
	}

	mqid = msgget(key, 0);
	if(mqid == -1){
		err_sys("msgget error\n");
		return (mqid);
	}

	rc = msgctl(mqid, IPC_RMID, NULL);
	if(rc == -1){
		err_sys("msgctl error\n");
		return rc;
	}
	
	exit(0);
}
