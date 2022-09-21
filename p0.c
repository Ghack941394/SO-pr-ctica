/*
Alumna 1 : Daniela Cisneros Sande
Alumna 2: Graciela Méndez Olmos

login 1: d.cisneross@udc.es
login 2: graciela.mendez.olmos@udc.es


*/


#include "p0.h"
#include "historial.h"


char *trozos[MAXTROZOS];
int numtrozos;
char linea[MAXLINEA];
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
    
void funPid(){};

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
}; 

void funFecha(){};

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
                        p = p = next(p,*listhistorial);
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
};


void funInfosis(){};

struct ax tabla[] = {
  {"fecha","[-d|.h	Muestra la fecha y o la hora actual"},
  {"autores","[-n|-l]	Muestra los nombres y logins de las autoras"},
  {"pid","[-p]	Muestra el pid del shell o de su proceso padre"},
  {"hist", "[-c|-N]	Muestra el historico de comandos, con -c lo borra"},
  {"carpeta", "[dir] Cambia (o muestra) el directorio actual del shell"},
  {"infosis", "Muestra informacion de la maquina donde corre el shell"},
  {"fin","Termina la ejecucion del shell"},
  {"bye","Termina la ejecucion del shell"},
  {"salir","Termina la ejecucion del shell"},
  {NULL,NULL},
};


void funAyuda(){
        int i;
  if (numtrozos>1){
    for (i = 0; ; i++){
      if (strcmp(tabla[i].nombre, trozos[1])==0){
        printf("%s %s\n",trozos[1], aytabla[i].explicacion);
        break;}
       }
      }
    else{
      printf("'ayuda cmd' donde cmd es uno de los siguientes comandos:\n");
      printf("1.autores[-l|-n]\n2.pid[-p]\n3.carpeta[direct]\n4.fecha[-d|-h]\n");
      printf("5.hist[- c|-N]\n6.infosis\n7.fin\n8.salir\n9.bye\n");
    }
        
};

void funFin(tList listhistorial){};


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
                printf("~€");
                if(fgets(linea, MAXLINEA,stdin)==NULL) {
                        exit(1);
                }
                //copio en d a cadea de entrada para insetar os comandos ó historial
                strcpy(*d.comando, linea); 
                numtrozos= TrocearCadena(linea,trozos);

                for(i=0;i<numtrozos;i++)
                        printf("trozo numero %d es [%s]\n",i,trozos[i]);
        
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
                                        break;
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
        
