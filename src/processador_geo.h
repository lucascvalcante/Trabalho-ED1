#ifndef PROCESSADOR_GEO_H
#define PROCESSADOR_GEO_H

#include "chao.h"
#include "texto.h"


/// @brief Lê um arquivo .geo, cria e insere as formas no chão
/// @param caminhoGeo O caminho para o arquivo.geo a ser lido
/// @param Estilos_criados Ponteiro para uma array de estilos, alocando todos os estilos criados
/// @param num_estilos Ponteiro para um inteiro que recebe a quantidade de estilos presentes na array 
/// @return Ponteiro para o chão, preenchido com as formas do arquivo .geo
Chao ProcessaGeo(const char *caminhoGeo, Estilo **Estilos_criados, int *num_estilos);


#endif