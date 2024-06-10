#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

typedef struct
{
    int matricula;
    char funcionario[50];
    char data[12];
    char origem[50];
    char destino[50];
    int distancia;
    float preco;
    float total;
} Viagem;

Viagem viagens[50];
int totalViagens = 0, i;

void carregaDados()
{
    FILE *arq;
    char linha[100];
    arq = fopen("viagens.csv", "r");
    if (arq == NULL)
    {
        printf("Erro ao abrir o arquivo\n");
    }
    else
    {
        fgets(linha, 100, arq); // Ignorar a primeira linha
        while (fgets(linha, 100, arq) != NULL)
        {
            viagens[totalViagens].matricula = atoi(strtok(linha, ";"));
            strcpy(viagens[totalViagens].funcionario, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].data, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].origem, strtok(NULL, ";"));
            strcpy(viagens[totalViagens].destino, strtok(NULL, ";"));
            viagens[totalViagens].distancia = atoi(strtok(NULL, ";"));
            viagens[totalViagens].preco = atof(strtok(NULL, ";"));
            totalViagens++;
        }
    }
    fclose(arq);
}

void criarRelatorioMarkdown()
{
    FILE *relatorio;
    relatorio = fopen("RelatorioViagens.md", "w");
    if (relatorio == NULL)
    {
        printf("Erro ao criar o arquivo de relatório\n");
        return;
    }

    fprintf(relatorio, "# Relatório de Viagens ACME\n\n");
    fprintf(relatorio, "| Matrícula | Funcionário | Data      | Origem    | Destino   | Distância | Preço  | Total  |\n");
    fprintf(relatorio, "|-----------|-------------|-----------|-----------|-----------|-----------|--------|--------|\n");
    for (i = 0; i < totalViagens; i++)
    {
        fprintf(relatorio, "| %9d | %-11s | %-9s | %-9s | %-9s | %9d | %.2f | %.2f |\n",
                viagens[i].matricula, viagens[i].funcionario, viagens[i].data,
                viagens[i].origem, viagens[i].destino, viagens[i].distancia,
                viagens[i].preco, viagens[i].total);
    }
    fprintf(relatorio, "\n## Total de Reembolso\n\n");
    float totalGeral = 0;
    for (i = 0; i < totalViagens; i++)
    {
        totalGeral += viagens[i].total;
    }
    fprintf(relatorio, "O total geral de reembolso é R$ %.2f\n", totalGeral);

    fclose(relatorio);

    printf("Relatório de viagens gerado com sucesso: RelatorioViagens.md\n");
}

void calcularReembolso()
{
    for(i=0; i < totalViagens; i++)
    {
        viagens[i].total = (viagens[i].preco * viagens[i].distancia) / 3.0; // Correção no cálculo
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    carregaDados();
    calcularReembolso();
    criarRelatorioMarkdown();
    return 0;
}
