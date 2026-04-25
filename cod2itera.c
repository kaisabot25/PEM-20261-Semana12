/*----------------------------------------------------------*
*                      FATEC Ipiranga                       *
* Disciplina: Programaçao Estruturada e Modular             *
*          Prof. Veríssimo                                  *
*-----------------------------------------------------------*
* Objetivo do Programa: Busca em profundidade(Recursividade)*
* Data - 24/04/2026                                         * 
* Karen Selenic da Costa                                    *
*-----------------------------------------------------------*/
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_PASTAS 50
#define LIMITE_ALERTA 300.0
typedef struct {
    char nome[50];
    float tamanho_proprio;
    float tamanho_total;
    int subpastas_indices[10];
    int qtd_sub;
} Pasta;
typedef struct {
    int index;
    int nivel;
    int visitado;
} StackItem;
int main() {
    Pasta drive[MAX_PASTAS] = {0};
    StackItem stack[MAX_PASTAS];
    int top = -1;
    strcpy(drive[0].nome, "RAIZ");
    drive[0].tamanho_proprio = 10.0;
    drive[0].qtd_sub = 2;
    drive[0].subpastas_indices[0] = 1;
    drive[0].subpastas_indices[1] = 2;
    strcpy(drive[1].nome, "Projetos_TI");
    drive[1].tamanho_proprio = 50.0;
    drive[1].qtd_sub = 1;
    drive[1].subpastas_indices[0] = 3;
    strcpy(drive[2].nome, "Backups_Antigos");
    drive[2].tamanho_proprio = 350.0;
    strcpy(drive[3].nome, "Videos_Aulas");
    drive[3].tamanho_proprio = 280.0;
    int limite;
    printf("Defina o limite de profundidade: ");
    if (scanf("%d", &limite) != 1 || limite < 0) {
        printf("Entrada inválida.\n");
        return 1;
    }
    clock_t t;
    t = clock(); // início
    stack[++top] = (StackItem){0, 0, 0};
    while (top >= 0) {
        StackItem current = stack[top--];
        if (current.nivel > limite) continue;
        int idx = current.index;
        Pasta *p = &drive[idx];
        if (!current.visitado) {
            stack[++top] = (StackItem){idx, current.nivel, 1};
            for (int i = p->qtd_sub - 1; i >= 0; i--) {
                int filho = p->subpastas_indices[i];
                stack[++top] = (StackItem){filho, current.nivel + 1, 0};
            }
        } else {
            p->tamanho_total = p->tamanho_proprio;
            for (int i = 0; i < p->qtd_sub; i++) {
                int filho = p->subpastas_indices[i];
                p->tamanho_total += drive[filho].tamanho_total;
            }
            for (int i = 0; i < current.nivel; i++) {
                printf("  ");
            }
            printf("|-- %s [%.2f GB]", p->nome, p->tamanho_total);
            if (p->tamanho_total > LIMITE_ALERTA) {
                printf("\n[!] ALERTA: GARGALO DETECTADO");
            }
            printf("\n");
        }
    }
    t = clock() - t;
    double tempo_execucao = ((double)t) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", tempo_execucao);
    return 0;
}
