include ../Make.defines

PROGS =	ctl msgcreate msgsnd msgrcv msgrmid
	
all:	${PROGS}

ctl:	ctl.o
		${CC} ${CFLAGS} -o $@ ctl.o ${LIBS}
msgcreate:	msgcreate.o
		${CC} ${CFLAGS} -o $@ msgcreate.o ${LIBS}
msgsnd:	msgsnd.o
		${CC} ${CFLAGS} -o $@ msgsnd.o ${LIBS}
msgrcv:	msgrcv.o
		${CC} ${CFLAGS} -o $@ msgrcv.o ${LIBS}
msgrmid:	msgrmid.o
		${CC} ${CFLAGS} -o $@ msgrmid.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
