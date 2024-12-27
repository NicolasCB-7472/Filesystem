#ifndef SISTEMA_H
#define SISTEMA_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Trabajo Obligatorio
// sistema.h
// Modulo de Definición del File System.

#include "archivo.h"
#include "archivos.h"
#include "directorio.h"
#include "directorios.h"
#include "definiciones.h"
#include <string.h>

typedef struct nodo_sistema * Sistema;
typedef struct nodo_directorios * directorios;
typedef struct nodo_directorio * directorio;	
typedef struct nodo_archivos * archivos;
typedef struct nodo_archivo * archivo;	

// *************** Funciones selectoras ***************

directorios Ret_Dir_RAIZ(Sistema s);
// Retorna el directorio RAIZ.

directorios Ret_Dir_Actual(Sistema s);
// Retorna el directorio actual.

// *************** Funciones constructoras ***************

TipoRet CREARSISTEMA(Sistema &s);
// Inicializa el sistema para que contenga únicamente al directorio RAIZ, sin subdirectorios ni archivos.
// Para mas detalles ver letra.

TipoRet DESTRUIRSISTEMA(Sistema &s);
// Destruye el sistema, liberando la memoria asignada a las estructuras que datos que constituyen el file system.
// Para mas detalles ver letra.

TipoRet CD (Sistema &s, Cadena nombreDirectorio);
// Cambia directorio. 
// Para mas detalles ver letra.
	
TipoRet MKDIR (Sistema &s, Cadena nombreDirectorio);
// Crea un nuevo directorio. 
// Para mas detalles ver letra.

TipoRet RMDIR (Sistema &s, Cadena nombreDirectorio);
// Elimina un directorio.
// Para mas detalles ver letra.

TipoRet MOVE (Sistema &s, Cadena nombre, Cadena directorioDestino);
// mueve un directorio o archivo desde su directorio origen hacia un nuevo directorio destino.
// Para mas detalles ver letra.

TipoRet DIR (Sistema &s, Cadena parametro);
// Muestra el contenido del directorio actual.
// Para mas detalles ver letra.

TipoRet DELETE (Sistema &s, Cadena nombreArchivo);
// Elimina un archivo del directorio actual, siempre y cuando no sea de sólo lectura.
// Para mas detalles ver letra.

TipoRet ATTRIB (Sistema &s, Cadena nombreArchivo, Cadena parametro);
// Cambia los atributos de un archivo perteneciente al directorio actual con "+W" agrefa "escritura" con "-W" quita "Escritura".
// Para mas detalles ver letra.

TipoRet IC (Sistema &s, Cadena nombreArchivo, Cadena texto);
// Agrega un texto al inicio del archivo NombreArchivo.
// Para mas detalles ver letra.

TipoRet IF (Sistema &s, Cadena nombreArchivo, Cadena texto);
// Agrega un texto al final del archivo NombreArchivo.
// Para mas detalles ver letra.

TipoRet DC (Sistema &s, Cadena nombreArchivo, int k);
// Elimina los a lo sumo K primeros caracteres del archivo parámetro.
// Para mas detalles ver letra.

TipoRet DF (Sistema &s, Cadena nombreArchivo, int k);
// Elimina los a lo sumo K últimos caracteres del archivo parámetro.
// Para mas detalles ver letra.

TipoRet TYPE (Sistema &s, Cadena nombreArchivo);
// Imprime el contenido del archivo parámetro.
// Para mas detalles ver letra.

TipoRet SEARCH (Sistema &s, Cadena nombreArchivo, Cadena texto);
// Busca dentro del archivo la existencia del texto.
// Para mas detalles ver letra.

TipoRet REPLACE (Sistema &s, Cadena nombreArchivo, Cadena texto1, Cadena texto2);
// Busca y reemplaza dentro del archivo la existencia del texto1 por el texto2. 
// Para mas detalles ver letra.

// *************** Funciones nuevas ***************

TipoRet CREATEFILE (Sistema &s, Cadena nombreArchivo);
// Crea un nuevo archivo en el directorio actual.
// Para mas detalles ver letra.

directorios Ret_Directorios_actual(Sistema s);
// Retorna el directorios actual del sistema s.




#endif


