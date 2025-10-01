#include "formas.h"
#include <stdio.h>
#include <stdlib.h>
#include "circulo.h"
#include "retangulo.h"
#include "texto.h"
#include "linha.h"

typedef struct formas{
    Tipo_Forma tipo;
    void *dados;
}Stforma;


Forma Criar_Forma(Tipo_Forma tipo, void *dados){
    Stforma *f = malloc(sizeof(Stforma));
    if(f == NULL){
        printf("Erro ao alocar memória para criar forma!\n");
        exit(1);
    } 

    f->tipo = tipo;
    f->dados = dados;

    return ((Stforma*)f);
}

Tipo_Forma GetTipoForma(Forma f){
    return ((Stforma*)f)->tipo;
}

void *GetDadosForma(Forma f){
    return ((Stforma*)f)->dados;
}

double GetAreaForma(Forma f){
    if(f == NULL){
        return 0;
    }

    switch (((Stforma*)f)->tipo) {
    case CIRCULO: return AreaCirculo(((Stforma*)f)); 
    case RETANGULO: return AreaRetangulo(((Stforma*)f));
    case TEXTO: return AreaTexto(((Stforma*)f));
    case LINHA: return AreaLinha(((Stforma*)f));

    }

    return 0;
}

void SetPosicaoForma(Forma f, double x, double y){
        if(f == NULL){
            return;
        }
        switch (((Stforma*)f)->tipo) {
        case CIRCULO: {
            Circulo c = ((Stforma*)f)->dados;
            SetXCirculo(c, x);
            SetYCirculo(c, y);
            break;
        }

        case RETANGULO:{
            Retangulo r = ((Stforma*)f)->dados;
            SetXRetangulo(r, x);
            SetYRetangulo(r, y);
            break;
        }

        case LINHA:{
            Linha l = ((Stforma*)f)->dados;
        
            double x1Antigo = GetX1Linha(l);
            double x2Antigo = GetX2Linha(l);
            double y1Antigo = GetY1Linha(l);
            double y2Antigo = GetY2Linha(l);

            double dx = x - x1Antigo;
            double dy = y - y1Antigo;

            SetX1Linha(l, x);
            SetY1Linha(l, y);
            SetX2Linha(l, x2Antigo + dx);
            SetY2Linha(l, y2Antigo + dy);
            break;
        }

        case TEXTO: {
            Texto t = ((Stforma*)f)->dados;

            SetXTexto(t, x);
            SetYTexto(t, y);  
            break;
        } 

        default: {
            printf("Forma inválida!\n");
            break;
        }
    
    }
}

void DestruirForma(Forma f){

}



