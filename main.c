#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#include "gotoxy.h"
#include "ADL_Users.h"
#include "CargarArchivoRandom.h"
#include "ArbolCanciones.h"

int main()
{
    system("COLOR 70");
    hidecursor(0);

    srand(getpid());
    int Users_validos = Val_users_Arch(), x=20, y=10, idUser=0;
    stCelda *ArrUsuarios = (stCelda *)malloc(Users_validos*sizeof(stCelda));
    pasar_Archivo_arreglo(&ArrUsuarios);
    int validosArchCanciones = ContarRegistrosArchCanciones();
    nodoArbolCancion *arbolCanciones = Pasar_Archivo_Arbol(arbolCanciones,validosArchCanciones);
    pasarDeArchivoPlaylistToADL(&ArrUsuarios,Users_validos,arbolCanciones);
    //inorder(arbolCanciones);

    inorder(arbolCanciones);
    char c;
   // mostrarUsuarios(ArrUsuarios,Users_validos);
    do
    {

        gotoxy(x,y);printf(">>>");
        gotoxy(50,1);printf("================");
        gotoxy(50,2);printf("MENU DE INGRESO");
        gotoxy(50,3);printf("================");
        gotoxy(25,10);printf("INGRESAR AL SISTEMA");
        gotoxy(25,12);printf("REGISTRAR UN USUARIO");
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
                    idUser = loginUser(ArrUsuarios,Users_validos,arbolCanciones);
                    system("cls");
                    ///ingresar user
                }else
                {
                    Users_validos = altaDeUser(ArrUsuarios,Users_validos);
                    system("cls");
                    ///registrar user
                }
                break;
       }
    }while(c!=27);

}







