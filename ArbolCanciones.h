#ifndef ARBOLCANCIONES_H_INCLUDED
#define ARBOLCANCIONES_H_INCLUDED
#include "listaCanciones.h"

typedef struct
{
    stCancion c;
    struct nodoArbolCancion * izq;
    struct nodoArbolCancion * der;
} nodoArbolCancion;

nodoArbolCancion * inicArbol();
nodoArbolCancion * crearNodoArbol(stCancion dato);
nodoArbolCancion * insertar(nodoArbolCancion * arbol, nodoArbolCancion *nuevoNodo);
void preorder(nodoArbolCancion * arbol);
void inorder(nodoArbolCancion * arbol);
void postorder(nodoArbolCancion * arbol);
nodoArbolCancion * buscar(nodoArbolCancion * arbol, int id);
nodoArbolCancion * buscarTitulo(nodoArbolCancion * arbol, char titulo[30]);
void llenar_Array_Aleatorio(int arrayRand[], int validos);
int ContarRegistrosArchCanciones();
nodoArbolCancion * Pasar_Archivo_Arbol(nodoArbolCancion *arbol, int validos);
void VerIDyTituloInorden(nodoArbolCancion *arbol);
stCancion Cargar_Una_Cancion(nodoArbolCancion *arbol);
void alta_Cancion(nodoArbolCancion **arbol);
nodoArbolCancion * EliminarNodoArbol(nodoArbolCancion * arbol, int id);
nodoArbolCancion * NMI(nodoArbolCancion * arbol);
nodoArbolCancion * NMD(nodoArbolCancion * arbol);
void modificar_Cancion(nodoArbolCancion *arbol);
int Pasar_Archivo_ArregloCanciones(stCancion **ArrCanciones);
void consultaYMuestraCancion(nodoArbolCancion *arbol);
#endif // ARBOLCANCIONES_H_INCLUDED
