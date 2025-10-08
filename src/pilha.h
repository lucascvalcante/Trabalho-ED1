#ifndef PILHA_H
#define PILHA_H

typedef void *Forma;
typedef void *Pilha;
/*
    Arquivo .h relacionao a uma pilha
*/

/// @brief Cria uma nova pilha vazia
/// @return Ponteiro apontando para a pilha
Pilha Criar_Pilha();


/// @brief Insere um elemento no topo da pilha
/// @param p Ponteiro apontando para a pilha
/// @param f A forma que será inserida
void InserirPilha(Pilha p, Forma f);


/// @brief Retira um elemento do topo da pilha
/// @param p Ponteiro apontando para a pilha
/// @return O elemento que foi retirado
Forma RetirarPilha(Pilha p);


/// @brief Obtém o primeiro elemento da pilha sem removê-lo
/// @param p Ponteiro apontando para a pilha
/// @return Ponteiro para o topo da pilha
Forma TopoPilha(Pilha p);


/// @brief Libera toda a memória ocupada pela pilha
/// @param p Ponteiro apontando para a pilha
void KillPilha(Pilha p); 


/// @brief Verifica e retorna o tamanho da pilha
/// @param p Ponteiro apontando para a pilha
/// @return O tamanho da pilha
int SizePilha(Pilha p);

#endif