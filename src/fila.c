#include "fila.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "svg.h"

typedef void *Forma;

typedef struct no{
    Forma forma;
    struct no *prox;
}no;

typedef struct{
    no *inicio;
    no *fim;
    int size;
}Stfila;

Fila Criar_Fila(){
    Stfila *f = malloc(sizeof(Stfila));
    if(f == NULL){
        printf("Não foi possível alocar memória para a fila!\n");
        exit(1);
    }

    f->inicio = NULL;
    f->fim = NULL;
    f->size = 0;

    return ((Stfila*)f);
}

void InserirFila(Fila fila, Forma forma){
    Stfila *f = ((Stfila*)fila);

    no *novo = malloc(sizeof(no));
    if(novo == NULL){
        printf("Não foi possível alocar memória para a fila!\n");
        exit(1);
    }

    novo->forma = forma;
    novo->prox = NULL;

    if(f->fim == NULL){
        f->fim = novo;
        f->inicio = novo;
    }else{
        f->fim->prox = novo;
        f->fim = novo;
    }

    f->size++;
}

Forma InicioFila(Fila fila){
    Stfila *f = ((Stfila*)fila);

    if(f->inicio == NULL){
        return NULL;
    }
    return f->inicio->forma;
}

Forma RetirarFila(Fila fila){
    Stfila *f = ((Stfila*)fila);

    if(f->inicio == NULL){
        printf("A fila está vazia!\nNada para retirar.\n");
        return NULL;
    }
    no *first = f->inicio;
    Forma removido = f->inicio->forma;
    f->inicio = f->inicio->prox;
    if(f->inicio == NULL){
        f->fim = NULL;
    } 
    free(first);
    f->size--;
    return removido;
}

void KillFila(Fila fila){
    Stfila *f = ((Stfila*)fila);

    no *atual = f->inicio;
    while(atual != NULL){
        no *prox = atual->prox;
        free(atual);
        atual = prox;
    }

    f->fim = NULL;
    f->inicio = NULL;
    f->size = 0;
    free(f);
}

void PassthroughQueue(Fila fila, void (*acao)(void *item, void *aux_data),void *aux_data){
    Stfila *f = ((Stfila*)fila);
    if(f == NULL || f->inicio == NULL){
        printf("Não há elementos suficientes na fila!\n");
        return;
    }

    no* atual = f->inicio;
    while(atual != NULL){
        acao(atual->forma, aux_data);
        atual = atual->prox;
    }
}

int SizeFila(Fila fila){
    Stfila *f = ((Stfila*)fila);
    return f->size;
}



