#ifndef DISPARADOR_H
#define DISPARADOR_H
#include "carregador.h"
#include "formas.h"
#include "arena.h"

typedef void *Disparador;
/*
    Arquivo .h relacionado a um disparador de formas
*/

/// @brief Cria e retorna um novo disparador
/// @param id Número de identificação do disparador
/// @param x Coordenada 'x' do disparador
/// @param y Coordenada 'y' do disparador
/// @return Um ponteiro para o novo disparador
Disparador CriarDisparador(int id, double x, double y);


/// @brief Retorna o número de identificação do disparador
/// @param d Ponteiro para o disparador
/// @return O número de identificação
int GetIDDisparador(Disparador d); 


/// @brief Retorna a coordenada 'X' do disparador
/// @param d Ponteiro para o disparador
/// @return A coordenada 'X'
double GetXDisparador(Disparador d);


/// @brief Retorna a coordenada 'Y' do disparador
/// @param d Ponteiro para o disparador
/// @return A coordenada 'Y'
double GetYDisparador(Disparador d);


/// @brief Posiciona o disparador em uma nova coordenada
/// @param d Ponteiro para o disparador
/// @param x Coordenada 'X' do disparador
/// @param y Coordenada 'Y' do disparador
void SetPosicaoDisparador(Disparador d, double x, double y);


/// @brief Retorna a forma que será disparada
/// @param d Ponteiro para o disparador
/// @return A forma 'engatilhada'
Forma GetFormaEmDisparo(Disparador d);


/// @brief Anexa os disparadores do carregador
/// @param d Ponteiro para o disparador
/// @param esq Carregador esquerdo
/// @param dir Carregador direito
void DisparadorAtch(Disparador d, Carregador esq, Carregador dir);


/// @brief Coloca a carga do carregador em posição de disparo
/// @param d Ponteiro para o disparador
/// @param botao Define qual lado do disparador será usado(esquerdo/direito)
/// @param n Número de vezes que o botão será apertado
/// @return Um ponteiro para a forma que ficou no ponto de disparo
/// @details Caso ja houvesse alguma carga na posição de disparo, transfere essa carga para o topo do carregador contrário
Forma DisparadorShft(Disparador d, char botao, int n);


/// @brief Dispara as formas de um carregador em uma rajada sequencial
/// @param d Ponteiro para o disparador que efetuará os disparos
/// @param botao Caractere que define o carregador a ser usado(e-esquerdo/d-direito)
/// @param dx Componente 'X' do vetor de direção do primeiro disparo
/// @param dy Componente 'Y' do vetor de direção do primeiro disparo
/// @param ix Valor a ser somado a 'dx' a cada disparo
/// @param iy Valor a ser somado a 'dy' a cada disparo
/// @param a Ponteiro apontando para a arena
/// @return Uma fila contendo ponteiros para todas as formas que foram disparadas
Fila RajadaDisparados(Disparador d, char botao, double dx, double dy, double ix, double iy, Arena a);


/// @brief Disparada a forma que esta engatilhada
/// @param d Ponteiro para o disparador
/// @param dx Distância em 'X' que a forma será disparada
/// @param dy Distância em 'Y' que a forma será disparada
/// @return Um ponteiro para a forma que foi disparada
Forma DisparaDisparador(Disparador d, double dx, double dy);


/// @brief Libera toda a memória alocada pelo disparador
/// @param d Ponteiro apontando para o disparador
void KillDisparador(Disparador d);


/// @brief Retira a forma da posição de disparo, transferindo a posse
/// @param d Ponteiro apontando para o disparador que contém a forma
Forma RetirarFormaEmDisparo(Disparador d);


#endif