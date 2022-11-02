p2 :  p2.o historial.o lmem.o ayuda.o
	gcc -o p2  p2.o historial.o lmem.o ayuda.o
	echo "Compilación exitosa"  

historial.o : historial.h historial.c
	gcc -c historial.c

ayuda.o : ayuda.c
	gcc -c ayuda.c

lmem.o : lmem.h lmem.c
	gcc -c lmem.c

p2.o : p2.h p2.c
	gcc -c p2.c
	
limpar:
	rm p2 historial.o p2.o lmem.o
