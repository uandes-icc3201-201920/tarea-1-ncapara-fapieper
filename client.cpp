#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"

using namespace std;
//path del socket sin comando
char *socket_path = "/tmp/db.tuples.sock";

int main(int argc, char** argv) {
	
	string cmd = "";//codigo original
	
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
    if ( sflag == 1 ){
	//hacer conexion de socket con pathname que nos entregan en la linea comando
	}
	else{
	//hacer conexion de socket con pathname que queramos
	}
	
	//codigo original
	while (cmd != "quit") {
		cout << ">";
		cin >> cmd;
	}// original

	return 0;	
}
