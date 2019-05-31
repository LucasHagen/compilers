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

/* Instructions ILOC */
#define ILOC_NOP		0	// ( não faz nada )

#define ILOC_ADD		1	// r1, r2   =>  r3     ( r3 = r1 + r2 )
#define ILOC_SUB		2	// r1, r2   =>  r3     ( r3 = r1 - r2 )
#define ILOC_MULT		3	// r1, r2   =>  r3     ( r3 = r1 * r2 )
#define ILOC_DIV		4	// r1, r2   =>  r3     ( r3 = r1 / r2 )
#define ILOC_ADDI		5	// r1, c2   =>  r3     ( r3 = r1 + c2 )
#define ILOC_SUBI		6	// r1, c2   =>  r3     ( r3 = r1 - c2 )
#define ILOC_RSUBI		7	// r1, c2   =>  r3     ( r3 = c2 - r1 )
#define ILOC_MULTI		8	// r1, c2   =>  r3     ( r3 = r1 * c2 )
#define ILOC_DIVI		9	// r1, c2   =>  r3     ( r3 = r1 / c2 )
#define ILOC_RDIVI		10	// r1, c2   =>  r3     ( r3 = c2 / r1 )
#define ILOC_LSHIFT		11	// r1, r2   =>  r3     ( r3 = r1 << r2 )
#define ILOC_LSHIFTI	12	// r1, c2   =>  r3     ( r3 = r1 << c2 )
#define ILOC_RSHIFT		13	// r1, r2   =>  r3     ( r3 = r1 >> r2 )
#define ILOC_RSHIFTI	14	// r1, c2   =>  r3     ( r3 = r1 >> c2 )
#define ILOC_AND		15	// r1, r2   =>  r3     ( r3 = r1 && r2 )
#define ILOC_ANDI		16	// r1, c2   =>  r3     ( r3 = r1 && c2 )
#define ILOC_OR		    17	// r1, r2   =>  r3     ( r3 = r1 || r2 )
#define ILOC_ORI		18	// r1, c2   =>  r3     ( r3 = r1 || c2 )
#define ILOC_XOR		19	// r1, r2   =>  r3     ( r3 = r1 xor r2 )
#define ILOC_XORI		20	// r1, c2   =>  r3     ( r3 = r1 xor c2 )
#define ILOC_LOADAI		21	// r1, c2   =>  r3     ( r3 = Memoria(r1 + c2) )
#define ILOC_LOADA0		22	// r1, r2   =>  r3     ( r3 = Memoria(r1 + r2) )
#define ILOC_CLOADAI	23	// r1, c2   =>  r3     ( caractere loadAI )
#define ILOC_CLOADA0	24	// r1, r2   =>  r3     ( caractere loadA0 )
#define ILOC_LOADI		25	// c1       =>  r2     ( r2 = c1 )
#define ILOC_LOAD		26	// r1       =>  r2     ( r2 = Memoria(r1) )
#define ILOC_CLOAD		27	// r1       =>  r2     ( caractere load )
#define ILOC_STORE		28	// r1       =>  r2     ( Memoria(r2) = r1 )
#define ILOC_CSTORE		29	// r1       =>  r2     ( caractere store )
#define ILOC_I2I		30	// r1       =>  r2     ( r2 = r1 para inteiros )
#define ILOC_C2C		31	// r1       =>  r2     ( r2 = r1 para caracteres )
#define ILOC_C2I		32	// r1       =>  r2     ( converte um caractere para um inteiro )
#define ILOC_I2C		33	// r1       =>  r2     ( converte um inteiro para caractere )
#define ILOC_CSTOREAI	34	// r1       =>  r2, c3 ( caractere storeAI )
#define ILOC_CSTOREA0	35	// r1       =>  r2, r3 ( caractere storeA0 )
#define ILOC_STOREAI	36	// r1       =>  r2, c3 ( Memoria(r2 + c3) = r1 )
#define ILOC_STOREA0	37	// r1       =>  r2, r3 ( Memoria(r2 + r3) = r1 )
#define ILOC_JUMPI		38	// ->  l1              ( PC = endereço(l1) )
#define ILOC_JUMP		39	// ->  r1              ( PC = r1 )
#define ILOC_CBR		40	// r1      ->  l2, l3  ( PC = endereço(l2) se r1 = true, senão PC = endereço(l3) )
#define ILOC_CMP_LT		41	// r1, r2  ->  r3      ( r3 = true se r1 < r2, senão r3 = false )
#define ILOC_CMP_LE		42	// r1, r2  ->  r3      ( r3 = true se r1 \leq r2, senão r3 = false )
#define ILOC_CMP_EQ		43	// r1, r2  ->  r3      ( r3 = true se r1 = r2, senão r3 = false )
#define ILOC_CMP_GE		44	// r1, r2  ->  r3      ( r3 = true se r1 \geq r2, senão r3 = false )
#define ILOC_CMP_GT		45	// r1, r2  ->  r3      ( r3 = true se r1 > r2, senão r3 = false )
#define ILOC_CMP_NE		46	// r1, r2  ->  r3      ( r3 = true se r1 \ne r2, senão r3 = false )

#endif
