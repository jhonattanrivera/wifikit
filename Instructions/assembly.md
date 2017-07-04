## Español

Esta guía se limita a los componentes que pueden producir alguna duda a la hora de soldarlos: los transistores, los LED, el regulador de tensión y el condensador electrolítico. Se omiten el resto por su naturaleza o por las indicaciones en la propia placa (serigrafiado).

![](https://raw.githubusercontent.com/jorgegarciadev/wifikit/master/pictures/IMG_1003.jpg)

### Transistores

Los transistores son unos PN2222, con encapsulado TO-92 y patillas anchas. No deben confundirse con el regulador de tensión MCP1700, también con encapsulado TO-92 pero patilla estrecha.

Al diseñar la placa utilicé un modelo que luego me fué imposible encontrar, por eso mismo si te fijas en la foto de más arriba no coinciden el serigrafiado con como está soldados los transistores.

![](https://raw.githubusercontent.com/jorgegarciadev/wifikit/master/Instructions/img/01.png)

Como se puede ver en el modelo 3d el lado plano del transitor queda del lado de los optocopladores.


### LED

Se trata de dos LED rojos de 3mm. Los LED tienen en la base una zona plana y una patilla más corta que coinciden con el polo negativo del LED. Éstas deben quedar del lado del los relés.

![](https://raw.githubusercontent.com/jorgegarciadev/wifikit/master/Instructions/img/02.png)


### Condensador electrolítico y regulador de tensión

El condensador electrolítico de 220μF tiene una franja blanca y una patilla más corta que coinciden con el polo negativo del condensador.

![](https://raw.githubusercontent.com/jorgegarciadev/wifikit/master/Instructions/img/03.png)

Estos deben ir del lado del ESP-8266-01.

El regulador de tensión es un MCP1700-3302E con empaquetado TO-92 con patillas estrecha, no confundir con los transistores PN2222 de patillas anchas. El regulador sigue el serigrafiado.



## English

This guide is just for the components that could mislead the user when soldering: transistors, LED, voltage regulator and electrolytic capacitor. The other ones are omited because of their nature or because the indications on the board's silk.

![](https://raw.githubusercontent.com/jorgegarciadev/wifikit/master/pictures/IMG_1003.jpg)


### Transistors

The transistors are PN2222, with TO-92 packaging and wide pins. Don't mistake them with the voltage regulator MCP1700, with TO-92 packaging too but narrow pins.

I couldn't find the model used in the design for the transistors, You can notice in the picture that the position of the transistors doesn't match the board's silk.

![](https://raw.githubusercontent.com/jorgegarciadev/wifikit/master/Instructions/img/01.png)

As you can see in the 3d model the flat side of the transistor is facing the optocouplers.


### LED

There are two 3mm red LED. They have a flat side in their bases and a shorter pin that tell where ground is. Those should face the relays.

![](https://raw.githubusercontent.com/jorgegarciadev/wifikit/master/Instructions/img/02.png)


### Electrolytic capacitor and voltage regulator

The 220μF electrolytic capacitor has a white bar and a shorter pin that coincide with ground.

![](https://raw.githubusercontent.com/jorgegarciadev/wifikit/master/Instructions/img/03.png)

Those should face the ESP-8266-01.

The voltage regulator is a MCP1700-3302E with TO-92 packaging and narrow pins, don't mistake it with the transistors PN2222, with TO-92 packaging too and wide pins. In this case the component follow the board's silk.