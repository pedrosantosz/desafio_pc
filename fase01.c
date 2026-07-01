#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 50

typedef struct {
	char nome[100];
	char descricao[200];
	char data_limite[11];
	char categoria[10];
	int prioridade;
} tarefa;

int menu(void);
void le_string(char *string);
void insercao(tarefa *tarefas, int *total_tarefas);
int procura_tarefa(tarefa *tarefas, int *total_tarefas);
void busca(tarefa *tarefas, int *total_tarefas);
void listagem(tarefa *tarefas, int *total_tarefas);
void edicao(tarefa *tarefas, int *total_tarefas);
void exclusao(tarefa *tarefas, int *total_tarefas);

int main() {
	tarefa tarefas[MAX];

	int total_tarefas = 0;

	do {

		int op = menu();

		switch(op) {
			case 1:
				insercao(tarefas, &total_tarefas);
				break;
			case 2:
				busca(tarefas, &total_tarefas);
				break;
			case 3:
				listagem(tarefas, &total_tarefas);
				break;
			case 4:
				edicao(tarefas, &total_tarefas);
				break;
			case 5:
				exclusao(tarefas, &total_tarefas);
				break;
			case 6:
				exit(0);
				break; 
		}
	} while (1);

	return 0;
}

int menu(void) {
	int escolha;

	do {
		printf("\nTarefas\n");
		printf("\t1. Inserir Tarefa\n");
		printf("\t2. Procurar Tarefa\n");
		printf("\t3. Listar Tarefas\n");
		printf("\t4. Editar Tarefa\n");
		printf("\t5. Excluir Tarefa\n");
		printf("\t6. Sair\n");

		printf("\nEscolha: ");
		scanf("%d", &escolha);
	} while (escolha < 1 || escolha > 6);
	getchar();

	return escolha;
}

void le_string(char *string) {
	scanf("%[^\n]", string);
	getchar();
}

void insercao(tarefa *tarefas, int *total_tarefas) {
	printf("\nInsercao de Tarefa\n");
	
	int posicao = *total_tarefas;

	if (*total_tarefas < MAX) {
		printf("\nNome: ");
		le_string(tarefas[posicao].nome);

		printf("Descricao: ");
		le_string(tarefas[posicao].descricao);
		
		printf("Data Limite (AAAA-MM-DD): ");
		le_string(tarefas[posicao].data_limite);
		
		printf("Categoria (\"Prova\",\"Trabalho\",\"Outra\"): ");
		le_string(tarefas[posicao].categoria);

		printf("Prioridade (1 a 3): ");
		scanf("%d", &tarefas[posicao].prioridade);
		
		(*total_tarefas)++;
	} else {
		printf("\nA Lista de Tarefas Esta Cheia!\n");
	}
}

int procura_tarefa(tarefa *tarefas, int *total_tarefas) {
	int i;
	char nome[100];

	printf("\nNome da Tarefa: ");
	le_string(nome);

	for (i = 0; i < *total_tarefas && strcmp(tarefas[i].nome, nome); i++);

	if (i == *total_tarefas) {
		printf("\nTarefa nao encontrada!\n");
		return -1;
	}

	return i;
}

void busca(tarefa *tarefas, int *total_tarefas) {
	int pos;

	printf("\nBusca de Tarefa\n");

	pos = procura_tarefa(tarefas, total_tarefas);

	if (pos != -1) {
		printf("\nTarefa: %d\n", pos);
		printf("\tNome: %s\n", tarefas[pos].nome);
		printf("\tDescricao: %s\n", tarefas[pos].descricao);
		printf("\tData Limite: %s\n", tarefas[pos].data_limite);
		printf("\tCategoria: %s\n", tarefas[pos].categoria);
		printf("\tPrioridade: %d\n", tarefas[pos].prioridade);
	}
}

void listagem(tarefa *tarefas, int *total_tarefas) {
	printf("\nListagem de Tarefas (%d tarefas)\n", *total_tarefas);

	for (int i = 0; i < *total_tarefas; i++) {
		printf("\nTarefa: %d\n", i);
		printf("\tNome: %s\n", tarefas[i].nome);
		printf("\tDescricao: %s\n", tarefas[i].descricao);
		printf("\tData Limite: %s\n", tarefas[i].data_limite);
		printf("\tCategoria: %s\n", tarefas[i].categoria);
		printf("\tPrioridade: %d\n", tarefas[i].prioridade);
	}
}

void edicao(tarefa *tarefas, int *total_tarefas) {
	int pos = procura_tarefa(tarefas, total_tarefas);

	if (pos != -1) {
		int escolha;

		printf("\nEdicao de Tarefa\n");
		printf("\nQual dado sera editado?");
		printf("\n1. Nome\n2. Descricao\n3. Data Limite\n4. Categoria\n5. Prioridade\n");
		printf("Escolha: ");
		scanf("%d", &escolha);
		getchar();

		switch(escolha) {
			case 1:
				printf("\nNome: ");
				le_string(tarefas[pos].nome);
				break;
			case 2:
				printf("\nDescricao: ");
				le_string(tarefas[pos].descricao);
				break;
			case 3:
				printf("\nData Limite (AAAA-MM-DD): ");
				le_string(tarefas[pos].data_limite);
				break;
			case 4:
				printf("\nCategoria (\"Prova\",\"Trabalho\",\"Outra\"): ");
				le_string(tarefas[pos].categoria);
				break;
			case 5:
				printf("\nPrioridade (1 a 3): ");
				scanf("%d", &tarefas[pos].prioridade);
				break;
		}
	}
}

void exclusao(tarefa *tarefas, int *total_tarefas) {
	int pos, i;

	printf("\nExclusao de Tarefa\n");

	pos = procura_tarefa(tarefas, total_tarefas);

	if (pos != -1) {
		for (i = pos; i < *total_tarefas - 1; i++) {
			 strcpy(tarefas[i].nome, tarefas[i+1].nome);
			 strcpy(tarefas[i].descricao, tarefas[i+1].descricao);
			 strcpy(tarefas[i].data_limite, tarefas[i+1].data_limite);
			 strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
			 tarefas[i].prioridade = tarefas[i+1].prioridade;
		}

		strcpy(tarefas[i].nome, "");
		strcpy(tarefas[i].descricao, "");
		strcpy(tarefas[i].data_limite, "");
		strcpy(tarefas[i].categoria, "");
		tarefas[i].prioridade = 0;

		(*total_tarefas)--;
	}
}
