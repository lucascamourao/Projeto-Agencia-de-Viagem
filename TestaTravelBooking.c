#include "TravelBooking.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

time_t agora = time(NULL);
char *string_data = ctime(&agora);
printf("%s\n", string_data);
// Imprime data no formato: DIA da SEMANA MES DIA HH:MM:SS YYYY
// Ex: Tue Nov 29 16:56:56 2022

*/

//=============================================== PASSAGEIRO

void teste_criar_passageiro_dados_validos() {

  Passageiro *passageiro = criar_passageiro(1, "João Lucas", "Russas");
  if (passageiro != NULL) {
    printf("teste_criar_passageiro_dados_validos PASSOU\n");
  } else {
    printf("teste_criar_passageiro_dados_validos NÃO PASSOU\n");
  }
}

void teste_criar_passageiro_dados_nulos() {

  Passageiro *passageiro = criar_passageiro(0, NULL, NULL);
  if (passageiro == NULL) {
    printf("teste_criar_passagero_dados_nulos PASSOU\n");
  } else {
    printf("teste_criar_passagero_dados_nulos NÃO PASSOU\n");
  }
}

void teste_criar_passageiro_dados_invalidos() {
  int id = 0;
  char nome[55];
  char endereco[55];

  for (int i = 0; i < 53; i++) {
    strcat(nome, "N");
  }
  for (int i = 0; i < 53; i++) {
    strcat(endereco, "C");
  }
  // ID n pode ser -1 por algum motivo
  Passageiro *passageiro = criar_passageiro(-1, nome, endereco);
  if (passageiro == NULL) {
    printf("teste_criar_passagero_dados_invalidos PASSOU\n");
  }
}

void teste_criar_no_passageiro_validos() {
  Passageiro *passageiro = criar_passageiro(1, "João Lucas", "Rua A , 368");
  No_passageiro *no_passageiro = criar_no_passageiro(passageiro);
  if (no_passageiro != NULL) {
    printf("teste_cria_no_passageiro_validos PASSOU\n");
    Lista_Passageiro *lista = criar_lista_passageiro();
  } else {
    printf("teste_cria_no_passageiro_validos NÃO PASSOU\n");
  }
}

void teste_criar_no_passageiro_nulos() {
  Passageiro *passageiro = NULL;
  No_passageiro *no = criar_no_passageiro(passageiro);
  if (no == NULL) {
    printf("teste_criar_no_passageiro_nulos PASSOU\n");
  } else {
    printf("teste_criar_no_passageiro_nulos NÃO PASSOU\n");
  }
}

void teste_criar_lista_passageiro_validos() {
  Lista_Passageiro *lista = criar_lista_passageiro();
  if (lista != NULL) {
    printf("teste_criar_lista_passageiro_validos PASSOU\n");
  } else {
    printf("testecriar_lista_passageiro_validos NÃO PASSOU\n");
  }
}

//----------------------------------------------------------INSERIR PASSAGEIRO
void teste_inserir_lista_passageiro_com_dados_validos() {
  int id;
  char nome[50];
  char endereco[100];

  Lista_Passageiro *lista = criar_lista_passageiro();

  Passageiro *passageiro1 = criar_passageiro(1, "Lucas", "Osasco");
  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  Passageiro *passageiro2 = criar_passageiro(2, "Fluvio", "Fortal");
  No_passageiro *no2 = criar_no_passageiro(passageiro2);
  Passageiro *passageiro3 = criar_passageiro(3, "Nicolas", "Russas");
  No_passageiro *no3 = criar_no_passageiro(passageiro3);

  if (lista != NULL) {
    if (inserir_passageiro(lista, no1) == 1) {
      if (inserir_passageiro(lista, no2) == 1) {
        if (inserir_passageiro(lista, no3) == 1) {
          printf("teste_inserir_passageiro_com_dados_validos PASSOU\n");
        } else {
          printf("teste_inserir_passageiro_com_dados_validos NÃO PASSOU\n");
        }
      } else {
        printf("teste_inserir_passageiro_com_dados_validos NÃO PASSOU\n");
      }
    } else {
      printf("teste_inserir_passageiro_com_dados_validos NÃO PASSOU\n");
    }
  } else {
    printf("teste_inserir_passageiro_com_dados_validos NÃO PASSOU\n");
  }
}

void teste_inserir_lista_passageiro_com_dados_invalidos() {
  Lista_Passageiro *lista = criar_lista_passageiro();

  if (lista != NULL) { // id iguais
    Passageiro *passageiro1 = criar_passageiro(1, "Jorge", "Uberlândia");
    No_passageiro *no1 = criar_no_passageiro(passageiro1);
    inserir_passageiro(lista, no1);
    Passageiro *passageiro2 = criar_passageiro(1, "Pigmeu", "Itaquaquecetuba");
    No_passageiro *no2 = criar_no_passageiro(passageiro2);
    if (inserir_passageiro(lista, no2) == 0) {
      printf("teste_inserir_passageiro_com_dados_invalidos PASSOU\n");
    }
  } else {
    printf("teste_inserir_passageiro_com_dados_invalidos NÃO PASSOU\n");
  }
}

void teste_inserir_lista_passageiro_com_dados_nulos() {
  Lista_Passageiro *lista = criar_lista_passageiro();
  if (inserir_passageiro(lista, NULL) == 0) {
    Passageiro *passageiro1 = criar_passageiro(1, "Jorge", "Uberlândia");
    No_passageiro *no1 = criar_no_passageiro(passageiro1);
    if (inserir_passageiro(NULL, no1) == 0) {
      if (inserir_passageiro(NULL, NULL) == 0) {
        printf("teste_inserir_passageiro_com_dados_nulos PASSOU.\n");
      } else {
        printf("teste_inserir_passageiro_com_dados_nulos NÃO PASSOU.\n");
      }
    } else {
      printf("teste_inserir_passageiro_com_dados_nulos NÃO PASSOU.\n");
    }
  } else {
    printf("teste_inserir_passageiro_com_dados_nulos NÃO PASSOU.\n");
  }
}

//----------------------------------------------------------BUSCAR PASSAGEIRO

void teste_busca_passageiro_validos() {
  int id;
  char nome[50];
  char endereco[50];

  Lista_Passageiro *lista_passageiro = criar_lista_passageiro();
  Passageiro *passageiro1 = criar_passageiro(3, "Beto", "Amapa");
  Passageiro *passageiro2 = criar_passageiro(1, "Fluvio", "Fortal");
  Passageiro *passageiro3 = criar_passageiro(2, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(4, "Julia", "Rio");
  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  No_passageiro *no2 = criar_no_passageiro(passageiro2);
  No_passageiro *no3 = criar_no_passageiro(passageiro3);
  No_passageiro *no4 = criar_no_passageiro(passageiro4);

  inserir_passageiro(lista_passageiro, no1);
  inserir_passageiro(lista_passageiro, no2);
  inserir_passageiro(lista_passageiro, no3);
  inserir_passageiro(lista_passageiro, no4);

  Passageiro *aux = buscar_passageiro(lista_passageiro, 3);
  if (aux != NULL) {
    acessar_passageiro(aux, &id, nome, endereco);
    if (id == 3 && strcmp(nome, "Beto") == 0 &&
        strcmp(endereco, "Amapa") == 0) {
      printf("teste_busca_passageiro_validos PASSOU\n");
    } else {
      printf("teste_busca_passageiro_validos NÃO PASSOU\n");
    }
  } else {
    printf("teste_busca_passageiro_validos NÃO PASSOU\n");
  }
}

void teste_busca_passageiro_invalidos() {
  int id;
  char nome[50];
  char endereco[50];
  Lista_Passageiro *lista_passageiro = criar_lista_passageiro();
  Passageiro *passageiro1 = criar_passageiro(3, "Beto", "Amapa");
  Passageiro *passageiro2 = criar_passageiro(1, "Fluvio", "Fortal");
  Passageiro *passageiro3 = criar_passageiro(2, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(4, "Julia", "Rio");
  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  No_passageiro *no2 = criar_no_passageiro(passageiro2);
  No_passageiro *no3 = criar_no_passageiro(passageiro3);
  No_passageiro *no4 = criar_no_passageiro(passageiro4);

  inserir_passageiro(lista_passageiro, no1);
  inserir_passageiro(lista_passageiro, no2);
  inserir_passageiro(lista_passageiro, no3);
  inserir_passageiro(lista_passageiro, no4);

  Passageiro *aux = buscar_passageiro(lista_passageiro, 6);
  if (aux == NULL) {
    printf("teste_busca_passageiro_invalidos PASSOU\n");
  } else {
    printf("teste_busca_passageiro_invalidos NÃO PASSOU\n");
  }
}

void teste_busca_passageiro_nulos() {
  Lista_Passageiro *lista_passageiro = criar_lista_passageiro();
  Passageiro *aux = buscar_passageiro(NULL, 1);

  if (aux == NULL || buscar_passageiro(lista_passageiro, 1) == NULL) {
    printf("teste_busca_passageiro_nulos PASSOU \n");
  } else {
    printf("teste_busca_passageiro_nulos NÃO PASSOU \n");
  }
}

//----------------------------------------------------------REMOVER PASSAGEIRO

void teste_remove_passageiro_validos() {
  Lista_Passageiro *lista_passageiro = criar_lista_passageiro();
  Passageiro *passageiro1 = criar_passageiro(3, "Beto", "Amapa");
  Passageiro *passageiro2 = criar_passageiro(1, "Fluvio", "Fortal");
  Passageiro *passageiro3 = criar_passageiro(2, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(4, "Julia", "Rio");
  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  No_passageiro *no2 = criar_no_passageiro(passageiro2);
  No_passageiro *no3 = criar_no_passageiro(passageiro3);
  No_passageiro *no4 = criar_no_passageiro(passageiro4);

  inserir_passageiro(lista_passageiro, no1);
  inserir_passageiro(lista_passageiro, no2);
  inserir_passageiro(lista_passageiro, no3);
  inserir_passageiro(lista_passageiro, no4);

  if (comp_passageiros(remover_passageiro(lista_passageiro, 4), passageiro4) ==
      1) {
    if (comp_passageiros(remover_passageiro(lista_passageiro, 3),
                         passageiro1) == 1) {
      if (comp_passageiros(remover_passageiro(lista_passageiro, 2),
                           passageiro3) == 1) {
        if (comp_passageiros(remover_passageiro(lista_passageiro, 1),
                             passageiro2) == 1) {
          printf("teste_remover_passageiros_validos PASSOU'\n");
        } else {
          printf("teste_remover_passageiros_validos NÃO PASSOU\n");
        }
      } else {
        printf("teste_remover_passageiros_validos NÃO PASSOU\n");
      }
    } else {
      printf("teste_remover_passageiros_validos NÃO PASSOU\n");
    }
  } else {
    printf("teste_remover_passageiros_validos NÃO PASSOU\n");
  }
}

void teste_remove_passageiro_invalidos() {
  Lista_Passageiro *lista_passageiro = criar_lista_passageiro();
  Passageiro *passageiro1 = criar_passageiro(3, "Beto", "Amapa");
  Passageiro *passageiro2 = criar_passageiro(1, "Fluvio", "Fortal");
  Passageiro *passageiro3 = criar_passageiro(2, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(4, "Julia", "Rio");
  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  No_passageiro *no2 = criar_no_passageiro(passageiro2);
  No_passageiro *no3 = criar_no_passageiro(passageiro3);
  No_passageiro *no4 = criar_no_passageiro(passageiro4);

  inserir_passageiro(lista_passageiro, no1);
  inserir_passageiro(lista_passageiro, no2);
  inserir_passageiro(lista_passageiro, no3);
  inserir_passageiro(lista_passageiro, no4);

  if (remover_passageiro(lista_passageiro, 6) == NULL) {
    printf("teste_remover_passageiros_invalidos PASSOU'\n");
  } else {
    printf("teste_remover_passageiros_invalidos NÃO PASSOU\n");
  }
}

void teste_remove_passageiro_nulos() {
  Lista_Passageiro *lista_passageiro = NULL;
  if (remover_passageiro(NULL, 1) == NULL) {
    printf("teste_remover_passageiros_nulos PASSOU'\n");
  } else {
    printf("teste_remover_passageiros_nulos NÃO PASSOU'\n");
  }
}
//----------------------------------------------------------EDITAR PASSAGEIRO
void teste_editar_passageiro_validos() {
  int id;
  char nome[50];
  char endereco[50];
  Lista_Passageiro *lista_passageiro = criar_lista_passageiro();
  Passageiro *passageiro1 = criar_passageiro(3, "Beto", "Amapa");
  Passageiro *passageiro2 = criar_passageiro(1, "Fluvio", "Fortal");
  Passageiro *passageiro3 = criar_passageiro(2, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(4, "Julia", "Rio");
  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  No_passageiro *no2 = criar_no_passageiro(passageiro2);
  No_passageiro *no3 = criar_no_passageiro(passageiro3);
  No_passageiro *no4 = criar_no_passageiro(passageiro4);
  inserir_passageiro(lista_passageiro, no1);
  inserir_passageiro(lista_passageiro, no2);
  inserir_passageiro(lista_passageiro, no3);
  inserir_passageiro(lista_passageiro, no4);

  if (editar_passageiro(passageiro2, 1, "Flavio", "Amapa", lista_passageiro) ==
      1) {
    printf("teste_editar_passageiro_validos PASSOU\n");
  } else {
    printf("teste_editar_passageiro_validos NÃO PASSOU\n");
  }
}

void teste_editar_passageiro_invalidos() {
  int id;
  char nome[50];
  char endereco[50];
  Lista_Passageiro *lista_passageiro = criar_lista_passageiro();
  Passageiro *passageiro1 = criar_passageiro(3, "Beto", "Amapa");
  Passageiro *passageiro2 = criar_passageiro(1, "Fluvio", "Fortal");
  Passageiro *passageiro3 = criar_passageiro(2, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(4, "Julia", "Rio");
  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  No_passageiro *no2 = criar_no_passageiro(passageiro2);
  No_passageiro *no3 = criar_no_passageiro(passageiro3);
  No_passageiro *no4 = criar_no_passageiro(passageiro4);
  inserir_passageiro(lista_passageiro, no1);
  inserir_passageiro(lista_passageiro, no2);
  inserir_passageiro(lista_passageiro, no3);
  inserir_passageiro(lista_passageiro, no4);
  if (editar_passageiro(passageiro2, 2, "Fluvio", "Amapa", lista_passageiro) ==
          0 ||
      editar_passageiro(passageiro2, 1, NULL, "Amapa", lista_passageiro) == 0 ||
      editar_passageiro(passageiro2, 1, "Fluvio", NULL, lista_passageiro) ==
          0) {
    printf("teste_editar_passageiro_invalidos PASSOU\n");
  } else {
    printf("teste_editar_passageiro_invalidos NÃO PASSOU\n");
  }
}

void teste_editar_passageiro_nulos() {
  Passageiro *passageiro = NULL;
  Lista_Passageiro *lista_passageiro = NULL;
  char nome[50], endereco[50];
  Lista_Passageiro *lista_passageiro_2 = criar_lista_passageiro();
  Passageiro *passageiro1 = criar_passageiro(3, "Beto", "Amapa");
  Passageiro *passageiro2 = criar_passageiro(1, "Fluvio", "Fortal");
  Passageiro *passageiro3 = criar_passageiro(2, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(4, "Julia", "Rio");
  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  No_passageiro *no2 = criar_no_passageiro(passageiro2);
  No_passageiro *no3 = criar_no_passageiro(passageiro3);
  No_passageiro *no4 = criar_no_passageiro(passageiro4);
  inserir_passageiro(lista_passageiro, no1);
  inserir_passageiro(lista_passageiro, no2);
  inserir_passageiro(lista_passageiro, no3);
  inserir_passageiro(lista_passageiro, no4);
  if (editar_passageiro(passageiro, 3, "Beto", "Amapa", lista_passageiro_2) ==
      0) {
    if (editar_passageiro(passageiro1, 3, NULL, "Amapa", lista_passageiro_2) ==
        0) {
      if (editar_passageiro(passageiro1, 3, "Beto", NULL, lista_passageiro_2) ==
          0) {
        if (editar_passageiro(passageiro1, 3, "Beto", "Amapa",
                              lista_passageiro) == 0) {
          printf("teste_editar_passageiro_nulos PASSOU\n");
        } else {
          printf("teste_editar_passageiro_nulos NÃO PASSOU\n");
        }
      } else {
        printf("teste_editar_passageiro_nulos NÃO PASSOU\n");
      }
    } else {
      printf("teste_editar_passageiro_nulos NÃO PASSOU\n");
    }
  } else {
    printf("teste_editar_passageiro_nulos NÃO PASSOU\n");
  }
}

//----------------------------------------------------------ACESSAR PASSAGEIRO

void teste_acessar_passageiro_validos() {
  int id;
  char nome[50];
  char endereco[50];
  Lista_Passageiro *lista_passageiro = criar_lista_passageiro();
  Passageiro *passageiro1 = criar_passageiro(3, "Beto", "Amapa");
  Passageiro *passageiro2 = criar_passageiro(1, "Fluvio", "Fortal");
  Passageiro *passageiro3 = criar_passageiro(2, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(4, "Julia", "Rio");
  No_passageiro *no1 = criar_no_passageiro(passageiro1);
  No_passageiro *no2 = criar_no_passageiro(passageiro2);
  No_passageiro *no3 = criar_no_passageiro(passageiro3);
  No_passageiro *no4 = criar_no_passageiro(passageiro4);

  acessar_passageiro(passageiro1, &id, nome, endereco);
  if (id == 3 && strcmp(nome, "Beto") == 0 && strcmp(endereco, "Amapa") == 0) {
    printf("teste_acessa_passageiro_validos PASSOU \n");
  } else {
    printf("teste_acessa_passageiro_validos NÃO PASSOU \n");
  }
}

void teste_acessar_passageiro_nulos() {
  int id;
  char nome[50];
  char endereco[50];

  Passageiro *passageiro1 = NULL;
  acessar_passageiro(passageiro1, &id, nome, endereco);
  if (id == -1 && strcmp(nome, "NULL") == 0 && strcmp("NULL", endereco) == 0) {
    printf("teste_acessa_passageiro_nulos PASSOU \n");
  } else {
    printf("teste_acessa_passageiro_nulos NÃO PASSOU \n");
  }
}

//================================================ VOO
//================================================ VOO
//================================================ VOO

void teste_criar_voo_dados_validos() {
  Voo *voo = criar_voo(1, "Fortaleza", "São Paulo");
  if (voo != NULL) {
    printf("teste_criar_voo PASSOU com dados válidos.\n");
  } else {
    printf("teste_criar_voo NÃO PASSOU com dados válidos.\n");
  }
}

void teste_criar_voo_dados_invalidos() { // incompleto?
  int codigo = 0;
  char origem[55] = "";
  char destino[55] = "";
  for (int i = 0; i < 53; i++) {
    strcat(origem, "N");
  }
  for (int i = 0; i < 53; i++) {
    strcat(destino, "C");
  }
  Voo *voo = criar_voo(-1, origem, destino);
  if (voo == NULL) {
    printf("teste_criar_voo_dados_invalidos PASSOU\n");
  }
}

void teste_criar_voo_dados_nulos() {
  Voo *voo = criar_voo(-1, NULL, NULL);
  if (voo == NULL) { //
    printf("teste_criar_voo PASSOU com dados nulos.\n");
  } else {
    printf("teste_criar_voo NÃO PASSOU com dados nulos.\n");
  }
}

void teste_criar_no_voo_validos() {

  Voo *voo1 = criar_voo(5, "Nova York", "Washington DC");
  Voo *voo2 = criar_voo(6, "Paris", "Bordeaux");
  No_voo *no_voo = criar_no_voo(voo2);

  if (no_voo != NULL) {
    printf("teste_criar_no_voo PASSOU com dados válidos.\n");
  } else {
    printf("teste_criar_no_voo NÃO PASSOU com dados válidos.\n");
  }
}

void teste_criar_no_voo_nulos() {
  No_voo *no_voo = criar_no_voo(NULL);

  if (no_voo == NULL) {
    printf("teste_criar_no_voo() PASSOU com dados nulos.\n");
  } else {
    printf("teste_criar_no_voo() NÃO PASSOU com dados nulos.\n");
  }
}

void teste_criar_lista_voo_validos() {
  Lista_Voo *lista = criar_lista_voo();
  if (lista != NULL) {
    printf("teste_criar_lista_voo_validos() PASSOU\n");
  } else {
    printf("teste_criar_lista_voo_validos NÃO PASSOU\n");
  }
}

//----------------------------------------------------------INSERIR VOO

void teste_inserir_lista_voo_com_dados_validos() { // ve se ta certo ae2

  Lista_Voo *lista = criar_lista_voo();

  Voo *voo1 = criar_voo(1, "Paris", "Osasco");
  No_voo *no1 = criar_no_voo(voo1);
  Voo *voo2 = criar_voo(2, "Acre", "Fortal");
  No_voo *no2 = criar_no_voo(voo2);
  Voo *voo3 = criar_voo(3, "Japão", "Russas");
  No_voo *no3 = criar_no_voo(voo3);

  if (lista != NULL) {
    if (inserir_voo(lista, no1) == 1) {
      if (inserir_voo(lista, no2) == 1) {
        if (inserir_voo(lista, no3) == 1) {
          printf("teste_inserir_voo_com_dados_validos PASSOU\n");
        } else {
          printf("teste_inserir_voo_com_dados_validos NÃO PASSOU\n");
        }
      } else {
        printf("teste_inserir_voo_com_dados_validos NÃO PASSOU\n");
      }
    } else {
      printf("teste_inserir_voo_com_dados_validos NÃO PASSOU\n");
    }
  } else {
    printf("teste_inserir_voo_com_dados_validos NÃO PASSOU\n");
  }
}

void teste_inserir_lista_voo_com_dados_invalidos() {

  Lista_Voo *lista = criar_lista_voo(); // Inicia e retorna uma lista_voo

  if (lista != NULL) { // id iguais
    Voo *voo1 = criar_voo(1, "Paris", "Uberlândia");
    No_voo *no1 = criar_no_voo(voo1);
    inserir_voo(lista, no1);
    Voo *voo2 = criar_voo(1, "Fortaleza", "Itaquaquecetuba");
    No_voo *no2 = criar_no_voo(voo2);
    if (inserir_voo(lista, no2) == 0) {
      printf("teste_inserir_voo_com_dados_invalidos PASSOU\n");
    }
  } else {
    printf("teste_inserir_voo_com_dados_invalidos NÃO PASSOU\n");
  }
}

void teste_inserir_lista_voo_com_dados_nulos() {
  Lista_Voo *lista = criar_lista_voo();
  if (inserir_voo(lista, NULL) == 0) {
    Voo *voo1 = criar_voo(1, "Paris", "Uberlândia");
    No_voo *no1 = criar_no_voo(voo1);
    if (inserir_voo(NULL, no1) == 0) {
      if (inserir_voo(NULL, NULL) == 0) {
        printf("teste_inserir_lista_voo_com_dados_nulos PASSOU.\n");
      } else {
        printf("Teste_inserir_lista_voo_com_dados_nulos NÃO PASSOU.\n");
      }
    } else {
      printf("Teste_inserir_lista_voo_com_dados_nulos NÃO PASSOU.\n");
    }
  } else {
    printf("teste_inserir_lista_voo_com_dados_nulos NÃO PASSOU.\n");
  }
}

//----------------------------------------------------------BUSCAR VOO

void teste_busca_voo_validos() {
  int id;
  char origem[50];
  char destino[50];

  Lista_Voo *lista_voo = criar_lista_voo();
  Voo *voo1 = criar_voo(3, "São Paulo", "Amapa");
  Voo *voo2 = criar_voo(1, "Manaus", "Fortal");
  Voo *voo3 = criar_voo(2, "Rio de Janeiro", "Russas");
  Voo *voo4 = criar_voo(4, "Paris", "Rio");
  No_voo *no1 = criar_no_voo(voo1);
  No_voo *no2 = criar_no_voo(voo2);
  No_voo *no3 = criar_no_voo(voo3);
  No_voo *no4 = criar_no_voo(voo4);

  inserir_voo(lista_voo, no1);
  inserir_voo(lista_voo, no2);
  inserir_voo(lista_voo, no3);
  inserir_voo(lista_voo, no4);

  Voo *aux = buscar_voo(3, lista_voo);
  if (aux != NULL) {
    acessar_voo(aux, &id, origem, destino);
    if (id == 3 && strcmp(origem, "São Paulo") == 0 &&
        strcmp(destino, "Amapa") == 0) {
      printf("teste_busca_voo_validos PASSOU\n");
    } else {
      printf("teste_busca_voo_validos NÃO PASSOU\n");
    }
  } else {
    printf("teste_busca_voo_validos NÃO PASSOU\n");
  }
}

void teste_busca_voo_invalidos() {
  int codigo;
  char origem[50];
  char destino[50];
  Lista_Voo *lista_voo = criar_lista_voo();
  Voo *voo1 = criar_voo(3, "São Paulo", "Amapa");
  Voo *voo2 = criar_voo(1, "Manaus", "Fortal");
  Voo *voo3 = criar_voo(2, "Rio de Janeiro", "Russas");
  Voo *voo4 = criar_voo(4, "Paris", "Rio");
  No_voo *no1 = criar_no_voo(voo1);
  No_voo *no2 = criar_no_voo(voo2);
  No_voo *no3 = criar_no_voo(voo3);
  No_voo *no4 = criar_no_voo(voo4);

  inserir_voo(lista_voo, no1);
  inserir_voo(lista_voo, no2);
  inserir_voo(lista_voo, no3);
  inserir_voo(lista_voo, no4);

  Voo *aux = buscar_voo(6, lista_voo);
  if (aux == NULL) {
    printf("teste_busca_voo_invalidos PASSOU\n");
  } else {
    printf("teste_busca_voo_invalidos NÃO PASSOU\n");
  }
}

void teste_busca_voo_nulos() {
  Lista_Voo *lista_voo = criar_lista_voo();
  Voo *aux = buscar_voo(1, NULL);

  if (aux == NULL || buscar_voo(1, lista_voo) == NULL) {
    printf("teste_busca_voo_nulos PASSOU \n");
  } else {
    printf("teste_busca_voo_nulos NÃO PASSOU \n");
  }
}

//----------------------------------------------------------REMOVER VOO
void teste_remove_voo_dados_validos() {
  Lista_Voo *lista_voo = criar_lista_voo();
  Voo *voo1 = criar_voo(3, "São Paulo", "Amapa");
  Voo *voo2 = criar_voo(1, "Manaus", "Fortal");
  Voo *voo3 = criar_voo(2, "Rio de Janeiro", "Russas");
  Voo *voo4 = criar_voo(4, "Paris", "Rio");
  No_voo *no1 = criar_no_voo(voo1);
  No_voo *no2 = criar_no_voo(voo2);
  No_voo *no3 = criar_no_voo(voo3);
  No_voo *no4 = criar_no_voo(voo4);
  inserir_voo(lista_voo,
              no1); // obs: implicit declaration of inserir_voo is invalid - JN
  inserir_voo(lista_voo, no2);
  inserir_voo(lista_voo, no3);
  inserir_voo(lista_voo, no4);
  if (comp_voo(remover_voo(4, lista_voo), voo4) == 1) {
    if (comp_voo(remover_voo(3, lista_voo), voo1) == 1) {
      if (comp_voo(remover_voo(2, lista_voo), voo3) == 1) {
        if (comp_voo(remover_voo(1, lista_voo), voo2) == 1) {
          printf("teste_remover_voo_validos PASSOU'\n");
        } else {
          printf("teste_remover_voo_validos NÃO PASSOU\n");
        }
      } else {
        printf("teste_remover_voo_validos NÃO PASSOU\n");
      }
    } else {
      printf("teste_remover_voo_validos NÃO PASSOU\n");
    }
  } else {
    printf("teste_remover_voo_validos NÃO PASSOU\n");
  }
}

void teste_remove_voo_invalidos() {
  Lista_Voo *lista_voo = criar_lista_voo();
  Voo *voo1 = criar_voo(3, "São Paulo", "Amapa");
  Voo *voo2 = criar_voo(1, "Manaus", "Fortal");
  Voo *voo3 = criar_voo(2, "Rio de Janeiro", "Russas");
  Voo *voo4 = criar_voo(4, "Paris", "Rio");
  No_voo *no1 = criar_no_voo(voo1);
  No_voo *no2 = criar_no_voo(voo2);
  No_voo *no3 = criar_no_voo(voo3);
  No_voo *no4 = criar_no_voo(voo4);
  inserir_voo(lista_voo, no1);
  inserir_voo(lista_voo, no2);
  inserir_voo(lista_voo, no3);
  inserir_voo(lista_voo, no4);

  if (remover_voo(6, lista_voo) == NULL) {
    printf("teste_remover_voo_validos PASSOU'\n");
  } else {
    printf("teste_remover_voo_validos NÃO PASSOU\n");
  }
}

void teste_remove_voo_dados_nulos() {
  Lista_Voo *lista_voo = NULL;
  if (remover_voo(1, NULL) == NULL) {
    printf("teste_remover_voo_nulos PASSOU'\n");
  } else {
    printf("teste_remover_voo_nulos NÃO PASSOU'\n");
  }
}

//----------------------------------------------------------EDITAR VOO

void teste_editar_voo_validos() {

  Lista_Voo *lista_voo = criar_lista_voo();

  Voo *voo1 = criar_voo(3, "São Paulo", "Amapa");
  Voo *voo2 = criar_voo(1, "Manaus", "Fortal");
  Voo *voo3 = criar_voo(2, "Rio de Janeiro", "Russas");
  Voo *voo4 = criar_voo(4, "Paris", "Rio");

  No_voo *no1 = criar_no_voo(voo1);
  No_voo *no2 = criar_no_voo(voo2);
  No_voo *no3 = criar_no_voo(voo3);
  No_voo *no4 = criar_no_voo(voo4);

  inserir_voo(lista_voo, no1);
  inserir_voo(lista_voo, no2);
  inserir_voo(lista_voo, no3);
  inserir_voo(lista_voo, no4);

  if (editar_voo(voo1, 3, "Rio de Janeiro", "Sergipe", lista_voo) == 1) {
    printf("teste_editar_voo_validos PASSOU.\n");
  } else {
    printf("teste_editar_voo_validos NÃO PASSOU.\n");
  }
}

void teste_editar_voos_invalidos() {

  Lista_Voo *lista_voo = criar_lista_voo();

  Voo *voo1 = criar_voo(3, "São Paulo", "Amapa");
  Voo *voo2 = criar_voo(1, "Manaus", "Fortal");
  Voo *voo3 = criar_voo(2, "Rio de Janeiro", "Russas");
  Voo *voo4 = criar_voo(4, "Paris", "Rio");

  No_voo *no1 = criar_no_voo(voo1);
  No_voo *no2 = criar_no_voo(voo2);
  No_voo *no3 = criar_no_voo(voo3);
  No_voo *no4 = criar_no_voo(voo4);
  // id errado, dado nulo (?)
  if (editar_voo(voo1, 2, "São Paulo", "Amazonas", lista_voo) == 0 ||
      editar_voo(voo1, 3, NULL, "Amapa", lista_voo) == 0 ||
      editar_voo(voo1, 3, "São Paulo", NULL, lista_voo) == 0) {
    printf("teste_editar_voo_invalidos PASSOU.\n");
  } else {
    printf("teste_editar_voo_invalidos NÃO PASSOU.\n");
  }
}

void teste_editar_voo_nulos() {
  Voo *voo = NULL;
  Lista_Voo *lista_voo = NULL;
  char origem[50], destino[50];

  Lista_Voo *lista_voo_2 = criar_lista_voo();

  Voo *voo1 = criar_voo(3, "São Paulo", "Amapa");
  Voo *voo2 = criar_voo(1, "Manaus", "Fortal");
  Voo *voo3 = criar_voo(2, "Rio de Janeiro", "Russas");
  Voo *voo4 = criar_voo(4, "Paris", "Rio");

  No_voo *no1 = criar_no_voo(voo1);
  No_voo *no2 = criar_no_voo(voo2);
  No_voo *no3 = criar_no_voo(voo3);
  No_voo *no4 = criar_no_voo(voo4);

  inserir_voo(lista_voo, no1);
  inserir_voo(lista_voo, no2);
  inserir_voo(lista_voo, no3);
  inserir_voo(lista_voo, no4);
  if (editar_voo(voo, 3, "São Paulo", "Amapa", lista_voo_2) == 0) {
    if (editar_voo(voo1, 3, NULL, "Amapa", lista_voo_2) == 0) {
      if (editar_voo(voo1, 3, "São Paulo", NULL, lista_voo_2) == 0) {
        if (editar_voo(voo1, 3, "Beto", "Amapa", lista_voo) == 0) {
          printf("teste_editar_voo_nulos PASSOU\n");
        } else {
          printf("teste_editar_voo_nulos NÃO PASSOU\n");
        }
      } else {
        printf("teste_editar_voo_nulos NÃO PASSOU\n");
      }
    } else {
      printf("teste_editar_voo_nulos NÃO PASSOU\n");
    }
  } else {
    printf("teste_editar_voo_nulos NÃO PASSOU\n");
  }
}

void teste_acessar_voo_validos() {
  int codigo;
  char origem[50];
  char destino[50];

  Lista_Voo *lista_voo = criar_lista_voo();
  Voo *voo1 = criar_voo(3, "São Paulo", "Amapa");
  Voo *voo2 = criar_voo(1, "Manaus", "Fortal");
  Voo *voo3 = criar_voo(2, "Rio de Janeiro", "Russas");
  Voo *voo4 = criar_voo(4, "Paris", "Rio");

  No_voo *no1 = criar_no_voo(voo1);
  No_voo *no2 = criar_no_voo(voo2);
  No_voo *no3 = criar_no_voo(voo3);
  No_voo *no4 = criar_no_voo(voo4);

  acessar_voo(voo1, &codigo, origem, destino);
  if (codigo == 3 && strcmp(origem, "São Paulo") == 0 &&
      strcmp(destino, "Amapa") == 0) {
    printf("teste_acessa_voo_validos PASSOU.\n");
  } else {
    printf("teste_acessa_voo_validos NÃO PASSOU.\n");
  }
}

void teste_acessar_voo_nulos() {
  int codigo;
  char origem[50];
  char destino[50];

  Voo *voo1 = NULL;
  acessar_voo(voo1, &codigo, origem, destino);
  if (codigo == -1 && strcmp(origem, "NULL") == 0 &&
      strcmp("NULL", destino) == 0) {
    printf("teste_acessa_voo_nulos PASSOU.\n");
  } else {
    printf("teste_acessa_voo_nulos NÃO PASSOU. \n");
  }
}

//================================================ RESERVA
//================================================ RESERVA
//================================================ RESERVA

// não faço ideia se o que eu to fazendo tá minimamente certo, mas eu tentei -
// JN 02/12 ;-;

// data valida
void teste_criar_data_validos() {
  Data *data = add_data(3, 10, 2023);
  if (data != NULL) {
    printf("teste_criar_data_validos PASSOU\n");
  } else {
    printf("teste_criar_data_validos NÃO PASSOU\n");
  }
}

// datas invalidas
void teste_criar_data_invalidos() {
  Data *data1 = add_data(30, 2, 2022); // invalido
  Data *data2 = add_data(2, 13, 2022); // invalido
  if (data1 == NULL) {
    if (data2 == NULL) {
      printf("teste_criar_data_invalidos PASSOU\n");
    } else {
      printf("teste_criar_data_invalidos NÃO PASSOU\n");
    }
  } else {
    printf("teste_criar_data_invalidos NÃO PASSOU\n");
  }
}

// dados válidos: código >= 0; voo != NULL; data_viagem != NULL
void teste_criar_reserva_dados_validos() {
  Passageiro *passageiro = criar_passageiro(1, "João Lucas", "Russas");
  Voo *voo = criar_voo(2, "Ceará", "Minas Gerais");
  Data *data = add_data(4, 9, 2022);
  // Reserva *criar_reserva(int codigo, Data *data_viagem, Passageiro
  // *passageiro, Voo *voo, Assento assento)
  Reserva *reserva = criar_reserva(1, data, passageiro, voo, A0);

  if (reserva != NULL) {
    printf("teste_criar_reserva_dados_validos PASSOU.\n");
  } else {
    printf("teste_criar_reserva_dados_validos NÃO PASSOU.\n");
  }
}

// dados inválidos: código < 0; data inválida; passageiro inválido; voo
// inválido; assento inválido perguntinha: no TravelBooking.c, no criar_reserva,
// na condição não deveria ter passageiro e assento != NULL?
// (!!!!!!!!!!!!!!!!!!)
// - JN

// Concertei isso, o assento é considerado int, os assentos variam de A0 a C9
// - JL

// retorna NULL se não é possível criar a reserva (é o que esperamos)
void teste_criar_reserva_dados_invalidos() {
  Data *data1 = add_data(4, 9, 2022);  // válida
  Data *data2 = add_data(-1, 9, 2022); // inválida
  Passageiro *passageiro1 =
      criar_passageiro(1, "João Lucas", "Russas"); // válido
  Passageiro *passageiro2 =
      criar_passageiro(-1000, "João Lucas", "Russas"); // inválido
  Voo *voo1 = criar_voo(2, "Ceará", "Minas Gerais");   // válido
  Voo *voo2 = criar_voo(-2, "Ceará", "Minas Gerais");  // inválido
  Assento assento1 = A0;                               // existe
  Assento assento2 = -1;                               // não existe
  Reserva *reserva1 =
      criar_reserva(-1, data1, passageiro1, voo1, assento1); // codigo inv.
  Reserva *reserva2 =
      criar_reserva(1, data2, passageiro1, voo1, assento1); // data inv.
  Reserva *reserva3 =
      criar_reserva(1, data1, passageiro2, voo1, assento1); // passag. inv.
  Reserva *reserva4 =
      criar_reserva(1, data1, passageiro1, voo2, assento1); // voo inv.
  Reserva *reserva5 =
      criar_reserva(1, data1, passageiro1, voo1, assento2); // assento inv.

  // basta uma info inválida que a função retorna NULL

  if (reserva1 == NULL && reserva2 == NULL && reserva3 == NULL &&
      reserva4 == NULL && reserva5 == NULL) {
    printf("teste_criar_reserva_dados_invalidos PASSOU.\n");
  } else {
    printf("teste_criar_reserva_dados_invalidos NÃO PASSOU.\n");
  }
}

void teste_criar_reserva_dados_nulos() { // esperamos que retorne NULL caso um
                                         // dos parâmetros seja NULL
  Passageiro *passageiro = criar_passageiro(1, "João Lucas", "Russas");
  Voo *voo = criar_voo(2, "Ceará", "Minas Gerais");
  Data *data = add_data(4, 9, 2022);

  Reserva *reserva2 = criar_reserva(1, NULL, passageiro, voo, A0); // data NULL
  Reserva *reserva3 = criar_reserva(1, data, NULL, voo, A0); // passag. NULL
  Reserva *reserva4 = criar_reserva(1, data, passageiro, NULL, A0); // voo NULL

  if (reserva2 == NULL && reserva3 == NULL && reserva4 == NULL) {
    printf("teste_criar_reserva_dados_nulos PASSOU.\n");
  } else {
    printf("teste_criar_reserva_dados_nulos NÃO PASSOU.\n");
  }
}

//----------------------------------------------------------CRIAR AGENDA

void teste_criar_agenda() {
  Agenda *agenda = criar_agenda();
  if (agenda != NULL) {
    printf("teste_criar_agenda PASSOU\n");
  } else {
    printf("teste_criar_agenda NÃO PASSOU\n");
  }
}

//----------------------------------------------------------BUSCAR AGENDA

void teste_buscar_agenda_dados_validos() {
  Passageiro *passageiro1 = criar_passageiro(3, "Beto", "Amapa");
  Passageiro *passageiro2 = criar_passageiro(1, "Fluvio", "Fortal");
  Passageiro *passageiro3 = criar_passageiro(2, "Nicolas", "Russas");
  Passageiro *passageiro4 = criar_passageiro(4, "Julia", "Rio");
  Voo *voo1 = criar_voo(3, "São Paulo", "Amapa");
  Voo *voo2 = criar_voo(1, "Manaus", "Fortal");
  Voo *voo3 = criar_voo(2, "Rio de Janeiro", "Russas");
  Voo *voo4 = criar_voo(4, "Paris", "Rio");
  Data *data1 = add_data(10, 3, 2002);
  Data *data2 = add_data(11, 5, 2022);
  Data *data3 = add_data(18, 6, 2012);
  Data *data4 = add_data(10, 2, 2001);
  Agenda *agenda = criar_agenda();
  Reserva *reserva1 = criar_reserva(1, data1, passageiro1, voo1, A1);
  Reserva *reserva2 = criar_reserva(2, data2, passageiro2, voo2, A2);
  Reserva *reserva3 = criar_reserva(3, data3, passageiro3, voo3, A3);
  Reserva *reserva4 = criar_reserva(4, data4, passageiro4, voo4, A4);
  inserir_agenda(agenda, reserva1);
  inserir_agenda(agenda, reserva2);
  inserir_agenda(agenda, reserva3);
  inserir_agenda(agenda, reserva4);
  if(buscar_agenda(agenda,3)==reserva3){
    printf("teste_buscar_agenda_dados_validos PASSOU\n");
  }else{
    printf("teste_buscar_agenda_dados_validos NÃO PASSOU\n");
  }
}

//----------------------------------------------------------EDITAR RESERVA

//*editar_reserva(Reserva *reserva, int codigo, Data *data_viagem, Passageiro
//*passageiro, Voo *voo, Assento assento)

// if (codigo >= 0 && verifica_dias(data_viagem->dia, data_viagem->mes)
// &&passageiro != NULL && voo != NULL

// espera-se que a função editar_reserva() retorne a reserva com novos dados se
// estes forem válidos e ((se não existir uma reserva com o msm código)) -> Como
// q eu faço isso hein? Usando uma função que busca/acessa o código?-JN

void teste_editar_reserva_dados_validos() { // INCOMPLETO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
  Passageiro *passageiro = criar_passageiro(1, "João Lucas", "Russas");
  Passageiro *passageiro2 = criar_passageiro(6, "Julia", "São Paulo");
  Voo *voo = criar_voo(2, "Ceará", "Minas Gerais");
  Voo *voo2 = criar_voo(3, "Ceará", "Rio Grande do Sul");
  Data *data = add_data(4, 9, 2022);
  Data *data2 = add_data(10, 3, 2022);
  Reserva *reserva =
      criar_reserva(1, data, passageiro, voo,
                    A0); // ta dando use of undeclared identifier data

  if (editar_reserva(reserva, 2, data2, passageiro2, voo2, A1) != NULL) {
    printf("teste_editar_reserva_dados_validos PASSOU\n");
  } else {
    printf("teste_editar_reserva_dados_validos NÃO PASSOU\n");
  }
}

// espera-se que a função retorne NULL - basta UM parâmetro INVÁLIDO
void teste_editar_reserva_dados_invalidos() {
  Data *data1 = add_data(4, 9, 2022);
  Passageiro *passageiro1 = criar_passageiro(1, "João Lucas", "Russas");
  Voo *voo1 = criar_voo(2, "Ceará", "Minas Gerais");
  Assento assento1 = A0; // existe
  Assento assento2 = 30; // não existe
  int codigo = 1000;
  int codigo2 = -1;
  Reserva *reserva = criar_reserva(codigo, data1, passageiro1, voo1,
                                   assento1); // reserva válida
  Reserva *reserva_editada =
      editar_reserva(reserva, codigo2, data1, passageiro1, voo1, assento2);

  if (reserva_editada == NULL) {
    printf("teste_editar_reserva_dados_invalidos PASSOU.\n");
  } else {
    printf("teste_editar_reserva_dados_invalidos NÃO PASSOU.\n");
  }
}

// espera-se que a função retorne NULL - basta UM parâmetro NULL
void teste_editar_reserva_dados_nulos() {
  Passageiro *passageiro = criar_passageiro(1, "João Lucas", "Russas");
  Voo *voo = criar_voo(2, "Ceará", "Minas Gerais");
  Voo *voo2 = criar_voo(3, "Ceará", "Rio Grande do Sul");
  Data *data = add_data(4, 9, 2022);
  Reserva *reserva = criar_reserva(1, data, passageiro, voo, A0);

  Reserva *reserva_editada2 =
      editar_reserva(reserva, 1, NULL, passageiro, voo, A0);
  Reserva *reserva_editada3 = editar_reserva(reserva, 1, data, NULL, voo, A0);
  Reserva *reserva_editada4 =
      editar_reserva(reserva, 1, data, passageiro, NULL, A0);

  if (reserva_editada2 == NULL && reserva_editada3 == NULL &&
      reserva_editada4 == NULL) {
    printf("teste_editar_reserva_dados_nulos PASSOU.\n");
  } else {
    printf("teste_editar_reserva_dados_nulos NÃO PASSOU.\n");
  }
}

// PROGRAMA PRINCIPAL
int main() {
  // TESTES PASSAGEIRO //20 funções
  printf("Testes funções do PASSAGEIRO:\n");
  printf("\n \n");
  teste_criar_passageiro_dados_validos();
  teste_criar_passageiro_dados_invalidos();
  teste_criar_passageiro_dados_nulos();
  teste_criar_no_passageiro_validos();
  teste_criar_no_passageiro_nulos();
  teste_criar_lista_passageiro_validos();
  printf("\n");
  teste_inserir_lista_passageiro_com_dados_validos();
  teste_inserir_lista_passageiro_com_dados_invalidos();
  teste_inserir_lista_passageiro_com_dados_nulos();
  printf("\n");
  teste_busca_passageiro_validos();
  teste_busca_passageiro_invalidos();
  teste_busca_passageiro_nulos();
  printf("\n");
  teste_remove_passageiro_validos();
  teste_remove_passageiro_invalidos();
  teste_remove_passageiro_nulos();
  printf("\n");
  teste_editar_passageiro_validos();
  teste_editar_passageiro_invalidos();
  teste_editar_passageiro_nulos();
  teste_acessar_passageiro_validos();
  teste_acessar_passageiro_nulos();
  printf("\n \n \n");

  // TESTES VOO //20 funções
  printf("Testes funções do VOO:\n");
  printf("\n \n");
  teste_criar_voo_dados_validos();
  teste_criar_voo_dados_invalidos();
  teste_criar_voo_dados_nulos();
  teste_criar_no_voo_validos();
  teste_criar_no_voo_nulos();
  teste_criar_lista_voo_validos();
  printf("\n");
  teste_inserir_lista_voo_com_dados_validos();
  teste_inserir_lista_voo_com_dados_invalidos();
  teste_inserir_lista_voo_com_dados_nulos();
  printf("\n");
  teste_busca_voo_validos();
  teste_busca_voo_invalidos();
  teste_busca_voo_nulos();
  printf("\n");
  teste_remove_voo_dados_validos();
  teste_remove_voo_invalidos();
  teste_remove_voo_dados_nulos();
  printf("\n");
  teste_editar_voo_validos();
  teste_editar_voos_invalidos();
  teste_editar_voo_nulos();
  teste_acessar_voo_validos();
  teste_acessar_voo_nulos();
  printf("\n \n");

  // TESTES RESERVA
  printf("Testes funções da RESERVA:\n \n");
  teste_criar_data_validos();
  teste_criar_data_invalidos();
  printf("\n \n");
  teste_criar_reserva_dados_validos();   // testar
  teste_criar_reserva_dados_invalidos(); // testar
  teste_criar_reserva_dados_nulos();     // testar
  printf("\n \n");
  teste_criar_agenda();
  printf("\n \n");
  teste_buscar_agenda_dados_validos();
  //teste_buscar_agenda_dados_invalidos();
  //teste_buscar_agenda_dados_nulos();
  printf("\n \n");
  //teste_inserir_agenda_dados_validos();
  //teste_inserir_agenda_dados_invalidos();
  //teste_inserir_agenda_dados_nulos();
  printf("\n \n");
  //teste_editar_reserva_dados_validos();   // incompleto
  //teste_editar_reserva_dados_invalidos(); // incompleto
  //teste_editar_reserva_dados_nulos();     // incompleto
  printf("\n \n");
  return 0;
}