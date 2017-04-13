### Cliente MQTT

#### Español

Con estos dos sketchs podrás manejar tu *WiFi + Relay Board Kit* mediante MQTT. La carpeta ```simple``` contiene la version sin TLS, y la carpeta ```secure``` contiene la versión con TLS, y soporta la versión ```TLSv1.2```. Están basados en la librería y ejemplos de [Adafruit MQTT](https://github.com/adafruit/Adafruit_MQTT_Library), y depende de ella.

Ambas versiones están configurados para conectarse al *broker* MQTT con credenciales. Cada relé se subscribe a un canal diferente, ```[usuario]/relay_one``` y ```[usuario]/relay_two```, que pueden cambiarse de nombre. El dispositivo se suscribe al canal ```/log``` donde informa de la conexión y cambio de estado de los relés.

Los comandos para encender y apagar los relés son ```ON``` y ```OFF```, y ```STATUS``` para conocer el estado actual del relé.

#####Simple

La versión simple necesita los siguientes datos para conectar con el *broker*:

- ```MQTT_SERVER``` dirección del *broker*
- ```MQTT_PORT``` puerto del broker, por definición **1883**
- ```MQTT_USERNAME``` Usuario
- ```MQTT_PASS``` Contraseña

Si el servidor permite conexiones anonimas habrá que modificar las lineas ```28```, ```31``` y ```33```, eliminando cualquier mencion de ```MQTT_USERNAME``` y ```MQTT_PASS```.

Para probar el dispositivo una vez conectado puedes utilizar ```mosquito_pub```:

```
mosquitto_pub -h [servidor] -p [puerto] -t '[usuario]/relay_one' -u [usuario] -P [contraseña] -m 'STATUS'
```

#####Secure

La única diferencia con la versión simple es que esta versión se concta con TLS. Además de los datos necesarios para la versión simple, es necesaria la **huella digital SHA-1** del certificado y ponerla en la variable ```fingerprint```. Solo comprueba si el certificado es correcto, para que setenga la ejecución hay que descomentar la línea ```140```.

Para probar el dispositivo una vez conectado puedes utilizar ```mosquito_pub```:

```
mosquitto_pub -h [servidor] -p [puerto] -t '[usuario]/relay_one' -u [usuario] -P [contraseña] -m 'STATUS'
--cafile ca.crt```

Siendo ```ca.crt``` la clave publica del certificado del *broker* MQTT.

#### English

With this Sketches you will be able to control *WiFi + Relay Board Kit* using the MQTT protocol. The ```simple``` folder contains a version without TLS, and the ```secure``` contians the TLS version, that supports ```TLSv1.2```. They are based on [Adafruit MQTT](https://github.com/adafruit/Adafruit_MQTT_Library) library and its examples, and depends on it.

Bothe versions are setup for connecting to the *broker* MQTT using auth. Each relay subscribes to different topics, ```[username]/relay_one``` and ```[username]/relay_two```, that can be changed. Th device suscribes to the topic ```/log``` where it logs the relays state changes and connction info.

The commands for switching on and off the relays are ```ON``` y ```OFF```, and ```STATUS``` to get the relay's state.

#####Simple

The simple versión need this data to connect to the broker:

- ```MQTT_SERVER``` broker's address
- ```MQTT_PORT``` broker's port, **1883** by default
- ```MQTT_USERNAME``` Username
- ```MQTT_PASS``` Password

If the server allows anonymous connections you have to edit lines ```28```, ```31``` y ```33```, removinf any mention of ```MQTT_USERNAME``` y ```MQTT_PASS```.

Once the device is connected you can try it with ```mosquito_pub```:

```
mosquitto_pub -h [server] -p [port] -t '[username]/relay_one' -u [username] -P [password] -m 'STATUS'
```

#####Secure

The only difference between the simple and secure versions is that the last one uses TLS. In addition for the data needed for the simple version, You need the cert **SHA-1 fingerprint** and put it in the ```fingerprint``` variable. The Sketch is setup to check if the certificate matches, if you want to stop the execution if the cert doesn't match you have to comment the line ```140```.

Once the device is connected you can try it with ```mosquito_pub```:

```
mosquitto_pub -h [server] -p [port] -t '[username]/relay_one' -u [username] -P [password] -m 'STATUS'
--cafile ca.crt```

```ca.crt``` is the public key for the *broker* MQTT server's cert.

