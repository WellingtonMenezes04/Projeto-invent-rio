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

// funcao para cadastrar fornecedores
void cadastrarFornecedor(Fornecedor **fornecedores, int *totalFornecedores) {
    if (*totalFornecedores >= maximo_fornecedores) {
        printf("Limite de fornecedores atingido.\n");
        return;
    }

    Fornecedor novoFornecedor;
    printf("Nome do fornecedor: ");
    fgets(novoFornecedor.nome, sizeof(novoFornecedor.nome), stdin);
    novoFornecedor.nome[strcspn(novoFornecedor.nome, "\n")] = 0;

    printf("Contato do fornecedor: ");
    fgets(novoFornecedor.contato, sizeof(novoFornecedor.contato), stdin);
    novoFornecedor.contato[strcspn(novoFornecedor.contato, "\n")] = 0;

    (*fornecedores)[*totalFornecedores] = novoFornecedor;
    (*totalFornecedores)++;
    printf("Fornecedor cadastrado com sucesso!\n");
}

// funcao para registrar histórico de preços
void registrarHistoricoPreco(Produto produto) {
    FILE *historico = fopen("historico_precos.txt", "a");
    if (historico == NULL) {
        printf("Erro ao abrir o arquivo de historico de precos.\n");
        return;
    }

    time_t t = time(NULL);
    struct tm *tm_info = localtime(&t);
    char data[20];
    strftime(data, sizeof(data), "%Y-%m-%d", tm_info);

    fprintf(historico, "Produto: %s - Preco de custo: %.2f, Preco de venda: %.2f - Data: %s\n",
            produto.nome, produto.precoCusto, produto.preco, data);

    fclose(historico);
}

// funcao para listar produtos por categoria
void listarProdutosPorCategoria(Produto *produtos, int totalProdutos) {
    char categoria[30];
    printf("Digite a categoria: ");
    fgets(categoria, sizeof(categoria), stdin);
    categoria[strcspn(categoria, "\n")] = 0;

    printf("\nProdutos da categoria: %s\n", categoria);
    for (int i = 0; i < totalProdutos; i++) {
        if (strcmp(produtos[i].categoria, categoria) == 0) {
            printf("Produto %d: %s\n", i + 1, produtos[i].nome);
            printf("Preco: R$ %.2f\n", produtos[i].preco);
            printf("Quantidade: %d\n", produtos[i].quantidade);
            printf("\n");
        }
    }
    printf("Fim da lista de produtos da categoria: %s\n", categoria);
}

// funcao para adicionar um produto
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

void salvarProdutosBinario(Produto *produtos, int totalProdutos) {
    FILE *arquivo = fopen("produtos.bin", "wb");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para salvar produtos.\n"); 
        return;
    }

    fwrite(produtos, sizeof(Produto), totalProdutos, arquivo);
    fclose(arquivo);
}

void carregarProdutosBinario(Produto **produtos, int *totalProdutos) {
    FILE *arquivo = fopen("produtos.bin", "rb");
    if (arquivo == NULL) {
        printf("-------------------------------------------------------------------\n");
        printf("Iniciando um novo inventario para uma melhor organizacao de vendas.\n");
        printf("-------------------------------------------------------------------\n");
        return;
    }

    *totalProdutos = fread(*produtos, sizeof(Produto), maximo_produtos, arquivo);
    fclose(arquivo);
}

// funcao para vender um produto
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

void controleLucroDiario(Venda *vendas, int totalVendas) {
    float lucroTotal = 0;
    // listar produtos vendidos no dia
    printf("\nProdutos vendidos:\n");
    for (int i = 0; i < totalVendas; i++) {
        printf("--------------------------------------------------\n");
        printf("Produto: %s, Lucro: R$ %.2f, Data: %s\n", vendas[i].produtoNome, vendas[i].lucro, vendas[i].data);
        printf("--------------------------------------------------\n");
        lucroTotal += vendas[i].lucro; 
    }
    // mostrar lucro diario de vendas 
    printf("Lucro total diario: R$ %.2f\n", lucroTotal);
}

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