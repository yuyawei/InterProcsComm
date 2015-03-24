include ../Make.defines

PROGS = semcreate semrmid semsetvalues SemGetVal SemOps
	
all:	${PROGS}

semcreate:	semcreate.o
		${CC} ${CFLAGS} -o $@ semcreate.o ${LIBS}
semrmid:	semrmid.o
		${CC} ${CFLAGS} -o $@ semrmid.o ${LIBS}
semsetvalues:	semsetvalues.o
		${CC} ${CFLAGS} -o $@ semsetvalues.o ${LIBS}
SemGetVal:	SemGetVal.o
		${CC} ${CFLAGS} -o $@ SemGetVal.o ${LIBS}
SemOps:		SemOps.o
		${CC} ${CFLAGS} -o $@ SemOps.o ${LIBS}

clean:
		rm -f ${PROGS} ${CLEANFILES}
