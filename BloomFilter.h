%%writefile BloomFilter.h
#ifndef BLOOMFILTER_H
#define BLOOMFILTER_H

#include <string>
#include <vector>

using namespace std;

class BloomFilter {
private:
    vector<bool> tabela;
    size_t tamanho;

    // --- 3 Funções de Hash Diferentes para espalhar os bits perfeitamente ---
    // 1. Hash DJB2
    size_t hash1(const string& str) const {
        size_t hash = 5381;
        for (char c : str) {
            hash = ((hash << 5) + hash) + c;
        }
        return hash % tamanho;
    }

    // 2. Hash SDBM
    size_t hash2(const string& str) const {
        size_t hash = 0;
        for (char c : str) {
            hash = c + (hash << 6) + (hash << 16) - hash;
        }
        return hash % tamanho;
    }

    // 3. Hash FNV-1a
    size_t hash3(const string& str) const {
        size_t hash = 2166136261U;
        for (char c : str) {
            hash ^= c;
            hash *= 16777619;
        }
        return hash % tamanho;
    }

public:
    // Construtor: inicializa o vetor com zeros (false)
    BloomFilter(size_t tam = 50000) : tamanho(tam) {
        tabela.assign(tamanho, false);
    }

    // Ativa os 3 bits correspondentes à chave
    void inserir(const string& chave) {
        tabela[hash1(chave)] = true;
        tabela[hash2(chave)] = true;
        tabela[hash3(chave)] = true;
    }

    // Checa se os 3 bits estão ativos
    bool contem(const string& chave) const {
        return tabela[hash1(chave)] &&
               tabela[hash2(chave)] &&
               tabela[hash3(chave)];
    }
};

#endif
