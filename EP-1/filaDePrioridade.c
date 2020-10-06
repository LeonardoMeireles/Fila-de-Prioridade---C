/*********************************************************************/
/**   ACH2023 - Algoritmos e Estruturas de Dados I                  **/
/**   EACH-USP - Segundo Semestre de 2020                           **/
/**   04  - Prof. Luciano Antonio Digiampietri                      **/
/**                                                                 **/
/**   EP1 - Fila de Prioridade                                      **/
/**                                                                 **/
/**   Leonardo Meireles da Silva                 11796207           **/
/**                                                                 **/
/*********************************************************************/

#include "filaDePrioridade.h"

//Busca pela posição ideal para um elemento em termos de prioridade. Retornando um elemento que deve ser seu antecessor.
PONT buscaSeqOrd(PFILA f, float p){
    PONT atual = f->fila->prox;
    while (atual != f->fila){
        if (p > atual->prioridade || p == atual->prioridade){
            return atual->ant;
        }
        atual = atual->prox;
    }
    return atual->ant;
}

PFILA criarFila(int max){
  PFILA res = (PFILA) malloc(sizeof(FILADEPRIORIDADE));
  res->maxElementos = max;
  res->arranjo = (PONT*) malloc(sizeof(PONT)*max);
  int i;
  for (i=0;i<max;i++) res->arranjo[i] = NULL;
  PONT cabeca = (PONT) malloc(sizeof(ELEMENTO));
  res->fila = cabeca;
  cabeca->ant = cabeca;
  cabeca->prox = cabeca;
  cabeca->id = -1;
  cabeca->prioridade = 1000000;
  return res;
}

void exibirLog(PFILA f){
  printf("Log [elementos: %i (alem do no cabeca)]\n", tamanho(f));
  PONT atual = f->fila;
  printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
  atual = atual->prox;
  while (atual != f->fila){
    printf("%p[%i;%f;%p]%p ", atual->ant, atual->id, atual->prioridade, atual, atual->prox);
    atual = atual->prox;
  }
  printf("\nElementos validos: ");
  atual = atual->prox;
  while (atual != f->fila){
    printf("[%i;%f;%p] ", atual->id, atual->prioridade, atual);
    atual = atual->prox;
  }

  printf("\nValores do arrajo:\n\[ ");
  int x;
  for (x=0;x<f->maxElementos;x++) printf("%p ",f->arranjo[x]);
  printf("]\n\n");
}


//Retorna o tamanho da fila
int tamanho(PFILA f){
  int tam = 0;
  PONT end = f->fila->prox;
  while (end != f->fila){
  tam++;
  end = end->prox;
  }
  return tam;
}


//Insere um elemento na posição ideal beaseando em sua prioridade.
bool inserirElemento(PFILA f, int id, float prioridade){
  bool resposta = false;
  if (id < 0 || id > f->maxElementos)
    return resposta;
  else if (f->arranjo[id] != NULL)
    return resposta;
  //Confirmamos que esse id é valido.
  resposta = true;
  PONT novo = (PONT)malloc(sizeof(ELEMENTO));
  novo->id = id;
  novo->prioridade = prioridade;
  f->arranjo[id] = novo;
  //Alocando o id na fila.
  //Caso ele seja o primeiro elemento na fila
  if (f->fila->prox == f->fila){ 
      f->fila->prox = novo;
      f->fila->ant = novo;
      novo->prox = f->fila;
      novo->ant = f->fila;
  }
  //Caso já existe um elemento na fila
  else{
    PONT posicao = buscaSeqOrd(f, prioridade);
    novo->prox = posicao->prox;
    novo->ant = posicao;
    posicao->prox->ant = novo;
    posicao->prox = novo;
  }
  return resposta;
}

//Aumentar a prioridade de um elemento e muda-lo de posição de acordo com essa sua nova prioridade
bool aumentarPrioridade(PFILA f, int id, float novaPrioridade){
  bool resposta = false;
  if (id < 0 || id >= f->maxElementos)
    return resposta;
  if (f->arranjo[id] == NULL)
    return resposta;
  if (f->arranjo[id]->prioridade >= novaPrioridade)
    return resposta;
  PONT novaPosicao = buscaSeqOrd(f, novaPrioridade);
  //Se a nova posição retornada (posição anterior à aquela que ele devera ser colocado) for igual ao seu anterior.
  if (novaPosicao->id == f->arranjo[id]->ant->id){
    f->arranjo[id]->prioridade = novaPrioridade;
    resposta = true;
    return resposta;
  }
  //Se a nova posição retornada (posição anterior à aquela que ele devera ser colocado) for a mesma posição que ele já se encontra, então ele continua no mesmo lugar.
  if (novaPosicao == f->arranjo[id]){
    f->arranjo[id]->prioridade = novaPrioridade;
    resposta = true;
    return resposta;
  }
  f->arranjo[id]->prox->ant = f->arranjo[id]->ant;
  f->arranjo[id]->ant->prox = f->arranjo[id]->prox;
  f->arranjo[id]->prioridade = novaPrioridade;
  f->arranjo[id]->prox = novaPosicao->prox;
  f->arranjo[id]->ant = novaPosicao;
  novaPosicao->prox->ant = f->arranjo[id];
  novaPosicao->prox = f->arranjo[id];
  resposta = true;
  return resposta;
}


//Diminuir a prioridade de um elemento e muda-lo de posição de acordo com essa sua nova prioridade
bool reduzirPrioridade(PFILA f, int id, float novaPrioridade){
  bool resposta = false;
  if (id < 0 || id >= f->maxElementos)
    return resposta;
  if (f->arranjo[id] == NULL)
    return resposta;
  if (f->arranjo[id]->prioridade <= novaPrioridade)
    return resposta;
  PONT novaPosicao = buscaSeqOrd(f, novaPrioridade);
  //Se a nova posição retornada (posição anterior à aquela que ele devera ser colocado) for igual ao seu anterior.
  if (novaPosicao->id == f->arranjo[id]->ant->id){
    f->arranjo[id]->prioridade = novaPrioridade;
    resposta = true;
    return resposta;
  }
  //Se a nova posição retornada (posição anterior à aquela que ele devera ser colocado) for a mesma posição que ele já se encontra, então ele continua no mesmo lugar.
  if (novaPosicao == f->arranjo[id]){
    f->arranjo[id]->prioridade = novaPrioridade;
    resposta = true;
    return resposta;
  }
  f->arranjo[id]->prox->ant = f->arranjo[id]->ant;
  f->arranjo[id]->ant->prox = f->arranjo[id]->prox;
  f->arranjo[id]->prioridade = novaPrioridade;
  f->arranjo[id]->prox = novaPosicao->prox;
  f->arranjo[id]->ant = novaPosicao;
  novaPosicao->prox->ant = f->arranjo[id];
  novaPosicao->prox = f->arranjo[id];
  resposta = true;
  return resposta;
}


//Remove um elemento da lista e retorna um ponteiro para esse elemento
PONT removerElemento(PFILA f){
  PONT resposta = NULL;
  if (f->fila->prox == f->fila)
    return resposta;
  PONT apagar = f->fila->prox;
  apagar->prox->ant = f->fila;
  f->fila->prox = apagar->prox;
  int id_ex = apagar->id;
  f->arranjo[id_ex] = NULL;
  resposta = apagar;
  return resposta;
}


//Armazena a prioridade de um certo elemento em um float passado como parâmetro.
bool consultarPrioridade(PFILA f, int id, float* resposta){
  bool resp = false;
  if (id < 0 || id > f->maxElementos)
    return resp;
  else if (f->arranjo[id] == NULL)
    return resp;
  *resposta = f->arranjo[id]->prioridade;
  resp = true;
  return resp;
}
