#include "listaCanciones.h"
#include <stdio.h>
#include <stdlib.h>

nodoListaCancion * inicLista()
{
    return NULL;
}

nodoListaCancion *crearNodoLista(stCancion dato)
{
    nodoListaCancion *aux = (nodoListaCancion *)malloc(sizeof(nodoListaCancion));
    aux->c = dato;
    aux->sig = NULL;
    return aux;
}

nodoListaCancion *agregarAlPrincipio(nodoListaCancion *lista, nodoListaCancion *nuevoNodo)
{
    if (lista==NULL)
    {
        lista = nuevoNodo;
    }
    else
    {
        nuevoNodo->sig = lista;
        lista = nuevoNodo;
    }
    return lista;
}

nodoListaCancion * buscarUltimo(nodoListaCancion *lista) {
   nodoListaCancion * seg = lista;
   if(seg != NULL)
      while(seg->sig != NULL) {
         seg = seg->sig;
      }
    return seg;
 }

nodoListaCancion *agregarAlFinal(nodoListaCancion *lista, nodoListaCancion *nuevoNodo)
{
     if(lista == NULL) {
      lista = nuevoNodo;
   } else {
      nodoListaCancion * ultimo = buscarUltimo(lista);
      ultimo->sig = nuevoNodo;
   }
   return lista;
}

nodoListaCancion * agregarEnOrdenPorNombreDeCancion(nodoListaCancion * lista, nodoListaCancion * nuevoNodo)
{
   if(lista == NULL) {
      lista = nuevoNodo;
   }else {
      if(strcmp(nuevoNodo->c.titulo,lista->c.titulo)<0){
         lista = agregarAlPrincipio(lista, nuevoNodo);
      }
      else
        {
         nodoListaCancion * ante = lista;
         nodoListaCancion * seg = lista->sig;
         while((seg != NULL) &&(strcmp(nuevoNodo->c.titulo,seg->c.titulo)>0))
        {
            ante = seg;
            seg = seg->sig;
         }

         nuevoNodo->sig = seg;
         ante->sig = nuevoNodo;
      }
   }
   return lista;
}

nodoListaCancion * borrarNodoPorIdCancion(nodoListaCancion *lista, int id)
{
    nodoListaCancion * seg;
    nodoListaCancion * ante;
   if((lista != NULL) && (id==lista->c.idCancion))
    {
      nodoListaCancion * aux = lista;
      lista = lista->sig;
      free(aux);
   }
   else
   {
      seg = lista;
      while((seg != NULL) && (id!=lista->c.idCancion))
      {
         ante = seg;
         seg = seg->sig;
      }
      if(seg!=NULL)
      {
         ante->sig = seg->sig;
         free(seg);
      }
   }
   return lista;
}
void MostrarUnaCancion(stCancion cancion)
{
   printf("\n ID Cancion...%d", cancion.idCancion);
   printf("\n Titulo...%s", cancion.titulo);
   printf("\n Artista...%s", cancion.artista);
   printf ("\n Duracion...%d", cancion.duracion);
   printf("\n Album... %s", cancion.album);
   printf("\n Genero...%s", cancion.genero);
   printf("\n Comentario... %s", cancion.comentario);
   printf("\n Eliminado...%d",cancion.eliminado);
   printf("\n =======================");
}
void mostrarLista(nodoListaCancion *lista)
{

    if(lista!=NULL)
    {
        MostrarUnaCancion(lista->c);
        mostrarLista(lista->sig);
    }

}
int contar_Validos(nodoListaCancion *lista, int validos)
{

    if(lista!=NULL)
    {

        validos = contar_Validos(lista->sig, validos+1);
    }
    return validos;
}






