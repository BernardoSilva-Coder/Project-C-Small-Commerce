// Projecto C++ Sketch inicial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string> // Premite usar o to_string
#include <ctime> // Acrescentar data e hora ao talao
#include <locale> // Usar caracteres como o c cedilhado e assentos e o simbolo do euro
#include <sstream> //Para Puder Usar ostringstream
#include <cstdlib> // Para poder usar o rand() no sorteio
#include <cctype> // Para usar isalpha() na validacao de letras

using namespace std;

//Variaveis Constantes Globais , quando precisamos das variaveis em varias funcoes enunciamos antes para todas poderem ter acesso.
int numMaxProd = 50;
int colunas = 4;
int totalProdutos = 4;
const double IVA = 1.23;
const double margemLucro = 1.30;
int qntdVenda;
int numeroFatura = 1;
int numeroCliente = 1;
int sorteioChance = 10;

// Matriz Para stock de 50 items diferentes ( ID: 0 | Nome: 1 | Quantidade : 2 | Preco de custo : 3)
string** stock = new string * [numMaxProd];
//Matriz para o carrinho
string** carrinho = new string * [50];
int totalCarrinho = 0;

void inicializarstock() {
    for (int i = 0; i < numMaxProd; i++)
    {
        stock[i] = new string[colunas];
    }
    //Primeiro Produto
    stock[0][0] = "1";
    stock[0][1] = "Pao";
    stock[0][2] = "100";
    stock[0][3] = "0.04";
    //Segundo Produto
    stock[1][0] = "2";
    stock[1][1] = "Agua";
    stock[1][2] = "150";
    stock[1][3] = "1.00";
    //Terceiro Produto
    stock[2][0] = "3";
    stock[2][1] = "Atum";
    stock[2][2] = "100";
    stock[2][3] = "0.50";
    //Quarto Produto
    stock[3][0] = "4";
    stock[3][1] = "Milho";
    stock[3][2] = "100";
    stock[3][3] = "0.40";
}

// Função para validar se o nome contém apenas letras (ou espaços)
bool validarNome(const string& nome) {
    for (char c : nome) {
        if (!(isalpha(c) || c == ' ')) { // Permite apenas letras e espaços
            return false;  // Se encontrar algum caractere não alfabético ou não for espaço, retorna false
        }
    }
    return true; // Se todos os caracteres são letras ou espaços, retorna true
}

// Função para validar se a quantidade é um número inteiro positivo
bool validarQuantidade(const string& quantidade) {
    // Verifica se a quantidade contém apenas números
    for (char c : quantidade) {
        if (!isdigit(c)) {  // Verifica se o caractere não é um dígito
            return false; // Se encontrar qualquer caractere que não seja um número, retorna falso
        }
    }

    int qnt = stoi(quantidade);  // Converte a string para inteiro

    // Verifica se o número é positivo
    return qnt > 0;
}


// Função para validar se o preço é um número decimal positivo (permitindo até duas casas decimais)
bool validarPreco(const string& preco) {
    int pontoCount = 0; // Contador para verificar se há mais de um ponto decimal
    int casasDecimais = 0; // Contador para contar as casas decimais

    // Itera sobre cada caractere da string
    for (size_t i = 0; i < preco.length(); ++i) {
        char c = preco[i];

        // Verifica se o caractere é um dígito
        if (isdigit(c)) {
            continue;
        }
        // Verifica se o caractere é um ponto decimal e se já não existe outro
        else if (c == '.' && pontoCount == 0) {
            pontoCount++;
            continue;
        }
        // Se encontrar qualquer caractere diferente de número ou ponto, retorna false
        else {
            return false;
        }

        // Se for um ponto decimal, contamos as casas decimais após ele
        if (c == '.' && i + 1 < preco.length()) {
            casasDecimais = 0; // Reinicia as casas decimais para verificar a parte depois do ponto
        }

        // Verifica o número de casas decimais
        if (pontoCount == 1 && i > 0 && preco[i - 1] == '.') {
            casasDecimais++;
            if (casasDecimais > 2) {
                return false; // Se houver mais de duas casas decimais, retorna false
            }
        }
    }

    // Agora tenta converter a string para um número decimal (double)
    double valorPreco = stod(preco); // Converte para número

    // Verifica se o número é positivo
    return valorPreco > 0;
}

// Função para validar se o ID é um número inteiro e não contém ponto decimal
bool validarID(const string& idStr) {
    // Verifica se o ID contém ponto decimal
    if (idStr.find('.') != string::npos) {
        return false;  // Se houver ponto decimal, retorna false
    }

    // Verifica se o ID contém apenas números
    for (char c : idStr) {
        if (!isdigit(c) && c != '-') { // Permite também o sinal de negativo
            return false;  // Se encontrar um caractere não numérico, retorna false
        }
    }

    return true; // Se todas as verificações passarem, retorna true
}


//Criacao da funcao Listar Produtos
void listarProdutos(string** stock) {

    // Imprimir a matriz, para listar produtos 
    cout << endl << "Lista de Produtos:" << endl;
    cout << "ID\tNome\tQnt\tPreco de Custo" << endl;
    cout << fixed << setprecision(2);
    for (int i = 0; i < totalProdutos; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            cout << stock[i][j] << fixed << setprecision(2) << "\t";
        }

        cout << endl;
    }
}
//Criacao da Funcao Adicionar Produto
void adicionarProdutos(string** stock) {
    // Variáveis
    int numeroProdAdd, idProd = 1;


    // Quantos produtos vai adicionar?
    cout << "Quantos produtos vai desejar adicionar? " << endl;

    while (true) {
        cin >> numeroProdAdd;

        // Verificar se a entrada é válida (só aceita números inteiros)
        if (cin.fail()) {
            cin.clear(); // Limpa o erro de fluxo
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpa a entrada
            cout << "Por favor, insira um numero valido!" << endl;
        }
        else {
            break; // Sai do loop quando a entrada for válida
        }
    }

    if (totalProdutos + numeroProdAdd < numMaxProd)
    {
        for (int i = 0; i < numeroProdAdd; i++)
        {

            stock[totalProdutos][0] = to_string(totalProdutos + 1); // ID |Converte em string usando a biblioteca String, torna o id automatico fazendo + 1.

            string nomeProduto;
            cout << "Nome do Produto : " << endl;// Nome
            while (true) {
                cin >> nomeProduto;
                if (validarNome(nomeProduto)) {
                    break; // Nome válido, sai do loop
                }
                else {
                    cout << "Por favor, insira apenas letras para o nome do produto: ";
                }
            }
            stock[totalProdutos][1] = nomeProduto; // Atribui o nome validado

            cout << "Quantidade :" << endl;// Quantidade
            while (true) {
                cin >> stock[totalProdutos][2];

                // Verifica se a quantidade é válida (usando a função validarQuantidade)
                if (validarQuantidade(stock[totalProdutos][2])) {
                    break; // Quantidade válida, sai do loop
                }
                else {
                    cout << "Quantidade invalida. Insira um numero positivo: ";
                }
            }

            cout << "Preco de Custo :" << endl;// Preco de Custo
            while (true) {
                cin >> stock[totalProdutos][3];
                if (validarPreco(stock[totalProdutos][3])) {
                    break; // Preço válido
                }
                else {
                    cout << "Preco invalido. Insira um numero maior que 0: ";
                }
            }

            totalProdutos++;
        }


    }
    else {
        cout << "Erro: excede o número máximo de produtos." << endl;
    }
}
void removerProdutos(string** stock) {

    listarProdutos(stock);
    int idProdApg;//Variavel para comparar ID's
    string idProdApgStr;

    cout << "Qual o ID do Produto que quer apagar? ";

    // Valida o ID usando a função validarID
    while (true) {
        cin >> idProdApgStr;

        // Verifica se o ID inserido é válido
        if (!validarID(idProdApgStr)) {
            cout << "Por favor, insira um numero inteiro valido! " << endl;
        }
        else {
            idProdApg = stoi(idProdApgStr); // Converte o ID para inteiro
            break; // Sai do loop quando a entrada for válida
        }
    }

    int index = -1;                             // A Variável index serve para guardar a posição (linha) onde está o produto que tem o ID que o utilizador quer remover.
    for (int i = 0; i < totalProdutos; i++) {
        if (stoi(stock[i][0]) == idProdApg) {   //stoi(stock[i][0]) significa converter a variavel da matriz ID (Coluna 0 que e uma string para Int, de modo a poder ser comparada)
            index = i;                          // Dai aqui a igualarmos a posicao, variavel que nos da a posicao.
            break;                              //Para o ciclo quando encontra e define a variavel index. E avanca para as validacoes em baixo.
        }
    }

    if (index == -1) {
        cout << "ID não encontrado." << endl;
        return;
    }

    // Remover o produto e deslocar os restantes para as posicoes anteriores a elas
    for (int i = index; i < totalProdutos - 1; i++) {
        for (int j = 0; j < colunas; j++) {
            stock[i][j] = stock[i + 1][j];
        }
    }
    for (int i = 0; i < totalProdutos; i++)
    {
        for (int j = 0; j < colunas; j++)
        {
            stock[totalProdutos][j] = "";
        }
    }

    totalProdutos--; // Atualiza o total de Produtos
    cout << "Produto removido com sucesso." << endl;
}
//Criacao da Funcao Inicializar carrinho
void inicializarCarrinho(string** carrinho) {
    for (int i = 0; i < 50; i++) {
        carrinho[i] = new string[5]; // 5 colunas
    }
}

//Criacao da Funcao Adicionar Carrinho
void adicionarCarrinho(string** stock) {

    string idProdStr;
    int idProd;

    if (totalProdutos == 0) //Validacao do Stock
    {
        cout << "Nao Existe Produtos em Stock ";
        return;
    }

    char continuar;
    double totalsemIva = 0;

    do {
        listarProdutos(stock);

        // Procurar produto pelo ID
        int index = -1;

        cout << "Insira o ID do Produto que Pretende Adicionar a Compra : ";
        cin >> idProdStr;

        // Validar o ID inserido usando a função validarID()
        if (!validarID(idProdStr)) {
            cout << "ID invalido!" << endl;
            return;  // Se o ID for inválido, termina a função
        }

        // Converter o ID validado para inteiro
        idProd = stoi(idProdStr);

        for (int i = 0; i < totalProdutos; i++) {
            if (stoi(stock[i][0]) == idProd) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << endl << "ID " << idProd << " nao encontrado." << endl;
            return;
        }
        //Variaveis Para fazer os calculos dos custos
        int quantidadeStock = stoi(stock[index][2]);

        string qntdVendaStr;
        int qntdVenda;

        cout << "Insira a Quantidade do Produto que deseja comprar : ";
        // Validar a quantidade inserida
        while (true) {
            cin >> qntdVendaStr;

            // Usamos a função validarQuantidade() para verificar se a quantidade é válida
            if (!validarQuantidade(qntdVendaStr)) {
                cout << "Quantidade invalida. Insira novamente: ";
            }
            else {
                qntdVenda = stoi(qntdVendaStr);  // Converte a quantidade válida para inteiro
                if (qntdVenda > quantidadeStock) {
                    cout << "Nao ha quantidade suficiente em estoque. Insira uma quantidade menor ou igual a " << quantidadeStock << ": ";
                }
                else {
                    break; // Sai do loop quando a quantidade for válida
                }
            }
        }

        // Calculo do preço
        double precoUnitario = stod(stock[index][3]) * margemLucro;
        double subtotal = precoUnitario * qntdVenda;
        totalsemIva += subtotal;

        // Adicionar à matriz carrinho
        carrinho[totalCarrinho][0] = stock[index][0];            // ID
        carrinho[totalCarrinho][1] = stock[index][1];            // Nome
        carrinho[totalCarrinho][2] = to_string(qntdVenda);       // Quantidade
        carrinho[totalCarrinho][3] = to_string(precoUnitario);   // Preço unitário
        carrinho[totalCarrinho][4] = to_string(subtotal);        // Subtotal

        totalCarrinho++;
        // Atualizar stock
        stock[index][2] = to_string(quantidadeStock - qntdVenda);



        cout << qntdVenda << " unidade do produto " << stock[index][1] << " foi adicionado ao carrinho. Subtotal: " << fixed << setprecision(2) << subtotal << " €" << endl;
        cout << "Deseja continuar a comprar? (s/n): ";
        cin >> continuar;

        while (continuar != 's' && continuar != 'S' && continuar != 'n' && continuar != 'N')
        {
            cout << "Entrada invalida! Por favor, insira 's' para continuar ou 'n' para sair: ";
            cin >> continuar;
        }
    } while (continuar == 's' || continuar == 'S');

}

void removerCarrinho(string** stock, string** carrinho) {
    if (totalCarrinho == 0) {
        cout << "O carrinho está vazio!\n";
        return;
    }

    cout << left << setw(10) << "ID"
        << setw(15) << "Produto"
        << setw(10) << "Qtd"
        << setw(15) << "Preco Unit"
        << setw(10) << "Subtotal" << endl;

    for (int i = 0; i < totalCarrinho; i++) {
        // Verifica se a linha está completamente preenchida antes de imprimir
        bool linhaValida = true;
        for (int j = 0; j < 5; j++) {
            if (carrinho[i][j].empty()) {
                linhaValida = false;
                break;
            }
        }

        if (linhaValida) {
            cout << left << setw(10) << carrinho[i][0]
                << setw(15) << carrinho[i][1]
                << setw(10) << carrinho[i][2]
                << setw(15) << carrinho[i][3]
                << setw(10) << carrinho[i][4] << endl;
        }
    }

   
    int posRemover;
    cout << "Digite o numero do item que deseja remover: ";
    while (true) {
        cin >> posRemover;
        if (cin.fail() || posRemover < 1 || posRemover > totalCarrinho) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Entrada invalida. Tente novamente: ";
        }
        else {
            break;
        }
    }

    int indexCarrinho = posRemover - 1;

    // Restaurar a quantidade ao stock
    string nomeProduto = carrinho[indexCarrinho][0];
    int quantidadeRemovida = stoi(carrinho[indexCarrinho][1]);

    for (int i = 0; i < totalProdutos; i++) {
        if (stock[i][1] == nomeProduto) {
            int quantidadeAtual = stoi(stock[i][2]);
            stock[i][2] = to_string(quantidadeAtual + quantidadeRemovida);
            break;
        }
    }

    // Remove o item deslocando os itens seguintes para "cima"
    for (int i = posRemover - 1; i < totalCarrinho - 1; i++) {
        for (int j = 0; j < 5; j++) {
            carrinho[i][j] = carrinho[i + 1][j];
        }
    }

    // Limpa o último slot
    for (int j = 0; j < 5; j++) {
        carrinho[totalCarrinho - 1][j] = "";
    }
    totalCarrinho--;
    cout << "Item removido com sucesso do carrinho." << endl;
}



bool sorteioVenda() {
    int sorteio = rand() % 100 + 1;  // Gera um número aleatório entre 1 e 100
    return sorteio <= sorteioChance;  // Se o número for menor ou igual a chance de sorteio, a venda é gratuita
}

void checkout(string** carrinho) {
    if (totalCarrinho == 0) {
        cout << "Carrinho vazio. Nada para finalizar." << endl;
        return;
    }

    // Exibir cabeçalho
    int faturaAtual = numeroFatura;
    int clienteAtual = numeroCliente;

    cout << left << setw(10) << "ID"
        << setw(15) << "Produto"
        << setw(10) << "Qtd"
        << setw(15) << "Preco"
        << setw(10) << "Subtotal" << endl;
    cout << "==============================================" << endl;

    for (int i = 0; i < totalCarrinho; i++) {
        bool linhaValida = true;
        for (int j = 0; j < 5; j++) {
            if (carrinho[i][j].empty()) {
                linhaValida = false;
                break;
            }
        }

        if (linhaValida) {
            cout << fixed << setprecision(2)
                << left << setw(10) << carrinho[i][0]
                << setw(15) << carrinho[i][1]
                << setw(10) << carrinho[i][2]
                << setw(15) << stod(carrinho[i][3])
                << setw(10) << stod(carrinho[i][4])
                << endl;
        }
    }

    cout << endl;

    // Confirmar compra
    char proseguir;
    cout << "Confirmas esta compra? (s/n): ";
    cin >> proseguir;

    if (proseguir != 's' && proseguir != 'S') {
        cout << "Compra cancelada." << endl;
        return;
    }

    numeroFatura++;
    numeroCliente++;

    // Sorteio
    bool vendaGratis = sorteioVenda();
    double totalSemIVA = 0.0;

    for (int i = 0; i < totalCarrinho; i++) {
        if (!carrinho[i][4].empty()) {
            totalSemIVA += stod(carrinho[i][4]);
        }
    }

    double totalComIVA = totalSemIVA * IVA;
    double pago = 0.0;
    double troco = 0.0;

    if (vendaGratis) {
        cout << "Parabens! Sua compra foi sorteada! Passou a ser gratuita!" << endl;
    }
    else {
        cout << "Total a pagar com IVA: " << fixed << setprecision(2) << totalComIVA << " €" << endl;
        cout << "Digite o valor pago: ";
        while (true) {
            cin >> pago;
            if (cin.fail() || pago < totalComIVA) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Valor inválido ou insuficiente. Tente novamente: ";
            }
            else {
                break;
            }
        }
        troco = pago - totalComIVA;
    }

    // Data e hora
    time_t agora = time(0);
    tm tempoLocal;
    localtime_s(&tempoLocal, &agora);
    char buffer[80];
    strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", &tempoLocal);

    // Talão
    cout << "\n========== TALAO DE COMPRA ==========" << endl;
    cout << "Data: " << buffer << endl;
    cout << "Numero da Fatura: " << faturaAtual << endl;
    cout << "Numero do Cliente: " << clienteAtual << endl;

    cout << left << setw(10) << "ID"
        << setw(15) << "Produto"
        << setw(10) << "Qtd"
        << setw(15) << "Preco"
        << setw(10) << "Subtotal" << endl;

    for (int i = 0; i < totalCarrinho; i++) {
        cout << fixed << setprecision(2)
            << left << setw(10) << carrinho[i][0]
            << setw(15) << carrinho[i][1]
            << setw(10) << carrinho[i][2]
            << setw(15) << stod(carrinho[i][3])
            << setw(10) << stod(carrinho[i][4]) << endl;
    }

    cout << "=====================================" << endl;
    cout << "Total sem IVA: " << fixed << setprecision(2) << totalSemIVA << " €" << endl;
    cout << "Total com IVA: " << fixed << setprecision(2) << totalComIVA << " €" << endl;
    cout << "Total Pago: " << fixed << setprecision(2) << (vendaGratis ? 0.0 : pago) << " €" << endl;
    cout << "Troco: " << fixed << setprecision(2) << troco << " €" << endl;

    // Limpar carrinho
    for (int i = 0; i < totalCarrinho; i++) {
        for (int j = 0; j < 5; j++) {
            carrinho[i][j] = "";
        }
    }
    totalCarrinho = 0;

    cout << endl;
}


int main()
{

    inicializarstock();
    inicializarCarrinho(carrinho);
    int op;
    string input;
    do {
        system("CLS");// Limpa o menu para a proxima operação             
        cout << endl;
        cout << "--- MENU ---" << endl;
        cout << "1. Adicionar ao Carrinho" << endl;
        cout << "2. Remover ao Carrinho" << endl;
        cout << "3. Adicionar produto" << endl;
        cout << "4. Eliminar produto" << endl;
        cout << "5. Listar produtos" << endl;
        cout << "6. Checkout" << endl;
        cout << "7. Sair" << endl;
        cout << "Opcao: ";
        cin >> input;

        try {
            op = stoi(input);
        }
        catch (...) {
            cout << endl;
            cout << "Entrada invalida. Por favor, escreva um numero inteiro de 1 a 7." << endl;
            op = -1; // opcao inválida
        }

        switch (op) {
        case 1:system("CLS"); adicionarCarrinho(stock); break; // criar funcao para efectuarVenda + Talao
        case 2:system("CLS"); removerCarrinho(stock, carrinho); break; // criar funcao que apaga items do carrinho
        case 3:system("CLS"); adicionarProdutos(stock); break; // criar funcao para adicionarProdutos
        case 4:system("CLS"); removerProdutos(stock); break; // criar funcao de eliminarProdutos
        case 5:system("CLS"); listarProdutos(stock); break; // criar a funcao de listarPprodutos, tendo em base o stock
        case 6:system("CLS"); checkout(carrinho); break;// criar funcao para carrinho
        case 7: cout << "A sair..." << endl; break;
        default: cout << "Opção inválida." << endl;
        }
        if (op != 7)
        {
            cout << endl;
            cout << "\nPressione Enter para continuar...";
            cin.ignore(); // Limpa o buffer do cin
            cin.get(); // Espera o Enter
        }


    } while (op != 7);
}
