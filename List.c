%%writefile list.c
#include "List.h"

NodeList *lista_ligada = NULL;

int in(NodeList** head, EletricDates *dado) {
    NodeList* novo = (NodeList*)malloc(sizeof(NodeList));
    if (!novo) {
        perror("malloc");
        return 0;
    }
    novo->dado = *dado;
    novo->next = NULL;

    if (*head == NULL) {
        *head = novo;
    } else {
        NodeList* atual = *head;
        while (atual->next != NULL) {
            atual = atual->next;
        }
        atual->next = novo;
    }
    return 1;
}

// Implementação da Busca O(N)
NodeList* buscar_lista(NodeList* head, const char* data_str) {
    NodeList* atual = head;
    while (atual != NULL) {
        if (strcmp(atual->dado.data, data_str) == 0) {
            return atual; // Encontrou o nó
        }
        atual = atual->next;
    }
    return NULL; // Não encontrou
}

// Implementação da Remoção O(N) com religação de ponteiros
int remover_lista(NodeList** head, const char* data_str) {
    if (*head == NULL) return 0; // Lista vazia

    NodeList* atual = *head;
    NodeList* anterior = NULL;

    // Se o elemento a remover for o primeiro da lista (Head)
    if (strcmp(atual->dado.data, data_str) == 0) {
        *head = atual->next; // A cabeça passa a ser o segundo elemento
        free(atual);         // Libera a memória do primeiro
        return 1;
    }

    // Procura no resto da lista
    while (atual != NULL && strcmp(atual->dado.data, data_str) != 0) {
        anterior = atual;
        atual = atual->next;
    }

    // Se chegou ao fim e não encontrou
    if (atual == NULL) return 0;

    // Desconecta o nó da lista e liga o anterior ao próximo
    anterior->next = atual->next;
    free(atual);
    return 1;
}

void liberar_lista(NodeList** head) {
    NodeList* atual = *head;
    while (atual != NULL) {
        NodeList* proximo = atual->next;
        free(atual);
        atual = proximo;
    }
    *head = NULL;
}
