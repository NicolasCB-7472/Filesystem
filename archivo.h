#ifndef ARCHIVO_H
#define ARCHIVO_H

// Estructuras de Datos y Algoritmos - Curso 2023
// Trabajo Obligatorio
// archivo.h
// Modulo de Definición del File System.

#include "directorio.h"
#include "directorios.h"
#include "definiciones.h"
#include "sistema.h"

typedef struct nodo_archivo * archivo;

// *************** Funciones selectoras ***************

Cadena Ret_nomArch(archivo a);
// Retorna el nombre del archivo a.

Cadena Ret_extenAR(archivo a);
// Retorna la extension del archivo a.

int Ret_artAR(archivo a);
// Retorna el atributo del archivo a.

Cadena Ret_textAR(archivo a);
// Retorna el texto que contiene del archivo a.

Cadena obtener_extension(Cadena &nombre);
// Recibe el nombre completo de un archivo "nombre,txt" y devuelve la extension como retorno y el nombre por referencia.

// *************** Funciones constructoras ***************

archivo crear_archivo(Cadena nom, Cadena ext);
// Crea un archivo de nombre "nom", con extension "ext", con atributo "Lectura/Escritura" y texto vacio.

// *************** Funciones nuevas ***************

bool search_text(archivo a, Cadena texto);
// Busca el texto dentro del archivo a, si existe retorna true y false en caso contrario

archivo cambio_permiso(archivo a, Cadena permiso);
// Cambia el atributo del archivo de Lectura/Escritura a Lectura y visceversa.

archivo quitar_Tex_INI(archivo a, int k);
// Quita "k" cantidad de letras y actualiza el archivo;

archivo quitar_Tex_FIN(archivo a, int k);
// Quita "k" cantidad de letras y actualiza el archivo;

void limpiar_memoria_arch(archivo a);
// Destruye la estructura del archivo "a"

archivo realizar_reemplazo(archivo a, Cadena texto1, Cadena texto2);
// Reemplaza el texto1 por el texto2

archivo agregar_texto_al_principio(archivo a, Cadena texto);
// Inserta el "texto" al principio del contenido del archivo a

archivo agregar_texto_al_final(archivo a, Cadena texto);
// Inserta el "texto" al final del contenido del archivo a

void impr_contenido(archivo a);
// Imprime el contenido del archivo a

//----x----//
archivo Ret_ARCH(archivos la);
// Devuelve un unico archivo de la lista de archivos la.

int caracteres_MAX(Cadena nombre);
// Funcion auxiliar para calcular la cantidad de caracteres de una cadena

void agrego_comienzo(Cadena nombreA, Cadena nombreB);
// Si esta dentro de los caracteres permitidos, copia la cadena B inmediatamente de la cadena A

#endif

