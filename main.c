#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Cabeçalho dicotomia  --------------------
void dicotomia();
float funcaoX(float ponto, int grau, float multi[]);
float calculaValorK(float a, float b, float erro, int grau, float multi[]);
void imprimirCabecalhoTabela();
void imprimirTabela(int iteracao, float a, float b, float m, float fA, float fB, float fM, char fAfM, char fMfB);
char sinal(float f1, float f2);
// -----------------------------------------

// Cabeçalho lagrange  ---------------------
void lagrange();
void aloca_x(float **p, int qtde);
void aloca_fx(float **px, int qtde);
// -----------------------------------------

int main()
{
  int op = 3;
  printf("\n\tBem-vindo!\n\tEscolha a opcao desejada:\n\n\t[1] Metodo da Dicotomia\n\t[2] Polinomios de Lagrange\n");
  scanf("%i", &op);
  while(op)
    {
      switch (op)
      {
          case 1:
              dicotomia();
              op = 0;
          break;

          case 2:
              lagrange();
              op = 0;
          break;
  
          default:
              printf("\nOpcao invalida! Tente novamente.");
              system("pause");
    }
  }
  return 0;
}

// Funções Dicotomia
void dicotomia()
{
    int i, grau = 0;
    float a, b, erro;

    while(grau > 6 || grau < 2)
    {
        printf("\nInforme o grau da funcao (2 a 6): ");
        scanf("%i", &grau);
      
        if (grau < 2 || grau > 6) 
            printf("Grau invalido!\n");
    }
    
    float *multi = malloc((grau+1) * sizeof(float)); //alocando dinamicamente
    
    for(i=grau; i>=0; i--)
    {
        printf("Informe o fator multiplicador de x^%i: ", i);
        scanf("%f", &multi[i]);
    }
    
    printf("A funcao recebida foi: ");
    
    for(i=grau; i>=0; i--)
    {
        if(i==0)
            printf("%.2f = 0", multi[i], i);
        else
            printf("%.2fx^%i + ", multi[i], i);
    }
    
    printf("\n\n");
    system("pause");
    printf("\n\n");
    printf("Resultado: %f %f %f\n", funcaoX(0, grau, multi), funcaoX(1, grau, multi), funcaoX(2, grau, multi));
    system("pause");

    while(1)
    {
        printf("Digite o valor de a: ");
        scanf("%f", &a);
        printf("Digite o valor de b: ");
        scanf("%f", &b);
        if(funcaoX(a, grau, multi)*funcaoX(b, grau, multi)<0)
            break;
        else
            printf("\n\nErro! Nao ha 0 de funcao no intervalo (%.2f, %.2f) (%.2f, %.2f).\n\n", a, funcaoX(a, grau, multi), b, funcaoX(b, grau, multi));
    }

    printf("Digite o valor do erro: ");
    scanf("%f", &erro);

    printf("Valor de K = %.2f\nNumero de iteracoes: %i\n\n", calculaValorK(a, b, erro, grau, multi), (int)ceil(calculaValorK(a, b, erro, grau, multi)));

    imprimirCabecalhoTabela();
    int it = (int)ceil(calculaValorK(a, b, erro, grau, multi));

    for(i=1;i<=it; i++)
    {
        float m = b-(b-a)/2;
        imprimirTabela(i, a, b, m, funcaoX(a, grau, multi), funcaoX(b, grau, multi), funcaoX(m, grau, multi), sinal(funcaoX(a, grau, multi),funcaoX(m, grau, multi)), sinal(funcaoX(m, grau, multi),funcaoX(b, grau, multi)));
        
        if(funcaoX(a, grau, multi)*funcaoX(m, grau, multi)>0)
        {
            a = m;
            m = (a + b) / 2;
        }
        else
        {
            b = m;
            m = (a + b) / 2;
        }
        if(i==it)
            printf("\nResultado final m = %lf", m);
    }
    system("pause");
}

float calculaValorK(float a, float b, float erro, int grau, float multi[])
{
    float fValorK;
    fValorK = (log10(b - a) - log10(erro)) / (log10(2));
    return fValorK;
}

float funcaoX(float ponto, int grau, float multi[])
{
    int i;
    float resultado = 0;
    for(i = 0; i <= grau; i++)
    {
        resultado += multi[i] * pow(ponto, i);
    }
    return resultado;
}

void imprimirCabecalhoTabela()
{
    printf(" I \t| a\t| b\t| m\t| f(a)\t| f(b)\t| f(m)\t| fafm\t| fmfb\t|\n");
    printf(" -------+-------+-------+-------+-------+-------+-------+-------+-------+\n");
}

void imprimirTabela(int iteracao, float a, float b, float m, float fA, float fB,
                     float fM, char fAfM, char fMfB)
{
    printf("%i \t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%.2f\t|%c\t|%c\t|\n", iteracao,
           a, b, m, fA, fB, fM, fAfM, fMfB);
}

char sinal(float f1, float f2)
{
    if(f1 * f2 > 0)
        return '+';
    else
        return '-';
}

//Funções Lagrange
void lagrange()
{
    int pontos, grau, cont, i, j, qtde;
    float Px, valorCalcular, Li;
    char resp;

    //Usando MATRIZES
    float matriz[2][10]; //Linha 0: valores de X, Linha 1: valores de f(x)
    //Usando Vetores
    float *valoresX = NULL;
    float *valoresFX = NULL;
    
    printf("Digite o grau da funcao que deseja obter: ");
    scanf("%i", &grau);
    
    //Obtendo o numero de pontos a partir do grau indicado
    pontos = grau + 1;
    
    //Alocacao do tamanho solicitado
    aloca_x(&valoresX, pontos);
    aloca_fx(&valoresFX, pontos);

    for (cont = 0; cont < pontos; cont++)
    {
        //recebendo valores
        printf("Digite o valor de F(x) correspondente a X = %f:\n", *(valoresX + cont));
        scanf("%f", valoresFX + cont);
    }

    do
    {
        printf("Digite o valor que deseja calcular: ");
        scanf("%f", &valorCalcular);

        Px = 0;
        //Implementar o calculo do Teorema de Lagrange
        for (i = 0; i < pontos; i++)
        {
            Li = 1;
            for (j = 0; j < pontos; j++)
            {
                if (j != i)
                {
                    Li *= (valorCalcular - *(valoresX + j)) / (*(valoresX + i) - *(valoresX + j));
                }
            }
            Px += Li * (*(valoresFX + i));
        }

        printf("Resultado: %f\n", Px);

        fflush(stdin);
        printf("Deseja calcular outro valor (s/n)? ");
        scanf(" %c", &resp);
    } while (resp == 's' || resp == 'S');

    //Liberando a memoria
    free(valoresX);
    free(valoresFX);

    system("pause");
}

void aloca_x(float **p, int qtde)
{
    printf("Digite os %d valores de x:\n", qtde);
    *p = (float *)malloc(qtde * sizeof(float));
    for (int i = 0; i < qtde; i++)
    {
        scanf("%f", *p + i);
    }
}
void aloca_fx(float **px, int qtde)
{
    *px = (float *)malloc(qtde * sizeof(float));
}
