#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"

using namespace std;
//path del socket sin comando
char *socket_path = (char*)"/tmp/db.tuples.sock";

int main(int argc, char** argv) {
	
	string cmd = "";//codigo original
	int insert_op = 0;
	int k,v;//int for key and values.
	//socket
	struct sockaddr_un addr;
	char buf[256];
	int fd,rc;
	
	/*else  aqui esta para ver mas facil las partes del socket
	{
	//hacer conexion de socket con pathname tmp
		fd = socket(AF_UNIX, SOCK_STREAM, 0);
		if ( fd == -1)
		{
   			perror("socket error");
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
		}
		if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
		{
			perror("connect error");
			exit(-1);
		}
		if( (rc=read(STDIN_FILENO, buf, sizeof(buf))) > 0)
		{
			if (write(fd, buf, rc) != rc)
			{
			  if (rc > 0) {fprintf(stderr,"partial write");}
			  else
			  {
				perror("write error");
				exit(-1);
			  }
			}
		}
	}*/
	
	//codigo original
	while (cmd != "quit")
	{
		cout << "Ingrese comando" <<endl <<  ">";
		cin >> cmd;
		if(cmd == "connect")
		{
			socket_path = new char[256];
			cout<<cmd<<endl;
			cout << "Socket path name: ";
			cin >> socket_path;
			fd = socket(AF_UNIX, SOCK_STREAM, 0);
			if ( fd == -1)
			{
	   			perror("socket error");
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
			}
			if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
			{
				perror("connect error");
				exit(-1);
			}
			cout<<"Connected"<<endl;
		}
		else if(cmd == "disconnect")
		{
			if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) != -1)
			{
				close(fd);
			}		
		}
		else if(cmd == "quit"){
			if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) != -1)
			{
				close(fd);
			}
			exit(-1);
		}
		else if(cmd == "insert")
		{
			cout << "Press 1 for key,value" << endl;
			cout << "Press 2 for value" << endl << ">";
			cin >> insert_op;
			if(insert_op == 1){
				cout << "Desired key" << endl << ">";
				cin >> k;
				cout << "Desired value" << endl << ">";
				cin >> v;
				
			}
			else if(insert_op == 2)
			{
				cout << "Desired value" << endl << ">";
				cin >> v;
				insert_op = 0;
			}
			if(cin.fail())
			{ 
				cout << "cin failed, thus loop was generated, therefor terminated" << endl;
				exit(-1);
			}
		}
		else if(cmd == "get")
		{
		
		}
		else if(cmd == "peek")
		{
		
		}
		else if(cmd == "update")
		{
		
		}
		else if(cmd == "delete")
		{
		
		}
		else if(cmd == "list")
		{
		
		}
	}// original

	return 0;	
}
