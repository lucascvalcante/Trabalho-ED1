#include "chao.h"
#include "formas.h"
#include "fila.h"
#include "stdio.h"
#include "stdlib.h"

typedef struct chao{
    Fila FilaChao;
}Stchao;

Chao Cria_Chao(){
    Stchao *c = malloc(sizeof(Stchao));
    if(c == NULL){
        printf("Não foi possível alocar memória para o chão!\n");
        exit(1);
    } 

    c->FilaChao = Criar_Fila();
    return ((Stchao*)c);
} 

void InserirChao(Chao chao, Forma f){
    Stchao *c = ((Stchao*)chao);
    if(f == NULL){
        printf("Forma inválida!\n");
        return;
    } 

    InserirFila(c->FilaChao, f);
}

Forma RetiraChao(Chao chao){
    Stchao *c = ((Stchao*)chao);

    return RetirarFila(c->FilaChao);
} 

void DestruirChao(Chao chao){
    Stchao *c = ((Stchao*)chao);

    KillFila(c->FilaChao);
    free(c);
}