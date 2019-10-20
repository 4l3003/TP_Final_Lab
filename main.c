#include <stdio.h>
#include <stdlib.h>
#include "usuario.h"
#include "gotoxy.h"
int main()
{
    menu_Ingreso();
}


void menu_Ingreso()
{
    gotoxy(50,1);printf("================");
    gotoxy(50,2);printf("MENU DE INGRESO");
    gotoxy(50,3);printf("================");

    gotoxy(25,8);printf("INGRESAR COMO ADMINISTRADOR");
    gotoxy(25,10);printf("INGRESAR COMO USUARIO");
    gotoxy(25,12);printf("REGISTRAR UN USUARIO");
    int x=20, y=8;
    char c;
    hidecursor(0);
    gotoxy(x,y);printf(">>>");
    y=y+2;
    do
    {
        c = getch();
        switch(c)
       {
            case 72: ///arriba
                gotoxy(x,y-2);printf("   ");
                gotoxy(x,y);printf(">>>");
                 y=y-2;
                break;
            case 80: ///abajo
                gotoxy(x,y-2);printf("   ");
                gotoxy(x,y);printf(">>>");
                y=y+2;
                break;
            case 13:
                if(y==8)
                {
                    ///ingresar administrador
                }else if(y==10)
                {
                    ///ingresar user
                }else
                {
                    ///registrar user
                }
                break;
       }
    }while(c!=27);

}
