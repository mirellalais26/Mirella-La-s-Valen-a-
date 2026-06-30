%%writefile SkipList.h
#ifndef SKIPLIST_H
#define SKIPLIST_H

#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

using namespace std;

struct SkipNode {
    string chave;
    double demanda_residual;
    vector<SkipNode*> forward;
    SkipNode(string k, double v, int level) : chave(k), demanda_residual(v), forward(level, nullptr) {}
};

class SkipList {
    int max_level;
    float p;
    int level;
    SkipNode* header;

public:
    SkipList(int max_lvl = 16, float prob = 0.5) {
        max_level = max_lvl;
        p = prob;
        level = 0;
        header = new SkipNode("", 0, max_level);
    }

    ~SkipList() {
        SkipNode* current = header->forward[0];
        while(current != nullptr) {
            SkipNode* next = current->forward[0];
            delete current;
            current = next;
        }
        delete header;
    }

    int randomLevel() {
        float r = (float)rand() / RAND_MAX;
        int lvl = 0;
        while (r < p && lvl < max_level - 1) {
            lvl++;
            r = (float)rand() / RAND_MAX;
        }
        return lvl;
    }

    // 1. INSERÇÃO O(log N)
    void inserir(string chave, double valor) {
        vector<SkipNode*> update(max_level, nullptr);
        SkipNode* current = header;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->chave < chave) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];

        if (current == nullptr || current->chave != chave) {
            int rlevel = randomLevel();
            if (rlevel > level) {
                for (int i = level + 1; i <= rlevel; i++) {
                    update[i] = header;
                }
                level = rlevel;
            }
            SkipNode* n = new SkipNode(chave, valor, rlevel + 1);
            for (int i = 0; i <= rlevel; i++) {
                n->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = n;
            }
        }
    }

    // 2. BUSCA O(log N)
    SkipNode* buscar(string chave) {
        SkipNode* current = header;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->chave < chave) {
                current = current->forward[i];
            }
        }
        current = current->forward[0];
        if (current != nullptr && current->chave == chave) {
            return current;
        }
        return nullptr; // Não encontrou
    }

    // 3. REMOÇÃO O(log N)
    bool remover(string chave) {
        vector<SkipNode*> update(max_level, nullptr);
        SkipNode* current = header;
        for (int i = level; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->chave < chave) {
                current = current->forward[i];
            }
            update[i] = current;
        }
        current = current->forward[0];

        if (current != nullptr && current->chave == chave) {
            for (int i = 0; i <= level; i++) {
                if (update[i]->forward[i] != current) break;
                update[i]->forward[i] = current->forward[i];
            }
            delete current;
            while (level > 0 && header->forward[level] == nullptr) {
                level--;
            }
            return true; // Removido com sucesso
        }
        return false; // Elemento não existia
    }
};
#endif
