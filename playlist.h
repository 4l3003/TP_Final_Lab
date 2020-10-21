#ifndef PLAYLIST_H_INCLUDED
#define PLAYLIST_H_INCLUDED
#include "ArbolCanciones.h"
#include "ADL_Users.h"

typedef struct
{
    int idPlaylist;
    int idUsuario;
    int idCancion;
} stPlaylist;

void mostrar_Arch_Playlist();
void Agregar_Arch_Playlist(int idCancion, int idUser);
void Agregar_A_Playlist(stCelda **ArrUsers,nodoArbolCancion *arbol, int posUser, int id);
void pasarDeArchivoPlaylistToADL(stCelda **ArrUsers, int validosUser, nodoArbolCancion *arbol);
void pasarADLtoArrPlaylist(nodoListaCancion *lista, stCancion **ArrPlaylist, int validos);
void ordenar_por_seleccion(stCancion *ArrPlaylist,int validos);
int buscarMenor(int pos, int dimension,stCancion *ArrPlaylist);
void insertarInsercion(stCancion *ArrPlaylist, int u, stCancion dato);
void ordenar_por_Insercion(stCancion *ArrPlaylist, int validos);
void mostrar_Arreglo_Playlist(stCancion *ArrPlaylist, int validos);
void mostrarCancionesRecomendadas(stCelda *ArrUsers, stCancion **ArrRandom, int posUser, int validos);
#endif // PLAYLIST_H_INCLUDED
