include ../Make.defines

PROGS = ftok slot
all:	$(PROGS)

ftok: ftok.o 
	$(CC) $(CFLAGS) -o $@ ftok.o $(LIBS)
ftok: slot.o
	$(CC) $(CFLAGS) -o $@ slot.o $(LIBS)

clean: 
	rm -f $(PROGS) *.o $(CLEANFIFLES)

