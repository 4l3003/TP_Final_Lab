#include "usuario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define nombre_archivo "usuarios.dat"

stUsuario cargar_Un_Usuario()
{
    stUsuario aux;
    printf("\n Ingrese Nombre de Usuario.... ");
    fflush(stdin);
    gets(aux.nombreUsuario);
    printf("\n Ingrese contrasena....");
    fflush(stdin);
    gets(aux.pass);
    printf("\n Ingrese Anio nacimiento.... ");
    fflush(stdin);
    scanf("%d",&aux.anioNacimiento);
    printf("\n Ingrese Genero (m/f)....");
    fflush(stdin);
    scanf("%c", &aux.genero);
    printf("\n Ingrese Pais");
    gets(aux.pais);

    return aux;
}
int validar_Usuario(stUsuario user)
{
    stUsuario aux;
    int flag=0;
    FILE *archi;
    archi = fopen(nombre_archivo, "rb");
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stUsuario),1,archi)>0 && flag==0)
        {
            if(strcmp(aux.nombreUsuario,user.nombreUsuario)==0)
            {
                flag=1;
            }
        }
        fclose(archi);
    }
    return flag;
}
void alta()
{
    FILE *archi;
    archi = fopen(nombre_archivo, "ab");
    if(archi!=NULL)
    {
        stUsuario user = cargar_Un_Usuario();
        if(validar_Usuario(user)==0)
        {
             fwrite(&user,sizeof(stUsuario),1,archi);
        }
        else
        {
            printf("Ese Usuario ya existe, por Favor registre otro");
        }
        fclose(archi);
    }
}






