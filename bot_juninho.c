#include "funcs.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>



int main() {
  char temp[MAX_LINE];
  char my_id[MAX_ID_SIZE];
  int warning;
  int pjogada = 0;

  setbuf(stdin, NULL);
  setbuf(stdout, NULL);
  setbuf(stderr, NULL);

  warning = scanf("PLAYERS %[^\n]\n", temp);
  warning = scanf("YOU %s\n", my_id);

  Carta *HAND;

  int numero_players = numplayers(strlen(temp));

  char **players = calloc(numero_players, sizeof(char)); // jogadores.

  for (int i = 0; i < numero_players; i++) // aloca memória para matriz jogadores.
  {
    players[i] = calloc(2, sizeof(char));
  }

  for (int i = 0; i < numero_players; i++) // adiciona jogadores na matriz.
  {
    players[i][0] = temp[i * 3];
    players[i][1] = temp[(i * 3) + 1];
  }
  
  warning = scanf("HAND [ %[^]]", temp); // lê as cartas na mão.
  warning = scanf("]\n");
  // tratamento de dados para a HAND.
 
  int *t_HAND = calloc(1, sizeof(int)); // número de cartas no deck.
  *t_HAND = 7;

  
  HAND = calloc(*t_HAND, sizeof(Carta));
  for (int i = 0; i < *t_HAND; i++) {
    HAND[i].naipe = calloc(3, sizeof(char));
    HAND[i].valor = calloc(1, sizeof(char));
    }
  int z = 0;
  for (int i = 0; i < *t_HAND; i++) {
    int x = i * 5 + z;

    if(temp[x] == '1' && temp[x+1] == '0')
    {
      HAND[i].valor = realloc(HAND[i].valor, 2*sizeof(char));
      HAND[i].valor[0] = '1'; HAND[i].valor[1] = '0';
      z ++;
      for (int j = 0; j < 3; j++) {
        HAND[i].naipe[j] = temp[x + j + 2];
      }
    }
    else
    {
      HAND[i].valor[0] = temp[x];
      for (int j = 0; j < 3; j++) {
        HAND[i].naipe[j] = temp[x + j + 1];
      }
    }
  }
  // // fim do tratamento de dados para a HAND.
  
  // tratamento de dados para carta na mesa.
  warning = scanf(" TABLE %s", temp); // lê carta na mesa.
  Carta na_mesa;
  na_mesa.naipe = calloc(3,sizeof(char));
  if(temp[0] == '1' && temp[1] == '0')
  {
    na_mesa.valor = calloc(2, sizeof(char));
    na_mesa.valor[0] = '1';
    na_mesa.valor[1] = '0';
    for(int i = 2; i < 5; i++) na_mesa.naipe[i-2] = temp[i];
  }
  else
  {
    na_mesa.valor = calloc(1, sizeof(char));
    na_mesa.valor[0] = temp[0];
    for(int i = 1; i < 4; i++) na_mesa.naipe[i-1] = temp[i];
  }

  // fim do tratamento de dados para carta na mesa.  


    char id[MAX_ID_SIZE];
    char action[MAX_ACTION];
    char complement[MAX_LINE];
  

  
  while(1){
    do
    {
      warning = scanf("%s %[^\n]\n", action, complement);
      
      if(strcmp(action, "DISCARD") == 0)
      {
        pjogada = 1;
        if(complement[0] == 'A' || complement[0] == 'C')
        {
          na_mesa.valor = realloc(na_mesa.valor, sizeof(char) * 1);
          na_mesa.valor[0] = complement[0];
          for(int i = 5; i < 8; i++) na_mesa.naipe[i-5] = complement[i];
        }
        
        if(complement[0] == '1' && complement[1] == '0')
        {
          na_mesa.valor = realloc(na_mesa.valor, sizeof(char) * 2);
          na_mesa.valor[0] = '1';
          na_mesa.valor[1] = '0';
          for(int i = 2; i < 5; i++) na_mesa.naipe[i-2] = complement[i];
        }
        else
        {
          na_mesa.valor = realloc(na_mesa.valor, sizeof(char) * 1);
          na_mesa.valor[0] = complement[0];
          for(int i = 1; i < 4; i++) na_mesa.naipe[i-1] = complement[i];
        }
      }

    } while(strcmp(action, "TURN") || strcmp(complement, my_id));

    
      debug("----- MINHA VEZ -----");
  
      if(strcmp(na_mesa.valor, "C") == 0 && strcmp(action, "BUY") != 0)
      {
        HAND = BUY(HAND, t_HAND, 4);
      }
      else if(na_mesa.valor[0] == 'V' && strcmp(action, "BUY") != 0)
      {
        HAND = BUY(HAND, t_HAND, 2);
      }  
      else
      {
        Carta descarte;
        
        descarte.naipe = calloc(3, sizeof(char));
        descarte = discard(HAND, na_mesa, t_HAND);
        if(strcmp(descarte.valor, "1") == 0)
        {
          HAND = BUY(HAND, t_HAND, 1);
        }
        else
        {
          
          if(descarte.valor[0] == 'A')
          {
            char* naipinho = calloc(3, sizeof(char));
            naipinho = mudar_naipe(HAND, t_HAND);
            printf("DISCARD %s%s %s\n", descarte.valor, descarte.naipe, naipinho);
            }
            
          else printf("DISCARD %s%s\n", descarte.valor, descarte.naipe);
        }
      }
    
  }
  
  return 0;
}
