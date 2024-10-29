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

void adicionarProduto(Produto **produtos, int *totalProdutos) {
    if (*totalProdutos >= maximo_produtos) {
        printf("Limite de produtos atingido.\n");
        return;
    }

    Produto novoProduto;
    printf("Nome do produto: ");
    fgets(novoProduto.nome, sizeof(novoProduto.nome), stdin);
    novoProduto.nome[strcspn(novoProduto.nome, "\n")] = 0;

    printf("Preco de custo do produto: ");
    if (scanf("%f", &novoProduto.precoCusto) != 1 || novoProduto.precoCusto < 0) {
        printf("Preco de custo invalido.\n");
        return;
    }

    printf("Preco de venda do produto: ");
    if (scanf("%f", &novoProduto.preco) != 1 || novoProduto.preco < novoProduto.precoCusto) {
        printf("Preco de venda invalido. Deve ser maior ou igual ao preco de custo.\n");
        return;
    }

    printf("Quantidade do produto: ");
    if (scanf("%d", &novoProduto.quantidade) != 1 || novoProduto.quantidade < 0) {
        printf("Quantidade invalida.\n");
        return;
    }
    getchar(); 

    printf("Categoria do produto: ");
    fgets(novoProduto.categoria, sizeof(novoProduto.categoria), stdin);
    novoProduto.categoria[strcspn(novoProduto.categoria, "\n")] = 0;

    (*produtos)[*totalProdutos] = novoProduto;
    (*totalProdutos)++;
    registrarHistoricoPreco(novoProduto);
    printf("Produto adicionado com sucesso!\n");
}