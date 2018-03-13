******************************
## Trabalho de Programação Paralela ##

### Simulação Computacional Paralela Baseada em Autômatos Celulares: Estudo de Caso de Espalhamento de Epidemias ###
******************************

Os arquivos estão dispostos nos arquivos da seguinte forma:

- versaoIterativa:
  * Possui a versão interativa do algoritmo.
  * executa.sh -> usada inicialmente para realizar as execuções, substituida por todos.sh.
  * todos.sh -> executa 4 execuções (com 100,200,400,800 iterações) por $max vezes, gerando os arquivos de cada uma dessas, e calcula cada respectiva media e desvio padrão, acrescentando no final do arquivo, além de juntar todas em um arquivo chamado junta.txt (temporário).
  * Possui um arquivo resposta.
    - resposta
      * mediaEdesvio ->  programa para calcular a média e desvio padrão de n números de entrada.
      * Todos os arquivos gerados para a versão sequencial.

- base
  * Possui documento TOPICOS onde foram anotadas as primeiras ideias para o trabalho, bem como os links que salvei para estudar.
  * Possui alguns artigos que utilizei como base para o trabalho.

- entradas
  * criaExemplo -> cria um exemplo de entrada pseudo-aleatório com tamanho definido.
  * Possui exemplos utilizados na execução do trabalho.
  * Documento randomNumberOMP.c que foi utilizado para testar a geração de números pseudo-aleatórios.

- versaoParalela
  * Possui a versão paralela do algoritmo.
  * Possui arquivo executa.sh e todos.sh -> iguais ao do arquivo 1versaoIter.
  * Documento analisesTrabalho.txt -> Possui todos os resultados de testes realizados e a conclusão de cada tópico. Tanto a verificação pelas mudanças de código quanto pelas mudanças (com código já definido) de tamanho, quantidade de interações e quantidade de Threads.
  * Possui um arquivo mudancas
    - mudancas
      * Possui um txt para cada mudança tentada.
  * Possui um arquivo resposta  
    - resposta
      * Está subdivido em arquivos por tamanho de matriz, onde cada possui um documento para cada quantidade de threads por cada variação de quantidade de iterações. Assim como mediaEdesvio igual ao 1versaoIter.

- trabalho-ProgParalela.pdf : Relatório do trabalho.
