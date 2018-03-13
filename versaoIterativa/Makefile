#definição de variáveis
OBJ=main.o cellularAutomaton.o

all:	inicial cellularAutomaton clean

inicial: 
	@echo "Iniciando"

cellularAutomaton:$(OBJ)
	@gcc -o cellularAutomaton $(OBJ) -fopenmp
main.o: cellularAutomaton.h main.c
	@gcc -c main.c -fopenmp
cellularAutomaton.o: cellularAutomaton.h cellularAutomaton.c
	@gcc -c cellularAutomaton.c -fopenmp

#remove arquivos objetos
clean:
	@echo "Finalizando"
	@rm -rf *.o
