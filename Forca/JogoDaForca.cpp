#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;

map<char, bool> acertou;
string palavraAleatoria;

bool chuteCorreto(char chute){
    for (char letra : palavraAleatoria){
        if (chute == letra){
            acertou[letra] = true;
            return true;
        }
    }
    return false;
    
}

bool naoVenceu(){
    for (char letra : palavraAleatoria){
        if (!acertou[letra]){
            return true;
        }
    }
    cout << endl << "*******************" << endl;
    cout << "*** Voce Venceu ***" << endl;
    cout << "*******************" << endl;
    return false;
}

vector<string> lerArquivo(){
    vector<string> palavrasDisponiveis;
    ifstream arquivo;
    arquivo.open("palavras.txt");

    if (!arquivo.is_open()){
        cout << "Nao foi possivel abrir o banco de palavras, por favor devolva o txt para a mesma pasta do exe." << endl;
        exit(0);
    }

    int numeroDePalavras(0);

    arquivo >> numeroDePalavras;

    for (int i(0); i < numeroDePalavras; i++){
        string palavraLida;
        arquivo >> palavraLida;
        palavrasDisponiveis.push_back(palavraLida);
    }

    arquivo.close();
    return palavrasDisponiveis;
}

void sorteiaPalavra(){
    vector <string> listaDePalavras = lerArquivo();
    srand(time(NULL));
    int indiceSorteado(rand() % listaDePalavras.size());
    palavraAleatoria = listaDePalavras[indiceSorteado];
}

void salvaArquivo(vector <string> listaDePalavras){
    ofstream arquivo;
    arquivo.open("palavras.txt");
    arquivo << listaDePalavras.size() << endl;
    for (string palavra : listaDePalavras){
        arquivo << palavra << endl;
    }    
    arquivo.close();
}
void adicionaPalavra(){
    vector <string> listaDePalavrasOLD(lerArquivo());
    
    cout << endl << endl << "Digite a palavra (MAIUSCULA) que voce deseja adicionar no banco de dados: ";
    string palavraAdicionar("");
    cin >> palavraAdicionar;
    listaDePalavrasOLD.push_back(palavraAdicionar);
    salvaArquivo(listaDePalavrasOLD);
    
}

void printForca(int numeroTentativas){
    string linha1("    |----------"), linha2("    |         |"), linha3("              |"),
    linha4("              |"), linha5("              |");
    vector <string> listaDeLinhas;
    switch (numeroTentativas){ 
        case 6:
            linha3 = "    o         |";
            linha4 = "   /|\\        |";
            linha5 = "   / \\        |";
            break;             
        case 5:
            linha3 = "    o         |";
            linha4 = "   /|\\        |";
            linha5 = "   /          |";
            break;
        case 4:
            linha3 = "    o         |";
            linha4 = "   /|\\        |";
            break;     
        case 3:
            linha3 = "    o         |";
            linha4 = "   /|         |";
            break;
        case 2:
            linha3 = "    o         |";
            linha4 = "    |         |";
            break;
             
        case 1:
            linha3 = "    o         |";
            break;

    }
    listaDeLinhas.push_back(linha1);
    listaDeLinhas.push_back(linha2);
    listaDeLinhas.push_back(linha3);
    listaDeLinhas.push_back(linha4);
    listaDeLinhas.push_back(linha5);

    for (string palavra : listaDeLinhas){
        for (char letra : palavra){
            cout << letra;
        }
        cout << endl;
    }
}

int main(){
    char chute, opcaoAdicionarPalavra;
    vector <char> chutesErrados;

    sorteiaPalavra();


    cout << "*********************" << endl;
    cout << "*** Jogo Da Forca ***" << endl;
    cout << "*********************" << endl << endl;

    while(naoVenceu()){
        printForca(chutesErrados.size());
        cout << endl << endl;
        for (char letra : palavraAleatoria){
            if (acertou[letra]){
                cout << letra << " ";
            }
        
            else{
                cout << "_ ";
            }
        }
        cout << " Ja chutados: ";
        
        for (char letra : chutesErrados){
            cout << letra << " ";
        }
        
        cout << endl << "Qual o seu chute: ";
        cin >> chute;
    
        
        if (chuteCorreto(chute)){
            cout << "Voce acertou! o seu chute esta na palavra secreta" << endl;
        }
    
        else{
            cout << "Voce errou :( o seu chute nao esta na palavra secreta" << endl;
            chutesErrados.push_back(chute);
        }

        if (chutesErrados.size() > 5){        
            cout << endl << "**************************" << endl;
            cout << "*** Voce foi enforcado ***" << endl;
            cout << "**************************" << endl << endl;
            printForca(chutesErrados.size());
            cout << endl << endl;
        
        break;
        }

    }

    cout << "voce deseja adicionar uma palavra ao banco de palavras [S / N]: ";
    cin >> opcaoAdicionarPalavra;

    if (opcaoAdicionarPalavra == 'S'){
        adicionaPalavra();
    }

    return 0;
}


//    |----------
//    |         |
//    o         |
//   /|\        |
//   / \        |

//    |----------
//    |         |
//    o         |
//   /|\        |
//   /          |