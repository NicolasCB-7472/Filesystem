// Estructuras de Datos y Algoritmos - Curso 2023
// Trabajo Obligatorio
// directorio.c
// Modulo de Implementacion del File System.

#include "directorio.h"

#include <iostream>

using namespace std;

struct nodo_directorio{	
	Cadena nombre;	
	archivos listaA;	
};	

// *************** Funciones selectoras ***************

Cadena Ret_Nombre_Dir(directorio dir){
// Retorna el nombre del directorio "dir".
	return dir->nombre;
}

archivos Ret_ListaAr(directorio dir){
// Retorna la lista de archivos del directorio "dir"
	return dir->listaA;
}

bool lista_vacia(directorio dir){
// Retorna true si la lista de archivos esta vacia, false en caso contrario
	return dir->listaA==NULL;
}

// *************** Funciones constructoras ***************

directorio crear_carpeta(Cadena nombre){
// Crea un directorio vacio de nombre "nombre".
	directorio d = new(nodo_directorio);
	d->nombre = new char[MAX_NOMBRE];
	strcpy(d->nombre, nombre);		// Nombre de la carpeta
	d->listaA=NULL;					// Lista vacia
	
	return d;
}

void act_lista(directorio &dir, archivos lista){
// Actualiza la lista del directorio "dir"
	dir->listaA=lista;
}



void destruir_directorio(directorio d){
// Destruye el directorio pasado como parametro.
	// Destruir estructura de archivos
	delete [] d->nombre;
	delete d;
}

// *************** Funciones nuevas ***************

void imprime_cadenaDIR(directorio d){
// Imprime el nombre cadena del directorio d
	cout << Ret_Nombre_Dir(d) << endl;
}

archivos Ret_listaA_dir(directorio d){
	return d->listaA;
}

