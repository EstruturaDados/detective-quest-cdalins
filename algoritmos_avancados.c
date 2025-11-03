#include <stdio.h>
#include <stdlib.h>

// Camila Lins, curso de ADS, Estácio, 2025.2.

// Tamanho do maior caminho que o usuário pode percorrer
#define CAMINHO_MAXIMO 15

// Definição da struct Sala
// Contém o nome, o cômoda da esquerda, e o cômodo da direita
typedef struct Sala {
    char nome[64];
    struct Sala *esquerda;
    struct Sala *direita;
} Sala;

// Função para criação das salas
Sala* criarSala(char *nome) {
    Sala* s = (Sala*) malloc(sizeof(Sala));

    if (!s) {
        printf("\n! Sem memória. :(\n\n"); exit(1);
    }

    int i=0;
    while (nome[i] != '\0' && i < 63) {
        s->nome[i]=nome[i]; i++;
    }

    s->nome[i]='\0';
    s->esquerda = s->direita = NULL;
    
    return s;
}

// Liberando a memória
// Usando pós-ordem: libera sub-árvores antes do nó atual
void liberarMapa(Sala* r) {
    if (!r) return;
    liberarMapa(r->esquerda);
    liberarMapa(r->direita);
    free(r);
}

// Explorando a mansão
void explorarSalas(Sala* atual) {
    char opcao;

    // 'caminho' guarda o percurso do jogador (até o máximo definido)
    Sala* caminho[CAMINHO_MAXIMO];

    int passos = 0;

    caminho[passos++] = atual;

    printf("• Você chegou no %s\n", atual->nome);

    while (1) {
        // Quando o usuário chegar em uma folha
        if (!atual->esquerda && !atual->direita) {
            printf("\n✦ Cômodo sem saída – fim da exploração!\n");

            // Exibe o percurso completo
            printf("✶ Caminho percorrido:");
            for (int i = 0; i < passos; i++) {
                printf(" %s", caminho[i]->nome);
                if (i < passos - 1) printf(" →");
            }
            printf("\n\nAté a próxima!\n\n");

            break;
        }

        // Menu de opções
        printf("\n✶ Escolha para onde ir:\n");

        if (atual->esquerda) printf("[e] Esquerda → %s\n", atual->esquerda->nome);
        if (atual->direita) printf("[d] Direita  → %s\n", atual->direita->nome);
        printf("[s] Sair da exploração\n\n→ ");

        // Prevenção de erros e loops
        if (scanf(" %c", &opcao) != 1) {
            printf("\n\n! Ops, tente novamente.\n\n");
            return;
        }

        if (opcao == 's') {
            printf("\nSaindo da mansão...\nAté a próxima!\n\n");
            break;

        } else if (opcao == 'e') {
            if (atual->esquerda) {
                atual = atual->esquerda;
                caminho[passos++] = atual;

                printf("\n• Você entrou em: %s\n", atual->nome);
            } else {
                printf("\n! Não existe mais caminho à esquerda.\n");
            }

        } else if (opcao == 'd') {
            if (atual->direita) {
                atual = atual->direita;
                caminho[passos++] = atual;
                printf("\n• Você entrou em: %s\n", atual->nome);
            } else {
                printf("\n! Não existe mais caminho à direita.\n");
            }

        } else {
            printf("\n! Opção inválida. Use apenas [e], [d] ou [s].\n");
        }
    }
}

int main(void) {
    // Criando o mapa da mansão
    Sala* hall = criarSala("Hall de Entrada");
    Sala* estar = criarSala("Sala de Estar");
    Sala* corredor = criarSala("Corredor");
    Sala* biblioteca = criarSala("Biblioteca");
    Sala* cozinha = criarSala("Cozinha");
    Sala* oficina = criarSala("Oficina");
    Sala* jardim = criarSala("Jardim");
    Sala* escritorio = criarSala("Escritório");
    Sala* quarto = criarSala("Quarto");
    Sala* despensa = criarSala("Despensa");
    Sala* adega = criarSala("Adega");
    Sala* varanda = criarSala("Varanda");
    Sala* closet = criarSala("Closet");
    Sala* banheiro = criarSala("Banheiro");
    Sala* garagem = criarSala("Garagem");
    Sala* porao = criarSala("Porão");
    Sala* entrada = criarSala("Entrada Secreta");
    Sala* sotao = criarSala("Sotão");

    // Associando os cômodos
    hall->esquerda = estar;
    hall->direita = corredor;
    
    estar->esquerda = biblioteca;
    estar->direita = cozinha;
    
    corredor->esquerda = oficina;
    corredor->direita = jardim;
    
    biblioteca->esquerda = escritorio;
    biblioteca->direita = quarto;
    
    cozinha->direita = despensa;
    
    escritorio->direita = sotao;
    
    quarto->esquerda = closet;
    quarto->direita = banheiro;
    
    oficina->esquerda = garagem;
    
    jardim->esquerda = adega;
    jardim->direita = varanda;
    
    adega->esquerda = porao;
    
    porao->direita = entrada;

    printf("\n✧✦☆★ Detective Quest ★☆✦✧\n☆ Explorando a mansão ☆\n\n");
    
    explorarSalas(hall);
    liberarMapa(hall);

    return 0;
}
