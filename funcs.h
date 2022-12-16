#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "discard.h"


void debug(char *message) {
  fprintf(stderr, "%s\n", message);
}

int numplayers(int x)// retorna o número de players a partir do tamanho da string PLAYERS.
{
  int numero_players = x;
  numero_players += 1;
  numero_players = numero_players/3;
  return numero_players;
}




char* retira_colchetes(char* temp)// função utilizada anteriormente para tratar a string HAND.
{
  temp[strlen(temp)-2] = '\0';
  int y = strlen(temp);
  for(int i = 2; i < y; i++)
  {
    temp[i-2] = temp[i];
  }
  temp[y-2] = '\0';
  
  return temp;
}



Carta* BUY(Carta* na_mao, int* t_HAND, int num)// compra uma carta e a adiciona no baralho.
{
  int war;
  char temp[100];
  printf("BUY %i\n", num);
  na_mao = realloc(na_mao, sizeof(Carta) * (*t_HAND + num));
  for(int i = 0; i < num; i++)
  {
    na_mao[*t_HAND + i].naipe = calloc(3, sizeof(char));  
    war = scanf("%s", temp);
    if(temp[0] == '1' && temp[1] == '0')
        {
          na_mao[*t_HAND + i].valor = calloc(2, sizeof(char));
          na_mao[*t_HAND + i].valor[0] = '1';
          na_mao[*t_HAND + i].valor[1] = '0';
          for(int j = 2; j < 5; j++) na_mao[*t_HAND + i].naipe[j-2] = temp[j];
        }
        else
        {
          na_mao[*t_HAND + i].valor = calloc(1, sizeof(char));
          na_mao[*t_HAND + i].valor[0] = temp[0];
          for(int j = 1; j < 4; j++) na_mao[*t_HAND + i].naipe[j-1] = temp[j];
        }
  }
  *t_HAND += num;
    
  return na_mao;
}

char* mudar_naipe(Carta* hand, int* t_hand)// escolhe um naipe para descarte da carta A.
{
  int naipes[4]; // naipes[0] = ♦, naipes[1] = ♣, naipes[2] = ♠, naipes[3] = ♥.
  for(int i = 0; i < *t_hand; i ++)
    {
      if(strcmp(hand[i].naipe, PAUS_U) == 0)
      {naipes[1]++;}
      else if(strcmp(hand[i].naipe, OURO_U) == 0)
      {naipes[0] ++;}
      else if(strcmp(hand[i].naipe, COPAS_U) == 0)
      {naipes[3] ++;}
      else if(strcmp(hand[i].naipe, ESPADA_U) == 0)
      {naipes[2] ++;}
    }
  int j = 0;
  for(int i = 1; i < 4; i++){if(naipes[i]> naipes[i-1]){int j = i;}}
  if(j == 0) return OURO_U;
  else if(j == 1) return PAUS_U;
  else if(j == 2) return ESPADA_U;
  else return COPAS_U;
}
