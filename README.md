# [75.42] Taller de programación I
## Trabajo práctico 1: Crypto-Sockets<br><sup>2do cuatrimestre 2020</sup>

**Camila Serra**  
**97422**  
**camilaserra5@gmail.com**  
**https://github.com/camilaserra5/75.42-taller-tp1**

_________________
## Introducción
Para este trabajo se implementará un servicio de cifrado con una arquitectura de cliente-servidor. Se desarrollará en el lenguaje de programación C.

En el presente informe se detalla la solución propuesta y las diferentes pruebas realizadas para garantizar el correcto funcionamiento.

- [Objetivos](#https://github.com/camilaserra5/75.42-taller-tp1#objetivos)
- [Diseño](#https://github.com/camilaserra5/75.42-taller-tp1#diseño)
- [Pruebas](#https://github.com/camilaserra5/75.42-taller-tp1#pruebas)
- [Referencias](#https://github.com/camilaserra5/75.42-taller-tp1#referencias)

## Objetivos
El objetivo del presente trabajo es realizar dos programas. El primer programa es un emisor (cliente) que se encarga se leer mensajes de la entrada estándar y enviarlos cifrado. El otro programa es el receptor (servidor), que se encargará de recibir los mensajes cifrados, descifralos y mostrarlos por salida estándar.

Los  algoritmos de cifrado a implementar serán:
- Cifrado de César
- Cifrado de Vigenere
- Rivest Cipher 4

Los mensajes leídos en la entrada estándar deberán ser leídos de a 64 Bytes.

El programa será ejecutado de la siguiente manera:
```bash
./server [port] --method=[method] --key=[key]
```
```bash
./client [host] [port] --method=[method] --key=[key] < input
```
## Diseño
Para resolver el problema planteado se crearon dos aplicaciones distintas. Una para el cliente y una para el servidor. El objetivo de esta sección es explicar el funcionamiento de cada una.

A continuación se muestran dos diagramas de secuencia (uno para el servidor y uno para el cliente) del camino feliz del programa en el cual se realiza correspondientemente el cifrado y descifrado.
### Servidor
![](http://www.plantuml.com/plantuml/png/ZL9BQiCm4Dtx5BDCm6ttePGiUe12wIe4OqlZH4JM66aScfB3TnHPhHDIquNXINwVqPFMWMlFGsUBlT48BH4tz5dKYid3Hq1VzFBVADFNZk4T_V5cwyqJao9xpIDrGBxQUaL5MhJH4nvUHgiLF3w52u9DJvwtiEcGzwG57F2qBOh44yLe2Yi85r0PPtYHS0bHl9mXDyRfH9wbMHCOtJ-8jLBOymznmio52BSVOHerhqh8glFv7B-9E26HxYH3fyggTd2A3Rb5gaRIB54FWsDZeJan1l2e31vHmpCqGzkAHJ1VE1h_CLJglH8fcYDEnaiELNHO5bbvhuGiJSiiBC6Ys_5-EHyVJzXX2FNkDtlIU7um8aazBAxTIv3tKGArROXLejEvplbOZO4zdUv6tfulS_DzhILbwEmt)

### Cliente
![](http://www.plantuml.com/plantuml/png/VP51QyCm38Nl_XKwff1jzp96OUm-63kL4b9RQKnTATZAM4T__9pQfWjbEPI-IEzzv2cR8AsNyUHKRmr2nonx_bQj5lRm6T2h8UwjjaDB0g_E8ibizEvPMBER3JzO7t7kUoFD9k8c9ZoyPDGQ7f_Yu2lEjZq7sS5sO3_zdL1wDb4SyRnJAjbZCBDX3U4g6ajMggHhc1Wm4LOB2Sr4g7DevYnbedV8Cl7BKmqbf2wNo_LtIsUrXWDAWwblqusanJ9LgL0CEkO1HXBhO7yM3E2nDV0C-x7hq4EmFtY3bhj5QY9MoLQ3Gpf8NqEyJmtSTU5MvPyc-hfi0fBvKsZEMwcIlBzSZYPz7rHnMQwo_286WtW-LsMmzB6AjznzWsJ6a_i5)

### Comunicación cliente-servidor
En lo expuesto en los diagramas anteriores, se puede ver que hay dos TDAs que facilitan la comunicación. El TDA socket es el encargado de crear el socket y manejar toda la conexión y el envío y recepción. Por otro lado, el protocolo se encarga de abstraer eso y permitir al cliente y al servidor enviar y recibir los mensajes con una interfaz sencilla.

### Cifrado - Descifrado

Para la implementación de los 3 algoritmos de cifrado se crearon dos funciones en común, que luego cada cifrador implementa a su manera.
![](http://www.plantuml.com/plantuml/png/ZSv1YeGm48NXVPsYbZF1GtWJoIHF3PEa81Mb6_7k3IqkseMTPJtuYw_NQajTKgGvUF0eKl_aSHmk51V1vA9LPMESf2HvS51RZE6DjeGwYz_Vou3inECdGTLEw3WYJtNk-1_FZcKS5VMN-H9vV8zePxeLbR12wmVfc9fCbwQHT0jQmuIC0cCsOZx_dskRwbgrkeXwPB-a-080)

Se puede ver que los parámertos recibidos por las funciones son idénticos, esto nos permite abstraer las funciones a variables de tipo
```c
void (*encoder_t)(char *, int, const char *, int);
```
```c
void (*decoder_t)(char *, int, const char *, int);
```
De esta manera, al obtener el método correspondiente, se puede asignar un puntero a la función de ese método y poder invocarla de una manera sencilla y evitando hacer múltiples veces la comparación de qué método estamos trabajando.
```c
(*encoder)(buffer, read, key, offset);
```
```c
(*decoder)(buffer, read, key, offset);
```
### Validaciones
Para realizar las validaciones sobre los parámetros recibidos, se creo un utils que contiene validaciones en común para el servidor y el cliente.
Contiene funciones para parsear y obtener los parámetros **method** y **key**. Además para validar que el puerto sea numérico, el método uno de los 3 permitidos, y que la key sea numérica en el caso de Cesar.

![](http://www.plantuml.com/plantuml/png/RL1B3eCW4DrpYbagyGRTU1CoXQcIWcDWD6sCTwzAqxIf2nxmFlEIQRDWaYa6rNj7S6EMAp_An_fa0u6o0NC6hIt7o8EPn8UiDIngYIGzkxKZCULfS73cJizgEmqKhW5CdJrmhZ-P6ODtAFGELkKwqKTEKkrGN_x4lUgeBFntwvbxn8GRHoaV0nluzQ-gfS5jktW1)


## Pruebas
Los siguientes casos de pruebas fueron los provistos por la cátedra:

Method  | Key | STDIN
------------- | ------------- | -------------
cesar  | 5 | Lorem ipsum..
cesar  | 5 | Pan
cesar  | 5 | Attack at dawn
rc4  | Secret | Lorem ipsum..
rc4  | queso | Pan
rc4  | Secret | Attack at dawn
vigenere  | Secret | Lorem ipsum..
vigenere  | queso | Pan
vigenere  | Secret | Attack at dawn

Por otro lado, se hicieron pruebas para validar más casos de uso. Se realizaron casos para probar las distintas validaciones de parámetros erroneos o incompletos

##### Parámetros incompletos
```bash
./server
./server 8080
./server 8080 --method=cesar
./server 8080 --key=2
./server --method=cesar
./server --key=2
./server --method=cesar --key=2
./client
./client localhost
./client localhost 8080
./client localhost 8080 --method=cesar
./client localhost 8080 --key=2
./client localhost --method=cesar
./client localhost --key=2
./client 8080
./client 8080 --method=cesar
./client 8080 --key=2
./client --method=cesar
./client --key=2
./client --method=cesar --key=2
```

##### Method o Key no encontrados
```bash
./server 8080 --method=cesar test
./server 8080 test --key=2
./client localhost 8080 --method=cesar test
./client localhost 8080 test --key=2
```

##### Puerto incorrecto
```bash
./server test --method=cesar --key=2
./client localhost test --method=cesar --key=2
```

##### Key incorrecta
```bash
./server 8080 --method=cesar --key=test
./client localhost 8080 --method=cesar --key=test
```

##### Method incorrecto
```bash
./server 8080 --method=test --key=2
./client localhost 8080 --method=test --key=2
```


## Referencias
* [Caesar Cipher - Wikipedia](https://en.wikipedia.org/wiki/Caesar_cipher)  
* [Caesar online - cryptii](https://cryptii.com/pipes/caesar-cipher)  


* [Vigenere Cipher - Wikipedia](https://en.wikipedia.org/wiki/Vigen%C3%A8re_cipher)  
* [Vigenere online - cryptii](https://cryptii.com/pipes/vigenere-cipher)  


* [RC4 Cipher - Wikipedia](https://en.wikipedia.org/wiki/RC4)  
* [RC4 online - cryptii](https://cryptii.com/pipes/rc4-encryption)  


* [Plant UML Server](http://www.plantuml.com/plantuml/)
