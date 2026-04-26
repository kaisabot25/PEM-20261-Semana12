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
long long ciclos = 0;
typedef struct {
    char nome[50];
    float tamanho_proprio;
    float tamanho_total;
    int subpastas_indices[10];
    int qtd_sub;
} Pasta;
float processarHierarquia(Pasta *drive, int index, int nivel_atual, int limite_profundidade) {
    ciclos++;
    if (index < 0 || nivel_atual > limite_profundidade) {
        ciclos++;
        return 0.0;
    } 
    Pasta *p = &drive[index];
    ciclos++;
    p->tamanho_total = p->tamanho_proprio;
    ciclos++;
    for (int i = 0; i < p->qtd_sub; i++) {
        ciclos++;
        int filho_idx = p->subpastas_indices[i];
        ciclos++;
        p->tamanho_total += processarHierarquia(drive, filho_idx, nivel_atual + 1, limite_profundidade);
        ciclos++;
    }
    for (int i = 0; i < nivel_atual; i++) {
        ciclos++;
        printf("  ");
    }
    ciclos++;
    printf("|-- %s [%.2f GB]", p->nome, p->tamanho_total);
    if (p->tamanho_total > LIMITE_ALERTA) {
        ciclos++;
        printf("\n[!] ALERTA: GARGALO DETECTADO");
    }
    printf("\n");
    ciclos++;
    return p->tamanho_total;
}
int main() {
    Pasta drive[MAX_PASTAS] = {0};
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
    clock_t t = clock();
    processarHierarquia(drive, 0, 0, limite);
    t = clock() - t;
    double tempo_execucao = ((double)t) / CLOCKS_PER_SEC;
    printf("Tempo de execução: %f segundos\n", tempo_execucao);
    printf("Ciclos estimados: %lld\n", ciclos);
    return 0;
}
