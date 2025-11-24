#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ===================== STRUCT E TIPOS BÁSICOS =====================

// Estrutura que representa um território no jogo War estruturado
typedef struct {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército que controla o território
    int tropas;     // Quantidade de tropas no território
} Territorio;


// ===================== FUNÇÕES DE MISSÃO =====================

/*
 * Função: atribuirMissao
 * ----------------------
 * Sorteia uma missão do vetor de missões e copia para o destino.
 *
 *  destino: ponteiro para a string de missão do jogador (já alocada com malloc)
 *  missoes: vetor de ponteiros para strings (missões pré-definidas)
 *  totalMissoes: quantidade total de missões disponíveis no vetor
 */
void atribuirMissao(char *destino, char *missoes[], int totalMissoes) {
    if (destino == NULL || missoes == NULL || totalMissoes <= 0) {
        return;
    }

    int indice = rand() % totalMissoes;  // Sorteia índice entre 0 e totalMissoes-1
    strcpy(destino, missoes[indice]);
}

/*
 * Função: exibirMissao
 * --------------------
 * Exibe a missão de um jogador (passada por valor, só leitura).
 *
 *  nomeJogador: nome do jogador (apenas para exibição)
 *  missao: string com a missão do jogador
 */
void exibirMissao(const char *nomeJogador, const char *missao) {
    printf("\n=== MISSAO DO %s ===\n", nomeJogador);
    printf("%s\n\n", missao);
}

/*
 * Função: verificarMissao
 * -----------------------
 * Verifica se uma missão foi cumprida.
 *
 * IMPORTANTE: para simplificar, vamos implementar uma lógica bem simples,
 * apenas como exemplo. A ideia é mostrar o uso de ponteiros e análise sobre o mapa.
 *
 * Regras implementadas nesta versão:
 *  - Se a missão contém a palavra "3territorios":
 *        O jogador vence se existir pelo menos 3 territórios consecutivos
 *        (no vetor) com a mesma cor.
 *  - Se a missão contém a palavra "dominar":
 *        O jogador vence se tiver mais da metade dos territórios com a sua cor.
 *
 *  missao: string com a missão do jogador
 *  mapa: ponteiro para o vetor de territórios
 *  tamanho: quantidade total de territórios
 *  corJogador: cor do exército do jogador
 *
 * Retorno:
 *  1  -> missão cumprida
 *  0  -> missão ainda não cumprida
 */
int verificarMissao(char *missao, Territorio *mapa, int tamanho, const char *corJogador) {
    if (missao == NULL || mapa == NULL || corJogador == NULL || tamanho <= 0) {
        return 0;
    }

    // Exemplo 1: missão de conquistar 3 territórios seguidos
    if (strstr(missao, "3territorios") != NULL) {
        int consecutivos = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                consecutivos++;
                if (consecutivos >= 3) {
                    return 1; // Missão cumprida
                }
            } else {
                consecutivos = 0;
            }
        }
        return 0;
    }

    // Exemplo 2: missão de dominar a maioria dos territórios
    if (strstr(missao, "dominar") != NULL) {
        int contaJogador = 0;
        for (int i = 0; i < tamanho; i++) {
            if (strcmp(mapa[i].cor, corJogador) == 0) {
                contaJogador++;
            }
        }
        if (contaJogador > tamanho / 2) {
            return 1; // Missão cumprida
        }
        return 0;
    }

    // Outras missões poderiam ser adicionadas aqui com lógicas diferentes.

    // Caso nenhuma regra especial seja correspondente, considera não cumprida.
    return 0;
}


// ===================== FUNÇÕES DE TERRITÓRIOS =====================

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
        printf("  Nome  : %s\n", mapa[i].nome);
        printf("  Cor   : %s\n", mapa[i].cor);
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
 *        * o número de tropas do defensor passa a ser metade das tropas do atacante
 *        * o atacante também perde metade das tropas (divide por 2)
 *  - Se o defensor for maior ou igual:
 *        * o atacante perde 1 tropa (se ainda tiver tropa)
 */
void atacar(Territorio *atacante, Territorio *defensor) {
    if (atacante == NULL || defensor == NULL) {
        return;
    }

    if (atacante->tropas < 1) {
        printf("\n[ERRO] O territorio atacante nao possui tropas suficientes para atacar.\n");
        return;
    }

    printf("\n=== SIMULACAO DE ATAQUE ===\n");
    printf("Atacante: %s (%s) - Tropas: %d\n",
           atacante->nome, atacante->cor, atacante->tropas);
    printf("Defensor: %s (%s) - Tropas: %d\n",
           defensor->nome, defensor->cor, defensor->tropas);

    int dadoAtacante = rand() % 6 + 1;
    int dadoDefensor = rand() % 6 + 1;

    printf("\nDado do atacante: %d\n", dadoAtacante);
    printf("Dado do defensor: %d\n", dadoDefensor);

    if (dadoAtacante > dadoDefensor) {
        printf("\nResultado: O ATACANTE VENCEU A BATALHA!\n");

        int tropasTransferidas = atacante->tropas / 2;
        if (tropasTransferidas < 1) {
            tropasTransferidas = 1;
        }

        atacante->tropas -= tropasTransferidas;

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
 * Libera a memória alocada dinamicamente para o vetor de territórios
 * e para as missões dos jogadores.
 *
 *  mapa: ponteiro para o vetor alocado dinamicamente
 *  missaoJogador1, missaoJogador2: strings de missão alocadas com malloc
 */
void liberarMemoria(Territorio *mapa, char *missaoJogador1, char *missaoJogador2) {
    if (mapa != NULL) {
        free(mapa);
    }
    if (missaoJogador1 != NULL) {
        free(missaoJogador1);
    }
    if (missaoJogador2 != NULL) {
        free(missaoJogador2);
    }
    printf("\nMemoria liberada com sucesso.\n");
}


// ===================== FUNÇÃO PRINCIPAL (main) =====================

int main() {
    int quantidade;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    printf("=== SISTEMA DE TERRITORIOS - JOGO WAR (NIVEL MESTRE) ===\n");

    // Pergunta ao usuário quantos territórios deseja cadastrar
    do {
        printf("\nDigite o numero total de territorios (minimo 2): ");
        scanf("%d", &quantidade);
        if (quantidade < 2) {
            printf("Quantidade invalida! E necessario pelo menos 2 territorios.\n");
        }
    } while (quantidade < 2);

    // Alocacao dinamica do mapa de territorios
    Territorio *mapa = (Territorio *) malloc(quantidade * sizeof(Territorio));
    if (mapa == NULL) {
        printf("Erro ao alocar memoria para os territorios.\n");
        return 1;
    }

    // Cadastro dos territórios
    cadastrarTerritorios(mapa, quantidade);

    // ===================== SISTEMA DE MISSOES =====================

    // Vetor de missoes pre-definidas (strings literais)
    char *missoes[] = {
        "Conquistar 3territorios seguidos com a sua cor.",
        "Dominar (dominar) a maioria dos territorios do mapa.",
        "Conquistar 3territorios consecutivos na mesma regiao.",
        "Dominar (dominar) todos os territorios de uma cor inimiga.",
        "Conquistar 3territorios e mante-los por um turno."
    };
    int totalMissoes = sizeof(missoes) / sizeof(missoes[0]);

    // Vamos considerar DOIS jogadores, cada um com uma cor principal.
    // Para simplificar, vamos supor:
    // Jogador 1: cor "vermelho"
    // Jogador 2: cor "azul"
    const char corJogador1[] = "vermelho";
    const char corJogador2[] = "azul";

    // Alocar dinamicamente espaço para as missoes de cada jogador
    char *missaoJogador1 = (char *) malloc(200 * sizeof(char));
    char *missaoJogador2 = (char *) malloc(200 * sizeof(char));

    if (missaoJogador1 == NULL || missaoJogador2 == NULL) {
        printf("Erro ao alocar memoria para as missoes dos jogadores.\n");
        liberarMemoria(mapa, missaoJogador1, missaoJogador2);
        return 1;
    }

    // Atribuir missões aleatórias a cada jogador
    atribuirMissao(missaoJogador1, missoes, totalMissoes);
    atribuirMissao(missaoJogador2, missoes, totalMissoes);

    // Exibir a missão de cada jogador apenas uma vez (no início)
    exibirMissao("JOGADOR 1 (cor vermelho)", missaoJogador1);
    exibirMissao("JOGADOR 2 (cor azul)", missaoJogador2);

    // Mostrar o mapa inicial
    exibirTerritorios(mapa, quantidade);

    // ===================== LOOP PRINCIPAL DO JOGO =====================

    int opcao;
    int venceu = 0; // 0 = ninguem venceu ainda, 1 = alguem venceu

    do {
        printf("=== MENU DE ACOES ===\n");
        printf("1 - Realizar um ataque\n");
        printf("2 - Exibir territorios\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            int idxAtacante, idxDefensor;

            exibirTerritorios(mapa, quantidade);

            printf("Digite o numero do territorio ATACANTE: ");
            scanf("%d", &idxAtacante);
            printf("Digite o numero do territorio DEFENSOR: ");
            scanf("%d", &idxDefensor);

            idxAtacante--;
            idxDefensor--;

            if (idxAtacante < 0 || idxAtacante >= quantidade ||
                idxDefensor < 0 || idxDefensor >= quantidade) {
                printf("\n[ERRO] Indice de territorio invalido!\n");
                continue;
            }

            if (idxAtacante == idxDefensor) {
                printf("\n[ERRO] Um territorio nao pode atacar a si mesmo!\n");
                continue;
            }

            // Validar que o ataque e sempre contra territorio inimigo
            if (strcmp(mapa[idxAtacante].cor, mapa[idxDefensor].cor) == 0) {
                printf("\n[ERRO] Nao e permitido atacar um territorio da mesma cor!\n");
                continue;
            }

            // Executa o ataque
            atacar(&mapa[idxAtacante], &mapa[idxDefensor]);

            // Exibe o mapa apos o ataque
            exibirTerritorios(mapa, quantidade);

            // Verificacao silenciosa das missoes ao final do "turno"
            if (verificarMissao(missaoJogador1, mapa, quantidade, corJogador1)) {
                printf("\n=== O JOGADOR 1 CUMPRIU SUA MISSAO! ===\n");
                printf("Missao: %s\n", missaoJogador1);
                printf("JOGADOR 1 VENCEU O JOGO!\n");
                venceu = 1;
            } else if (verificarMissao(missaoJogador2, mapa, quantidade, corJogador2)) {
                printf("\n=== O JOGADOR 2 CUMPRIU SUA MISSAO! ===\n");
                printf("Missao: %s\n", missaoJogador2);
                printf("JOGADOR 2 VENCEU O JOGO!\n");
                venceu = 1;
            }

            if (venceu) {
                printf("\nFim de jogo!\n");
                break;
            }

        } else if (opcao == 2) {
            exibirTerritorios(mapa, quantidade);

        } else if (opcao == 0) {
            printf("\nSaindo do sistema...\n");

        } else {
            printf("\nOpcao invalida! Tente novamente.\n");
        }

    } while (opcao != 0);

    // Libera toda a memoria dinamicamente alocada
    liberarMemoria(mapa, missaoJogador1, missaoJogador2);

    return 0;
}
