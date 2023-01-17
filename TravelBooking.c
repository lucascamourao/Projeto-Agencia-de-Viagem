#include "TravelBooking.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> //

struct data {
  int dia;
  int mes;
  int ano;
};

struct voo {
  int codigo;
  char origem[50];
  char destino[50];
};

struct no_voo {
  Voo *voo;
  struct no_voo *proximo;
};

struct lista_voo {
  struct no_voo *primeiro;
};

struct passageiro {
  int id;
  char nome[50];
  char endereco[50];
};

struct no_passageiro {
  Passageiro *passageiro;
  struct no_passageiro *proximo;
};

struct lista_passageiro {
  struct no_passageiro *primeiro;
};

struct reserva {
  int codigo;
  Data *data_viagem;
  Passageiro *passageiro;
  Voo *voo;
  Assento assento;
};

struct agenda {
  Reserva *reserva;
  Agenda *esq;
  Agenda *dir;
};

struct trecho {
  Reserva *reserva;
  struct trecho *proximo;
};

struct viagem {
  struct trecho *trechos;
};

struct tabela_viagem {
  int tamanho;
  Viagem *tabela_hash;
};
// verifica a quantidade de dias de cada mês, se o número de dias passar do
// total de dias do mês a função retorna 0, caso contrário retorna 1.
int verifica_dias(int dia, int mes) {
  if ((mes == 1 && dia <= 31) || (mes == 3 && dia <= 31) ||
      (mes == 5 && dia <= 31) || (mes == 7 && dia <= 31) ||
      (mes == 8 && dia <= 31) || (mes == 10 && dia <= 31) ||
      (mes == 12 && dia <= 31) || (mes == 2 && dia <= 28) ||
      (mes == 4 && dia <= 30) || (mes == 6 && dia <= 30) ||
      (mes == 9 && dia <= 30) || (mes == 11 && dia <= 30)) {
    return 1;
  } else {
    return 0;
  }
}

// se data1 for passado da data2 retorna 1
// se data1 for futuro da data2 retorna 2
// se forem o mesmo dia retorna 0
int passado_futuro(Data *data1, Data *data2) {
  if (data1->ano < data2->ano) {
    return 1;
  } else if (data1->ano > data2->ano) {
    return 2;
  } else {
    if (data1->mes < data2->mes) {
      return 1;
    } else if (data1->mes > data2->mes) {
      return 2;
    } else {
      if (data1->dia < data2->dia) {
        return 1;
      } else if (data1->dia > data2->dia) {
        return 2;
      } else {
        return 0;
      }
    }
  }
}

// Se nome, endereço ou ID forem invalidos, retorna -1
// Se todos os parametros forem validos, retorna 1
int verif_parametros(int id, char *nome, char *endereco) {
  if (nome == NULL || endereco == NULL) {
    return -1;
  } else if (id < 0 || strlen(nome) > 50 || strlen(endereco) > 50) {
    return -1;
  } else {
    return 1;
  }
}

// Recebe os campos <id,nome,endereco> e retorna uma passageiro com
// com esses valores ou NULL caso id<0, nome=NULL ou endereco=NULL
Passageiro *criar_passageiro(int id, char *nome, char *endereco) {
  if (verif_parametros(id, nome, endereco) == -1) {
    return NULL;
  }
  Passageiro *passageiro = (Passageiro *)malloc(sizeof(Passageiro));
  passageiro->id = id;
  strcpy(passageiro->nome, nome);
  strcpy(passageiro->endereco, endereco);
  return passageiro;
}

void pas_libera(Passageiro **passageiro) {
  if (passageiro != NULL) {
    free(*passageiro);
    *passageiro = NULL;
  }
}

// Cria e retorna um No com um passageiro dentro
// retorna NULL caso passageiro seja NULL
No_passageiro *criar_no_passageiro(Passageiro *passageiro) {
  if (passageiro == NULL) {
    return NULL;
  }
  No_passageiro *no_passageiro = (No_passageiro *)malloc(sizeof(No_passageiro));
  no_passageiro->passageiro = passageiro;

  return no_passageiro;
}

// Inicia e retorna uma lista_passageiro
Lista_Passageiro *criar_lista_passageiro() {
  Lista_Passageiro *lista_passageiro =
      (Lista_Passageiro *)malloc(sizeof(Lista_Passageiro));
  return lista_passageiro;
}

int lis_pas_libera(Lista_Passageiro **lista_passageiro) {
  if (lista_passageiro != NULL) {
    if ((*lista_passageiro)->primeiro != NULL) {
      No_passageiro *aux = (*lista_passageiro)->primeiro;
      while (aux != NULL) {
        pas_libera(&aux->passageiro);
        aux = aux->proximo;
      }
    }
    free(*lista_passageiro);
    *lista_passageiro = NULL;
    return 1;
  }
  return 0;
}

// Verifica se existe um passageiro com o id inserido, retorna NULL se o
// id não existir, a lista for vazia ou se a lista for NULL
Passageiro *buscar_passageiro(Lista_Passageiro *lista_passageiro, int id) {
  if (lista_passageiro == NULL || lista_passageiro->primeiro == NULL) {
    return NULL;
  }
  No_passageiro *no_aux = lista_passageiro->primeiro;
  Passageiro *aux = no_aux->passageiro;
  // Percorrer a lista ate o final (ate o proximo ser NULL)
  while (no_aux != NULL) {
    if (aux->id ==
        id) { // se for o ID procurado, retorna o passageiro correspondente
      return aux;
    }
    no_aux = no_aux->proximo;   // vai para o proximo no_passageiro
    if (no_aux != NULL) {       // se esse proximo no nao for NULL
      aux = no_aux->passageiro; // pega o passageiro desse novo no
    }
  }
  return NULL;
}

// Insere um novo no_passageiro a lista, retorna 1 se for possivel
// adicionar, retorna 0 caso a lista seja NULL,caso o no seja NULL ou já exista
// o id do passageiro
int inserir_passageiro(Lista_Passageiro *lista_passageiro,
                       No_passageiro *no_passageiro) {
  if (lista_passageiro == NULL || no_passageiro == NULL ||
      buscar_passageiro(lista_passageiro, no_passageiro->passageiro->id) !=
          NULL) {
    return 0; // nao eh possivel inserir esse passageiro na lista
  }
  No_passageiro *aux = lista_passageiro->primeiro;
  no_passageiro->proximo = aux; // o proximo nó recebe o primeiro nó
  lista_passageiro->primeiro = no_passageiro;
  // o primeiro nó agora recebe o novo no_passageiro a ser adicionado
  return 1;
}

// Remove e retorna no_passageiro com id inserido, retorna NULL caso id não seja
// encontrado, a lista esteja vazia ou seja NULL
Passageiro *remover_passageiro(Lista_Passageiro *lista_passageiro, int id) {
  if (buscar_passageiro(lista_passageiro, id) != NULL) {
    // se os parametros forem validos, entram no if
    No_passageiro *aux_ant = NULL;
    No_passageiro *aux = lista_passageiro->primeiro;
    while (aux->passageiro->id != id) {
      // enquanto nao for o ID desejado
      aux_ant = aux;
      // aux_ant vai recebendo um valor de no_passageiro aux que esta sendo
      // percorrido
      aux = aux->proximo;
    }
    if (aux_ant != NULL) {
      aux_ant->proximo = aux->proximo;
    } else {
      lista_passageiro->primeiro = aux->proximo;
    }
    return aux->passageiro;
  }
  return NULL;
}
// retorna 1 se dois passageiros forem iguais e 0 caso forem diferentes
int comp_passageiros(Passageiro *passageiro1, Passageiro *passageiro2) {
  if (passageiro1->id == passageiro2->id) {
    if (strcmp(passageiro1->nome, passageiro2->nome) == 0) {
      if (strcmp(passageiro1->endereco, passageiro2->endereco) == 0) {
        return 1;
      }
    }
  }
  return 0;
}

// Modifica dados de um passageiro dentro da lista inserida
// retorna 1 caso tenha sido possivel realizar a modificação
// retorna 0 caso a lista seja NULL, a lista seja vazia,
// o passageiro não seja encontrado ou as novas informações não
// sejam coerentes com o formato exigido ou o novo id já exista na lista
int editar_passageiro(Passageiro *passageiro, int id, char *nome,
                      char *endereco, Lista_Passageiro *lista_passageiro) {
  if (lista_passageiro == NULL || lista_passageiro->primeiro == NULL ||
      passageiro == NULL || id < 0 || nome == NULL || endereco == NULL ||
      buscar_passageiro(lista_passageiro, passageiro->id) == NULL ||
      (passageiro->id != id &&
       buscar_passageiro(lista_passageiro, id) != NULL)) {
    return 0;
  }
  passageiro->id = id;
  strcpy(passageiro->nome, nome);
  strcpy(passageiro->endereco, endereco);
  return 1;
}

// Recupera <id,nome,endereco> de um passageiro, caso passageiro seja
// NULL recupera <-1,'NULL','NULL'>
void acessar_passageiro(Passageiro *passageiro, int *id, char *nome,
                        char *endereco) {
  if (passageiro != NULL) {
    *id = passageiro->id;
    strcpy(nome, passageiro->nome);
    strcpy(endereco, passageiro->endereco);
  } else {
    *id = -1;
    strcpy(nome, "NULL");
    strcpy(endereco, "NULL");
  }
}

int verif_parametros2(int codigo, char *origem, char *destino) {
  if (origem == NULL || destino == NULL) {
    return -1;
  } else if (codigo < 0 || strlen(origem) > 50 || strlen(destino) > 50) {
    return -1;
  } else {
    return 1;
  }
}
// Recebe os campos <codigo,origem,destino> e retorna um voo com
// com esses valores ou NULL caso codigo<0, origem=NULL ou endereco=NULL
Voo *criar_voo(int codigo, char *origem, char *destino) {
  // isdigit(int c) : retorna 0 se não for do tipo inteiro
  if (verif_parametros2(codigo, origem, destino) == -1) {
    return NULL;
  }
  Voo *voo = (Voo *)malloc(sizeof(Voo));
  voo->codigo = codigo;
  strcpy(voo->origem, origem);
  strcpy(voo->destino, destino);
  return voo;
}

// Cria e retorna um No com um voo dentro
// retorna NULL caso voo seja NULL
No_voo *criar_no_voo(Voo *voo) {
  No_voo *no_voo = (No_voo *)malloc(sizeof(No_voo));
  if (voo != NULL) {
    no_voo->voo = voo;

    return no_voo;
  }
  return NULL; // retorna NULL se voo for nulo
}

// Inicia e retorna uma lista_voo
Lista_Voo *criar_lista_voo() {
  Lista_Voo *lista_voo = (Lista_Voo *)malloc(sizeof(Lista_Voo));
  return lista_voo;
}

// verifica se existe um voo com o codigo inserido, retorna NULL se o
// codigo não existir, a lista for vazia ou se a lista for NULL
Voo *buscar_voo(int codigo, Lista_Voo *lista_voo) {
  if (lista_voo == NULL || lista_voo->primeiro == NULL) {
    return NULL;
  }
  No_voo *no_aux = lista_voo->primeiro;
  Voo *aux = no_aux->voo;
  while (no_aux != NULL) {
    if (aux->codigo == codigo) {
      return aux;
    }
    no_aux = no_aux->proximo;
    if (no_aux != NULL) {
      aux = no_aux->voo;
    }
  }
  return NULL;
}

// Insere um novo no_voo a lista, retorna 1 se for possivel
// adicionar, retorna 0 caso a lista seja NULL,caso o no seja NULL ou já exista
// o codigo do voo
int inserir_voo(Lista_Voo *lista_voo, No_voo *no_voo) {
  if (lista_voo == NULL || no_voo == NULL ||
      buscar_voo(no_voo->voo->codigo, lista_voo) != NULL) {
    return 0;
  }
  No_voo *aux = lista_voo->primeiro;
  no_voo->proximo = aux;
  lista_voo->primeiro = no_voo;
  return 1;
}
int comp_voo(No_voo *voo, Voo *voo2) {
  Voo *voo1 = voo->voo;
  if (voo1->codigo == voo2->codigo) {
    if (strcmp(voo1->origem, voo2->origem) == 0) {
      if (strcmp(voo1->destino, voo2->destino) == 0) {
        return 1;
      } else {
        return 0;
      }
    } else {
      return 0;
    }
  } else {
    return 0;
  }
}
// Remove e retorna no_voo com codigo inserido, retorna NULL caso codigo não
// seja encontrado, a lista esteja vazia ou seja NULL
No_voo *remover_voo(int codigo, Lista_Voo *lista_voo) {
  if (buscar_voo(codigo, lista_voo) != NULL) {
    No_voo *aux_ant = NULL;
    No_voo *aux = lista_voo->primeiro;
    while (aux->voo->codigo != codigo) {
      aux_ant = aux;
      aux = aux->proximo;
    }
    if (aux_ant == NULL) {
      lista_voo->primeiro = aux->proximo;
      return aux;
    }
    aux_ant->proximo = aux->proximo;
    return aux;
  }
  return NULL;
}

// Modifica dados de um voo dentro da lista inserida
// retorna 1 caso tenha sido possivel realizar a modificação
// retorna 0 caso a lista seja NULL, a lista seja vazia,
// o voo não seja encontrado ou as novas informações não
// sejam coerentes com o formato exigido ou o novo codigo já exista na lista
int editar_voo(Voo *voo, int codigo, char *origem, char *destino,
               Lista_Voo *lista_voo) {
  if (lista_voo == NULL || lista_voo->primeiro == NULL || voo == NULL ||
      codigo < 0 || origem == NULL || destino == NULL ||
      buscar_voo(voo->codigo, lista_voo) == NULL ||
      (voo->codigo != codigo && buscar_voo(codigo, lista_voo) != NULL)) {
    return 0;
  }
  voo->codigo = codigo;
  strcpy(voo->origem, origem);
  strcpy(voo->destino, destino);
  return 1;
}

// Recupera <codigo,origem,destino> de um voo, caso voo seja
// NULL recupera <-1,'NULL','NULL'>
void acessar_voo(Voo *voo, int *codigo, char *origem, char *destino) {
  if (voo != NULL) {
    *codigo = voo->codigo;
    strcpy(origem, voo->origem);
    strcpy(destino, voo->destino);
  } else {
    *codigo = -1;
    strcpy(origem, "NULL");
    strcpy(destino, "NULL");
  }
}

// Recebe os campos <dia,mes,ano> e retorna uma data com
// com esses valores ou NULL caso dia, mes, ano nao sejam validos
Data *add_data(int dia, int mes, int ano) {
  // Data *data = (Data *)malloc(sizeof(Data)); // desse jeito n ajuda n?
  if (dia > 0 && verifica_dias(dia, mes) && mes > 0 && mes <= 12 && ano > 0) {
    Data *data = (Data *)malloc(sizeof(Data)); // aqui
    data->dia = dia;
    data->mes = mes;
    data->ano = ano;

    return data;
  }
  return NULL;
}
// reserva
// reserva
// reserva
// reserva
// reserva
// reserva
// reserva
Reserva *criar_reserva(int codigo, Data *data_viagem, Passageiro *passageiro,
                       Voo *voo, Assento assento) {
  if (codigo >= 0 && voo != NULL && data_viagem != NULL && passageiro != NULL &&
      assento >= A0 && assento <= C9) {
    Reserva *reserva = (Reserva *)malloc(sizeof(Reserva));
    reserva->codigo = codigo;
    reserva->data_viagem = data_viagem;
    reserva->passageiro = passageiro;

    reserva->voo = voo;

    reserva->assento = assento;
    return reserva;
  }
  return NULL;
}

Reserva *buscar_agenda(Agenda *agenda, int codigo) {
  if (agenda != NULL && codigo >= 0) {
    if (agenda->esq != NULL) {
      buscar_agenda(agenda->esq, codigo);
    }
    if (agenda->reserva->codigo == codigo) {
      return agenda->reserva;
    }
    if (agenda->dir != NULL) {
      buscar_agenda(agenda->dir, codigo);
    }
  }
  return NULL;
}

// Aloca memoria para uma agenda
Agenda *criar_agenda() {
  Agenda *agenda = (Agenda *)malloc(sizeof(Agenda));
  return agenda;
}

// Se der certo inserir, retorna 1. Caso não seja possível, retorna 0
int inserir_agenda(Agenda *agenda, Reserva *reserva) {
  if (reserva == NULL || agenda == NULL) {
    return 0;
  } else if (agenda->reserva == NULL) { // a agenda foi inicializada mas não tem
                                        // nada, então inserimos a raiz
    agenda->reserva = reserva;
  } else if (passado_futuro(reserva->data_viagem,
                            agenda->reserva->data_viagem) == 1 ||
             passado_futuro(reserva->data_viagem,
                            agenda->reserva->data_viagem) == 0) {
    if(agenda->esq==NULL){
      n precisa mais,
    }
  } // vou rodar no vs code agr
  return 1; // alguem ve se essa biranga ta certa pfvr (achamos que esta certo)
}

// editar os valores de um nó da agenda
int editar_agenda(Agenda *agenda, Reserva *reserva) {
  if (agenda != NULL && agenda->reserva != NULL) {
    agenda->reserva = reserva;
    remover_agenda(agenda, reserva->codigo);
    inserir_agenda(agenda, reserva);
    return 1;
  }
  return 0; // agenda null ou vazia
}

// Recebe novos dados e modifica os dados de uma reserva
int editar_reserva(Reserva *reserva, int codigo, Data *data_viagem,
                   Passageiro *passageiro, Voo *voo, Assento assento) {
  if (codigo >= 0 && data_viagem != NULL &&
      verifica_dias(data_viagem->dia, data_viagem->mes) && passageiro != NULL &&
      voo != NULL && assento >= A0 && assento <= C9) {
    reserva->codigo = codigo;
    reserva->data_viagem = data_viagem;
    reserva->passageiro = passageiro;
    reserva->voo = voo;
    reserva->assento = assento;
    return 1;
  }
  return 0;
}

// encontrar o pai do nó fornecido
Agenda *busca_pai(Agenda *agenda, int codigo) {
  while (agenda->dir->reserva->codigo != codigo ||
         agenda->esq->reserva->codigo != codigo) {
    if (agenda->reserva->codigo > codigo) {
      busca_pai(agenda->esq, codigo);
    }
    if (agenda->reserva->codigo < codigo) {
      busca_pai(agenda->dir, codigo);
    }
  }
  return agenda;
}

Agenda *min(Agenda *agenda) {
  if (agenda->esq != NULL) {
    min(agenda->esq);
  }
  return agenda;
}

Agenda *max(Agenda *agenda) {
  if (agenda->dir != NULL) {
    max(agenda->dir);
  }
  return agenda;
}

Agenda *sucessor(Agenda *agenda) {
  Agenda *sucessor = min(agenda->dir);
  return sucessor;
}

Agenda *antecessor(Agenda *agenda) {
  Agenda *antecessor = max(agenda->esq);
  return antecessor;
}

// Retorna NULL caso a agenda seja NULL ou não exista dentro da agenda, remove o
// nó com o código fornecido da agenda e retorna a agenda removida
Agenda *remover_agenda(Agenda *agenda, int codigo) {
  if (agenda == NULL || codigo < 0) {
    return NULL;
  }
  Agenda *aux_agenda = buscar_agenda(agenda, codigo);
  if (aux_agenda == NULL) {
    return NULL;
  }
  Agenda *aux_aux;
  if (aux_agenda->dir != NULL) {
    aux_aux = sucessor(aux_agenda);
  } else {
    aux_aux = antecessor(aux_agenda);
  }
  Agenda *pai = busca_pai(agenda, codigo);
  if (pai->dir->reserva->codigo == codigo) {
    pai->dir = aux_aux;
  } else {
    pai->esq = aux_aux;
  }
  if (aux_aux != NULL) {
    Agenda *pai_aux_aux = busca_pai(agenda, aux_aux->reserva->codigo);
    if (pai_aux_aux->esq == aux_aux) {
      pai_aux_aux->esq = aux_aux->dir;
    } else {
      pai_aux_aux->dir = aux_aux->esq;
    }
    aux_aux->dir = aux_agenda->dir;
    aux_aux->esq = aux_agenda->esq;
  }
  return aux_agenda;
}

// separa todas as reservas de um certo id da agenda em outra agenda separada
Reserva *busca_id(Agenda *agenda, int id) {
  if (agenda->esq != NULL) {
    busca_id(agenda->esq, id);
  }
  if (agenda->reserva->passageiro->id == id) {
    return agenda->reserva;
  }
  if (agenda->dir != NULL) {
    busca_id(agenda->dir, id);
  }
}

// busca reservas com o mesmo codigo de voo
void busca_codigo(Agenda *agenda, Agenda *agenda_codigo, int codigo) {
  if (agenda->esq != NULL) {
    busca_codigo(agenda->esq, agenda_codigo, codigo);
  }
  if (agenda->reserva->voo->codigo == codigo) {
    inserir_agenda(agenda_codigo, agenda->reserva);
  }
  if (agenda->dir != NULL) {
    busca_codigo(agenda->dir, agenda_codigo, codigo);
  }
}

// busca uma reserva pelo id do passageiro e pelo codigo do voo
Reserva *busca_id_codigo(Agenda *agenda, int id, int codigo) {
  if (agenda == NULL || agenda->reserva == NULL || id < 0 || codigo < 0) {
    return NULL;
  }
  Agenda *agenda_codigo = criar_agenda();
  busca_codigo(agenda, agenda_codigo, codigo);
  if (agenda_codigo->reserva == NULL) {
    return NULL;
  }
  Reserva *reserva = busca_id(agenda_codigo, id);
  return reserva;
}

// Busca uma uma reserva pela data dentro de uma arvore
void busca_data(Agenda *agenda, Agenda *agenda_data, Data *data) {
  if (agenda->esq != NULL) {
    busca_data(agenda->esq, agenda_data, data);
  }
  if (agenda->reserva->data_viagem->ano == data->ano &&
      agenda->reserva->data_viagem->mes == data->mes &&
      agenda->reserva->data_viagem->dia == data->dia) {
    inserir_agenda(agenda_data, agenda->reserva);
  }
  if (agenda->dir != NULL) {
    busca_data(agenda->dir, agenda_data, data);
  }
}

// Busca uma reserva pelo id do passageiro e pela data
Reserva *busca_id_data(Agenda *agenda, int id, Data *data) {
  if (agenda == NULL || id < 0 || data == NULL || agenda->reserva == NULL) {
    return NULL;
  }
  Agenda *agenda_data = criar_agenda();
  busca_data(agenda, agenda_data, data);
  if (agenda_data == NULL) {
    return NULL;
  }
  Reserva *reserva = busca_id(agenda, id);
  return reserva;
}