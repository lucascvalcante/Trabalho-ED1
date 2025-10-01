#include "texto.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Estilo{
    char *fFamily, *fWeight, *fSize;
}StEstilo;

typedef struct Texto{
    int id;
    double x, y;
    char *corb, *corp;
    char a, *txto;
    Estilo st;
}StTexto;

Texto Criar_Texto(int id, double x, double y, char *corb, char *corp, char a, char *txto, Estilo st){
    StTexto *t = malloc(sizeof(StTexto));
    if(t == NULL){
        printf("Não foi possível alocar memória para a criação do texto!\n");
        exit(1);
    }

    t->id = id;
    t->x = x;
    t->y = y;
    t->a = a;
    t->st = st;

    t->corb = malloc(strlen(corb)+1);
    if(t->corb == NULL){
        printf("Não foi possível alocar memória para a cor de borda do texto!\n");
        exit(1);
    }
    strcpy(t->corb, corb);

    t->corp = malloc(strlen(corp)+1);
    if(t->corp == NULL){
        printf("Não foi possível alocar memória para a cor de preenchimento do texto!\n");
        exit(1);
    }
    strcpy(t->corp, corp);

    t->txto = malloc(strlen(txto)+1);
    if(t->txto == NULL){
        printf("Não foi possível alocar memória para o texto!\n");
        exit(1);
    }
    strcpy(t->txto, txto);

    return ((StTexto*)t);
}

Estilo Criar_Estilo(char *fFamily, char *fWeight, char *fSize){
    StEstilo *st = malloc(sizeof(StEstilo));
    if(st == NULL){
        printf("Não foi possível alocar memória para a criação do esilo de texto!\n");
        exit(1);
    }
    
    st->fFamily = malloc(strlen(fFamily)+1);
    if(st->fFamily == NULL){
        printf("Não foi possível alocar memória para a família do texto!\n");
        exit(1);
    }
    strcpy(st->fFamily, fFamily);

    st->fWeight = malloc(strlen(fWeight)+1);
    if(st->fWeight == NULL){
        printf("Não foi possível alocar memória para o weight do texto!\n");
        exit(1);
    }
    strcpy(st->fWeight, fWeight);

    st->fSize = malloc(strlen(fSize)+1);
    if(st->fSize == NULL){
        printf("Não foi possível alocar memória para o tamanho do texto!\n");
        exit(1);
    }
    strcpy(st->fSize, fSize);

    return ((StEstilo*)st);

}

char *GetfFamily(Estilo st){
    return ((StEstilo*)st)->fFamily;
}

char *GetfSize(Estilo st){
    return ((StEstilo*)st)->fSize;
}

char *GetfWeight(Estilo st){
    return ((StEstilo*)st)->fWeight;
}

void SetfFamily(Estilo st, char *fFamily){
    strcpy(((StEstilo*)st)->fFamily, fFamily);
}

void SetfSize(Estilo st, char *fSize){
    strcpy(((StEstilo*)st)->fSize, fSize);
}

void SetfWeight(Estilo st, char *fWeigh){
    strcpy(((StEstilo*)st)->fWeight, fWeigh);
}

int GetIDTexto(Texto t){
    return ((StTexto*)t)->id;
}

double GetXTexto(Texto t){
    return ((StTexto*)t)->x;
}

double GetYTexto(Texto t){
    return ((StTexto*)t)->y;
}

char *GetCorbTexto(Texto t){
    return ((StTexto*)t)->corb;
}

char *GetCorpTexto(Texto t){
    return ((StTexto*)t)->corp;
}

char GetATexto(Texto t){
    return ((StTexto*)t)->a;
}

char *GetTxtoTexto(Texto t){
    return ((StTexto*)t)->txto;
}

double AreaTexto(Texto t){
    return 20 * strlen(((StTexto*)t)->txto);
}

void SetIDTexto(Texto t, int id){
    ((StTexto*)t)->id = id;
}

void SetXTexto(Texto t, double x){
    ((StTexto*)t)->x = x;
}

void SetYTexto(Texto t, double y){
    ((StTexto*)t)->y = y;
}

void SetCorbTexto(Texto t, char *corb){
    ((StTexto*)t)->corb = corb;
}

void SetCorpTexto(Texto t, char *corp){
    ((StTexto*)t)->corp = corp;
}

void SetATexto(Texto t, char a){
    ((StTexto*)t)->a = a;
}

void SetTxtoTexto(Texto t, char *txto){
    ((StTexto*)t)->txto = txto;
}

Estilo GetEstilo(Texto t){
    return ((StTexto*)t)->st;
}


