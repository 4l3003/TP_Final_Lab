#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED
#include "ADL_Users.h"
#include "ArbolCanciones.h"
#include "playlist.h"


void menu_User(stCelda *ArrUsers,int idUser, int validos, nodoArbolCancion *arbol);
void menu_Admin(stCelda *ArrUsers,int idUser, int validos, nodoArbolCancion *arbol);
void Menu_escuchar_Cancion(stCelda *ArrUsers,nodoArbolCancion *arbol, int posUser);
int Escuchar_Una_Cancion();
void menuVerPlaylist(nodoListaCancion *lista);
void menu_GestionUsuarios(stCelda *ArrUsers,int idUser, int validos, nodoArbolCancion *arbol);
void SeleccionarDatoModificacion(stCelda **ArrUsers, int pos, int validos);
void menu_GestionCanciones(nodoArbolCancion *arbol);
void SeleccionarDatoModificacionCancion(nodoArbolCancion **arbol);
void Menu_Listado_Canciones();

#endif // MENUS_H_INCLUDED
