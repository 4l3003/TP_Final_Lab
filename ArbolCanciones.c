#include "ArbolCanciones.h"
#include <stdio.h>
#include <stdlib.h>
#define archUser "usuarios.dat"
#define archCanciones "canciones.dat"
#define archPlaylist "playlist.dat"
nodoArbolCancion * inicArbol()
{
    return NULL;
}

nodoArbolCancion * crearNodoArbol(stCancion dato)
{
    nodoArbolCancion * aux = (nodoArbolCancion *) malloc(sizeof(nodoArbolCancion));
    aux->c=dato;
    aux->der=NULL;
    aux->izq=NULL;
    return aux;
}

nodoArbolCancion * insertar(nodoArbolCancion * arbol, nodoArbolCancion *nuevoNodo)
{
    if(arbol==NULL)
    {
        arbol = nuevoNodo;
    }
    else
    {
        if((nuevoNodo->c.idCancion)>(arbol->c.idCancion))
        {
          arbol->der = insertar(arbol->der, nuevoNodo);
        }
        else
        {
           arbol->izq = insertar(arbol->izq, nuevoNodo);
        }
    }
    return arbol;
}

void preorder(nodoArbolCancion * arbol)
{
    if(arbol != NULL)
    {
     MostrarUnaCancion(arbol->c);
     preorder(arbol->izq);
     preorder(arbol->der);
    }
}

void inorder(nodoArbolCancion * arbol)
{
    if(arbol != NULL)
    {
     inorder(arbol->izq);
     MostrarUnaCancion(arbol->c);
     inorder(arbol->der);
    }
}

void postorder(nodoArbolCancion * arbol)
{
    if(arbol != NULL)
    {
     postorder(arbol->izq);
     postorder(arbol->der);
     MostrarUnaCancion(arbol->c);
    }
}

nodoArbolCancion * buscar(nodoArbolCancion * arbol, int id)
{
    nodoArbolCancion * rta=NULL;
    if(arbol!=NULL)
    {
        if(id == arbol->c.idCancion)
        {
              rta = arbol;
        }
        else
        {
              if(id>arbol->c.idCancion)
              {
                   rta = buscar(arbol->der, id);
              }
             else
             {
                  rta = buscar(arbol->izq, id);
             }
        }

    }
    return rta;
}
nodoArbolCancion * buscarTitulo(nodoArbolCancion * arbol, char titulo[30])
{
    nodoArbolCancion *rta=NULL;
    if(arbol!=NULL)
    {
        if(strcmp(titulo,arbol->c.titulo)==0)
        {
              rta = arbol;
        }
        else
        {
              if(strcmp(titulo,arbol->c.titulo)>0)
              {
                   rta = buscarTitulo(arbol->der, titulo);
              }
             else
             {
                  rta = buscarTitulo(arbol->izq, titulo);
             }
        }
    }
    return rta;
}
void llenar_Array_Aleatorio(int arrayRand[], int validos)
{
        for (int i=0; i<validos; i++) {
            arrayRand[i] = i;
        }
        for (int i = 0; i<validos; i++) {
            int temp = arrayRand[i];
            int randomIndex = rand()%validos;
            arrayRand[i]= arrayRand[randomIndex];
            arrayRand[randomIndex]=temp;
        }

}
int ContarRegistrosArchCanciones()
{
    int Cantregistros=0;
    stCancion aux;
    FILE *archi;
    archi = fopen(archCanciones, "rb");
    if(archi!=NULL)
    {
            fseek(archi,0L,SEEK_END);
            Cantregistros = ftell(archi)/sizeof(stCancion);
            fclose(archi);
    }
    return Cantregistros;
}
nodoArbolCancion * Pasar_Archivo_Arbol(nodoArbolCancion *arbol, int validos)
{
    int arrayRand[100], x=0;
    llenar_Array_Aleatorio(arrayRand,validos);
    stCancion aux;
    FILE *archi;
    archi = fopen(archCanciones,"rb");
    if(archi!=NULL)
    {
        while(x<validos)
        {

            fread(&aux,sizeof(stCancion),1,archi);
            if(arrayRand[x] == aux.idCancion)
            {
                if(aux.eliminado==1)
                {
                    nodoArbolCancion *nuevo = crearNodoArbol(aux);
                    arbol = insertar(arbol,nuevo);
                }


               rewind(archi);
                x++;

            }

        }
        fclose(archi);
    }
    return arbol;
}
void VerIDyTituloInorden(nodoArbolCancion *arbol)
{
     if(arbol != NULL)
    {
     VerIDyTituloInorden(arbol->izq);
     printf("[%d] - %s -- %s \n", arbol->c.idCancion,arbol->c.titulo, arbol->c.artista);
     VerIDyTituloInorden(arbol->der);
    }
}
stCancion Cargar_Una_Cancion(nodoArbolCancion *arbol)
{
    nodoArbolCancion *encuentra;
    stCancion aux;
    printf("\n Ingrese Titulo...");
    fflush(stdin);
    gets(aux.titulo);
    encuentra = buscarTitulo(arbol,aux.titulo);
    if(encuentra==NULL)
    {
         printf("\n Ingrese Artista...");
         fflush(stdin);
         gets(aux.artista);
         printf("\n Ingrese Duracion...");
         fflush(stdin);
         scanf("%d",&aux.duracion);
         printf("\n Ingrese Album...");
         fflush(stdin);
         gets(aux.album);
         printf("\n Ingrese Anio...");
         fflush(stdin);
         scanf("%d",&aux.anio);
         printf("\n Ingrese Genero...");
         fflush(stdin);
         gets(aux.genero);
         printf("\n Ingrese Comentario...");
         fflush(stdin);
         gets(aux.comentario);
         aux.eliminado=1;
    }
    else
    {
        gotoxy(20,10);printf(" Ese Cancion ya existe \n Presione cualquier Tecla para cargar otra...");
        getch();
        system("cls");
        aux = Cargar_Una_Cancion(arbol);
    }
    return aux;
}
void cargar_Una_Cancion_Arch(stCancion cancion)
{
    stCancion aux;
    FILE *archi;
    archi = fopen(archCanciones,"a+b");
    if(archi!=NULL)
    {
        fseek(archi,(long)(-1)*sizeof(stCancion),SEEK_END);
        fread(&aux,sizeof(stCancion),1,archi);
        cancion.idCancion = aux.idCancion+1;
        fseek(archi,0L,SEEK_END);
        fwrite(&cancion,sizeof(stCancion),1,archi);
        fclose(archi);
    }
}
void alta_Cancion(nodoArbolCancion **arbol)
{
    system("cls");
    gotoxy(50,1);printf("==============");
    gotoxy(50,2);printf("ALTA CANCION");
    gotoxy(50,3);printf("==============");
    stCancion cancion = Cargar_Una_Cancion(*arbol);

     nodoArbolCancion *nuevo = crearNodoArbol(cancion);
     (*arbol) = insertar((*arbol),nuevo);
     cargar_Una_Cancion_Arch(cancion);

     gotoxy(20,19);printf("La cancion se Ha Cargado Correctamente! \n");
     gotoxy(25,22);system("pause");
     system("cls");
}

nodoArbolCancion * EliminarNodoArbol(nodoArbolCancion * arbol, int id)
{
 if(arbol!=NULL)
 {
    if(arbol->c.idCancion==id)
    {
        if(arbol->izq==NULL && arbol->der==NULL)
        {
            arbol=NULL;
            free(arbol);

        }
        else if(arbol->izq!=NULL)
        {

            nodoArbolCancion * masDer = NMD(arbol->izq);
            arbol->c = masDer->c;
            arbol->izq = EliminarNodoArbol(arbol->izq, masDer->c.idCancion);
        }
        else
        {

            nodoArbolCancion * masIzq =NMI(arbol->der);
            arbol->c = masIzq->c;
            arbol->der = EliminarNodoArbol(arbol->der,masIzq->c.idCancion);
        }

    }
    else
    {
        if(id>arbol->c.idCancion)
        {
           EliminarNodoArbol(arbol->der,id);
        }
        else
        {
           EliminarNodoArbol(arbol->izq,id);
        }
    }
 }
 return arbol;
}

nodoArbolCancion * NMI(nodoArbolCancion * arbol)
{
if(arbol->izq!=NULL || arbol->der!=NULL)
{
    if(arbol->izq!=NULL)
    {
        arbol=NMI(arbol->izq);
    }
    else
    {
        arbol=NMI(arbol->der);
    }
}

return arbol;

}
nodoArbolCancion * NMD(nodoArbolCancion * arbol)
{
    if(arbol->izq!=NULL || arbol->der!=NULL)
    {
        if(arbol->der!=NULL)
        {
            arbol=NMD(arbol->der);
        }
        else
        {
            arbol=NMD(arbol->izq);
        }
    }
    return arbol;
}

void modificar_Cancion(nodoArbolCancion *arbol)
{
    system("cls");
   int id = pedirID();
   nodoArbolCancion *encuentra = buscar(arbol,id);
   gotoxy(17,5);printf("Seleccione con las Direccionales del teclado el dato que quiere modificar: ");
   if(encuentra!=NULL)
   {

        gotoxy(25,8);printf("Titulo: %s", arbol->c.titulo);
        gotoxy(25,10);printf("Artista: %s", arbol->c.artista);
        gotoxy(25,12);printf("Duracion: %d", arbol->c.duracion);
        gotoxy(25,14);printf("Album: %s", arbol->c.album);
        gotoxy(25,16);printf("Anio: %d", arbol->c.anio);
        gotoxy(25,18);printf("Genero: %s", arbol->c.genero);
        gotoxy(25,20);printf("Comentario: %s", arbol->c.comentario);
        SeleccionarDatoModificacionCancion(&arbol);
   }
}

int Pasar_Archivo_ArregloCanciones(stCancion **ArrCanciones)
{
    int x=0;
    stCancion aux;
    FILE *archi;
    archi = fopen(archCanciones,"rb");
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stCancion),1,archi)>0)
        {
            (*ArrCanciones)[x] = aux;
            x++;
        }
        fclose(archi);
    }
    return x;
}
void consultaYMuestraCancion(nodoArbolCancion *arbol)
{

    system("cls");
     int id=0;
    gotoxy(50,1);printf("================");
    gotoxy(50,2);printf("CONSULTA CANCIONES");
    gotoxy(50,3);printf("================");
    id = pedirID();
    nodoArbolCancion *encuentra = buscar(arbol,id);
    if (encuentra!=NULL)
    {
        MostrarUnaCancion(encuentra->c);
        gotoxy(10,25);printf("Presione cualquier tecla para volver al menu anterior...");
        getch();
        system("cls");
    }
    else
    {
        gotoxy(10,22);printf("No existe Una cancion con ese ID, Presione cualquier tecla para volver a ingresar");
        getch();
        system("cls");
        consultaYMuestraCancion(arbol);
    }
}
void Modificar_ArchCanciones(stCancion cancion)
{
    int validos=0;
    stCancion aux;
    FILE *archi;
    archi = fopen(archCanciones, "r+b");
    if(archi!=NULL)
    {
       while(fread(&aux,sizeof(stCancion),1,archi)>0 && aux.idCancion!=cancion.idCancion)
       {
           validos++;
       }
        fseek(archi,(long)(-1)*sizeof(stCancion),SEEK_CUR);
        fwrite(&cancion,sizeof(stCancion),1,archi);
        fclose(archi);
    }
}

void eliminar_Una_Cancion(nodoArbolCancion **arbol)
{
    system("cls");
    //inorder(arbol);
    int id = pedirID();
    nodoArbolCancion *encuentra = buscar((*arbol),id);
    if(encuentra!=NULL)
    {

        (*arbol)->c.eliminado = 0;
        Modificar_ArchCanciones((*arbol)->c);
        (*arbol) = EliminarNodoArbol((*arbol),id);


       // inorder(arbol);
    }
    else
    {
        gotoxy(20,19);printf("ERROR: No se encuentra una cancion con dicho ID...");
        getch();
        eliminar_Una_Cancion(arbol);
    }

    gotoxy(10,22);printf("La cancion elegida se ha eliminado correctamente!");
    getch();
    system("cls");
}






