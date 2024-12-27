// Estructuras de Datos y Algoritmos - Curso 2023
// Trabajo Obligatorio
// sistema.c
// Modulo de Implementacion del File System.

#include "sistema.h"

#include <iostream>

using namespace std;


struct nodo_sistema{
	Cadena usr;
	directorios RAIZ;	
	directorios actual;	
};

// *************** Funciones selectoras ***************

directorios Ret_Dir_RAIZ(Sistema s){
// Retorna el directorio RAIZ.
	return s->RAIZ;
}

directorios Ret_Dir_Actual(Sistema s){
// Retorna el directorio actual.
	return s->actual;
}

// *************** Funciones constructoras ***************

TipoRet CREARSISTEMA(Sistema &s){
// Inicializa el sistema para que contenga únicamente al directorio RAIZ, sin subdirectorios ni archivos.
// Para mas detalles ver letra.
	s = new(nodo_sistema);
	Cadena nombre = new char[MAX_NOMBRE];
	s->usr = new char[MAX_NOMBRE];
	strcpy(s->usr, "LINUX");
	strcpy(nombre, "RAIZ");
	s->RAIZ = crear_directorio(nombre);
	delete [] nombre;
	s->actual = s->RAIZ;
	return OK;
}

TipoRet DESTRUIRSISTEMA(Sistema &s){
// Destruye el sistema, liberando la memoria asignada a las estructuras que datos que constituyen el file system.
// Para mas detalles ver letra.
	/* Destruir_Directorio(s->RAIZ);
	s->RAIZ = destruir_directorio(s->RAIZ);
	delete s;
	*/
	return NO_IMPLEMENTADA;
}

TipoRet RMDIR (Sistema &s, Cadena nombreDirectorio){
// Elimina un directorio.
// Para mas detalles ver letra.
	return NO_IMPLEMENTADA;
}

TipoRet MOVE (Sistema &s, Cadena nombre, Cadena directorioDestino){
// mueve un directorio o archivo desde su directorio origen hacia un nuevo directorio destino.
// Para mas detalles ver letra.
	return NO_IMPLEMENTADA;
}

TipoRet DIR (Sistema &s, Cadena parametro){
// Muestra el contenido del directorio actual.
	directorios aux;
	//Pido carpeta contenido
	aux = Ret_Directorios_actual(s);
	//IMPRIME ARCHIVOS ACTUAL
	
	/*
	if((strcmp(parametro, "/S")==0) || (strcmp(parametro, "/s")==0)){
		cout << "NO_IMPLEMENTADA" << endl;
	}
	else{
		//imprimir_path(s->actual);
		//cout << endl;
	*/
		if(Ret_Dir_d(aux) != NULL){
			if(Ret_listaA_dir(Ret_Dir_d(aux)) != NULL){
				imprime_listaARCH(Ret_listaA_dir(Ret_Dir_d(aux)));
			}else{
				cout << " - [vacio]" << endl;
			}
		}
		//IMPRIME NOMBRE CARPETAS DE ACTUAL
		if(Ret_Dir_hijo(aux) != NULL){
			aux=Ret_Dir_hijo(aux);
				//Caso 1 elemento (siempre existe al menos 1)
			if(Ret_Dir_sig(aux) == NULL && Ret_Dir_ant(aux) == NULL){
				if(Ret_Dir_d(aux) != NULL){
					imprime_cadenaDIR(Ret_Dir_d(aux));
				}else{
					cout << "Elemento unico vacio" << endl;
				}
			}else{
				//Caso 2: mas de uno 
				while(Ret_Dir_sig(aux) != NULL){
					if(Ret_Dir_d(aux)!= NULL)
						imprime_cadenaDIR(Ret_Dir_d(aux));
					aux=Ret_Dir_sig(aux);
				}
				if(Ret_Dir_d(aux)!=NULL)
					imprime_cadenaDIR(Ret_Dir_d(aux));			
			}
		}else{
			cout << "MENSAJE: directorio de carpetas vacio" << endl;
		}
	//}
	return OK;
}

TipoRet IC (Sistema &s, Cadena nombreArchivo, Cadena texto){
// Agrega un texto al inicio del archivo NombreArchivo.
// Para mas detalles ver letra.
	
	TipoRet Ret;
	int permisos;
	Cadena extenAR = new (char[MAX_EXTENSION]);
	extenAR=obtener_extension(nombreArchivo);
	archivos lista=Ret_ListaAr(Ret_Dir_d(Ret_Directorios_actual(s)));
	archivo a;
	
	bool encontrado = arch_existente(lista,nombreArchivo, extenAR);
	
	if(encontrado){
		a=buscar_y_retornar(lista, nombreArchivo, extenAR);
		permisos = Ret_artAR(a);
		if(permisos == 666){
			//agrego_comienzo(nombreArchivo, texto);
			texto_al_principio(s, a, texto);
			Ret=OK;
		}else{
			cout << " - No tienes los permisos, hable con el admin" << endl;
			Ret=ERROR;
		}
	}else{
		cout << " - No se ha encontrado el archivo" << endl;
		Ret=ERROR;
	}
	return Ret;
}

TipoRet IF (Sistema &s, Cadena nombreArchivo, Cadena texto){
// Agrega un texto al final del archivo NombreArchivo.
	
	TipoRet Ret;
	int permisos;
	Cadena extenAR = new (char[MAX_EXTENSION]);
	extenAR=obtener_extension(nombreArchivo);
	archivos lista=Ret_ListaAr(Ret_Dir_d(Ret_Directorios_actual(s)));
	archivo a;
	
	bool encontrado = arch_existente(lista,nombreArchivo, extenAR);
	
	if(encontrado){
		a=buscar_y_retornar(lista, nombreArchivo, extenAR);
		permisos = Ret_artAR(a);
		if(permisos == 666){
			texto_al_final(s, a, texto);
			Ret=OK;
		}else{
			cout << " - No tienes los permisos, hable con el admin" << endl;
			Ret=ERROR;
		}
	}else{
		cout << " - No se ha encontrado el archivo" << endl;
		Ret=ERROR;
	}
	return Ret;
}

TipoRet TYPE (Sistema &s, Cadena nombreArchivo){
// Imprime el contenido del archivo parámetro.
// Para mas detalles ver letra.

	TipoRet Ret;	
	Cadena extenAR = new (char[MAX_EXTENSION]);
	archivos lista=Ret_ListaAr(Ret_Dir_d(s->actual));
	archivo a;
	
	extenAR=obtener_extension(nombreArchivo);
	
	if(arch_existente(lista, nombreArchivo, extenAR)){ // Si el archivo existe, imprimo el contenido
		a=buscar_y_retornar(lista, nombreArchivo, extenAR);
		impr_contenido(a);
		Ret=OK;
	}
	else{
		cout << " - El el archivo no existe en el directorio actual." << endl;
		Ret=ERROR;
	}
	return Ret;

}

// *************** Funciones nuevas ***************
	
TipoRet MKDIR (Sistema &s, Cadena nombreDirectorio){
// Crea un nuevo directorio. 
// Para mas detalles ver letra.

	TipoRet Ret;
	directorios nuevo;
	
	
	if((strcmp(nombreDirectorio, "RAIZ")==0) || (strcmp(nombreDirectorio, "raiz")==0)){// Si quiero ir al RAIZ
		cout << " - olo puede existir un unico directorio RAIZ" << endl;
		Ret=ERROR;	
	}
	else if(dir_existente(s, nombreDirectorio)){		// Si el directorio es hijo del actual
		cout << " - Ya existe el directorio: " << nombreDirectorio << " en el directorio actual" << endl;
		Ret=ERROR;
	}
	else{						// No existe o no es hijo del actual
		nuevo=crear_directorio(nombreDirectorio);
		ins_directorio(s, nuevo);
		Ret=OK;
	}
	
	return Ret;
	
}

TipoRet CD (Sistema &s, Cadena nombreDirectorio){
// Cambia directorio. 
// Para mas detalles ver letra.

	TipoRet Ret;

	if((strcmp(nombreDirectorio, "..")==0)){		// Si quiero ir al directorio padre del actual
		if(s->actual==s->RAIZ){ 
			cout << " - Ya se encuentra en el directorio RAIZ" << endl;
			Ret=ERROR;
		}
		else{
			s->actual=Ret_Dir_padre(s->actual);
			Ret=OK;	
		}
	}
	else if((strcmp(nombreDirectorio, "RAIZ")==0) || (strcmp(nombreDirectorio, "raiz")==0)){// Si quiero ir al RAIZ
			s->actual=s->RAIZ;
			Ret=OK;	
	}
	else{						// Si quiero ir a un directorio especifico
		if(dir_existente(s, nombreDirectorio)){		// Si el directorio es hijo del actual
			s->actual=cambiar_directorio(s, nombreDirectorio);
			Ret=OK;
		}
		else{						// No existe o no es hijo del actual
			cout << " - No existe el directorio: ´" << nombreDirectorio << "´ en el directorio actual" << endl;
			Ret=ERROR;
		}
	}
	return Ret;

}

TipoRet CREATEFILE (Sistema &s, Cadena nombreArchivo){
// Crea un nuevo archivo en el directorio actual.
// Para mas detalles ver letra.
	
	//TipoRet Ret;
	archivo a;						// Creo una variable para guardar el archivo
	archivos lista=Ret_ListaAr(Ret_Dir_d(s->actual));
	Cadena extenAR = new (char[MAX_EXTENSION]);

	extenAR=obtener_extension(nombreArchivo);
	if(arch_existente(lista, nombreArchivo, extenAR)){ 	// Si el archivo ya existe
		cout << " - Ya existe el archivo "; //nombreArchivo << "." <<  extenAR << " en el directorio actual." << endl;
		cout << "ERROR DESCONOCIDO";
	}
	else{
		a=crear_archivo(nombreArchivo, extenAR);	// Creo el archivo
		ins_archivo(s, a);				// Inserto el archivo
		cout << "ARCHIVO INSERTADO";
	}
	
	return OK;

}

TipoRet DELETE (Sistema &s, Cadena nombreArchivo){
// Elimina un archivo del directorio actual, siempre y cuando no sea de sólo lectura.
// Para mas detalles ver letra.
	
	TipoRet Ret;
	Cadena extenAR = new (char[MAX_EXTENSION]);
	archivos lista=Ret_ListaAr(Ret_Dir_d(s->actual));
	archivo a;
	int permiso;
	
	extenAR=obtener_extension(nombreArchivo);
	
	if(arch_existente(lista, nombreArchivo, extenAR)){
		a=buscar_y_retornar(lista, nombreArchivo, extenAR);
		permiso=Ret_artAR(a);
		if(permiso==666){
			eliminar_archivo(s, a);	
			Ret=OK;
		}
		else{
			cout << " - No se puede elimiar un archivo de 'Solo Letura'" << endl;
			Ret=ERROR;
		}
	}
	else{
		cout << " - No existe el archivo " << nombreArchivo << "." <<  extenAR << " en el directorio actual." << endl;
		Ret=ERROR;
	}
	return Ret;
}


TipoRet SEARCH (Sistema &s, Cadena nombreArchivo, Cadena texto){
// Busca dentro del archivo la existencia del texto.
// Para mas detalles ver letra.

	TipoRet Ret;	
	Cadena extenAR = new (char[MAX_EXTENSION]);
	archivos lista=Ret_ListaAr(Ret_Dir_d(s->actual));
	archivo a;
	bool existe=false;
	
	extenAR=obtener_extension(nombreArchivo);

	if(arch_existente(lista, nombreArchivo, extenAR)){ 	// Si el archivo existe
		a=buscar_y_retornar(lista, nombreArchivo, extenAR);
		existe=search_text(a, texto);
		if(existe)
			Ret=OK;
		else{
			cout << " - El texto no se encuentra en el archivo" << endl;
			Ret=ERROR;
		}
	}
	else{
		cout << " - El archivo no existe" << endl;
		Ret=ERROR;
	}

	return Ret;
}

TipoRet REPLACE (Sistema &s, Cadena nombreArchivo, Cadena texto1, Cadena texto2){
// Busca y reemplaza dentro del archivo la existencia del texto1 por el texto2. 
// Para mas detalles ver letra.

	TipoRet Ret;	
	Cadena extenAR = new (char[MAX_EXTENSION]);
	archivos lista=Ret_ListaAr(Ret_Dir_d(s->actual));
	archivo a;
	bool existe=false;
	
	extenAR=obtener_extension(nombreArchivo);

	if(arch_existente(lista, nombreArchivo, extenAR)){ 	// Si el archivo existe
		a=buscar_y_retornar(lista, nombreArchivo, extenAR);
		existe=search_text(a, texto1);
		if(existe){
			reemplazar_texto(s, a, texto1, texto2);
			Ret=OK;
		}
		else{
			cout << " - El texto no se encuentra en el archivo" << endl;
			Ret=ERROR;
		}
	}
	else{
		cout << " - El archivo no existe" << endl;
		Ret=ERROR;
	}

	return Ret;
}

TipoRet ATTRIB (Sistema &s, Cadena nombreArchivo, Cadena parametro){
// Cambia los atributos de un archivo perteneciente al directorio actual con "+W" agrefa "escritura" con "-W" quita "Escritura".
// Para mas detalles ver letra.

	TipoRet Ret;	
	Cadena extenAR = new (char[MAX_EXTENSION]);
	archivos lista=Ret_ListaAr(Ret_Dir_d(s->actual));
	archivo a;
	
	extenAR=obtener_extension(nombreArchivo);
	
	if(arch_existente(lista, nombreArchivo, extenAR)){ // Si el archivo existe
		a=buscar_y_retornar(lista, nombreArchivo, extenAR);
		act_archivo(s, a, parametro);
		Ret=OK;
	}
	else{
		cout << " - El el archivo no existe en el directorio actual." << endl;
		Ret=ERROR;
	}
	return Ret;
}

TipoRet DC (Sistema &s, Cadena nombreArchivo, int k){
// Elimina los a lo sumo K primeros caracteres del archivo parámetro.
// Para mas detalles ver letra.
	
	TipoRet Ret;					// Variable de retorno del sistema
	Cadena extenAR = new (char[MAX_EXTENSION]);	// Variable para guardar extension
	archivos lista=Ret_ListaAr(Ret_Dir_d(s->actual));// Obtengo la lista de archivos
	archivo a;
	int permiso;
	
	extenAR=obtener_extension(nombreArchivo);	// Obtengo la extension del archivo
	
	if(arch_existente(lista, nombreArchivo, extenAR)){ // Si el archivo existe
		a=buscar_y_retornar(lista, nombreArchivo, extenAR);// Guardo el archivo a modificar en "a"
		permiso=Ret_artAR(a);
		if(permiso==666){			// Archivo de "Lectura/Escritura"
			quitar_al_principio(s, a, k);	// Funcion auxiliar en archivo.c	
			Ret=OK;
		}
		else{					// Archivo de solo "Lectura"
			cout << " - No se puede modificar un archivo de 'Solo Letura'" << endl;
			Ret=ERROR;
		}
	}
	else{						// El archivo no existe
		cout << " - El archivo no existe en el directorio actual." << endl;
		Ret=ERROR;
	}
	return Ret;
}

TipoRet DF (Sistema &s, Cadena nombreArchivo, int k){
// Elimina los a lo sumo K últimos caracteres del archivo parámetro.
// Para mas detalles ver letra.
	
	TipoRet Ret;					// Variable de retorno del sistema
	Cadena extenAR = new (char[MAX_EXTENSION]);	// Variable para guardar extension
	archivos lista=Ret_ListaAr(Ret_Dir_d(s->actual));// Obtengo la lista de archivos
	archivo a;
	int permiso;
	
	extenAR=obtener_extension(nombreArchivo);	// Obtengo la extension del archivo
	
	if(arch_existente(lista, nombreArchivo, extenAR)){ // Si el archivo existe
		a=buscar_y_retornar(lista, nombreArchivo, extenAR);// Guardo el archivo a modificar en "a"
		permiso=Ret_artAR(a);
		if(permiso==666){			// Archivo de "Lectura/Escritura"
			quitar_al_final(s, a, k);	// Funcion auxiliar en archivo.c	
			Ret=OK;
		}
		else{					// Archivo de solo "Lectura"
			cout << " - No se puede modificar un archivo de 'Solo Letura'" << endl;
			Ret=ERROR;
		}
	}
	else{						// El archivo no existe
		cout << " - El archivo no existe en el directorio actual." << endl;
		Ret=ERROR;
	}
	return Ret;
	
}


//--------x---------// NUEVAS

directorios Ret_Directorios_actual(Sistema s){
// Retorna el directorios actual del sistema s.
	return s->actual;
}




