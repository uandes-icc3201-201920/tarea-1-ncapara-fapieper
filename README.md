# icc3201-201920-tarea1
Repositorio base para tarea 1 de Sistemas Operativos y Redes 201920

En cliente funciones que faltan es update,delete,list
en server se reciben los datos y conexions pero falta agregar la bd
en peek y get falta hacer la parte de recibir la informacion del server osea el "read"

las dificultades encontradas fue como hacer pasar strings en un principio pero luego 
cambiamos a pasar int en forma htonl y ntohl de la lib arpa por lo que con eso intentamos hacer
que el server reconosca los pedidos del cliente.
tambien de dificultad fue adaptar el uso de socket y entender que se pasan bytes en vez de objetos directamente, osea un stream de dato por lo que complicaba el uso de string.

Para la conexion con el server del cliente y sus comando dejo reservado los numeros desde el 1 al 7 como keys particulares, por lo que no funcionara si el cliente quiere hacer un key value usando esos numeros, por ende hay exit(-1) despues de un cout diciendo error.
