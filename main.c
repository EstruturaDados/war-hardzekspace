#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Definição da struct Territorio
// Representa um território no jogo War estruturado
typedef struct {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército que controla o território
    int tropas;     // Quantidade de tropas no território
} Territorio;

/*
 * Função: cadastrarTerritorios
 * ----------------------------
 * Lê do usuário os dados dos territórios e preenche o vetor dinâmico.
 *
 *  mapa: ponteiro para o primeiro elemento do vetor de Territorio
 *  quantidade: número total de territórios a serem cadastrados
 */
void cadastrarTerritorios(Territorio *mapa, int quantidade) {
    for (int i = 0; i < quantidade; i++) {
        printf("\n=== CADASTRO DO TERRITORIO %d ===\n", i + 1);

        printf("Digite o nome do territorio: ");
        // " %29[^\n]" lê até 29 caracteres ou até encontrar quebra de linha
        scanf(" %29[^\n]", mapa[i].nome);

        printf("Digite a cor do exercito (ex: vermelho, azul, verde): ");
        scanf(" %9s", mapa[i].cor);

        do {
            printf("Digite o numero de tropas (minimo 1): ");
            scanf("%d", &mapa[i].tropas);
            if (mapa[i].tropas < 1) {
                printf("Numero de tropas invalido! Tente novamente.\n");
            }
        } while (mapa[i].tropas < 1);
    }
}

/*
 * Função: exibirTerritorios
 * -------------------------
 * Mostra todos os territórios cadastrados com seus dados.
 *
 *  mapa: ponteiro para o vetor de Territorio
 *  quantidade: número total de territórios
 */
void exibirTerritorios(Territorio *mapa, int quantidade) {
    printf("\n=== LISTA DE TERRITORIOS ===\n");
    for (int i = 0; i < quantidade; i++) {
        printf("\nTerritorio %d:\n", i + 1);
        printf("  Nome : %s\n", mapa[i].nome);
        printf("  Cor  : %s\n", mapa[i].cor);
        printf("  Tropas: %d\n", mapa[i].tropas);
    }
    printf("\n");
}

/*
 * Função: atacar
 * --------------
 * Simula um ataque entre dois territórios utilizando "dados" (números aleatórios).
 *
 *  atacante: ponteiro para o território que está atacando
 *  defensor: ponteiro para o território que está defendendo
 *
 * Regras básicas:
 *  - Cada lado rola um "dado" de 1 a 6 (rand() % 6 + 1).
 *  - Se o valor do atacante for maior que o do defensor:
 *        * o defensor muda de cor para a cor do atacante
 *        * o número de tropas do defensor passa a ser metade das tropas do atacante (atacante / 2)
 *        * o atacante também perde metade das tropas (divide por 2, arredondando para baixo)
 *  - Se o defensor for maior ou igual:
 *        * o atacante perde 1 tropa (se ainda tiver tropa)
 */
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante == NULL || defensor == NULL) {
        return;
    }

    // Verifica se o atacante tem pelo menos 1 tropa para atacar
    if (atacante->tropas < 1) {
        printf("\n[ERRO] O territorio atacante nao possui tropas suficientes para atacar.\n");
        return;
    }

    printf("\n=== SIMULACAO DE ATAQUE ===\n");
    printf("Atacante: %s (%s) - Tropas: %d\n",
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - Tropas: %d\n",
           defensor->nome, defensor->cor, defensor->tropas);

    int dadoAtacante = rand() % 6 + 1; // 1 a 6
    int dadoDefensor = rand() % 6 + 1; // 1 a 6

    printf("\nDado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nResultado: O ATACANTE VENCEU A BATALHA!\n");

        // Metade das tropas do atacante vai para o defensor
        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) {
            tropasTransferidas = 1; // Garante que pelo menos 1 tropa ocupe o território
        }

        // Atualiza tropas do atacante (perde as tropas que foram transferidas)
        atacante->tropas -= tropasTransferidas;

        // Atualiza dados do defensor: muda de cor e recebe tropas
        strcpy(defensor->cor, atacante->cor);
        defensor->tropas = tropasTransferidas;

        printf("O territorio %s foi conquistado!\n", defensor->nome);
        printf("Nova cor do defensor: %s\n", defensor->cor);
        printf("Tropas que permaneceram no atacante: %d\n", atacante->tropas);
        printf("Tropas no territorio conquistado: %d\n", defensor->tropas);

    } else {
        printf("\nResultado: O DEFENSOR RESISTIU AO ATAQUE!\n");

        if (atacante->tropas > 0) {
            atacante->tropas -= 1;
        }

        printf("O atacante perdeu 1 tropa.\n");
        printf("Tropas restantes no atacante: %d\n", atacante->tropas);
    }
}

/*
 * Função: liberarMemoria
 * ----------------------
 * Libera a memória alocada dinamicamente para o vetor de territórios.
 *
 *  mapa: ponteiro para o vetor alocado dinamicamente
 */
void liberarMemoria(Territorio *mapa) {
    if (mapa != NULL) {
        free(mapa);
        printf("\nMemoria liberada com sucesso.\n");
    }
}

int main() {
    int quantidade;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("=== SISTEMA DE TERRITORIOS - JOGO WAR (NIVEL AVANCADO) ===\n");

    // Pergunta ao usuário quantos territórios deseja cadastrar
    do {
        printf("\nDigite o numero total de territorios (minimo 2): ");
        scanf("%d", &quantidade);
        if (quantidade < 2) {
            printf("Quantidade invalida! E necessario pelo menos 2 territorios.\n");
        }
    } while (quantidade < 2);

    // Alocacao dinamica de um vetor de Territorio
    // Usando malloc (poderia usar calloc tambem)
    Territorio *mapa = (Territorio *) malloc(quantidade * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria para os territorios.\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, quantidade);

    // Exibe o mapa inicial
    exibirTerritorios(mapa, quantidade);

    // Loop de ataques
    int opcao;
    do {
        printf("=== MENU DE ACOES ===\n");
        printf("1 - Realizar um ataque\n");
        printf("2 - Exibir territorios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idxAtacante, idxDefensor;

            // Mostra territorios para o usuario escolher
            exibirTerritorios(mapa, quantidade);

            printf("Digite o numero do territorio ATACANTE: ");
            scanf("%d", &idxAtacante);
            printf("Digite o numero do territorio DEFENSOR: ");
            scanf("%d", &idxDefensor);

            // Ajuste de índice (usuário vê 1..N, vetor é 0..N-1)
            idxAtacante--;
            idxDefensor--;

            // Validacoes básicas
            if (idxAtacante < 0 || idxAtacante >= quantidade ||
                idxDefensor < 0 || idxDefensor >= quantidade) {
                printf("\n[ERRO] Indice de territorio invalido!\n");
                continue;
            }

            if (idxAtacante == idxDefensor) {
                printf("\n[ERRO] Um territorio nao pode atacar a si mesmo!\n");
                continue;
            }

            // Nao permitir atacar territorio da mesma cor
            if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
                printf("\n[ERRO] Nao e permitido atacar um territorio da mesma cor!\n");
                continue;
            }

            // Chama a função de ataque, passando ponteiros para os territórios
            atacar(&mapa[idxAtacante], &mapa[idxDefensor]);

            // Mostra o estado atualizado após o ataque
            exibirTerritorios(mapa, quantidade);

        } else if (opcao == 2) {
            exibirTerritorios(mapa, quantidade);
        } else if (opcao == 0) {
            printf("\nSaindo do sistema...\n");
        } else {
            printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    // Libera a memoria dinamicamente alocada
    liberarMemoria(mapa);

    return 0;
}
