#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define TamMax 5

typedef struct{
    int Id_TT;
    char Nome_TT[99];
    char descricao[999];
} TipoTarefa;

typedef struct{
    int Id_P;
    char Nome_P[99];
} Pessoa;

typedef struct {
    int Id_T;
    char Nome_T[99];
    Pessoa Tarefa_P;
    TipoTarefa Tarefa_TT;
} Tarefa;

void CriarTarefa(Tarefa tarefa[],int numTarefas) {

	printf("\n---- Criar Tarefa ----\n");

	printf("Digite o ID da tarefa: ");
	scanf("%d", &tarefa[numTarefas].Id_T);

	printf("Digite o nome da tarefa: ");
	scanf(" %[^\n]s", tarefa[numTarefas].Nome_T);

	printf("Digite o ID da pessoa responsavel pela tarefa: ");
	scanf("%d", &tarefa[numTarefas].Tarefa_P.Id_P);

	printf("Digite o nome da pessoa responsavel pela tarefa: ");
	scanf(" %[^\n]s", tarefa[numTarefas].Tarefa_P.Nome_P);

	printf("Digite o ID do tipo de tarefa: ");
	scanf("%d", &tarefa[numTarefas].Tarefa_TT.Id_TT);

	printf("Digite o nome do tipo de tarefa: ");
	scanf(" %[^\n]s", tarefa[numTarefas].Tarefa_TT.Nome_TT);

	printf("Digite a descricao da tarefa: ");
	scanf(" %[^\n]s", tarefa[numTarefas].Tarefa_TT.descricao);

	printf("\nTarefa criada com sucesso!\n");

}

void VisualizarTarefa(Tarefa tarefa[], int numTarefas) {
	printf("\n---- Visualizar Tarefas ----\n");

	if (numTarefas == 0) {
    	printf("Nenhuma tarefa foi criada.\n");
    	return;
	}

	for (int i = 0; i < numTarefas; i++) {
        if(tarefa[i].Id_T != NULL){
    	printf("Tarefa %d:\n", i + 1);
    	printf("ID: %d\n", tarefa[i].Id_T);
    	printf("Nome: %s\n", tarefa[i].Nome_T);
    	printf("Responsavel: %s (ID: %d)\n", tarefa[i].Tarefa_P.Nome_P, tarefa[i].Tarefa_P.Id_P);
    	printf("Tipo: %s (ID: %d)\n", tarefa[i].Tarefa_TT.Nome_TT, tarefa[i].Tarefa_TT.Id_TT);
    	printf("Descricao: %s\n\n", tarefa[i].Tarefa_TT.descricao);
    	}else{printf("Nenhuma tarefa foi criada.\n");}
	}
}

void AtualizarTarefa(Tarefa tarefa[], int numTarefas) {
	int id;

	printf("\n---- Atualizar Tarefa ----\n");

	if (numTarefas == 0) {
    	printf("Nenhuma tarefa foi criada.\n");
    	return;
	}

	printf("Digite o ID da tarefa que deseja atualizar: ");
	scanf("%d", &id);

	int found = 0;

	for (int i = 0; i < numTarefas; i++) {
    	if (tarefa[i].Id_T == id) {
        	found = 1;

        	printf("Tarefa encontrada:\n");
        	printf("ID: %d\n", tarefa[i].Id_T);
        	printf("Nome: %s\n", tarefa[i].Nome_T);
        	printf("Responsavel: %s (ID: %d)\n", tarefa[i].Tarefa_P.Nome_P, tarefa[i].Tarefa_P.Id_P);
        	printf("Tipo: %s (ID: %d)\n", tarefa[i].Tarefa_TT.Nome_TT, tarefa[i].Tarefa_TT.Id_TT);
        	printf("Descricao: %s\n\n", tarefa[i].Tarefa_TT.descricao);

        	printf("Digite o novo nome da tarefa: ");
        	scanf(" %[^\n]s", tarefa[i].Nome_T);

        	printf("Digite o novo ID da pessoa responsavel pela tarefa: ");
        	scanf("%d", &tarefa[i].Tarefa_P.Id_P);

        	printf("Digite o novo nome da pessoa responsavel pela tarefa: ");
        	scanf(" %[^\n]s", tarefa[i].Tarefa_P.Nome_P);

        	printf("Digite o novo ID do tipo de tarefa: ");
        	scanf("%d", &tarefa[i].Tarefa_TT.Id_TT);

        	printf("Digite o novo nome do tipo de tarefa: ");
        	scanf(" %[^\n]s", tarefa[i].Tarefa_TT.Nome_TT);

        	printf("Digite a nova descricao da tarefa: ");
        	scanf(" %[^\n]s", tarefa[i].Tarefa_TT.descricao);

        	printf("\nTarefa atualizada com sucesso!\n");
        	break;
    	}
	}

	if (!found) {
    	printf("Tarefa com ID %d nao encontrada.\n", id);
	}
}


void ExcluirTarefa(Tarefa tarefa[], int *numTarefas) {
	int id;

	printf("\n---- Excluir Tarefa ----\n");

	if (*numTarefas == 0) {
    	printf("Nenhuma tarefa foi criada.\n");
    	return;
	}

	printf("Digite o ID da tarefa que deseja excluir: ");
	scanf("%d", &id);

	int found = 0;

	for (int i = 0; i < *numTarefas; i++) {
    	if (tarefa[i].Id_T == id) {
        	found = 1;

        	for (int j = i; j < *numTarefas - 1; j++) {
            	tarefa[j] = tarefa[j + 1];
        	}

        	(*numTarefas)--;

        	printf("Tarefa com ID %d excluída com sucesso.\n", id);
        	break;
    	}
	}

	if (!found) {
    	printf("Tarefa com ID %d nao encontrada.\n", id);
	}
}

void LerArquivo(Tarefa tarefa[], int *numTarefas){
	FILE *arquivo;
	arquivo = fopen("Lista_tarefas.txt", "r");

	if (arquivo == NULL) {
    	printf("Erro ao abrir o arquivo. Se voce nao fez nenhuma lista antes, isso eh normal.\n");
    	return;
	}

	while (!feof(arquivo) && *numTarefas < TamMax) {
    	fscanf(arquivo, "%d\n", &tarefa[*numTarefas].Id_T);
    	fgets(tarefa[*numTarefas].Nome_T, 99, arquivo);
    	tarefa[*numTarefas].Nome_T[strcspn(tarefa[*numTarefas].Nome_T, "\n")] = '\0';
    	fscanf(arquivo, "%d\n", &tarefa[*numTarefas].Tarefa_P.Id_P);
    	fgets(tarefa[*numTarefas].Tarefa_P.Nome_P, 99, arquivo);
    	tarefa[*numTarefas].Tarefa_P.Nome_P[strcspn(tarefa[*numTarefas].Tarefa_P.Nome_P, "\n")] = '\0';
    	fscanf(arquivo, "%d\n", &tarefa[*numTarefas].Tarefa_TT.Id_TT);
    	fgets(tarefa[*numTarefas].Tarefa_TT.Nome_TT, 99, arquivo);
    	tarefa[*numTarefas].Tarefa_TT.Nome_TT[strcspn(tarefa[*numTarefas].Tarefa_TT.Nome_TT, "\n")] = '\0';
    	fgets(tarefa[*numTarefas].Tarefa_TT.descricao, 999, arquivo);

    	(*numTarefas)++;

	}

	fclose(arquivo);
	printf("As suas listas foram carregadas com sucesso !!\n");
}

void EscreverArquivo(Tarefa tarefa[], int numTarefas) {
	FILE *arquivo;
	arquivo = fopen("Lista_tarefas.txt", "w");

	if (arquivo == NULL) {
    	printf("Erro ao abrir o arquivo. Perdeu todo o teu banco de dados kkkkk vacilao\n");
    	return;
	}

	for (int i = 0; i < numTarefas; i++) {
        if(tarefa[i].Id_T != NULL){
    	fprintf(arquivo, "%d\n", tarefa[i].Id_T);
    	fprintf(arquivo, "%s\n", tarefa[i].Nome_T);
    	fprintf(arquivo, "%d\n", tarefa[i].Tarefa_P.Id_P);
    	fprintf(arquivo, "%s\n", tarefa[i].Tarefa_P.Nome_P);
    	fprintf(arquivo, "%d\n", tarefa[i].Tarefa_TT.Id_TT);
    	fprintf(arquivo, "%s\n", tarefa[i].Tarefa_TT.Nome_TT);
    	fprintf(arquivo, "%s\n", tarefa[i].Tarefa_TT.descricao);
        }
	}

	fclose(arquivo);
	printf("Suas listas foram salvas com sucesso !!\n");
}




int main() {
	int i, n;
	TipoTarefa tipotarefa[TamMax];
	Pessoa pessoa[TamMax];
	Tarefa tarefa[TamMax];
	int numTarefas = 0;

	printf("Lista de tarefas tuctuctuc !!\n");

	LerArquivo(tarefa, &numTarefas);

	for (i = 0; i > -1; i++) {
    	printf("\nCriar tarefa - 1\nVisualizar tarefas - 2\nAtualizar tarefa - 3\nExcluir tarefa - 4\nFinalizar app - 5\n");
    	printf("\nO que voce quer fazer? (Digite o numero correspondente)\n");
    	scanf("%d", &n);
    	if (n == 1) {
        	if(numTarefas == TamMax){
            	printf("Numero maximo de tarefas atingidas. Tente Excluir alguma.");
        	}else{
        	CriarTarefa(tarefa,numTarefas);
        	numTarefas++;
        	}
    	} else if (n == 2) {
        	VisualizarTarefa(tarefa, numTarefas);
    	} else if (n == 3) {
        	AtualizarTarefa(tarefa, numTarefas);
    	} else if (n == 4) {
        	ExcluirTarefa(tarefa, &numTarefas);
    	} else if (n == 5) {
        	EscreverArquivo(tarefa, numTarefas);
        	return 0;
    	}
	}

	return 0;
}





