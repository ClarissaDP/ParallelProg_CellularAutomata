#!/bin/bash

echo "quantExecuções quantIteraçõesPorExecução arquivoEntradaMatriz"

max=$1
#iter=$2
initial=$2
saida=$3

for ((i = 0; i < 4; i++)) do
  if [ -e "$saida"-100.txt ] ; then
    rm "$saida"-100.txt
  fi
  if [ -e "$saida"-200.txt ] ; then
    rm "$saida"-200.txt
  fi
  if [ -e "$saida"-400.txt ] ; then
    rm "$saida"-400.txt
  fi
  if [ -e "$saida"-800.txt ] ; then
    rm "$saida"-800.txt
  fi
  if [ -e junta.txt ] ; then
    rm junta.txt
  fi
done

for ((i = 0; i < $max; i++)) do
  #./cellularAutomaton $iter < $initial >> "$saida".txt
  ./cellularAutomaton 100 < $initial >> "$saida"-100.txt
  ./cellularAutomaton 200 < $initial >> "$saida"-200.txt
  ./cellularAutomaton 400 < $initial >> "$saida"-400.txt
  ./cellularAutomaton 800 < $initial >> "$saida"-800.txt
done

./resposta/mediaEdesvio 10 < "$saida"-100.txt >> "$saida"-100.txt
./resposta/mediaEdesvio 10 < "$saida"-200.txt >> "$saida"-200.txt
./resposta/mediaEdesvio 10 < "$saida"-400.txt >> "$saida"-400.txt
./resposta/mediaEdesvio 10 < "$saida"-800.txt >> "$saida"-800.txt

./resposta/mediaEdesvio 10 < "$saida"-100.txt >> junta.txt
./resposta/mediaEdesvio 10 < "$saida"-200.txt >> junta.txt
./resposta/mediaEdesvio 10 < "$saida"-400.txt >> junta.txt
./resposta/mediaEdesvio 10 < "$saida"-800.txt >> junta.txt
