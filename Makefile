SRCDIR=.
CC=gcc 
CFLAGS =-g -I$(SRCDIR)/include
LDFLAGS = -L$(SRCDIR)/lib -lpthread
TARGETS=server client
all: $(TARGETS)

#server.c的编译
server:server.o
	$(CC)  $(CFLAGS) -o $@  $^ $(LDFLAGS)

server.o:server.c
	$(CC)  $(CFLAGS) -o $@ -c $< $(LDFLAGS)

#client的编译
client:client.o
	$(CC)  -g  -o $@ $^ 
client.o:client.c
	$(CC)  -g  -o $@ -c $<

clean:
	rm -f *.o
