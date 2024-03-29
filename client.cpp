#include <iostream>
#include <memory>
#include <string>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "util.h"
#include <arpa/inet.h>

using namespace std;
//path del socket sin comando
char *socket_path = (char*)"/tmp/db.tuples.sock";

int main(int argc, char** argv) {
	int op1=htonl(1),op2=htonl(2),op3=htonl(3),op4=htonl(4),op5=htonl(5),op6=htonl(6),op7=htonl(7),op8=htonl(8);//insert(,) , insert , get , peek,update,delete,list opciones reservadas para el server
	string cmd = "";
	int insert_op = 0;
	int k,v;//int for key and values.
	int converted_k,converted_v;// int para pasarlos segun htonl
	//socket
	struct sockaddr_un addr;
	char buf[256];
	int fd,rc;
	int nn; //for errors
	
	/*
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
	
	while (cmd != "quit")
	{
		cout << "Ingrese comando" <<endl <<  ">";
		cin >> cmd;
		if(cmd == "connect")
		{
			//Para las conexiones 
			//funciona
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
			if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
			{
				close(fd);
				cout << "Disconnected" << endl;
			}	
			//cout << "No entro al disconected" << endl;
		}
		else if(cmd == "quit"){
			//funciona
			if (connect(fd, (struct sockaddr*)&addr, sizeof(addr)) == -1)
			{
				close(fd);
			}
			exit(-1);
		}
		else if(cmd == "insert")
		{
			//hace el envio de key values
			cout << "Press 1 for key,value" << endl;
			cout << "Press 2 for value" << endl << ">";
			cin >> insert_op;
			if(insert_op == 1)
			{
				cout << "Desired key" << endl << ">";
				cin >> k;
				cout << "Desired value" << endl << ">";
				cin >> v;
				if( k > 0 && k < 9){ cout << "Key error\n1 to 8 not valid\n" <<endl; continue;}
				write(fd,&op1,sizeof(op1));
				converted_k = htonl(k);//host a network byte int
				converted_v = htonl(v);
				write(fd,&converted_k,sizeof(converted_k));//pasa el key
				write(fd,&converted_v,sizeof(converted_v));//pasa el value
			}	
			
			else if(insert_op == 2)
			{
				//envio de values
				cout << "Desired value" << endl << ">";
				cin >> v;
				converted_v = htonl(v);
				write(fd,&op2,sizeof(op2));
				write(fd,&converted_v,sizeof(converted_v));
			}
			if(cin.fail())
			{ //maneja error en caso de fallo de cin
				cout << "cin failed, thus loop was generated, therefor terminated" << endl;
				exit(-1);
			}
		}
		else if(cmd == "get")
		{
			cout << "key of the desired value" << endl << ">";
			cin >> k;
			converted_k = htonl(k);
			if( k > 0 && k < 9){ cout << "Key error\n1 to 8 not valid\n" <<endl; continue;}
			write(fd,&op3,sizeof(op3));
			write(fd,&converted_k,sizeof(converted_k));
			//read
			if ( ( rc=read(fd,&nn,sizeof(nn))) > 0 )
			{
				if( ntohl(nn) == 1)
				{
					cout << "Key not found" << endl;
				}
				else
				{
					cout << htonl(nn) << endl;
				}
				
			}
			if(cin.fail())
			{ //maneja error en caso de fallo de cin
				cout << "cin failed, thus loop was generated, therefor terminated" << endl;
				exit(-1);
			}
		}
		else if(cmd == "peek")
		{
			cout << "Input key" << endl << ">";
			cin >> k;
			converted_k = htonl(k);
			if( k > 0 && k < 9){ cout << "Key error\n1 to 8 not valid\n" <<endl; continue;}
			write(fd,&op4,sizeof(op4));
			write(fd,&converted_k,sizeof(converted_k));
			//falta hacer read aqui
			if(cin.fail())
			{ //maneja error en caso de fallo de cin
				cout << "cin failed, thus loop was generated, therefor terminated" << endl;
				exit(-1);
			}
		}
		else if(cmd == "update")
		{
			cout << "Input key" << endl << ">";
			cin >> k;
			converted_k = htonl(k);
			if( k > 0 && k < 9){ cout << "Key error\n1 to 8 not valid\n" <<endl; continue;}
			write(fd,&op5,sizeof(op5));
			write(fd,&converted_k,sizeof(converted_k));
			//falta un read
			if(cin.fail())
			{ //maneja error en caso de fallo de cin
				cout << "cin failed, thus loop was generated, therefor terminated" << endl;
				exit(-1);
			}
		
		}
		else if(cmd == "delete")
		{
			cout << "Input key" << endl << ">";
			cin >> k;
			converted_k = htonl(k);
			if( k > 0 && k < 9){ cout << "Key error\n1 to 8 not valid\n" <<endl; continue;}
			write(fd,&op6,sizeof(op6));
			write(fd,&converted_k,sizeof(converted_k));
			//falta un read
			if(cin.fail())
			{ //maneja error en caso de fallo de cin
				cout << "cin failed, thus loop was generated, therefor terminated" << endl;
				exit(-1);
			}
		}
		else if(cmd == "list")
		{
			write(fd,&op7,sizeof(op7));
			while(1)
			{
				//read del socket para la lista
				break;
			}
		}
	}
	write(fd,&op8,sizeof(op8));
	close(fd);
	return 0;	
}
