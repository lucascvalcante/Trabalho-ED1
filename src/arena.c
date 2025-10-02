#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "fila.h"
#include "formas.h"

typedef struct arena{
    Fila FilaArena;
    double altura, largura;
}Starena;

Arena CriarArena(double largura, double altura){
    Starena *a = malloc(sizeof(Starena));
    if(a == NULL){
        printf("Não foi possível alocar memória para a criação da arena!\n");
        exit(1);
    }

    a->altura = altura;
    a->largura = largura;
    a->FilaArena = Criar_Fila();

    return ((Starena*)a);
} 


void InserirArena(Forma f, Arena *arena){
    Starena *a = ((Starena*)arena);
    
    InserirFila(a->FilaArena, f);
} 

Forma RetirarArena(Arena *arena){
    Starena *a = ((Starena*)arena);
    return RetirarFila(a->FilaArena);
}

int GetNumeroFormas(Arena *arena){
    Starena *a = ((Starena*)arena);
    return SizeFila(a->FilaArena);
} 

void SetLarguraArena(Arena *arena, double largura){
    Starena *a = ((Starena*)arena);
    a->largura = largura;
}

void SetAlturaArena(Arena *arena, double altura){
    Starena *a = ((Starena*)arena);
    a->altura = altura;
}

double GetLarguraArena(Arena *arena){
    return ((Starena*)arena)->largura;
}

double GetAlturaArena(Arena *arena){
    return ((Starena*)arena)->altura;
}