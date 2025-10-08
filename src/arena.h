#ifndef ARENA_H
#define ARENA_H
#include "fila.h"
#include "formas.h"

/*/
    Arquivo .h relacionado a uma "arena", uma fila representando o cenário do jogo, onde as formas ficam armazenadas
*/

typedef void *Arena;
typedef void *Forma;

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



void ProcessamentoArena(Arena a);

#endif