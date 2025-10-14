#include "processador_geo.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "chao.h"
#include "linha.h"
#include "texto.h"
#include "retangulo.h"
#include "circulo.h"

Chao ProcessaGeo(const char *caminhoGeo, Estilo **Estilos_criados, int *num_estilos){
    FILE *arqGeo = fopen(caminhoGeo, "r");
    if(arqGeo == NULL){
        printf("Não foi possível realizar a leitura do arquivo!\n");
        return NULL;
    }

    char buffer[1024];
    Chao chao = NULL;
    Estilo estiloAtual = NULL;

    int capacidade_estilos = 4; 
    *num_estilos = 0;
    *Estilos_criados = malloc(capacidade_estilos * sizeof(Estilo));
    if (*Estilos_criados == NULL) {
        exit(1); 
    }

    while (fgets(buffer, sizeof(buffer), arqGeo) != NULL){
        if (buffer[0] == '\n' || buffer[0] == '#') {
            continue;
        }

        char comando[16];
        sscanf(buffer, "%s", comando);

        if (strcmp(comando, "nx") == 0){
            double w, h;
            sscanf(buffer, "%*s %lf %lf", &w, &h);
            if(chao == NULL){
                chao = Criar_Chao(w, h); 
            }
        } 
        else if (strcmp(comando, "ts") == 0) {
            if (*num_estilos >= capacidade_estilos) {
                capacidade_estilos *= 2;
                Estilo *temp = realloc(*Estilos_criados, capacidade_estilos * sizeof(Estilo));
                if (temp == NULL) {
                    printf("erro ao alocar memória para os estilos!\n.\n");
                    exit(1);
                }
                *Estilos_criados = temp;
            }

            char fFamily[100], fWeight[100], fSize[100];
            sscanf(buffer, "%*s %s %s %s", fFamily, fWeight, fSize);
            
            estiloAtual = Criar_Estilo(fFamily, fWeight, fSize);
            
            (*Estilos_criados)[*num_estilos] = estiloAtual;
            (*num_estilos)++;
        }
        else {
            if (chao == NULL) {
                continue;
            }

            if (strcmp(comando, "c") == 0) {
                int id; double x, y, r; char corb[100], corp[100];
                sscanf(buffer, "%*s %d %lf %lf %lf %s %s", &id, &x, &y, &r, corb, corp);
                
                Circulo c = Criar_Circulo(id, x, y, r, corp, corb);
                Forma f = Criar_Forma(CIRCULO, c);
                InserirChao(chao, f);
            }
            else if (strcmp(comando, "r") == 0) {
                int id; double x, y, w, h; char corb[100], corp[100];
                sscanf(buffer, "%*s %d %lf %lf %lf %lf %s %s", &id, &x, &y, &w, &h, corb, corp);

                Retangulo rt = Criar_Retangulo(id, x, y, w, h, corp, corb);
                Forma f = Criar_Forma(RETANGULO, rt);
                InserirChao(chao, f);
            }
            else if (strcmp(comando, "l") == 0) {
                int id; double x1, y1, x2, y2; char cor[100];
                sscanf(buffer, "%*s %d %lf %lf %lf %lf %s", &id, &x1, &y1, &x2, &y2, cor);

                Linha l = Criar_Linha(id, x1, y1, x2, y2, cor);
                Forma f = Criar_Forma(LINHA, l);
                InserirChao(chao, f);
            }
            else if (strcmp(comando, "t") == 0) {
                int id, chars_lidos = 0;
                double x, y; char corb[100], corp[100], a;
                
                sscanf(buffer, "%*s %d %lf %lf %s %s %c %n", &id, &x, &y, corb, corp, &a, &chars_lidos);
                char *conteudo_texto = buffer + chars_lidos;
                conteudo_texto[strcspn(conteudo_texto, "\r\n")] = 0;
                
                if (estiloAtual == NULL) {
                    if(*num_estilos >= capacidade_estilos){
                        capacidade_estilos *= 2;
                        Estilo *temp = realloc(*Estilos_criados, capacidade_estilos * sizeof(Estilo));
                        if(temp == NULL){
                            exit(1);
                        }
                        *Estilos_criados = temp;
                    }

                    estiloAtual = Criar_Estilo("sans-serif", "normal", "12");
                    (*Estilos_criados)[*num_estilos] = estiloAtual;
                    (*num_estilos)++;
                }

                Texto t = Criar_Texto(id, x, y, corb, corp, a, conteudo_texto, estiloAtual);
                Forma f = Criar_Forma(TEXTO, t);
                InserirChao(chao, f);
            }
        }
    }

    fclose(arqGeo);
    return chao;
}