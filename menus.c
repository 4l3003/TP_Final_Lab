#include "menus.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "gotoxy.h"


void menu_User(stCelda *ArrUsers,int idUser, int validos, nodoArbolCancion *arbol)
{

    int x=20, y=8;
    char c;
    do
    {

        gotoxy(x,y);printf(">>>");
        gotoxy(50,1);printf("================");
        gotoxy(50,2);printf("MENU PRINCIPAL (USER)");
        gotoxy(50,3);printf("================");
        gotoxy(25,8);printf("VER PERFIL");
        gotoxy(25,10);printf("MOSTRAR PLAYLIST");
        gotoxy(25,12);printf("ESCUCHAR CANCION");
        gotoxy(25,14);printf("CANCIONES RECOMENDADAS");

        int pos = buscarUsuario(ArrUsers,validos,idUser);
        c = getch();
        switch(c)
       {

            case 72: ///arriba
                if(y==8)
                {
                   gotoxy(x,y-2);printf("   ");
                }
                else
                {
                     y=y-2;
                     gotoxy(x,y+2);printf("   ");
                     gotoxy(x,y);printf(">>>");

                }
                break;
            case 80: ///abajo
                if(y==14)
                {
                     gotoxy(x,y+2);printf("   ");
                }
                else
                {
                  y=y+2;
                  gotoxy(x,y-2);printf("   ");
                  gotoxy(x,y);printf(">>>");

                }
                break;
            case 13:
                system("cls");
                if(y==8)
                {

                    ///VER PERFIL
                    MostrarUnUsuario(ArrUsers[pos].usr);
                    gotoxy(20,17);printf("Presione Cualquier tecla para volver al menu... \n");
                    getch();
                    system("cls");

                }else if(y==10)
                {

                    menuVerPlaylist(ArrUsers[pos].listaCanciones);
                    system("cls");
                    ///MOSTRAR PLAYLIST
                }else if(y==12)
                {
                    ///ESCUCHAR CANCION
                    Menu_escuchar_Cancion(ArrUsers,arbol,pos);
                    system("cls");
                }
                else
                {
                    //mostrarCancionesRecomendadas(Arrusers,pos,validos);
                    ///CANCIONES RECOMENDADAS
                }
                break;
       }
    }while(c!=27);
}

void menu_Admin(stCelda *ArrUsers,int idUser, int validos, nodoArbolCancion *arbol)
{
    int x=20, y=8;
    char c;
    do
    {
        gotoxy(x,y);printf(">>>");
        gotoxy(50,1);printf("================");
        gotoxy(50,2);printf("MENU PRINCIPAL (ADMIN)");
        gotoxy(50,3);printf("================");
        gotoxy(25,8);printf("GESTIONAR USUARIOS");
        gotoxy(25,10);printf("GESTIONAR CANCIONES");
        c = getch();
        switch(c)
       {
            case 72: ///arriba
                if(y==8)
                {
                   gotoxy(x,y-2);printf("   ");
                }
                else
                {
                     y=y-2;
                     gotoxy(x,y+2);printf("   ");
                     gotoxy(x,y);printf(">>>");

                }
                break;
            case 80: ///abajo
                if(y==10)
                {
                     gotoxy(x,y+2);printf("   ");
                }
                else
                {
                  y=y+2;
                  gotoxy(x,y-2);printf("   ");
                  gotoxy(x,y);printf(">>>");

                }
                break;
            case 13:
                system("cls");
                if(y==8)
                {
                    ///gestionar users
                    menu_GestionUsuarios(ArrUsers,idUser,validos,arbol);
                    system("cls");
                }else
                {
                    ///gestionar canciones
                    menu_GestionCanciones(arbol);
                }
        }
    }while(c!=27);
}
int Escuchar_Una_Cancion()
{
    int id=0;
    gotoxy(50,1);printf("================");
    gotoxy(50,2);printf("ESCUCHAR CANCION");
    gotoxy(50,3);printf("================");
    gotoxy(30,10);printf("Ingrese ID de la cancion que desea escuchar...");
    scanf("%d",&id);
    return id;
}
void Menu_escuchar_Cancion(stCelda *ArrUsers,nodoArbolCancion *arbol, int posUser)
{
    int x=20, y=10;
    char c;
     system("cls");
     do
     {
         gotoxy(x,y);printf(">>>");
         gotoxy(50,1);printf("================");
         gotoxy(50,2);printf("ESCUCHAR CANCION");
         gotoxy(50,3);printf("================");
         gotoxy(5,6);printf("Con las direccionales del teclado, muevase en el menu y elija la opcion correcta");
         gotoxy(25,10);printf("VER LISTA DE CANCIONES");
         gotoxy(25,12);printf("ESCUCHAR UNA CANCION");
         c = getch();
         switch(c)
         {
            case 72: ///arriba
                if(y==10)
                {
                    gotoxy(x,y-2);printf("   ");
                }
                else
                {
                    y=y-2;
                    gotoxy(x,y+2);printf("   ");
                    gotoxy(x,y);printf(">>>");
                }
            break;
            case 80: ///abajo
                if(y==12)
                {
                    gotoxy(x,y+2);printf("   ");
                }
                else
                {
                    y=y+2;
                    gotoxy(x,y-2);printf("   ");
                    gotoxy(x,y);printf(">>>");
                }
            break;
            case 13:
                system("cls");
                if(y==10)
                {
                    ///VER LISTA CANCIONES
                    VerIDyTituloInorden(arbol);
                    gotoxy(5,25);printf("Presione Cualquier Tecla para volver al menu anterior...");
                    getch();
                    system("cls");
                }
                else
                {
                    ///ESCUCHAR CANCION
                    int idCancion = Escuchar_Una_Cancion();
                    nodoArbolCancion *encuentra = buscar(arbol,idCancion);
                    if(encuentra==NULL)
                    {
                        gotoxy(5,25);printf("El id ingresado no existe en el arbol... Por favor vuelva a ingresar!");
                        getch();
                        Menu_escuchar_Cancion(ArrUsers,arbol,posUser);
                    }
                    Agregar_A_Playlist(&ArrUsers,arbol,posUser,idCancion);
                    gotoxy(5,25);printf("La cancion seleccionada se ha agregado al Playlist correctamente!");
                    gotoxy(5,27);printf("Presione Cualquier tecla para volver al menu anterior...");
                    getch();
                    system("cls");

                }
            break;
        }
    }while(c!=27);
}
void menuVerPlaylist(nodoListaCancion *lista)
{

    int x=20, y=10;
    char c;
     system("cls");

      int validos = contar_Validos(lista,0);
      stCancion *ArrPlaylist = (stCancion *)malloc(validos*sizeof(stCancion));
      pasarADLtoArrPlaylist(lista,&ArrPlaylist,validos);
     do
     {
         system("cls");
         gotoxy(x,y);printf(">>>");
         gotoxy(50,1);printf("================");
         gotoxy(50,2);printf("VER MI PLAYLIST");
         gotoxy(50,3);printf("================");
         gotoxy(5,6);printf("Como quiere visualizar su playlist?");
         gotoxy(25,10);printf("ORDENADA POR NOMBRE DE CANCION");
         gotoxy(25,12);printf("ORDENADA POR GENERO");
         c = getch();
         switch(c)
         {
            case 72: ///arriba
                if(y==10)
                {
                    gotoxy(x,y-2);printf("   ");
                }
                else
                {
                    y=y-2;
                    gotoxy(x,y+2);printf("   ");
                    gotoxy(x,y);printf(">>>");
                }
            break;
            case 80: ///abajo
                if(y==12)
                {
                    gotoxy(x,y+2);printf("   ");
                }
                else
                {
                    y=y+2;
                    gotoxy(x,y-2);printf("   ");
                    gotoxy(x,y);printf(">>>");
                }
            break;
            case 13:

                 system("cls");
                if(y==10)
                {
                    ///ordenada x nombre
                     ordenar_por_seleccion(ArrPlaylist,validos);
                     mostrar_Arreglo_Playlist(ArrPlaylist,validos);
                    getch();
                    system("cls");
                }
                else
                {
                    ///ordenada x genero
                    ordenar_por_Insercion(ArrPlaylist,validos);
                    mostrar_Arreglo_Playlist(ArrPlaylist,validos);
                    getch();
                    system("cls");
                }
            break;
        }
    }while(c!=27);
}
void menu_GestionUsuarios(stCelda *ArrUsers,int idUser, int validos, nodoArbolCancion *arbol)
{

    int x=20, y=8;
    char c;
    do
    {
        gotoxy(x,y);printf(">>>");
        gotoxy(50,1);printf("================");
        gotoxy(50,2);printf("GESTIONAR USERS");
        gotoxy(50,3);printf("================");
        gotoxy(25,8);printf("ALTA");
        gotoxy(25,10);printf("BAJA");
        gotoxy(25,12);printf("MODIFICACION");
        gotoxy(25,14);printf("CONSULTA");
        gotoxy(25,16);printf("LISTADOS");
        c = getch();
        switch(c)
       {
            case 72: ///arriba
                if(y==8)
                {
                   gotoxy(x,y-2);printf("   ");
                }
                else
                {
                     y=y-2;
                     gotoxy(x,y+2);printf("   ");
                     gotoxy(x,y);printf(">>>");

                }
                break;
            case 80: ///abajo
                if(y==16)
                {
                     gotoxy(x,y+2);printf("   ");
                }
                else
                {
                  y=y+2;
                  gotoxy(x,y-2);printf("   ");
                  gotoxy(x,y);printf(">>>");

                }
                break;
            case 13:
                system("cls");
                switch(y)
                {
                    case 8:
                        altaDeUser(ArrUsers,validos);
                        system("cls");
                        ///ALTA
                    break;
                    case 10:
                        bajadeUser(&ArrUsers,validos);
                        //mostrarUsuarios(ArrUsers,validos);
                        system("cls");
                        ///BAJA
                    break;
                    case 12:
                         ModificaciondeUser(ArrUsers,validos);
                         system("cls");
                        ///MODIFICACION
                    break;
                    case 14:
                        consulta_User(ArrUsers,validos);
                        system("cls");
                         ///CONSULTA
                    break;
                    case 16:
                        OrdenarYMostrarUser(ArrUsers, validos);
                        system("cls");
                          ///LISTADOS
                    break;
                }
        }
    }while(c!=27);
}
void SeleccionarDatoModificacion(stCelda **ArrUsers, int pos, int validos)
{
     int x=20, y=8;
    char c;
    do
    {
        gotoxy(x,y);printf(">>>");
        gotoxy(50,1);printf("================");
        gotoxy(50,2);printf("MODIFICACION USERS");
        gotoxy(50,3);printf("================");
        c = getch();
        switch(c)
       {
            case 72: ///arriba
                if(y==8)
                {
                   gotoxy(x,y-2);printf("   ");
                }
                else
                {
                     y=y-2;
                     gotoxy(x,y+2);printf("   ");
                     gotoxy(x,y);printf(">>>");

                }
                break;
            case 80: ///abajo
                if(y==16)
                {
                     gotoxy(x,y+2);printf("   ");
                }
                else
                {
                  y=y+2;
                  gotoxy(x,y-2);printf("   ");
                  gotoxy(x,y);printf(">>>");

                }
                break;
            case 13:
                system("cls");
                char aux[30];
                switch(y)
                {
                    case 8:
                        gotoxy(20,19);printf("Ingrese Nuevo Nombre de Usuario...");
                        fflush(stdin);
                        gets(aux);
                        int encuentra = buscarUsuarioNombre((*ArrUsers),validos,aux);
                        if(encuentra==-1)
                        {
                            strcpy((*ArrUsers)[pos].usr.nombreUsuario,aux);
                        }
                        else
                        {
                            gotoxy(20,19);printf("ERROR! el id ingresado corresponde a un user ya registrado :(");
                            getch();
                            system("cls");
                            ModificaciondeUser((*ArrUsers),validos);
                        }
                    break;
                    case 10:
                        gotoxy(20,19);printf("Ingrese Nueva Clave...");
                        fflush(stdin);
                        gets((*ArrUsers)[pos].usr.pass);
                    break;
                    case 12:
                        gotoxy(20,19);printf("Ingrese Nuevo Anio Nac...");
                        fflush(stdin);
                        gets((*ArrUsers)[pos].usr.anioNacimiento);
                    break;
                    case 14:
                         gotoxy(20,19);printf("Ingrese Nuevo Genero (m/f)...");
                         fflush(stdin);
                        scanf("%c", &(*ArrUsers)[pos].usr.genero);
                    break;
                    case 16:
                         gotoxy(20,19);printf("Ingrese Nuevo Pais...");
                         fflush(stdin);
                         gets((*ArrUsers)[pos].usr.pais);
                    break;
                }

                gotoxy(20,10);printf("El dato se Ha modificado con Exito! Presione cualquier tecla para volver atras...");
                Modificar_Arch((*ArrUsers)[pos].usr);
                getch();
                system("cls");

        }
    }while(c!=13);
}
void menu_GestionCanciones(nodoArbolCancion *arbol)
{
     int x=20, y=8;
    char c;
    do
    {
        gotoxy(x,y);printf(">>>");
        gotoxy(50,1);printf("================");
        gotoxy(50,2);printf("GESTIONAR CANCIONES");
        gotoxy(50,3);printf("================");
        gotoxy(25,8);printf("ALTA");
        gotoxy(25,10);printf("BAJA");
        gotoxy(25,12);printf("MODIFICACION");
        gotoxy(25,14);printf("CONSULTA");
        gotoxy(25,16);printf("LISTADOS");
        c = getch();
        switch(c)
       {
            case 72: ///arriba
                if(y==8)
                {
                   gotoxy(x,y-2);printf("   ");
                }
                else
                {
                     y=y-2;
                     gotoxy(x,y+2);printf("   ");
                     gotoxy(x,y);printf(">>>");

                }
                break;
            case 80: ///abajo
                if(y==16)
                {
                     gotoxy(x,y+2);printf("   ");
                }
                else
                {
                  y=y+2;
                  gotoxy(x,y-2);printf("   ");
                  gotoxy(x,y);printf(">>>");

                }
                break;
            case 13:
                switch(y)
                {
                    case 8:
                        alta_Cancion(&arbol);
                        ///ALTA
                    break;
                    case 10:
                        ///BORRAR NODO (MARTIN)
                        inorder(arbol);
                        getch();
                        eliminar_Una_Cancion(&arbol);

                       inorder(arbol);

                        getch();
                    break;
                    case 12:
                        modificar_Cancion(arbol);
                        system("cls");

                        ///MODIFICACION
                    break;
                    case 14:
                         consultaYMuestraCancion(arbol);
                         system("cls");
                         ///CONSULTA
                    break;
                    case 16:
                        Menu_Listado_Canciones();
                        system("cls");
                          ///LISTADOS
                    break;
                }
        }
    }while(c!=27);
    system("cls");
}
void SeleccionarDatoModificacionCancion(nodoArbolCancion **arbol)
{
     int x=20, y=8;
    char c;
    do
    {
        gotoxy(x,y);printf(">>>");
        gotoxy(50,1);printf("================");
        gotoxy(50,2);printf("MODIFICACION CANCION");
        gotoxy(50,3);printf("================");
        c = getch();
        switch(c)
       {
            case 72: ///arriba
                if(y==8)
                {
                   gotoxy(x,y-2);printf("   ");
                }
                else
                {
                     y=y-2;
                     gotoxy(x,y+2);printf("   ");
                     gotoxy(x,y);printf(">>>");

                }
                break;
            case 80: ///abajo
                if(y==20)
                {
                     gotoxy(x,y+2);printf("   ");
                }
                else
                {
                  y=y+2;
                  gotoxy(x,y-2);printf("   ");
                  gotoxy(x,y);printf(">>>");

                }
                break;
            case 13:
                system("cls");
                switch(y)
                {
                    case 8:
                        gotoxy(20,19);printf("Ingrese Nuevo Titulo...");
                        fflush(stdin);
                        gets((*arbol)->c.titulo);
                    break;
                    case 10:
                        gotoxy(20,19);printf("Ingrese Nuevo Artista...");
                        fflush(stdin);
                        gets((*arbol)->c.artista);
                    break;
                    case 12:
                        gotoxy(20,19);printf("Ingrese Nueva Duracion...");
                        fflush(stdin);
                        scanf("%d",&(*arbol)->c.duracion);
                    break;
                    case 14:
                         gotoxy(20,19);printf("Ingrese Nuevo Album...");
                         fflush(stdin);
                         gets((*arbol)->c.album);
                    break;
                    case 16:
                         gotoxy(20,19);printf("Ingrese Nuevo Anio...");
                         fflush(stdin);
                         scanf("%d",&(*arbol)->c.anio);
                    break;
                     case 18:
                         gotoxy(20,19);printf("Ingrese Nuevo Genero...");
                         fflush(stdin);
                         gets((*arbol)->c.genero);
                    break;
                     case 20:
                         gotoxy(20,19);printf("Ingrese Nuevo Comentario...");
                         fflush(stdin);
                         gets((*arbol)->c.comentario);
                    break;
                }

                Modificar_ArchCanciones((*arbol)->c);
                gotoxy(20,10);printf("El dato se Ha modificado con Exito! Presione cualquier tecla para volver atras...");
                getch();
                system("cls");
        }
    }while(c!=13);
}
void Menu_Listado_Canciones()
{
     int x=20, y=10;
     char c;
    system("cls");
      int validos = ContarRegistrosArchCanciones();
      stCancion *ArrCanciones = (stCancion *)malloc(validos*sizeof(stCancion));
      Pasar_Archivo_ArregloCanciones(&ArrCanciones);
     do
     {
         gotoxy(x,y);printf(">>>");
         gotoxy(50,1);printf("================");
         gotoxy(50,2);printf("LISTADO CANCIONES");
         gotoxy(50,3);printf("================");
         gotoxy(5,6);printf("Como quiere visualizar las canciones?");
         gotoxy(25,10);printf("ORDENADA POR NOMBRE DE CANCION");
         gotoxy(25,12);printf("ORDENADA POR GENERO");
         c = getch();
         switch(c)
         {
            case 72: ///arriba
                if(y==10)
                {
                    gotoxy(x,y-2);printf("   ");
                }
                else
                {
                    y=y-2;
                    gotoxy(x,y+2);printf("   ");
                    gotoxy(x,y);printf(">>>");
                }
            break;
            case 80: ///abajo
                if(y==12)
                {
                    gotoxy(x,y+2);printf("   ");
                }
                else
                {
                    y=y+2;
                    gotoxy(x,y-2);printf("   ");
                    gotoxy(x,y);printf(">>>");
                }
            break;
            case 13:

                 system("cls");
                if(y==10)
                {
                    ///ordenada x nombre
                     ordenar_por_seleccion(ArrCanciones,validos);
                     mostrar_Arreglo_Playlist(ArrCanciones,validos);
                    getch();
                    system("cls");
                }
                else
                {
                    ///ordenada x genero
                    ordenar_por_Insercion(ArrCanciones,validos);
                    mostrar_Arreglo_Playlist(ArrCanciones,validos);
                    getch();
                    system("cls");
                }
            break;
        }
    }while(c!=27);
}

