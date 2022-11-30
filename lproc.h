#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <signal.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/resource.h>


#define MAXI 1024

typedef char proc[MAXI];



typedef struct tNodep* tPosP;

typedef struct {
  pid_t pid;
  proc tempo;
  proc estado;
  proc comando;
  int prioridade; 
}tItemP;

struct tNodep{
tItemP data;
tPosP next;
};

typedef tPosP tListP;

void createListp(tListP*);

bool isEmptyListp(tListP);

tPosP firstp(tListP);

tPosP nextp(tPosP, tListP);

tItemP getItemp(tPosP, tListP);

bool insertElementp(tItemP, tListP*);

void removeElementp(tListP*, tPosP);

