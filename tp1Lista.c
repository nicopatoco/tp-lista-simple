#include <stdlib.h>
#include <stdio.h>
#include "pila.c"


typedef struct{
   int dato;
   struct Nodo *sig;
}Nodo;

Nodo *inicLista(){
   return NULL;
}

void cargarArchivo(char archivoNumeros[]){
   //garga un archivo.
   char control;
   int num;
   printf("Quiere cargar algun dato(s)?: ");
   fflush(stdin);
   scanf("%c",&control);
   printf("\n");
   FILE *archivo;
   archivo=fopen("archivoNumeros","a+b");
   if(archivo!=NULL){
      while(control=='s'){
         printf("\nIngrese un numero: \n");
         fflush(stdin);
         scanf("%d",&num);
         fwrite(&num,sizeof(int),1,archivo);
         printf("Quiere seguir cargando(s)?: ");
         fflush(stdin);
         scanf("%c",&control);
      }
      fclose(archivo);
   }
}

int dimensionArchivo(char archivoNumeros[]){
   //retorna la cantidad de datos cargados en un archivo de integers.
   FILE *archivo;
   int dim=0;
   archivo=fopen("archivoNumeros","rb");
   if(archivo!=NULL){
      fseek(archivo,0,SEEK_END);
      dim=ftell(archivo)/sizeof(int);//Chequeo validos del archivo.
      fclose(archivo);
   }
   return dim;
}

Nodo *crearNodo(int dato){
   Nodo *aux=(Nodo*)malloc(sizeof(Nodo));
   aux->dato=dato;
   aux->sig=NULL;
   return aux;
}

int archivoDato(char archivoNumeros[],int pos){
   FILE *archivo;
   int num=-1;
   int dim=dimensionArchivo(archivoNumeros);
   if (pos<dim){
      archivo=fopen("archivoNumeros","rb");
      if(archivo!=NULL){
         fseek(archivo,pos*sizeof(int),SEEK_SET);
         fread(&num,sizeof(int),1,archivo);
         fclose(archivo);
      }
   }
   return num;
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

Nodo *cargarListaArchivo(Nodo *lista,char archivoNumeros[]){
   int dim=dimensionArchivo(archivoNumeros);
   int i=0;
   int dato;
   while(i<dim){
      dato=archivoDato(archivoNumeros,i);
      Nodo *nuevoNodo = crearNodo(dato);
      lista=agregarPrincipio(lista,nuevoNodo);
      i++;
   }
   return lista;
}

void mostrarLista(Nodo *cursor){
   if(cursor!=NULL){
      printf("Dato:%d\n",cursor->dato);
      mostrarLista(cursor->sig);
   }
}

Nodo *agregarOrdenado(Nodo *lista,Nodo *nuevoNodo){
   if(lista == NULL) {//si esta vacia.
      lista = nuevoNodo;
   } else {
      if(nuevoNodo->dato < lista->dato){ //si va al principio
         lista = agregarPrincipio(lista, nuevoNodo);
      }else {
         // busco el lugar en donde insertar el nuevo elemento.
         // necesito mantener la dirección de memoria del nodo anterior
         // al nodo que tiene un nombre mayor al del nuevo nodo.
         Nodo * ante = lista;
         Nodo * cursor = lista->sig;
         while((cursor != NULL) && (nuevoNodo->dato >= lista->dato)) {
            ante = cursor;
            cursor = cursor->sig;
         }
         // inserto el nuevo nodo en el lugar indicado.
         nuevoNodo->sig = cursor;
         ante->sig = nuevoNodo;
      }
   }
   return lista;
}

Nodo *cargarListaArchivoOrdenados(Nodo *lista,char archivoNumeros[]){
   int dim=dimensionArchivo(archivoNumeros);
   int i=0;
   int dato;
   while(i<dim){
      dato=archivoDato(archivoNumeros,i);
      Nodo *nuevoNodo = crearNodo(dato);
      lista=agregarOrdenado(lista,nuevoNodo);
      i++;
   }
   return lista;
}

int buscarElemento(Nodo *cursor,int dato){
   int existe=0;
   if(cursor!=NULL){
      if(cursor->dato==dato){
         existe=1;
      }else{
         existe=buscarElemento(cursor->sig,dato);
      }
   }
   return existe;
}

Nodo *intercalarDosListas(Nodo *cursor1,Nodo *cursor2,Nodo *cursor3,Nodo *ant3,Nodo *listaNueva){
   if((cursor1!=NULL)&&(cursor2!=NULL)){
      if(cursor1->dato < cursor2->dato){
         if(listaNueva==NULL){
            listaNueva=cursor1;
            ant3=cursor1;
         }else{
            cursor3=cursor1;
            ant3->sig=cursor3;//Redirecciona el nodo
            ant3=cursor3;//avanza
         }
         intercalarDosListas(cursor1->sig,cursor2,cursor3,ant3,listaNueva);
      }else{
         if(listaNueva==NULL){
            listaNueva=cursor2;
            ant3=cursor2;
         }else{
            cursor3=cursor2;
            ant3->sig=cursor3;//Redirecciona el nodo
            ant3=cursor3;//avanza
         }
         intercalarDosListas(cursor1,cursor2->sig,cursor3,ant3,listaNueva);
      }
   }else{
      if(cursor1!=NULL){
         if(listaNueva==NULL){
            listaNueva=cursor1;
            ant3=cursor1;
         }else{
            cursor3=cursor1;
            ant3->sig=cursor3;//Redirecciona el nodo
            ant3=cursor3;//avanza
         }
         intercalarDosListas(cursor1->sig,cursor2,cursor3,ant3,listaNueva);
      }
      if (cursor2!=NULL) {
         if(listaNueva==NULL){
            listaNueva=cursor2;
            ant3=cursor2;
         }else{
            cursor3=cursor2;
            ant3->sig=cursor3;//Redirecciona el nodo
            ant3=cursor3;//avanza
         }
         intercalarDosListas(cursor1,cursor2->sig,cursor3,ant3,listaNueva);
      }
   }
   return listaNueva;
}

Nodo *invertirLista(Nodo *lista,Nodo *cursor,Nodo *aux,int i){//esta funcion invierte la lista con recursion sin crear nodos nuevos.
   if(cursor!=NULL && cursor->sig!=NULL){
      if(i==0){ //Le paso un int con valor cero, para poner en null el primer elemento que va a ser el ultimo.
         aux=inicpila(aux);
         i++;
         lista=invertirLista(lista,cursor,aux,i);
      }else{
         aux=cursor;
         cursor=cursor->sig;
         lista=invertirLista(lista,cursor,aux,i);// asigno anterior del cursor y el cursor.
      }
      cursor->sig=aux;
   }else{
      if(cursor!=NULL){//Cuando llego al ultimo nodo, lo convierto en el primero.
         lista=cursor;
      }
   }
   return lista;
}

int main(int argc, char const *argv[]) {
   int opcion,elem,i;
   int repite=1;
   char archivoNumeros[]={"archivoNumeros.dat"};
   Nodo *lista,*cursor,*aux;
   Nodo *lista1,*lista2; // las listas que van a ser entrelazadas para el punto 4
   Nodo *listaNueva,*cursor3,*ant3;// las variables corresponden al punto 4.
   lista=inicLista();
   cursor=inicLista();
   lista1=inicLista(lista1);
   lista2=inicLista(lista2);
   listaNueva=inicLista(listaNueva);
   Pila *p;
   do{
      printf("\t\tQUE EJERCICIO DESEA REALIZAR. Salir(0)\n\n\n");
      printf("1. Hacer un programa que lea de un archivo los datos y los cargue en una lista.\n");
      printf("2. Hacer un programa que lea de un archivo los datos y los inserte en una lista en forma ordenada.\n");
      printf("3. Hacer una funcion que retorne un 1 (uno) o 0 (cero) si existe un determinado elemento en una lista dada.\n");
      printf("4. Hacer una funcion que intercale en orden los elementos de dos listas ordenadas generando una nueva lista.Se deben redireccionar los punteros, no se deben crear nuevos nodos.\n");
      printf("5. Codificar el TDA Pila con las funciones necesarias, implementada con una lista enlazada (Similar al ejercicio hecho con arreglo).\n");
      printf("6. Invertir los elementos de una lista redireccionando solamente los punteros\n\n");
      printf("Opcion: ");
      fflush(stdin);
      scanf("%d",&opcion);
      switch (opcion) {
         case 0:
            repite=0;
            break;
         case 1:
            system("cls");
            //printf("\n\nCARGAR ARCHIVO\n");
            //cargarArchivo(archivoNumeros);
            printf("\n\nCARGAR LISTA CON ARCHIVO\n");
            lista=cargarListaArchivo(lista,archivoNumeros);
            cursor=lista;
            mostrarLista(cursor);
            system("pause");
            system("cls");
         break;
         case 2:
            system("cls");
            //printf("\n\nCARGAR ARCHIVO\n");
            //cargarArchivo(archivoNumeros);
            printf("\n\nCARGAR LISTA CON ARCHIVO ORDENADAMENTE\n");
            lista=cargarListaArchivoOrdenados(lista,archivoNumeros);
            cursor=lista;
            mostrarLista(cursor);
            system("pause");
            system("cls");
         break;
         case 3:
            system("cls");
            printf("\t\tEXISTE TU ELEMENTO?\n\n\n");
            printf("Ingrese elemento a buscar de tipo integer: ");
            fflush(stdin);
            scanf("%d",&elem);
            lista=cargarListaArchivoOrdenados(lista,archivoNumeros);
            cursor=lista;
            mostrarLista(cursor);
            if(buscarElemento(cursor,elem)){
               printf("EXISTE\n");
            }else{
               printf("No EXISTE\n");
            }
            system("pause");
            system("cls");
         break;
         case 4:
            system("cls");
            printf("\n\nCARGAR LISTA CON ARCHIVO ORDENADAMENTE\n");
            cursor3=listaNueva;
            ant3=listaNueva;
            lista1=cargarListaArchivoOrdenados(lista1,archivoNumeros);
            lista2=cargarListaArchivoOrdenados(lista2,archivoNumeros);
            printf("Datos de lista 1\n\n");
            cursor=lista1;
            mostrarLista(cursor);
            printf("Datos de lista 2\n\n");
            cursor=lista2;
            mostrarLista(cursor);
            listaNueva=intercalarDosListas(lista1,lista2,cursor3,ant3,listaNueva);
            printf("Datos de lista enlazada 3\n\n");
            cursor=listaNueva;
            mostrarLista(cursor);
            system("pause");
            system("cls");
         break;
         case 5:
            system("cls");
            p=inicpila(p);
            i=0;
            while(i<5){
               p=leer(p);
               i++;
            }
            mostrar(p);
            printf("El tope de la pila es:%d\n\n",tope(p));
            i=0;
            printf("Vamos a desapilar hasta vaciarla\n");
            while(!pilavacia(p)){
               p=desapilar(p);
               i++;
            }
            printf("Desapilamos:%d datos\n",i);
            system("pause");
            system("cls");
         break;
         case 6:
            system("cls");
            lista=cargarListaArchivoOrdenados(lista,archivoNumeros);
            printf("LISTA NORMAL\n");
            cursor=lista;
            mostrarLista(cursor);
            cursor=lista;
            lista=invertirLista(lista,cursor,aux,0);
            printf("\nLISTA INVERTIDA\n");
            cursor=lista;
            mostrarLista(cursor);
            printf("\n");
            system("pause");
            system("cls");
         break;
      }
   }while (repite==1);
   return 0;
}
