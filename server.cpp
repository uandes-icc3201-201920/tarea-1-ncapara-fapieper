#include <iostream>
#include <memory>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"
#include <arpa/inet.h>
#include <random>
#include <thread>
#include <iterator>

using namespace std;
//path del socket sin comando
char *socket_path = (char *)"/tmp/db.tuples.sock";
int recieved_int;

//contador entre 1000 y 100000
int count = 1000 + (rand()% static_cast<int>(10000-1000+1));
// Almacenamiento KV
//KVStore db;
map<int,int> db;

void coneccion(int cl){ //en esta funcion es que corre el thread
	int key,values;
	int rc;
	int temporal_K, temporal_V;
	int nn = htonl(1); //not found value
	map<int,int>::iterator itr;
	while (1) {
	    while ( (rc=read(cl,&recieved_int,sizeof(recieved_int))) > 0) {
			//cout << ntohl(recieved_int) << endl;
			if ( ntohl(recieved_int) == 1){ cout << "entre aqui del input 1" << endl;}
			else if(ntohl(recieved_int) == 2)
			{
				if( (rc=read(cl,&values,sizeof(values))) > 0 )
				{
					db.insert(pair<int,int>(count,ntohl(values)));
					count++;
					cout << "bd actualizada" << endl;
				}
				
				
			}
			else if(ntohl(recieved_int) == 3)
			{
				cout << "entre aqui del get" << endl;
				if( (rc=read(cl,&key,sizeof(key))) > 0 )
				{
					for ( itr = db.begin(); itr != db.end(); ++itr)
					{
						if( itr->first == ntohl(key) )
						{
							temporal_V = htonl(itr->second);
							write(cl,&temporal_V,sizeof(temporal_V));
						}
					}
					write(cl,&nn,sizeof(nn));
				}
			}
			else if(ntohl(recieved_int) == 4){cout << "entre aqui del peek" << endl;}
			else if(ntohl(recieved_int) == 5){cout << "entre aqui del update" << endl;}
			else if(ntohl(recieved_int) == 6){cout << "entre aqui del delete" << endl;}
			else if(ntohl(recieved_int) == 7)
			{
				cout << "entre aqui del list" << endl;
				cout << "\tKey\tValue\n";
				for ( itr = db.begin(); itr != db.end(); ++itr)
				{
					cout << '\t' << itr->first << '\t' << itr->second << '\n';
				}
			}
			else if(ntohl(recieved_int) == 8) { close(cl); break;}
	    }
	    if (rc == -1) {
	      perror("read");
	      exit(-1);
	    }
	    else if (rc == 0) {
	      close(cl);
	      break;
	    }
	}
	pthread_exit(NULL);
}

int main(int argc, char** argv) {	
	cout << count << endl;
	struct sockaddr_un addr; //asociado a socket
	int fd,cl,rc; // asociado a socket
	char buf[256];//socketss
	vector<unique_ptr<thread>> threads;
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
/*    // Uso elemental del almacenamiento KV:
	
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
*/	
	
	//sockets
	if ( sflag == 1 ){
		cout << "No funciona con socket ingresado por cmd" << endl;
	//hacer conexion de socket con pathname que nos entregan en la linea comando
	// si los argc > 2
		/*if (argc > 2) {socket_path = argv[2];}
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
		}*/
	}
	else{
	//hacer conexion de socket con pathname en tmp
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

		if (listen(fd, 3) == -1) 
		{
			perror("listen error");
			exit(-1);
		}
		for(;;)
		{
			if ( (cl = accept(fd, NULL, NULL)) == -1)
			{
	    			perror("accept error");
	     			continue;
	   		}
			threads.emplace_back(new thread(coneccion,cl));//aqui asigno el thread a la funcion
		}
	}
	
	return 0;
}
