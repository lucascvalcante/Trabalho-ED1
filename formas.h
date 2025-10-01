#ifndef FORMAS_H
#define FORMAS_H

/* 
    Arquivo .h Relacionado a formas, permitindo que diferentes formas sejam tratadas de maneira uniforme.
*/


/// @brief "Enum" que define os tipos de formas presentes
typedef enum Tipo_Forma{
    CIRCULO,
    LINHA,
    RETANGULO,
    TEXTO,
}Tipo_Forma;


typedef void *Forma;


/// @brief Cria e retorna um ponteiro para uma forma genérica
/// @param tipo O tipo da forma(Circulo, retângulo, etc)
/// @param dados Um ponteiro para a forma ja criada
/// @return Um ponteiro para a forma genérica
Forma Criar_Forma(Tipo_Forma tipo, void *dados);


/// @brief Libera memória alocada de uma forma genérica 
/// @param f A forma a ser destruída
void DestruirForma(Forma f);


/// @brief Retorna o tipo da forma(Circulo, retãngulo, etc)
/// @param f A forma
/// @return O tipo da forma
Tipo_Forma GetTipoForma(Forma f);


/// @brief Obtém e retorna um ponteiro para os dados da forma 
/// @param f A forma
/// @return O ponteiro para os dados da forma
void *GetDadosForma(Forma f);


/// @brief Calcula e retorna a área da forma genérica
/// @param f A forma
/// @return O calculo da área
double GetAreaForma(Forma f);


/// @brief Define a posição de uma forma genérica
/// @param f A forma 
/// @param x A posição na coordenada X
/// @param y A posição na coordenada Y
void SetPosicaoForma(Forma f, double x, double y);


#endif