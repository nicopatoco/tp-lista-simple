#ifndef PILA_H_INCLUDED
#define PILA_H_INCLUDED

#include <stdio.h>
#include <malloc.h>

typedef struct
{
    int dato;
    struct Pila *sig;
}Pila;

/*Al realizar la Pila con listas, tuve que hacer algunas funciones diferentes que
   en la pila que habitualmente usamos. Como es desapilar que borra un nodo y no devuelve el dato.
   O las funciones que retornan Pila. */

Pila *inicpila(Pila *p);
Pila *apilar(Pila *p, int dato);
Pila *agregarPila(Pila *p, Pila *nuevoNodo);
Pila *desapilar(Pila *p);
int tope(Pila *p);
int pilavacia(Pila *p);
Pila *leer(Pila *p);
void mostrar(Pila *p);

#endif // PILA_H_INCLUDED
