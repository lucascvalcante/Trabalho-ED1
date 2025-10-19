#include "disparador.h"
#include <stdio.h>
#include <stdlib.h>
#include "formas.h"
#include "carregador.h"
#include "fila.h"
#include "arena.h"

typedef struct disparador{
    int id;
    double x, y;
    Carregador CarregadorEsquerdo;
    Carregador CarregadorDireito;
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

Forma DisparadorShft(Disparador disparador, char botao, int n) {
    StDisparador *d = ((StDisparador*)disparador);

    // Verificação inicial (mantida)
    if (d == NULL || n < 0) {
        return NULL;
    }

    Forma forma_a_devolver = d->formaEmDisparo;

    Carregador fonte = NULL;
    Carregador destino = NULL;
    Forma proxima_forma = NULL; 


    for (int i = 0; i < n; i++) {
        switch (botao) {
            case 'd': 
                fonte = d->CarregadorEsquerdo;
                destino = d->CarregadorDireito;

                if (fonte == NULL || destino == NULL) {
                    printf("Pelo menos um dos carregadores não está anexado (shft 'd')!\n");
                    return d->formaEmDisparo;
                }

                if (forma_a_devolver != NULL) {
                    InserirCarregador(destino, forma_a_devolver);
                    forma_a_devolver = NULL;
                }

                if (GetSizeCarregador(fonte) == 0) {
                    printf("O carregador esquerdo esgotou durante o shft 'd'!\n");
                    d->formaEmDisparo = NULL;
                    return NULL; 
                }

                proxima_forma = RetirarCarregador(fonte);
                d->formaEmDisparo = proxima_forma;
                forma_a_devolver = proxima_forma;

                break; 

            case 'e': 
                fonte = d->CarregadorDireito;
                destino = d->CarregadorEsquerdo;

                if (fonte == NULL || destino == NULL) {
                    printf("Pelo menos um dos carregadores não está anexado (shft 'e')!\n");
                    return d->formaEmDisparo; 
                }

                if (forma_a_devolver != NULL) {
                    InserirCarregador(destino, forma_a_devolver);
                    forma_a_devolver = NULL;
                }

                if (GetSizeCarregador(fonte) == 0) {
                    printf("O carregador direito esgotou durante o shft 'e'!\n");
                    d->formaEmDisparo = NULL;
                    return NULL;
                }
                proxima_forma = RetirarCarregador(fonte);
                d->formaEmDisparo = proxima_forma;
                forma_a_devolver = proxima_forma;
                break; 

            default: 
                printf("Botao invalido para shft: '%c'\n", botao);
                return d->formaEmDisparo;
        } 
    } 

    return d->formaEmDisparo;
}

Fila RajadaDisparados(Disparador disparador, char botao, double dx, double dy, double ix, double iy, Arena a){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL){
        return NULL;
    }

    Carregador c = NULL;
    if(botao == 'e' || botao == 'E'){
        c = d->CarregadorEsquerdo;
    }else if(botao == 'd' || botao == 'D'){
        c = d->CarregadorDireito;
    }
    if(c == NULL){
        printf("Carregador não conectado!\n");
        return NULL;
    }

    printf("DEBUG rajada: botão %c. Usado no carregador ID %d", botao, GetIDCarregador(c));
    int num_disparos = GetSizeCarregador(c);
    printf("DEBUG rajada: num_disparos = %d\n", num_disparos);
    if(num_disparos == 0){
        printf("DEBUG rajada: Carregador está vazio. Saindo!\n");
        return NULL;
    }

    Fila FormasDisparadas = Criar_Fila();
    double dx1 = dx;
    double dy1 = dy;

    for(int i = 0; i < num_disparos; i++){
        Forma Forma_atual = RetirarCarregador(c);
        if(Forma_atual == NULL){
            break;
        }
        SetPosicaoForma(Forma_atual, (d->x + dx1), (d->y)+dy1);
        InserirArena(a, Forma_atual);
        InserirFila(FormasDisparadas, Forma_atual);
        dx1 += ix;
        dy1 += iy;
    }
    return FormasDisparadas;
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
    free(d);
}


Forma RetirarFormaEmDisparo(Disparador disparador){
    StDisparador *d = ((StDisparador*)disparador);
    if(d == NULL){
        return NULL;
    }

    Forma forma_retirada = d->formaEmDisparo;
    d->formaEmDisparo = NULL;
    return forma_retirada;
}