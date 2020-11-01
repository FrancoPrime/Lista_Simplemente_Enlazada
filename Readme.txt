Lista Simplemente Enlazada

El proyecto consiste en la implementación de una lista compuesta por nodos. Los mismos apuntarán unicamente al nodo siguiente. Además se creara tanto un iterador interno como uno externo. Finalmente se incluirán pruebas para demostrar el correcto funcionamiento de la implementación.

Para compilar el programa se utilizará la linea
make lista_se

Para ejecutar el programa podrá utilizarse:
make valgrind
para compilar y ejecutar las pruebas con valgrind.

O bien:
./lista_se
Para ejecutar las pruebas sin verificar perdidas de memoria.

La implementación mantiene funciones que por su nombre dan a entender que es una lista, tales como:
-lista_borrar_de_posicion
-lista_elemento_en_posicion
-lista_insertar_en_posicion
Funciones que por su nombre parecen ser de una pila:
-lista_apilar
-lista_desapilar
-lista_tope
Y funciones que parecen ser de una cola
-lista_encolar
-lista_desencolar
-lista_primero

Esto se debe a que esta lista puede ser usada(en algunos casos limitando las funciones) como cualquiera de estos TDAs
