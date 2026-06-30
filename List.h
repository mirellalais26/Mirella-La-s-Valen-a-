%%writefile List.h
#ifndef LISTA_ENCADEADA_H
#define LISTA_ENCADEADA_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define EPSILON_list 1e-9

typedef struct EletricDates {
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
} EletricDates;

typedef struct {
    EletricDates *dados;
    size_t qtd;
    size_t capacidade;
} VetorEletricDates;

typedef struct {
    double media;
    double variancia;
    double desvio_padrao;
} EstatisticasSimplesList;

typedef struct {
    EstatisticasSimplesList demanda_residual;
    EstatisticasSimplesList demanda_contratada;
    EstatisticasSimplesList geracao_despachavel;
    EstatisticasSimplesList geracao_renovavel_total;
    EstatisticasSimplesList carga_reduzida_manual;
    EstatisticasSimplesList capacidade_instalada;
    EstatisticasSimplesList perdas_geracao_total;
    EstatisticasSimplesList geracao_termica;
    EstatisticasSimplesList importacoes;
} EstatisticasCamposList;

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
} MedianasList;

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
} ModasList;

typedef struct NodeList {
    EletricDates dado;
    struct NodeList* next;
} NodeList;

extern NodeList *lista_ligada;

int in(NodeList** head, EletricDates *dado);
NodeList* buscar_lista(NodeList* head, const char* data_str);  // <-- Nova função de busca
int remover_lista(NodeList** head, const char* data_str);      // <-- Nova função de remoção
long long datetime_para_inteiro_list(const char *datetime);
void vetor_inicializarList (VetorEletricDates *v, size_t capacidade_inicial);
void vetor_adicionarList (VetorEletricDates *v, EletricDates reg);
void vetor_liberarList (VetorEletricDates *v);
void buscar_intervalo_list(const char *inicio_str, const char *fim_str, char **saida, VetorEletricDates *vetor);
void imprimir_lista(NodeList* no);
void liberar_lista(NodeList** head);
EstatisticasCamposList calcular_estatisticasList(VetorEletricDates *v);
int comparador_double_list(const void *a, const void *b);
MedianasList calcular_mediana_list(VetorEletricDates *v);
ModasList calcular_moda_list(VetorEletricDates *v);
char* estatisticas_para_json_conteudo_list(EstatisticasCamposList est, MedianasList med, ModasList moda);

#endif
