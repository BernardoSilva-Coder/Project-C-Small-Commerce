// Projecto C++ Sketch inicial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string> // Premite usar o to_string
#include <ctime> //TODO: Acrescentar data e hora ao talao
#include <locale> // Usar caracteres como o c cedilhado e assentos e o simbolo do euro
#include <sstream> //Para Puder Usar ostringstream

using namespace std;

//Variaveis Constantes Globais , quando precisamos das variaveis em varias funcoes enunciamos antes para todas poderem ter acesso.
int numMaxProd = 50;
int colunas = 4;
int totalProdutos = 4;
const double IVA = 1.23;
const double margemLucro = 1.30;
int qntdVenda;
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
    cin >> numeroProdAdd;

    if (totalProdutos + numeroProdAdd < numMaxProd)
    {
        for (int i = 0; i < numeroProdAdd; i++)
        {

            stock[totalProdutos][0] = to_string(totalProdutos + 1); // ID |Converte em string usando a biblioteca String, torna o id automatico fazendo + 1.

            cout << "Nome do Produto : " << endl;// Nome
            cin >> stock[totalProdutos][1];

            cout << "Quantidade :" << endl;// Quantidade
            cin >> stock[totalProdutos][2];

            cout << "Preco de Custo :" << endl;// Preco de Custo
            cin >> stock[totalProdutos][3];
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
    cout << "Qual o ID do Produto que quer apagar? ";
    cin >> idProdApg;

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
    for (int i = 0; i < 50; i++)
    {
        carrinho[i] = new string[4];
    }
}

//Criacao da Funcao Adicionar Carrinho
void adicionarCarrinho(string** stock) {
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
        cin >> idProd;
        for (int i = 0; i < totalProdutos; i++) {
            if (stoi(stock[i][0]) == idProd) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            cout << endl << "ID " << idProd << " não encontrado." << endl;
            return;
        }
        //Variaveis Para fazer os calculos dos custos
        int quantidadeStock = stoi(stock[index][2]);
        
        cout << "Insira a Quantidade do Produto que deseja comprar : ";
        cin >> qntdVenda;

        if (qntdVenda <= 0) {
            cout << endl << "A quantidade introduzida não é válida." << endl;
            return;
        }
        if (qntdVenda > quantidadeStock) {
            cout << endl << "Nao existe quantidade suficiente em stock desse produto." << endl;
            return;
        }

        // Calculo do preço
        double precoUnitario = stod(stock[index][3]) * margemLucro;
        double subtotal = precoUnitario * qntdVenda;
        totalsemIva += subtotal;

        // Adicionar à matriz carrinho
        carrinho[totalCarrinho][0] = stock[index][1]; // Nome
        carrinho[totalCarrinho][1] = to_string(qntdVenda); // Quantidade
        carrinho[totalCarrinho][2] = to_string(precoUnitario); // Preço unitário
        carrinho[totalCarrinho][3] = to_string(subtotal); // Subtotal

        totalCarrinho++;
        // Atualizar stock
        stock[index][2] = to_string(quantidadeStock - qntdVenda);

        

        cout << qntdVenda << " unidade do produto " << stock[index][1] << " foi adicionado ao carrinho. Subtotal: " << fixed << setprecision(2) << subtotal << " €" << endl;
        cout << "Deseja continuar a comprar? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');
}
void removerCarrinho(string** carrinho,string** stock) {
    if (totalCarrinho == 0) {
        cout << "Carrinho vazio!" << endl;
        return;
    }

    cout << "Itens no carrinho:\n";
    for (int i = 0; i < totalCarrinho; i++) {
        cout << i + 1 << ". " << carrinho[i][0] << " x " << carrinho[i][1] << endl;
    }

    int pos;
    cout << "Indique o numero do item a remover: ";
    cin >> pos;
    pos--; // para índice 0-based

    if (pos >= 0 && pos < totalCarrinho) {
        // devolver a quantidade ao stock
        for (int i = 0; i < totalProdutos; i++) {
            if (stock[i][1] == carrinho[pos][0]) {
                int quantidadeStock = stoi(stock[i][2]);
                int qntRemovida = stoi(carrinho[pos][1]);
                stock[i][2] = to_string(quantidadeStock + qntRemovida);
                break;
            }
        }

        // remover item e deslocar restantes
        for (int i = pos; i < totalCarrinho - 1; i++) {
            for (int j = 0; j < 4; j++) {
                carrinho[i][j] = carrinho[i + 1][j];
            }
        }
        totalCarrinho--;
        cout << "Item removido com sucesso.\n";
    }
    else {
        cout << "Índice inválido.\n";
    }
}
void checkout(string**carrinho)
{
    for (int i = 0; i < totalCarrinho; i++)
    {
        cout << left << setw(10) << "Produto" << setw(10) << "Qtd" << setw(10) << "Preco" << setw(10) << "Subtotal" << endl;
        cout << "=====================================" << endl;
        cout << fixed << setprecision(2) << left << setw(10) << carrinho[i][0]
             << setw(10) << carrinho[i][1]
             << setw(10) << stod(carrinho[i][2])
             << setw(10) << stod(carrinho[i][3]) << endl;    
    }
    cout << endl;


    
    char proseguir;
    cout << "Confirmas esta compra ? ";
    cin >> proseguir;
    cout << endl;


    if (proseguir == 's' || proseguir == 'S')
    {
        double totalSemIVA = 0;
        double totalComIVA = 0;
        double pago;
        double troco;
        cout << "Qual a Quantia com que deseja pagar ? " << endl;
        cin >> pago;
        // Obter data e hora atual
        time_t agora = time(0);
        tm tempoLocal;
        localtime_s(&tempoLocal, &agora); // versão segura no Visual Studio

        // Criar string formatada com data e hora
        char buffer[80];
        strftime(buffer, 80, "%d/%m/%Y %H:%M:%S", &tempoLocal);;

        
        cout << "========== TALAO DE COMPRA ==========" << endl;
        cout << "Data: " << buffer << endl;
        cout << left << setw(10) << "Produto" << setw(10) << "Qtd" << setw(10) << "Preco" << setw(10) << "Subtotal" << endl;

        for (int i = 0; i < totalCarrinho; i++) {
            cout << left << setw(10) << carrinho[i][0]
                << setw(10) << carrinho[i][1]
                << setw(10) << fixed << setprecision(2) << stod(carrinho[i][2])
                << setw(10) << fixed << setprecision(2) << stod(carrinho[i][3]) << endl;

            totalSemIVA += stod(carrinho[i][3]);
        }

        totalComIVA = totalSemIVA * IVA;

        cout << "=====================================" << endl;
        cout << "Total sem IVA: " << fixed << setprecision(2) << totalSemIVA << " €" << endl;
        cout << "Total com IVA: " << fixed << setprecision(2) << totalComIVA << " €" << endl;
        troco = pago - totalComIVA;
        cout << "Total Pago :" << fixed << setprecision(2) << pago << " €" << endl;
        cout << "Troco : " << fixed << setprecision(2) << troco << " €" << endl;



    }
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
        case 2:system("CLS"); removerCarrinho(stock,carrinho); break; // criar funcao que apaga items do carrinho
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
