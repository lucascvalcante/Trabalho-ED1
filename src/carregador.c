#include "carregador.h"
#include <stdio.h>
#include <stdlib.h>
#include "pilha.h"
#include "fila.h"
#include "chao.h"
#include "formas.h"

typedef struct Carregador{
    int id;
    Pilha formas;
}Stcarregador; 


Carregador CriarCarregador(int id){
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
    c->id = id;
    
    return ((Stcarregador*)c);
} 

Forma InserirCarregador(Carregador carregador, Forma f){
    Stcarregador *c = ((Stcarregador*)carregador);
    
    InserirPilha(c->formas, f);
    return f;
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
    if(c == NULL){
        return;
    }

    while(GetSizeCarregador(carregador)){
        Forma f = RetirarCarregador(carregador);
        if(f != NULL){
            DestruirForma(f);
        }
    }

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

int GetIDCarregador(Carregador carregador){
    Stcarregador *c = ((Stcarregador*)carregador);
    if(c == NULL){
        return 0;
    }    

    return c->id;
} 

Fila AdicionaNCarregador(Chao chao, Carregador carregador, int n){
    Stcarregador *c = ((Stcarregador*)carregador);
    if(n <= 0){
        return Criar_Fila();
    } 

    if(c == NULL || chao == NULL){
        return NULL;
    }
    
    Fila FormasInseridas = Criar_Fila();
    for(int i = 0; i < n; i++){
        Forma FormaInserida = InserirCarregador(carregador, (RetiraChao(chao)));
        if(FormaInserida == NULL){
            break;
        }
        InserirFila(FormasInseridas, FormaInserida);
    }
    return FormasInseridas;
}



