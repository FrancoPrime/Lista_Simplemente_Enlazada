#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "pa2mm.h"
#define EXITO 0
#define ERROR -1

bool mostrar_elemento(void* elemento, void* contador){
    if(elemento && contador)
        (*(int*)contador)++;
    return true;
}

void probar_operaciones_iteradores(){
    lista_t* lista = lista_crear();
    char a='a', b='b', c='c', d='d';
    char e='e', f='f', g='g', h='h';

    lista_insertar(lista, &a);
    lista_insertar(lista, &c);
    lista_insertar_en_posicion(lista, &d, 100);
    lista_insertar_en_posicion(lista, &b, 1);
    lista_insertar(lista, &e);
    lista_insertar(lista, &f);
    lista_insertar(lista, &g);
    lista_insertar(lista, &h);

    lista_iterador_t* it = NULL;

    it = lista_iterador_crear(lista);
    lista_iterador_avanzar(it);
    lista_iterador_avanzar(it);
    pa2m_afirmar(*(char*)lista_iterador_elemento_actual(it) == c, "El iterador externo funciona");
    lista_iterador_destruir(it);
    int contador = 0;
    size_t elementos_recorridos = 0;
    elementos_recorridos = lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador);
    pa2m_afirmar(elementos_recorridos == 8 && contador == 8, "El iterador interno funciona");
    lista_destruir(lista);
}

void probar_operaciones_cola(){
    lista_t* cola = lista_crear();

    int numeros[]={1,2,3,4,5,6};

    for(size_t i=0; i<sizeof(numeros)/sizeof(int); i++){
        lista_encolar(cola, &numeros[i]);
    }

    bool respeta_elementos=true;
    int i=1;
    while(!lista_vacia(cola)){
        if(*(int*)lista_primero(cola) != i)
          respeta_elementos = false;
        lista_desencolar(cola);
        i++;
    }
    pa2m_afirmar(respeta_elementos, "Cumple las funciones de cola");
    lista_destruir(cola);
}

void probar_operaciones_pila(){
    lista_t* pila = lista_crear();
    char* algo="somtirogla";
    char texto_resultado[20];
    strcpy(texto_resultado, "Nada");
    for(int i=0; algo[i]!= 0; i++){
        lista_apilar(pila, &algo[i]);
    }
    size_t i=0;
    while(!lista_vacia(pila)){
        texto_resultado[i] = *(char*)lista_tope(pila);
        lista_desapilar(pila);
        i++;
    }
    texto_resultado[i] = '\0';
    pa2m_afirmar(strcmp(texto_resultado, "algoritmos") == 0, "Cumple las funciones de pila");
    lista_destruir(pila);
}

void probar_crear_lista(){
  lista_t* lista = lista_crear();
  pa2m_afirmar(lista != NULL, "Crear una lista");
  lista_destruir(lista);
}

void probar_insertar_con_NULL(){
  int resultado = lista_insertar(NULL, (void*)2);
  pa2m_afirmar(resultado == ERROR, "Quiero insertar un numero a NULL y no me deja");
  resultado = lista_insertar_en_posicion(NULL, &resultado, 3);
  pa2m_afirmar(resultado == ERROR, "Quiero insertar un numero a NULL en una posicion y no me deja");
  resultado = lista_borrar(NULL);
  pa2m_afirmar(resultado == ERROR, "Quiero borrar el ultimo elemento de una lista NULL y no me deja");
  resultado = lista_borrar_de_posicion(NULL, 5);
  pa2m_afirmar(resultado == ERROR, "Quiero borrar el quinto elemento de una lista NULL y no me deja");
  void* elemento = lista_elemento_en_posicion(NULL, 5);
  pa2m_afirmar(elemento == NULL, "Quiero obtener el quinto elemento de una lista NULL y me devuelve NULL");
  void* elemento2 = lista_ultimo(NULL);
  pa2m_afirmar(elemento2 == NULL, "Quiero obtener el ultimo elemento de una lista NULL y me devuelve NULL");
  bool vacia = lista_vacia(NULL);
  pa2m_afirmar(vacia == true, "Quiero saber si una lista NULL está vacia");
  size_t cantidad_elementos = lista_elementos(NULL);
  pa2m_afirmar(cantidad_elementos == 0, "La cantidad de elementos de una lista NULL es 0");
  lista_iterador_t* iterador = lista_iterador_crear(NULL);
  pa2m_afirmar(iterador == NULL, "Quiero crear un iterador con una lista NULL y me devuelve NULL");
  bool tiene_siguiente = lista_iterador_tiene_siguiente(NULL);
  pa2m_afirmar(tiene_siguiente == false, "Un iterador NULL no tiene siguiente");

}

void probar_insertar_elementos_secuencia(){
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

void probar_insertar_elementos_aleatorio(){
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
  probar_crear_lista();
  pa2m_nuevo_grupo("Inserción secuencial y aleatoria");
  probar_insertar_elementos_secuencia();
  probar_insertar_elementos_aleatorio();
  pa2m_nuevo_grupo("Inserción de cosas con NULL");
  probar_insertar_con_NULL();
  pa2m_nuevo_grupo("Iteradores");
  probar_operaciones_iteradores();
  pa2m_nuevo_grupo("Operaciones de pila y cola");
  probar_operaciones_pila();
  probar_operaciones_cola();

  return pa2m_mostrar_reporte();
}
