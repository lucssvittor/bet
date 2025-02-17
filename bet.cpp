#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
#include <iomanip>
#include <limits>
#include <fstream>

using namespace std;

// Estruturas de Dados
struct Jogador
{
    int saldo;
    int nivel;
    vector<string> historico;
    int vitorias;
    int derrotas;
    int apostasFeitas;
};

void exibirCabecalho(const Jogador &jogador)
{
    cout << "******************************************\n";
    cout << "        LUCAS BET - VEM QUE TA PAGADO      \n";
    cout << "\n";
    cout << "               Saldo: R$ " << jogador.saldo << "\n";
    cout << "******************************************\n";
}

// Menu
void exibirMenu()
{
    cout << "\nEscolha uma opção abaixo:\n";
    cout << "\n";
    cout << "1. Caça-Níquel\n";
    cout << "2. Jogo de Dados\n";
    cout << "3. Par ou Ímpar\n";
    cout << "4. Blackjack\n";
    cout << "5. Histórico\n";
    cout << "6. Estatísticas\n";
    cout << "7. Depositar\n";
    cout << "8. Sacar\n";
    cout << "9. Sair\n";
    cout << "Digite sua opção: ";
}

// Estatísticas do jogador
void exibirEstatisticas(const Jogador &jogador)
{
    cout << "\n=== Estatísticas do Jogador ===\n";
    cout << "\n";
    cout << "Saldo: R$" << jogador.saldo << endl;
    cout << "Nível: " << jogador.nivel << endl;
    cout << "Vitórias: " << jogador.vitorias << endl;
    cout << "Derrotas: " << jogador.derrotas << endl;
    cout << "Apostas feitas: " << jogador.apostasFeitas << endl;
    cout << "==============================\n";
}

// Histórico de jogos
void exibirHistorico(const Jogador &jogador)
{
    cout << "\n=== Histórico ===\n";
    cout << "\n";
    if (jogador.historico.empty())
    {
        cout << "Nenhum registro.\n";
    }
    else
    {
        for (const string &jogo : jogador.historico)
        {
            cout << jogo << endl;
        }
    }
    cout << "\n";
    cout << "==========================\n";
}

// Nível do jogador
void atualizarNivel(Jogador &jogador)
{
    if (jogador.saldo >= 500 && jogador.nivel == 1)
    {
        jogador.nivel = 2;
        cout << "Parabéns! Você subiu para o Nível 2!\n";
    }
    else if (jogador.saldo >= 1000 && jogador.nivel == 2)
    {
        jogador.nivel = 3;
        cout << "Parabéns! Você subiu para o Nível 3!\n";
    }
}

// Depósito
void depositar(Jogador &jogador)
{
    int deposito;
    cout << "\n--- Depósito ---\n";
    cout << "\n";
    cout << "Digite o valor que você deseja depositar\n(mínimo R$ 10): R$ ";
    while (!(cin >> deposito) || deposito < 10)
    {
        cout << "Valor inválido! O depósito deve ser maior que R$ 10.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Digite novamente: R$";
    }
    jogador.saldo += deposito;
    cout << "Você depositou R$" << deposito << ". Saldo atual: R$" << jogador.saldo << "\n";
}

// Saque
void sacar(Jogador &jogador)
{
    int saque;
    char opcao;

    while (true)
    {
        cout << "\n--- Saque ---\n";
        cout << "\n";
        cout << "Digite o valor que você deseja sacar\n(mínimo R$ 100): R$ ";

        while (!(cin >> saque) || saque < 100 || saque > jogador.saldo)
        {
            cout << "Valor inválido! O saque deve ser no mínimo R$ 100 e não pode ultrapassar seu saldo atual (R$" << jogador.saldo << ").\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Digite novamente: R$ ";
        }

        jogador.saldo -= saque;
        cout << "Você sacou R$ " << saque << ". Saldo atual: R$ " << jogador.saldo << "\n";

        cout << "\nDeseja voltar ao menu principal? (S/N): ";
        cin >> opcao;

        if (opcao == 'S' || opcao == 's')
        {
            break;
        }
    }
}

// Progresso do jogador
void carregarProgresso(Jogador &jogador)
{
    ifstream arquivo("progresso.txt");
    if (arquivo.is_open())
    {
        arquivo >> jogador.saldo;
        arquivo >> jogador.nivel;
        arquivo >> jogador.vitorias;
        arquivo >> jogador.derrotas;
        arquivo >> jogador.apostasFeitas;
        int historicoSize;
        arquivo >> historicoSize;
        jogador.historico.resize(historicoSize);
        for (int i = 0; i < historicoSize; ++i)
        {
            arquivo >> jogador.historico[i];
        }
        arquivo.close();
    }
    else
    {
        jogador.saldo = 50;
        jogador.nivel = 1;
        jogador.vitorias = 0;
        jogador.derrotas = 0;
        jogador.apostasFeitas = 0;
    }
}

// Salvar o jogo
void salvarProgresso(const Jogador &jogador)
{
    ofstream arquivo("progresso.txt");
    if (arquivo.is_open())
    {
        arquivo << jogador.saldo << endl;
        arquivo << jogador.nivel << endl;
        arquivo << jogador.vitorias << endl;
        arquivo << jogador.derrotas << endl;
        arquivo << jogador.apostasFeitas << endl;
        arquivo << jogador.historico.size() << endl;
        for (const string &jogo : jogador.historico)
        {
            arquivo << jogo << endl;
        }
        arquivo.close();
    }
    else
    {
        cout << "Erro ao salvar o progresso.\n";
    }
}

// Caça-Níquel
void jogarCacaNiquel(Jogador &jogador)
{
    int aposta;
    cout << "Digite o valor da aposta (R$): ";
    while (!(cin >> aposta) || aposta <= 0 || aposta > jogador.saldo)
    {
        cout << "Valor inválido! A aposta deve ser maior que zero.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Digite novamente: ";
    }

    string simbolos[] = {"🍒", "🍋", "🍊", "🍉", "🍓"};
    string giro1 = simbolos[rand() % 5];
    string giro2 = simbolos[rand() % 5];
    string giro3 = simbolos[rand() % 5];

    cout << "Giros: " << giro1 << " | " << giro2 << " | " << giro3 << "\n";

    if (giro1 == giro2 && giro2 == giro3)
    {
        cout << "Parabéns! Você ganhou! O prêmio é o dobro da sua aposta.\n";
        jogador.saldo += aposta * 5;
        jogador.vitorias++;
        jogador.historico.push_back("Caça-Níquel: Vitória");
    }
    else
    {
        cout << "Você perdeu! Tente novamente.\n";
        jogador.saldo -= aposta;
        jogador.derrotas++;
        jogador.historico.push_back("Caça-Níquel: Derrota");
    }
    jogador.apostasFeitas++;
}

// Jogo de Dados
void jogarDados(Jogador &jogador)
{
    int aposta;
    cout << "Digite o valor da aposta (R$): ";
    while (!(cin >> aposta) || aposta <= 0 || aposta > jogador.saldo)
    {
        cout << "Valor inválido! A aposta deve ser maior que zero e não pode ultrapassar seu saldo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Digite novamente: ";
    }

    int dado1 = rand() % 6 + 1;
    int dado2 = rand() % 6 + 1;

    cout << "Você rolou: " << dado1 << " e " << dado2 << "\n";

    if (dado1 + dado2 == 7 || dado1 + dado2 == 11)
    {
        cout << "Parabéns! Você ganhou! O prêmio é o dobro da sua aposta.\n";
        jogador.saldo += aposta * 5;
        jogador.vitorias++;
        jogador.historico.push_back("Jogo de Dados: Vitória");
    }
    else
    {
        cout << "Você perdeu! Tente novamente.\n";
        jogador.saldo -= aposta;
        jogador.derrotas++;
        jogador.historico.push_back("Jogo de Dados: Derrota");
    }
    jogador.apostasFeitas++;
}

// Par ou Ímpar
void jogarParOuImpar(Jogador &jogador)
{
    int aposta;
    cout << "Digite o valor da aposta (R$): ";
    while (!(cin >> aposta) || aposta <= 0 || aposta > jogador.saldo)
    {
        cout << "Valor inválido! A aposta deve ser maior que zero e não pode ultrapassar seu saldo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Digite novamente: ";
    }

    int numero;
    char escolha;
    cout << "Escolha: (P)ar ou (I)mpar: ";
    cin >> escolha;
    cout << "Digite um número de 1 a 10: ";
    cin >> numero;

    int sorteio = rand() % 10 + 1;
    cout << "Número sorteado: " << sorteio << "\n";

    bool ganhou = (escolha == 'P' && (numero + sorteio) % 2 == 0) ||
                  (escolha == 'I' && (numero + sorteio) % 2 != 0);

    if (ganhou)
    {
        cout << "Você ganhou! O prêmio é o dobro da sua aposta.\n";
        jogador.saldo += aposta * 5;
        jogador.vitorias++;
        jogador.historico.push_back("Par ou Ímpar: Vitória");
    }
    else
    {
        cout << "Você perdeu! Tente novamente.\n";
        jogador.saldo -= aposta;
        jogador.derrotas++;
        jogador.historico.push_back("Par ou Ímpar: Derrota");
    }
    jogador.apostasFeitas++;
}

// Blackjack
void jogarBlackjack(Jogador &jogador)
{
    int aposta;
    cout << "Digite o valor da aposta (R$): ";
    while (!(cin >> aposta) || aposta <= 0 || aposta > jogador.saldo)
    {
        cout << "Valor inválido! A aposta deve ser maior que zero e não pode ultrapassar seu saldo.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Digite novamente: ";
    }

    int cartaJogador = rand() % 20 + 2;
    int cartaDealer = rand() % 50 + 2;

    cout << "Sua carta: " << cartaJogador << ", Carta do Dealer: " << cartaDealer << "\n";

    if (cartaJogador > cartaDealer)
    {
        cout << "Você ganhou! O prêmio é o dobro da sua aposta.\n";
        jogador.saldo += aposta * 3;
        jogador.vitorias++;
        jogador.historico.push_back("Blackjack: Vitória");
    }
    else if (cartaJogador < cartaDealer)
    {
        cout << "Você perdeu! Tente novamente.\n";
        jogador.saldo -= aposta;
        jogador.derrotas++;
        jogador.historico.push_back("Blackjack: Derrota");
    }
    else
    {
        cout << "Empate! Aposta devolvida.\n";
    }
    jogador.apostasFeitas++;
}

// Função principal
int main()
{
    srand(time(0));
    Jogador jogador;

    carregarProgresso(jogador);

    bool jogoAtivo = true;
    while (jogoAtivo)
    {
        exibirCabecalho(jogador);
        exibirMenu();

        int back;
        cin >> back;

        switch (back)
        {
        case 1:
            jogarCacaNiquel(jogador);
            break;
        case 2:
            jogarDados(jogador);
            break;
        case 3:
            jogarParOuImpar(jogador);
            break;
        case 4:
            jogarBlackjack(jogador);
            break;
        case 5:
            exibirHistorico(jogador);
            break;
        case 6:
            exibirEstatisticas(jogador);
            break;
        case 7:
            depositar(jogador);
            break;
        case 8:
            sacar(jogador);
            break;
        case 9:
            jogoAtivo = false;
            cout << "Saindo do jogo...\n";
            break;
        default:
            cout << "Opção inválida! Tente novamente.\n";
            break;
        }

        atualizarNivel(jogador);

        salvarProgresso(jogador);
    }

    return 0;
}
