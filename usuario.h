#ifndef USUARIO_H_INCLUDED
#define USUARIO_H_INCLUDED

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



stUsuario cargar_Un_Usuario();
stUsuario validar_Usuario(char nombreUser[30]);
void altaDeUser();
stUsuario Login();
void LoginUser();

#endif
