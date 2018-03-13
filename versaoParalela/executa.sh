#!/bin/bash

echo "quantExecuções quantIteraçõesPorExecução arquivoEntradaMatriz"

max=$1
iter=$2
initial=$3

if [ -e "tempoTeste.txt" ] ; then
  rm tempoTeste.txt
fi

for ((i = 0; i < $max; i++)) do
  ./cellularAutomaton $iter < $initial >> tempoTeste.txt
done
