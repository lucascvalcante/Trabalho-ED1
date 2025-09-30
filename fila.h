#ifndef FILA_H
#define FILA_H

typedef void *Forma;
typedef void *Fila;

/*
    Arquivo .h relacionado a uma fila
*/

/// @brief Cria uma nova fila vazia
/// @return Ponteiro apontando para a fila
Fila Criar_Fila();


/// @brief Insere elementos no final da fila
/// @param f Ponteiro apontando para a fila
/// @param f1 Forma que será inserida na fila
void InserirFila(Fila *f, Forma f1);


/// @brief Retira o primeiro elemento da fila
/// @param f Ponteiro para a fila
/// @return O elemento retirado
void RetirarFila(Fila *f);

/// @brief Obtém o primeiro elemento da fila sem removê-lo
/// @param f Ponteiro apontando para a fila
/// @return O elemento presente no ínicio da fila
Fila InicioFila(Fila *f);


/// @brief Obtém o elemento da fila após o primeiro
/// @param f Ponteiro apontando para a fila
/// @return Ponteiro para o próximo elemento em relação ao início 
Fila NexFila(Fila *f);


/// @brief Libera toda a memória alocada pela fila
/// @param f Ponteiro apontando para a fila
void KillFila(Fila *f);


/// @brief Retorna o tamanho atual da fila
/// @param f Ponteiro apontando para a fila
/// @return o tamanho
int SizeFila(Fila *f);


#endif