#ifndef DIRECTORIO_H
#define DIRECTORIO_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Trabajo Obligatorio
// directorio.h
// Modulo de Definición del File System.

typedef struct nodo_directorio * directorio;
typedef struct nodo_archivos * archivos;
typedef struct nodo_archivo * archivo;

#include "archivo.h"
#include "archivos.h"
#include "directorios.h"
#include "definiciones.h"
#include "sistema.h"

// *************** Funciones selectoras ***************

Cadena Ret_Nombre_Dir(directorio dir);
// Retorna el nombre del directorio "dir".

archivos Ret_ListaAr(directorio dir);
// Retorna la lista de archivos del directorio "dir"

bool lista_vacia(directorio dir);
// Retorna true si la lista de archivos esta vacia, false en caso contrario

// *************** Funciones constructoras ***************

void act_lista(directorio &dir, archivos lista);
// Actualiza la lista del directorio "dir"

directorio crear_carpeta(Cadena nombre);
// Crea un directorio vacio de nombre "nombre".

void destruir_directorio(directorio d);
// Destruye el directorio pasado como parametro.

// *************** Funciones nuevas ***************

void imprime_cadenaDIR(directorio d);
// Imprime el nombre cadena del directorio d.

archivos Ret_listaA_dir(directorio d);
// Retorna la lista de archivos del directorio d.

#endif

