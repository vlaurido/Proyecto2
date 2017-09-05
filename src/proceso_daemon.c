#include <sys/types.h>          /* some systems still require this */
#include <sys/stat.h>
#include <stdio.h>              /* for convenience */
#include <stdlib.h>             /* for convenience */
#include <stddef.h>             /* for offsetof */
#include <string.h>             /* for convenience */
#include <unistd.h>             /* for convenience */
#include <signal.h>             /* for SIG_ERR */
#include <netdb.h>
#include <errno.h>
#include <syslog.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/resource.h>
#include <libudev.h>
#include "funciones_usb.h"

#define BUFLEN 1000000
#define QLEN 10
#define BUFRD 100

#ifndef HOST_NAME_MAX
#define HOST_NAME_MAX 256
#endif

void servidor_usb(){
	struct sockaddr_in direccion_servidor;
	struct sockaddr_in direccion_cliente;
	char *host;
	int puerto;
	int sockfd;
	int clfd;
	unsigned int clsize;
	int n;
	struct udev *p;

	puerto = 8080;

	if (( n = sysconf(_SC_HOST_NAME_MAX)) < 0)
		n = HOST_NAME_MAX; /* best guess */
	if ((host = malloc(n)) == NULL)
		printf(" malloc error");
	if (gethostname( host, n) < 0) 		//Obtenemos nombre del host
		printf(" gethostname error");

	//Creamos el socket
	sockfd = socket(((struct sockaddr *)&direccion_servidor)->sa_family, SOCK_STREAM, 0);
	if (sockfd == -1) {
		printf("Error al abrir el socket\n");
		exit(-1);
	}

	//Configuramos la direccion del socket
	memset(&direccion_servidor, 0, sizeof(direccion_servidor));	//ponemos en 0 la estructura direccion_servidor

	//llenamos los campos
	direccion_servidor.sin_family = AF_INET;		//IPv4
	direccion_servidor.sin_port = htons(puerto);		//Convertimos el numero de puerto al endianness de la red
	direccion_servidor.sin_addr.s_addr = INADDR_ANY;	//Nos vinculamos a la interface localhost o podemos usar INADDR_ANY para ligarnos A TODAS las interfaces

	if (bind(sockfd, (struct sockaddr *)&direccion_servidor, sizeof(direccion_servidor)) != 0){
		printf("Error con la direccion del servidor\n");
		exit(-1);
	}
	if (listen(sockfd, 1000) == -1){
		printf("Error al escuchar el puerto\n");
		exit(-1);
	}

	while(1) {
		clfd = accept(sockfd,(struct sockaddr *)&direccion_cliente,&clsize);
		if (clfd < 0) {
				syslog( LOG_ERR, "Error al aceptar la conexion: %s", strerror(errno));
				exit(-1);
		}

		char *request = malloc(BUFLEN*sizeof(char *));
		recv(clfd, request, BUFLEN, 0);

	  if ((strstr(request, "GET") != NULL) && (strstr(request, "listar_dispositivos") != NULL)){
			p = udev_new();
			struct dispositivos *listaDisp = enumerar_disp_alm_masivo(p);
			send(clfd, listaDisp, 1000, 0);
		}
		close(clfd);
	}
}

//Programa principal que se ejecuta como daemon
int main(int argc, char* argv[]){
	pid_t pid;
  pid = fork();

  if (pid < 0) {
      printf("Fallo de fork\n");
      exit(1);
  }
  if (pid > 0) {
      printf("Id del proceso hijo: %d\n",pid);
      exit(0);
  }

  umask(0);

  int sid = setsid();
  if (sid < 0) {
			printf("Fallo al crear nueva sesion\n");
      exit(1);
  }

  close(0);
  close(1);
  close(2);

  while(1) {
      servidor_usb();
  }
  return 0;
}
