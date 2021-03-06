#ifndef DEFINES_H
#define DEFINES_H

/* Verificação de declarações */
#define ERR_UNDECLARED  10 //identificador não declarado
#define ERR_DECLARED    11 //identificador já declarado

/* Uso correto de identificadores */
#define ERR_VARIABLE    20 //identificador deve ser utilizado como variável
#define ERR_VECTOR      21 //identificador deve ser utilizado como vetor
#define ERR_FUNCTION    22 //identificador deve ser utilizado como função

/* Tipos e tamanho de dados */
#define ERR_WRONG_TYPE  30 //tipos incompatíveis
#define ERR_STRING_TO_X 31 //coerção impossível de var do tipo string
#define ERR_CHAR_TO_X   32 //coerção impossível de var do tipo char

/* Argumentos e parâmetros */
#define ERR_MISSING_ARGS    40 //faltam argumentos
#define ERR_EXCESS_ARGS     41 //sobram argumentos
#define ERR_WRONG_TYPE_ARGS 42 //argumentos incompatíveis

/* Verificação de tipos em comandos */
#define ERR_WRONG_PAR_INPUT  50 //parâmetro não é identificador
#define ERR_WRONG_PAR_OUTPUT 51 //parâmetro não é literal string ou expressão
#define ERR_WRONG_PAR_RETURN 52 //parâmetro não é expressão compatível com tipo do retorno

/* Definições de Natureza */
#define NATUREZA_LITERAL_INT        1
#define NATUREZA_LITERAL_FLOAT      2
#define NATUREZA_LITERAL_CHAR       3
#define NATUREZA_LITERAL_STRING     4
#define NATUREZA_LITERAL_BOOL       5
#define NATUREZA_VARIAVEL           6
#define NATUREZA_VECTOR             7
#define NATUREZA_FUNCAO             8

/* Definições de tamanhos */
#define SIZE_CHAR     1
#define SIZE_STRING   1 //Multiplicado pelo comprimento do string
#define SIZE_INT      4
#define SIZE_FLOAT    8
#define SIZE_BOOL     1

#endif
