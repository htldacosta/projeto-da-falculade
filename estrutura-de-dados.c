#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Loja {
    char* nome;
    struct Loja* proximo;
} Loja;

typedef struct {
    Loja* inicio;
} RotaEntrega;

RotaEntrega* criar_rota() {
    RotaEntrega* rota = (RotaEntrega*) malloc(sizeof(RotaEntrega));
    rota->inicio = NULL;
    return rota;
}

void inserir_inicio(RotaEntrega* rota, const char* nome_loja) {
    Loja* nova_loja = (Loja*) malloc(sizeof(Loja));
    nova_loja->nome = (char*) malloc(strlen(nome_loja) + 1);
    strcpy(nova_loja->nome, nome_loja);
    nova_loja->proximo = rota->inicio;
    rota->inicio = nova_loja;
}

void inserir_na_posicao(RotaEntrega* rota, const char* nome_loja, int posicao) {
    if (posicao == 0) {
        inserir_inicio(rota, nome_loja);
        return;
    }

    Loja* nova_loja = (Loja*) malloc(sizeof(Loja));
    nova_loja->nome = (char*) malloc(strlen(nome_loja) + 1);
    strcpy(nova_loja->nome, nome_loja);
    nova_loja->proximo = NULL;

    Loja* atual = rota->inicio;
    int contador_atual = 0;

    while (atual != NULL && contador_atual < posicao - 1) {
        atual = atual->proximo;
        contador_atual++;
    }

    if (atual != NULL) {
        nova_loja->proximo = atual->proximo;
        atual->proximo = nova_loja;
    } else {
        printf("Posição %d inválida.\n", posicao);
        free(nova_loja->nome);
        free(nova_loja);
    }
}

void imprimir_rota(RotaEntrega* rota) {
    Loja* atual = rota->inicio;
    while (atual != NULL) {
        printf(" %s\n", atual->nome);
        atual = atual->proximo;
    }
}

void liberar_rota(RotaEntrega* rota) {
    Loja* atual = rota->inicio;
    Loja* proximo_no;
    while (atual != NULL) {
        proximo_no = atual->proximo;
        free(atual->nome);
        free(atual);
        atual = proximo_no;
    }
    free(rota);
}

int main() {
    RotaEntrega* rota = criar_rota();

    inserir_inicio(rota, "Loja D");
    inserir_inicio(rota, "Loja B");
    inserir_inicio(rota, "Loja A");

    inserir_na_posicao(rota, "Loja C", 2);

    printf(" Rota final:\n");
    imprimir_rota(rota);

    liberar_rota(rota);

    return 0;
}