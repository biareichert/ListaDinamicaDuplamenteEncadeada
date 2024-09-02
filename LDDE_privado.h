#ifndef LDDE_PRIVADO_H
#define LDDE_PRIVADO_H

#include "LDDE.h"

/*Struct do elemento, dado que é uma lista heterogênea*/
typedef struct elemento{
    void *dado; /*armazena o dado genérico*/
    int tamInfo; /*armazena o tamanho (sizeof) do dado (elemento)*/
    int tipo; /*1: float. 2: caracter. 3: int.*/
} elemento;

/*Struct do nó da lista*/
typedef struct noLDDE{
    elemento *dados; /*armazena uma struct elemento com as informações do item*/
    struct noLDDE *prox; /*ponteiro para a próxima posição*/
    struct noLDDE *ant; /*ponteiro para a posição anterior*/
} noLDDE;

/*Struct do descritor da lista*/
typedef struct LDDE{
    int tamLista; /*armazena o tamanho atual da lista*/
    noLDDE *inicio; /*ponteiro para o nó de início*/
    noLDDE *fim; /*ponteiro para o nó de fim*/
} LDDE;

#endif