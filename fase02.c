#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct tarefa{
	char nome[100];
	char descricao[200];
	char data_limite[11];
	char categoria[10];
	int prioridade;

	int concluida;
	struct tarefa *prox;
} tarefa;

int menu(void);
void le_string(char *string);
void ordena_tarefa(tarefa *comeco, tarefa *nova_trf);
void insercao(tarefa *tarefas);
tarefa *procura_tarefa(tarefa *tarefas);
void busca(tarefa *tarefas);
void listagem(tarefa *tarefas);
void atualiza_anterior(tarefa *origem, tarefa *destino);
void exclusao(tarefa *tarefas, tarefa *tarefa_excluida);
void edicao(tarefa *tarefas);

void concluir_tarefa(tarefa *tarefas);
void salvar_tarefas(tarefa *tarefas);
void carregar_tarefas(tarefa *tarefas);

int main() {
	tarefa *tarefas;
	tarefas = (tarefa *) malloc(sizeof(tarefa));
	tarefas->prox = NULL;

	carregar_tarefas(tarefas);

	do {

		int op = menu();

		switch(op) {
			case 1:
				insercao(tarefas);
				break;
			case 2:
				busca(tarefas);
				break;
			case 3:
				listagem(tarefas);
				break;
			case 4:
				edicao(tarefas);
				break;
			case 5:
				exclusao(tarefas, procura_tarefa(tarefas));
				break;
			case 6:
				concluir_tarefa(tarefas);
				break;
			case 7:
				salvar_tarefas(tarefas);
				break;
			case 8:
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
		printf("\t6. Concluir Tarefa\n");
		printf("\t7. Salvar Tarefas\n");
		printf("\t8. Sair\n");

		printf("\nEscolha: ");
		scanf("%d", &escolha);
	} while (escolha < 1 || escolha > 8);
	getchar();

	return escolha;
}

void le_string(char *string) {
	scanf("%[^\n]", string); // nao trata o caso de serem lidos mais caracteres do que se pode
	getchar();
}

void insercao(tarefa *tarefas) {
	printf("\nInsercao de Tarefa\n");
	
	tarefa *nova_tarefa;
	nova_tarefa = (tarefa *) malloc(sizeof(tarefa));

	printf("\nNome: ");
	le_string(nova_tarefa->nome); // nao verifica se o nome ja existe

	printf("Descricao: ");
	le_string(nova_tarefa->descricao);
	
	printf("Data Limite (AAAA-MM-DD): ");
	le_string(nova_tarefa->data_limite);
	
	printf("Categoria (\"Prova\",\"Trabalho\",\"Outra\"): ");
	le_string(nova_tarefa->categoria);

	printf("Prioridade (1 a 3): ");
	scanf("%d", &(nova_tarefa->prioridade));
	getchar();

	nova_tarefa->concluida = 0;

	ordena_tarefa(tarefas, nova_tarefa);
}

void ordena_tarefa(tarefa *comeco, tarefa *nova_trf) {
	tarefa *atual;	

	for (atual = comeco; atual->prox != NULL && 
		 (strcmp(nova_trf->data_limite, (atual->prox)->data_limite) > 0 || 
		  (!strcmp(nova_trf->data_limite, (atual->prox)->data_limite) && 
		  	nova_trf->prioridade < (atual->prox)->prioridade)); atual = atual->prox);

	nova_trf->prox = atual->prox;
	atual->prox = nova_trf;
}

tarefa *procura_tarefa(tarefa *tarefas) {
	tarefa *tarefa_buscada;
	char nome[100];

	printf("\nNome da Tarefa: ");
	le_string(nome);

	for (tarefa_buscada = tarefas->prox; tarefa_buscada != NULL && strcmp(tarefa_buscada->nome, nome); tarefa_buscada = tarefa_buscada->prox);

	if (tarefa_buscada == NULL)
		printf("\nTarefa nao encontrada!\n");

	return tarefa_buscada;
}

void busca(tarefa *tarefas) {
	tarefa *tarefa_buscada;

	printf("\nBusca de Tarefa\n");

	tarefa_buscada = procura_tarefa(tarefas);

	if (tarefa_buscada != NULL) {
		printf("\tNome: %s\n", tarefa_buscada->nome);
		printf("\tDescricao: %s\n", tarefa_buscada->descricao);
		printf("\tData Limite: %s\n", tarefa_buscada->data_limite);
		printf("\tCategoria: %s\n", tarefa_buscada->categoria);
		printf("\tPrioridade: %d\n", tarefa_buscada->prioridade);
		printf("\tConcluida: %d\n", tarefa_buscada->concluida);
	}
}

void listagem(tarefa *tarefas) {
	int escolha, i = 0;

	do {
		printf("\nFiltrar por:\n1. Todas Tarefas\n2. Apenas Concluidas\n3. Apenas Nao Concluidas\nEscolha: ");
		scanf("%d", &escolha);
	} while (escolha < 1 || escolha > 3);

	printf("\nListagem de Tarefas\n");

	for (tarefa *tarefa_atual = tarefas->prox; tarefa_atual != NULL; tarefa_atual = tarefa_atual->prox) {
		if (escolha == 1 || (escolha == 2 && tarefa_atual->concluida == 1) || (escolha == 3 && tarefa_atual->concluida == 0)) {
			printf("\nTarefa %d\n", i);
			printf("\tNome: %s\n", tarefa_atual->nome);
			printf("\tDescricao: %s\n", tarefa_atual->descricao);
			printf("\tData Limite: %s\n", tarefa_atual->data_limite);
			printf("\tCategoria: %s\n", tarefa_atual->categoria);
			printf("\tPrioridade: %d\n", tarefa_atual->prioridade);
			printf("\tConcluida: %d\n", tarefa_atual->concluida);
			i++;
		}
	}
}

void edicao(tarefa *tarefas) {
	tarefa *tarefa_atualizada = procura_tarefa(tarefas);

	if (tarefa_atualizada != NULL) {
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
				le_string(tarefa_atualizada->nome);
				break;
			case 2:
				printf("\nDescricao: ");
				le_string(tarefa_atualizada->descricao);
				break;
			case 3:
				printf("\nData Limite (AAAA-MM-DD): ");
				le_string(tarefa_atualizada->data_limite);

				atualiza_anterior(tarefas, tarefa_atualizada);
				ordena_tarefa(tarefas, tarefa_atualizada);
				break;
			case 4:
				printf("\nCategoria (\"Prova\",\"Trabalho\",\"Outra\"): ");
				le_string(tarefa_atualizada->categoria);
				break;
			case 5:
				printf("\nPrioridade (1 a 3): ");
				scanf("%d", &tarefa_atualizada->prioridade);
				atualiza_anterior(tarefas, tarefa_atualizada);
				ordena_tarefa(tarefas, tarefa_atualizada);
				break;
		}
	}
}

void atualiza_anterior(tarefa *origem, tarefa *destino) {
	tarefa *anterior;

	for(anterior = origem; anterior->prox != NULL && anterior->prox != destino; anterior = anterior->prox);
	anterior->prox = destino->prox;
}

void exclusao(tarefa *tarefas, tarefa *tarefa_excluida) {
	if (tarefa_excluida != NULL) {
		atualiza_anterior(tarefas, tarefa_excluida);
		free(tarefa_excluida);
	}
}

void concluir_tarefa(tarefa *tarefas) {
	tarefa *tarefa_concluida;

	tarefa_concluida = procura_tarefa(tarefas);

	if (tarefa_concluida != NULL)
		tarefa_concluida->concluida = 1;
}

void salvar_tarefas(tarefa *tarefas) {
	FILE *fp;

	if ((fp = fopen("tarefas_out.txt", "w")) != NULL) {
		for (tarefa *trf = tarefas->prox; trf != NULL; trf = trf->prox) 
			fprintf(fp, "%s|%s|%s|%s|%d|%d\n", trf->nome, trf->descricao, trf->data_limite, trf->categoria, trf->prioridade, trf->concluida);
		printf("\nTarefas Salvas com Sucesso!\n");
		
		fclose(fp);
	}
}

void carregar_tarefas(tarefa *tarefas) {
	FILE *fp;
	char linha[350];

	if ((fp = fopen("tarefas_in.txt", "r")) != NULL) {
		while (fscanf(fp, "%[^\n]", linha) != EOF) {
			fgetc(fp);

			tarefa *nova_tarefa;
			nova_tarefa = (tarefa *) malloc(sizeof(tarefa));

			strcpy(nova_tarefa->nome, strtok(linha, "|"));
			strcpy(nova_tarefa->descricao, strtok(NULL, "|"));
			strcpy(nova_tarefa->data_limite, strtok(NULL, "|"));
			strcpy(nova_tarefa->categoria, strtok(NULL, "|"));
			nova_tarefa->prioridade = atoi(strtok(NULL, "|"));
			nova_tarefa->concluida = atoi(strtok(NULL, "|"));

			ordena_tarefa(tarefas, nova_tarefa);
		}
		fclose(fp);
	}
}
