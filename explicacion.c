#include <stdlib.h>
#include <stdio.h>
#include "string.h"

typedef struct{
   char nombre[30];
   int edad;
   struct Nodo *sig;
}Nodo;

Nodo *inicLista(){
   return NULL;
}

Nodo * crearNodo(char nombre[], int edad){
   //crea un puntero de tipo nodo
   Nodo * aux = (Nodo*) malloc(sizeof(Nodo));
   //asigna valores a sus campos de información
   aux->edad = edad;
   strcpy(aux->nombre, nombre);
   //asigna valor NULL al campo que contiene la dir de memoria del ste. nodo
   aux->sig = NULL;
   //retorna la dirección de memoria del nuevo nodo, que deberá ser
   //asignada a una variable de tipo “puntero a nodo”.
   return aux;
}

Nodo *agregarPrincipio(Nodo *lista,Nodo *nuevoNodo){
   if(lista==NULL){
      lista=nuevoNodo;
   }else{
      nuevoNodo->sig=lista;
      lista=nuevoNodo;
   }
   return lista;
}

Nodo * buscarUltimo(Nodo * lista){
   Nodo * cursor = lista;
   if(cursor != NULL)
   while(cursor->sig != NULL){
      cursor = cursor->sig;
   }
   return cursor;
}

// free(cursor);

Nodo * borrarNodo(char nombre[20], Nodo * lista) {
   Nodo * seg;
   Nodo * ante;
   //apunta al nodo anterior que seg.
   if((lista != NULL) && (strcmp(nombre, lista->nombre)==0 )) {
      Nodo *aux = lista;
      lista=lista->sig;//salteo el primer nodo.
      free(aux); //elimino el primer nodo.
   } else {
      seg = lista;
      while((seg != NULL) && (strcmp(nombre, seg->nombre)!=0 )) {
         ante = seg;//adelanto una posición la variable ante.
         seg = seg->sig; //avanzo al siguiente nodo.
      }
      if(seg!=NULL) {
         ante->sig = seg->sig;//salteo el nodo que quiero eliminar.
         free(seg); //elimino el nodo.
      }
   }
   return lista;
}
int main(int argc, char const *argv[]) {
   Nodo *lista;
   lista=inicLista();
   return 0;
}
