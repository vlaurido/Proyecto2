#include <stdio.h>
#include <libudev>

/*ESTRUCTURAS*/

//Definimos estructura para obtener dispositivo
struct udev_devide* obtener_hijo(struct udev* udev, struct udev_device* padre, const char* subsistema){
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

/*FUNCIONES*/

//Definimos función para enumerar los dispositivos de almacenamiento masivo
static void enumerar_disp_alm_masivo(struct udev* udev){
	struct udev_enumerate* enumerar =  udev_enumerate_new(udev);
	
	//Buscamos los dispositivos USB del tipo SCSI (MASS STORAGE)

}
