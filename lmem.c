

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "lmem.h"

void createListm(tListMem* L){
*L = NULL;
}

bool isEmptyListm(tListMem L){
return L == NULL;
}

tPosMem firstm(tListMem L){
return L;
}

tPosMem nextm(tPosMem p, tListMem L){
        return p->next;
}

tItemMem getItemm(tPosMem p, tListMem* L){
return p->data ; // a función de tipo tItemL tenque devolver tItemL
}

bool createNodem(tPosMem* p){
*p = malloc(sizeof(**p));
return *p != NULL;
}

bool insertElementm(tItemMem d, tListMem* L){
tPosMem q, r;
bool i;
// agora comprobamos se hai espazo
if (!createNodem(&q))
i = false;
else{
q->data = d;
q->next=NULL;
if(*L==NULL){
*L = q;
} else{
for(r=*L; r->next != NULL; r = r->next);
r->next = q;
  }
i = true; }
return i;
}

void removeElementm(tListMem *L){
tPosMem q;
while(*L != NULL){
q = *L;
*L = (*L)->next;
free(q);}
}
