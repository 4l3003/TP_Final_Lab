#include "ADL_Users.h"
#include "gotoxy.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

int agregarUsuario(stCelda **ArrUsers, int validos, stCelda nueva)
{
    (*ArrUsers)[validos] = nueva;
    validos++;
    return validos;
}

int buscarUsuario(stCelda *a, int validos, int id)
{
    int rta=-1;
    int i=0;
    while(i<validos && rta==-1)
    {
        if(a[i].usr.idUsuario == id)
        {
            rta = i;
        }
        i++;
    }
    return rta;
}
int buscarUsuarioNombre(stCelda *a, int validos, char Username[30])
{
    int rta=-1;
    int i=0;
    while(i<validos && rta==-1)
    {
        if(strcmp(a[i].usr.nombreUsuario,Username)==0)
        {
            rta = i;
        }
        i++;
    }
    return rta;
}
void MostrarUnUsuario(stUsuario user)
{
    printf("\n ID...%d",user.idUsuario);
    printf("\n Nombre de User...%s",user.nombreUsuario);
    printf("\n Pass...%s",user.pass);
    printf("\n Anio Nac: %d", user.anioNacimiento);
    printf("\n Genero: %c", user.genero);
    printf("\n Pais: %s", user.pais);
    printf("\n =============================");
}

void mostrarUsuarios(stCelda *arrUsers, int validos)
{
    for(int x=0; x<validos; x++)
    {
        printf("\n =====User=====");
        MostrarUnUsuario(arrUsers[x].usr);
        printf("\n =====Canciones=====");
        mostrarLista(arrUsers[x].listaCanciones);
    }
}
int Val_users_Arch()
{
    int validos=0;
    stUsuario aux;
    FILE *archi;
    archi = fopen(archUser,"rb");
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stUsuario),1,archi)>0)
        {
            if(aux.eliminado==0)
            {
                validos++;
            }
        }
        fclose(archi);
    }
    return validos;
}
void pasar_Archivo_arreglo(stCelda **ArregloDinUsers)
{
    int x=0;
    stUsuario aux;
    FILE *archi;
    archi = fopen(archUser,"rb");
    if(archi!=NULL)
    {
         while(fread(&aux,sizeof(stUsuario),1,archi)>0)
        {
            if(aux.eliminado==0)
            {
                (*ArregloDinUsers)[x].usr = aux;
                (*ArregloDinUsers)[x].listaCanciones = inicLista();
                //agregar las canciones tambien a la lista
                x++;
            }
        }
    }
}
int validar_Usuario(stCelda *arregloUser, char nombreUser[30], int validos)
{
    int x=0, id=-1;
            while((x<validos) && (id==-1))
            {
                if(strcmp(nombreUser,arregloUser[x].usr.nombreUsuario)==0)
                {
                    id=arregloUser[x].usr.idUsuario;
                }
                x++;
            }
    return id;
}

stUsuario cargar_Un_Usuario(stCelda *arregloUser, int validos)
{
    stUsuario aux;
    int id=0;
    printf("\n Ingrese Nombre de Usuario.... ");
    fflush(stdin);
    gets(aux.nombreUsuario);
    id=validar_Usuario(arregloUser,aux.nombreUsuario,validos);
    if(id==-1)
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
         aux.eliminado = 0;
         aux.rol = 0;
    }
    else
    {
        gotoxy(20,10);printf(" Ese Nombre de Usuario ya esta en uso \n Presione cualquier Tecla para ingresar otro...");
        getch();
        system("cls");
        aux = cargar_Un_Usuario(arregloUser,validos);
    }
    return aux;
}
void Cargar_Un_Usuario_Arch(stUsuario user)
{
    stUsuario aux;
    FILE *archi;
    archi = fopen(archUser,"a+b");
    if(archi!=NULL)
    {
        fseek(archi,(long)(-1)*sizeof(stUsuario),SEEK_END);
        fread(&aux,sizeof(stUsuario),1,archi);
        user.idUsuario = aux.idUsuario+1;
        fseek(archi,0L,SEEK_END);
        fwrite(&user,sizeof(stUsuario),1,archi);

        fclose(archi);
    }
}
int altaDeUser(stCelda *ArregloUser, int validos)
{
        stCelda aux;
        stUsuario user = cargar_Un_Usuario(ArregloUser,validos);

        aux.usr = user;
        aux.listaCanciones = inicLista();

        validos = agregarUsuario(&ArregloUser,validos,aux);

        Cargar_Un_Usuario_Arch(user);

        gotoxy(20,17);printf("El usuario se Ha registrado Correctamente! \n");
        gotoxy(25,20);system("pause");
        return validos;
}
int loginUser(stCelda *ArrUsers,int validos, nodoArbolCancion *arbol)
{
     int flag=0;
     stUsuario user;
     gotoxy(25,8);printf("Ingrese Nombre de Usuario....");
     gets(user.nombreUsuario);
     int id = validar_Usuario(ArrUsers,user.nombreUsuario,validos);
     if(id!=-1)
     {
         int pos = buscarUsuario(ArrUsers,validos,id);
         while(flag==0)
            {
                  gotoxy(25,10);printf("Ingrese Clave....");
                  fflush(stdin);
                  gets(user.pass);
                  if(strcmp(user.pass,ArrUsers[pos].usr.pass)==0)
                  {
                    flag=1;
                    system("cls");
                    gotoxy(20,17);printf("Ingreso correcto!!!");
                    gotoxy(20,18);printf(" Presione Cualquier Tecla para Continuar... ");
                    getch();
                    system("cls");
                    if(ArrUsers[pos].usr.rol==0)
                    {
                        menu_User(ArrUsers,id,validos, arbol);
                    }
                    else
                    {
                        menu_Admin(ArrUsers,id,validos,arbol);
                    }

                  }
                  else
                  {
                    system("cls");
                    gotoxy(20,17);printf(" La clave es incorrecta");
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
        loginUser(ArrUsers,validos,arbol);
     }
     return id;
}
int pedirID()
{
    int id=0;
    gotoxy(25,10);printf("Ingrese ID...");
    scanf("%d",&id);
    return id;
}
void Modificar_Arch(stUsuario user)
{
    int validos=0;
    stUsuario aux;
    FILE *archi;
    archi = fopen(archUser, "r+b");
    if(archi!=NULL)
    {
       while(fread(&aux,sizeof(stUsuario),1,archi)>0 && aux.idUsuario!=user.idUsuario)
       {
           validos++;
       }
        fseek(archi,(long)(-1)*sizeof(stUsuario),SEEK_CUR);
        fwrite(&user,sizeof(stUsuario),1,archi);
        fclose(archi);
    }

}
void bajadeUser(stCelda **ArrUsers, int *validos)
{
    int id = pedirID();
    int encuentra = buscarUsuario((*ArrUsers),validos,id);
    if (encuentra!=-1)
    {
            (*ArrUsers)[encuentra].usr.eliminado = 1;
            Modificar_Arch((*ArrUsers)[encuentra].usr);
            validos--;
            gotoxy(20,17);printf("El Usuario se ha eliminado con exito! :)");
    }
    else
    {
        gotoxy(20,17);printf("ERROR! el id ingresado no corresponde a ningun usuario registrado :(");
        getch();
        system("cls");
        bajadeUser(ArrUsers, validos);
    }

    gotoxy(20,18);printf("Presione Cualquier Tecla para regresar al menu... ");
    getch();
    system("cls");
}
void ModificaciondeUser(stCelda *ArrUsers, int validos)
{
   int id = pedirID();
   int pos = buscarUsuario(ArrUsers,validos,id);
   system("cls");

   if(pos!=-1)
   {
        gotoxy(17,5);printf("Seleccione con las Direccionales del teclado el dato que quiere modificar: ");
        gotoxy(25,8);printf("Nombre de User: %s", ArrUsers[pos].usr.nombreUsuario);
        gotoxy(25,10);printf("Clave: %s", ArrUsers[pos].usr.pass);
        gotoxy(25,12);printf("Anio de Nac: %d", ArrUsers[pos].usr.anioNacimiento);
        gotoxy(25,14);printf("Genero: %c",ArrUsers[pos].usr.genero);
        gotoxy(25,16);printf("Pais: %s", ArrUsers[pos].usr.pais);
        SeleccionarDatoModificacion(&ArrUsers,pos, validos);
   }
   else
   {
       gotoxy(20,17);printf("ERROR! el id ingresado no corresponde a ningun usuario registrado :(");
       gotoxy(20,18);printf("Presione Cualquier Tecla para volver a ingresar... ");
       getch();
       ModificaciondeUser(ArrUsers,validos);
   }
}
int buscarMenorUser(int pos, int dimension,stCelda *ArrUsers)
{
    stCelda menor;
    strcpy(menor.usr.nombreUsuario,ArrUsers[pos].usr.nombreUsuario);
    int posmenor=pos;
    int index=pos+1;
    while(index<dimension)
    {
        if(strcmp(ArrUsers[index].usr.nombreUsuario,menor.usr.nombreUsuario)<0)
        {
            strcpy(menor.usr.nombreUsuario,ArrUsers[index].usr.nombreUsuario);
            posmenor=index;
        }
        index++;
    }
    return posmenor;
}
void OrdenarYMostrarUser(stCelda *ArrUsers, int validos)
{
    gotoxy(50,1);printf("================");
    gotoxy(50,2);printf("LISTADO USERS");
    gotoxy(50,3);printf("================");
    int posmenor=0;
    stCelda aux;
    int i = 0, x=0;
    while (i<validos-1)
    {
        posmenor = buscarMenorUser(i,validos,ArrUsers);
        aux = ArrUsers[posmenor];
        ArrUsers[posmenor]=ArrUsers[i];
        ArrUsers[i]= aux;
        i++;
    }
    for(x=0; x<validos; x++)
    {
        MostrarUnUsuario(ArrUsers[x].usr);
    }
    printf("\n\n                 ");
    system("pause");
    system("cls");
}
void consulta_User(stCelda *ArrUsers, int validos)
{
    char User[30];
    gotoxy(50,1);printf("================");
    gotoxy(50,2);printf("CONSULTA USERS");
    gotoxy(50,3);printf("================");
    gotoxy(35,5);printf("Ingrese Nombre de Usuario a consultar...");
    gets(User);
    int pos = buscarUsuarioNombre(ArrUsers,validos,User);
    if (pos!=-1)
    {
        MostrarUnUsuario(ArrUsers[pos].usr);
        gotoxy(10,25);printf("Presione cualquier tecla para volver al menu anterior...");
        getch();
        system("cls");
    }
    else
    {
        gotoxy(10,22);printf("No existe Un Usuario con ese nombre, Presione cualquier tecla para volver a ingresar");
        getch();
        system("cls");
        consulta_User(ArrUsers,validos);
    }

}








