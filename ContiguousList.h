%%writefile ContiguousList.h
#ifndef CONTIGUOUSLIST_H
#define CONTIGUOUSLIST_H

#include <string>
#include <cstring>
#include <iostream>

using namespace std;

// Struct limpa e compacta para maximizar o aproveitamento da Cache do CPU
struct RecordContiguo {
    char data[30];
    double demanda_residual;
};

class ContiguousList {
private:
    RecordContiguo* arr;
    int capacidade;
    int tamanho;

    // Se o bloco encher, dobramos o tamanho realocando tudo de forma contígua
    void realocar() {
        capacidade *= 2;
        RecordContiguo* novoArr = new RecordContiguo[capacidade];
        for (int i = 0; i < tamanho; i++) {
            novoArr[i] = arr[i];
        }
        delete[] arr;
        arr = novoArr;
    }

public:
    ContiguousList(int cap_inicial = 2000) {
        capacidade = cap_inicial;
        tamanho = 0;
        arr = new RecordContiguo[capacidade];
    }

    ~ContiguousList() {
        delete[] arr;
    }

    // 1. INSERÇÃO RÁPIDA
    void inserir(const string& data_str, double demanda_res) {
        if (tamanho >= capacidade) {
            realocar();
        }
        strncpy(arr[tamanho].data, data_str.c_str(), sizeof(arr[tamanho].data) - 1);
        arr[tamanho].data[sizeof(arr[tamanho].data) - 1] = '\0';
        arr[tamanho].demanda_residual = demanda_res;
        tamanho++;
    }

    // 2. BUSCA O(N), mas muito mais rápida que a Lista Encadeada devido ao Cache Hit
    bool buscar(const string& data_str) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(arr[i].data, data_str.c_str()) == 0) {
                return true;
            }
        }
        return false;
    }

    // 3. REMOÇÃO O(N)
    bool remover(const string& data_str) {
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(arr[i].data, data_str.c_str()) == 0) {
                // Move o último elemento para a posição removida para manter a contiguidade O(1)
                arr[i] = arr[tamanho - 1];
                tamanho--;
                return true;
            }
        }
        return false;
    }
};

#endif
