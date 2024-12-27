CFLAG = -Wall -O2

todo: main.o archivo.o archivos.o directorio.o directorios.o sistema.o
	g++ -o prog main.o archivo.o archivos.o directorio.o directorios.o sistema.o $(CFLAG)
main.o: main.c
	g++ -c main.c $(CFLAG)
archivo.o: archivo.h archivo.c
	g++ -c archivo.c $(CFLAG)
archivos.o: archivos.h archivos.c 
	g++ -c archivos.c $(CFLAG)
directorio.o: directorio.h directorio.c
	g++ -c directorio.c $(CFLAG)
directorios.o: directorios.h directorios.c
	g++ -c directorios.c $(CFLAG)
sistema.o: sistema.h sistema.c
	g++ -c sistema.c $(CFLAG)
limpiar:
	rm *.o
	rm prog

