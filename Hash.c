%%writefile hash.c
#include "Hash.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

#define INITIAL_SIZE 1024
#define MAX_LOAD_FACTOR 0.7
int qtd_elementos = 0;

#define LIVRE 0
#define OCUPADO 1
#define REMOVIDO 2

int TABLE_SIZE = INITIAL_SIZE;
Entrada *hashLinear = NULL;

unsigned long hashDJB2(const char *str) {
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c;
    return hash;
}

int hashSimples(const char *chave, int tamanho) {
    return hashDJB2(chave) % tamanho;
}

void inicializarHash() {
    if (hashLinear) {
        free(hashLinear);
        hashLinear = NULL;
    }
    hashLinear = (Entrada*)malloc(TABLE_SIZE * sizeof(Entrada));
    if (!hashLinear) {
        perror("malloc");
        exit(1);
    }
    for (int i = 0; i < TABLE_SIZE; i++) hashLinear[i].ocupado = LIVRE;
    qtd_elementos = 0;
}

int inserirHash_linear_sem_rehash(const Entrada *e) {
    int pos = hashSimples(e->chave, TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (pos + i) % TABLE_SIZE;
        if (hashLinear[idx].ocupado == LIVRE || hashLinear[idx].ocupado == REMOVIDO) {
            hashLinear[idx] = *e;
            hashLinear[idx].ocupado = OCUPADO;
            qtd_elementos++;
            return 1;
        }
    }
    return 0;
}

void rehash_linear() {
    int old_size = TABLE_SIZE;
    Entrada *old_table = hashLinear;

    TABLE_SIZE *= 2;
    hashLinear = (Entrada*)malloc(TABLE_SIZE * sizeof(Entrada));
    for (int i = 0; i < TABLE_SIZE; i++) hashLinear[i].ocupado = LIVRE;

    qtd_elementos = 0;

    for (int i = 0; i < old_size; i++) {
        if (old_table[i].ocupado == OCUPADO) {
            inserirHash_linear_sem_rehash(&old_table[i]);
        }
    }

    free(old_table);
}

int inserirHash_linear(const Entrada *e) {
    if ((double)(qtd_elementos + 1) / TABLE_SIZE > MAX_LOAD_FACTOR) {
        rehash_linear();
    }

    int pos = hashSimples(e->chave, TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (pos + i) % TABLE_SIZE;
        if (hashLinear[idx].ocupado == LIVRE || hashLinear[idx].ocupado == REMOVIDO) {
            hashLinear[idx] = *e;
            hashLinear[idx].ocupado = OCUPADO;
            qtd_elementos++;
            return 1;
        }
    }
    return 0;
}

// Implementação da busca: pula os REMOVIDOS e para apenas se encontrar LIVRE
Entrada* buscarHash_linear(const char *chave) {
    int pos = hashSimples(chave, TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (pos + i) % TABLE_SIZE;
        if (hashLinear[idx].ocupado == LIVRE) {
            return NULL; // Se encontrou livre, o elemento de fato não existe
        }
        if (hashLinear[idx].ocupado == OCUPADO && strcmp(hashLinear[idx].chave, chave) == 0) {
            return &hashLinear[idx];
        }
    }
    return NULL;
}

// Implementação da remoção conceitual estável
int removerHash_linear(const char *chave) {
    int pos = hashSimples(chave, TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        int idx = (pos + i) % TABLE_SIZE;
        if (hashLinear[idx].ocupado == LIVRE) {
            return 0; // Elemento não encontrado
        }
        if (hashLinear[idx].ocupado == OCUPADO && strcmp(hashLinear[idx].chave, chave) == 0) {
            hashLinear[idx].ocupado = REMOVIDO; // Marcação lógica estável
            qtd_elementos--;
            return 1; // Removido com sucesso
        }
    }
    return 0;
}

void estatisticasHash() {
    int count = 0;
    double soma = 0, min = 1e9, max = -1e9;
    for (int i = 0; i < TABLE_SIZE; i++) {
        if (hashLinear[i].ocupado == OCUPADO) {
            double v = hashLinear[i].demanda_residual;
            soma += v;
            if (v < min) min = v;
            if (v > max) max = v;
            count++;
        }
    }
    if (count)
        printf("Média: %.2f | Mín: %.2f | Máx: %.2f\n", soma / count, min, max);
    else
        printf("Nenhum dado disponível.\n");
}

void liberarHashLinear() {
    if (hashLinear) {
        free(hashLinear);
        hashLinear = NULL;
        TABLE_SIZE = 0;
        qtd_elementos = 0;
    }
}
