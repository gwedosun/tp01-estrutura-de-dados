#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

#include "processo.h"

Processo* criar_processo_de_linha(char* linha_csv){
    Processo* p = (Processo*)malloc(sizeof(Processo));
    if(p == NULL){
        fprintf(stderr, "Erro: falha de alocacao de memoria para processo.\n");
        return NULL;
    }

    char* linha_copia = strdup(linha_csv);
    if(linha_copia == NULL){
        fprintf(stderr, "Erro: falha de alocacao de memoria para linha.\n");
        free(p);
        return NULL;
    }

    char* token;

    token = strtok(linha_copia, ";");
    if(token) p->id_processo = strdup(token); else p->id_processo = NULL;

    token = strtok(NULL, ";");
    if(token) p->numero_sigilo = atoll(token);

    token = strtok(NULL, ";");
    if(token) strncpy(p->sigla_grau, token, sizeof(p->sigla_grau) - 1);
    p->sigla_grau[sizeof(p->sigla_grau) - 1] = '\0';

    token = strtok(NULL, ";");
    if(token) strncpy(p->procedimento, token, sizeof(p->procedimento) - 1);
    p->procedimento[sizeof(p->procedimento) - 1] = '\0';

    token = strtok(NULL, ";");
    if(token) strncpy(p->ramo_justica, token, sizeof(p->ramo_justica) - 1);
    p->ramo_justica[sizeof(p->ramo_justica) - 1] = '\0';

    token = strtok(NULL, ";");
    if(token) strncpy(p->sigla_tribunal, token, sizeof(p->sigla_tribunal) - 1);
    p->sigla_tribunal[sizeof(p->sigla_tribunal) - 1] = '\0';

    token = strtok(NULL, ";");
    if(token) p->id_tribunal = atoi(token);

    token = strtok(NULL, ";");
    if(token) strncpy(p->recurso, token, sizeof(p->recurso) - 1);
    p->recurso[sizeof(p->recurso) - 1] = '\0';

    token = strtok(NULL, ";");
    if(token) p->id_ultimo_oj = strdup(token); else p->id_ultimo_oj = NULL;

    token = strtok(NULL, ";");
    if(token) strncpy(p->dt_recebimento, token, sizeof(p->dt_recebimento) - 1);
    p->dt_recebimento[sizeof(p->dt_recebimento) - 1] = '\0';

    token = strtok(NULL, ";");
    if(token) p->id_ultima_classe = atoi(token);

    token = strtok(NULL, ";");
    if(token) p->flag_violencia_domestica = (atoi(token) == 1);

    token = strtok(NULL, ";");
    if(token) p->flag_feminicidio = (atoi(token) == 1);

    token = strtok(NULL, ";");
    if(token) p->flag_ambiental = (atoi(token) == 1);

    token = strtok(NULL, ";");
    if(token) p->flag_quilombolas = (atoi(token) == 1);

    token = strtok(NULL, ";");
    if(token) p->flag_indigenas = (atoi(token) == 1);

    token = strtok(NULL, ";");
    if(token) p->flag_infancia = (atoi(token) == 1);

    token = strtok(NULL, ";");
    if(token) strncpy(p->decisao, token, sizeof(p->decisao) - 1);
    p->decisao[sizeof(p->decisao) - 1] = '\0';
    
    token = strtok(NULL, ";");
    if(token) strncpy(p->dt_resolvido, token, sizeof(p->dt_resolvido) - 1);
    p->dt_resolvido[sizeof(p->dt_resolvido) - 1] = '\0';

    token = strtok(NULL, ";");
    if(token) p->cnm1 = atoi(token);

    token = strtok(NULL, ";");
    if(token) p->primeirasentm1 = atoi(token);

    token = strtok(NULL, ";");
    if(token) p->baixm1 = atoi(token);

    token = strtok(NULL, ";");
    if(token) p->decm1 = atoi(token);

    token = strtok(NULL, ";");
    if(token) p->mpum1 = atoi(token);

    token = strtok(NULL, ";");
    if(token) p->julgadom1 = atoi(token);

    token = strtok(NULL, ";");
    if(token) p->desm1 = atoi(token);

    token = strtok(NULL, ";");
    if(token) p->susm1 = atoi(token);

    free(linha_copia);
    return p;
}

void liberar_processo(Processo* p){
    if(p){
        free(p->id_processo);
        free(p->id_ultimo_oj);
        free(p);
    }
}