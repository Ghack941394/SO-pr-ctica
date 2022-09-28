/*
Alumna 1 : Daniela Cisneros Sande
Alumna 2: Graciela Méndez Olmos

login 1: d.cisneross@udc.es
login 2: graciela.mendez.olmos@udc.es

*/

#include "p1.h"

//Variables GLOBAIs para 
//cadea recibida:
char *trozos[MAXTROZOS];
int numtrozos;
char linea[MAXLINEA];
//path 
char ruta[MAXPATHLEN];


//Función para comando autores [-l|-n]
void funAutores(){

        char* nomes[4] = {"Graciela Méndez Olmos", "Daniela Cisneros Sande", "graciela.mendez.olmos@udc.es", "d.cisneross@udc.es"};

        int flaglogin=1, flagnome=1;
        
        if (numtrozos>1){
                if(strcmp(trozos[1], "-l")==0)
                        flagnome = 0;
                if(strcmp(trozos[1], "-n")==0)
                        flaglogin = 0;
        }
        //Se só ponme autores
        if(numtrozos == 1)
                printf("%s:%s\n%s:%s\n",nomes[1],nomes[3],nomes[0],nomes[2]); 
        else{
                if(flaglogin)
                        printf("%s\n%s\n", nomes[2], nomes[3]);
                if(flagnome)
                        printf("%s\n%s\n", nomes[0], nomes[1]);                               
        }
}
//Función para pid [-p]
void funPid(){
	if (numtrozos == 1)
		printf("Pid de shell: %d\n", getpid());
	else if (strcmp(trozos[1],"-p")==0)  
		printf("Pid del padre shell: %d\n", getppid());
}

//Función para carpeta [directorio]
void funCarpeta(){
        if(getcwd(ruta, MAXPATHLEN)==NULL){ perror("getcwd"); exit(0);}
        if (numtrozos == 1)
                printf("El directorio actual es: %s\n", ruta);
        if(numtrozos > 1){
                if(chdir(trozos[1])==-1)
                        fprintf(stderr, " %s '%s'\n", strerror(2), trozos[1]);
                else
                        chdir(trozos[1]);
        }
} 

//Función para fecha [-f|-h]
void funFecha(){
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char fecha[MAXFyH];
	char hora[MAXFyH];

	strftime(hora, MAXFyH, "%H:%M:%S", tlocal);
	strftime(fecha, MAXFyH, "%d/%m/%y", tlocal);

	if (numtrozos == 1){
		printf("%s\n%s\n", hora, fecha);
	} else {
		if(strcmp(trozos[1], "-h")==0)
		printf("%s\n", hora);
		else if(strcmp(trozos[1], "-d")==0)
		printf("%s\n", fecha);
	}
}

//Función para historial [-h|-N]
void funHist(tList *listhistorial){
        int i=0, flagbal=0, n;
        tItemL d;
        tPosL p = first(*listhistorial);
        char* token;
        
        if(numtrozos == 1){
                while(p!=NULL){
                        d = getItem(p,listhistorial);
                        printf("%d->%s\n", i, *d.comando);
                        i++;
                        p = next(p,*listhistorial);
                } 
        }
        if(numtrozos>1){
                if(strcmp(trozos[1],"-c")==0)
                        flagbal=1;
                if(flagbal){
                        removeElement(listhistorial);
                        }
                else{
                        token = strtok(trozos[1], "-"); //consego unha cadea que so conteña o número
                        n = (int) strtol(token,NULL,10); // Converto a cadea a un enteiro numérico
                        
                        if(n<0)
                                fprintf(stderr, "%s\n", strerror(3));
                        else{
                                while(i!=n){
                                        d = getItem(p,listhistorial);
                                        printf("%d->%s\n", i, *d.comando);
                                        i++;
                                        p = next(p,*listhistorial);
                                }
                        }
                }       
        }        
}


//Función para infor do sistema
void funInfosis(){
	struct utsname infosisp;
	uname(&infosisp);
	
	printf("%s (%s), OS: %s-%s-%s\n", infosisp.nodename, infosisp.machine, infosisp.sysname, infosisp.release, infosisp.version);
}

//Función para comando ayuda [cmd]
void funAyuda(){
        int i, flagatopar = 0;
        if (numtrozos>1){
                for (i = 0; ; i++){
                        if (strcmp(tabla[i].nombre, trozos[1])==0){
                                printf("%s %s\n",trozos[1], tabla[i].info);
                        break;}
                        if (i >= 10){ flagatopar = 1; break;}
                }
                if (flagatopar)  printf(" '%s' no encontrado\n", trozos[1]);
        }  
        else{
                printf("'ayuda cmd' donde cmd es uno de los siguientes comandos:\n");
                printf("1.autores\n2.pid\n3.carpeta\n4.fecha\n5.hist\n");
                printf("6.infosis\n7.fin\n8.salir\n9.bye\n10.ayuda\n");
                printf("11.create\n");
        } 
        for (int j = 0; tabla[j].nombre!=NULL;j++)
                printf("%s\n",tabla[j].nombre);       
};

//Función para terminar execución
void funFin(tList *listhistorial){
        removeElement(listhistorial);
        exit(0);
}


//////////////////////// P1     /////////////////////////////////////////////////////////////////

char LetraTF (mode_t m)
{
     switch (m&S_IFMT) { /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l'; /*symbolic link*/
        case S_IFREG: return '-'; /* fichero normal*/
        case S_IFBLK: return 'b'; /*block device*/
        case S_IFDIR: return 'd'; /*directorio */ 
        case S_IFCHR: return 'c'; /*char device*/
        case S_IFIFO: return 'p'; /*pipe*/
        default: return '?'; /*desconocido, no deberia aparecer*/
     }
}

char * ConvierteModo3 (mode_t m)
{
    char *permisos;

    if ((permisos=(char *) malloc (12))==NULL)
        return NULL;
    strcpy (permisos,"---------- ");
    
    permisos[0]=LetraTF(m);
    if (m&S_IRUSR) permisos[1]='r';    /*propietario*/
    if (m&S_IWUSR) permisos[2]='w';
    if (m&S_IXUSR) permisos[3]='x';
    if (m&S_IRGRP) permisos[4]='r';    /*grupo*/
    if (m&S_IWGRP) permisos[5]='w';
    if (m&S_IXGRP) permisos[6]='x';
    if (m&S_IROTH) permisos[7]='r';    /*resto*/
    if (m&S_IWOTH) permisos[8]='w';
    if (m&S_IXOTH) permisos[9]='x';
    if (m&S_ISUID) permisos[3]='s';    /*setuid, setgid y stickybit*/
    if (m&S_ISGID) permisos[6]='s';
    if (m&S_ISVTX) permisos[9]='t';
    
    return permisos;
}    

//Función crear ficheiros ou directorios
void funCreate(){
        int fich, dir;
        
        if(strcmp(trozos[1],"-f")!=0){
                if((dir=mkdir(trozos[1],0775))==-1)
                        perror("No se ha podido crear el directorio.\n");
                
        }
        else{
                if((fich=creat(trozos[2], 0775))==-1)
                        perror("No se ha podido crear el archivo.\n");
        }
}

void funList(){
int flagreca=0, flagrecb=0, flaghid=0, flaglong=0, flaglink=0, flagacc=0

        //se é 1 ou non le, dir act?
  DIR *d;
  struct dirent *de;
  struct stat sb;
  struct group *grp;
  struct passwd *prop;
  
  int i;
  
  char name[MAXTROZOS], paux[PATH_MAX], paux1[PATH_MAX*2];
  char *modo, fecha[DATA], *feca, *fecm, enlace[PATH_MAX], enlace2[PATH_MAX]; 
  
  for (i = 1; i< numtrozos && trozos[i][0] == '-' ; i++){
    if(strcmp(trozos[k], "-long")==0)
      flaglong = 1;
    if(strcmp(trozos[k], "-link")==0) 
      flaglink = 1;
    if(strcmp(trozos[k], "-acc")==0)
      flagacc = 1;
    if(strcmp(trozos[k], "-hid")==0)
      flaghid = 1;
    if(strcmp(trozos[k], "-reca")==0) 
      flagreca = 1;
    if(strcmp(trozos[k], "-recb")==0)
      flagrecb = 1;
   }
   
   if
  
  /*for(p=i; p<numtrozos; p++ ){
    if(strcmp(trozos[p],nom)==0){
      d = opendir(trozos[p]);
      strcpy(name,strcat(strcpy(name,"/"), trozos[p]));
      strcpy(paux, strcat(strcpy(paux, ruta), name));
      }
    else{
      d = opendir(nom);
      strcpy(name,strcat(strcpy(name,"/"), nom));
      strcpy(paux, strcat(paux, name));
      }
    printf("%d\n",i);
    if(d==NULL){
      if(stat(paux,&sb) == -1)
        fprintf(stderr, "****error al acceder a %s: %s\n", nom, strerror(errno));
      else
      	if(LetraTF(sb.st_mode)!= 'd')
      	 cmdListfich();
      return; //continue;
    }
    
    printf("************%s\n",nom);
    
    strcpy(paux,strcat(paux,"/"));
    
    while( (de = readdir(d)) != NULL ) {
      
      sprintf(paux1,"%s/%s", paux, de->d_name);
  
      if(stat(paux1, &sb) == -1){
        perror("stat");
        continue;
      }
      
      l = i;
      modo = ConvierteModo(sb.st_mode);
      fecm = data(fecha, sb.st_mtime);
      feca = data(fecha, sb.st_atime);
      grp = getgrgid(sb.st_gid);
      prop = getpwuid(sb.st_uid);
      if(grp == NULL)
        perror("grupo");
      if(prop == NULL)
        perror("usuario");
        */
        

}











//Función para trocear a cadea de entrada
int TrocearCadena(char * cadena, char * trozos[]){
        int i=1;
        if ((trozos[0]=strtok(cadena," \n\t"))==NULL)
                return 0;
        while ((trozos[i]=strtok(NULL," \n\t"))!=NULL)
                i++;
        return i;
}

//Main

int main(){
        tList listhistorial;
        createList(&listhistorial);
        int i;
        tItemL d;

        while(1){
                printf("~€ ");
                if(fgets(linea, MAXLINEA,stdin)==NULL) 
                        exit(1);
                //copio en d a cadea de entrada para insetar os comandos ó historial
                strcpy(*d.comando, linea); 
                numtrozos= TrocearCadena(linea,trozos);
                if (numtrozos==0)
                        continue;
                for (i = 0; ; i++){
                        if(comandos[i].nombre==NULL){
                                if (strcmp(trozos[0],"hist")==0){
                                        insertElement(d, &listhistorial);
                                        funHist(&listhistorial);
                                        break;
                                }
                                else if(strcmp(trozos[0],"fin")==0||strcmp(trozos[0],"bye")==0||strcmp(trozos[0],"salir")==0){
                                        insertElement(d, &listhistorial);
                                        funFin(&listhistorial);
                                }
                                else{
                                        fprintf(stderr, "%s '%s'\n", strerror(3), trozos[0] );
                                        insertElement(d, &listhistorial);
                                        break;
                                }
                        }
                        if (strcmp(comandos[i].nombre, trozos[0])==0){  
                                comandos[i].pfun();
                                insertElement(d, &listhistorial);
                                break;
                        }
                }
        }
}    


