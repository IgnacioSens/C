#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#define TAM 15

typedef struct quarto{
int num; // número do quarto
char categoria; // [S]olteiro / [F]amiliar
char status; // [L]ivre / [O]cupado
}quarto;

typedef struct hospede{
int quarto; // número do quarto
char nome[80];
int acompanhante; // quantidade de acompanhantes
char categoria; // [S]olteiro / [F]amiliar
int dias; // tempo de permanência – em dias
}hospede;

void alocaQuarto(quarto **q,int cont);
void alocaHospede(hospede **h,int cont);
void separacao();
int cadastro(quarto *q,hospede *h,int cont);
void alocarQuartoParametros(quarto *q);
int buscar(quarto *q,char cat);
void mostra(quarto *q,hospede *h, int tam);

main()
{
	quarto lista[TAM];
	hospede pessoa[100];
	quarto *q=NULL;
	hospede *h=NULL;
	char saida;
	int opcao;
	int cont=0;
	alocaQuarto(&q,15);
	alocarQuartoParametros(q);
	alocaHospede(&h,100);
	do{
		system("cls");
		separacao();
		printf("Menu\nDigite a opcao:\n1)Check-in\n2)Check-out\n3)Fim\n4)Funcao Mostra\nSua escolha:");
		scanf("%i",&opcao);
		fflush(stdin);
		switch (opcao)
		{
			case 1:
				(h+cont)->dias=0;
			cont=cadastro(q,h,cont);
			break;
			case 4:
			mostra(q,h,15);
			break;	
		}
		scanf("%c",&saida);
	}while(saida != 'N' && saida != 'n');
	printf("encerrou");
	return 0;
}

void alocaQuarto(quarto **q,int cont)
{
	if((*q=(quarto*)realloc(*q,cont*sizeof(quarto)))==NULL)
	{
		printf("Erro");
		exit(1);
	}
}
void alocaHospede(hospede **h,int cont)
{
	if((*h=(hospede*)realloc(*h,cont*sizeof(hospede)))==NULL)
	{
		printf("Erro de memoria");
		exit(1);
	}
}

void separacao()
{
	printf("\n-------------------------------------------------------------------------------------------------------\n");
}

int cadastro(quarto *q,hospede *h,int x)
{
	int cont=16;
	int y=x;
	char cadastroTemp,escolha;
	int qtdAcom,qtdDias;
	printf("\nDigite sua categoria Solteiro ou Familiar <S/F>:");
	scanf("%c",&cadastroTemp);
	fflush(stdin);
	cont=buscar(q,cadastroTemp);
	if(cont != 16)
	{
		printf("\nquarto encontrado em %i",cont);
	}
	if(cont==16)
	{
		printf("\nQuarto indisponivel");
		return y;
	}
	if(cadastroTemp=='F' ||cadastroTemp=='f')
	{
		printf("\nDigite a quantidade de acompanhantes:");
		scanf("%i",&qtdAcom);
		fflush(stdin);
	}
	printf("\nDigite a quantidade de dias:");
		scanf("%i",&qtdDias);
	fflush(stdin);
	printf("\nDeseja cancelar o cadastro? <S/N>");
	scanf("%c",&escolha);
	if(escolha=='s' || escolha=='S')
	{
		printf("\nCadastro cancelado");
		return 0;
	}
	(h+x)->acompanhante = qtdAcom;
	(h+x)->dias = qtdDias;
	(h+x)->categoria = cadastroTemp;
	(h+x)->categoria = toupper((h+x)->categoria);
	if(cadastroTemp=='F' ||cadastroTemp=='f')
	{
		(q+cont-1)->status='O';
	printf("\nCadastro realizado com sucesso, quarto %i,tipo %c, status %c, %i acompanhantes e %i dias",(q+x)->num,(h+x)->categoria,(q+x)->status,(h+x)->acompanhante,(h+x)->dias);
	return cont;
	}
	(q+x)->status='O';
	printf("\nCadastro realizado com sucesso, quarto %i,tipo %c, status %c e %i dias",(q+x)->num,(h+x)->categoria,(q+x)->status,(h+x)->dias);
	return cont;
}
void alocarQuartoParametros(quarto *q)
{
	int x,y;
	for(x=0;x<5;x++)
	{
		(q+x)->categoria='S';
	}
	for(x=5;x<15;x++)
	{
		(q+x)->categoria='F';
	}
	for(y=0;y<15;y++)
	{
		(q+y)->num=y+1;
	}
	for(y=0;y<15;y++)
	{
		(q+y)->status='L';
	}
}
int buscar(quarto *q, char cat)
{
	int x=16,y;
	cat=toupper(cat);
	for(y=0;y<15;y++)
	
	{
		if((q+y)->categoria==cat)
		{
			if((q+y)->status=='L')
			{
				x=(q+y)->num;
				return x;
			}
		}
	}
	return 16;
}
void mostra(quarto *q,hospede *h, int tam)
{
	int i;
	for(i=0;i<tam;i++)
	printf("\nvetor %i=%i,%c,%c,%i",i+1,(q+i)->num,(q+i)->categoria,(q+i)->status,(h+i)->acompanhante);
}
