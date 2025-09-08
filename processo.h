#ifndef PROCESSO_H
#define PROCESSO_H

#include <stdbool.h>

typedef struct {
    char *id_processo; 
    long long numero_sigilo;
    char sigla_grau[3]; 
    char procedimento[50]; 
    char ramo_justica[20];
    char sigla_tribunal[10];
    int id_tribunal;
    char recurso[20];
    char *id_ultimo_oj;
    char dt_recebimento[11]; 
    int id_ultima_classe;

    bool flag_violencia_domestica;
    bool flag_feminicidio;
    bool flag_ambiental;
    bool flag_quilombolas;
    bool flag_indigenas;
    bool flag_infancia;

    char decisao[100];
    char dt_resolvido[11]; 

    int cnm1;
    int primeirasentm1;
    int baixm1;
    int decm1;
    int mpum1;
    int julgadom1;
    int desm1;
    int susm1;

} Processo;



Processo* criar_processo_de_linha(char* linha_csv);

void liberar_processo(Processo* p);

#endif 