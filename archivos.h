#ifndef ARCHIVOS_H
#define ARCHIVOS_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Tecnologo en Informatica FIng - DGETP - UTEC
//
// Trabajo Obligatorio
// archivos.h
// Modulo de Definición del File System.

#include "archivo.h"
#include "directorio.h"
#include "directorios.h"
#include "definiciones.h"
#include "sistema.h"

typedef struct nodo_archivos * archivos;
typedef struct nodo_archivo * archivo;	
typedef struct nodo_sistema * Sistema;		

// *************** Funciones selectoras ***************

archivo Ret_Archivo(archivos lista);
// Retorna el archivo actual de la lista de archivos

int cantArch(archivos lista);
// Retorna la cantidad de archivos de una lista

archivo buscar_y_retornar(archivos lista, Cadena nombreArchivo, Cadena extenAR);
// Busca el archivo de nombre "nombre" en la lista y lo retorna;
// PRE: El archivo existe

// *************** Funciones constructoras ***************

void rebobinar_lista(archivos &lista);
// Rebobina la lista dejando el puntero en el primer elemento de la misma

void ins_archivo(Sistema &s, archivo a);
// Inserta ordenadamente el archivo "a" en la lista de archivos.

bool arch_existente(archivos lista, Cadena nombreArchivo, Cadena extenAR);
// Retorna true si el archivo pertenece al directorio actual y false en caso contrario

void act_archivo(Sistema &s, archivo a, Cadena parametro);
// Actualiza el archivo "a" en la lista
// PRE: a pertenece a la lista

void quitar_al_principio(Sistema &s, archivo a, int k);
// Quita "k" cantidad de letras y actualiza el archivo
// PRE: a pertenece a la lista

void quitar_al_final(Sistema &s, archivo a, int k);
// Quita "k" cantidad de letras y actualiza el archivo
// PRE: a pertenece a la lista

void reemplazar_texto(Sistema &s, archivo a, Cadena texto1, Cadena texto2);
// Reemplaza dentro del archivo 'a' el texto1 por el texto2.
// PRE: a pertenece a la lista

void texto_al_principio(Sistema &s, archivo a, Cadena texto);
// Inserta el "texto" al final del contenido del archivo a
// PRE: Archivo existe

void texto_al_final(Sistema &s, archivo a, Cadena texto);
// Inserta el "texto" al final del contenido del archivo a
// PRE: Archivo existe

void eliminar_archivo(Sistema &s, archivo a);
// Elimina el archivo "a" del directorio/carpeta actual

// *************** Funciones nuevas ***************

archivos Ret_ARCHs_sig(archivos la);
// Retorna el archivos siguiente de la lista la.

archivos Ret_ARCHs_ant(archivos la);
// Retorna el archivos anterior de la lista la.

archivos crear_listaA();
// Crea una lista de archivos vacia

archivo Ret_ARCH(archivos la);
// Devuelve un unico archivo de la lista de archivos la.

void imprime_listaARCH(archivos la);
//Imprime los nombres de un archivo de una lista 'archivos'
//PRECOND: lista doble con comienzo y final a NULL
//PRECOND2: Puede haber archivos con txt vacio pero el puntero a 'archivo' existe (es diferente a NULL)


#endif

