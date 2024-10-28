Sistema de Gerenciamento de Inventário de Loja

Descrição do Projeto
Este é um sistema de gerenciamento de inventário desenvolvido em C que permite a gestão de produtos em uma loja física e on-line, ele gerencia sua loja por categoria do seu produto, fornecendo informaçôes de quanto está ganhando em um certo produto. O sistema inclui funcionalidades para adicionar, listar produtos, vender, fornecer relatorio de estoque, remover, buscar e atualizar produtos, além de e controlar lucros diários das suas vendas. 

O projeto foi desenvolvido como parte dos estudos dos alunos:
Wellington de Menezes Paim (RA: 24.124.083-7)
Luan Garcia Candido (RA: 24.124.019-1)
Yuri Lucas Oishi (RA: 24.124.082-9)

PATH DO PROJETO

O programa solicitará ao usuário seu nome e seu contato, para um melhor entendimento do seus dados da sua loja.

Menu de Operações
Após iniciar o programa, o usuário pode selecionar uma das seguintes opções:

Adicionar Produto
Listar Produtos por Categoria
Vender Produto
Gerar Relatório de Estoque
Buscar Produto
Remover Produto
Atualizar Produto
Controle de Lucro Diário
Sair

Estrutura de Arquivos
O sistema armazena dados de produtos em um arquivo binário (produtos.bin) para persistência do inventário entre execuções. Ele também gera um arquivo de texto (historico_precos.txt) para registrar o histórico de preços dos produtos e um arquivo de relatório (relatorio_estoque.txt) para o relatório de estoque.

Funcionalidades
O sistema é dividido nas seguintes funcionalidades:

Cadastro de Produto: Permite adicionar produtos ao inventário, incluindo informações como nome, preço de custo, preço de venda, quantidade e categoria.

Listagem por Categoria: Lista todos os produtos de uma determinada categoria.
EXEMPLO - nome: bike, preço de custo: 200, preço de venda: 399, quantidade: 5, categoria: veiculo; Nessa função se você colocar veiculo aparece todos os dados da bike ou de outros produtos que colocou nessa categoria.

Venda de Produto: Registra a venda de um produto, atualiza o estoque e calcula o lucro.

Relatório de Estoque: Gera um relatório de todos os produtos no estoque, com informações detalhadas.

Busca de Produto: Permite buscar um produto específico pelo nome.

Remoção de Produto: Remove um produto do inventário.

Atualização de Produto: Atualiza as informações de um produto existente, como preço e quantidade.

Controle de Lucro Diário: Calcula o lucro diário com base nas vendas realizadas.

Compilação do Código
Para compilar o código, utilize um compilador C, como o GCC. 

Execute o seguinte comando no terminal:
bash
Copiar código
gcc -o inventario inventario.c
Executar o Programa
Após a compilação, execute o programa:

bash
Copiar código
./inventario

Requisitos
Compilador C (por exemplo, GCC)
Ambiente de execução para programas C
Contato
Para dúvidas ou sugestões, entre em contato pelos e-mails:

Contato Para dúvidas ou sugestões, entre em contato pelo e-mail: luanccandi@gmail.com / yurilucasoishi@gmail.com / tonmenezes21@gmail.com
