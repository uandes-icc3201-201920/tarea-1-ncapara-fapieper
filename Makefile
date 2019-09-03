# TODO: Crear el Makefile...

CC=g++
ASCIIDOC=/usr/bin/asciidoc
DOC = Unix_domain_sockets.html
PROGS = client server

#all: $(PROGS) $(DOC)
server: serv.o
	$(CC) -o server serv.o
client: cli.o
	$(CC) -o client cli.o
serv.o: server.cpp util.h
	$(CC) -o serv.o -c server.cpp
cli.o: client.cpp
	$(CC) -o cli.o -c client.cpp

#Unix_domain_sockets.html: Unix_domain_sockets.txt
#	if [ -x $(ASCIIDOC) ]; then $(ASCIIDOC) $<; fi

.PHONY: clean

clean:
	rm -rf *.o
	rm -f client
	rm -f server
	rm -f *.o socket $(PROGS)
