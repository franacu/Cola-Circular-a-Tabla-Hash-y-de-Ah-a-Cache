//
// Created by Fran on 04/09/2024.
//

#ifndef UNTITLED36_HELPER_H
#define UNTITLED36_HELPER_H
#define TAM 10
typedef struct usuarios
{
    struct usuarios *sig;
    struct usuarios *ant;
    int id;
    char nombre[53];
}Usuarios;
typedef struct Cc
{
    Usuarios *pos[TAM];
}ColaCircular;
typedef struct TablaHash
{
    Usuarios *pos[TAM];
}TablaHash;
Usuarios *hash[TAM];
typedef struct cache
{
    Usuarios *cache;
    int tamanio;
    int capacidad;
}Cache;
Usuarios *newUsuario(char *nombre,int id);
ColaCircular *newColaCircular();
TablaHash *newTablaHash();
Cache *newCache(int capacidad);
void agregarEnCola(ColaCircular*cola,Usuarios*usuarioAI);
void transferenciaATabla(ColaCircular*cola,TablaHash*tabla);
void transferenciaACache(TablaHash*tabla,Cache*cache,int id);

#endif //UNTITLED36_HELPER_H
