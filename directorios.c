// Estructuras de Datos y Algoritmos - Curso 2023
// Trabajo Obligatorio
// directorios.c
// Modulo de Implementacion del File System.

#include "directorios.h"

#include <iostream>

using namespace std;

struct nodo_directorios{	
	directorio d;		
	directorios sig;	
	directorios ant;	
	directorios padre;	
	directorios hijo;	
};

// *************** Funciones selectoras ***************

directorio Ret_Dir_d(directorios dir){
// Retorna los datos (nombre y lista de archivos) del directorio "dir".
	return dir->d;
}

directorios Ret_Dir_sig(directorios dir){
// Retorna el directorio siguiente.
	return dir->sig;
}	

directorios Ret_Dir_ant(directorios dir){
// Retorna el directorio anterior.
	return dir->ant;
}

directorios Ret_Dir_padre(directorios dir){
// Retorna el directorio padre.
	return dir->padre;
}

directorios Ret_Dir_hijo(directorios dir){
// Retorna el directorio padre.
	return dir->hijo;
}

bool dir_existente(Sistema s, Cadena nombreDirectorio){
// Retorna true si el "nombreDirectorio" algun hijo del actual y false en caso contrario.

	bool pertenece=false;
	bool salir=false;
	directorios dir=Ret_Dir_Actual(s);
	
	
	if(dir->hijo==NULL){			// Si el directorio actual no tiene hijo (sub carpetas) retorna false
		pertenece=false;
	}
	else{	
		dir=dir->hijo;			// Avanzo al primer hijo y luego busco si existe alguno con ese nombre
		if(dir->ant==NULL && dir->sig==NULL){		// Caso unico hijo
			if(strcmp(Ret_Nombre_Dir(dir->d), nombreDirectorio)==0)
				pertenece=true;
			else 
				pertenece=false;
		}
		else{						// Caso mas de un hijo		
			while(dir->sig!=NULL && salir==false){	
				if(strcmp(Ret_Nombre_Dir(dir->d), nombreDirectorio)==0){
					pertenece=true;
					salir=true;
				}
				else
					dir=dir->sig;
			}
		
			if(dir->sig==NULL && pertenece==false){	// Si salgo del while porque se termino la lista
				if(strcmp(Ret_Nombre_Dir(dir->d), nombreDirectorio)==0)//Analizo ultimo hijo
					pertenece=true;
				else
					pertenece=false;
			}
		}
	}

	return pertenece;
}	


directorios cambiar_directorio(Sistema &s, Cadena nombreDirectorio){
// Cambia el directorio actual por el directorio "nombreDirectorio"
// PRE: "nombreDirectorio" existe y es hijo del directorio actual

	directorios dir=Ret_Dir_Actual(s);
	bool salir=true;
	
	dir=dir->hijo;		// Avanzo al primer hijo y recorro los siguientes hasta encontrarlo
	do{	
		if(strcmp(Ret_Nombre_Dir(dir->d), nombreDirectorio)==0)
			salir=false;
		else
			dir=dir->sig;
	}while(salir);	

	return dir;
}


// *************** Funciones constructoras ***************

directorios crear_directorio(Cadena nombre){
// Crea un directorio vacio de nombre "nombre".
	directorios d = new(nodo_directorios);
	d->d=crear_carpeta(nombre);
	d->sig=NULL;
	d->ant=NULL;
	d->padre=NULL;
	d->hijo=NULL;
	return d;
}

// *************** Funciones nuevas ***************

void imprimir_path(directorios dir){
// Imprime el path del directorio actual

	if(dir->padre==NULL)
		cout << Ret_Nombre_Dir(dir->d);
	else{
		imprimir_path(dir->padre);
		cout << "/" << Ret_Nombre_Dir(dir->d);
	}
}


void ins_directorio(Sistema &s, directorios aux){
// Inserta ordenadamente el directorio "nuevo" como sub directorio del actual
	
	directorios actual=Ret_Dir_Actual(s);
	directorios primerHijo=Ret_Dir_hijo(Ret_Dir_Actual(s));
	bool salir=true;
	int x;
	
	if(primerHijo==NULL){			// Caso directorio actual sin hijos
		actual->hijo=aux;
		aux->padre=actual;
		primerHijo=aux;
	}
	else{ 							// Caso directorio actual con hijo/hijos
		if(primerHijo->ant==NULL && primerHijo->sig==NULL){		// Caso unico hijo
			x=strcmp(Ret_Nombre_Dir(primerHijo->d), Ret_Nombre_Dir(aux->d));
			if(x<0){					// Si aux es mayor que el actual
				primerHijo->sig=aux;
				aux->ant=primerHijo;
				aux->padre=actual;
			}
			else{						// aux es menor que el actual
				primerHijo->ant=aux;
				aux->sig=primerHijo;
				aux->padre=actual;
				actual->hijo=aux;		// aux pasa a ser el primer hijo
			}
		}
		else{							// Caso con mas de un hijo
			x=strcmp(Ret_Nombre_Dir(primerHijo->d), Ret_Nombre_Dir(aux->d));
			if(x>0){					// si inserto en el primer lugar de la lista
				primerHijo->ant=aux;
				aux->sig=primerHijo;
				aux->padre=actual;
				actual->hijo=aux;
			}			//  ***********************************************
			else{
				do{
					x=strcmp(Ret_Nombre_Dir(primerHijo->d), Ret_Nombre_Dir(aux->d));
					if(x>0){				// Si aux es menor inserto
						aux->ant=primerHijo->ant;
						aux->sig=primerHijo;
						aux->padre=actual;
						primerHijo->ant->sig=aux;
						primerHijo->ant=aux;
						salir=false;
					}
					else{					// aux mayor;
						if(primerHijo->sig!=NULL)	// Avanzo si hay elementos en la lista
							primerHijo=primerHijo->sig;
						else{				// Si no hay mas elementos, inserto al final
							primerHijo->sig=aux;
							aux->ant=primerHijo;
							aux->padre=actual;
							salir=false;
						}
					}
				}while(salir);
			}
		}
	}
	while(primerHijo->ant!=NULL){	// avanzo hasta el primer hijo
		primerHijo=primerHijo->ant;
	}
	actual->hijo=primerHijo;
		
}
