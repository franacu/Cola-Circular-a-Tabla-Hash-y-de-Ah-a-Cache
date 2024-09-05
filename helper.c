//
// Created by Fran on 04/09/2024.
//
#include "stdlib.h"
#include "string.h"
#include "stdio.h"
#include "helper.h"
Usuarios *newUsuario(char *nombre,int id)
{
    Usuarios *aux=malloc(sizeof(Usuarios));
    if(aux==NULL)
    {
        printf("Sin memoria disponible\n");
        exit(-1);
    }
    strcpy(aux->nombre,nombre);
    aux->sig=NULL;
    aux->ant=NULL;
    aux->id=id;
    return aux;
}
ColaCircular *newColaCircular()
{
    ColaCircular *aux= malloc(sizeof(ColaCircular));
    if(aux==NULL)
    {
        printf("Sin memoria disponible\n");
        exit(-1);
    }
    for(int i=0;i<TAM;i++)
    {
        aux->pos[i]=NULL;
    }
    return aux;
}
TablaHash *newTablaHash()
{
    TablaHash *aux= malloc(sizeof(TablaHash));
    if(aux==NULL)
    {
        printf("Sin memoria disponible\n");
        exit(-1);
    }
    for(int i=0;i<TAM;i++)
    {
        aux->pos[i]=NULL;
    }
    return aux;
}
Cache *newCache(int capacidad)
{
    Cache *aux= malloc(sizeof(Cache));
    if(aux==NULL)
    {
        printf("Sin memoria disponible\n");
        exit(-1);
    }
    aux->cache=NULL;
    aux->capacidad=capacidad;
    aux->tamanio=0;
    return aux;
}
void agregarEnCola(ColaCircular*cola,Usuarios*usuarioAI)
{
    int posActual=-1;
    for(int i=0;i<TAM;i++)
    {
        if(cola->pos[i]==NULL)
        {
            posActual=i;
        }
    }
    if(posActual==-1)
    {
        for(int i=0;i<TAM-1;i++)
        {
            cola->pos[i]=cola->pos[i+1];
        }
        posActual=TAM-1;
    }
    cola->pos[posActual]=usuarioAI;
}
int Fhash(int id)
{
    return id%TAM;
}
void transferenciaATabla(ColaCircular*cola,TablaHash*tabla)
{
    for(int i=0;i<TAM;i++)
    {
        if(cola->pos[i]!=NULL)
        {
            Usuarios *aux=cola->pos[i];
            cola->pos[i]=aux->sig;

            int index=Fhash(aux->id);
            while (tabla->pos[index]!=NULL)
            {
                index=(index+1)%TAM;
            }
            tabla->pos[index]=aux;
        }
    }
}
void eliminar(Cache*cache)
{
    if (cache->cache == NULL) return;

    Usuarios *act = cache->cache;
    while (act->sig != NULL) {
        act = act->sig;
    }

    if (act->ant != NULL) {
        act->ant->sig = NULL;
    } else {
        cache->cache = NULL;
    }

    hash[act->id] = NULL;
    free(act);
    cache->tamanio--;
}
void apilar(Cache*cache,Usuarios*usuarioAI)
{
    if (cache->cache != NULL) {
        cache->cache->ant = usuarioAI;
    }
    usuarioAI->sig = cache->cache;
    cache->cache = usuarioAI;
    usuarioAI->ant = NULL;
    hash[usuarioAI->id] = usuarioAI;
    cache->tamanio++;
}
void transferenciaACache(TablaHash*tabla,Cache*cache,int id)
{

    int i=Fhash(id);
    Usuarios *act=tabla->pos[i];
    Usuarios *ant=NULL;
    while (act!=NULL)
    {
        if(act->id==id)
        {
            if(ant==NULL)
            {
                tabla->pos[i]=act->sig;
            }else
                {
                    ant->sig=act->sig;
                }

            if(hash[id]==NULL)
            {
                if(cache->tamanio==cache->capacidad)
                {
                    eliminar(cache);
                }
                apilar(cache,act);
                hash[id] = act;
            }else
                {
                    if(cache->cache!=act)
                    {
                        if(act->sig!=NULL)
                        {
                            act->ant->sig=act->sig;
                        }
                        if(act->ant!=NULL)
                        {
                            act->sig->ant=act->ant;
                        }
                    }
                    cache->tamanio--;
                    apilar(cache,act);
                }

        }
        ant=act;
        act=act->sig;
    }
}