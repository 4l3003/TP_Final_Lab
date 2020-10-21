#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "menus.h"
#define nombre_archivo "usuarios.dat"

stUsuario cargar_Un_Usuario()
{
    stUsuario aux, userArchi;
    printf("\n Ingrese Nombre de Usuario.... ");
    fflush(stdin);
    gets(aux.nombreUsuario);
    userArchi=validar_Usuario(aux.nombreUsuario);
    //printf("validar user: %d", aux.idUsuario);
    if(userArchi.idUsuario==1)
    {

         printf("\n Ingrese contrasena....");
         fflush(stdin);
         gets(aux.pass);
         printf("\n Ingrese Anio nacimiento.... ");
         fflush(stdin);
         scanf("%d",&aux.anioNacimiento);
         printf("\n Ingrese Genero (m/f)....");
         fflush(stdin);
         scanf("%c", &aux.genero);
         printf("\n Ingrese Pais....");
         fflush(stdin);
         gets(aux.pais);

    }
    else
    {
        gotoxy(20,10);printf(" Ese Nombre de Usuario ya esta en uso \n Presione cualquier Tecla para ingresar otro...");
        getch();
        system("cls");
        aux = cargar_Un_Usuario();
    }
    return aux;
}

stUsuario validar_Usuario(char nombreUser[30])
{
    stUsuario aux;
    int flag=0;
    FILE *archi;
    archi = fopen(nombre_archivo, "rb");

    if(archi!=NULL)
    {
        aux.idUsuario=1;
        while(fread(&aux,sizeof(stUsuario),1,archi)>0 && flag==0)
        {
            aux.idUsuario=1;

            if(strcmp(aux.nombreUsuario,nombreUser)==0)
            {
                aux.idUsuario=0;
                flag=1;

            }


        }
        fclose(archi);

    }
    return aux;
}

void altaDeUser()
{
    FILE *archi;
    archi = fopen(nombre_archivo, "ab");
    if(archi!=NULL)
    {
        stUsuario user = cargar_Un_Usuario();
        printf("usuario en alta: %s", &user.nombreUsuario);
        fwrite(&user,sizeof(stUsuario),1,archi);
        gotoxy(20,17);printf("El usuario se Ha registrado Correctamente! \n");
        gotoxy(25,20);system("pause");
        fclose(archi);
    }
}

stUsuario Login()
{
    int flag=0;
     stUsuario user;
     gotoxy(25,8);printf("Ingrese Nombre de Usuario....");
     gets(user.nombreUsuario);
     stUsuario aux = validar_Usuario(user.nombreUsuario);

     if(aux.idUsuario==0)
     {
         while(flag==0)
            {
                  gotoxy(25,10);printf("Ingrese Clave....");
                  fflush(stdin);
                  gets(user.pass);
                  if(strcmp(aux.pass,user.pass)==0)
                  {
                    flag=1;
                    system("cls");
                    gotoxy(20,17);printf("¡Ingreso correcto!");
                    gotoxy(20,18);printf(" Presione Cualquier Tecla para Continuar... ");
                    getch();
                    system("cls");
                    menu_User();
                  }
                  else
                  { system("cls");
                    gotoxy(20,17);printf(" La contraseña es incorrecta");
                    gotoxy(20,18);printf(" Presione Cualquier Tecla para volver a ingresar... ");

                  }
            }
     }
     else
     {
        gotoxy(20,17);printf(" El nombre de usuario no existe! ");
        gotoxy(20,18);printf(" Presione Cualquier Tecla para volver a ingresar... ");
        getch();
        system("cls");
        LoginUser();
     }

     return user;
}

void LoginUser()
{
    gotoxy(50,1);printf("================");
    gotoxy(50,2);printf("LOGIN DE USUARIO");
    gotoxy(50,3);printf("================");

    stUsuario user = Login();
    getch();
}







