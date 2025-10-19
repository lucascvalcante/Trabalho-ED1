#ifndef CHAO_H
#define CHAO_H
#include "formas.h"
#include "fila.h"

typedef void *Chao;
typedef void *Fila;
/*
    Arquivo .h relacionado ao "chão", elemento lúdico de armazenamento das formas que ainda não estão em jogo, como um repositório
*/


/// @brief Cria e retorna um ponteiro para o chão
/// @return Ponteiro para o chão
Chao Cria_chao();


/// @brief Insere um novo elemento(forma) no chão
/// @param c Ponteiro para o chão
/// @param f A forma que será inserida
void InserirChao(Chao c, Forma f);


/// @brief Retira e retorna a primeira forma do chão
/// @param c Ponteiro para o chão
/// @return A forma retirada
Forma RetiraChao(Chao c);


/// @brief Libera toda a memória armazenada pelo chão
/// @param c Ponteiro apontando para o chão
void DestruirChao(Chao c);

/// @brief Retorna a fila do chão
/// @param c Ponteiro apontando para o chão
/// @return A fila do chão
Fila GetFilaChao(Chao c);


#endif