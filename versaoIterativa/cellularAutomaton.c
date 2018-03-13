 #include "cellularAutomaton.h"


double timestamp(void){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec + tp.tv_usec/1000000.0));
}




/*------------------------------------------------------------------------------------------------------*/
/* Função responsável pela alteração da matriz, baseada no estado anterior                              */
/*------------------------------------------------------------------------------------------------------*/

void celulaAlteration(typeProb save[N][N], typeProb ant[N][N],  int lin, int pos, int beta, int mi, int gama, int d) {


    /* Morte natural (possível para todos) */
    if(morteNatural(ant, lin, pos, mi) >= 0.5) {
        save[lin][pos].estado = S;
        save[lin][pos].normal = save[lin][pos].inf = 0;
        return;
    }
    

    /* Recuperado -> Recuperado ou Vacinado -> Vacinado  */
    if(ant[lin][pos].estado == VP || ant[lin][pos].estado == R) {
        if(ant[lin][pos].estado == VP) {
            save[lin][pos].estado = VP;
            save[lin][pos].normal = ant[lin][pos].normal + 1;
        }
        else {
            save[lin][pos].estado = R;
            save[lin][pos].normal = ant[lin][pos].normal + 1;
        }
        return;
    }

    /* Suscetível -> Suscetível ou Infectado */
    if(ant[lin][pos].estado == S) {
        if( infecta(ant, lin, pos, beta) >= 0.5) {
          save[lin][pos].estado = I;
          save[lin][pos].inf = 1;
        }
        else {
          save[lin][pos].estado = S;
          save[lin][pos].normal = ant[lin][pos].normal + 1;
        }
    }

    /* Infectado -> Infectado, Recuperado ou Suscetível(morrer) */
    else {
        save[lin][pos].estado  = recupera(ant, lin, pos, gama, d);

        if(save[lin][pos].estado == I)
            save[lin][pos].inf = ant[lin][pos].inf + 1;
        else if(save[lin][pos].estado == R)
            save[lin][pos].normal = ant[lin][pos].normal + 1;
        else {
            save[lin][pos].normal = 0;
            save[lin][pos].inf = 0;
        }
    }

    return;
}



/*------------------------------------------------------------------------------------------------------*/
/* Probabilidade que todos possuem de morrer por uma causa diferente da doença                          */
/*------------------------------------------------------------------------------------------------------*/

float morteNatural(typeProb malha[N][N], int linha, int coluna, int mi) {
    float res;
    res = ( mi *((19*malha[linha][coluna].normal)+(13*malha[linha][coluna].inf) - (100)) ) / 8;
    return res;
}


/*------------------------------------------------------------------------------------------------------*/
/* Probabilidade de um Suscetível se tornar Infectado pela epidemia                                     */
/*------------------------------------------------------------------------------------------------------*/

float infecta(typeProb malha[N][N], int linha, int coluna, int beta) {
    int infecta = 0, i, j;


    /* Moore */
    for (i = (linha-1) ; i <= (linha+1) ; ++i)
        for (j = (coluna-1); j <= (coluna+1) ; ++j)
            if(malha[i][j].estado == 7)
                infecta++;
    /*
        // Von Newmann
        infecta = malha[linha-1][coluna].estado + malha[linha+1][coluna].estado + malha[linha][coluna-1].estado + malha[linha][coluna+1].estado;
        // + Moore
        infecta += malha[linha+1][coluna-1].estado + malha[linha+1][coluna+1].estado + malha[linha-1][coluna-1].estado + malha[linha-1][coluna+1].estado;
    */

    return ((beta*infecta)/8);

}



/*------------------------------------------------------------------------------------------------------*/
/* Resposta se um Infectado pode Morrer pela doença(suscetível), Recuperar ou continuar Infectado       */
/*------------------------------------------------------------------------------------------------------*/

int recupera(typeProb malha[N][N], int linha, int coluna, int gama, int d) {
    int soma = 0, i, j;
  

    if(malha[linha][coluna].inf > 1) {

        /* Moore */
        for (i = (linha-1) ; i <= (linha+1) ; ++i)
            for (j = (coluna-1); j <= (coluna+1) ; ++j)
                if(malha[i][j].estado == 7)
                    soma++;

        if( ((d*soma)/8 >= 0.1) || (malha[i][j].inf > 9) )
            return S;

        if( (gama*(8-soma)/8) >= 0.5  )
            return R;

    }

    return I;
}



/*------------------------------------------------------------------------------------------------------*/
/* Vacina que ocorre em tempos programados, aleatoriamente, na população                                */
/*------------------------------------------------------------------------------------------------------*/

void vacinaPulsada(typeProb malha[N][N]) {
    int i, j, lin, col;
    uint32_t aleat[NRANDS];    
    int idx, size;
    
    // puts("Entrou vacinaPulsada");

    for ( j = 0; j < MAX ; ++j ) {
        srand(25234 + 17*j);    

        for(i = 0 ; i < (NRANDS/MAX) ; ++i) 
            aleat[i+((NRANDS/MAX)*j)] = rand();

    }

    size = N-2;
    for (i = 1; i < N ; i += PSEUDO) {
        for (j = 1; j < N ; j += PSEUDO)  {
            idx = ((i-1)*N + (j-1)) % NRANDS;

            lin = aleat[idx] % size;
            col = aleat[idx]*3 % size;

            if(malha[lin][col].estado != R)
                malha[lin][col].estado = VP;

        }
    }


    return;
}



/*------------------------------------------------------------------------------------------------------*/
/* Vacina que ocorre em tempos programados, aleatoriamente, na população - por região/vizinhança        */
/*------------------------------------------------------------------------------------------------------*/

void vacinaPulsadaLocalidade(typeProb malha[N][N]) {
    int i, j, lin, col;
    uint32_t aleat[NRANDS];
    int idx, size;

    /* Em vez de vacinar apenas uma pessoa aleatoriamente, vacina uma região/vizinhança aleatoriamente por vez */
    // puts("Entrou vacinaPulsadaLocalidade");
    

    for ( j = 0; j < MAX ; ++j ) {
        srand(25234 + 17*j);

        for(i = 0 ; i < (NRANDS/MAX) ; ++i) 
            aleat[i+((NRANDS/MAX)*j)] = rand();

    }

    size = N-2;
    for (i = 1; i < N ; i += PSEUDO) 
        for (j = 1; j < N ; j += PSEUDO)  {

            idx = ((i-1)*N + (j-1)) % NRANDS;
            
            lin = aleat[idx] % size;
            col = aleat[idx]*3 % size;

            if(malha[lin][col].estado != R)
                malha[lin][col].estado = VP;

            if((lin-1) >= 0  &&  malha[lin-1][col].estado != R)
                malha[lin-1][col].estado = VP;

            if((lin+1) >= 0  &&  malha[lin+1][col].estado != R)
                malha[lin+1][col].estado = VP;

            if((col-1) >= 0  &&  malha[lin][col-1].estado != R)
                malha[lin][col-1].estado = VP;

            if((col+1) >= 0  &&  malha[lin][col+1].estado != R)
                malha[lin][col+1].estado = VP;

        }


    return;
}



/*------------------------------------------------------------------------------------------------------*/
/* Impressão da matriz, para visualização                                                               */
/*------------------------------------------------------------------------------------------------------*/

void impressao (typeProb malha[N][N]) {
    int i, j;


    for(i=1; i < (N-1) ; ++i) {
        for(j=1; j < (N-1) ; ++j) {

            if(malha[i][j].estado == 0)
                printf("x ");
            else if(malha[i][j].estado == 1)
                printf(". ");
            else if(malha[i][j].estado == 3)
                printf("° ");
            else 
                printf("# ");

        }
        printf("\n");
    }
    printf("\n");

    return;
    
}
