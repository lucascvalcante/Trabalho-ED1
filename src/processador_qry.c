#include "processador_qry.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chao.h"
#include "disparador.h"
#include "carregador.h"
#include "formas.h"
#include "fila.h"
#include "linha.h"
#include "arena.h"

#define MAX 1000

typedef struct Repositorio{ 
    Carregador *c[MAX];
    int numCarregadores;
    Disparador *d[MAX];
    int numDisparadores;
}Strepositorio;


typedef struct txt{
    FILE* arquivotxt;
    char* relatorio;
}StTxt;

typedef struct{
    char* linha_buffer;
    Repositorio repo;
    Arena a;
    Chao c;
    FILE* arquivoTxt;
    Fila filaSvg;
    int* totalDisparos;
}CommandContext;

/*
    --- FUNÇÕES AUXILIARES: ---
*/

Repositorio CriarRepositorio(){
    Strepositorio *repo = malloc(sizeof(Strepositorio));
    if(repo == NULL){
        printf("Erro ao criar o repositório!\n");
        return NULL;
    }
    repo->numCarregadores = 0;
    repo->numDisparadores = 0;
    return repo;
} 


void KillRepositorio(Repositorio r){
    Strepositorio *repo = ((Strepositorio*)r);
    if(r == NULL){
        return;
    }

    for(int i = 0; i < repo->numCarregadores; i++){
        KillCarregador(repo->c[i]);
    }
    for(int i = 0; i < repo->numDisparadores; i++){
        KillDisparador(repo->d[i]);
    }
    free(repo);
}

Disparador SeekDisparador(Repositorio r, int id){
    Strepositorio *repo = ((Strepositorio*)r);
    if(r == NULL){
        return NULL;
    } 
    
    for(int i = 0; i < repo->numDisparadores; i++){
        if(GetIDDisparador(repo->d[i]) == id){
            return repo->d[i];
        } 
    }
    if(repo->numDisparadores < MAX){
        Disparador novo = CriarDisparador(id, 0, 0);
        repo->d[repo->numDisparadores++] = novo;
        return novo;
    }
    return NULL;
}

Carregador SeekCarregador(Repositorio r, int id){
    Strepositorio *repo = ((Strepositorio*)r);
    if(r == NULL){
        return NULL;
    } 
    
    for(int i = 0; i < repo->numCarregadores; i++){
        if(GetIDCarregador(repo->c[i]) == id){
            return repo->c[i];
        }
    }
    if(repo->numCarregadores < MAX){
        Carregador novo = CriarCarregador(id);
        repo->c[repo->numCarregadores++] = novo;
        return novo;
    }
    return NULL;   
}

static void EscreverDados(void* item, void* aux){
    Forma f = (Forma*)item;
    StTxt *dados = (StTxt*)aux;
    InserirDadosTxt(f, dados->arquivotxt, dados->relatorio);
    
} 

static void ReportarForma(void* item, void* aux){
    Forma f = (Forma*)item;
    FILE* arquivoTxt = (FILE*)aux;
    InserirDadosTxt(f, arquivoTxt, NULL);
}


static int handle_pd(CommandContext* ctx){
    int id;
    double x, y;
    sscanf(ctx->linha_buffer, "pd %i %lf %lf", &id, &x, &y);
    Disparador d = SeekDisparador(ctx->repo, id);
    if(d){
        SetPosicaoDisparador(d, x, y);
        return 1;
    }
    return 0;
}

static int handle_lc(CommandContext* ctx){
    int id, n;
    sscanf(ctx->linha_buffer, "lc %i %i", &id, &n);
    Carregador c = SeekCarregador(ctx->repo, id);
    if(c){
        Fila FormasCarregadas = AdicionaNCarregador(ctx->c, c, n);
        if(FormasCarregadas != NULL){
            StTxt info_txt = {.arquivotxt = ctx->arquivoTxt, .relatorio = NULL};
            PassthroughQueue(FormasCarregadas, EscreverDados, &info_txt);
            KillFila(FormasCarregadas);
        }
        return 1;
    }
    return 0;
}

static int handle_atch(CommandContext* ctx){
    int id1, id2, id3;
    sscanf(ctx->linha_buffer, "atch %i %i %i", &id1, &id2, &id3);
    Disparador d = SeekDisparador(ctx->repo, id1);
    Carregador c1 = SeekCarregador(ctx->repo, id2);
    Carregador c2 = SeekCarregador(ctx->repo, id3);

    if(d && c1 && c2){
        DisparadorAtch(d, c1, c2);
        return 1;
    }
    return 0;
}

static int handle_shft(CommandContext* ctx){
    int id, n;
    char botao;
    sscanf(ctx->linha_buffer, "shft %i %c %i", &id, &botao, &n);
    Disparador d = SeekDisparador(ctx->repo, id);
    if(d){
        DisparadorShft(d, botao, n);
        Forma FormaFim = GetFormaEmDisparo(d);
        if(FormaFim){
            InserirDadosTxt(FormaFim, ctx->arquivoTxt, NULL);
        }else{
            fprintf(ctx->arquivoTxt, "Nenhuma forma na posição de disparo!\n");
        }
        return 1;
    }
    return 0;
}

static int handle_dsp(CommandContext* ctx){
    int id; 
    double dx, dy;
    char flag_visual[4] = "";
    sscanf(ctx->linha_buffer, "dsp %d %lf %lf %3s", &id, &dx, &dy, flag_visual);
    Disparador d = SeekDisparador(ctx->repo, id);
    if(d){
        double x1 = GetXDisparador(d);
        double y1 = GetYDisparador(d);
        Forma FormaDisparada = DisparaDisparador(d, dx, dy);
        if(FormaDisparada){
            (*(ctx->totalDisparos))++;
            InserirArena(FormaDisparada, ctx->a);
            InserirDadosTxt(FormaDisparada, ctx->arquivoTxt, NULL);
            if(strcmp(flag_visual, "v") == 0){
                double x2 = GetXForma(FormaDisparada);
                double y2 = GetYForma(FormaDisparada);

                Forma forma_linha_cinza1 = Criar_Forma(LINHA, Criar_Linha(-1, x2, y1, x2, y2, "grey"));
                if(forma_linha_cinza1){
                    InserirFila(ctx->filaSvg, forma_linha_cinza1); 
                    printf("DEBUG: Linha cinza 1 inserida na fila svg!\n");
                }else{
                    printf("DEBUG: Erro ao inserir linha cinza 1 no svg!\n");
                }

                Forma forma_linha_cinza2 = Criar_Forma(LINHA, Criar_Linha(-1, x1, y2, x2, y2, "grey"));
                if(forma_linha_cinza2){
                    InserirFila(ctx->filaSvg, forma_linha_cinza2);
                    printf("DEBUG: Linha cinza 2 inserida no svg!\n");
                }else{
                    printf("DEBUG: Erro ao criar linha cinza 2 e inserir no svg!\n");
                }

                Forma forma_linha_roxa = Criar_Forma(LINHA, Criar_Linha(-1, x1, y1, x2, y2, "purple"));
                if(forma_linha_roxa){
                    InserirFila(ctx->filaSvg, forma_linha_roxa);
                    printf("DEBUG: Linha roxa inserida no svg!\n");
                }else{
                    printf("DEBUG>: Não foi possível criar linha roxa e inserir no svg!\n");
                }
        
            }
        }else{
            fprintf(ctx->arquivoTxt, "Falha no disparo!\n");
        }
        return 1;
    }
    return 0;
}

static int handle_rjd(CommandContext* ctx){
    int id;
    char botao;
    double dx, dy, ix, iy;

    sscanf(ctx->linha_buffer, "rjd %i %c %lf %lf %lf %lf", &id, &botao, &dx, &dy, &ix, &iy);
    Disparador d = SeekDisparador(ctx->repo, id);
    if(d){
        Fila FormasDisparadas = RajadaDisparados(d, botao, dx, dy, ix, iy, ctx->a);
        if(FormasDisparadas){
            (*(ctx->totalDisparos)) += SizeFila(FormasDisparadas);
            PassthroughQueue(FormasDisparadas, ReportarForma, ctx->arquivoTxt);
            KillFila(FormasDisparadas);
        }
        return 1;
    }
    return 0;
}

static int handle_calc(CommandContext* ctx, double* pontuacao, int* clonadas, int* esmagadas){
    ProcessaArena(ctx->a, ctx->c, pontuacao, esmagadas, clonadas, ctx->arquivoTxt, ctx->filaSvg);
    return 1;
} 

/*
    --- FUNÇÕES PRINCIPAIS: ---
*/



void ProcessarQry(Repositorio repo, Chao chao, const char *path_qry, const char *path_txt, Arena arena, double *pontuacao_final, Fila fila_svg, int *formas_clonadas, int *formas_esmagadas){
    Strepositorio *r = ((Strepositorio*)repo);
    if(r == NULL){
        return;
    }    

    FILE *Arquivo_qry = fopen(path_qry, "r");
    if(Arquivo_qry == NULL){
        printf("Erro ao ler o arquivo qry!\n");
        return;
    }

    FILE *Arquivo_txt = fopen(path_txt, "w");
    if(Arquivo_txt == NULL){
        printf("Erro ao abrir o arquivo txt!\n");
        fclose(Arquivo_qry);
        return;
    }

    int num_instrucoes = 0;
    int total_disparos = 0;
    *formas_esmagadas = 0;
    *formas_clonadas = 0;

    char linha_buffer[512];
    char comando[16]; 

    CommandContext ctx = {
        .linha_buffer = linha_buffer,
        .repo = repo,
        .a = arena,
        .c = chao,
        .arquivoTxt = Arquivo_txt,
        .filaSvg = fila_svg,
        .totalDisparos = &total_disparos
    };

    while(fgets(linha_buffer, sizeof(linha_buffer), Arquivo_qry) != NULL){
        linha_buffer[strcspn(linha_buffer, "\n")] = 0;

        if(sscanf(linha_buffer, "%s", comando) != 1){
            continue;
        }

        fprintf(Arquivo_txt, "[*] %s\n", linha_buffer);
        int sucesso = 0;

        if(strcmp(comando, "pd") == 0) sucesso = handle_pd(&ctx);
        else if(strcmp(comando, "lc") == 0) sucesso = handle_lc(&ctx);
        else if(strcmp(comando, "atch") == 0) sucesso = handle_atch(&ctx);
        else if(strcmp(comando, "shft") == 0) sucesso = handle_shft(&ctx);
        else if(strcmp(comando, "dsp") == 0) sucesso = handle_dsp(&ctx);
        else if(strcmp(comando, "rjd") == 0) sucesso = handle_rjd(&ctx);
        else if(strcmp(comando, "calc") == 0) sucesso = handle_calc(&ctx, pontuacao_final, formas_clonadas, formas_esmagadas);

        if(sucesso){
            num_instrucoes++;
        }
    }

    fprintf(Arquivo_txt, "\nRelatorio final:\n");
    fprintf(Arquivo_txt, "\nPontuacao total: %.2f\nTotal de instruções feitas: %d\nTotal de disparos: %d\nFormas esmagadas: %i\nFormas clonadas: %i",
    *pontuacao_final, num_instrucoes, total_disparos, *formas_esmagadas, *formas_clonadas);

    fclose(Arquivo_qry);
    fclose(Arquivo_txt);

}

void InserirFormasCarregadorChao(Repositorio repo, Chao chao){
    Strepositorio *r = ((Strepositorio*)repo);
    if(r == NULL){
        return;
    }     

    for(int i = 0; i < r->numCarregadores; i++){
        Carregador carregador = r->c[i];

        while(GetSizeCarregador(carregador) > 0){
            Forma f = RetirarCarregador(carregador);
            if(f != NULL){
                InserirChao(chao, f);
            }
        }
    }
}

void InserirFormasDisparadorChao(Repositorio repo, Chao chao){
    Strepositorio *r = ((Strepositorio*)repo);
    if(r == NULL){
        return;
    } 

    for(int i = 0; i < r->numDisparadores; i++){
        Disparador disp = r->d[i];
        Forma f = RetirarFormaEmDisparo(disp);

        if(f != NULL){
            InserirChao(chao, f);
        }
    }    
}



