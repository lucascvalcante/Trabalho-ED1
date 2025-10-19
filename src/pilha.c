#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef void *Forma;

typedef struct no{
    Forma forma;
    struct no *prox;
}no;

typedef struct{
    no *topo;
    int size;
}Stpilha;

Pilha Criar_Pilha(){
    Stpilha *p = malloc(sizeof(Stpilha));
    if(p == NULL){
        printf("Não foi possível alocar memória para criar a pilha!\n");
        exit(1);
    }

    p->topo = NULL;
    p->size = 0;
    
    return ((Stpilha*)p);
}

void InserirPilha(Pilha pilha, Forma forma){
    Stpilha *p = ((Stpilha*)pilha);

    no *novo = malloc(sizeof(no));
    if(novo == NULL){
        printf("Não foi possível alocar memória!\n");
        exit(1);
    } 

    novo->forma = forma;
    novo->prox = p->topo;
    p->topo = novo;
    p->size++;
} 

Forma RetirarPilha(Pilha pilha){
    Stpilha *p = ((Stpilha*)pilha);

    if(p->topo == NULL){
        printf("A pilha está vazia!\nNada para retirar.\n");
        return NULL;
    } 

    no* inicio = p->topo;
    Forma removido = inicio->forma;
    p->topo = p->topo->prox;
    free(inicio);
    p->size--;
    return removido;
}

Forma TopoPilha(Pilha pilha){
    Stpilha *p = ((Stpilha*)pilha);

    if(p->topo == NULL){
        printf("A pilha está vazia!\n");
        return NULL;
    }
    return p->topo->forma;
}

void KillPilha(Pilha pilha){
    Stpilha *p = ((Stpilha*)pilha);

    no *atual = p->topo;
    while(atual != NULL){
        no *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }
    p->topo = NULL;
    p->size = 0;
    free(p);
}

int SizePilha(Pilha pilha){
    Stpilha *p = ((Stpilha*)pilha);
    return p->size;
}