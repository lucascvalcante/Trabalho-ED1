#ifndef ARENA_H
#define ARENA_H

#include "formas.h"
#include "svg.h"
#include "chao.h"
#include "fila.h"
#include <stdio.h>

/*/
    Arquivo .h relacionado a uma "arena", uma fila representando o cenário do jogo, onde as formas ficam armazenadas
*/

typedef void *Arena;
typedef void *Forma;
typedef void *Svg;
typedef void *Chao;
typedef void *Fila;

/// @brief Armazena memória para a criação da arena do jogo
/// @param largura Tamanho da largura da arena
/// @param altura Tamanho da altura da arena
/// @return Um ponteiro para a arena
Arena CriarArena(double largura, double altura); 


/// @brief Insere um elemento (forma) na arena
/// @param f Ponteiro para a forma
/// @param a Ponteiro para a arena
void InserirArena(Forma f, Arena a);


/// @brief Retira um elemento da arena
/// @param a Ponteiro para a arena
/// @return O elemento (forma) que será removido
Forma RetirarArena(Arena a);


/// @brief Retorna o número de formas presentes atualmente na arena
/// @param a Ponteiro para a arena
/// @return O número de formas
int GetNumeroFormas(Arena a);


/// @brief Define uma largura para a arena
/// @param a Ponteiro para a arena
/// @param largura A nova largura
void SetLarguraArena(Arena a, double largura); 


/// @brief Define uma altura para a arena
/// @param a Ponteiro para a arena
/// @param altura A nova altura
void SetAlturaArena(Arena a, double altura);


/// @brief Retorna a altura atual da arena
/// @param a Ponteiro para a arena
/// @return A altura
double GetAlturaArena(Arena a);


/// @brief Retorna a largura atual da arena
/// @param a Ponteiro para a arena
/// @return A largura
double GetLarguraArena(Arena a);


/// @brief Libera toda a memória alocada pela arena
/// @param a Ponteiro apontando para a arena
void KillArena(Arena a);


/// @brief Processa a pontuação da rodada. Consome as formas da arena e as envia de volta para o chão,
/// atualizando as estatísticas e pontuação do processo
/// @param a Ponteiro para a arena com as formas que foram disparadas
/// @param c Ponteiro para o chão onde as formas retornam após o processo
/// @param Pontuacaofinal Um ponteiro para a variável de pontuação
/// @param FormasEsmagadas Um ponteiro para a variével com o número de formas esmagadas
/// @param FormasClonadas Um ponteiro para a variável com o número de formas clonadas
/// @param arquivotxt A arquivo .txt para registrar os acontecimentos da rodada
void ProcessaArena(Arena a, Chao c, double *Pontuacaofinal, int *FormasEsmagadas, int *FormasClonadas, FILE *arquivotxt, Fila fila_svg);


/// @brief Passa por todas as formas presentes na arena e as desenha em um arquivo svg
/// @param a 
/// @param svg 
void ArenaDesenharSvg(Arena a, Svg svg);


#endif