#include <stdio.h>
#include <stdlib.h>

#define PERCENTO(a,b) 100*((float)a/(float)b)

typedef enum { REPF, REP, REPN, REC, APR, APRN, REMF, RENF, DEFAULT } Status;
typedef struct
{
	int matricula;
	char nome[80];
	int faltas;
	float notas[3];
	float reposicao;
	Status sitaucao;
}Aluno;
typedef struct
{
	char nome[80];
	int aulas;
	int alunos;
	Aluno *lista;
}Turma;
float calculaMediaAluno (Aluno* registro){
	float soma = 0;
	for (int i = 0; i < 3; ++i)
		soma += registro->notas[i];
	return soma/3.0;
}
float calculaMediaFinalAluno (Aluno* registro){
	float min = 11, soma = 0, menor;
	for (int i = 0; i < 3; ++i)
		soma += registro->notas[i];
	for (int i = 0; i < 3; ++i) // Procura a menor nota
		if (registro->notas[i] < min){
			min = registro->notas[i];
			menor = registro->notas[i];
		}
	soma -= menor;
	soma += registro->reposicao; // substitui a menor nota pela nota da reposição
	return soma/3.0;
}
void atualizaSituacao (Aluno* registro, int totalAulas){
	float media = calculaMediaAluno(registro);
	int notasInvalidas = 0;
	// Verificar se está reprovado por falta
	if (PERCENTO(registro->faltas, totalAulas) > 25){
		if (media < 5)
			registro->sitaucao = REMF;
		else if (((registro->notas[0] < 3.0 || registro->notas[1] < 3.0 || registro->notas[2] < 3.0) && media > 5.0 && media < 7.0))
			registro->sitaucao = RENF;
		else {
			registro->sitaucao = REPF;
		}
	}
	else {
		if(registro->sitaucao == REC)
			media = calculaMediaFinalAluno(registro);
		// Verifica quantas notas abaixo de 3 o aluno tirou
		for (int i = 0; i < 3; ++i){
			if(registro->notas[i] < 3){
				notasInvalidas++;
			}
		}
		// Verificar se está reprovado por média
		if (media < 3 || (media < 5 && registro->sitaucao == REC) || notasInvalidas > 1)
			registro->sitaucao = REP;
		// Verificar se está reprovado por Média e nota REPN ​ 	Reprovado por Média e Nota - Reprovado porque a média está entre cinco e sete e a nota da reposição foi inferior a três.
		else if (registro->sitaucao != REC && ((media >= 3.0 && media < 5.0) || (notasInvalidas == 1 && media < 7.0)))
			registro->sitaucao = REC;
		else if (registro->reposicao < 3.0 && media > 5.0 && media < 7.0 && registro->sitaucao == REC)
			registro->sitaucao = REPN;
		else if (media >=7 )
			registro->sitaucao = APR;
		else if (media >= 5)
			registro->sitaucao = APRN;
	}
}
char* imprimeSituacao (Aluno* registro){
	switch (registro->sitaucao){
		case REPF: return "Reprovado por Faltas";break;
		case REP: return "Reprovado por Média";break;
		case REPN: return "Reprovado por Média e Nota";break;
		case REC: return "Em Recuperação";break;
		case APR: return "Aprovado por Média";break;
		case APRN: return "Aprovado por Notas";break;
		case REMF: return "Reprovado por Média e Faltas";break;
		case RENF: return "Reprovado por Notas e Faltas";break;
		default: return "Situação não Processada";
	}
}

void listaTurma (Turma* registro){
	printf("Nome da turma: %s\nNúmero de aulas: %d\nNúmero de Alunos: %d\n", registro->nome, registro->aulas, registro->alunos);
	for (int i = 0; i < registro->alunos; ++i)
	{
		printf("\nMatrícula: %03d\nNome: %s\nPercentual de faltas: %.0f%%\nNotas: \n", registro->lista[i].matricula, registro->lista[i].nome, PERCENTO(registro->lista[i].faltas, registro->aulas));
		for (int j = 0; j < 3; ++j)
			printf("%.2f ", registro->lista[i].notas[j]);
		printf("\n");
		if (registro->lista[i].reposicao != -1){
			printf("Reposição: %.2f\n", registro->lista[i].reposicao);
		}
		printf("Situação: %s\n", imprimeSituacao(&registro->lista[i]));
	}
}
void carregarDadosDeTurma(char *arquivo, Turma *t){
	int i, j;
	FILE *pFile = fopen(arquivo, "r");
	fscanf(pFile, "%s%d%d", t->nome, &t->aulas, &t->alunos);
	t->lista = malloc(t->alunos*sizeof(int));
	for (i = 0; i < t->alunos; ++i)
	{
		fscanf(pFile, "%d%s%d", &t->lista[i].matricula, t->lista[i].nome, &t->lista[i].faltas);
		for (j = 0; j < 3; ++j)
			fscanf(pFile, "%f", &t->lista[i].notas[j]);
		t->lista[i].sitaucao = DEFAULT; // Só para garantir que não haja lixo na memória
		atualizaSituacao(&t->lista[i], t->aulas);
		if (t->lista[i].sitaucao == REC) 
		{
			fscanf(pFile, "%f", &t->lista[i].reposicao); // Está pegando a nota no primeiro aluno
			atualizaSituacao(&t->lista[i], t->aulas);
		} else {
			t->lista[i].reposicao = -1;
		}
	}
}
int main(int argc, char const *argv[])
{
	Turma imd0012;
	carregarDadosDeTurma("inputRegEnum03", &imd0012);
	listaTurma(&imd0012);
	
	free(imd0012.lista);

	return 0;
}