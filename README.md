# Proyecto2
En este proyecto, se creará un programa que se encargará de monitorear los puertos USB, detectando nuevos dispositivos. El programa usará el formato JSON y un API REST para comunicarse con clientes externos, que darán órdenes al programa. El programa ejecutará estas órdenes, y devolverá resultados al cliente.

# Proceso USB
Para poder poner a correr procesos_usb.c es necesario contar con la libreria libudev-dev, la cual se puede instalar en la Terminal con permisos de root con el comando:

  sudo apt-get install libudev-dev

Adicionalmente, es necesario contar con la librería apue.3e, la cual tiene funciones necesarias para que proceso_usb funcione como daemon. Este paquete ya se encuentra descargado en el proyecto.

# Servidor Web
Para poder poner a correr servidor_web.c es necesario contar con la libreria libmicrohttpd, la cual se puede instalar en la Terminal con permisos de root con el comando:

  sudo apt-get install libmicrohttpd

El servidor web recibe solicitudes GET/POST+JSON, por lo cual se usa la libreria jsmn para poder parsear en formato JSON. Esta libreria ya viene instalada con el proyecto.

# Cliente Python
Para poder probar el programa, se facilita un archivo cliente.py el cual le da las indicaciones de como enviar los requerimientos al servidor web.
  1) Para listar dispositivos:
    cliente.py <IP> <GET> <listar_dispositivos>
  2) Para nombrar dispositivo:
    cliente.py <IP> <POST> <nombrar_dispositivo> <nodo> <nombre>
  3) Para leer archivo:
    cliente.py <IP> <GET> <leer_archivo> <nombre> <nombre archivo>
  4) Para escribir archivo:
    cliente.py <IP> <POST> <escribir_archivo> <nombre> <nombre archivo> <tamano contenido> <contenido>

# Autores
Laurido Aguirre Viviana Priscilla & Rivadeneira Sevilla Alexis Leonardo.
Copyrigth (c) 2017.
Escuela Superior Politécnica del Litoral. Guayaquil, Ecuador.
Todos los Derechos Reservados.
