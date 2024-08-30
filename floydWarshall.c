/****************************
 *          ALUNOS          *
 *                          * 
 *   Caio Bohlhalter        *
 *   Eduarda Moreira        *
 *   Beatriz Cavalheri      *
 *   Jerferson Dietrich     *
 *   Larissa Ferrari        *
 *   Maysa Marques          *
 *                          *
 ***************************/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define INFINITO INT_MAX

// Função para implementar o algoritmo de Floyd-Warshall
void floydWarshall(int **grafo, int n, int **distancias) {
    // Inicializa a matriz de distâncias com a matriz de adjacência
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j) {
                distancias[i][j] = 0;
            } else if (grafo[i][j] != 0) {
                distancias[i][j] = grafo[i][j];
            } else {
                distancias[i][j] = INFINITO;
            }
        }
    }

    // Executa o algoritmo de Floyd-Warshall
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (distancias[i][k] != INFINITO && distancias[k][j] != INFINITO &&
                    distancias[i][j] > distancias[i][k] + distancias[k][j]) {
                    distancias[i][j] = distancias[i][k] + distancias[k][j];
                }
            }
        }
    }
}

// Função para carregar o grafo de um arquivo
int** carregarGrafo(const char *nomeArquivo, int *n) {
    FILE *arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    // Contar o número de linhas e colunas no arquivo
    int linhas = 0;
    int colunas = 0;
    char ch;

    while ((ch = fgetc(arquivo)) != EOF) {
        if (ch == '\n') {
            linhas++;
        }
    }
    if (ch == '\0' && ftell(arquivo) != 0) {
        linhas++; // Contar a última linha se o arquivo não terminar com uma nova linha
    }
    rewind(arquivo);

    // Alocar memória para a matriz de adjacência
    int **grafo = (int **)malloc(linhas * sizeof(int *));
    for (int i = 0; i < linhas; i++) {
        grafo[i] = (int *)malloc(linhas * sizeof(int));
    }

    // Ler a matriz de adjacência
    *n = linhas;
    for (int i = 0; i < linhas; i++) {
        for (int j = 0; j < linhas; j++) {
            if (fscanf(arquivo, "%d", &grafo[i][j]) != 1) {
                printf("Erro ao ler o arquivo!\n");
                fclose(arquivo);
                exit(1);
            }
        }
    }

    fclose(arquivo);
    return grafo;
}

// Função para imprimir a matriz de distâncias
void imprimirMatriz(int **matriz, int n) {
    printf("Matriz de distâncias:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matriz[i][j] == INFINITO) {
                printf("INF ");
            } else {
                printf("%3d ", matriz[i][j]);
            }
        }
        printf("\n");
    }
}

int main() {
    int **grafo;
    int **distancias;
    int n;

    // Como o código foi feito pensando em reutilizar o grafo gerado no exercício anterior, fizemos essa leitura de arquivo para implementação do algoritmo
    printf("Digite o nome do arquivo com a matriz adjacência do grafo: ");
    char nomeArquivo[100];
    scanf("%s", nomeArquivo);
    grafo = carregarGrafo(nomeArquivo, &n);

    // Aloca memória para a matriz de distâncias
    distancias = (int **)malloc(n * sizeof(int *));
    for (int i = 0; i < n; i++) {
        distancias[i] = (int *)malloc(n * sizeof(int));
    }

    // Exibir o grafo carregado
    printf("Grafo carregado:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", grafo[i][j]);
        }
        printf("\n");
    }

    floydWarshall(grafo, n, distancias);
    imprimirMatriz(distancias, n);

    for (int i = 0; i < n; i++) {
        free(grafo[i]);
        free(distancias[i]);
    }
    free(grafo);
    free(distancias);

    return 0;
}
