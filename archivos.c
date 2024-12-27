// Estructuras de Datos y Algoritmos - Curso 2023
// Trabajo Obligatorio
// archivos.c
// Modulo de Implementacion del File System.

#include "archivos.h"

#include <iostream>
#include <string.h>

using namespace std;

struct nodo_archivos{
	archivo a;	
	archivos sig;	
	archivos ant;	
};	

// *************** Funciones selectoras ***************

archivo Ret_Archivo(archivos lista){
// Retorna el archivo actual de la lista de archivos
	return lista->a;
}

int cantArch(archivos lista){
// Retorna la cantidad de archivos de una lista
	int cant=0;
	if (lista==NULL)
		cant=0;
	else if(lista->ant==NULL && lista->sig==NULL)
			cant=1;	
	else {	
		rebobinar_lista(lista);
		do{
			lista=lista->sig;	// Avanzo y cuento hasta llegar al final de la lista
			cant++;
		}while(lista!=NULL);
	}

	return cant;
}

archivo buscar_y_retornar(archivos lista, Cadena nombreArchivo, Cadena extenAR){
// Busca el archivo de nombre "nombreArchivo" y extension "extenAR" en la lista y lo retorna;
// PRE: El archivo existe
	
	bool salir=true;
	
	rebobinar_lista(lista);
	do{	
		if((strcmp(Ret_nomArch(lista->a), nombreArchivo)==0) && (strcmp(Ret_extenAR(lista->a), extenAR)==0))
			salir=false;	// Se que el archivo existe, asi que avanzo hasta encontrarlo
		else
			lista=lista->sig;
	}while(salir);	
	
	return lista->a;
}


// *************** Funciones constructoras ***************

void rebobinar_lista(archivos &lista){
// Rebobina la lista dejando el puntero en el primer elemento de la misma
	
	if(lista!=NULL)
		while(lista->ant!=NULL)
			lista=lista->ant;
}


void ins_archivo(Sistema &s, archivo a){
//Inserta ordenadamente el archivo "a" en la lista de archivos.
	
	int x;
	bool salir=true;
	directorio dir=Ret_Dir_d(Ret_Dir_Actual(s));
	archivos lista=Ret_ListaAr(Ret_Dir_d(Ret_Dir_Actual(s)));
	archivos aux = new(nodo_archivos);
	
	aux->a=a;
	aux->ant=NULL;
	aux->sig=NULL;
	
	rebobinar_lista(lista);
	
	if(lista==NULL){					// Caso lista vacia
		lista=aux;
		act_lista(dir, lista);		
	}
	else if(lista->ant==NULL && lista->sig==NULL){		// Caso lista de un elemento
		x=strcmp(Ret_nomArch(lista->a), Ret_nomArch(aux->a));
		if(x<0){					// aux es mayor que el elemento actual de la lista
			lista->sig=aux;
			aux->ant=lista;
		}
		else{						// aux es menor que el elemento actual de la lista
			lista->ant=aux;
			aux->sig=lista;		
		}
		rebobinar_lista(lista);
		act_lista(dir, lista);				// Actualizo la lista en el sistema
	}
	else{							// Caso lista de mas de un elemento
		rebobinar_lista(lista);
		x=strcmp(Ret_nomArch(lista->a), Ret_nomArch(aux->a));
		if(x>0){					// si inserto en el primer lugar de la lista
			lista->ant=aux;
			aux->sig=lista;
		}
		else{//lista=lista->sig;
			do{
				x=strcmp(Ret_nomArch(lista->a), Ret_nomArch(aux->a));
				if(x>0){				// Si aux es menor inserto
					aux->sig=lista;
					aux->ant=lista->ant;
					lista->ant->sig=aux;
					lista->ant=aux;
					rebobinar_lista(lista);
					act_lista(dir, lista);		// Actualizo la lista en el sistema
					salir=false;
				}
				else{					// aux mayor;
					if(lista->sig!=NULL)		// Avanzo si hay elementos en la lista
						lista=lista->sig;
					else{				// Si no hay mas elementos, inserto al final
						lista->sig=aux;
						aux->ant=lista;
						rebobinar_lista(lista);
						act_lista(dir, lista);	// Actualizo la lista en el sistema
						salir=false;
					}
				}
			}while(salir);
		}
	}
}

bool arch_existente(archivos lista, Cadena nombreArchivo, Cadena extenAR){
// Retorna true si el archivo pertenece al directorio actual y false en caso contrario
	
	bool pertenece=false;
	
	if(lista==NULL){							// Caso lista vacia
		pertenece=false;
	}
	else if(lista->ant==NULL && lista->sig==NULL){				// Caso lista de un elemento
		if(strcmp(Ret_nomArch(lista->a), nombreArchivo)==0){		//  Mismo nombre, me fijo:
			if(strcmp(Ret_extenAR(lista->a), extenAR)==0)	
				pertenece=true; 				// Mismo nombre y extension
			else
				pertenece=false; 				// Mismo nombre, distinta extension
		}	
		else
			pertenece=false; 					// Distinto nombre
	}
	else{
		rebobinar_lista(lista);
		do{
			if(strcmp(Ret_nomArch(lista->a), nombreArchivo)==0){	//  Mismo nombre, me fijo:
				if(strcmp(Ret_extenAR(lista->a), extenAR)==0)	
					pertenece=true; 			// Mismo nombre y extension
				else
					pertenece=false; 			// Mismo nombre, distinta extension
			}
			lista=lista->sig;
		}while(pertenece==false && lista->sig!=NULL);
		
		if(pertenece==false && lista->sig==NULL){			// Analizo el ultimo elemento de la lista
			if(strcmp(Ret_nomArch(lista->a), nombreArchivo)==0){	//  Mismo nombre, me fijo:
				if(strcmp(Ret_extenAR(lista->a), extenAR)==0)	
					pertenece=true; 			// Mismo nombre y extension
				else
					pertenece=false; 			// Mismo nombre, distinta extension
			}
			else
				pertenece=false; 				// Distinto nombre
		}
	}
	
	return pertenece;
}

void act_archivo(Sistema &s, archivo a, Cadena parametro){
// Actualiza el archivo "a" en la lista
// PRE: a pertenece a la lista
	
	bool salir=true;
	directorio dir=Ret_Dir_d(Ret_Dir_Actual(s));
	archivos lista=Ret_ListaAr(dir);
	
	rebobinar_lista(lista);
	do{	
		if((strcmp(Ret_nomArch(lista->a), Ret_nomArch(a))==0) && (strcmp(Ret_extenAR(lista->a), Ret_extenAR(a))==0)){
			lista->a=cambio_permiso(a, parametro);
			salir=false;	// Se que el archivo existe, asi que avanzo hasta encontrarlo
		}
		else
			lista=lista->sig;
	}while(salir);	
	rebobinar_lista(lista);
	act_lista(dir, lista);
}

void quitar_al_principio(Sistema &s, archivo a, int k){
// Quita "k" cantidad de letras y actualiza el archivo;
// PRE: a pertenece a la lista
	
	bool salir=true;
	directorio dir=Ret_Dir_d(Ret_Dir_Actual(s));
	archivos lista=Ret_ListaAr(dir);
	
	rebobinar_lista(lista);
	do{	
		if((strcmp(Ret_nomArch(lista->a), Ret_nomArch(a))==0) && (strcmp(Ret_extenAR(lista->a), Ret_extenAR(a))==0)){
			lista->a=quitar_Tex_INI(a, k);
			salir=false;	// Se que el archivo existe, asi que avanzo hasta encontrarlo
		}
		else
			lista=lista->sig;
	}while(salir);	
	
	rebobinar_lista(lista);
	act_lista(dir, lista);
}

void quitar_al_final(Sistema &s, archivo a, int k){
// Quita "k" cantidad de letras y actualiza el archivo;
// PRE: a pertenece a la lista
	
	bool salir=true;
	directorio dir=Ret_Dir_d(Ret_Dir_Actual(s));
	archivos lista=Ret_ListaAr(dir);
	
	rebobinar_lista(lista);
	do{	
		if((strcmp(Ret_nomArch(lista->a), Ret_nomArch(a))==0) && (strcmp(Ret_extenAR(lista->a), Ret_extenAR(a))==0)){
			lista->a=quitar_Tex_FIN(a, k);
			salir=false;	// Se que el archivo existe, asi que avanzo hasta encontrarlo
		}
		else
			lista=lista->sig;
	}while(salir);	
	
	rebobinar_lista(lista);
	act_lista(dir, lista);
}

void reemplazar_texto(Sistema &s, archivo a, Cadena texto1, Cadena texto2){
// Reemplaza dentro del archivo 'a' el texto1 por el texto2.
// PRE: Archivo existe
	
	bool salir=true;
	directorio dir=Ret_Dir_d(Ret_Dir_Actual(s));
	archivos lista=Ret_ListaAr(dir);
	
	rebobinar_lista(lista);
	do{	
		if((strcmp(Ret_nomArch(lista->a), Ret_nomArch(a))==0) && (strcmp(Ret_extenAR(lista->a), Ret_extenAR(a))==0)){
			lista->a=realizar_reemplazo(a, texto1, texto2);
			salir=false;	
		}
		else
			lista=lista->sig; // Se que el archivo existe, asi que avanzo hasta encontrarlo
	}while(salir);	
	
	rebobinar_lista(lista);
	act_lista(dir, lista);
}

void texto_al_principio(Sistema &s, archivo a, Cadena texto){
// Inserta el "texto" al final del contenido del archivo a y actualiza el archivo
// PRE: Archivo existe
	
	bool salir=true;
	directorio dir=Ret_Dir_d(Ret_Dir_Actual(s));
	archivos lista=Ret_ListaAr(dir);
	
	rebobinar_lista(lista);
	do{	
		if((strcmp(Ret_nomArch(lista->a), Ret_nomArch(a))==0) && (strcmp(Ret_extenAR(lista->a), Ret_extenAR(a))==0)){
			lista->a=agregar_texto_al_principio(a, texto);
			salir=false;
		}
		else
			lista=lista->sig; // Se que el archivo existe, asi que avanzo hasta encontrarlo
	}while(salir);	
	
	rebobinar_lista(lista);
	act_lista(dir, lista);
}

void texto_al_final(Sistema &s, archivo a, Cadena texto){
// Inserta el "texto" al final del contenido del archivo a y actualiza el archivo
// PRE: Archivo existe
	
	bool salir=true;
	directorio dir=Ret_Dir_d(Ret_Dir_Actual(s));
	archivos lista=Ret_ListaAr(dir);
	
	rebobinar_lista(lista);
	do{	
		if((strcmp(Ret_nomArch(lista->a), Ret_nomArch(a))==0) && (strcmp(Ret_extenAR(lista->a), Ret_extenAR(a))==0)){
			lista->a=agregar_texto_al_final(a, texto);
			salir=false;
		}
		else
			lista=lista->sig; // Se que el archivo existe, asi que avanzo hasta encontrarlo
	}while(salir);	
	
	rebobinar_lista(lista);
	act_lista(dir, lista);
}




void eliminar_archivo(Sistema &s, archivo a){
// Elimina el archivo "a" del directorio/carpeta actual

	bool salir=true;
	directorio dir=Ret_Dir_d(Ret_Dir_Actual(s));
	archivos lista=Ret_ListaAr(dir);
	archivos aux;
	
	rebobinar_lista(lista);
	do{	
		if((strcmp(Ret_nomArch(lista->a), Ret_nomArch(a))==0) && (strcmp(Ret_extenAR(lista->a), Ret_extenAR(a))==0)){
			if(lista->ant==NULL && lista->sig==NULL){		// Caso lista de un elemento
				limpiar_memoria_arch(lista->a);
				delete lista;
				lista=NULL;
				salir=false;
				act_lista(dir, lista);
			}
			else{						// Hay por lo menos 2 archivos
				if(lista->ant==NULL){				// Si elimino el primer archivo de la lista
					aux=lista;
					lista=lista->sig;
					limpiar_memoria_arch(aux->a);
					lista->ant=NULL;				
				}
				else if(lista->sig==NULL){			// Si elimino el ultimo archivo de la lista
					aux=lista;
					lista=lista->ant;
					limpiar_memoria_arch(aux->a);
					lista->sig=NULL;				
				}
				else{								// Si no elimino ni el primero, ni el ultimo
					aux=lista;						// Guardo ubicacion del archivo
					lista=lista->ant;					
					limpiar_memoria_arch(aux->a);
					lista->sig=aux->sig;;
					lista->sig->ant=aux->ant;
				}
				delete aux;
				rebobinar_lista(lista);
				act_lista(dir, lista);
				salir=false;
			}
		}
		else
			lista=lista->sig;
	}while(salir);	
	
}

// *************** Funciones nuevas ***************

archivo Ret_ARCH(archivos la){
// Devuelve un unico archivo de la lista de archivos la.
	return la->a;
}

archivos Ret_ARCHs_sig(archivos la){
// Retorna el archivos siguiente de la lista la.
	return la->sig;
}
archivos Ret_ARCHs_ant(archivos la){
// Retorna el archivos anterior de la lista la.
	return la->ant;
}

archivos crear_listaA(){
// Crea una lista de archivos vacia
	archivos nueva=new(nodo_archivos);
	nueva->sig = NULL;
	nueva->ant = NULL;
	nueva->a = NULL; 
	
	return nueva;
}

void imprime_listaARCH(archivos la){
//PRECOND: lista doble con comienzo y final a NULL
//PRECOND2: Puede haber archivos con txt vacio pero el puntero a 'archivo' existe (es diferente a NULL)

	archivos vacia = crear_listaA();
	if(la != vacia){ //Si es diferente al vacio tiene al menos un elemento en la lista
		//seteo la lista al inicio
		while((Ret_ARCHs_ant(la)) != Ret_ARCHs_ant(vacia))
			la=Ret_ARCHs_ant(la);
		//Comienzo a imprimir desde primer elemento
		while(Ret_ARCHs_sig(la) != Ret_ARCHs_sig(vacia)){
			cout << Ret_nomArch(Ret_Archivo(la)) << "." << Ret_extenAR(Ret_Archivo(la));
			if(Ret_artAR(Ret_Archivo(la))==666)
				cout << "\t\tLectura/Escritura" << endl;
			else 
				cout << "\t\tLectura" << endl;
			la=Ret_ARCHs_sig(la);
		}
		cout << Ret_nomArch(Ret_Archivo(la)) << "." << Ret_extenAR(Ret_Archivo(la));
		if(Ret_artAR(Ret_Archivo(la))==666)
			cout << "\t\tLectura/Escritura" << endl;
		else 
			cout << "\t\tLectura" << endl;
		//FIN ListaArchivos
	}else{
		cout << "ERROR: Necesitas archivos para imprimir, lista vacia" << endl;
	}
}



