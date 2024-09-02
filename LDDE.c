#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "LDDE_privado.h"

int cria(LDDE **pp){
   int retorno = 1;
   
   /*Alocando espaço de memória para o descritor da lista*/
   LDDE *desc = (LDDE*)malloc(sizeof(LDDE));
   
   if(!desc){
      /*Se a alocação der errado retornamos 1*/
      retorno = 1;
      return retorno;

   }else{
      /*Caso contrário iniciamos as variáveis da struct LDDE
      caracterizando uma lista vazia*/
      desc->inicio = NULL;
      desc->fim = NULL;
      desc->tamLista = 0;
      (*pp) = desc;

      retorno = 0;
      return retorno;    
   }   

   return retorno;
}

int insereNoInicio(LDDE *p, void *novo, int tipo){
   noLDDE *temp;   /*nó "temporário" que irá apontar para o novo elemento que será inserido na lista*/
   int retorno = 1;
   
   /*Alocação de memória para o descritor do novo nó*/
   if((temp = (noLDDE*) malloc(sizeof(noLDDE))) != NULL){
      /*Alocação de memória para os dados que são do tipo elemento*/
      if((temp->dados = (elemento*)malloc(sizeof(elemento)))!=NULL){
         /*Alocação de memória para o dado do tipo void* */
         if((temp->dados->dado = (void *)malloc(sizeof(novo)))!=NULL){
            
            /*Iniciando as variáveis da struct elemento do novo nó*/
            temp->dados->tipo = tipo;
            temp->dados->tamInfo = sizeof(novo);
            memcpy(temp->dados->dado, novo, temp->dados->tamInfo);   

            if(p->tamLista == 0){
               /*Se a lista está vazia então estaremos inserindo o primeiro elemento*/
               p->inicio = temp;
               p->fim = temp;
               temp->ant = NULL;
               temp->prox = NULL;
               p->tamLista++;

               retorno = 0;
               return retorno;
            }else{
               /*Se a lista não está vazia precisamos manipular os ponteiros para ligar
               o antigo nó de início ao novo nó que será agora o início*/                 
               p->inicio->ant = temp; //aponta pra caixinha completa 
               temp->prox = p->inicio;
               temp->ant = NULL;
               p->inicio = temp;
               p->tamLista++;

               retorno = 0;
               return retorno;
            }          
        
         }else{
            /*Se a alocação de temp->dados->dado der errado precisamos desalocar
            as duas alocações anteriores que deram certo*/
            free(temp->dados);
            free(temp);

            retorno = 1;
            return retorno;
         }
      }else{      
         /*Se a alocação de temp->dados der errado precisamos desalocar a alocação 
         anterior que deu certo*/      
         free(temp);

         retorno = 1;
         return retorno;
      }
   }else{
      /*Se a alocação de temp der errado*/
      retorno = 1;
      return retorno;
   }
   
   return retorno;
}

int insereNoFim(LDDE *p, void *novo, int tipo){
   noLDDE *temp; /*nó "temporário" que irá apontar para o novo elemento que será inserido na lista*/
   int retorno = 1;

   /*Alocação de memória para o descritor do novo nó*/
   if((temp = (noLDDE*) malloc(sizeof(noLDDE))) != NULL){
      /*Alocação de memória para os dados que são do tipo elemento*/
      if((temp->dados = (elemento*)malloc(sizeof(elemento)))!=NULL){
         /*Alocação de memória para o dado do tipo void* */
         if((temp->dados->dado = (void *)malloc(sizeof(novo)))!=NULL){

            /*Iniciando as variáveis da struct elemento do novo nó*/
            temp->dados->tipo = tipo;
            temp->dados->tamInfo = sizeof(novo);
            memcpy(temp->dados->dado, novo, temp->dados->tamInfo);     

            if(p->tamLista == 0){
               /*Se a lista está vazia então estaremos inserindo o primeiro elemento*/
               p->inicio = temp;
               p->fim = temp;
               temp->ant = NULL;
               temp->prox = NULL;
               p->tamLista++;

               retorno = 0;
               return retorno;

            }else{
               /*Se a lista não está vazia precisamos manipular os ponteiros para ligar
               o antigo nó do fim ao novo nó que será agora o fim*/                
               p->fim->prox = temp; //aponta pra caixinha completa 
               temp->ant = p->fim;
               temp->prox = NULL;
               p->fim = temp;
               p->tamLista++;

               retorno = 0;
               return retorno;
            }          
        
         }else{
            /*Se a alocação de temp->dados->dado der errado precisamos desalocar
            as duas alocações anteriores que deram certo*/
            free(temp->dados);
            free(temp);

            retorno = 1;
            return retorno;
         }
      }else{            
         /*Se a alocação de temp->dados der errado precisamos desalocar a alocação 
         anterior que deu certo*/ 
         free(temp);

         retorno = 1;
         return retorno;
      }
   }else{
      /*Se a alocação de temp der errado*/
      retorno = 1;
      return retorno;
   }

   return retorno;
}

int insereNaPosLog (LDDE *p, void *novo, int posLog, int tipo){
   noLDDE *temp; /*nó "temporário" que irá apontar para o novo elemento que será inserido na lista*/
   noLDDE *aux1, *aux2; /*ponteiros auxiliares para caminhar na lista*/
   int cont = 0;   
   int retorno = 1;

   if(posLog >= 0){
      /*Se o valor de posLog passado por parâmetro for um número positivo*/

      /*Alocação de memória para o descritor do novo nó*/
      if((temp = (noLDDE*) malloc(sizeof(noLDDE))) != NULL){
         /*Alocação de memória para os dados que são do tipo elemento*/
         if((temp->dados = (elemento*)malloc(sizeof(elemento)))!=NULL){
            /*Alocação de memória para o dado do tipo void* */
            if((temp->dados->dado = (void *)malloc(sizeof(novo)))!=NULL){

               /*Iniciando as variáveis da struct elemento do novo nó*/
               temp->dados->tipo = tipo;
               temp->dados->tamInfo = sizeof(novo);
               memcpy(temp->dados->dado, novo, temp->dados->tamInfo);  

               if(posLog == 0){
                  /*Se a posição escolhida for 0 (primeira posição da lista), então
                  chamamos a função que temos pronta (insereNoInicio)*/
                  retorno = insereNoInicio(p, novo, tipo);

                  /*Dado que a função insereNoInicio faz as devidas alocações para o
                  novo nó, aqui podemos liberar as alocações das linhas 171, 173 e 175*/
                  free(temp->dados->dado);
                  free(temp->dados);
                  free(temp);

                  return retorno;

               }else{
                  if(posLog > p->tamLista){
                     /*Se a posição escolhida for maior do que o tamanho da lista, então
                     não será possível inserir o novo elemento. Por exemplo, uma lista com 
                     tamanho = 4 possui as seguintes posições: 0,1,2,3. Se a posLog
                     for 5 ficaria um buraco vazio entre a posição 3 e a 5.
                     Então podemos liberar as alocações das linhas 171, 173 e 175*/
                     free(temp->dados->dado);
                     free(temp->dados);
                     free(temp);

                     retorno = 1;
                     return retorno;
                  }
                  if(posLog == p->tamLista){
                     /*Se a posição escolhida for igual ao tamanho da lista (última posição da 
                     lista), então chamamos a função que temos pronta (insereNoFim)*/
                     retorno = insereNoFim(p, novo, tipo);

                     /*Dado que a função insereNoFim faz as devidas alocações para o
                     novo nó, aqui podemos liberar as alocações das linhas 171, 173 e 175*/
                     free(temp->dados->dado);
                     free(temp->dados);
                     free(temp);

                     return retorno;
                  }else{
                     /*Se a posição escolhida for válida e for diferente do início e do fim
                     da lista, então precisamos arrumar os ponteiros para adicionar o novo nó*/

                     aux1 = p->inicio;
                     while(cont != posLog - 1){
                        /*O ponteiro aux1 irá percorrer a lista (partindo do início) até 
                        encontrar a posição anterior a posição que se deseja inserir*/
                        aux1 = aux1->prox;
                        cont++;
                     }
                     /*O ponteiro aux2 irá apontar para o nó da posição onde queremos
                     inserir o novo nó*/
                     aux2 = aux1->prox;

                     /*Então fazemos a manipulação dos ponteiros*/
                     aux1->prox = temp;
                     aux2->ant = temp;
                     temp->ant = aux1;
                     temp->prox = aux2;
                     p->tamLista++;

                     retorno = 0;
                     return retorno;
                  }

               }     
        
            }else{
               /*Se a alocação de temp->dados->dado der errado precisamos desalocar
               as duas alocações anteriores que deram certo*/
               free(temp->dados);
               free(temp);

               retorno = 1;
               return retorno;
            }
       
         }else{
            /*Se a alocação de temp->dados der errado precisamos desalocar a alocação 
            anterior que deu certo*/ 
            free(temp);
            
            retorno = 1;
            return retorno;
         }
      }else{
         /*Se a alocação de temp der errado*/
         retorno = 1;
         return retorno;
      }   
   }

   return retorno;
}

int removeDoInicio(LDDE *p, elemento *reg){
   noLDDE *auxiliar; /*ponteiro auxiliar para caminhar na lista*/
   int retorno = 1;

   if(p->tamLista != 0){ 
      /*Se a lista não está vazia então fazemos a cópia do primeiro elemento da lista
      para a variável reg passada por parâmetro*/

      /*Aloca espaço de memória para o dado do tipo void* */
      if((reg->dado = (void*)malloc(p->inicio->dados->tamInfo)) != NULL){
         /*Copia o dado do início para o elemento passado por parâmetro*/
         memcpy(reg->dado, p->inicio->dados->dado, p->inicio->dados->tamInfo);
         reg->tamInfo = p->inicio->dados->tamInfo;
         reg->tipo = p->inicio->dados->tipo;
      }
     
      if(p->tamLista == 1){
         /*Se tiver apenas 1 elemento na lista podemos desalocar espaço de memória
         deste elemento e a lista será setada como vazia*/
         free(p->inicio->dados->dado);
         free(p->inicio->dados);
         free(p->inicio);
         p->tamLista--;
         p->inicio=NULL;
         p->fim=NULL;

         retorno = 0;
         return retorno;
      }else{
         /*Se tiver mais de 1 elemento na lista o ponteiro auxiliar irá
         apontar para o segundo nó da lista (futuro nó de início)*/
         auxiliar = p->inicio->prox;

         /*Então podemos desalocar espaço de memória do nó que estava no 
         início e arrumar os ponteiros para indicar o novo nó de início*/
         free(p->inicio->dados->dado);
         free(p->inicio->dados);
         free(p->inicio);
         p->tamLista--;
         auxiliar->ant = NULL;
         p->inicio = auxiliar;

         retorno = 0;
         return retorno;
      }

   }
   
   retorno = 1;
   return retorno;
}

int removeDoFim(LDDE *p, elemento *reg){
   noLDDE *auxiliar; /*ponteiro auxiliar para caminhar na lista*/
   int retorno = 1;

   if(p->tamLista != 0){
      /*Se a lista não está vazia então fazemos a cópia do primeiro elemento da lista
      para a variável reg passada por parâmetro*/

      /*Aloca espaço de memória para o dado do tipo void* */
      if((reg->dado = (void*)malloc(p->fim->dados->tamInfo)) != NULL){
         /*Copia o dado do fim para o elemento passado por parâmetro*/
         memcpy(reg->dado, p->fim->dados->dado, p->fim->dados->tamInfo);
         reg->tamInfo = p->fim->dados->tamInfo;
         reg->tipo = p->fim->dados->tipo;
      }
      
      if(p->tamLista == 1){
         /*Se tiver apenas 1 elemento na lista podemos desalocar espaço de memória
         deste elemento e a lista será setada como vazia*/ 
         free(p->fim->dados->dado);
         free(p->fim->dados);
         free(p->fim);
         p->tamLista--;
         p->inicio=NULL;
         p->fim=NULL;

         retorno = 0;
         return retorno;
      
      }else{
         /*Se tiver mais de 1 elemento na lista o ponteiro auxiliar irá
         apontar para o penúltimo nó da lista (futuro nó de fim)*/
         auxiliar = p->fim->ant;

         /*Então podemos desalocar espaço de memória do nó que estava no 
         fim e arrumar os ponteiros para indicar o novo nó de fim*/
         free(p->fim->dados->dado);
         free(p->fim->dados);
         free(p->fim);
         p->tamLista--;
         auxiliar->prox = NULL;
         p->fim = auxiliar;

         retorno = 0;
         return retorno;
      }

   }

   retorno = 1;
   return retorno;
}

int removeDaPosLog(LDDE *p, elemento *reg, int posLog){
   noLDDE *aux1, *aux2, *aux3; /*ponteiros auxiliares para caminhar na lista*/
   int retorno = 1;
   int cont = 0;

   if(posLog >= 0){
      /*Se o valor de posLog passado por parâmetro for um número positivo*/

      if(p->tamLista != 0){
         /*Se a lista não estiver vazia*/

         if(posLog == 0){
            /*Se a posição escolhida for 0 (primeira posição da lista), então
            chamamos a função que temos pronta (removeDoInicio)*/
            return removeDoInicio(p, reg);

         }else{
            if(posLog == p->tamLista-1){
               /*Se a posição escolhida for a última posição da lista, então
               chamamos a função que temos pronta (removeDoFim)*/
               return removeDoFim(p, reg);
            
            }else{

               if(posLog >= p->tamLista){
                  /*Se a posição escolhida for maior do que o número de posições que
                  temos na lista não é possível remover algo que não existe*/
                  retorno = 1;
                  return retorno;
               
               }else{
                  /*Se a posição escolhida for válida e for diferente do início e do fim
                  da lista, então precisamos arrumar os ponteiros para remover o nó desejado*/

                  aux1 = p->inicio;
                  while(cont != posLog - 1){
                     /*O ponteiro aux1 irá percorrer a lista (partindo do início) até 
                     encontrar a posição anterior a posição que se deseja remover*/
                     aux1 = aux1->prox;
                     cont++;
                  }

                  /*O ponteiro aux2 irá apontar para o nó da posição que queremos remover*/
                  aux2 = aux1->prox;

                  /*O ponteiro aux3 irá apontar para o nó da posição seguinte a que queremos
                  remover*/
                  aux3 = aux2->prox;

                  /*Fazemos a cópia do elemento da posição desejada para a variável reg passada 
                  por parâmetro*/
                  if((reg->dado = (void*)malloc(aux2->dados->tamInfo)) != NULL){
                     /*Copia o dado do início para o elemento passado por parâmetro*/
                     memcpy(reg->dado, aux2->dados->dado, aux2->dados->tamInfo);
                     reg->tamInfo = aux2->dados->tamInfo;
                     reg->tipo = aux2->dados->tipo;
                  }

                  /*Conforme mencionado, o aux2 aponta para o nó que queremos remover, então
                  podemos liberar espaço de memória dele*/
                  free(aux2->dados->dado);
                  free(aux2->dados);
                  free(aux2);

                  /*Em seguida fazemos a manipulação dos ponteiros para ligar aux1 com aux3,
                  já que aux2 vou removido da lista*/
                  aux1->prox = aux3;
                  aux3->ant = aux1;
                  p->tamLista--;

                  retorno = 0;
                  return retorno;
               }
            }
         }
      }
   }

   retorno = 1;
   return retorno;
}

int buscaNoInicio(LDDE *p, elemento *reg){
   int retorno = 1;

   if(p->tamLista != 0){
      /*Se a lista não está vazia então fazemos a cópia do primeiro elemento da lista
      para a variável reg passada por parâmetro*/
      if((reg->dado = (void*)malloc(p->inicio->dados->tamInfo)) != NULL){
         memcpy(reg->dado, p->inicio->dados->dado, p->inicio->dados->tamInfo);
         reg->tamInfo = p->inicio->dados->tamInfo;
         reg->tipo = p->inicio->dados->tipo;
      }

      retorno = 0;
      return retorno;
   }

   return retorno;
}

int buscaNoFim(LDDE *p, elemento *reg){
   int retorno = 1;

   if(p->tamLista != 0){
      /*Se a lista não está vazia então fazemos a cópia do último elemento da lista
      para a variável reg passada por parâmetro*/
      if((reg->dado = (void*)malloc(p->fim->dados->tamInfo)) != NULL){
         memcpy(reg->dado, p->fim->dados->dado, p->fim->dados->tamInfo);
         reg->tamInfo = p->fim->dados->tamInfo;
         reg->tipo = p->fim->dados->tipo;
      }
      
      retorno = 0;
      return retorno;
   }

   return retorno;
}


int buscaNaPosLog(LDDE *p, elemento *reg, int posLog){
   noLDDE *aux1; /*ponteiro auxiliar para caminhar na lista*/
   int retorno = 1;
   int cont = 0;

   if(posLog >= p->tamLista || posLog < 0){
      /*Verifica se a posição escolhida é válida, isto é, ela não deve ser 
      maior do que o tamanho da lista e nem menor do que 0*/
      retorno = 1;
      return retorno;
   }

   if(p->tamLista != 0){
      /*Se a posição escolhida for válida e a lista não estiver vazia,
      então precisamos andar com o ponteiro aux1 até chegar na posição
      escolhida (partindo do início)*/
      aux1 = p->inicio;
      while(cont != posLog){
         aux1 = aux1->prox;
         cont++;
      }

      /*Copia o elemento da posição escolhida para a variável reg
      passada por parâmetro*/
      if((reg->dado = (void*)malloc(aux1->dados->tamInfo)) != NULL){
         memcpy(reg->dado, aux1->dados->dado, aux1->dados->tamInfo);
         reg->tamInfo = aux1->dados->tamInfo;
         reg->tipo = aux1->dados->tipo;
      }
      
      retorno = 0;
      return retorno;
   }
   
   return retorno;
}

/*Essa função libera espaço de memória para todos os elementos que estão
na lista e seta a lista como vazia*/
void reinicia(LDDE *p){
   noLDDE *aux1; /*ponteiro auxiliar para caminhar na lista*/

   if(p->tamLista != 0){
      /*Se a lista não está vazia então aux1 aponta para o nó de início
      e vamos percorrer a lista*/
      aux1 = p->inicio;

      for(int i = 0; i < p->tamLista; i++){
         
         /*Move o ponteiro do início p/ frente*/
         p->inicio = p->inicio->prox;  

         /*Remove o elemento apontado pelo aux1*/
         free(aux1->dados->dado);
         free(aux1->dados);
         free(aux1);

         /*aux1 aponta para a posição seguinte*/
         aux1 = p->inicio;
      }

      p->tamLista= 0;
      p->inicio = NULL;
      p->fim = NULL;
   }
}

void destroi(LDDE **pp){
   /*Chamamos a função reinicia() para liberar espaço de meória
   dos elementos ainda presentes na lista*/
   reinicia(*pp);

   /*Libera o descritor da lista*/
   free(*pp);

   (*pp) = NULL;
}

int tamanho(LDDE *p){
   return p->tamLista;
}

elemento *criarElemento(){
   elemento *e = (elemento*)malloc(sizeof(elemento));

   return e;
}

void *verDado(elemento *e){
    void *novoElem = NULL;

    if((novoElem = malloc(e->tamInfo)) != NULL){
        /*Cópia do elemento do tipo *void para a variável passada por parâmetro*/
        memcpy(novoElem, e->dado, e->tamInfo);
    }

    return novoElem;
    
}

int verTipo(elemento *e){
   return e->tipo;
}

void destruirElemento(elemento *e){
   free(e->dado);
}
