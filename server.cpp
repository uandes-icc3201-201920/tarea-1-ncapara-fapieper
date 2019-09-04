#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"
#include <arpa/inet.h>
#include <random>

using namespace std;
//path del socket sin comando
char *socket_path = (char *)"/tmp/db.tuples.sock";
int recieved_int;

//contador entre 1000 y 100000
int count = 1000 + (rand()% static_cast<int>(10000-1000+1));
// Almacenamiento KV
KVStore db;

int main(int argc, char** argv) {	
cout << count << endl;
	struct sockaddr_un addr; //asociado a socket
	int fd,cl,rc; // asociado a socket
	char buf[256];//socketss
	
	int sflag = 0;
	int opt;
	
	// Procesar opciones de linea de comando
    while ((opt = getopt (argc, argv, "s:")) != -1) {
        switch (opt)
		{
			/* Procesar el flag s si el usuario lo ingresa */
			case 's':
				sflag = 1;
				break;
			default:
				return EXIT_FAILURE;
          }	    	
    }
    // Uso elemental del almacenamiento KV:
	
	// Creamos un arreglo de bytes a mano
	byte data[] = { 0x01, 0x01, 0x01, 0x01, 0x01 };

	// Luego un vector utilizando el arreglo de bytes
	vector<byte> vdata(data, data + sizeof(data));
	
	// Creamos el valor
	Value val = { 5, vdata };
	
	// Insertamos un par clave, valor directamente
	// en el mapa KV
	
	// Nota: Debiera diseñarse una solución más robusta con una interfaz
	// adecuada para acceder a la estructura.
	db.insert(std::pair<unsigned long, Value>(1000, val));
		
	// Imprimir lo que hemos agregado al mapa KV.
	cout << db[1000].size << " " << (int) db[1000].data[0] << endl;
	
	
	//sockets
	if ( sflag == 1 ){
	//hacer conexion de socket con pathname que nos entregan en la linea comando
	// si los argc > 2
		if (argc > 2) {socket_path = argv[2];}
		fd = socket(AF_UNIX,SOCK_STREAM,0);
		if ( fd  == -1)
		{
			perror("Socket error");
			exit(-1);
		}
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		if (*socket_path == '\0') 
		{
			*addr.sun_path = '\0';
			strncpy(addr.sun_path+1, socket_path+1, sizeof(addr.sun_path)-2);
		} 
		else 
		{
			strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
			unlink(socket_path);
		}

		if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
		{
			perror("bind error");
			exit(-1);
		}

		if (listen(fd, 5) == -1) 
		{
			perror("listen error");
			exit(-1);
		}
	}
	else{
	//hacer conexion de socket con pathname en tmp
		if (argc > 2) {socket_path = argv[2];}
		fd = socket(AF_UNIX,SOCK_STREAM,0);
		if ( fd == -1)
		{
			perror("Socket error");
			exit(-1);
		}
		memset(&addr, 0, sizeof(addr));
		addr.sun_family = AF_UNIX;
		if (*socket_path == '\0') 
		{
			*addr.sun_path = '\0';
			strncpy(addr.sun_path+1, socket_path+1, sizeof(addr.sun_path)-2);
		} 
		else 
		{
			strncpy(addr.sun_path, socket_path, sizeof(addr.sun_path)-1);
			unlink(socket_path);
		}

		if (bind(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1) 
		{
			perror("bind error");
			exit(-1);
		}

		if (listen(fd, 5) == -1) 
		{
			perror("listen error");
			exit(-1);
		}
		while (1)
		{
			if ( (cl = accept(fd, NULL, NULL)) == -1)
			{
			  perror("accept error");
			  continue;
			}

			while ( (rc=read(cl,&recieved_int,sizeof(recieved_int))) > 0)
			{
			  cout << ntohl(recieved_int) << endl;

			}
			if (rc == -1)
			{
			  perror("read");
			  exit(-1);
			}
			else if (rc == 0)
			{
			  printf("EOF\n");
			  close(cl);
			}
		}
	}
	
	return 0;
}
