// Projecto C++ Sketch inicial.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>

using namespace std;

//Variaveis Constantes Globais , quando precisamos das variaveis em varias funcoes enunciamos antes para todas poderem ter acesso.
int numMaxProd = 50;
int colunas = 4;
int totalProdutos = 4;
double IVA = 1.3;
// Matriz Para stock de 50 items diferentes ( ID: 0 | Nome: 1 | Quantidade : 2 | Preco de custo : 3)
string** stock = new string * [numMaxProd];

void inicializarstock(string** stock) {
    for (int i = 0; i < numMaxProd; i++)
    {
        stock[i] = new string[colunas];
    }
    stock[0][0] = "1";
    stock[0][1] = "Pao";
    stock[0][2] = "100";
    stock[0][3] = "0.04";
    stock[1][0] = "2";
    stock[1][1] = "Arroz";
    stock[1][2] = "150";
    stock[1][3] = "1.00";
    stock[2][0] = "3";
    stock[2][1] = "Atum";
    stock[2][2] = "100";
    stock[2][3] = "0.50";
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
            cout << stock[i][j] << "\t";
        }

        cout << endl;
    }
}
//Criacao da Funcao Adicionar Produto
void adicionarProdutos(string** stock) {
    // Variáveis
    int numeroProdAdd;


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

    int index = 0;                             // A Variável index serve para guardar a posição (linha) onde está o produto que tem o ID que o utilizador quer remover.
    for (int i = 0; i < totalProdutos; i++) {
        if (stoi(stock[i][0]) == idProdApg) {   //stoi(stock[i][0]) significa converter a variavel da matriz ID (Coluna 0 que e uma string para Int, de modo a poder ser comparada)
            index = i;                          // Dai aqui a igualarmos a posicao, variavel que nos da a posicao.
            break;                              //Para o ciclo quando encontra e define a variavel index. E avanca para as validacoes em baixo.
        }
    }

    if (index <= 0) {
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
void efectuarVenda(string** stock) {
    











}

int main()
{
    inicializarstock();
    int op;
    do {

        system("CLS");// Limpa o menu para a proxima operação

        cout << "--- MENU ---" << endl;
        cout << "1. Efetuar venda" << endl;
        cout << "2. Adicionar produto" << endl;
        cout << "3. Eliminar produto" << endl;
        cout << "4. Listar produtos" << endl;
        cout << "5. Sair" << endl;
        cout << "Opcao: ";
        cin >> op;
    

        switch (op) {
        case 1:; break; // criar funcao para efectuarVenda + Talao
        case 2: adicionarProdutos(stock); break; // criar funcao para adicionarProdutos
        case 3: removerProdutos(stock); break; // criar funcao de eliminarProdutos
        case 4: listarProdutos(stock); break; // criar a funcao de listarPprodutos, tendo em base o stock
        case 5: cout << "A sair..." << endl; break;
        default: cout << "Opção inválida." << endl;
        }

        if (op != 5) {
            cout << "\nPressione Enter para continuar...";
            cin.ignore(); // Limpa o buffer do cin
            cin.get(); // Espera o Enter
        }
        
    } while (op != 5);


