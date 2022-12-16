#include <stdio.h>
#include <string.h>

typedef struct{ //struct das cartas
  char *valor;
  char *naipe;
} Carta;

#define MAX_LINE 100
#define MAX_ACTION 10
#define MAX_ID_SIZE 10



#ifndef COPAS_U
#define COPAS_U "♥️"
#endif

#ifndef OURO_U
#define OURO_U "♦️"
#endif

#ifndef PAUS_U
#define PAUS_U "♣️"
#endif

#ifndef ESPADA_U
#define ESPADA_U "♠️"
#endif

