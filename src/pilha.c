#include "pilha.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef void *Forma;

typedef struct no{
    Forma *forma;
    char tipo;
    struct no *prox;
}no;

typedef struct{
    no *topo;
    int *size;
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

void InserirPilha(Pilha *pilha, Forma forma){
    Stpilha *p = ((Stpilha*)pilha);

    no *novo = malloc(sizeof(no));
    if(novo == NULL){
        printf("Não foi possível alocar memória!\n");
        exit(1);
    } 

    novo->forma = forma;
    if(p->topo == NULL){
        p->topo = novo;
        novo->prox = NULL;
    }else{
        novo->prox = p->topo;
        p->topo = novo;
    } 

    p->size++;
} 

void RetirarPilha(Pilha *pilha){
    Stpilha *p = ((Stpilha*)pilha);

    if(p->topo == NULL){
        printf("A pilha está vazia!\nNada para retirar.\n");
        exit(1);
    } 

    no* inicio = p->topo;
    p->topo = p->topo->prox;
    free(inicio);
    p->size--;
}

Pilha TopoPilha(Pilha *pilha){
    Stpilha *p = ((Stpilha*)pilha);

    if(p->topo == NULL){
        printf("A pilha está vazia!\n");
        return NULL;
    }
    return p->topo->forma;
}

Pilha NextPilha(Pilha *pilha){
    Stpilha *p = ((Stpilha*)pilha);

    if(p->topo == NULL || p->topo->prox == NULL){
        printf("A pilha não tem a quantidade de elementos suficientes!\n");
        return NULL;
    } 
    return p->topo->prox;
}

void KillPilha(Pilha *pilha){
    Stpilha *p = ((Stpilha*)pilha);

    no *atual = p->topo;
    while(atual != NULL){
        no *proximo = p->topo->prox;
        free(atual);
        atual = proximo;
    }

    p->topo = NULL;
    p->size = 0;
}

int SizePilha(Pilha *pilha){
    Stpilha *p = ((Stpilha*)pilha);

    return p->size;
}