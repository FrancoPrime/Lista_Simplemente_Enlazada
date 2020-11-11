#include <stdio.h>
#include <string.h>
#include "lista.h"
#include "pa2mm.h"
#define EXITO 0
#define ERROR -1

//Si existen ambos parametros aumenta el segundo en 1, y siempre devuelve true
bool mostrar_elemento(void* elemento, void* contador){
    if(elemento && contador)
        (*(int*)contador)++;
    return true;
}

//Prueba operaciones relacionadas con ambos iteradores
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

    lista_iterador_t* it = lista_iterador_crear(lista);
    pa2m_afirmar(it != NULL, "Puedo crear un iterador externo");
    bool puede_avanzar = lista_iterador_tiene_siguiente(it);
    pa2m_afirmar(puede_avanzar == true, "El iterador puede avanzar");

    lista_iterador_avanzar(it);
    lista_iterador_avanzar(it);
    pa2m_afirmar(*(char*)lista_iterador_elemento_actual(it) == c, "Le pido al iterador externo avanzar y funciona");
    lista_iterador_avanzar(it);
    lista_iterador_avanzar(it);
    lista_iterador_avanzar(it);
    lista_iterador_avanzar(it);
    lista_iterador_avanzar(it);
    bool puede_avanzar_ultimo = lista_iterador_avanzar(it);
    pa2m_afirmar(puede_avanzar_ultimo == true, "El iterador puede avanzar hasta el final");
    bool puede_avanzar_mas_alla = lista_iterador_avanzar(it);
    pa2m_afirmar(puede_avanzar_mas_alla == false, "El iterador no puede avanzar más allá del final");
    pa2m_afirmar(lista_iterador_elemento_actual(it) == NULL, "Le pido el elemento cuando ya termino de iterar y me devuelve NULL");
    lista_iterador_destruir(it);
    size_t cant_elementos = lista_elementos(lista);
    int contador = 0;
    size_t elementos_recorridos = 0;
    elementos_recorridos = lista_con_cada_elemento(lista, NULL, (void*)&contador);
    pa2m_afirmar(elementos_recorridos == 0 && contador == 0, "El iterador interno no itera si le pasas una funcion NULL");
    elementos_recorridos = lista_con_cada_elemento(lista, mostrar_elemento, (void*)&contador);
    pa2m_afirmar(elementos_recorridos == cant_elementos && contador == (int)cant_elementos, "El iterador interno realiza una iteración completa");
    elementos_recorridos = lista_con_cada_elemento(lista, mostrar_elemento, NULL);
    pa2m_afirmar(elementos_recorridos == cant_elementos, "El iterador interno realiza la iteración completa sin pasarle contexto");
    lista_destruir(lista);
}

//Prueba que se comporte como una cola, cumpliendo el patrón FIFO
void probar_operaciones_cola(){
    pa2m_afirmar(lista_encolar(NULL, (void*)1) == ERROR, "No me deja encolar en una cola NULL");
    pa2m_afirmar(lista_desencolar(NULL) == ERROR, "No me deja desencolar en una cola NULL");
    pa2m_afirmar(lista_primero(NULL) == NULL, "No hay elementos en una cola NULL");
    lista_t* cola = lista_crear();

    int numeros[]={1,2,3,4,5,6};
    bool hubo_error = false;
    for(size_t i=0; i<sizeof(numeros)/sizeof(int); i++){
        int resultado = lista_encolar(cola, &numeros[i]);
        if(resultado == ERROR) hubo_error = true;
    }
    pa2m_afirmar(hubo_error == false, "Puedo encolar elementos");
    pa2m_afirmar(*(int*)lista_primero(cola) == 1, "Respeta el orden de la cola");
    bool respeta_elementos=true;
    int i=1;
    while(!lista_vacia(cola)){
        if(*(int*)lista_primero(cola) != i)
          respeta_elementos = false;
        lista_desencolar(cola);
        i++;
    }
    pa2m_afirmar(respeta_elementos, "Los elementos se desencolan correctamente");
    lista_destruir(cola);
}

//Prueba que se comporte como una pila, cumpliendo el patron LIFO
void probar_operaciones_pila(){
    pa2m_afirmar(lista_apilar(NULL, (void*)1) == ERROR, "No me deja apilar en una pila NULL");
    pa2m_afirmar(lista_desapilar(NULL) == ERROR, "No me deja desapilar en una pila NULL");
    pa2m_afirmar(lista_tope(NULL) == NULL, "No hay nada apilado en una pila NULL");
    lista_t* pila = lista_crear();
    char* algo="somtirogla";
    char texto_resultado[20];
    strcpy(texto_resultado, "Nada");
    bool hubo_error = false;
    for(int i=0; algo[i]!= 0; i++){
        int resultado = lista_apilar(pila, &algo[i]);
        if (resultado == ERROR) hubo_error = true;
    }
    pa2m_afirmar(hubo_error == false, "Puedo apilar elementos");
    pa2m_afirmar(*(char*)lista_tope(pila) == 'a', "Respeta el orden de la pila");
    size_t i=0;
    while(!lista_vacia(pila)){
        texto_resultado[i] = *(char*)lista_tope(pila);
        lista_desapilar(pila);
        i++;
    }
    texto_resultado[i] = '\0';
    pa2m_afirmar(strcmp(texto_resultado, "algoritmos") == 0, "Los elementos se desapilan correctamente");
    lista_destruir(pila);
}

//Prueba funciones con una lista vacía
void probar_lista_vacia(){
  lista_t* lista = lista_crear();
  pa2m_afirmar(lista != NULL && lista->nodo_inicio == NULL && lista->nodo_fin == NULL && lista_elementos(lista) == 0, "Puedo crear una lista");
  pa2m_afirmar(lista_vacia(lista) == true, "La lista está vacia");
  int resultado = lista_borrar(lista);
  pa2m_afirmar(resultado == ERROR, "No me deja borrar elementos de una lista vacia");
  resultado = lista_borrar_de_posicion(lista, 0);
  pa2m_afirmar(resultado == ERROR, "No me deja borrar el elemento de la posición 0");
  void* elemento = lista_elemento_en_posicion(lista, 0);
  pa2m_afirmar(elemento == NULL, "No puedo obtener el elemento de la posición 0");
  void* elemento2 = lista_ultimo(lista);
  pa2m_afirmar(elemento2 == NULL, "El último elemento no existe");
  lista_destruir(lista);
}

//Prueba funciones pasando NULL como parametro
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
  pa2m_afirmar(lista_apilar(NULL, NULL) == ERROR, "Pruebo apilar en una pila NULL y no me deja");
  pa2m_afirmar(lista_desapilar(NULL) == ERROR, "Pruebo desapilar en una pila NULL y no me deja");
  pa2m_afirmar(lista_tope(NULL) == NULL, "Busco el elemento al tope de una pila NULL y devuelve NULL");
  pa2m_afirmar(lista_primero(NULL) == NULL, "Busco el primer elemento de una cola NULL y devuelve NULL");
  pa2m_afirmar(lista_encolar(NULL, NULL) == ERROR, "Pruebo encolar en una cola NULL y no me deja");
  pa2m_afirmar(lista_desencolar(NULL) == ERROR, "Pruebo desencolar en una cola NULL y no me deja");
  pa2m_afirmar(vacia == true, "Quiero saber si una lista NULL está vacia");
  size_t cantidad_elementos = lista_elementos(NULL);
  pa2m_afirmar(cantidad_elementos == 0, "La cantidad de elementos de una lista NULL es 0");
  lista_iterador_t* iterador = lista_iterador_crear(NULL);
  pa2m_afirmar(iterador == NULL, "Quiero crear un iterador con una lista NULL y me devuelve NULL");
  bool tiene_siguiente = lista_iterador_tiene_siguiente(NULL);
  pa2m_afirmar(tiene_siguiente == false, "Un iterador NULL no tiene siguiente");
  bool puede_avanzar = lista_iterador_avanzar(NULL);
  pa2m_afirmar(puede_avanzar == false, "Quiero avanzar un iterador NULL y no me deja");
  void* elemento3 = lista_iterador_elemento_actual(NULL);
  pa2m_afirmar(elemento3 == NULL, "Quiero obtener el elemento de un iterador NULL y me devuelve NULL");
  size_t iterador_interno = lista_con_cada_elemento(NULL, mostrar_elemento, NULL);
  pa2m_afirmar(iterador_interno == 0, "Quiero usar al iterador interno en una lista NULL y no me deja");
}

//Prueba comportamiento de lista añadiendo y sacando cosas del final
void probar_insertar_elementos_secuencia(){
  lista_t* lista = lista_crear();
  lista_insertar(lista, (void*)7);
  pa2m_afirmar(lista_elementos(lista) == 1, "Inserto un elemento en una lista vacia");
  for(size_t i=0;i<10;i++)
  {
    lista_insertar(lista, (void*)i);
  }
  int resultado = lista_insertar(lista, (void*)4);
  pa2m_afirmar(resultado == EXITO && lista_elementos(lista) == 12, "Inserto varios elementos secuencialmente");
  void* elemento = lista_elemento_en_posicion(lista, 4);
  pa2m_afirmar(elemento == (void*)3, "Los elementos son correctos al añadir secuencialmente");
  pa2m_afirmar(lista_primero(lista) == (void*)7 && lista_ultimo(lista) == (void*)4, "La lista se encuentra integra al añadir secuencialmente");
  pa2m_afirmar(lista_elemento_en_posicion(lista, 12) == NULL, "El elemento en una posición inexistente es NULL");
  pa2m_afirmar(lista_borrar_de_posicion(lista, 12) == EXITO, "Si quiero borrar de una posición inexistente me borra el último.");
  lista_destruir(lista);
}

//Prueba funciones de lista añadiendo y sacando cosas de forma aleatoria
void probar_insertar_elementos_aleatorio(){
  lista_t* lista = lista_crear();
  for(size_t i=0;i<10;i++)
  {
    lista_insertar(lista, (void*)i);
  }
  lista_insertar_en_posicion(lista, (void*)99, 0);
  pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == (void*)99, "Inserto un elemento en la posicion inicial de una lista no vacia");
  int resultado = lista_insertar_en_posicion(lista, (void*)99, 3);
  pa2m_afirmar(resultado == EXITO && lista_elementos(lista) == 12, "Inserto un elemento en una posicion aleatoria");
  void* elemento = lista_elemento_en_posicion(lista, 3);
  pa2m_afirmar(elemento == (void*)99, "Los elementos son correctos al añadir aleatoriamente");
  pa2m_afirmar(lista_primero(lista) == (void*)99 && lista_ultimo(lista) == (void*)9, "La lista se encuentra integra al añadir aleatoriamente");
  lista_destruir(lista);
}

int main(){
  pa2m_nuevo_grupo("Creación y funcionamiento de lista vacia");
  probar_lista_vacia();
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
