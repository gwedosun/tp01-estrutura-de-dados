#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdbool.h>

#include "processo.h"

int contar_numero_processos(int tamanho){
    return tamanho;   
}

char* encontrar_processo_mais_antigo(Processo** processos, int tamanho) {
    if (tamanho == 0) {
        return NULL;
    }
    Processo* mais_antigo = processos[0];
    for (int i = 1; i < tamanho; i++) {
        if (processos[i] != NULL && strcmp(processos[i]->dt_recebimento, mais_antigo->dt_recebimento) < 0) {
            mais_antigo = processos[i];
        }
    }
    return strdup(mais_antigo->id_processo);
}

int contar_violencia_domestica(Processo** processos, int tamanho){
    int contador = 0;
    for(int i = 0; i < tamanho; i++){
        if(processos[i] != NULL && processos[i]->flag_violencia_domestica){
            contador++;
        }
    }
    return contador;
}

int contar_feminicidio(Processo** processos, int tamanho){
    int contador = 0;
    for(int i = 0; i < tamanho; i++){
        if(processos[i] != NULL && processos[i]->flag_feminicidio){
            contador++;
        }
    }
    return contador;
}

int contar_ambiental(Processo ** processos, int tamanho){
    int contador = 0;
    for(int i = 0; i < tamanho; i++){
        if(processos[i] != NULL && processos[i]->flag_ambiental){
            contador++;
        }
    }
    return contador;
}

int contar_quilombolas(Processo ** processos, int tamanho){
    int contador = 0;
    for(int i = 0; i < tamanho; i++){
        if(processos[i] != NULL && processos[i]->flag_quilombolas){
            contador++;
        }
    }
    return contador;
}

int contar_indigenas(Processo ** processos, int tamanho){
    int contador = 0;
    for(int i = 0; i < tamanho; i++){
        if(processos[i] != NULL && processos[i]->flag_indigenas){
            contador++;
        }
    }
    return contador;
}

int contar_infancia(Processo ** processos, int tamanho){
    int contador = 0;
    for(int i = 0; i < tamanho; i++){
        if(processos[i] != NULL && processos[i]->flag_infancia){
            contador++;
        }
    }
    return contador;
}

long long calcular_dias(Processo* p) {
    if (strcmp(p->dt_resolvido, "0") == 0) {
        return -1;
    }

    struct tm recebimento_tm, resolvido_tm;
    memset(&recebimento_tm, 0, sizeof(struct tm));
    memset(&resolvido_tm, 0, sizeof(struct tm));

    sscanf(p->dt_recebimento, "%d-%d-%d", &recebimento_tm.tm_year, &recebimento_tm.tm_mon, &recebimento_tm.tm_mday);
    sscanf(p->dt_resolvido, "%d-%d-%d", &resolvido_tm.tm_year, &resolvido_tm.tm_mon, &resolvido_tm.tm_mday);

    recebimento_tm.tm_year -= 1900;
    recebimento_tm.tm_mon--;
    resolvido_tm.tm_year -= 1900;
    resolvido_tm.tm_mon--;

    time_t recebimento_sec = mktime(&recebimento_tm);
    time_t resolvido_sec = mktime(&resolvido_tm);

    return difftime(resolvido_sec, recebimento_sec) / (60 * 60 * 24);
}

// 11. O percentual de cumprimento da meta 1
float calcular_cumprimento_meta1(int julgadom1, int cnm1, int desm1, int susm1) {
    if ((cnm1 + desm1 - susm1) == 0) {
        return 0.0;
    }
    return ((float)julgadom1 / (cnm1 + desm1 - susm1)) * 100.0;
}

// 12. Gerar um arquivo CSV com todos os processos julgados (mérito) na Meta 1
void gerar_csv_julgados_meta1(Processo** processos, int tamanho) {
    FILE* arq_saida = fopen("processos_julgados_meta1.csv", "w");
    if (arq_saida == NULL) {
        fprintf(stderr, "Erro ao criar o arquivo de saida.\n");
        return;
    }

    fprintf(arq_saida, "id_processo;numero_sigilo;procedimento;julgadom1\n");

    for (int i = 0; i < tamanho; i++) {
        if (processos[i] != NULL && processos[i]->julgadom1 > 0) {
            fprintf(arq_saida, "%s;%lld;%s;%d\n",
                    processos[i]->id_processo,
                    processos[i]->numero_sigilo,
                    processos[i]->procedimento,
                    processos[i]->julgadom1);
        }
    }

    fclose(arq_saida);
    printf("Arquivo 'processos_julgados_meta1.csv' gerado com sucesso!\n");

}

int main() {
    FILE* arquivo = fopen("TJDFT_filtrado.csv", "r");
    if (arquivo == NULL) {
        fprintf(stderr, "Erro: Nao foi possivel abrir o arquivo 'TJDFT_filtrado.csv'.\n");
        return 1;
    }

    int total_processos = 0;
    char linha[1024];

    fgets(linha, sizeof(linha), arquivo);
    while (fgets(linha, sizeof(linha), arquivo) != NULL) {
        total_processos++;
    }

    rewind(arquivo);
    fgets(linha, sizeof(linha), arquivo);

    Processo** processos = (Processo**)calloc(total_processos, sizeof(Processo*));
    if (processos == NULL) {
        fprintf(stderr, "Erro de alocacao de memoria para vetor de processos.\n");
        fclose(arquivo);
        return 1;
    }

    int i = 0;
    while (fgets(linha, sizeof(linha), arquivo) != NULL && i < total_processos) {
        linha[strcspn(linha, "\n")] = '\0';
        Processo* novo_processo = criar_processo_de_linha(linha);
        if (novo_processo != NULL) {
            processos[i] = novo_processo;
            i++;
        }
    }
    fclose(arquivo);

    printf("Total de processos carregados: %d\n", total_processos);

    printf("1. Total de processos na base de dados: %d\n", contar_numero_processos(total_processos));
    
    char* id_mais_antigo = encontrar_processo_mais_antigo(processos, total_processos);
    if (id_mais_antigo != NULL) {
        printf("3. ID do processo mais antigo: %s\n", id_mais_antigo);
        free(id_mais_antigo);
    } else {
        printf("3. Nenhum processo encontrado.\n");
    }

    printf("4. Processos com flag de violencia domestica: %d\n", contar_violencia_domestica(processos, total_processos));
    printf("5. Processos com flag de feminicidio: %d\n", contar_feminicidio(processos, total_processos));
    printf("6. Processos com flag ambiental: %d\n", contar_ambiental(processos, total_processos));
    printf("7. Processos com flag quilombolas: %d\n", contar_quilombolas(processos, total_processos));
    printf("8. Processos com flag indigenas: %d\n", contar_indigenas(processos, total_processos));
    printf("9. Processos com flag infancia: %d\n", contar_infancia(processos, total_processos));

 if (total_processos > 0) {
        long long dias = calcular_dias(processos[0]);
        if (dias != -1) {
            printf("10. Dias entre recebimento e resolucao do primeiro processo: %lld dias\n", dias);
        } else {
            printf("10. O primeiro processo ainda nao foi resolvido.\n");
        }
    }

    float percentual_total_meta1 = 0;
    int cnm1_total = 0, desm1_total = 0, susm1_total = 0, julgadom1_total = 0;
    for (int i = 0; i < total_processos; i++) {
        cnm1_total += processos[i]->cnm1;
        desm1_total += processos[i]->desm1;
        susm1_total += processos[i]->susm1;
        julgadom1_total += processos[i]->julgadom1;
    }
    percentual_total_meta1 = calcular_cumprimento_meta1(julgadom1_total, cnm1_total, desm1_total, susm1_total);
    printf("11. Percentual de cumprimento da Meta 1: %.2f%%\n", percentual_total_meta1);

    gerar_csv_julgados_meta1(processos, total_processos);


// limpa tudo
    for (int j = 0; j < total_processos; j++) {
        liberar_processo(processos[j]);
    }
    free(processos);

    return 0;
}
