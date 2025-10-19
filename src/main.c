#include <stdio.h>
#include <stdlib.h>
#include "processador_qry.h"
#include "fila.h"
#include "chao.h"
#include "arena.h"
#include "processador_geo.h"
#include "svg.h"
#include "string.h"
#include "texto.h"


static void Criar_path(char *path, const char* diretorio_base, const char* nome_arquivo){ 
    if(diretorio_base != NULL && strlen(diretorio_base) > 0){
        sprintf(path, "%s/%s", diretorio_base, nome_arquivo);
    }else{
        strcpy(path, nome_arquivo);
    }
}

int main(int argc, char *argv[]){
    char *entrada = NULL;
    char *ArqGeo = NULL;
    char *saida = NULL;
    char *ArqQry = NULL;
    double pontos = 0.0;
    int formas_clonadas = 0, formas_esmagadas = 0;

    Arena arena = CriarArena(1000, 800);
    Repositorio repo = CriarRepositorio();
    Fila svg = Criar_Fila();
    

    for(int i = 1; i < argc; i++){ 
        if(strcmp((argv[i]), "-e") == 0 && i + 1 < argc){
            entrada = argv[++i];
        }else if(strcmp(argv[i], "-f") == 0 && i + 1 < argc){
            ArqGeo = argv[++i];
        }else if(strcmp(argv[i], "-o") == 0 && i + 1 < argc){
            saida = argv[++i];
        }else if(strcmp(argv[i], "-q") == 0 && i + 1 < argc){
            ArqQry = argv[++i];
        }
    }

   char pathGeo[1024];
   Criar_path(pathGeo, entrada, ArqGeo);

   char baseGeo[1024];
   char *aux = strrchr(ArqGeo, '/');
   strcpy(baseGeo, aux ? aux + 1 : ArqGeo);
   char *ponto_ext = strrchr(baseGeo, '.');
   if(ponto_ext) * ponto_ext = '\0';

   char PathSvg[1024];
   snprintf(PathSvg, sizeof(PathSvg), "%s/%s.svg", saida, baseGeo);

    Chao chao = ProcessaGeo(pathGeo);
    if(chao == NULL){
        printf("DEBUG: Não foi possível criar o chão!\n");
        exit(1);
    }

    printf("Geração do svg: %s\n", PathSvg);
    GerarSvg(PathSvg, GetFilaChao(chao));

    if(ArqQry != NULL){
        char path_qry[1024];
        Criar_path(path_qry, entrada, ArqQry);

        char nome_qry[1024];
        char *ultimo_slash_qry = strrchr(ArqQry, '/');
        strcpy(nome_qry, ultimo_slash_qry ? ultimo_slash_qry + 1 : ArqQry);
        ponto_ext = strrchr(nome_qry, '.');
        if(ponto_ext) *ponto_ext = '\0';

        char path_svg_final[1024];
        char path_txt_final[1024];
        snprintf(path_svg_final, sizeof(path_svg_final), "%s/%s-%s.svg", saida, baseGeo, nome_qry);
        snprintf(path_txt_final, sizeof(path_txt_final), "%s/%s-%s.txt", saida, baseGeo, nome_qry);

        ProcessarQry(repo, chao, path_qry, path_txt_final, arena, &pontos, svg, &formas_clonadas, &formas_esmagadas);
        
        while(SizeFila(svg) > 0){
            Forma anotacao = RetirarFila(svg);
            if(anotacao != NULL){
                InserirChao(chao, anotacao);
            }
        }
        
        printf("Gerando svg final: %s\n", path_svg_final);
        GerarSvg(path_svg_final, GetFilaChao(chao));
    }

    InserirFormasCarregadorChao(repo, chao);
    InserirFormasDisparadorChao(repo, chao);

    KillRepositorio(repo);
    DestruirChao(chao);
    KillArena(arena);

    while(SizeFila(svg) > 0){
        Forma anotacao = RetirarFila(svg);
        if(anotacao != NULL){
            DestruirForma(anotacao);
        }
    }
    KillFila(svg);

    printf("Programa finalizado!\n");
    return 0;
}