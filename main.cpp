#include <fstream>
using namespace std;

int main() {
	int nciclos = 0;
    int ninstrucao = 0;
    int cont = 0;
    ifstream arquivo("config.txt");  //abre o arquivo
    if(arquivo.fail()){
        cout << "O arquivo de entrada nao foi encontrado!" << endl;
        return 1;
    }
    string str = "";
    while(!arquivo.eof()) { // faz a contagem de linhas do arquivo
        getline(arquivo, str);
        if(str != "")
            cont++;
    }
    arquivo.clear(); // reseta objeto para limpar memoria
    arquivo.seekg(arquivo.beg); // setando para o começo do arquivo
    if(cont <= 0) {
        cout << "O arquivo foi encontrado, mas está vazio. Adicione instrucoes, lembre-se de salvar e tente novamente." << endl;
        return 1;
    }
    string *instrucoes = new string[cont]; 
    int cabecalho[6]; // armazena as configuracoes do cabecalho
    string *comandos= new string[cont-6];
    for(int i = 0; i < cont; i++){
        getline(arquivo, instrucoes[i]); //leitura do arquivo
        int auxi = 0;
        int auxc = 0;
        if(i<=6){
            cabecalho[aux]=atoi(instrucoes[i]);
            aux++;
        }else {
            comandos[auxc]=instrucoes[i];
        }
    }   
    arquivo.clear();
    arquivo.seekg(arquivo.beg);
    
    delete[] instrucoes;
    delete[] pipeline;
    return 0;
}