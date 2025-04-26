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
// Matriz Para stock de 50 items diferentes ( ID: 0 | Nome: 1 | Quantidade : 2 | Preco de custo : 3)
string** stock = new string * [numMaxProd];

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
    stock[1][1] = "Arroz";
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
//Criacao da Funcao Efectuar venda
void efectuarVenda(string** stock) {
    int idProd;
    if (totalProdutos == 0) //Validacao do Stock
    {
        cout << "Nao Existe Produtos em Stock ";
        return;
    }

    char continuar;
    double totalsemIva = 0;
    //Criacao de String que vai guardar os detahes da compra
    string detalhesVenda = "";

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
        int qntdVenda;
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

        // Atualizar stock
        stock[index][2] = to_string(quantidadeStock - qntdVenda); 

        // Adicionar à string do talão atraves do "OSTRINGSTREAM" : Para formatar números (com setprecision, fixed, etc.) antes de transformar em string.Para juntar vários valores num só texto, de forma organizada.
        ostringstream linha;
        linha << left << setw(15) << stock[index][1] << setw(15) << qntdVenda << setw(15) << precoUnitario << setw(15) << precoUnitario * qntdVenda << "\n";//linha funciona como um cout invisível. // Formatei tudo como queria que saisse a string no talao  
        detalhesVenda += linha.str();// Puxei o resultado para o detalhesVenda com linha.str().// Para evitar que to_string() ponha casas decimais a mais.

        cout << qntdVenda << " unidade do produto " << stock[index][1] << " foi adicionado ao carrinho. Subtotal: " << fixed << setprecision(2) << subtotal << " €" << endl;
        cout << "Deseja continuar a comprar? (s/n): ";
        cin >> continuar;

    } while (continuar == 's' || continuar == 'S');

    double totalComIva = totalsemIva * IVA;
    cout << detalhesVenda;

    /* // TODO:Imprimir talão com o ostringstreeam para o formatar direitinho (Nao estou  a conseguir inprinmir)
    ostringstream totais;
    totais << fixed << setprecision(2);
    totais << "\n====== TALÃO DE COMPRA ======\n";
    totais << left << setw(15) << "Produto" << setw(15) << "Qtd" << setw(15) << "Preço Unitário" << setw(15) << "Subtotal" << "\n";
    totais << "----------------------------------------------------------------------------------------------------------------\n";
    totais << detalhesVenda;
    totais << "----------------------------------------------------------------------------------------------------------------\n";
    totais << left << setw(30) << "Total sem IVA:" << totalsemIva << " €\n";
    totais << left << setw(30) << "Total com IVA:" << totalComIva << " €\n";
    totais << "=============================\n";
    // left	Alinha o texto à esquerda.
    // setw(15)	Reserva 15 caracteres de largura para o camp
    //fixed << setprecision(2)	Força sempre 2 casas decimais.
    cout << totais.str();*/ 
}
int main()
{
    setlocale(LC_ALL, ".65001");
    inicializarstock();
    int op;
    do {
        system("CLS");// Limpa o menu para a proxima operação             TODO:Validacoes Para que quando escrevemos uma letras no menu nao de crash
        cout << endl;
        cout << "--- MENU ---" << endl;
        cout << "1. Efetuar venda" << endl;
        cout << "2. Adicionar produto" << endl;
        cout << "3. Eliminar produto" << endl;
        cout << "4. Listar produtos" << endl;
        cout << "5. Sair" << endl;
        cout << "Opcao: ";
        cin >> op;

        switch (op) {
        case 1: efectuarVenda(stock); break; // criar funcao para efectuarVenda + Talao
        case 2: adicionarProdutos(stock); break; // criar funcao para adicionarProdutos
        case 3: removerProdutos(stock); break; // criar funcao de eliminarProdutos
        case 4: listarProdutos(stock); break; // criar a funcao de listarPprodutos, tendo em base o stock
        case 5: cout << "A sair..." << endl; break;
        default: cout << "Opção inválida." << endl;
        }
        cout << "\nPressione Enter para continuar...";
        cin.ignore(); // Limpa o buffer do cin
        cin.get(); // Espera o Enter

    } while (op != 5);
}
