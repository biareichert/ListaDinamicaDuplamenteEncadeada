#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "Aplicacao.h"

void ImprimirItem(void *e, int tipo){
    switch (tipo){
        case 1:
            /*O elemento é um float*/
            printf("%.2f\n", *(float *) e); 
            
            break;
        case 2:
            /*O elemento é um caracter*/
            printf("%c\n", *(int *) e);
            
            break;
        case 3:
            /*O elemento é um inteiro*/
            printf("%d\n", *(int *) e);
            
            break;
            
        default:
            break;
    }
}

int main (void) {
    LDDE *p = NULL;
    int retorno, tipo;
    int nota = 10;
    char conceito = 'a';
    float nFloat = 8.5;
    elemento *eBusca = criarElemento();
    elemento *eRemove = criarElemento();
    void *dado = NULL;
    
    if(cria(&p) == 0){
       
       /*####################### Inserção (Início, Fim, PosLog) #######################*/

       printf("\n\n####################### Inserção (Início, Fim, PosLog) #######################\n\n");
        for(int i = 0; i < 9; i++){
            if(i % 2 == 0){
                retorno = insereNoInicio(p, &nota, 3);
                if(retorno == 0){
                    printf("Nota inserida com sucesso!\n");
                }else{
                    printf("Erro ao inserir a nota!\n");
                }

                nota--;
            }else{
                retorno = insereNoFim(p, &conceito, 2);
                if(retorno == 0){
                    printf("Conceito inserido com sucesso!\n");
                }else{
                    printf("Erro ao inserir o conceito!\n");
                }

                conceito = conceito + 1;
            }
        }

        retorno = insereNaPosLog(p, &nFloat, 2, 1);
        if(retorno == 0){
            printf("Nota (float) inserida com sucesso!\n");
        }else{
            printf("Erro ao inserir a nota (float)!\n");
        }

        /*A Lista está assim: 6, 7, 8.5, 8, 9, 10, a, b, c, d*/

        
        /*####################### Busca (PosLog) #######################*/

        printf("\n\n####################### Busca (PosLog) #######################\n\n");
        retorno = buscaNaPosLog(p, eBusca, 2);
        if(retorno == 0){
            tipo = verTipo(eBusca);
            dado = verDado(eBusca);

            printf("O elemento da posição 2 é: ");
            ImprimirItem(dado, tipo);

            destruirElemento(eBusca);
            free(dado);
        }else{
            printf("Erro ao buscar o elemento na posição 2!\n");
        }
        
        
        /*####################### Remoção (PosLog) #######################*/

        printf("\n\n####################### Remoção (PosLog) #######################\n\n");
        retorno = removeDaPosLog(p, eRemove, 2);
        if(retorno == 0){
            tipo = verTipo(eRemove);
            dado = verDado(eRemove);

            printf("O elemento removido da posição 2 é: ");
            ImprimirItem(dado, tipo);

            destruirElemento(eRemove);
            free(dado);
        }else{
            printf("Erro ao remover o elemento da posição 2!\n");
        }

        /*A Lista está assim: 6, 7, 8, 9, 10, a, b, c, d*/

        /*####################### Busca (Início, Fim) #######################*/

        printf("\n\n####################### Busca (Início, Fim) #######################\n\n");
        retorno = buscaNoInicio(p, eBusca);
        if(retorno == 0){
            tipo = verTipo(eBusca);
            dado = verDado(eBusca);

            printf("O elemento do início é: ");
            ImprimirItem(dado, tipo);

            destruirElemento(eBusca);
            free(dado);
        }else{
            printf("Erro ao buscar o elemento do início!\n");
        }

        retorno = buscaNoFim(p, eBusca);
        if(retorno == 0){
            tipo = verTipo(eBusca);
            dado = verDado(eBusca);

            printf("O elemento do fim é: ");
            ImprimirItem(dado, tipo);

            destruirElemento(eBusca);
            free(dado);
        }else{
            printf("Erro ao buscar o elemento do fim!\n");
        }

        /*####################### Remoção (Início) #######################*/

        printf("\n\n####################### Remoção (Início) #######################\n\n");
        int tam = ceil((tamanho(p) / 2));
        for(int i = 0; i <= tam; i++){
            retorno = removeDoInicio(p, eRemove);
            if(retorno == 0){
                tipo = verTipo(eRemove);
                dado = verDado(eRemove);

                printf("O elemento removido é: ");
                ImprimirItem(dado, tipo);

                destruirElemento(eRemove);
                free(dado);
            }else{
                printf("Erro ao remover elemento do início!\n");
            }
        }
        
        /*A Lista está assim: a, b, c, d*/

        /*####################### Busca (Início, Fim) #######################*/

        printf("\n\n####################### Busca (Início, Fim) #######################\n\n");
        retorno = buscaNoInicio(p, eBusca);
        if(retorno == 0){
            tipo = verTipo(eBusca);
            dado = verDado(eBusca);

            printf("O elemento do início é: ");
            ImprimirItem(dado, tipo);

            destruirElemento(eBusca);
            free(dado);
        }else{
            printf("Erro ao buscar o elemento do início!\n");
        }

        retorno = buscaNoFim(p, eBusca);
        if(retorno == 0){
            tipo = verTipo(eBusca);
            dado = verDado(eBusca);

            printf("O elemento do fim é: ");
            ImprimirItem(dado, tipo);

            destruirElemento(eBusca);
            free(dado);
        }else{
            printf("Erro ao buscar o elemento do fim!\n");
        }

        /*####################### Remoção (Fim) #######################*/

        printf("\n\n####################### Remoção (Fim) #######################\n\n");
        tam = tamanho(p);
        for(int i = 0; i < tam; i++){
            retorno = removeDoFim(p, eRemove);
            if(retorno == 0){
                tipo = verTipo(eRemove);
                dado = verDado(eRemove);

                printf("O elemento removido é: ");
                ImprimirItem(dado, tipo);

                destruirElemento(eRemove);
                free(dado);
            }else{
                printf("Erro ao remover elemento do fim!\n");
            }
        }

    }
    
    free(eRemove);
    free(eBusca);
    destroi(&p);
    return 0;
}