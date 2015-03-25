include ../Make.defines

PROGS = shmGet shmRmid shmWrite shmRead limits
	
all:	${PROGS}

shmGet:	shmGet.o
		${CC} ${CFLAGS} -o $@ shmGet.o ${LIBS}
shmRmid:	shmRmid.o
		${CC} ${CFLAGS} -o $@ shmRmid.o ${LIBS}
shmWrite:	shmWrite.o
		${CC} ${CFLAGS} -o $@ shmWrite.o ${LIBS}
shmRead:	shmRead.o
		${CC} ${CFLAGS} -o $@ shmRead.o ${LIBS}
limits:		limits.o
		${CC} ${CFLAGS} -o $@ limits.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
