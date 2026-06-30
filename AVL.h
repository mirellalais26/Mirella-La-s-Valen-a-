%%writefile AVL.h
#ifndef AVL_H
#define AVL_H

#include <string>
#include <iostream>

using namespace std;

struct NoAVL {
    string data;
    double demanda_residual;
    NoAVL* esq;
    NoAVL* dir;
    int altura;
};

// Funções utilitárias
inline int altura(NoAVL* N) {
    if (N == NULL) return 0;
    return N->altura;
}

inline int max_val(int a, int b) {
    return (a > b) ? a : b;
}

inline NoAVL* novoNoAVL(string data, double demanda_residual) {
    NoAVL* no = new NoAVL();
    no->data = data;
    no->demanda_residual = demanda_residual;
    no->esq = NULL;
    no->dir = NULL;
    no->altura = 1;
    return no;
}

// Rotações
inline NoAVL* rotacaoDireita(NoAVL* y) {
    NoAVL* x = y->esq;
    NoAVL* T2 = x->dir;
    x->dir = y;
    y->esq = T2;
    y->altura = max_val(altura(y->esq), altura(y->dir)) + 1;
    x->altura = max_val(altura(x->esq), altura(x->dir)) + 1;
    return x;
}

inline NoAVL* rotacaoEsquerda(NoAVL* x) {
    NoAVL* y = x->dir;
    NoAVL* T2 = y->esq;
    y->esq = x;
    x->dir = T2;
    x->altura = max_val(altura(x->esq), altura(x->dir)) + 1;
    y->altura = max_val(altura(y->esq), altura(y->dir)) + 1;
    return y;
}

inline int getBalanceamento(NoAVL* N) {
    if (N == NULL) return 0;
    return altura(N->esq) - altura(N->dir);
}

// 1. INSERÇÃO
inline NoAVL* inserirAVL(NoAVL* no, string data, double demanda_residual) {
    if (no == NULL) return novoNoAVL(data, demanda_residual);

    if (data < no->data)
        no->esq = inserirAVL(no->esq, data, demanda_residual);
    else if (data > no->data)
        no->dir = inserirAVL(no->dir, data, demanda_residual);
    else
        return no;

    no->altura = 1 + max_val(altura(no->esq), altura(no->dir));
    int balanceamento = getBalanceamento(no);

    if (balanceamento > 1 && data < no->esq->data)
        return rotacaoDireita(no);
    if (balanceamento < -1 && data > no->dir->data)
        return rotacaoEsquerda(no);
    if (balanceamento > 1 && data > no->esq->data) {
        no->esq = rotacaoEsquerda(no->esq);
        return rotacaoDireita(no);
    }
    if (balanceamento < -1 && data < no->dir->data) {
        no->dir = rotacaoDireita(no->dir);
        return rotacaoEsquerda(no);
    }
    return no;
}

// 2. BUSCA O(log N)
inline NoAVL* buscarAVL(NoAVL* raiz, const string& data) {
    if (raiz == NULL || raiz->data == data)
        return raiz;
    if (raiz->data < data)
        return buscarAVL(raiz->dir, data);
    return buscarAVL(raiz->esq, data);
}

// Função auxiliar para encontrar o menor nó (usado na remoção)
inline NoAVL* noMenorValor(NoAVL* no) {
    NoAVL* atual = no;
    while (atual->esq != NULL)
        atual = atual->esq;
    return atual;
}

// 3. REMOÇÃO O(log N) com rebalanceamento
inline NoAVL* removerAVL(NoAVL* raiz, const string& data) {
    if (raiz == NULL) return raiz;

    if (data < raiz->data)
        raiz->esq = removerAVL(raiz->esq, data);
    else if (data > raiz->data)
        raiz->dir = removerAVL(raiz->dir, data);
    else {
        if ((raiz->esq == NULL) || (raiz->dir == NULL)) {
            NoAVL* temp = raiz->esq ? raiz->esq : raiz->dir;
            if (temp == NULL) {
                temp = raiz;
                raiz = NULL;
            } else
                *raiz = *temp;
            delete temp;
        } else {
            NoAVL* temp = noMenorValor(raiz->dir);
            raiz->data = temp->data;
            raiz->demanda_residual = temp->demanda_residual;
            raiz->dir = removerAVL(raiz->dir, temp->data);
        }
    }

    if (raiz == NULL) return raiz;

    raiz->altura = 1 + max_val(altura(raiz->esq), altura(raiz->dir));
    int balanceamento = getBalanceamento(raiz);

    if (balanceamento > 1 && getBalanceamento(raiz->esq) >= 0)
        return rotacaoDireita(raiz);
    if (balanceamento > 1 && getBalanceamento(raiz->esq) < 0) {
        raiz->esq = rotacaoEsquerda(raiz->esq);
        return rotacaoDireita(raiz);
    }
    if (balanceamento < -1 && getBalanceamento(raiz->dir) <= 0)
        return rotacaoEsquerda(raiz);
    if (balanceamento < -1 && getBalanceamento(raiz->dir) > 0) {
        raiz->dir = rotacaoDireita(raiz->dir);
        return rotacaoEsquerda(raiz);
    }

    return raiz;
}

#endif
