//Librerias usb y main
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libudev.h>
#include <mntent.h> /*mtab*/
#include "funciones_usb.h"

/*ESTRUCTURAS*/

//Estructura que representa a un dispositivo
//Tiene el mismo formato de retorno que el diccionario
//En la funbcion listar_dispositivos
typedef struct dispositivo{
	char *nombre;
	char *id;
	char *vendor;
	char *montaje;
	char *nodo;
}dispositivo;

//Estructura que representa una lista de dispositivos
//La cual posee un puntero a dispositivos usb
//y el numero de dispositivos que hay en la lista
typedef struct dispositivos{
	dispositivo **dispositivos_usb;
	int largoLista;
}dispositivos;


/*FUNCIONES*/

//Definimos funcion para obtener dispositivo
struct udev_device* obtener_hijo(struct udev* udev, struct udev_device* padre, const char* subsistema){
	struct udev_device* hijo = NULL;
	struct udev_enumerate *enumerar = udev_enumerate_new(udev);

	udev_enumerate_add_match_parent(enumerar, padre);
	udev_enumerate_add_match_subsystem(enumerar, subsistema);
	udev_enumerate_scan_devices(enumerar);

	struct udev_list_entry *dispositivos = udev_enumerate_get_list_entry(enumerar);
	struct udev_list_entry *entrada;

	udev_list_entry_foreach(entrada, dispositivos){
		const char *ruta = udev_list_entry_get_name(entrada);
		hijo = udev_device_new_from_syspath(udev, ruta);
		break;
	}

	udev_enumerate_unref(enumerar);
	return hijo;
}

//Definimos función para enumerar los dispositivos de almacenamiento masivo
struct dispositivos* enumerar_disp_alm_masivo(struct udev* udev){
	struct udev_enumerate* enumerar =  udev_enumerate_new(udev);
	dispositivos *lista = (dispositivos *)malloc(sizeof(dispositivo *));
	lista->dispositivos_usb =(dispositivo **)malloc(sizeof(dispositivo *));
	lista->largoLista = 0;

	//Buscamos los dispositivos USB del tipo SCSI (MASS STORAGE)
	udev_enumerate_add_match_subsystem(enumerar, "scsi");
	udev_enumerate_add_match_property(enumerar, "DEVTYPE", "scsi_device");
	udev_enumerate_scan_devices(enumerar);

	//Obtenemos los dispositivos con dichas caracteristicas
	struct udev_list_entry *dispositivos = udev_enumerate_get_list_entry(enumerar);
	struct udev_list_entry *entrada;

	//Recorremos la lista obtenida
	int contElementos = 0;
	udev_list_entry_foreach(entrada, dispositivos){
		const char *ruta = udev_list_entry_get_name(entrada);
		struct udev_device* scsi = udev_device_new_from_syspath(udev, ruta);

		//Obtenemos la informacion pertinente del dispositivo
		struct udev_device* block = obtener_hijo(udev, scsi, "block");
		struct udev_device* scsi_disk = obtener_hijo(udev, scsi, "scsi_disk");

		struct udev_device* usb = udev_device_get_parent_with_subsystem_devtype(scsi, "usb", "usb_device");

		if (block && scsi_disk &&usb){
			dispositivo *dispUsb = (dispositivo *)malloc(sizeof(dispositivo));
			char *id = (char *)malloc(sizeof(char));
			char *vendor = (char *)malloc(sizeof(char));
			char *montaje = (char *)malloc(sizeof(char));
			char *nodo = (char *)malloc(sizeof(char));

			strcpy(id,(char *)udev_device_get_sysattr_value(usb, "idProduct"));
			strcpy(vendor,(char *)udev_device_get_sysattr_value(usb, "vendor"));
			strcpy(nodo,(char *)udev_device_get_devnode(block));

			dispUsb->nombre = "";
			dispUsb->id = id;
			dispUsb->vendor = vendor;
			dispUsb->nodo = nodo;

			struct mntent *m;
			FILE *f = setmntent("/etc/mtab", "r");

			while((m = getmntent(f))){
				if (strstr(m->mnt_fsname,udev_device_get_devnode(block)) != NULL)
				{
					strcpy(montaje, (char *)m->mnt_dir);
					dispUsb->montaje = montaje;
				}
			}
			contElementos++;
			*((lista->dispositivos_usb)+contElementos) = dispUsb;
			endmntent(f);
		}

		if (block){
			udev_device_unref(block);
		}

		if (scsi_disk){
			udev_device_unref(scsi_disk);
		}

		udev_device_unref(scsi);
	}

	udev_enumerate_unref(enumerar);

	lista->largoLista = contElementos;
	return lista;
}
