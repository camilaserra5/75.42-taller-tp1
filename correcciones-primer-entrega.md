* client.c: mover la función `main` a otra unidad de compilación. Crear TDA "client" que le de una cohesión a todos los TDAs usados en esta aplicación cliente. las funciones "privadas" marcarlas como static.
* server.c: idem cliente
* common_protocol.c: Este TDA queda medio colgado, podría ser el que se encarga de coordinar el encriptador con el socket, pero dado el tamaño del TP podría incluso ni existir. `server_receive` libera y crea un buffer innecesariamente, podría usar el mismo buffer reutilizándose, o incluso recibir el buffer ya creado (quedando este TDA como una capa redundante sobre `socket`).
* common_socket.c: Falta loop entre candidatos de init al usar getaddrinfo (ver ejemplo en `man getaddrinfo`). No es necesario 
* server.c: ligado a lo anterior, `_read_and_decode` podría  proveerle un buffer estático a protocol_server_receive y evitar el uso de memoria dinámica.
* `socket_accept`: ¿Por qué duplicar el file descriptor?
* No utilizar `#define _GNU_SOURCE`
* Documentar brevemente TDAs (structs) y las funciones asociadas.
