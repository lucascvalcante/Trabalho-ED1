#include "carregador.h"
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"

typedef struct Carregador{
    Pilha formas;
    LadoCarregador lado;
}Stcarregador; 


Carregador CriarCarregador(LadoCarregador lado){
    Stcarregador *c = malloc(sizeof(Stcarregador));
    if(c == NULL){
        printf("Não foi possivel alocar memória para o carregador!\n");
        exit(1);
    } 

    c->formas = Criar_Pilha();
    if(c->formas == NULL){
        printf("Não foi possível criar a pilha para o carregador!\n");
        free(c);
        exit(1);
    } 
    c->lado = lado;
    
    return ((Stcarregador*)c);
} 

void InserirCarregador(Carregador carregador, Forma f){
    Stcarregador *c = ((Stcarregador*)carregador);
    
    InserirPilha(c->formas, f);
} 

Forma RetirarCarregador(Carregador carregador){
    Stcarregador *c = ((Stcarregador*)carregador);

    return RetirarPilha(c->formas);
} 

int GetSizeCarregador(Carregador carregador){
    Stcarregador *c = ((Stcarregador*)carregador);
    return SizePilha(c->formas);
}

void KillCarregador(Carregador carregador){
    Stcarregador *c = ((Stcarregador*)carregador);

    KillPilha(c->formas);
    free(c);
}

Forma VerFormaCarregador(Carregador carregador){
    Stcarregador *c = ((Stcarregador*)carregador);
    if(c == NULL || c->formas == NULL){
        return NULL;
    }

    return TopoPilha(c->formas);
}