#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definitions.h"

void troca_carta(Carta receptora, Carta copiada)// troca o valor e o naipe de uma carta x para uma y.
{
  strcpy(receptora.naipe, copiada.naipe);
  if(strlen(copiada.valor)>1) strcpy(receptora.valor, copiada.valor);
  else receptora.valor = copiada.valor;
}


Carta discard(Carta* HAND, Carta atual, int *t_HAND)// descarta uma carta do naipe e retorna o seu valor.
{
  Carta invalida;
  invalida.valor = calloc(1,sizeof(char));
  invalida.valor[0] = '1';
  Carta descarte;
  descarte.valor = calloc(2, sizeof(char));

  descarte.naipe = calloc(3, sizeof(char));
  
  for(int i = 0; i < *t_HAND; i++)
  {
    
    if(strcmp(HAND[i].valor, atual.valor) == 0 || strcmp(HAND[i].naipe, atual.naipe) == 0)
    {
      troca_carta(descarte, HAND[i]);
      troca_carta(HAND[i], HAND[*t_HAND - 1]);
      descarte.valor = HAND[i].valor;
      HAND[i].valor = HAND[*t_HAND - 1].valor;
      *t_HAND = *t_HAND - 1;
      HAND = (Carta*) realloc(HAND, *t_HAND * (sizeof(Carta) + 3*sizeof(char)));
      return descarte;
    }
  }
  return invalida;
}