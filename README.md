Projeto realizado em C, com os integrantes Wellington de Menezes Paim (RA: 24.124.083-7), Luan Garcia Candido (RA: 24.124.019-1), Yuri Lucas Oishi (RA: 24.124.082-9) contando com o auxilio do git e git hub.

Sistema de Gerenciamento de Inventário de Loja
Este é um programa desenvolvido em C que permite o gerenciamento de inventário de uma loja. Ele oferece funcionalidades como adicionar, listar, vender, buscar, remover e atualizar produtos, além de gerar relatórios de estoque e registrar lucros por venda.

Funcionalidades
Adicionar Produto: Permite cadastrar novos produtos no inventário, registrando nome, preço de custo, preço de venda, quantidade e categoria. Também registra o histórico de preços no arquivo historico_precos.txt.

Listar Produtos por Categoria: Lista todos os produtos de uma categoria especificada, mostrando o nome, preço e quantidade de cada produto.

Vender Produto: Realiza uma venda para um produto específico, subtraindo a quantidade vendida do estoque e calculando o lucro da transação. As informações de cada venda são registradas para o cálculo de lucro diário.

Gerar Relatório de Estoque: Gera um relatório completo do inventário em um arquivo de texto (relatorio_estoque.txt), incluindo detalhes de cada produto como nome, preço de custo, preço de venda, quantidade e categoria.

Buscar Produto: Busca um produto específico pelo nome e exibe suas informações, incluindo preço, quantidade e categoria.

Remover Produto: Permite remover um produto do inventário.

Atualizar Produto: Atualiza informações de um produto existente, como preço de custo, preço de venda e quantidade.

Controle de Lucro Diário: Exibe o total de lucro gerado pelas vendas realizadas no dia, além de uma lista de produtos vendidos, lucro e data da venda.

Cadastrar Fornecedor: Permite cadastrar um fornecedor, armazenando o nome e o contato.

Salvar e Carregar Inventário: O inventário é salvo em um arquivo binário (produtos.bin) e carregado ao iniciar o programa, permitindo persistência dos dados.
