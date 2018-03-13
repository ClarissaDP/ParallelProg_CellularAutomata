#include  <stdio.h>

int main (int argc, char *argv[]) {
  int i,j, tam, primeiro, segundo, mod;
  FILE *escrita;

  if(argc < 3) {
    printf("Parâmetros: %s nomeArquivoSaida tamanhoMatriz\n", argv[0]);
    return (-1);
  }

  if( !(escrita = fopen(argv[1],"w")) ) {
    printf("Erro na abertura do arquivo.\n");
    return (-1);
  }
  tam = atoi(argv[2]);

//printf("tam = %d",tam);

  srand(12345);
  primeiro = tam/6;
  segundo = tam/5;

  for(i = 0; i < tam ; ++i) {
    for(j = 0 ; j < tam/2 ; ++j) {
      mod = (rand() % tam);

      if(mod < (primeiro))
        fprintf(escrita,"7 ");
      else if(mod < segundo)
        fprintf(escrita,"3 ");
      else      
        fprintf(escrita,"1 ");
    }

    fprintf(escrita,"\n");    
  }

  fclose(escrita);

  return 0;
}
