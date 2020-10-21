#ifndef LISTACANCIONES_H_INCLUDED
#define LISTACANCIONES_H_INCLUDED

typedef struct {
   int idCancion;
   char titulo[30];
   char artista[20];
   int duracion;
   char album[20];
   int anio;
   char genero[20];
   char comentario[100];
   int eliminado;  // indica 1 o 0 si la canción fue eliminada
} stCancion;

typedef struct
{
    stCancion c;
    struct nodoListaCancion * sig;
} nodoListaCancion;

nodoListaCancion * inicLista();
nodoListaCancion * crearNodoLista(stCancion dato);
nodoListaCancion * agregarAlPrincipio(nodoListaCancion *lista, nodoListaCancion *nuevoNodo);
nodoListaCancion * buscarUltimo(nodoListaCancion *lista);
nodoListaCancion * agregarAlFinal(nodoListaCancion *lista, nodoListaCancion *nuevoNodo);
nodoListaCancion * agregarEnOrdenPorNombreDeCancion(nodoListaCancion * lista, nodoListaCancion * nuevoNodo);
nodoListaCancion * borrarNodoPorIdCancion();
void MostrarUnaCancion(stCancion cancion);
void mostrarLista(); // modularizar
int contar_Validos(nodoListaCancion *lista, int validos);


#endif // LISTACANCIONES_H_INCLUDED
