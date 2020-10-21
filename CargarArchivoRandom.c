#include "CargarArchivoRandom.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ADL_Users.h"
#include "listaCanciones.h"
#define archUser "usuarios.dat"
#define archCanciones "canciones.dat"
#define archPlaylist "playlist.dat"

void NombreRandom(char n[])
{

    char nombres[][30] = {"Martin","Alejo","Emanuel","Maxi","Rodrigo","Pepe","Octavio","Martina","Victoria","Valentin","Matias",
    "Carlos","Trinidad","Roberta","Eric","Susana","Ramiro","Toto","Coco","Pepa","Hidra","German","Pablo","Eduardo","Lazaro",
    "Lazara","Nicolas","Nacho","Gonzalo","Alejandra" };

    int random = rand()%(sizeof(nombres))/(sizeof(char)*30);

    strcpy(n,nombres[random]);
}

void PaisRandom(char p[])
{

    char paises[][30] = {"Argentina","Chile","Brasil","Uruguay","Paraguay", "Bolivia","Peru","Afganistan","Usa"};

    int random = rand()%(sizeof(paises))/(sizeof(char)*30);

    strcpy(p,paises[random]);
}

int fechaNacRandom()
{
    int random = rand()%2005;
    return random;
}

void cargar_Archivo_User()
{
    char nombre[30], pais[30], pass[30]="1234";
    stUsuario aux;
    FILE *archi;
    archi = fopen(archUser,"ab");
    if(archi!=NULL)
    {
        for(int x=0; x<10; x++)
        {
            aux.idUsuario = x;
            NombreRandom(nombre);
            strcpy(aux.nombreUsuario,nombre);
            strcpy(aux.pass,pass);
            aux.anioNacimiento = fechaNacRandom();
            aux.genero = 'm';
            PaisRandom(pais);
            aux.rol = 0;
            aux.eliminado=0;
            strcpy(aux.pais,pais);

            fwrite(&aux,sizeof(stUsuario),1,archi);
        }
    }
    fclose(archi);
}
void Cargar_Archivo_canciones()
{
    stCancion aux;
    int x=0;
    char titulo[][60] = {"Muerdeme","Arrebatate","Tutu","Que tire pa lante","Lo que te di","No se me quita","Bonita","La mejor version de mi",
     "China","Lampara para mis pies","El favor","Chica bombastic","Yo x ti tu x mi","Calma","Parecen Viernes","Minifalda","Indeciso",
     "Date la vuelta","No lo trates"};
     char artista[][60] = {"Alkilados","Charly gitanos","Pedro capo","Daddy Yankee","Marc Anthony","Maluma","Sebastian Yatra", "Romeo Santos",
     "Anuel AA","Juan Luis Guerra","Nicky Jam","Wisin y Yandel","Rosalia","Pedro Capo","Marc Anthony", "Juanes","Reik","Luis Fonsi",
     "Pitbull"};

     int anio[] = {1967,1969,1973,1990,1986,1978,1970,1978,1990,1993,1972,1970,1983,1968,1984,1985,1987,1993,1970};
     char genero[][20] = {"Rock Nacional", "Latinos","Reggaeton", "Pop", "Rap"};
     char comentario[30] = {"Sin Comentariosssss"};

     FILE *archi;
     archi = fopen(archCanciones,"ab");
     int id=20;
     if(archi!=NULL)
     {
         for(x=0; x<19; x++)
        {

            aux.idCancion = id;
            strcpy(aux.titulo, titulo[x]);
            strcpy(aux.artista,artista[x]);
            aux.duracion = rand()%10;
            strcpy(aux.album,"Sin Nombre");
            aux.anio = anio[x];

            strcpy(aux.genero,genero[1]);

          strcpy(aux.comentario, comentario);
            aux.eliminado = 1;
           fwrite(&aux,sizeof(stCancion),1,archi);
           id++;
        }

        fclose(archi);
     }
}
void mostrar_archivoUser()
{
    FILE *archi;
    stUsuario aux;
    archi = fopen(archUser,"rb");
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stUsuario),1,archi)>0)
        {
            printf("\n ============================");
            printf("\n ID user...%d", aux.idUsuario);
            printf("\n Nombre...%s", aux.nombreUsuario);
            printf("\n Pass...%s", aux.pass);
            printf("\n anio nac...%d", aux.anioNacimiento);
            printf("\n Genero...%c", aux.genero);
            printf("\n Pais...%s", aux.pais);
            printf("\n Rol...%d", aux.rol);
            printf("\n Eliminado...%d",aux.eliminado);
        }
        fclose(archi);
    }
}
void mostrar_archivoCanciones()
{
    FILE *archi;
    stCancion aux;
    archi = fopen(archCanciones,"rb");
    if(archi!=NULL)
    {
        while(fread(&aux,sizeof(stCancion),1,archi)>0)
        {
            printf("\n ============================");
            printf("\n ID Cancion...%d", aux.idCancion);
            printf("\n Titulo...%s", aux.titulo);
            printf("\n Artista...%s", aux.artista);
            printf("\n Duracion...%d", aux.duracion);
            printf("\n Album...%s", aux.album);
            printf("\n Anio...%d", aux.anio);
            printf("\n Genero...%s", aux.genero);
            printf("\n Comentario...%s", aux.comentario);
            printf("\n Eliminado...%d",aux.eliminado);
        }
        fclose(archi);
    }
}

