#include "lista.h"
#include <stdlib.h>
#define EXITO 0
#define ERROR -1

//Pre: -
//Post: Si puede crear la lista devuelve un puntero a ella
lista_t* lista_crear(){
  lista_t* lista = malloc(sizeof(lista_t));
  if(!lista)
    return NULL;
  lista->nodo_inicio = NULL;
  lista->nodo_fin = NULL;
  lista->cantidad = 0;
  return lista;
}

//Inserta un elemento al final de la lista.
//Devuelve EXITO si pudo insertar o ERROR si no pudo.
int lista_insertar(lista_t* lista, void* elemento){
  if(!lista)
    return ERROR;
  nodo_t* nodo_nuevo = malloc(sizeof(nodo_t));
  if(!nodo_nuevo)
    return ERROR;
  nodo_nuevo->siguiente = NULL;
  nodo_nuevo->elemento = elemento;
  if(lista->cantidad == 0)
  {
    lista->nodo_inicio = nodo_nuevo;
    lista->nodo_fin = nodo_nuevo;
    lista->cantidad = 1;
    return EXITO;
  }
  lista->nodo_fin->siguiente = nodo_nuevo;
  lista->nodo_fin = nodo_nuevo;
  lista->cantidad += 1;
  return EXITO;
}

//Quita de la lista el elemento que se encuentra en la ultima posición.
//Devuelve EXITO si pudo eliminar o ERROR si no pudo.
int lista_borrar(lista_t* lista){
  if(!lista)
    return ERROR;
  if(lista->nodo_fin == NULL)
    return ERROR;
  return EXITO;
}


//Devuelve el último elemento de la lista o NULL si la lista se
//encuentra vacía.
void* lista_ultimo(lista_t* lista){
  if(!lista)
    return NULL;
  if(lista->nodo_fin == NULL)
    return NULL;
  return lista->nodo_fin;
}


//Devuelve true solo si la lista existe y está vacía
bool lista_vacia(lista_t* lista){
  if(!lista)
    return false;
  return (lista->cantidad == 0);
}

//Devuelve la cantidad de elementos almacenados en la lista.
//o 0 si la lista no existe
size_t lista_elementos(lista_t* lista){
  if(!lista)
    return 0;
  return (lista->cantidad);
}

//Apila un elemento.
//Devuelve 0 si pudo o -1 en caso contrario.
int lista_apilar(lista_t* lista, void* elemento){
  return lista_insertar(lista, elemento);
}

//Devuelve el elemento en el tope de la pila o NULL
//en caso de estar vacía.
void* lista_tope(lista_t* lista){
  return lista_ultimo(lista);
}

//Encola un elemento.
//Devuelve EXITO si pudo encolar o ERROR si no pudo.
int lista_encolar(lista_t* lista, void* elemento){
  return lista_insertar(lista, elemento);
}

//Devuelve el primer elemento de la cola o NULL en caso de estar
//vacía.
void* lista_primero(lista_t* lista){
  if(!lista)
    return NULL;
  if(lista->nodo_inicio == NULL)
    return NULL;
  return lista->nodo_inicio;
}

//Pre: Recibe un puntero a una lista
//Post: Libera el bloque de memoria al que apunta
void lista_destruir(lista_t* lista){

  free(lista);
}
