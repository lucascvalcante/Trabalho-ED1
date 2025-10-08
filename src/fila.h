#ifndef FILA_H
#define FILA_H

#include "formas.h"
#include "texto.h"

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
void InserirFila(Fila f, Forma f1);


/// @brief Retira o primeiro elemento da fila
/// @param f Ponteiro para a fila
/// @return O elemento retirado
Forma RetirarFila(Fila f);

/// @brief Obtém o primeiro elemento da fila sem removê-lo
/// @param f Ponteiro apontando para a fila
/// @return O elemento presente no ínicio da fila
Forma InicioFila(Fila f);


/// @brief Libera toda a memória alocada pela fila
/// @param f Ponteiro apontando para a fila
void KillFila(Fila f);


/// @brief Retorna o tamanho atual da fila
/// @param f Ponteiro apontando para a fila
/// @return o tamanho
int SizeFila(Fila f);


/// @brief Percorre uma fila e realiza uma função de ação em cada elemento
/// @param f Ponteiro apontando para a fila
/// @param tipo Tipo da forma presente na fila
/// @param fs Ponteiro para o arquivo svg onde as formas serão inseridas
/// @param st Estilo de texto que será usado elementos do tipo texto
void PassthroughQueue(Fila f, FILE *fs, Estilo st);


/// @brief Seleciona a ação que será realizada em um elemento da fila
/// @param f Ponteiro apontando para uma forma
/// @param tipo Tipo da forma que será usada(Círculo, retângulo, etc)
/// @param fs Ponteiro para o arquivo svf onde as formas serão inseridas
/// @param st Estilo do texto que será usado para elementos do tipo texto
void SelectQueue(Forma f, FILE *fs, Estilo st);


#endif