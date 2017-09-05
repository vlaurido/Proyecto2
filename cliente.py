#Archivo para probar el proyecto
import requests
import json

if (len(sys.argv) != 4 or (len(sys.argv) != 6):
    #SOLICITUD 1
    if sys.argv[3]=="listar_dispositivos":
        if sys.argv[2]=="GET":
            url="http://127.0.0.1:"+str(sys.argv[1])+"/"+sys.argv[3]
            print(url)
            r=requests.get(url)
            dic=r.json()
            print("ENCABEZADOS:",r.headers)
            print("CODIGO ESTADO:",r.status_code)
            print("JSON RESPUESTA:",dic)
            print("JSON STATUS:",dic['status'])
            print("LISTADO DE DISPOSITIVO:",dic['dispositivos'])
    #SOLICITUD 2
    elif sys.argv[3]=="nombrar_dispositivo":
        if sys.argv[2]=="POST":
            url="http://127.0.0.1:"+str(sys.argv[1])+"/"+sys.argv[3]
            jsons={"solicitud":sys.argv[3],"nodo": sys.argv[4],"nombre":sys.argv[5]}
            print(url)
            r=requests.post(url,json=json.dumps(jsons))
            dic=r.json()
            print("ENCABEZADOS:",r.headers)
            print("CODIGO ESTADO:",r.status_code)
            print("JSON RESPUESTA:",dic)
            print("JSON STATUS:",dic['status'])
    #SOLICITUD 3
    #SOLICITUD 4
else:
    print("No se ingresaron bien los parametros.")
    print("Para listar dispositivos: cliente.py <IP> <GET> <listar_dispositivos>")
    print("Para nombrar dispositivo: cliente.py <IP> <POST> <nombrar_dispositivo> <nodo> <nombre>")
