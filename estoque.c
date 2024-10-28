#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define maximo_produtos 100
#define maximo_fornecedores 50
#define maximo_vendas 100
#define maximo_categoria 5

typedef struct {
    char nome[50];
    float preco;
    float precoCusto;
    int quantidade;
    char categoria[30];
} Produto;

typedef struct {
    char nome[50];
    char contato[50];
} Fornecedor;

typedef struct {
    char produtoNome[50];
    float lucro;
    char data[11];  
} Venda;

// funcoes para manipulação do inventário
void adicionarProduto(Produto **produtos, int *totalProdutos);
void salvarProdutosBinario(Produto *produtos, int totalProdutos);
void carregarProdutosBinario(Produto **produtos, int *totalProdutos);
void listarProdutosPorCategoria(Produto *produtos, int totalProdutos);
void venderProduto(Produto *produtos, int totalProdutos, Venda *vendas, int *totalVendas);
void gerarRelatorioEstoque(Produto *produtos, int totalProdutos);
void buscarProduto(Produto *produtos, int totalProdutos);
void removerProduto(Produto *produtos, int *totalProdutos);
void atualizarProduto(Produto *produtos, int totalProdutos);
void cadastrarFornecedor(Fornecedor **fornecedores, int *totalFornecedores);
void registrarHistoricoPreco(Produto produto);
void controleLucroDiario(Venda *vendas, int totalVendas);
void listarPorCategoria(Produto *produtos, int totalProdutos, char *categoria);

void gerarRelatorioEstoque(Produto *produtos, int totalProdutos) {
    FILE *relatorioArquivo = fopen("relatorio_estoque.txt", "w");
    if (relatorioArquivo == NULL) {
        printf("Erro ao abrir o arquivo de relatório.\n");
        return;
    }

    fprintf(relatorioArquivo, "Relatorio de Estoque:\n");
    fprintf(relatorioArquivo, "---------------------------------\n");
    for (int i = 0; i < totalProdutos; i++) {
        fprintf(relatorioArquivo, "Produto %d: %s\n", i + 1, produtos[i].nome);
        fprintf(relatorioArquivo, "Preco: R$ %.2f\n", produtos[i].preco);
        fprintf(relatorioArquivo, "Preco de Custo: R$ %.2f\n", produtos[i].precoCusto);
        fprintf(relatorioArquivo, "Quantidade: %d\n", produtos[i].quantidade);
        fprintf(relatorioArquivo, "Categoria: %s\n", produtos[i].categoria);
        fprintf(relatorioArquivo, "---------------------------------\n");
    }

    fclose(relatorioArquivo);
    printf("Relatorio de estoque gerado com sucesso!\n");
}

void buscarProduto(Produto *produtos, int totalProdutos) {
    char nomeProduto[50];
    printf("Digite o nome do produto: ");
    fgets(nomeProduto, sizeof(nomeProduto), stdin);
    nomeProduto[strcspn(nomeProduto, "\n")] = 0;

    for (int i = 0; i < totalProdutos; i++) {
        if (strcmp(produtos[i].nome, nomeProduto) == 0) {
            printf("Produto encontrado:\n");
            printf("Nome: %s\n", produtos[i].nome);
            printf("Preço: R$ %.2f\n", produtos[i].preco);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("Categoria: %s\n", produtos[i].categoria);
            return;
        }
    }
    printf("Produto nao encontrado!\n");
}

void removerProduto(Produto *produtos, int *totalProdutos) {
    char nomeProduto[50];
    printf("Digite o nome do produto a ser removido: ");
    fgets(nomeProduto, sizeof(nomeProduto), stdin);
    nomeProduto[strcspn(nomeProduto, "\n")] = 0;

    for (int i = 0; i < *totalProdutos; i++) {
        if (strcmp(produtos[i].nome, nomeProduto) == 0) {
            for (int j = i; j < *totalProdutos - 1; j++) {
                produtos[j] = produtos[j + 1];
            }
            (*totalProdutos)--;
            printf("Produto removido com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado!\n");
}

void atualizarProduto(Produto *produtos, int totalProdutos) {
    char nomeProduto[50];
    printf("Digite o nome do produto a ser atualizado: ");
    fgets(nomeProduto, sizeof(nomeProduto), stdin);
    nomeProduto[strcspn(nomeProduto, "\n")] = 0;

    for (int i = 0; i < totalProdutos; i++) {
        if (strcmp(produtos[i].nome, nomeProduto) == 0) {
            printf("Novo preco de custo: ");
            scanf("%f", &produtos[i].precoCusto);
            printf("Novo preco de venda: ");
            scanf("%f", &produtos[i].preco);
            printf("Nova quantidade: ");
            scanf("%d", &produtos[i].quantidade);
            getchar();  
            printf("Produto atualizado com sucesso!\n");
            return;
        }
    }
    printf("Produto nao encontrado!\n");
}