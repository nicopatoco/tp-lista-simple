#include "pila.h"

Pila *inicpila(Pila *p){//Inicializa la pila.
   return NULL;
}

Pila *agregarPila(Pila *p, Pila *nuevoNodo){//Agrega el nodo al principio de la pila.
   if(p==NULL){
      p=nuevoNodo;
   }else{
      nuevoNodo->sig=p;
      p=nuevoNodo;
   }
   return p;
}

Pila *apilar(Pila *p,int dato){//dado un dato integer, genera un nodo y lo agrega a la lista llamando a agregarPila.
   Pila *q=(Pila*)malloc(sizeof(Pila));
   q->dato=dato;
   q->sig=NULL;
   p=agregarPila(p,q);
   return p;
}

void mostrar(Pila *p){//muestra los datos de la lista, no usa recursion porque creo el nodo aux (cursor) dentro de la funcion.
   Pila *aux=p;
   printf("\t\t\tMOSTRAR PILA\n\n");
   while(aux!=NULL){
      printf("Dato:%d\n",aux->dato);
      aux=aux->sig;
   }
   printf("\n");
   free(aux);
}

Pila *desapilar(Pila *p){//elimina el primer nodo de la lista, anteriormente avanza un nodo.
   if(p!=NULL){
      Pila *aux=p;
      p=p->sig;
      free(aux);
   }else{
      printf("ERROR, PILA VACIA.\n");
   }
   return p;
}

int tope(Pila *p){//devulve el dato del tope.
   int tope;
   if(p!=NULL){
      tope=p->dato;
   }else{
      printf("ERROR, PILA VACIA.\n");
   }
   return tope;
}

int pilavacia(Pila *p){//retorna 1 si la pila esta vacia 0 sino.
   int flag;
   if(p==NULL){
      flag=1;
   }else{
      flag=0;
   }
   return flag;
}

Pila *leer(Pila *p){//Pide un dato integer al usuario y lo carga en la pila con la funcion apilar.
   int aux=0;
   printf("Ingrese un valor entero: ");
   fflush(stdin);
   scanf("%d",&aux);
   p=apilar(p,aux);
   return p;
}
