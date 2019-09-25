# icc3201-201920-tarea1
Repositorio base para tarea 1 de Sistemas Operativos y Redes 201920

Nicolas Apara, Francisco Pieper

### TAREA 1 parte 1
### Dificultades encontradas

En esta parte del trabajo nos encontramos con varias dificultades. La primera fue como pasar un `string` de cliente a servidor, lo cual pudimos solucionar cambiando este `string` por `int` a travez de `htonl` y `ntohl` de la libreria arpa. A traves de esto logramos el flujo de informacion entre servidor/cliente y que se reconocieran las peticiones del cliente al servidor.

```
	cout << "Desired key" << endl << ">";
	cin >> k;
	cout << "Desired value" << endl << ">";
	cin >> v;
	if( k > 0 && k < 5){ cout << "Key error" <<endl; exit(-1);}
	write(fd,&op1,sizeof(op1));
	converted_k = htonl(k);
	converted_v = htonl(v);
	write(fd,&converted_k,sizeof(converted_k));
	write(fd,&converted_v,sizeof(converted_v));
```
Otra dificultades que encontramos fue adaptar el uso de sockets y entender su funcionalidad. Entender el como se traspasan bytes en lugar de texto o variables, es decir, un stream de datos lo cual nos hizo investigar como lograr este flujo sin utilizar `string`.

### Funciones no implementadas

Las funciones que no logramos implementar fueron:
 - En nuestro Client:
  - Update()
  - Delete()
  - List()
  - Peek(), esta incompleta, falta que reciban la informacion del Server, es decir, no esta implementado el Read.
  - Get(), al igual que el Peek(), falta el Read.

 - En nuestro Server, mas alla de faltar funciones, estas logran recibir los datos del cliente pero falta que las guarden en la base de datos.

### Problemas conocidos

Para la conexion Server/Client y sus comandos, tuvimos que dejar reservado los numeros del 1 al 7 como keys particulares, por lo que en el case de que el Client quiera hacer un key-value usando uno de estos numeros, se provocara un error, por lo que programamos un  `exit(-1)` si ocurre este caso y luego un mensaje de error en pantalla.

### TAREA 1 parte 2

En esta parte del trabajo nos encontramos con la dificultad de poder hacer los threads del servidor, de tal forma en que cada thread atienda un cliente. Lo cual solucionamos usando la libreria threads y vector para crear un vector de threads que los mantiene sin interrumpir el servidor.

'''
	vector<unique_ptr<thread>> threads;
	for(;;)
	{
		if ( (cl = accept(fd, NULL, NULL)) == -1)
		{
	    		perror("accept error");
	     		continue;
	   	}
		threads.emplace_back(new thread(coneccion,cl));//aqui asigno el thread a la funcion
	}
'''
La siguiente dificultad que encontramos fue lograr que al salir de un thread, no se termine el proceso del server principal.

### Funciones no implementadas

Las funciones que no logramos implementar fueron:
 - En nuestro Client:
  - Update(), falta implementar el read
  - Delete(), falta implementar el read
  - Peek(), esta incompleta, falta que reciban la informacion del Server, es decir, no esta implementado el Read.
No logramos hacer que el usuario escribiera la direccion del servidor ocupando el flag -s, es por esto que es necesario escribir la direccion /tmp/db.tuples.sock cuando se pregunte en la consola del usuario luego de escribir el comando connect.

### Problemas conocidos

Para la conexion Server/Client y sus comandos, tuvimos que dejar reservado los numeros del 1 al 8 como keys particulares, por lo que en el case de que el Client quiera hacer un key-value usando uno de estos numeros, se provocara un error, por lo que programamos un mensaje de error en pantalla y un  `continue` si ocurre este caso.
