#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include "processos.hpp"
using namespace std;

int main() {
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
    int auxi = 0;
    int auxc = 0;
    for(int i = 0; i < cont; i++){
        getline(arquivo, instrucoes[i]); //leitura do arquivo
        if(i<6){
            cabecalho[auxi]=stoi(instrucoes[i]);
            cout<<cabecalho[i]<<endl;
            auxi++;
        }else {
            comandos[auxc]=instrucoes[i];
            auxc++;
        }
    }
    int tambloco= cabecalho[0];
    int linhascache = cabecalho[1];
    int numblocos = cabecalho[2];
    int mapeamento = cabecalho[3];
    int *cache = new int[linhascache];
    int *cont2 = new int[linhascache];
    int *conteudo=new int[numblocos*tambloco]();
	for(int i = 0; i < linhascache; i++) {
		cache[i] = -1;
		cont2[i]= 0;
	}
	srand(time(NULL));
 	bool cheio = false;
 	int palavra, posmaior, contquantos=0;
 	int teste1,teste2,teste3,teste4;
    bool existemaior = false;
    if(mapeamento==1){
    	cout<<"SELECIONADO: MAPEAMENTO DIRETO"<<endl;
    	for(int i = 0 ; i<auxc ; i++){
 			if(comandos[i][2]=='a' && comandos[i][3]=='d'){
 				if(comandos[i][6]){
 					teste1=(comandos[i][5]-48);
 					teste2=(comandos[i][6]-48);
 					palavra=(teste1*10)+(teste2);
 					mapeamentodireto(cabecalho,palavra, cache); 
 				}else{
					palavra=comandos[i][5]-48;
					mapeamentodireto(cabecalho,palavra, cache); 
				}
 			}//read 25
             else if(comandos[i][2]=='i' && comandos[i][3]=='t'){
                if(comandos[i][7]!=' '){
                    teste1=(comandos[i][6]-48); //write 2
                    teste2=(comandos[i][7]-48); // write 25
                    teste3=(comandos[i][9]-48);
                    palavra=(teste1*10)+teste2;
                    if(comandos[i][10]){
                        teste4=comandos[i][10]-48;
                        conteudo[palavra]=(teste3*10)+teste4;
                    }else{
                        conteudo[palavra]=teste3;
                    }
                }else{
                    teste1=(comandos[i][6]-48);
                    teste3=comandos[i][8]-48;
                    palavra=teste1;
                    if(comandos[i][9]){
                        teste4=comandos[i][9]-48;
                        conteudo[palavra]=teste3*10+teste4;
                    }else{
                        conteudo[palavra]=teste3;
                    }
                }
            }
            else if(comandos[i][2]=='o' && comandos[i][3]=='w'){
                cout<< "CACHE L1:"<<endl;
                for(int i=0;i <linhascache;i++){
                    for(int z=0;z<linhascache;z++){
                        if(cache[i]>-1){
                            cout<<i<< " - " <<cache[i]<< " - "<<cache[i]*linhascache+z <<" - " <<conteudo[cache[i]*linhascache+z] <<endl;
                        }else{
                            cout<<i<< " - " <<"semnada"<< " - "<<"semnada" <<endl;
                        }
                    }
                }
            }
        }
    }else if(mapeamento==2){
    	cout<<"SELECIONADO: TOTALMENTE ASSOCIATIVO"<<endl;
    	for(int i = 0 ; i<auxc ; i++){
 			if(comandos[i][2]=='a' && comandos[i][3]=='d'){
 				if(comandos[i][6]){
 					teste1=(comandos[i][5]-48);
 					teste2=(comandos[i][6]-48);
 					palavra=(teste1*10)+(teste2);
 					totalmenteassociativo(cabecalho,palavra,cache,cont2,cheio,contquantos,posmaior,existemaior); 
 				}else{
					palavra=comandos[i][5]-48;
					totalmenteassociativo(cabecalho,palavra,cache,cont2,cheio,contquantos,posmaior,existemaior);
				}
 			}//read 25
             else if(comandos[i][2]=='i' && comandos[i][3]=='t'){
               if(comandos[i][7]!=' '){
                    teste1=(comandos[i][6]-48); //write 2
                    teste2=(comandos[i][7]-48); // write 25
                    teste3=(comandos[i][9]-48);
                    palavra=(teste1*10)+teste2;
                    if(comandos[i][10]){
                        teste4=comandos[i][10]-48;
                        conteudo[palavra]=(teste3*10)+teste4;
                    }else{
                        conteudo[palavra]=teste3;
                    }
                }else{
                    teste1=(comandos[i][6]-48);
                    teste3=comandos[i][8]-48;
                    palavra=teste1;
                    if(comandos[i][9]){
                        teste4=comandos[i][9]-48;
                        conteudo[palavra]=teste3*10+teste4;
                    }else{
                        conteudo[palavra]=teste3;
                    }
                }
            }
            else if(comandos[i][2]=='o' && comandos[i][3]=='w'){
                cout<< "CACHE L1:"<<endl;
                for(int i=0;i <linhascache;i++){
                    for(int z=0;z<linhascache;z++){
                        if(cache[i]>-1){
                            cout<<i<< " - " <<cache[i]<< " - "<<cache[i]*linhascache+z <<" - " <<conteudo[cache[i]*linhascache+z] <<endl;
                        }else{
                            cout<<i<< " - " <<"semnada"<< " - "<<"semnada" <<endl;
                        }
                    }
                }
            }
 		}
    }else if(mapeamento==3){
    	cout<<"SELECIONADO: PARCIALMENTE ASSOCIATIVO"<<endl;
        for(int i = 0 ; i<auxc ; i++){
            if(comandos[i][2]=='a' && comandos[i][3]=='d'){
                if(comandos[i][6]){
                    teste1=(comandos[i][5]-48);
                    teste2=(comandos[i][6]-48);
                    palavra=(teste1*10)+(teste2);
                    parcialmenteassociativo(cabecalho,palavra,cache,cont2,cheio,contquantos,posmaior,existemaior); 
                }else{
                    palavra=comandos[i][5]-48;
                    parcialmenteassociativo(cabecalho,palavra,cache,cont2,cheio,contquantos,posmaior,existemaior);
                }
            }//read 25
            else if(comandos[i][2]=='i' && comandos[i][3]=='t'){
               if(comandos[i][7]!=' '){
                    teste1=(comandos[i][6]-48); //write 2
                    teste2=(comandos[i][7]-48); // write 25
                    teste3=(comandos[i][9]-48);
                    palavra=(teste1*10)+teste2;
                    if(comandos[i][10]){
                        teste4=comandos[i][10]-48;
                        conteudo[palavra]=(teste3*10)+teste4;
                    }else{
                        conteudo[palavra]=teste3;
                    }
                }else{
                    teste1=(comandos[i][6]-48);
                    teste3=comandos[i][8]-48;
                    palavra=teste1;
                    if(comandos[i][9]){
                        teste4=comandos[i][9]-48;
                        conteudo[palavra]=teste3*10+teste4;
                    }else{
                        conteudo[palavra]=teste3;
                    }
                }
            }
            else if(comandos[i][2]=='o' && comandos[i][3]=='w'){
                cout<< "CACHE L1:"<<endl;
                for(int i=0;i <linhascache;i++){
                    for(int z=0;z<linhascache;z++){
                        if(cache[i]>-1){
                            cout<<i<< " - " <<cache[i]<< " - "<<cache[i]*linhascache+z <<" - " <<conteudo[cache[i]*linhascache+z] <<endl;
                        }else{
                            cout<<i<< " - " <<"semnada"<< " - "<<"semnada" <<endl;
                        }
                    }
                }
            }
        }
    }
    arquivo.clear();
    arquivo.seekg(arquivo.beg);
    
    delete[] instrucoes;
    delete[] comandos;
    delete[] conteudo;
    return 0;
}