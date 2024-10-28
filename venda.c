
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

void venderProduto(Produto *produtos, int totalProdutos, Venda *vendas, int *totalVendas) {
    char nomeProduto[50];
    printf("Nome do produto a ser vendido: ");
    fgets(nomeProduto, sizeof(nomeProduto), stdin);
    nomeProduto[strcspn(nomeProduto, "\n")] = 0;

    for (int i = 0; i < totalProdutos; i++) {
        if (strcmp(produtos[i].nome, nomeProduto) == 0) {
            if (produtos[i].quantidade <= 0) {
                printf("Produto fora de estoque!\n");
                return;
            }

            float quantidade;
            printf("Quantidade a ser vendida do seu estoque: ");
            if (scanf("%f", &quantidade) != 1 || quantidade <= 0 || quantidade > produtos[i].quantidade) {
                printf("Quantidade invalida.\n");
                return;
            }
            getchar();  

            produtos[i].quantidade -= quantidade;

            // calcular o lucro
            float lucro = (produtos[i].preco - produtos[i].precoCusto) * quantidade;

            // registrar a venda
            strcpy(vendas[*totalVendas].produtoNome, produtos[i].nome);
            vendas[*totalVendas].lucro = lucro;

            // data atual
            time_t t = time(NULL);
            struct tm *tm_info = localtime(&t);
            strftime(vendas[*totalVendas].data, sizeof(vendas[*totalVendas].data), "%d/%m/%Y", tm_info);

            (*totalVendas)++;
            printf("Venda realizada com sucesso!\n");
            printf("Lucro da venda: R$ %.2f\n", lucro);
            return;
        }
    }

    printf("Produto nao encontrado!\n");
}