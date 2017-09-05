#Archivo para probar el proyecto
#Json con las ordenes para el programa

import requests
import json

def menu():
    print(
        """
        **** Menu ****
        1. Listar dispositivos
        2. Nombrar dispositivo
        3. Leer archivo
        4. Escribir archivo
        5. Salir
        """
    )

print("** Cliente python de prueba **")

IP = input("Ingrese la IP a usar: ")
PORT = input("Ingrese el puerto a usar: ")
URL = "http://"+IP+":"+PORT

menu()
option = input("Escoja una opcion: ")
while option != '1' and option != '2' and option != '3' and option != '4' and option != '5':
    option = input("Opcion no valida. Escoja una opcion correcta: ")

while (option != '5'):
    if option == '1':
        r = requests.get(url+"/listar__dispositivos")
        print("Estado: ", r.status_code)
        print("JSON: ", r.json())
    
    elif option == '2':
        info = {
            "solicitud": "nombrar_dispositivo",
            "nodo": input("Ingrese la direccion del nodo: "),
            "nombre": input("Ingrese el nombre del dispositivo: ")
        }
        r = requests.post(url+"/nombrar_dispositivo", json=json.dumps(info))
        print("Estado: ", r.status_code)
        print("JSON: ", r.json())
    
    elif option == '3':
        info = {
            "solicitud": "leer_archivo",
            "nombre": input("Ingrese el nombre del dispositivo: "),
            "nombre_archivo": input("Ingrese el nombre del archivo: ")
        }
        r = requests.post(url+"/leer_archivo", data=info)
        print("Estado: ", r.status_code)
        print("JSON: ", r.json())        
    
    else:
        nombre_archivo = input("Ingrese el nombre del archivo: ")
        try:
            archivo = open(nombre_archivo, "r")
            contenido = ""
            for linea in archivo:
                contenido += linea
            archivo.close()
        except:
            print("Ese archivo no existe")
            break
        info = {
            "solicitud": "escribir_archivo",
            "nombre": input("Ingrese el nombre del dispositivo: "),
            "nombre_archivo": nombre_archivo,
            "contenido": contenido,
            "tamano_contenido": len(contenido)
        }
        r = requests.post(url+"/escribir_archivo", data=info)
        print("Estado: ", r.status_code)
        print("JSON: ", r.json())

    menu()
option = input("Escoja una opcion: ")
while option != '1' and option != '2' and option != '3' and option != '4' and option != '5':
    option = input("Opcion no valida. Escoja una opcion correcta: ")

if option == '5':
    print("Usted ha salido del programa")