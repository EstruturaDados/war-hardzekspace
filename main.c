#include <stdio.h>
#include <string.h>

// Definição da struct Territorio
// Esta estrutura agrupa informações relacionadas a um território no jogo War
// - nome: nome do território (máximo 30 caracteres)
// - cor: cor do exército que controla o território (máximo 10 caracteres)
// - tropas: quantidade de tropas estacionadas no território
struct Territorio {
    char nome[30];  // Nome do território
    char cor[10];   // Cor do exército (ex: "vermelho", "azul")
    int tropas;     // Número de tropas no território
};

int main() {
    // Declaração do vetor de structs para armazenar 5 territórios
    // Este array terá capacidade fixa para 5 elementos do tipo Territorio
    struct Territorio territorios[5];
    
    // Variáveis auxiliares para controle do loop
    int i;
    
    // Mensagem de boas-vindas e explicação do sistema
    printf("=== SISTEMA DE CADASTRO DE TERRITORIOS - JOGO WAR ===\n");
    printf("Você cadastrará 5 territórios com nome, cor do exército e número de tropas.\n\n");
    
    // Laço for para cadastro dos 5 territórios
    // Este loop itera 5 vezes, solicitando dados para cada território
    for (i = 0; i < 5; i++) {
        printf("=== CADASTRO DO TERRITORIO %d ===\n", i + 1);
        
        // Solicitação e leitura do nome do território
        // Usamos scanf com especificador %s para ler strings sem espaços
        printf("Digite o nome do territorio (max 29 caracteres): ");
        scanf(" %29[^\n]", territorios[i].nome);  // %29[^\n] lê até 29 chars ou nova linha
        // O espaço antes do %29 limpa qualquer caractere de nova linha residual
        
        // Solicitação e leitura da cor do exército
        printf("Digite a cor do exercito (ex: vermelho, azul, verde): ");
        scanf(" %9s", territorios[i].cor);  // %9s lê até 9 caracteres para cor
        
        // Solicitação e leitura do número de tropas
        // Validação básica para garantir que o número seja positivo
        do {
            printf("Digite o numero de tropas (mínimo 1): ");
            scanf("%d", &territorios[i].tropas);
        } while (territorios[i].tropas < 1);
        
        // Limpeza do buffer de entrada para evitar problemas com próxima leitura
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        printf("Territorio %d cadastrado com sucesso!\n\n", i + 1);
    }
    
    // Exibição de todos os territórios cadastrados
    // Este loop percorre o vetor e exibe as informações de cada território
    printf("=== LISTA DE TERRITORIOS CADASTRADOS ===\n");
    printf("Total de territorios: 5\n");
    printf("----------------------------------------\n");
    
    for (i = 0; i < 5; i++) {
        // Formatação clara para exibição dos dados
        // Utilizamos printf com especificadores para alinhamento e clareza
        printf("TERRITORIO %d:\n", i + 1);
        printf("  Nome: %s\n", territorios[i].nome);
        printf("  Cor do Exercito: %s\n", territorios[i].cor);
        printf("  Tropas: %d\n", territorios[i].tropas);
        printf("----------------------------------------\n");
    }
    
    // Mensagem final confirmando conclusão do cadastro
    printf("\n=== CADASTRO CONCLUIDO ===\n");
    printf("Todos os 5 territorios foram cadastrados e exibidos com sucesso!\n");
    
    return 0;
}
