#ifndef DIRECTORIOS_H
#define DIRECTORIOS_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Trabajo Obligatorio
// directorios.h
// Modulo de Definición del File System.

typedef struct nodo_sistema * Sistema;
typedef struct nodo_directorios * directorios;
typedef struct nodo_directorio * directorio;		

#include "archivo.h"
#include "archivos.h"
#include "directorio.h"
#include "definiciones.h"
#include "sistema.h"

// *************** Funciones selectoras ***************

directorio Ret_Dir_d(directorios dir);
// Retorna los datos (nombre y lista de archivos) del directorio "dir".

directorios Ret_Dir_sig(directorios dir);
// Retorna el directorio siguiente.

directorios Ret_Dir_ant(directorios dir);
// Retorna el directorio anterior.

directorios Ret_Dir_padre(directorios dir);
// Retorna el directorio padre.

directorios Ret_Dir_hijo(directorios dir);
// Retorna el directorio padre.

bool dir_existente(Sistema s, Cadena nombreDirectorio);
// Retorna true si el "nombreDirectorio" algun hijo del actual y false en caso contrario.

directorios cambiar_directorio(Sistema &s, Cadena nombreDirectorio);
// Cambia el directorio actual por el directorio "nombreDirectorio"
// PRE: "nombreDirectorio" existe y es hijo del directorio actual


// *************** Funciones constructoras ***************

directorios crear_directorio(Cadena nombre);
// Crea un directorio vacio de nombre "nombre".

void ins_directorio(Sistema &s, directorios nuevo);
// Inserta ordenadamente el directorio "nuevo" como sub directorio del actual

// *************** Funciones nuevas ***************

void imprimir_path(directorios dir);
// Imprime el path del directorio actual

#endif

