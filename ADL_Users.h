#ifndef ADL_USERS_H_INCLUDED
#define ADL_USERS_H_INCLUDED
#include "listaCanciones.h"
#include "ArbolCanciones.h"
#define archUser "usuarios.dat"
#define archCanciones "canciones.dat"
#define archPlaylist "playlist.dat"
typedef struct
{
    int idUsuario;
    char nombreUsuario[30];
    char pass[20];
    int anioNacimiento;
    char genero;
    char pais[20];
    int rol;
    int eliminado;   // indica 1 o 0 si el cliente fue eliminado
} stUsuario;

typedef struct
{
    stUsuario usr;
    nodoListaCancion * listaCanciones;
} stCelda;

int agregarUsuario(stCelda **ArrUsers, int validos, stCelda nueva);
int buscarUsuario(stCelda *a, int validos, int id);
int buscarUsuarioNombre(stCelda *a, int validos, char Username[30]);
void MostrarUnUsuario(stUsuario user);
void mostrarUsuarios(stCelda *arrUsers, int validos);
int Val_users_Arch();
void pasar_Archivo_arreglo(stCelda **ArregloDinUsers);
int validar_Usuario(stCelda *arregloUser, char nombreUser[30], int validos);
stUsuario cargar_Un_Usuario(stCelda *arregloUser, int validos);
int altaDeUser(stCelda *ArregloUser, int validos);
int loginUser(stCelda *ArrUsers,int validos, nodoArbolCancion *arbol);
int pedirID();
void Modificar_Arch(stUsuario user);
void bajadeUser(stCelda **ArrUsers, int *validos);
void ModificaciondeUser(stCelda *ArrUsers, int validos);
int buscarMenorUser(int pos, int dimension,stCelda *ArrUsers);
void OrdenarYMostrarUser(stCelda *ArrUsers, int validos);
void consulta_User(stCelda *ArrUsers, int validos);


#endif // ADL_USERS_H_INCLUDED
