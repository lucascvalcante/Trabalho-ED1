#ifndef CARREGADOR_H
#define CARREGADOR_H
#include "pilha.h"
#include "formas.h"

typedef enum{
    LadoEsquerdo,
    LadoDireito
}LadoCarregador;

typedef void *Carregador;
/*
    Arquivo .h relacionado a um carregador, local onde as formas serão retiradas para serem disparadas
*/


/// @brief Cria e retorna um carregador
/// @param lado O lado em que o carregador irá operar(direito ou esquerdo)
/// @return Ponteiro apontando para o carregador
Carregador CriarCarregador(LadoCarregador lado);


/// @brief Adiciona uma forma no carregador
/// @param c Ponteiro apontando para o carregador
/// @param f Ponteiro apontando para a forma que será inserida
void InserirCarregador(Carregador c, Forma f);


/// @brief Retira e retorna uma forma que está no topo do carregador
/// @param c Ponteiro para o carregador
/// @return A forma retirada
Forma RetirarCarregador(Carregador c);


/// @brief Retorna o número de formas que está presente no atual momento no carregador
/// @param c Ponteiro para o carregador
/// @return Número de formas
int GetSizeCarregador(Carregador c);


/// @brief Retorna um ponteiro para a forma que está atualmente na posição de disparo 
/// @param c Ponteiro para o carregador
/// @return Um ponteiro para a forma
Forma VerFormaCarregador(Carregador c);


/// @brief Libera toda a memória alocada pelo carregador
/// @param c Ponteiro para o carregador
void KillCarregador(Carregador c);


#endif
