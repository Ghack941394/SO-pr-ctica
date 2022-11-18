#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/param.h>
#include <time.h>
#include <sys/utsname.h>
#include <math.h>
#include <errno.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <pwd.h>
#include <dirent.h>
#include <grp.h>
#include <fcntl.h>
#include "historial.h"
#include "lmem.h"
#include<sys/shm.h>
#include<sys/mman.h>
#include<sys/ipc.h>
#include <sys/wait.h>
#include <ctype.h>

#define DATA 32
#define MAXLINEA 4096
#define MAXTROZOS 1028
#define MAXFyH 128
#define NAMEMAX 1024
#define TAMANO 2048

void funAutores();
void funFecha();
void funAyuda();
void funPid();
void funInfosis();
void funCarpeta();
void funFin(tList *L, tListMem *Lm);
void funHist(tList *L);
void funCreate();
void funList();
void funStat();
void funDelete();
void funDeltree();
void funAlloc(tListMem *L);
void funIo();
void funMemDump();
void funMemFill();
void funMemory(tListMem *L);
void funRecursiva();

struct cmd {
  char *nombre;
  void (*pfun)();
};

struct ax {
  char *nombre;
  char *info;
};

struct cmd comandos[] = {
        {"ayuda",funAyuda}, 
        {"fecha",funFecha},
        {"autores",funAutores},
        {"pid",funPid},
        {"infosis",funInfosis},
        {"carpeta",funCarpeta},
        {"create",funCreate},
        {"list", funList},
        {"stat",funStat},
        {"delete",funDelete},
        {"deltree", funDeltree},
        {"i-o",funIo},
        {"e-s",funIo},
        {"i/o",funIo},
        {"e/s",funIo},
        {"memdump", funMemDump},
        {"memfill", funMemFill},
        {"recursiva",funRecursiva},
        {NULL,NULL},
};

struct ax tabla[] = {
  {"fecha"," [-d|.h	Muestra la fecha y o la hora actual"},
  {"autores"," [-n|-l]	Muestra los nombres y logins de las autoras"},
  {"pid"," [-p]	Muestra el pid del shell o de su proceso padre"},
  {"hist", " [-c|-N]	Muestra el historico de comandos, con -c lo borra"},
  {"carpeta", " [dir] Cambia (o muestra) el directorio actual del shell"},
  {"infosis", " Muestra informacion de la maquina donde corre el shell"},
  {"ayuda", " [cmd]	Muestra ayuda sobre los comandos"},
  {"fin"," Termina la ejecucion del shell"},
  {"bye"," Termina la ejecucion del shell"},
  {"salir"," Termina la ejecucion del shell"},
  {"create"," [-f] [name]    Crea un directorio o un fichero (-f)"},
  {"stat"," [-long] [-acc] [-link] name1 name2 ..  	lista ficheros;\n\t-long: listado largo\n\t-acc: acesstime\n\t-link: si es enlace simbolico, el path contenido"},
  {"list", " [-reca] [-recb] [-hid][-long][-link][-acc] n1 n2 ..	lista contenidos de directorios\n-hid: incluye los ficheros ocultos\n-reca: recursivo (antes)\n-recb: recursivo (despues)\nresto parametros como stat"},
  {"delete", " [name1 name2 ..] Borra ficheros o directorios vacios"},
  {"deltree", " [name1 name2 ..] Borra ficheros o directorios no vacios recursivamente"},
  {NULL,NULL},
};

