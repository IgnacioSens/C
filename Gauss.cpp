/*
 * Nome: Ignacio Antonio Gama Sens 
 * RA: 247653
 * Nome: Isadora Soares e Silva
 * RA: 247551
 * Nome: Luiz Fernando de Almeida Morais
 * RA: 249625
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct 
{
    float *x;
    float *y;
    int n;
} Pontos;

void lerPontos(Pontos *pontos)
{
    int i;
    printf("Digite a quantidade de pontos da tabela:\n");
    scanf("%d", &(pontos->n));
    pontos->x = (float *)realloc(NULL, pontos->n * sizeof(float));
    pontos->y = (float *)realloc(NULL, pontos->n * sizeof(float));
    if (pontos->x == NULL || pontos->y == NULL) 
    {
        printf("Erro na alocacao de memoria.\n");
        exit(1);
    }
    printf("Digite os pares ordenados (x f(x)) separados por espaco, um ponto por linha:\n");
    for(i = 0; i < pontos->n; i++) 
    {
        printf("Ponto %d: ", i + 1);
        scanf("%f %f", &(pontos->x[i]), &(pontos->y[i]));
    }
}

void imprimirSistema(float **A, float *b, int ordem) 
{
    int i,j;
    printf("Sistema linear:\n");
    for(i = 0; i < ordem; i++) 
    {
        for(j = 0; j < ordem; j++) 
        {
            printf("%10.4f ", A[i][j]);
        }
        printf(" | %10.4f\n", b[i]);
    }
    printf("\n");
}

void montarSistema(const Pontos *pontos, int grau, float ***A, float **b) 
{
    int ordem = grau + 1,i,j,k;
    *A = (float **)realloc(NULL, ordem * sizeof(float *));
    *b = (float *)realloc(NULL, ordem * sizeof(float));
    if (*A == NULL || *b == NULL) 
    {
        printf("Erro na alocacao de memoria do sistema.\n");
        exit(1);
    }
    for(i = 0; i < ordem; i++) 
    {
        (*A)[i] = (float *)realloc(NULL, ordem * sizeof(float));
        if ((*A)[i] == NULL) 
        {
            printf("Erro na alocacao da linha da matriz.\n");
            exit(1);
        }
    }

    for(i = 0; i < ordem; i++) 
    {
        (*b)[i] = 0.0f;
        for(j = 0; j < ordem; j++) 
        {
            (*A)[i][j] = 0.0f;
        }
    }

    for(i = 0; i < ordem; i++) 
    {
        for(j = 0; j < ordem; j++) 
        {
            float soma = 0.0f;
            for(k = 0; k < pontos->n; k++) 
            {
                soma += powf(pontos->x[k], i + j);
            }
            (*A)[i][j] = soma;
        }
    }

    for(i = 0; i < ordem; i++) 
    {
        float soma = 0.0f;
        for(k = 0; k < pontos->n; k++) 
        {
            soma += pontos->y[k] * powf(pontos->x[k], i);
        }
        (*b)[i] = soma;
    }
}

void eliminacaoGauss(float **A, float *b, int ordem) 
{
    int i,j,k;
    for(k = 0; k < ordem - 1; k++) 
    {
        int max = k;
        for (i = k + 1; i < ordem; i++) 
        {
            if (fabsf(A[i][k]) > fabsf(A[max][k]))
                max = i;
        }
        if (max != k)
        {
            float *tempLinha = A[k];
            A[k] = A[max];
            A[max] = tempLinha;
            float tempB = b[k];
            b[k] = b[max];
            b[max] = tempB;
        }

        for(i = k + 1; i < ordem; i++) 
        {
            if (A[k][k] == 0) 
            {
                printf("Erro: pivo zero, sistema nao resolvivel pelo metodo.\n");
                exit(1);
            }
            float fator = A[i][k] / A[k][k];
            for(j = k; j < ordem; j++) 
            {
                A[i][j] -= fator * A[k][j];
            }
            b[i] -= fator * b[k];
        }
    }

    printf("Sistema apos escalonamento:\n");
    imprimirSistema(A, b, ordem);
}

void substituicaoAscendente(float **A, float *b, float *coef, int ordem) 
{
    int i,j;
    for(i = ordem - 1; i >= 0; i--) 
    {
        float soma = b[i];
        for(j = i + 1; j < ordem; j++) 
        {
            soma -= A[i][j] * coef[j];
        }
        if (A[i][i] == 0) 
        {
            printf("Erro: diagonal zero no sistema triangular.\n");
            exit(1);
        }
        coef[i] = soma / A[i][i];
    }
}

void liberarMatriz(float **A, int linhas) 
{
    int i;
    for(i = 0; i < linhas; i++) 
    {
        free(A[i]);
    }
    free(A);
}

void imprimirPolinomio(const float *coef, int grau) 
{
    int i;
    printf("Polinomio ajustado: p(x) = ");
    for(i = 0; i <= grau; i++) 
    {
        printf("%.4f", coef[i]);
        if (i >= 1) printf("x");
        if (i > 1) printf("^%d", i);
        if (i < grau) printf(" + ");
    }
    printf("\n");
}

int main() 
{
    Pontos pontos;
    int grau;
    lerPontos(&pontos);

    do {
        printf("Informe o grau do polinomio para ajuste (1 ou 2): ");
        scanf("%d", &grau);
    } while (grau != 1 && grau != 2);

    float **A = NULL;
    float *b = NULL;
    montarSistema(&pontos, grau, &A, &b);

    printf("Sistema linear original:\n");
    imprimirSistema(A, b, grau + 1);

    eliminacaoGauss(A, b, grau + 1);

    float *coef = (float *)realloc(NULL, (grau + 1) * sizeof(float));
    if (coef == NULL) 
	{
        printf("Erro na alocacao do vetor de coeficientes.\n");
        exit(1);
    }

    substituicaoAscendente(A, b, coef, grau + 1);

    imprimirPolinomio(coef, grau);

    free(pontos.x);
    free(pontos.y);
    free(b);
    free(coef);
    liberarMatriz(A, grau + 1);

    return 0;
}

