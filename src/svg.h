#ifndef SVG_H
#define SVG_H

#include "texto.h"
#include "circulo.h"
#include "linha.h"
#include "retangulo.h"

/*
    Arquivo .h relacionado a manipulação do arquivo em formato svg. Com funções para escrever e inserir formas no arquivo
*/

typedef void* Svg;

/// @brief Cria, abre e escreve o cabeçalho SVG em um arquivo
/// @param nomearquivo O nome do arquivo que será criado
/// @param largura A largura da imagem SVG
/// @param altura A altura da imagem SVG
/// @return Um ponteiro para a estrutura SVG
Svg CriarSvg(const char* nomearquivo, double largura, double altura);


/// @brief Insere a forma 'círculo' no svg
/// @param svg Ponteiro para a estrutura svg
/// @param c A forma círculo que será desenhada
void InserirCirculoSvg(Svg svg, Circulo c);


/// @brief Insere a forma 'retângulo' no svg
/// @param svg Ponteiro para a estrutura svg
/// @param r A forma retângulo que será desenhada
void InserirRetanguloSvg(Svg svg, Retangulo r);


/// @brief Insere a forma 'texto' no svg
/// @param svg Ponteiro para a estrutura svg
/// @param t A forma texto que será desenhada
void InserirTextoSvg(Svg svg, Texto t);


/// @brief Insere a forma 'círculo' no svg
/// @param svg Ponteiro para a estrutura svg
/// @param l A forma círculo que será desenhada
void InserirLinhaSvg(Svg svg, Linha l);


/// @brief Finaliza e fecha o arquivo svg
/// @param svg Ponteiro para a estrutura svg
void FinalizarSvg(Svg svg);


#endif