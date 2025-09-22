# tp01-estrutura-de-dados
Atividade avaliativa sugerida pelo Professor Marcelo Eustáquio como composição da nota da disciplina Estrutura de Dados, 2025.2, do curso de Bacharelado em Ciência da Computação da Universidade Católica de Brasília.

Alunos: Beatriz Evangelista, Gabriella Braga e Keven Régio.

Descrição do problema:
A partir de uma base de dados de processos existentes no Tribunal de Justiça do Distrito Federal e Territórios, construir um código-fonte capaz de determinar:
1. o número de processos presentes na base de dados;
2. o id_ultimo_oj a partir de id_processo;
3. o id_processo do processo com dt_recebimento mais antigo;
4. quantos processos estão relacionadas a causas de violência doméstica;
5. quantos processos estão relacionadas a causas de feminicídio;
6. quantos processos estão relacionadas a causas ambientais;
7. quantos processos estão relacionadas a causas de quilombolas;
8. quantos processos estão relacionadas a causas indígenas;
9. quantos processos envolve causas relacionadas a infância e juventude;
10. o número de dias entre dt_recebimento e dt_resolvido;
11. o percentual de cumprimento da meta 1; e
12. gerar um arquivo CSV com todos os processos julgados (mérito) na Meta 1;

Seguindo as observações de implementação:
- Implementar e utilizar o Tipo Abstrato de Dados (TAD);
- Código-fonte estruturado em três arquivos;
- Implementar uma função para resolução de cada item;

# O programa
Desenvolvido para analisar e processar dados de processos judiciais, é estruturado em um Tipo Abstrato de Dados chamado Processo, dividido em três arquivos principais (processo.h, processo.c e main.c), a serem detalhados abaixo:

## processo.h
O arquivo processo.h define a estrutura do TAD Processo e declara as funções que serão usadas para manipular os dados dos processos.

Inclui-se a biblioteca <stdbool.h> para melhor manipulação dos dados que, segundo a documentação cedida, são definidos em TRUE ou FALSE (booleanos).

A struct Processo armazena identificadores (id_processo, id_tribunal), informações textuais (sigla_grau, procedimentos), datas (dt_recebimento, dt_resolvido) e flags temáticas (flag_ambiental, flag_indigenas). Os identificadores id_processo e id_ultimo_oj são definidos como char* e têm memória alocada dinamicamente, visto que podem conter valores grandes e/ou alfanuméricos.
As flags temáticas são do tipo booleano.

A Meta 1 é representada pelos campos cnm1, primeirasentm1, baixm1, decm1, mpum1, julgadom1, desm1, susm1.

## processo.c
A primeira função, criar_processo_de_linha, aloca memória dinamicamente para o objeto Processo e preenche seus atributos.

Na parte de tokenização, usa-se strtok_s para separar os campos da linha no arquivo .csv a cada ";" encontrado, e preenche a struct com o valor correspondente.

A segunda função, liberar_processo, libera toda a memória alocada pelos ponteiros e libera também a struct em si, prevenindo vazamentos de memória.


## main.c
A função é responsável por destrinchar as funções de processo.h e processo.c e gerenciar a execução do código, guarda os dados do arquivo CSV, utiliza alocação dinâmica de memória para mostrar os resultados chamados pelas funções do código. E possui a função principal que integra todas as funções todas as etapas.

As principais funções são:

    - contar_numeros_processos: retorna o número total de processos carregados;
    
    - encontrar_processo_mais_antigo: identifica o processo com a data de recebimento mais antiga (dt_recebimento);
    
    - contar_violencia_domestica, contar_feminicidio, contar_ambiental, contar_quilombolas, contar_indigenas, contar_infancia: realizam contagens especificas de cada flag;
    
    - calcular_dias: calcula o número de dias entre dt_recebimento e dt_resolvido de um processo (return - 1 caso não esteja resolvido);
    
    - calcular_cumprimento_meta1: calcula o porcentual de cumprimento da META1 com base nos campos relacionados (julgadom1, cnm1, desm1, susm1);
    
    - gerar_csv_julgados_meta1: gera um arquivo processos_julgados_meta1.csv contendo apenas os processos julgados na META1.
    
Função Principal:

Executa em quatro etapas

    1. Leitura do CSV: ignora o cabeçalho e aloca os processos em memória dinâmica usando criar_processo_de_linha;
    
    2. Execução das análises: chama cada função dos requisitos (de 1 a 12) e exibe o resultado após compilado no terminal;
    
    3. Geração de arquivo: cria um novo CSV com os processos julgados na META1;
    
    4. Liberação de memória: libera os processos alocados e encerra a execução do programa.
    
