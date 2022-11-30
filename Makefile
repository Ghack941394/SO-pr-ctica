p3 :  p3.o historial.o lmem.o 
	gcc -o p3  p3.o historial.o lmem.o 
	echo "Compilación exitosa"  

historial.o : historial.h historial.c
	gcc -c historial.c

lmem.o : lmem.h lmem.c
	gcc -c lmem.c

p3.o : p3.h p3.c
	gcc -c p3.c
	
limpar:
	rm p3 historial.o p3.o lmem.o
