#include <stdio.h>
#include <stdlib.h>
#include <math.h>


int main (int argc, char *argv[]) {
    double soma = 0.0, media = 0.0, desvio = 0.0, atual[20];
    int i, max;

    if(argc < 2) {
        printf("Parâmetros: %s quantDeAmostras\n", argv[0]);
        return (-1);
    }

    max = atoi(argv[1]);


    for(i = 0; i < max ; ++i) {
        scanf("%lf", &atual[i]);
        media += atual[i];
    }
    media = media/max;

    for(i = 0 ; i < max ; ++i) 
        desvio += (atual[i]-media)*(atual[i]-media);
    desvio = sqrt(desvio/max);

    printf("Media = %.20lf\n", media);
    printf("DesvioP = %.20lf\n", desvio);

    return 0;
}
