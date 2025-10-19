#ifndef PROCESSADOR_QRY_H
#define PROCESSADOR_QRY_H
#include "chao.h"
#include "arena.h"
#include "fila.h"
#include "disparador.h"

typedef void *Repositorio;


/// @brief Aloca memória para a criação de um repositório de objetos
/// @return Ponteiro para o repositório
Repositorio CriarRepositorio();


/// @brief Libera toda a memória alocada pelo repositório 
/// @param r Ponteiro para o repositório
void KillRepositorio(Repositorio r);


/// @brief Devolve todas as formas presentes no carregador de volta para o chão
/// @param repo Ponteiro para o repositório contendo as formas
/// @param chao Ponteiro para o chão
void InserirFormasCarregadorChao(Repositorio r, Chao chao);

/// @brief Devolve todas as formas presentes no disparador para o chão
/// @param repo Ponteiro para o repositório contendo as formas
/// @param chao Ponteiro para o chão
void InserirFormasDisparadorChao(Repositorio repo, Chao chao);

/// @brief Lê e processa um arquivo .qry executando as ações pedidas
/// @param r Ponteiro para o repositorio que armazena os disparadores e carregadores
/// @param chao Ponteiro para o chão, de onde as formas são carregadas
/// @param CaminhoQry Caminho para o arquivo .qry a ser lido
/// @param CaminhoTxt Caminho para o arquivo de texto de saída, onde o relatório será escrito
/// @param a Ponteiro para a arena, o 'inventário' de formas
/// @param Pontuacao Ponteiro para uma variável que acumula a pontuação final do jogo
/// @param FilaSvg Ponteiro para adicionar elementos visuais no svg
/// @param FormasClonadas Ponteiro para um contador de formas clonadas
/// @param FormasEsmagas Ponteiro para um contador de formas esmagadas
void ProcessarQry(Repositorio r, Chao chao, const char *CaminhoQry, const char *CaminhoTxt, Arena a, double *Pontuacao, Fila FilaSvg, int *FormasClonadas, int *FormasEsmagas);


#endif