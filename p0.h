
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

#define DATA 32
#define MAXLINEA 4096
#define MAXTROZOS 1028
#define MAXPATHLEN PATH_MAX

void funAutores();
void funFecha();
void funAyuda();
void funPid();
void funInfosis();
void funCarpeta();
void funFin(tList *L);
void funHist(tList *L);

struct cmd {
  char *nombre;
  void (*pfun)();
};

struct cmd comandos[] = {
        {"ayuda",funAyuda}, 
        {"fecha",funFecha},
        {"autores",funAutores},
        {"pid",funPid},
        {"infosis",funInfosis},
        {"carpeta",funCarpeta},
        {NULL,NULL},
};


