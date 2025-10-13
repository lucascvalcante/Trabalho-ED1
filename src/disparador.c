#include "disparador.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct disparador{
    int id;
    double x, y;
    Carregador CarregadorEsquerdo;
    Carregador CarregadorDireito;
    LadoCarregador ladoAtivo;
    Forma formaEmDisparo;
}StDisparador;


Disparador CriarDisparador(int id, double x, double y){
    StDisparador *d = malloc(sizeof(StDisparador));
    if(d == NULL){
        printf("Não foi possível alocar memória para a criação do disparador!\n");
        exit(1);
    }

    d->id = id;
    d->x = x;
    d->y = y;
    d->CarregadorEsquerdo = NULL;
    d->CarregadorDireito = NULL;
    d->ladoAtivo = LadoEsquerdo;
    d->formaEmDisparo = NULL;

    return d;
}

int GetIDDisparador(Disparador disparador){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL){
        return -1;
    }
    return d->id;
}

double GetXDisparador(Disparador disparador){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL){
        return 0.0;
    }
    return d->x;
}

double GetYDisparador(Disparador disparador){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL){
        return 0.0;
    }
    return d->y;
} 

void SetPosicaoDisparador(Disparador disparador, double x, double y){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL){
        return;
    }
    d->x = x;
    d->y = y;
}

Forma GetFormaEmDisparo(Disparador disparador){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL){
        return NULL;
    } 
    return d->formaEmDisparo;
}

void DisparadorAtch(Disparador disparador, Carregador esq, Carregador dir){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL){
        return;
    } 

    if (d->CarregadorEsquerdo != NULL) KillCarregador(d->CarregadorEsquerdo);
    if (d->CarregadorDireito != NULL) KillCarregador(d->CarregadorDireito);

    d->CarregadorDireito = dir;
    d->CarregadorEsquerdo = esq;
    d->formaEmDisparo = NULL;

} 

Forma DisparadorShft(Disparador disparador, LadoCarregador lado, int n){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL || n <= 0){
        return NULL;
    }
    
    Forma UltimaForma = NULL;
    Carregador fonte = NULL;
    Carregador destino = NULL;

    for(int i = 0; i < n; i++){
        if(lado == LadoEsquerdo){
            fonte = d->CarregadorEsquerdo;
            destino = d->CarregadorDireito;
        } else{
            fonte = d->CarregadorDireito;
            destino = d->CarregadorEsquerdo;
        }

        if(fonte == NULL || destino == NULL){
            printf("Pelo menos um dos carregadores não está anexado!\n");
            d->formaEmDisparo = UltimaForma;
            return UltimaForma;
        }

        if(GetSizeCarregador(fonte) == 0){
            printf("O carregador esgotou durante o shft!\n");
            d->formaEmDisparo = UltimaForma;
            return UltimaForma;
        }

        UltimaForma = RetirarCarregador(fonte);
        InserirCarregador(destino, UltimaForma);
    }

    d->formaEmDisparo = UltimaForma;
    return UltimaForma;

}

Forma DisparaDisparador(Disparador disparador, double dx, double dy){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL){
        return NULL;
    }

    if(d->formaEmDisparo == NULL){
       printf("Não há nenhuma forma para ser disparada!\n");
       return NULL; 
    }
    
    Forma FormaDisparada = d->formaEmDisparo;
    double xDisparador = GetXDisparador(d);
    double yDisparador = GetYDisparador(d);
    double xFinal = dx + xDisparador;
    double yFinal = dy + yDisparador;
    
    SetPosicaoForma(FormaDisparada, xFinal, yFinal);
    d->formaEmDisparo = NULL;

    return FormaDisparada;

}

void KillDisparador(Disparador disparador){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL){
        return;
    }

    if(d->CarregadorDireito != NULL){
        KillCarregador(d->CarregadorDireito);
    } 
    if(d->CarregadorEsquerdo != NULL){
        KillCarregador(d->CarregadorEsquerdo);
    }
    free(d);
}