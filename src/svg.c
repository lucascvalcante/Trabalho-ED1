#include <stdio.h>
#include <stdlib.h>
#include "svg.h"


typedef struct Svg{
    FILE* arquivo;
}Stsvg;


Svg CriarSvg(const char* nomearquivo, double largura, double altura){
    Stsvg *s = malloc(sizeof(Stsvg));
    if(s == NULL){
        printf("Não foi possível alocar memória para a criação do svg!\n");
        exit(1);
    }

    s->arquivo = fopen(nomearquivo, "w");
    if(s->arquivo == NULL){
        printf("Não foi possível abrir o arquivo para escrita!\n");
        free(s);
        exit(1);
    }

    fprintf(s->arquivo, "<svg width=\"%.2f\" height=\"%.2f\" xmlns=\"http://www.w3.org/2000/svg\">\n", largura, altura);

    return s;
} 

void InserirCirculoSvg(Svg svg, Circulo c){
    Stsvg *s = ((Stsvg*)svg);

    if(s == NULL || c == NULL || s->arquivo == NULL){
        return;
    }

    double x = GetXCirculo(c);
    double y = GetYCirculo(c);
    double r = GetRCirculo(c);
    char* Corb = GetCorbCirculo(c);
    char* Corp = GetCorpCirculo(c);

    fprintf(s->arquivo, "\t<circle cx=\"%.2f\" cy=\"%.2f\" r=\"%.2f\" stroke=\"%s\" fill=\"%s\" />\n", x, y, r, Corb, Corp);
}

void InserirRetanguloSvg(Svg svg, Retangulo r){
    Stsvg *s = ((Stsvg*)svg);

    if(s == NULL || r == NULL || s->arquivo == NULL){
    return;
    }

    double x = GetXRetangulo(r);
    double y = GetYRetangulo(r);
    double w = GetWRetangulo(r);
    double h = GetHRetangulo(r);
    char *Corb = GetCorbRetangulo(r);
    char *Corp = GetCorpRetangulo(r);

    fprintf(s->arquivo, "\t<rect x=\"%.2f\" y=\"%.2f\" width=\"%.2f\" height=\"%.2f\" stroke=\"%s\" fill=\"%s\" />\n", x, y, w, h, Corb, Corp);
     
} 

void InserirTextoSvg(Svg svg, Texto t){
    Stsvg *s = ((Stsvg*)svg);

    if(s == NULL || t == NULL || s->arquivo == NULL){
    return;
    }

    double x = GetXTexto(t);
    double y = GetYTexto(t);
    char* Corp = GetCorpTexto(t);
    char *Corb = GetCorbTexto(t);
    char Ancorachar = GetATexto(t);
    char* Conteudo = GetTxtoTexto(t);

    char* Ancorasvg;
    switch (Ancorachar){
    case 'i':
        Ancorasvg = "start";
        break;
    case 'm': 
        Ancorasvg = "middle";
        break;
    case 'f':
        Ancorasvg = "end";
        break;
    default:
        Ancorasvg = "start";
        break;
    }

    Estilo st = GetEstilo(t);
    if(st != NULL){
        char *fFamily = GetfFamily(st);
        char *fWeight = GetfWeight(st);
        char *fSize = GetfSize(st);

    fprintf(s->arquivo, "\t<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1px\" text-anchor=\"%s\" font-family=\"%s\" font-weight=\"%s\" font-size=\"%s\">%s</text>\n",
                x, y, Corp, Corb, Ancorasvg, fFamily, fWeight, fSize, Conteudo);

    }else{
        fprintf(s->arquivo, "\t<text x=\"%.2f\" y=\"%.2f\" fill=\"%s\" stroke=\"%s\" stroke-width=\"1px\" text-anchor=\"%s\">%s</text>\n",
                x, y, Corp, Corb, Ancorasvg, Conteudo);
    }
}

void InserirLinhaSvg(Svg svg, Linha l){
    Stsvg *s = ((Stsvg*)svg);

    if(s == NULL || l == NULL || s->arquivo == NULL){
        return;
    } 

    double x1 = GetX1Linha(l);
    double y1 = GetY1Linha(l);
    double x2 = GetX2Linha(l);
    double y2 = GetY2Linha(l);
    char *Cor = GetCorLinha(l);

    fprintf(s->arquivo, "\t<line x1=\"%.2f\" y1=\"%.2f\" x2=\"%.2f\" y2=\"%.2f\" stroke=\"%s\" />\n", x1, y1, x2, y2, Cor);
}

void FinalizarSvg(Svg svg){
    Stsvg *s = ((Stsvg*)svg);

    if(s == NULL || s->arquivo == NULL){
        return;
    }

    fprintf(s->arquivo, "</svg>\n");
    fclose(s->arquivo);
    free(s);
}