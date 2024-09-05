#include "helper.h"
#include "helper.h"
#include <stdio.h>

int main() {
    // Crear una ColaCircular, una TablaHash y una Cache
    ColaCircular *cola = newColaCircular();
    TablaHash *tabla = newTablaHash();
    Cache *cache = newCache(5);  // Capacidad de la caché es 5

    // Crear algunos usuarios
    Usuarios *user1 = newUsuario("Carlos", 1);
    Usuarios *user2 = newUsuario("Juan", 2);
    Usuarios *user3 = newUsuario("Marcos", 3);

    // Agregar usuarios a la cola circular
    agregarEnCola(cola, user1);
    agregarEnCola(cola, user2);
    agregarEnCola(cola, user3);

    // Transferir usuarios de la cola a la tabla hash
    transferenciaATabla(cola, tabla);
    transferenciaATabla(cola, tabla);

    transferenciaACache(tabla, cache, 1);
    transferenciaACache(tabla, cache, 3);

    printf("Contenido de la caché:\n");
    Usuarios *aux = cache->cache;
    while (aux != NULL) {
        printf("Usuario: %s, ID: %d\n", aux->nombre, aux->id);
        aux = aux->sig;
    }
    return 0;
}
