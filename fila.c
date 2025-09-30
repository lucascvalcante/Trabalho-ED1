#include "fila.h"
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

void InserirFila(Fila *fila, Forma forma){
    Stfila *f = ((Stfila*)fila);

    no *novo = malloc(sizeof(no));
    if(novo == NULL){
        printf("Não foi possível alocar memória!\n");
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

Fila InicioFila(Fila *fila){
    Stfila *f = ((Stfila*)fila);

    if(f->inicio == NULL){
        return NULL;
    }
    return f->inicio->forma;
}

Fila NexFila(Fila *fila){
    Stfila *f = ((Stfila*)fila);

    if(f->inicio == NULL || f->inicio->prox == NULL){
        printf("A fila não tem elementos suficientes!\n");
        return NULL;
    }
    return f->inicio->prox->forma;
}

void RetirarFila(Fila *fila){
    Stfila *f = ((Stfila*)fila);

    if(f->inicio == NULL){
        printf("A fila está vazia!\nNada para retirar.\n");
        exit(1);
    }
    no *first = f->inicio;
    f->inicio = f->inicio->prox;
    if(f->inicio == NULL){
        f->fim = NULL;
    } 
    free(first);
    f->size--;
}

void KillFila(Fila *fila){
    Stfila *f = ((Stfila*)fila);

    no *atual = f->inicio;
    while(atual != NULL){
        no *prox = f->inicio->prox;
        free(atual);
        atual->prox;
    }

    f->fim = NULL;
    f->inicio = NULL;
    f->size = 0;
}

