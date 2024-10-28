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

int main() {
    Produto *produtos = malloc(maximo_produtos * sizeof(Produto));
    Fornecedor *fornecedores = malloc(maximo_fornecedores * sizeof(Fornecedor));
    Venda *vendas = malloc(maximo_vendas * sizeof(Venda));
    int totalProdutos = 0;
    int totalFornecedores = 0;
    int totalVendas = 0;
    int opcao;

    carregarProdutosBinario(&produtos, &totalProdutos);

    
    cadastrarFornecedor(&fornecedores, &totalFornecedores);
    printf("--------------------------------------------------\n");

    do {
        printf("\nSistema de Gerenciamento de Inventario de Loja\n");
        printf("1. Adicionar Produto\n");
        printf("2. Listar Produtos por Categoria\n");  
        printf("3. Vender Produto\n");
        printf("4. Gerar Relatorio de Estoque\n");
        printf("5. Buscar Produto\n");
        printf("6. Remover Produto\n");
        printf("7. Atualizar Produto\n");
        printf("8. Controle de Lucro Diario\n");
        printf("9. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        getchar();  

        switch (opcao) {
            case 1:
                adicionarProduto(&produtos, &totalProdutos);
                salvarProdutosBinario(produtos, totalProdutos);
                break;
            case 2:
                listarProdutosPorCategoria(produtos, totalProdutos);  
                break;
            case 3:
                venderProduto(produtos, totalProdutos, vendas, &totalVendas);
                salvarProdutosBinario(produtos, totalProdutos);
                break;
            case 4:
                gerarRelatorioEstoque(produtos, totalProdutos);
                break;
            case 5:
                buscarProduto(produtos, totalProdutos);
                break;
            case 6:
                removerProduto(produtos, &totalProdutos);
                salvarProdutosBinario(produtos, totalProdutos);
                break;
            case 7:
                atualizarProduto(produtos, totalProdutos);
                salvarProdutosBinario(produtos, totalProdutos);
                break;
            case 8:
                controleLucroDiario(vendas, totalVendas);
                break;
            case 9:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (opcao != 9);

    free(produtos);
    free(fornecedores);
    free(vendas);
    return 0;
}

