#include "cellularAutomaton.h"


int main(int argc, char *argv[]) {
	int i, j, k, QTD, chunk;
	static typeProb cel[N][N];	
	static typeProb novo[N][N];
	double tempo = 0.0, temp;
	float beta, mi, d, gama;
  	int size = (N-1);
  

  	omp_set_num_threads(MAX);


	if(argc < 2) {
		printf("Parâmetros: %s quantidadeIterações [B] [µ] [γ] [d]\n", argv[0]);
		return -1;
	}

	if ( (strcmp(argv[1],"help") == 0) || (strcmp(argv[1],"?") == 0) ) {

		printf("MAX Number of threads = %d\n\n", omp_get_max_threads());

		printf("\n*** Programa para representar uma Simulação (simples) sobre Espalhamento de Epidemias utilizando Automatos Celulares.  ***\n\n");

		printf("Parâmetros: %s quantidadeIterações [B] [µ] [γ] [d]\n\n", argv[0]);
		printf("quantidadeIterações: Em quantas matrizes será aplicado o espalhamento, dada uma entrada inicial.\n");
		printf("[B] = (beta): Coeficiente de transmissão que determina a taxa em que novas infecções surgem como consequência do contato entre suscetíveis e infectados. (inicial: 3.5)\n");
		printf("[µ] = (mi): Taxa  de  novos  suscetíveis  por  unidade  de  tempo (morte). (inicial: 0.10)\n");
		printf("[γ] = (gama): Taxa de recuperação dos indivíduos infectados. (inicial: 0.60)\n");
		printf("[d]: Taxa de indivíduos infectados que morrem por causa da doença. (inicial: 0.30)\n\n");

		printf("Observação: Se algum dos parâmetros forem adicionados (além dos obrigatórios) todos devem ser colocados.\n");
		printf("\n");

		return (-1);
	}


	QTD = atoi(argv[1]);	

	// Coeficiente de transmissão que determina a taxa em que novas infecções surgem como consequência do contato entre suscetíveis e infectados
	beta = 3.5;
	// Taxa  de  novos  suscetíveis  por  unidade  de  tempo (morte)
	mi = 0.10;
	// Taxa de recuperação dos indivíduos infectados
	gama = 0.60;
	// Taxa de indivíduos infectados que morrem por causa da doença
	d = 0.30;

	if (argc > 2) {
		beta = atof(argv[2]);
	}
	if (argc > 3) {
		mi = atof(argv[3]);
	}
	if (argc > 4) {
		gama = atof(argv[4]);
	}
	if (argc > 5) {
		d = atof(argv[5]);
	}


	/*------------------------------------------------------------------------------*/
	/* Leitura da Matriz inicial													*/
	/*------------------------------------------------------------------------------*/

	//temp = timestamp();

		/* Margem superior */
		//#pragma omp parallel for private(j) shared (cel)
    	for(j = 0; j < N ; ++j) {
  			cel[0][j].estado = S;
  			cel[0][j].normal = cel[0][j].inf = 0;
  		}

		/* Leitura da matriz inicial + margens laterais */
			for(i=1; i < (N-1) ; ++i) {
				cel[i][0].estado = S;
				for(j=1; j < (N-1) ; ++j) {
					scanf("%d",&cel[i][j].estado);
					cel[i][j].normal = cel[i][j].inf = 0;
				}
				cel[i][j].estado = S;
			}

    	/* Margem inferior */
		//#pragma omp parallel for private(j) shared (cel)
    	for(j = 0; j < N ; ++j) {
      		cel[i][j].estado = S;
  	  		cel[i][j].normal = cel[i][j].inf = 0;
    	}

	//tempo += (timestamp() - temp);

	/*------------------------------------------------------------------------------*/
	/* Impressão da Matriz Inicial 													*/
	/*------------------------------------------------------------------------------*/

	// printf("Inicial:\n");
	// impressao(cel);


	/*------------------------------------------------------------------------------*/
	/* Chama a função para espalhamento, revezando, até a quantidade pedida			*/
	/*------------------------------------------------------------------------------*/
    //chunk = (N/MAX);

	for (k = 0; k < QTD ; ++k) {

		if( (k % 2) == 0) {

			temp = timestamp();

			#pragma omp parallel for private(i,j) shared(cel,novo,beta,mi,gama,d,size) //schedule(static,chunk)
			for(i=1; i < size ; ++i) {
				//#pragma omp parallel for private(j) shared(i,cel,novo,beta,mi,gama,d,size)
				for(j=1; j < size ; ++j) 
					celulaAlteration(novo, cel, i, j, beta, mi, gama, d);
			}

      		tempo += (timestamp() - temp);

			/* Impressão */
      		// impressao(novo);
		
		}

		else {
	

			temp = timestamp();

			#pragma omp parallel for private(i,j) shared(cel,novo,beta,mi,gama,d,size) //schedule(static,chunk)
			for(i=1; i < size ; ++i) {
				//#pragma omp parallel for private(j) shared(i,cel,novo,beta,mi,gama,d,size)
				for(j=1; j < size ; ++j)
					celulaAlteration(cel, novo, i, j, beta, mi, gama, d);
			}

			tempo += (timestamp() - temp);

			/* Impressão */
			// impressao(cel);


			/* Vacinação pulsada */
			if( (k % 7) == 0 ) {
				// vacinaPulsada(cel);
				vacinaPulsadaLocalidade(cel);
			}

		}


	}

  
  printf("%.20lf\n", tempo);


  return 0;
}
