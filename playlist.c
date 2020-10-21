#include "playlist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mostrar_Arch_Playlist()
{
    stPlaylist aux;
    FILE *archi;
    archi = fopen(archPlaylist,"rb");
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stPlaylist),1,archi)>0)
        {
             printf("\n ID playlist...%d",aux.idPlaylist);
             printf("\n ID Usuario...%d",aux.idUsuario);
             printf("\n ID Cancion...%d",aux.idCancion);
        }
       fclose(archi);
    }
}
void Agregar_Arch_Playlist(int idCancion, int idUser)
{
    stPlaylist aux;
    stPlaylist nuevo;
    FILE *archi;
    archi = fopen(archPlaylist,"a+b");
    if(archi!=NULL)
    {
        fseek(archi,(long)(-1)*sizeof(stPlaylist),SEEK_END);
        if(fread(&aux,sizeof(stPlaylist),1,archi)>0)
        {
              nuevo.idPlaylist = aux.idPlaylist+1;
        }
        else
        {
            nuevo.idPlaylist = 0;
        }
        nuevo.idUsuario = idUser;
        nuevo.idCancion = idCancion;
        fseek(archi,0L,SEEK_END);
        fwrite(&nuevo,sizeof(stPlaylist),1,archi);
        fclose(archi);
    }
}
void Agregar_A_Playlist(stCelda **ArrUsers,nodoArbolCancion *arbol, int posUser, int id)
{
    nodoArbolCancion *aux = buscar(arbol,id);
    if(aux!=NULL)
    {
         nodoListaCancion *nuevo = crearNodoLista(aux->c);

         (*ArrUsers)[posUser].listaCanciones = agregarAlPrincipio((*ArrUsers)[posUser].listaCanciones,nuevo);

         // printf("%s", (*ArrUsers)[posUser].listaCanciones->c.titulo);
         Agregar_Arch_Playlist(aux->c.idCancion,(*ArrUsers)[posUser].usr.idUsuario);
    }

}

void pasarDeArchivoPlaylistToADL(stCelda **ArrUsers, int validosUser, nodoArbolCancion *arbol)
{
    int posUser=0;
    stPlaylist aux;
    FILE *archi;
    archi = fopen(archPlaylist,"rb");
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stPlaylist),1,archi)>0)
        {
            posUser = buscarUsuario((*ArrUsers),validosUser,aux.idUsuario);
            if(posUser!=-1)
            {
                nodoArbolCancion *cancion = buscar(arbol,aux.idCancion);
                if(cancion!=NULL)
                {
                    nodoListaCancion *nuevoNodo = crearNodoLista(cancion->c);
                    (*ArrUsers)[posUser].listaCanciones = agregarAlPrincipio((*ArrUsers)[posUser].listaCanciones,nuevoNodo);
                }
            }
        }

        fclose(archi);
    }
}
void pasarADLtoArrPlaylist(nodoListaCancion *lista, stCancion **ArrPlaylist, int validos)
{
    nodoListaCancion *seg = lista;
    for(int x=0; x<validos; x++)
    {

        (*ArrPlaylist)[x] = seg->c;
        seg = seg->sig;
    }

}


void ordenar_por_seleccion(stCancion *ArrPlaylist,int validos)
{
    int posmenor=0;
    stCancion aux;
    int i = 0;
    while (i<validos-1)
    {
        posmenor = buscarMenor(i,validos,ArrPlaylist);
        aux = ArrPlaylist[posmenor];
        ArrPlaylist[posmenor]=ArrPlaylist[i];
        ArrPlaylist[i]= aux;
        i++;
    }

}
int buscarMenor(int pos, int dimension,stCancion *ArrPlaylist )
{

    stCancion menor;
    strcpy(menor.titulo,ArrPlaylist[pos].titulo);
    int posmenor=pos;
    int index=pos+1;

    while(index<dimension)
    {
        if(strcmp(ArrPlaylist[index].titulo,menor.titulo)<0)
        {
            strcpy(menor.titulo,ArrPlaylist[index].titulo);
            posmenor=index;
        }
        index++;
    }
    return posmenor;
}
void insertarInsercion(stCancion *ArrPlaylist, int u, stCancion dato)
{
    int i=u;
    while (i>=0 && strcmp(ArrPlaylist[i].genero,dato.genero)<0)
    {
        ArrPlaylist[i+1] = ArrPlaylist[i];
        i--;
    }
    ArrPlaylist[i+1] = dato;

}
void ordenar_por_Insercion(stCancion *ArrPlaylist, int validos)
{
    int u=0;
    while(u<validos-1)
    {
        insertarInsercion(ArrPlaylist,u,ArrPlaylist[u+1]);
        u++;
    }
}
void mostrar_Arreglo_Playlist(stCancion *ArrPlaylist, int validos)
{
    for(int x=0; x<validos; x++)
    {
        printf("[%d] - %s - %s - %s \n",ArrPlaylist[x].idCancion,ArrPlaylist[x].titulo,ArrPlaylist[x].artista,ArrPlaylist[x].genero);
    }
}
/*
void mostrarCancionesRecomendadas(stCelda *ArrUsers, int posUser, int validos)
{
    int random=0;
    int ArrRandom[100];
    pasarADLtoArrPlaylist(ArrUsers[posUser].listaCanciones,&ArrRandom,validos);
    for(int x=0; x<8;x++)
    {
     random = rand()%20;
     printf("[%d] - %s - %s - %s \n",(*ArrRandom)[random].idCancion,(*ArrRandom)[random].titulo,(*ArrRandom)[random].artista,(*ArrRandom)[random].genero);
    }
}
*/



