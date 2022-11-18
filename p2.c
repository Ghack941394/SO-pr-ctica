/**
 * TITLE: Lab Assignment 1
 * @author Daniela Cisneros Sande @login: d.cisneross
 * @author Graciela Méndez Olmos @login: graciela.mendez.olmos@udc.es
 * GROUP: 4.1
 * DATE: 21 / 10 / 2022
 */

#include "p2.h"

/*Variables Globales*/

char *trozos[MAXTROZOS]; //Array para guardar y luego leer lo cada uno de los trozos escritos por terminal 
int numtrozos;           //Lleva la cuenta del numero de palabras introducidas
char linea[MAXLINEA];    //Guarda absolutamente todo lo escrito por terminal 
char ruta[PATH_MAX];     //Array para guardar el path 


/**
 * Function: funAutores
 * ----------------------
 * Prints the names and logins
 * of the program autors. 
 *
 * Opcions: 
 *      [-l] Prints only the logins. 
 *      [-n] Prints only the names. 
 *
 * @return void.
 */
void funAutores(){
        char* nomes[4] = {"Graciela Méndez Olmos", "Daniela Cisneros Sande", "graciela.mendez.olmos@udc.es", "d.cisneross@udc.es"}; 
        int flaglogin=1, flagnome=1; 
        
        //Verificamos si nos introducen alguna opcion del comando
        if (numtrozos>1){ 
                if(strcmp(trozos[1], "-l")==0){
                        flagnome = 0;
                }
                if(strcmp(trozos[1], "-n")==0){
                        flaglogin = 0;
                }
        }
        //Si solo llama al comando "autores" mostramos los nombres y los logins
        if(numtrozos == 1){
                printf("%s:%s\n%s:%s\n",nomes[1],nomes[3],nomes[0],nomes[2]);
        } else {
                if(flaglogin){
                        printf("%s\n%s\n", nomes[2], nomes[3]); //Opcion -> -l
                } if(flagnome){
                        printf("%s\n%s\n", nomes[0], nomes[1]); //Opcion -> -n
                }                                          
        }
}

/**
 * Function: funPid
 * ----------------------
 * Prints the pid of the process 
 * executing the shell. 
 *
 * Opcions: 
 *      [-p] Prints the pid of the 
 *           shell’s parent process.
 *
 * @return void.
 */
void funPid(){
	if (numtrozos == 1){
                printf("Pid de shell: %d\n", getpid());
        } else if (strcmp(trozos[1],"-p")==0){
                printf("Pid del padre shell: %d\n", getppid());
        } 		
}

/**
 * Function: funCarpeta
 * ----------------------
 * Prints the current working 
 * directory.
 *
 * Opcions: 
 *      [direct] Changes the current 
 *               working directory of 
 *               the shell to direct.                
 *
 * @return void.
 */
void funCarpeta(){       
        if(getcwd(ruta, PATH_MAX)==NULL){ //envia NULL si el nombre del directorio supera el tamaño de la memoria 
                fprintf(stderr, "%s '%s'\n", strerror(errno),trozos[1]);   
        }                                           
        
        if (numtrozos == 1){
                printf("El directorio actual es: %s\n", ruta);
        } else if(numtrozos > 1){ //si se le manda mas de una palabra al comando
                if(chdir(trozos[1]) != 0){ //si no logra hacer el cambio del directorio muestra un error
                        fprintf(stderr, " %s '%s'\n", strerror(2), trozos[1]);
                } 
        }
} 

/**
 * Function: funFecha
 * ----------------------
 * Prints the current date and 
 * the current time.
 *
 * Opcions: 
 *      [-d] Prints only the current date. 
 *      [-h] Prints only the current time.                
 *
 * @return void.
 */
void funFecha(){
	time_t tiempo = time(0);
	struct tm *tlocal = localtime(&tiempo);
	char fecha[MAXFyH];
	char hora[MAXFyH];

        //Ponemos el formato que queremos
	strftime(hora, MAXFyH, "%H:%M:%S", tlocal);  
	strftime(fecha, MAXFyH, "%d/%m/%y", tlocal);

	if (numtrozos == 1){
		printf("%s\n%s\n", hora, fecha);
	} else {
		if(strcmp(trozos[1], "-h")==0){
		        printf("%s\n", hora);
                } else if(strcmp(trozos[1], "-d")==0){
                        printf("%s\n", fecha);
                }
	}
}

/**
 * Function: funHist
 * ----------------------
 * Shows/clears the historic of 
 * commands executed by this shell.
 *
 * Opcions: 
 *      [-c] Clears (empties) the list 
             of historic commands. 
 *      [-N] Prints the first N comands.                
 *
 * @return void.
 */
void funHist(tList *listhistorial){
        int numLista=0, flagbal=0, n;
        tItemL d;
        tPosL pos = first(*listhistorial);
        char* token;
        
        if(numtrozos == 1){
                while(pos != NULL){ //mientras la lista no llegue al final y no este vacia
                        d = getItem(pos,listhistorial);
                        printf("%d->%s\n", numLista, *d.comando);
                        numLista++;
                        pos = next(pos,*listhistorial);
                } 
        }
        if(numtrozos > 1){
                if(strcmp(trozos[1],"-c")==0){
                        flagbal=1;
                }

                if(flagbal){
                        removeElement(listhistorial);
                } else {
                        token = strtok(trozos[1], "-");  //borramos el "-" para solo tener el numero.
                        n = (int) strtol(token, NULL, 10); //convertimos el numero obtenido como string a un entero numerico
                        if(n < 0){
                                fprintf(stderr, "%s\n", strerror(3));
                        } else {
                                while(numLista != n){
                                        d = getItem(pos,listhistorial);
                                        printf("%d->%s\n", numLista, *d.comando);
                                        numLista++;
                                        pos = next(pos,*listhistorial);
                                }
                        }
                }       
        }        
}


/**
 * Function: funInfosis
 * ----------------------
 * Prints information on the machine 
 * running the shell.
 *
 * @return void.
 */
void funInfosis(){
	struct utsname infosisp;
	uname(&infosisp);
	
	printf("%s (%s), OS: %s-%s-%s\n", infosisp.nodename, infosisp.machine, infosisp.sysname, infosisp.release, infosisp.version);
        //nodename: nombre del nodo dentro de la red           machine: identificador del hardware
        //sysname: nombre del sistema operativo                release: lanzamiento del sistema operativo
}

/**
 * Function: funAyuda
 * ----------------------
 * Displays a list of available commands.
 *
 * Opcions: 
 *      [cmd] Gives a brief help on the 
              usage of comand cmd.
 *            
 * @return void.
 */
void funAyuda(){
        int i, flagatopar = 0;
        if (numtrozos > 1){
                for (i = 0; ; i++){
                        if (strcmp(tabla[i].nombre, trozos[1])==0){
                                printf("%s %s\n",trozos[1], tabla[i].info);
                                break;
                        }
                        
                        if (i >= 13){
                                 flagatopar = 1; 
                                 break;
                        }
                }
                
                if (flagatopar){
                        printf(" '%s' no encontrado\n", trozos[1]);
                } 
        } else {
                printf("'ayuda cmd' donde cmd es uno de los siguientes comandos:\n");
                printf("1.autores\n2.pid\n3.carpeta\n4.fecha\n5.hist\n");
                printf("6.infosis\n7.fin\n8.salir\n9.bye\n10.ayuda\n");
                printf("11.create\n12.stat\n13.list\n14.delete\n15.deltree\n");
        } 
}

/**
 * Function: funFin
 * ----------------------
 * Function that serves to end 
 * the execution of the shell.
 *            
 * @return void.
 */
void funFin(tList *listhistorial, tListMem *listmemoria){
        removeElement(listhistorial);
        tPosMem p=firstm(*listmemoria);
        while (p!=NULL){
                removeElementm(listmemoria, p);
                p = nextm(p,*listmemoria);
        }       
        exit(0);
}

//////////////////////////////////// P1 ///////////////////////////////////////////

/**
 * Function: LetraTF
 * ----------------------
 * Checks mode of the file and
 * returns the corresponding letter.
 *
 * @return Mode letter.
 */
char LetraTF (mode_t m)
{
     switch (m&S_IFMT) {           /*and bit a bit con los bits de formato,0170000 */
        case S_IFSOCK: return 's'; /*socket */
        case S_IFLNK: return 'l';  /*symbolic link*/
        case S_IFREG: return '-';  /*normal file*/
        case S_IFBLK: return 'b';  /*block device*/
        case S_IFDIR: return 'd';  /*directorio */ 
        case S_IFCHR: return 'c';  /*char device*/
        case S_IFIFO: return 'p';  /*pipe*/
        default: return '?';       /*desconocido, no deberia aparecer*/
     }
}

/**
 * Function: ConvierteModo
 * ----------------------
 * Checks permissions of files and returns 
 * the corresponding string.
 *
 * @param m File mode.
 * @param permisos String.
 * @return Updated string with the
 *         corresponding permissions.
 */
char * ConvierteModo (mode_t m, char *permisos){
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

/**
 * Function: funCreate
 * ----------------------
 * Creates files or directories.
 *
 * Opcions: 
 *      [-f] Create a file.             
 *            
 * @return void.
 */
void funCreate(){
        int fich, dir;
        
        if(strcmp(trozos[1], "-f") != 0){ //si no se le introduce -f
                if((dir = mkdir(trozos[1], 0775)) == -1){ //se crea el directorio con los permisos comunes, si falla dara -1
                        perror("No se ha podido crear el directorio.\n");
                }       
        } else {
                if((fich = creat(trozos[2], 0775)) == -1) //se crea el fichero con los permisos comunes, si falla dara -1
                        perror("No se ha podido crear el archivo.\n");
        }
}

/**
 * Function: funStatAux
 * ----------------------
 * Gives information on files 
 * or directories.
 *
 * @param name File or directory name,
 *             type string. 
 * @param Acc options indicator 
 *            type int.
 * @param Link options indicator 
 *             type int.
 * @param Long options indicator 
 *             type int.    
 * @return void.
 */        
void funStatAux(char *name, int Acc, int Link, int Long){
        char *apunta_a;                                    
        char *permisos = malloc(sizeof(char)*PATH_MAX);    
        char buffer[PATH_MAX];                             
        struct tm *time;
        struct stat buf; 
        struct passwd *p;
        struct group *g;
        ssize_t bufsiz, nbytes;

        //examinamos el fichero al que apunta name y si es un enlace simbolico examina el enlace y llena el buf
        if(lstat(name, &buf) == 0){
                time = localtime(&buf.st_mtime); //ultima modificacion 

                if(Acc){
                        time = localtime(&buf.st_atime);//ultimo acceso
                        strftime(buffer, sizeof(buffer), "%Y/%m/%d-%H:%M", time); //indicamos el formato que queremos

                        if(!(Long) && !(Link)){ //si solo ponemos como opcion -acc 
                                printf("%s" , buffer); //mostrara unicamente la ultima hora de acceso y el nombre con el tamaño de dicho fichero
                        }
                }
                strftime(buffer, sizeof(buffer), "%Y/%m/%d-%H:%M", time); //indicamos el formato que queremos

                p = getpwuid(buf.st_uid); // obtenemos el id del usuario propietario
                g = getgrgid(buf.st_gid); //obtenemos el id del grupo propietario
                
                if(p == NULL ||  g == NULL){
                        perror("Error: pxd"); 
                }

                if ((Long && Acc) || Long){ 
                        ConvierteModo(buf.st_mode, permisos); //ponemos los permisos correspondientes en el string
                        printf("%s" , buffer); //imprimimos la fecha y hora 
                        printf("   %ld (%ld)     %s     %s   %s", buf.st_nlink, buf.st_ino, p->pw_name, g->gr_name, permisos);
                        //st_nlink: numero de enlaces fisicos.                 st_ino: inodo  
                        //p->pw_name: user name                                gr_name: group name
                        free(permisos);
                }
                printf("       %ld %s\n", buf.st_size, name); //imprimimos el tamaño y el nombre
                
                if(Link){ 
                        bufsiz = buf.st_size;
                        apunta_a = malloc(bufsiz);
                        nbytes = readlink(name, apunta_a, bufsiz); //coloca el contenido de la ruta del enlace simbolico en apunta_a que tiene tamaño bufsiz.
                        if (nbytes == -1){
                                fprintf(stderr, "%s '%s' for option -link\n", strerror(errno), name);
                        } else {
                                 printf(" -> %s\n", apunta_a); //imprimimos a donde apunta el enlace simbolico   
                        } 
                        free(apunta_a);
                }
        } else {
                fprintf(stderr, "%s '%s'\n", strerror(errno), name);
        }
}

/**
 * Function: funStat
 * ----------------------
 * The options entered by the shells 
 * are evaluated and each of the 
 * files or directories is sent to 
 * the funStatAux function.
 *
 * Opcions: 
 *      [-long] Shows the long  
 *              list of information.             
 *      [-acc] Shows the acesstime.
 *      [-link] Si es enlace simbolico, 
 *              el path contenido.
 * 
 * @return void.
 */
void funStat(){
        int flagAcc = 0, flagLink = 0, flagLong = 0;
        tList ficheiros;
        createList(&ficheiros);
        tItemL d;
        tPosL p ;
        int i = 0;

        for (int k = 1; k < numtrozos; k++){
                
                if(strcmp(trozos[k], "-long") == 0){
                        flagLong = 1;
                } else if (strcmp(trozos[k], "-link") == 0) {
                        flagLink = 1;
                } else if (strcmp(trozos[k], "-acc") == 0){
                        flagAcc = 1;
                } else {
					strcpy(*d.comando, trozos[k]);
                	insertElement(d, &ficheiros);
                }                  
        }
        
        while (p!=NULL){
                funStatAux(*d.comando, flagAcc, flagLink, flagLong);
        }
}

/**
 * Function: funListFiles
 * ----------------------
 * List directories contens.
 *
 * @param directorio directory name,
 *                   type string. 
 * @param Acc options indicator 
 *            type int.
 * @param Link options indicator 
 *             type int.
 * @param Long options indicator 
 *             type int. 
 * @param Hid options indicator 
 *             type int.
 * @return void.
 */
 void funListFiles(char *directorio, int Acc, int Link, int Long, int Hid){
        DIR *dir; 
        struct dirent *d;

        dir = opendir(directorio); //accedemos al directorio
        if (dir) {
                chdir(directorio); //cambia el directorio 
                printf("************%s\n", directorio);
                while ((d = readdir(dir)) != NULL) { //leemos cada entrada del directorio y cuando llega al final muestra NULL
                        if (d->d_name[0] == '.' && !Hid) { //si el nombre del archivo es un punto y hid no esta activo seguimos  
                                continue;
                        }
                        funStatAux(d->d_name, Acc, Link, Long); //llamamos stat para mostrar lo que queremos archivo por archivo.
                }
                //si no es el propio directorio o el principal 
                if (strcmp(directorio, ".") != 0 && strcmp(directorio, "..") != 0) {
                chdir(".."); //abrimos el padre
                }
                closedir(dir); //cerramos el directorio
        }       
}

/**
 * Function: funListRecAux
 * ----------------------
 * List directories contens recursively.
 *
 * @param directorio directory name,
 *                   type string. 
 * @param Acc options indicator 
 *            type int.
 * @param Link options indicator 
 *             type int.
 * @param Long options indicator 
 *             type int. 
 * @param Reca options indicator 
 *             type int.
 * @param Recb options indicator 
 *             type int.
 * @param Hid options indicator 
 *             type int.
 * @return void.
 */
void funListRecAux(char *directorio, int Acc, int Link, int Long, int Reca, int Recb ,int Hid){
        DIR *dir;               //cabecera que contiene operaciones con directorios
        struct dirent *d;
        struct stat buf;

        if (Reca){ //si la opcion es -reca
               funListFiles(directorio, Acc, Link, Long, Hid); //primero listamos los archivos del directorio
        }
        
        dir = opendir(directorio); //accedemos al directorio
        if(dir){
                chdir(directorio); //cambia el directorio
                while((d = readdir(dir)) != NULL){ //leemos cada entrada
                        //controlamos los ocultos
                        if(d->d_name[0] == '.' && !(Hid)){
                                continue;
                        }

                        //no mostramos "." y ".." para evitar una recursividad infinita
                        if (strcmp(d->d_name, ".") == 0 || strcmp(d->d_name, "..") == 0){
                                continue;
                        }
                                        
                        stat(d->d_name, &buf); 
                        if(LetraTF(buf.st_mode) == 'd') { //si encontramos un directorio 
                                funListRecAux(d->d_name, Acc, Link, Long, Reca, Recb, Hid); //volvemos a entrar en la funcion
                        }
                }
                //si no es el propio directorio o el principal 
                if (strcmp(directorio, ".") != 0 && strcmp(directorio, "..") != 0) {
                        chdir(".."); //abrimos el directorio padre     
                }                           
                closedir(dir); 
        }

        if(Recb){ //si la opcion es -recb
                funListFiles(directorio, Acc, Link, Long, Hid); //listamos los archivos del directorio al final
        }
}

/**
 * Function: funList
 * ----------------------
 * The options that were introduced 
 * by the shell are evaluated and the 
 * directories are sent one by one to 
 * funtions to list them.
 *
 * Opcions: 
 *      [-reca] The list is displayed 
 *              recursively (before).   
 *      [-recb] The list is displayed 
 *              recursively (after).
 *      [-hid] It is shown in the 
 *              hidden files list.
 *      [-long] Shows the long  
 *              list of information.             
 *      [-acc] Shows the acesstime.
 *      [-link] Si es enlace simbolico, 
 *              el path contenido.
 * 
 * @return void.
 */
void funList(){
    int flagreca=0, flagrecb=0, flaghid=0, flaglong=0, flaglink=0, flagacc=0, opciones_trozos = 0;
    //char *fileORdir[NAME_MAX];
    struct stat buf;
    int k = 0 ;
	tList ficheiros;
    createList(&ficheiros);
    tItemL d;
    tPosL p ;

        for (int i = 1; i < numtrozos ; i++){
                if(strcmp(trozos[i], "-long") == 0){
                        flaglong = 1;
                } else if (strcmp(trozos[i], "-link") == 0){
                        flaglink = 1;
                } else if (strcmp(trozos[i], "-acc") == 0){
                        flagacc = 1;
                } else if (strcmp(trozos[i], "-hid") == 0){
                        flaghid = 1;
                } else if (strcmp(trozos[i], "-reca") == 0){ 
                        flagreca = 1;
                } else if (strcmp(trozos[i], "-recb") == 0){
                        flagrecb = 1;
                } else { 
                        if (stat(trozos[i], &buf) == -1){
                        perror("Error: ");
                        continue;
                		}
                        strcpy(*d.comando, trozos[i]); //sobreescribimos
             			insertElement(d, &ficheiros);  //insertanos novo ou o primeiro ficheiro
                }   
        } 
        
        opciones_trozos = flaglong + flaglink + flagacc + flaghid + flagreca +  flagrecb;
        if(numtrozos == opciones_trozos + 1){ 
                funCarpeta();
        }

		p=first(ficheiros);

        while(p!=NULL){  
				d = getItem(p,&ficheiros);
				printf("hola\n");
				printf("%s\n",*d.comando);
				
				if(lstat(*d.comando, &buf) == 0){
						
                 //comprobamos que es un directorio
                if(LetraTF(buf.st_mode) == 'd'){       
                        if(!(flagreca) && !(flagrecb)){
                                funListFiles(*d.comando, flagacc, flaglink, flaglong, flaghid);
                        }
                        
                        if(flagrecb || flagreca){ 
                                funListRecAux(*d.comando, flagacc, flaglink, flaglong, flagreca, flagrecb, flaghid);
                        }

                } else { 
                        //si es un archivo, entonces llamamos a Stat
                        funStatAux(*d.comando, flagacc, flaglink, flaglong);
                }
				}
				p= next(p,ficheiros);
        }
}

/**
 * Function: funDelete
 * ----------------------
 * Deletes files and/or empty directories.
 *
 * @return void.
 */
void funDelete(){
        int i;
        for(i = 1; i < numtrozos; i++){
                if(remove(trozos[i]) != 0)
                        fprintf(stderr, "%s '%s'\n", strerror(errno), trozos[i]); //devolve error se o directorio esta baleiro ou non tes permiso.
        }
        if (numtrozos == 1)
                funCarpeta();     
}

/**
 * Function: funAuxDelRec
 * ----------------------
 * Auxiliary function used to 
 * recursively delete a non-empty 
 * directory.
 *
 * @param directorio directory name,
 *                   type string.
 * @return void.
 */
void funAuxDelRec(char* directorio){                                        
        DIR * dir;
        struct dirent *d;
        char direccion[PATH_MAX];
                
        if((dir = opendir(directorio)) != NULL){ //Si podemos abrirlo
                while((d = readdir(dir)) != NULL){ //leemos cada entrada del directorio
                        //cojemos la direccion de cada entrada
                        strcpy(direccion, directorio);
                        strcat(direccion,"/");
                        strcat(direccion, d->d_name);
                        //si no es el propio directorio o el principal 
                        if ((strcmp(d->d_name,"..") != 0) && (strcmp(d->d_name,".") != 0)){
                                if(d->d_type == DT_DIR)   //se es un directorio                                 
                                        funAuxDelRec(direccion); //volvemos recursivamente a ingresar en ese directorio            
                                else {                                   
                                        if(remove(direccion) != 0) //borramos el contenido
                                                fprintf(stderr, "%s '%s'\n", strerror(errno), direccion );
                                }                                        
                        }
                } //para borrar o directorio actual
                if(remove(directorio) != 0) 
                        fprintf(stderr, "%s '%s'\n", strerror(errno), direccion );
        } else {
                fprintf(stderr, "%s '%s'\n", strerror(errno), direccion );    
        }           
}

/**
 * Function: funDeltree
 * ----------------------
 * Deletes files and/or non empty 
 * directories recursively.
 *
 * @return void.
 */
void funDeltree(){
        for(int i = 1; i < numtrozos; i++){
                if(remove(trozos[i]) != 0){
                        funAuxDelRec(trozos[i]);
                }
        }
        if(numtrozos == 1){
                funCarpeta();
        }
}

//////////////////////////////////////////////////////P2///////////////////////////////////////////////////////////////////////

void Recursiva (int n){
  char automatico[TAMANO];
  static char estatico[TAMANO];

  printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);

  if (n>0)
    Recursiva(n-1);
}


void LlenarMemoria (void *p, size_t cont, unsigned char byte){
  unsigned char *arr=(unsigned char *) p;
  size_t i;

  for (i=0; i<cont;i++)
		arr[i]=byte;
}

void Do_pmap () /*sin argumentos*/
 { pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
   char elpid[32];
   char *argv[4]={"pmap",elpid,NULL};
   
   sprintf (elpid,"%d", (int) getpid());
   if ((pid=fork())==-1){
      perror ("Imposible crear proceso");
      return;
      }
   if (pid==0){
      if (execvp(argv[0],argv)==-1)
         perror("cannot execute pmap (linux, solaris)");


   }
 }



//Función para printar Lista de alloc/delloc
void printListMm(tListMem L, char *tipo){
         int all = 1; //flag para ver se imprimo a lista completa , canto tipo = all
        printf("******Lista de bloques asignados "); 
        if (strcmp("all",tipo)!=0){
                printf("%s ", tipo);
                all = 0;
        }
        printf("para el proceso %d\n\n", getpid());
         
        if(!isEmptyListm(L)){
                tPosMem p = firstm(L);
                tItemMem d;
                while (p!=NULL){
                        d = getItemm(p, L);
                        if( strcmp(d.tipo, tipo)==0 || all){
                                printf("   %p%10d  %s ", d.direc, d.tam, d.tempo);
                                if(strcmp(d.tipo,"mmap")==0 )
				        printf("%s (descriptor %d)",d.nomefich, d.df);
			        if(strcmp(d.tipo,"shared")==0 || strcmp(d.tipo,"malloc")==0)
				        printf("%s ",d.tipo);
                                if (strcmp(d.tipo,"shared")==0)
                                        printf("(key %d)", d.chave);  
                                printf("\n");           
                        }
                        p = nextm(p, L);
		}
        }
}

//Función auxiliar para insertar elementos á lista de memoria según os parámetros
void AuxInsertElememMem(void *dire, int tam, char *tipo, int chave, char *nfich, int df, tListMem *L ){
        tItemMem d;
        time_t data_t;
        time(&data_t);
        struct tm *data;

        int mmap=0, shared=0;

        if(strcmp(tipo, "shared") == 0)
                shared = 1;
        if(strcmp(tipo, "mmap") == 0)
                mmap = 1;

        if ((data= localtime(&data_t))==NULL)
                perror("time\n");
        strcpy(d.tempo, asctime(data));   // engado o tempo e data
        d.direc = dire; //engado direc
        d.tam = tam; //engado tam
        strcpy(d.tipo, tipo); //engado tipo
        d.chave = chave; //en shared ou mmap engado chave, se non é 0
        d.df = df; //descriptor de fich, que se non é mmap é -1
        if (mmap)
                strcpy(d.nomefich, nfich);  // en mmap nome do fich
        
        //inserto elemento
        insertElementm(d, L);
}



//Auxiliar dada para obtener segmento de memoria
void * ObtenerMemoriaShmget (key_t clave, size_t tam, int flag, tListMem *L){ //flag para insertar na lista o tamaño segun se é created = 0 ou shared = 1
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;
    if (tam)     /*tam distito de 0 indica crear */
        flags=flags | IPC_CREAT | IPC_EXCL;
    if (clave==IPC_PRIVATE)  /*no nos vale*/
        {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1)//Se non podo encontrar ese seg. de memoria , null, se si, identificador
        return (NULL);
    if ((p=shmat(id,NULL,0))==(void*) -1){// unha vez que sei o identificador, miro a ver cal é a súa dir de memoria
        aux=errno;
        if (tam || s.shm_segsz) // se o tam non é cero : (Nota: cando é shared só teño a chave, por ende para obter o tamaña uso s.shm_segz)
             shmctl(id,IPC_RMID,NULL); // permite que poda recibir a info so segmento
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s);// permite que poda recibir a info so segmento
    if(flag)
        tam = s.shm_segsz;
    AuxInsertElememMem(p,tam,"shared",clave,NULL,-1,L);
    return (p);
}

//Función auxiliar dada para facer o allocate tanto shared como createshared
void do_AllocateCreateshared (tListMem *L){
   key_t cl;
   size_t tam;
   tItemMem d;
   tPosMem p = firstm(*L);
   int flagCreate = 0;
   int flagShared = 0;
   //flags para distinguir cando crear chave  e asignar segmento de me compartida ou só asignar
   if(strcmp(trozos[1],"-shared")==0)
        flagShared = 1;
   if(strcmp(trozos[1],"-createshared")==0)
        flagCreate = 1;

   if ((numtrozos==2 && flagShared) || (numtrozos < 3 && flagCreate))
        printListMm(*L, "shared");             

   else{
        cl=(key_t)  strtoul(trozos[2],NULL,10);
        if(trozos[3]!=NULL) 
                tam=(size_t) strtoul(trozos[3],NULL,10); // para convertilo nun unsigned lon
        else
                tam=0;
        if (tam==0 && flagCreate) { //se me pasan 0 bytes
	        perror("No se asignan bloques de 0 bytes\n");
	        return;
        }
        if (flagCreate){ // se teño que crear chave
                if ((p=ObtenerMemoriaShmget(cl,tam,0,L))!=NULL)
		        printf ("Asignados %lu bytes en %p\n",(unsigned long) tam, p);
                else
	        	printf("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
        }
        if (flagShared){//Se non
                if ((p=ObtenerMemoriaShmget(cl,tam,1,L))!=NULL)
                        printf("Memoria compartida de clave %lu en %p\n",(unsigned long) cl,p);             
                else
                        perror("Imposible obtener memoria shmget\n");
        } 
        }
}

//Función auxiliar dada para mapear ficheiros, devolve NULL en caso de erro

void * MapearFichero (char * fichero, int protection, tListMem *L){
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;
    int tam;

    if (protection&PROT_WRITE)
          modo=O_RDWR; // podo ler e escribir se teño permisos
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1)
          return NULL;
    if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED) //se podo 
           return NULL;
    
    tam = s.st_size; //gardo o tamaño do ficheiro na variable tam
    AuxInsertElememMem(p, tam, "mmap", 0, fichero, df, L);

    return p;
}

//Aux mmap dada
void do_AllocateMmap(tListMem *L){ 
     char *perm;
     void *p;
     int protection=0;
     tItemMem d;
     tPosMem pos = firstm(*L);
     
     if ((numtrozos==2 && strcmp(trozos[1], "-mmap")==0))
            printListMm(*L,"mmap");
     
     else{
        if ((perm=trozos[3])!=NULL && strlen(perm)<4) {
            if (strchr(perm,'r')!=NULL) protection|=PROT_READ;
            if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
            if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
        }
        if ((p=MapearFichero(trozos[2],protection, L))==NULL)// Se non podo mapear
             perror ("Imposible mapear fichero");
        else // Se sí :
             printf ("fichero %s mapeado en %p\n", trozos[2], p);
     }
}

//Aux malloc feita por nós 
void do_AllocateMalloc(tListMem *L){
        void *dire; //direción de memoria onde vou asignar o bloque
        int tama; //tamaño do bloque 
        if (trozos[2]!=NULL){
                tama = atoi(trozos[2]); // para pasar o string a enteiro
                if (tama>0){
                        if ((dire = malloc(tama))!=NULL){ // se poodo asignar memoria
                                AuxInsertElememMem(dire, tama, "malloc", 0 ,NULL,-1, L);
                                printf("Asignados %d bytes en %p\n", tama, dire);
                        }else
                                perror("malloc");
                
                }else if (trozos[2]<0){
                        printf("uso: allocate [-malloc|-shared|-createshared|-mmap] ....\n");
                }else{
                        printf("No se asignan bloques de 0 bytes\n");
                }
        }else
                 printListMm(*L,"malloc");
}


//Función para opcións do allocate
void funAlloc(tListMem *L){      
        if (numtrozos>1){
                
                if(strcmp("-malloc", trozos[1]) == 0)
                        do_AllocateMalloc(L);
                else if(strcmp("-mmap", trozos[1]) == 0)
                        do_AllocateMmap(L);
                else if((strcmp("-shared", trozos[1]) == 0) || (strcmp("-createshared", trozos[1])==0))
                        do_AllocateCreateshared(L);
                else
                        printf("uso: allocate [-malloc|-shared|-createshared|-mmap] ....\n");
        }else
                printListMm(*L, "all"); 
        
}

//Aux delkey dada para borrar as chaves creadas con createshared 
void do_DeallocateDelkey (){
   key_t clave;
   int id;
   char *key=trozos[2];

   if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
        printf ("      delkey necesita clave_valida\n");
        return;
   }
   if ((id=shmget(clave,0,0666))==-1){
        perror ("shmget: imposible obtener memoria compartida");
        return;
   }
   if (shmctl(id,IPC_RMID,NULL)==-1) //establezco con shmctl que a chave que teña ese identificador sexa borrada ( con ipc_rmid) 
        perror ("shmctl: imposible eliminar memoria compartida\n");
}


//Aux xeral dealloc para deasignar o bloque de memoria que teña a dirección dada por parámetro 

void do_Deallocate(tListMem *L){
        char *dir;
        tPosMem p;
        tItemMem d;

        if(sscanf(trozos[1],"0x%p",&dir)==0 ){ // comprobo se a dir que me dan é valida
                perror("Dirección no válida\n"); return;
        }

        if(!isEmptyListm(*L)){
        p = firstm(*L);

        while (p!=NULL){// recorro a lista para ver se teño esa dirección
                d = getItemm(p,*L);
                if (strcmp(dir, d.direc)==0) // salgo se a encontro
                        break;
                p = nextm(p,*L);            
        }
        
        if(p!=NULL){ // se p non é null porque encontrouse a dirección e existe na miña lista
                
                if( (strcmp("malloc", d.tipo) == 0) ){
                        free(d.direc);
                }else if(strcmp("shared", d.tipo) == 0){
                        shmdt(d.direc);
                }else if( strcmp("mmap", d.tipo) == 0){
                        munmap(d.direc, d.tam);
                }else{
                        printf("\n");
                }
                removeElementm(L,p);
        }else
        	printf("Dirección %s no asignada con malloc, shared o mmap\n",trozos[1]);
        }else
        	printf("Dirección %s no asignada con malloc, shared o mmap\n",trozos[1]);
}

//Aux  dealloc con malloc para deasignar o bloque de memoria que teña x tamaño dado
void do_DeallocateMalloc(tListMem *L){
        tPosMem p;
        tItemMem d;

        if (numtrozos == 2){
                printListMm(*L, "malloc");
        }
        else{
                int tama = atoi(trozos[2]);
        
                p = firstm(*L);

                while (p!=NULL){
                        d = getItemm(p,*L);

                        if (strcmp(d.tipo,"malloc")==0) // como recorro toda a lista teño que indicar que me mire se é malloc
                                if (d.tam == tama )// Se encontra un tamaño igual, colleme ese para borralo
                                        break;
                        p = nextm(p,*L);
                }
                if (p!=NULL){
                        free(d.direc);
                        removeElementm(L,p);
                }
                else
                        printListMm(*L, "malloc");
        }

}
//Aux  dealloc con shared para deasignar o bloque de memoria compartida que teña x chave dada
void do_DeallocateShared(tListMem *L){
        tPosMem p;
        tItemMem d;
        int s;
        if (numtrozos == 2)
                printListMm(*L,"shared");
        else{
                int chave = atoi(trozos[2]);
                p = firstm(*L);
                //recoro a lista para ver se atopo a chave 
                while (p!=NULL){
                        d = getItemm(p,*L);
                        if (strcmp(d.tipo,"shared") == 0){
                                if (d.chave == chave)
                                        break;
                        }
                        p = nextm(p,*L);
                }
                //se a encontro 
                if (p!=NULL){
                        s = shmdt(d.direc);
                        if (s!=-1){
                                removeElementm(L,p);
                        }else
                                perror("shmdt: Imposible desmapear el bloque de memoria compartida\n");
                }else // se non existe :
                        printf("No hay bloque de esa clave mapeado en el proceso\n");
        }

}

//Aux  dealloc con mmap para deasignar o bloque de memoria que teña  asignado ese ficheiro dado
void do_DeallocateMmap(tListMem *L){
        tPosMem p;
        tItemMem d;

        if (numtrozos == 2)
                printListMm(*L,"mmap");
        else{
                p = firstm(*L);
                while (p!=NULL){ // recorro a lista para ver se alunha dirección ten ese fich
                        d = getItemm(p,*L);
                        if(strcmp(d.tipo,"mmap")==0){
                                if(strcmp(trozos[2],d.nomefich)==0)
                                        break;
                        }
                        p = nextm(p,*L);
                }
                if (p!=NULL){//se encotro o ficheiro na lista
                        munmap(d.direc, d.tam);
                        removeElementm(L, p);
                }
                else
                        printf("Fichero %s no mapeado\n", trozos[2]);        
        }
}


//Función para opcións do deallocate
void funDealloc(tListMem *L){
        if (numtrozos>1){
                
                if(strcmp("-malloc", trozos[1]) == 0)
                        do_DeallocateMalloc(L);
                else if(strcmp("-mmap", trozos[1]) == 0)
                        do_DeallocateMmap(L);
                else if((strcmp("-shared", trozos[1]) == 0))
                        do_DeallocateShared(L);
                else if((strcmp("-delkey", trozos[1]) == 0))
                        do_DeallocateDelkey();
                else{
                        do_Deallocate(L);
                }
        }else
                printListMm(*L, "all"); 
}


//Funcións para o comando i-o 

//Función auxiliar dada por SO para ler ficheiros
ssize_t LeerFichero (char *f, void *p, size_t cont){
   struct stat s;
   ssize_t  n;  
   int df,aux;

   if (stat (f,&s)==-1 || (df=open(f,O_RDONLY))==-1)//se non se pode abrir 
	return -1;     
   if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
	cont=s.st_size;
   if ((n=read(df,p,cont))==-1){ // se non se pode ler
	aux=errno;
	close(df);
	errno=aux;
	return -1;
   }
   close (df);
   return n;
}

//Opción read do comando i-o 
void do_I_O_read (){
   void *p;
   size_t cont=-1;
   ssize_t n;
   if (numtrozos<5){
	printf ("faltan parametros\n");
	return;
   }
   p=(void*) strtoul(trozos[3],NULL,16) ;  /*convertimos de cadena a puntero*/
   if (trozos[4]!=NULL) //Comprobación para que non dei erro atoll
	cont=(size_t) atoll(trozos[4]); // atoll pasa de string a  long

   if ((n=LeerFichero(trozos[2],p,cont))==-1) //Se temos algún erro ao  ler 
	perror ("Imposible leer fichero");
   else //Se non lemos 
	printf ("leidos %lld bytes de %s en %p\n",(long long) n,trozos[2],p);
}

//Función auxiliar dada por SO para escribir/sobrescribir ficheiros
ssize_t EscribirFichero (char *f, void *p, size_t cont,int overwrite){
   ssize_t  n;
   int df,aux, flags=O_CREAT | O_EXCL | O_WRONLY; 

   if (overwrite) // se teño a opción -o de sobrescribir 
	flags=O_CREAT | O_WRONLY | O_TRUNC; //doulle estes permisos , porque O_TRUNC permite que un ficheiro existente trunque a lonxitude
        //se non , quedome con O_EXCL que combinado co de creación solta unn erro se xa existe o ficheiro
   if ((df=open(f,flags,0777))==-1)
	return -1;

   if ((n=write(df,p,cont))==-1){//escribo fich
	aux=errno;
	close(df);
	errno=aux;
	return -1;
   }
   close (df);
   return n;
}

//Opción write do comando i-o 
void do_I_O_write(){
        void *p;
        size_t cont=-1;
        ssize_t n;

        if ((numtrozos<5 && strcmp("-o",trozos[2])!=0) || (numtrozos<6 && strcmp("-o", trozos[2])==0)){
                printf("faltan parametros\n");
                return;
        }else{  
                if((strcmp(trozos[2],"-o")==0)){ // Se teño a opción de sobrescribir

                        p=(void*) strtoul(trozos[4],NULL,16); // paso a cadea a punteiro
                
                        if (trozos[5]!=NULL) //paso o número de bytes a ler de cadea a long
	                        cont=(size_t) atoll(trozos[5]);
    		
                        if((n=EscribirFichero(trozos[3], p, cont, 1))==-1){ // Se falla a escfritura:
    		        	perror("Imposible escribir el fichero\n");
                        }else// Se non, escribo
    		                printf("escritos %s bytes en %s desde %p\n",trozos[5],trozos[3],p);
  	        }else{ //Se non sobreescribo
                //Fago o mesmo pero con trozos nunha posición menos porque non teño -o
    		        p=(void*) strtoul(trozos[3],NULL,16);
                        if (trozos[4]!=NULL)
	                        cont=(size_t) atoll(trozos[4]);
    	        	if((n=EscribirFichero(trozos[2],p,cont,0))==-1){
    		        	perror("Imposible  escribir el fichero\n");
    			        return;
    	        	}else
    		        	printf("escritos %s bytes en %s desde %p\n",trozos[4],trozos[2],p);
                }
        }
}


//Función i-o para escribir ou leer dunha direccion a un fich e viceversa
void funIo(){
        if (numtrozos == 1)
                printf("uso: e-s [read|write] ......\n");
        else{
                if(strcmp(trozos[1],"read")==0) //para ler
                        do_I_O_read();
                else if (strcmp(trozos[1],"write")==0) // para escribir
                        do_I_O_write();
                else
                        printf("uso: e-s [read|write] ......\n");
        }
}


//Función recursiva de recursiva, chama n veces a función recursiva de parámetros
void  funRecursiva(){
        int n ;//parametro para invocar a función recursiva n veces 
        if (numtrozos > 1){
                n = atoi(trozos[1]);
                Recursiva(n);
        }
}


/**
 * Function: trocearCadena
 * ----------------------
 * Copies in trozos all the tokens found
 * in the string separated by spaces.
 *
 * @param cadena string with the command
 * @param trozos array of strings
 * @return number of strings copied in trozos
 */

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
        tListMem listamemoria;
        createListm(&listamemoria);

        while(1){
                printf("-> ");
                if(fgets(linea, MAXLINEA, stdin) == NULL) 
                        exit(1);
                //copio en d a cadena de entrada para insetar los comandos o historial
                strcpy(*d.comando, linea); 
                numtrozos = TrocearCadena(linea, trozos);
                if (numtrozos == 0)
                        continue;
                for (i = 0; ; i++){
                        if(comandos[i].nombre == NULL){
                                if (strcmp(trozos[0], "hist") == 0){
                                        insertElement(d, &listhistorial);
                                        funHist(&listhistorial);
                                        break;
                                }
                                else if(strcmp(trozos[0], "fin") == 0 || strcmp(trozos[0], "bye") == 0 || strcmp(trozos[0], "salir") == 0){
                                        insertElement(d, &listhistorial);
                                        funFin(&listhistorial, &listamemoria);
                                }
                                else if(strcmp(trozos[0], "allocate") == 0){
                                        insertElement(d, &listhistorial);
                                        funAlloc(&listamemoria);
                                        break;
                                }else if(strcmp(trozos[0], "deallocate") == 0){
                                        insertElement(d, &listhistorial);
                                        funDealloc(&listamemoria);
                                        break;
                                }
                                else{
                                        fprintf(stderr, "%s '%s'\n", strerror(3), trozos[0]);
                                        insertElement(d, &listhistorial);
                                        break;
                                }
                        }
                        if (strcmp(comandos[i].nombre, trozos[0]) == 0){  
                                comandos[i].pfun();
                                insertElement(d, &listhistorial);
                                break;
                        }
                }
        }
}    