### HTTP Server Sketch

#### Español

Con este sketch podrás manejar tu *WiFi + Relay Board Kit* con solicitudes ```GET``` desde cualquier dispositivo. Para ilustrar los ejemplos utilizaré ```curl``` y ```python```.

##### Encender relé

Para encender los relés utilizaremos la ruta ```/on``` con el parámetro ```relay``` y el número de relé a encender:

Con ```curl```:
```
curl "http://192.168.1.40/on" --data 'relay=1'
```
Con ```python```:
```
import requets

r = requests.get("http://192.168.1.40" + "/on", params = {'relay': 1})

```

##### Apagar relé

Para apagar los relés utilizaremos la ruta ```/off``` con el parámetro ```relay``` y el número de relé a apagar:

Con ```curl```:
```
curl "http://192.168.1.40/off" --data 'relay=2'
```
Con ```python```:
```
import requets

r = requests.get("http://192.168.1.40" + "/off", params = {'relay': 2})

```

##### Estado de los relés

Para conocer el estado actual de un rele utilizaremos la ruta ```/status``` y el parámetro ```relay``` con el número del relé a consultar:

Con ```curl```:
```
curl "http://192.168.1.40/status" --data 'relay=2'
```
Con ```python```:
```
import requets

r = requests.get("http://192.168.1.40" + "/status", params = {'relay': 2})
print(r.text)

```

#### Opciones

El sketch viene configurado para usar una IP estática, se puede cambiar a una dinámica comentando las líneas ```12-14``` y ```84```.
```mDNS``` está desactivado, para configurarlo es necesario descomentar las líneas ```4``` y ```98-100```, el dispositivo tiene el nombre "kit", para cambiarlo hay que modificar ```mdns.begin("kit", WiFi.localIP())``` en la línea ```98```.

En la carpeta ```HTTP_Server+Panel``` hay una versión de este mismo *sketch* con un panel hospedado en el propio ESP8266 (exceptuando imágenes y archivos javascript y estilos). El panel consta de dos interruptores, uno para cada relé. Para acceder al panel abre un navegador en cualquier dispositivo con acceso a internet e introduce la IP del dispositivo o, si tu sistema operativo soporta Bonjour o Avahi, escribiendo ```kit.local```.



#### English

With this sketch you will be able to control your *WiFi + Relay Board Kit* using ```GET``` requests from any device. For the example I'm going to use ```curl``` and ```python```.

##### Switch On Relay

For switching on one of the relay use the path ```/on``` with the parameter ```relay``` and the relay number:

With ```curl```:
```
curl "http://192.168.1.40/on" --data 'relay=1'
```
With ```python```:
```
import requets

r = requests.get("http://192.168.1.40" + "/on", params = {'relay': 1})

```

##### Switch Off Relay

For switching on one of the relay use the path ```/off``` with the parameter ```relay``` and the relay number:

With ```curl```:
```
curl "http://192.168.1.40/off" --data 'relay=2'
```
With ```python```:
```
import requets

r = requests.get("http://192.168.1.40" + "/off", params = {'relay': 2})

```

##### Relay State

If you want to know the actual state of one of the relays use the path ```/status``` and the parameter ```relay``` with the number of the relay:

With ```curl```:
```
curl "http://192.168.1.40/status" --data 'relay=2'
```
With ```python```:
```
import requets

r = requests.get("http://192.168.1.40" + "/status", params = {'relay': 2})
print(r.text)

```

#### Options

This sketch is configured with an static IP, you can change it to dinamic commenting the lines```12-14``` and ```84```.
```mDNS``` is disabled, to enable it just uncomment lines ```4``` y ```98-100```, the device is named "kit", to change it modify ```mdns.begin("kit", WiFi.localIP())``` in line ```98```.

There is a version of this same sketch with a control panel hosted in the ESP8266 (but the images, and javascript and styles files). This panel has two switch, one for each relay. To access this panel open a browser in any device with internet access an open the device IP or, if your operating system support Bonjour or Avahi, open ```kit.local```.

