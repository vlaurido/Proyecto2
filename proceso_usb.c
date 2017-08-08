#include <stdio.h>
#include <libudev.h>

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
	udev_enumerate_add_match_subsystem(enumerar, "scsi");
	udev_enumerate_add_match_property(enumerar, "DEVTYPE", "scsi_device");
	udev_enumerate_scan_devices(enumerar);
	
	//Obtenemos los dispositivos con dichas caracteristicas
	struct udev_list_entry *dispositivos = udev_enumerate_get_list_entry(enumerar);
	struct udev_list_entry *entrada;
	
	//Recorremos la lista obtenida
	udev_list_entry_foreach(entrada, dispositivos){
		const char *ruta = udev_list_entry_get_name(entrada);
		struct udev_device* scsi = udev_device_new_from_syspath(udev, ruta);

		//Obtenemos la informacion pertinente del dispositivo
		struct udev_device* block = obtener_hijo(udev, scsi, "block");
		struct udev_device* scsi_disk = obtener_hijo(udev, scsi, "scsi_disk");

		struct udev_device* usb = udev_device_get_parent_with_subsystem_devtype(scsi, "usb", "usb_device");
		
		if (block && scsi_disk &&usb){
			printf("block = %s, usb = %s:%s, scsi = %s\n", udeb_device_get_devnode(block), udev_device_get_sysattr_value(useb, "idVendor"), udev_device_get_sysattr_value(useb, "idProduct"), udev_device_get_sysattr_value(useb, "vendor"));
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
}
