#ifndef _cellularAutomaton_
#define _cellularAutomaton_


#include <stdio.h>                                                         
#include <stdlib.h>                                                        
#include <string.h> 
//#include <stdint.h>
#include <inttypes.h>


// Modelo matemático SIR
#define S 1		// Suscetível
#define I 7		// Infectado
#define R 3		// Recuperado

// Modelo baseado no SIR com acréscimo de vacina.
#define VP 0	// Vacinação Pulsada


#define N 1002

/* Número de valores aleatórios */
#define NRANDS 10000
#define PSEUDO 4

/* Número de threads */
// #define MAX (omp_get_max_threads())
#define MAX 8


typedef struct prob {
	int32_t estado;
	int32_t normal;
	int32_t inf;
} typeProb;


#endif




double timestamp(void);


/* Alteração das matrizes */
void celulaAlteration(typeProb save[N][N], typeProb ant[N][N], int, int, int, int, int, int);

/* retorna a probabilidade de ocorrer uma morte não decorrente na epidemia */
float morteNatural(typeProb malha[N][N], int, int, int);

/* retorna a probabilidade de um suscetível ser infectado pela epidemia */
float infecta(typeProb malha[N][N], int, int, int);

/* retorna o valor se recuperou, continuou infectado ou morreu pela doença */
int recupera(typeProb malha[N][N], int ,int, int, int);

/* Vacina que ocorre em tempos programados, aleatoriamente, na população */
void vacinaPulsada(typeProb malha[N][N]);

/* Vacina que ocorre em tempos programados, aleatoriamente, na população - por região/vizinhança */
void vacinaPulsadaLocalidade(typeProb malha[N][N]);

/* Impressão da matriz, para visualização */
void impressao (typeProb malha[N][N]);
