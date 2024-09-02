#ifndef LDDE_H
#define LDDE_H

typedef struct LDDE LDDE;
typedef struct elemento elemento;

int cria(LDDE **pp);
void reinicia(LDDE *p);
void destroi(LDDE **pp);

int insereNoInicio(LDDE *p, void *novo, int tipo);
int insereNoFim(LDDE *p, void *novo, int tipo);
int insereNaPosLog (LDDE *p, void *novo,int posLog, int tipo);

int buscaNoInicio(LDDE *p, elemento *reg);
int buscaNoFim(LDDE *p, elemento *reg);
int buscaNaPosLog(LDDE *p, elemento *reg, int posLog);

int removeDoInicio(LDDE *p, elemento *reg);
int removeDoFim(LDDE *p, elemento *reg);
int removeDaPosLog(LDDE *p, elemento *reg, int posLog);

int tamanho (LDDE *p);

/*Funções para manipular o elemento*/
elemento *criarElemento();
void *verDado(elemento *e);
int verTipo(elemento *e);
void destruirElemento(elemento *e);

#endif
