#include <stdio.h>
#include <stdlib.h>
#include "arena.h"
#include "fila.h"
#include "formas.h"
#include "chao.h"
#include "colisao.h"
#include "texto.h"
#include "linha.h"

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


void InserirArena(Forma f, Arena arena){
    Starena *a = ((Starena*)arena);
    
    InserirFila(a->FilaArena, f);
} 

Forma RetirarArena(Arena arena){
    Starena *a = ((Starena*)arena);
    return RetirarFila(a->FilaArena);
}

int GetNumeroFormas(Arena arena){
    Starena *a = ((Starena*)arena);
    return SizeFila(a->FilaArena);
} 

void SetLarguraArena(Arena arena, double largura){
    Starena *a = ((Starena*)arena);
    a->largura = largura;
}

void SetAlturaArena(Arena arena, double altura){
    Starena *a = ((Starena*)arena);
    a->altura = altura;
}

double GetLarguraArena(Arena arena){
    return ((Starena*)arena)->largura;
}

double GetAlturaArena(Arena arena){
    return ((Starena*)arena)->altura;
}

void KillArena(Arena arena){
    Starena *a = ((Starena*)arena);
    if(a == NULL){
        return;
    }

    while(GetNumeroFormas(arena)){
        Forma f = RetirarArena(arena);
        if(f != NULL){
            DestruirForma(f);
        }
    }

    KillFila(a->FilaArena);
    free(a);
}

void ProcessaArena(Arena arena, Chao chao, double *PontuacaoFinal, int *FormasEsmagadas, int *FormasClonadas, FILE *arquivotxt, Fila fila_svg){

    while(GetNumeroFormas(arena) >= 2){
        Forma f1 = RetirarArena(arena);
        Forma f2 = RetirarArena(arena);
        fprintf(arquivotxt, "\n[*] Analisando par: Forma ID %d vs Forma ID %d\n", GetIDForma(f1), GetIDForma(f2));
        if(FormaSobrepoe(f1, f2)){
            double AreaF1 = GetAreaForma(f1);
            double AreaF2 = GetAreaForma(f2);
            fprintf(arquivotxt, "\nSobreposição!. Área 1: %.2f, área 2: %.2f\n", AreaF1, AreaF2);

            if(AreaF1 < AreaF2){
                fprintf(arquivotxt, "Forma %d esmagada! Pontos: + %.2f\n", GetIDForma(f1), AreaF1);
                double x = GetXForma(f1);
                double y = GetYForma(f1);
                Texto asterisco = Criar_Texto(-1, x, y, "red", "red", 'm', "*", NULL);  
                InserirFila(fila_svg, Criar_Forma(TEXTO, asterisco));
                *PontuacaoFinal += AreaF1;
                (*FormasEsmagadas)++;
                DestruirForma(f1);
                InserirChao(chao, f2);

            }else if(AreaF1 >= AreaF2){

                fprintf(arquivotxt, "Forma %d muda a cor de borda da forma %d!\n", GetIDForma(f1), GetIDForma(f2));

                if(GetTipoForma(f1) == LINHA){
                    char *Corlinha = GetCorLinha(f1);
                    char *CorComplementar = GetCorComplementar(Corlinha);
                    SetCorbForma(f2, CorComplementar);
                    free(CorComplementar);
                }else{
                    SetCorbForma(f2, GetCorpForma(f1));
                }
                InserirChao(chao, f1);
                InserirChao(chao, f2);
                Forma clone1 = ClonarForma(f1);
                TrocaCoresForma(clone1);
                InserirChao(chao, clone1);
                (*FormasClonadas)++;
                fprintf(arquivotxt, "Forma %d clonada e enviada para o chão!\n", GetIDForma(f1));
            }

        } else{

            fprintf(arquivotxt, "Sem sobreposição. Ambas as formas voltam para o chão!\n");
            InserirChao(chao, f1);
            InserirChao(chao, f2);
        }
    }

    if(GetNumeroFormas(arena) == 1){
        Forma forma_restante = RetirarArena(arena);
        fprintf(arquivotxt, "\n[*]Forma restante: id %d retorna ao chão.\n", GetIDForma(forma_restante));
        InserirChao(chao, forma_restante);
    }
}




