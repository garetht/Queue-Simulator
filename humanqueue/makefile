CFLAGS = -std=c99

humanqueue: humanqueue.o hqfunctions.o

humanqueue.o: humanqueue.h
hqfunctions.o: humanqueue.h

clean:
	rm -f humanqueue.o hqfunctions.o humanqueue

install: humanqueue
	cp humanqueue ~/bin
