#include <stdio.h>
#include "lista.h"
#include "pa2mm.h"
#define EXITO 0
#define ERROR -1

void probar_operaciones_lista(){
    lista_t* lista = lista_crear();
    char a='a', b='b', c='c', d='d', w='w';

    lista_insertar(lista, &a);
    lista_insertar(lista, &c);
    lista_insertar_en_posicion(lista, &d, 100);
    lista_insertar_en_posicion(lista, &b, 1);
    lista_insertar_en_posicion(lista, &w, 3);

    lista_borrar_de_posicion(lista, 3);

    printf("Elementos en la lista: ");
    for(size_t i=0; i<lista_elementos(lista); i++)
        printf("%c ", *(char*)lista_elemento_en_posicion(lista, i));

    printf("\n\n");
    /*
    printf("Imprimo la lista usando el iterador externo: \n");
    lista_iterador_t* it = NULL;

    for(it = lista_iterador_crear(lista);
        lista_iterador_tiene_siguiente(it);
        lista_iterador_avanzar(it))
        printf("%c ", *(char*)lista_iterador_elemento_actual(it));
    printf("\n\n");

    lista_iterador_destruir(it);

    int contador=0;
    size_t elementos_recorridos = 0;
    printf("Imprimo la lista usando el iterador interno: \n");
    elementos_recorridos = lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador);

    printf("Recorri %lu elementos con el iterador interno y sume %i elementos\n", elementos_recorridos, contador);

    printf("\n");*/
    lista_destruir(lista);
}

void probar_operaciones_cola(){
    lista_t* cola = lista_crear();

    int numeros[]={1,2,3,4,5,6};

    for(size_t i=0; i<sizeof(numeros)/sizeof(int); i++){
        printf("Encolo %i\n", numeros[i]);
        lista_encolar(cola, &numeros[i]);
    }

    printf("\nDesencolo los numeros y los muestro: ");
    while(!lista_vacia(cola)){
        printf("%i ", *(int*)lista_primero(cola));
        lista_desencolar(cola);
    }
    printf("\n");
    lista_destruir(cola);
}

void probar_operaciones_pila(){
    lista_t* pila = lista_crear();
    char* algo="somtirogla";

    for(int i=0; algo[i]!= 0; i++){
        printf("Apilo %c\n", algo[i]);
        lista_apilar(pila, &algo[i]);
    }

    printf("\nDesapilo y muestro los elementos apilados: ");
    while(!lista_vacia(pila)){
        printf("%c", *(char*)lista_tope(pila));
        lista_desapilar(pila);
    }
    printf("\n");
    lista_destruir(pila);
}

void prueba_crear_lista(){
  lista_t* lista = lista_crear();
  pa2m_afirmar(lista != NULL, "Crear una lista");
  lista_destruir(lista);
}

void prueba_insertar_elementos_secuencia(){
  lista_t* lista = lista_crear();
  for(size_t i=0;i<10;i++)
  {
    lista_insertar(lista, (void*)i);
  }
  int resultado = lista_insertar(lista, (void*)4);
  pa2m_afirmar(resultado == EXITO && lista_elementos(lista) == 11, "Insertar nodos secuenciales");
  void* elemento = lista_elemento_en_posicion(lista, 3);
  pa2m_afirmar(elemento == (void*)3, "Los elementos son correctos al añadir secuencialmente");
  lista_destruir(lista);
}

void prueba_insertar_elementos_aleatorio(){
  lista_t* lista = lista_crear();
  for(size_t i=0;i<10;i++)
  {
    lista_insertar(lista, (void*)i);
  }
  int resultado = lista_insertar_en_posicion(lista, (void*)99, 3);
  pa2m_afirmar(resultado == EXITO && lista_elementos(lista) == 11, "Insertar nodo aleatorio");
  void* elemento = lista_elemento_en_posicion(lista, 3);
  pa2m_afirmar(elemento == (void*)99, "Los elementos son correctos al añadir aleatoriamente");
  lista_destruir(lista);
}

int main(){
  pa2m_nuevo_grupo("Creación de lista");
  prueba_crear_lista();
  pa2m_nuevo_grupo("Inserción secuencial y aleatoria");
  prueba_insertar_elementos_secuencia();
  prueba_insertar_elementos_aleatorio();
  return 0;
}
