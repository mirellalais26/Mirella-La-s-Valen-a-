%%writefile Hash.h
#ifndef HASH_H
#define HASH_H

#include <stddef.h>

#define EPSILON_HT 1e-6

typedef struct {
    char chave[100];
    char data[100];
    double demanda_residual;
    double demanda_contratada;
    double geracao_despachavel;
    double geracao_termica;
    double importacoes;
    double geracao_renovavel_total;
    double carga_reduzida_manual;
    double capacidade_instalada;
    double perdas_geracao_total;
    int ocupado;
} Entrada;

typedef struct {
    Entrada *dados;
    size_t tamanho;
    size_t capacidade;
} VetorEntrada;

typedef struct {
    double media;
    double variancia;
    double desvio_padrao;
} EstatisticaCampo;

typedef struct {
    EstatisticaCampo demanda_residual;
    EstatisticaCampo demanda_contratada;
    EstatisticaCampo geracao_despachavel;
    EstatisticaCampo geracao_renovavel_total;
    EstatisticaCampo carga_reduzida_manual;
    EstatisticaCampo capacidade_instalada;
    EstatisticaCampo perdas_geracao_total;
    EstatisticaCampo geracao_termica;
    EstatisticaCampo importacoes;
} EstatisticasCamposHT;

typedef struct {
    double demanda_residual;
    double demanda_contratada;
    double geracao_despachavel;
    double geracao_renovavel_total;
    double carga_reduzida_manual;
    double capacidade_instalada;
    double perdas_geracao_total;
    double geracao_termica;
    double importacoes;
} MedianasHT;

typedef struct {
    double demanda_residual;
    double demanda_contratada;
    double geracao_despachavel;
    double geracao_renovavel_total;
    double carga_reduzida_manual;
    double capacidade_instalada;
    double perdas_geracao_total;
    double geracao_termica;
    double importacoes;
} ModasHT;

void inicializarHash();
int inserirHash_linear(const Entrada *e);
Entrada* buscarHash_linear(const char *chave);  // <-- Nova operação!
int removerHash_linear(const char *chave);      // <-- Nova operação!
void liberarHashLinear();
void estatisticasHash();

#endif
