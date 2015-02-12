include Makefile_generic_opt
OBJS   = smat.o comp.o verify.o ftimer.o verfunc.o
TAGGED_FILES = smat.h smat.c \
	comp.h comp.c \
	perf.h perf.c \
	verify.h verify.c \
	ftimer.c ftimer.h \
    verfunc.c verfunc.h 

all: driver_opt

driver_opt: perf.c $(OBJS) comp.d Makefile_generic_opt
	$(CC) $(CFLAGS) -o driver_opt perf.c $(OBJS) $(LIBS)

smat.o: smat.h smat.c
	$(CC) -c $(CFLAGS) -o smat.o smat.c

comp.d: comp.o
	$(OBJDUMP) comp.o > comp.d

comp.o: smat.h comp.h comp.c
	$(CC) -c $(CFLAGS) -o comp.o comp.c

perf.o: perf.h perf.c
	$(CC) -c $(CFLAGS) -o perf.o perf.c

verify.o: verify.h verify.c
	$(CC) -c $(CFLAGS) -o verify.o verify.c

ftimer.o: ftimer.c ftimer.h
	$(CC) -c $(CFLAGS) -o ftimer.o ftimer.c

verfunc.o: verfunc.c verfunc.h
	$(CC) -c $(CFLAGS) -o verfunc.o verfunc.c

TAGS:	$(TAGGED_FILES)
	etags -o TAGS $(TAGGED_FILES)

clean:
	-rm $(OBJS) comp.d

distclean: clean
	-rm main *~
