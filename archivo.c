// Estructuras de Datos y Algoritmos - Curso 2023
// Trabajo Obligatorio
// archivo.c
// Modulo de Implementacion del File System.

#include "archivo.h"

#include <iostream>
#include <string.h>

using namespace std;

struct nodo_archivo{
	Cadena nombre;	
	Cadena extension;	
	int atributo;	
	Cadena texto;
};

// *************** Funciones selectoras ***************

Cadena Ret_nomArch(archivo a){
// Retorna el nombre del archivo a.
	return a->nombre;
}

Cadena Ret_extenAR(archivo a){
// Retorna la extension del archivo a.
	return a->extension;
}

int Ret_artAR(archivo a){
// Retorna el atributo del archivo a.
	return a->atributo;
}

Cadena Ret_textAR(archivo a){
// Retorna el texto que contiene del archivo a.
	return a->texto;
}

Cadena obtener_extension(Cadena &nombre){
// Recibe el nombre completo de un archivo "nombre,txt" y devuelve la extension como retorno y el nombre por referencia.
	
	Cadena copiaNombre = new char[MAX_NOMBRE];
	Cadena copiaExt = new char[MAX_EXTENSION];
	int i=0, j=0, CONT=0;
	
	while(nombre[i]!='.' && CONT<16){			// Copio el nombre hasta el punto '.'
		copiaNombre[i]=nombre[i];
		i++;
		CONT++;
	}
	copiaNombre[i]='\0';
	i++;
	while(nombre[i]!='\0' && CONT<4){			// Copio la extension hasta el final '\0'
		copiaExt[j]=nombre[i];
		j++;
		i++;
		CONT++;
	}
	copiaExt[i]='\0';
	
	strcpy(nombre, copiaNombre);	
	
	return copiaExt;
	
}

// *************** Funciones constructoras ***************

archivo crear_archivo(Cadena nom, Cadena ext){
// Crea un archivo de nombre "nom", con extension "ext", con atributo "Lectura/Escritura" y texto vacio.
	archivo a = new(nodo_archivo);					// Crea un nodo de tipo archivo
	
	a->nombre = new char[MAX_NOMBRE];				// Pido memoria para copiar los datos
	strcpy(a->nombre, nom);						// Copio los datos
	
	a->extension = new char[MAX_EXTENSION];				// Pido memoria para copiar los datos
	strcpy(a->extension, ext);					// Copio los datos
	
	a->atributo=666;
									// Copio los datos
	a->texto = NULL;						// Texto vacio
	/*a->texto = new char[MAX_TAM];
	strcpy(a->texto, "hola");	
	*/

	return a;
}

bool search_text(archivo a, Cadena texto){
// Busca el texto dentro del archivo a, si pertenece retorna true y false en caso contrario

	bool pertenece=false;
	bool salir=true;
	int tamText=0, tamTexSave=0, tamArch=0, posT=0, posA=0;

	if(a->texto==NULL)
		pertenece=false;
	else{
		while(texto[posT]!='\0'){	// Cuento la cantidad de letras del texto a buscar
			tamText++;
			posT++;
		}
		while(a->texto[posA]!='\0'){	// Cuento la cantidad de letras del texto del archivo
			tamArch++;
			posA++;
		}
		if(tamText>tamArch){		// Si el texto es mas grande que el archivo
			pertenece=false;
		}
		else{
			posA=0;
			posT=0;
			tamTexSave=tamText;
			do{
				if(a->texto[posA]==texto[posT]){
					posA++;
					posT++;
					tamArch--;
					tamText--;
					if(tamText==0){
						pertenece=true;
						salir=false;
					}
				}
				else{
					tamText=tamTexSave;
					if(a->texto[posA]!='\0')
						posA++;
					else if(a->texto[posA]=='\0' && tamText>0){
						pertenece=true;
						salir=false;
					}
				}
			}while(salir);		
		}
	}

	return pertenece;
}

archivo cambio_permiso(archivo a, Cadena parametro){
// Cambia el atributo del archivo de Lectura/Escritura a Lectura y visceversa.
	
	if((strcmp(parametro, "-W")==0) || (strcmp(parametro, "-w")==0))
		a->atributo=222;		// Lectura
	else					// Caso contrario, lo dejo por defecto
		a->atributo=666;		// Lectura/Escritura
	
	return a;	
}

archivo quitar_Tex_INI(archivo a, int k){
// Quita "k" cantidad de letras y actualiza el archivo;
	
	// Implementar
	
	return a;
}

archivo quitar_Tex_FIN(archivo a, int k){
// Quita "k" cantidad de letras y actualiza el archivo;

	// Implementar
	
	return a;
}

void impr_contenido(archivo a){
// Imprime el contenido del archivo a
	
	if(a->texto==NULL)
		cout << "[vacio]" << endl;	
	else
		cout << a->texto << endl;

}

archivo agregar_texto_al_principio(archivo a, Cadena texto){
// Inserta el "texto" al principio del contenido del archivo a

	// Falta implementar los demas caso
	if(a->texto==NULL){
		a->texto = new char[MAX_TAM];
		strcpy(a->texto, texto);	
	}

	return a;
}

archivo agregar_texto_al_final(archivo a, Cadena texto){
// Inserta el "texto" al final del contenido del archivo a

	// Falta implementar los demas casos
	if(a->texto==NULL){
		a->texto = new char[MAX_TAM];
		strcpy(a->texto, texto);	
	}

	return a;
}


archivo realizar_reemplazo(archivo a, Cadena texto1, Cadena texto2){
// Reemplaza el texto1 por el texto2

	// Implementar
	
	return a;
}

// *************** Funciones nuevas ***************

int caracteres_MAX(Cadena nombre){
// Funcion auxiliar para calcular la cantidad de caracteres de una cadena
	int contador=0;
	while(nombre[contador] != '\0' && contador<99){
		contador++;
	}
	if(contador>=99){
		cout << "AVISO: Cadena nombre de car_max no es una string" << endl;
	}
	return contador;
}

void agrego_comienzo(Cadena nombreA, Cadena nombreB){
// Si esta dentro de los caracteres permitidos, copia la cadena B inmediatamente de la cadena A
	int contA, contB, contT, posA, posB;
	char contenido[15];
	contenido[0]='\0';

	contA = caracteres_MAX(nombreA);	
	contB = caracteres_MAX(nombreB);
	contT = contA + contB;

	//caracteres_MAX = CaracteresMax(nombreArchivo);
	if(contT >= 0 && contT < 15){
		//Modifica normalmente
		posA=0;
		while(nombreA[posA] != '\0' && posA<15){
			contenido[posA]=nombreA[posA];
			posA++;
		}
		posB=0;
		while(nombreB[posB] != '\0' && posA<15 && posB<15){
			contenido[posA]=nombreA[posB];
			posA++;
			posB++;
		}	
	}else if(contT >= 15 && contT < 22){
		//Extiende la cantidad max a la permitida
		//Idem anterior hasta 22 pero con aviso
		cout << "AVISO: Resultado truncado a cantidad maxima permitida" << endl;
	}else{
		cout << "AVISO: Overflow de caracteres_MAX" << endl;
	}	

	
}

void limpiar_memoria_arch(archivo a){
// Destruye la estructura del archivo "a"

	delete [] a->nombre;
	delete [] a->extension;
	delete [] a->texto;
	
	delete a;
	
}



