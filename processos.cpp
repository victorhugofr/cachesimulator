#include "processos.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
using namespace std;
void mapeamentodireto(int *cabecalho, int palavra, int * cache){ // read25
	//int palavra2=stoi(palavra);
	int bloco = palavra / cabecalho[0]; // 6
	int linha = bloco % cabecalho[1]; // 2
	if(cache[linha] == bloco) cout << "HIT: linha " << linha << endl; 
	else {
		cache[linha] = bloco;
		cout << "MISS -> alocado na linha " << linha << endl;
	}
}
int maiorta(int* cabecalho, int* contadoraux) {
	int maior = 0;
	for(int j = 0; j < cabecalho[1]; j++) {
		if(maior < contadoraux[j]) maior = contadoraux[j];
	}
	return maior;
}
int menorta(int* cabecalho, int* contadoraux){
	int menor = contadoraux[0];
	for(int j = 0; j < cabecalho[1]; j++) {
		if(contadoraux[j] == 0) return 0;
	}
	for(int i = 1; i < cabecalho[1]; i++) {
		if(contadoraux[i] < menor) menor = contadoraux[i];
	}
	return menor;
}
int menorpa(int *cabecalho, int *contadoraux, int inicioBusca){
	int menor = contadoraux[inicioBusca];
	for(int i = inicioBusca; i < (inicioBusca + (cabecalho[1] / cabecalho[4])); i++) {
		if(contadoraux[i] == 0) return 0;
	}

	for(int i = inicioBusca + 1; i < (inicioBusca + (cabecalho[1] / cabecalho[4])); i++) {
		if(contadoraux[i] < menor) menor = contadoraux[i];
	}
	return menor;
}
int totalmenteassociativo(int *cabecalho, int palavra, int* cache, int* contadoraux, bool &cheio,int &contquantos, int &posmaior, bool &existemaior) {	
	//int palavra2=stoi(palavra);
	int subs = cabecalho[5];
	int bloco = palavra / cabecalho[0];
	//ALEATORIO
	if(subs == 1) {	
		bool procura = false;
		int linha = rand() % cabecalho[1];
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				procura = true;
			}
		}
		//if(cache[linha] == bloco) cout << "HIT: linha " << linha << endl;
		if(!procura) {
			cache[linha] = bloco;
			cout << "MISS -> alocado na linha " << linha << endl;
		}
	}
	//FIFO(FILA)
	else if(subs == 2) {
		bool procura = false;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				procura = true;
			}
		}
		if(!procura) {
			cout << "MISS -> alocado na linha ";
			int maior = maiorta(cabecalho, contadoraux);
			for(int j = 0; j < cabecalho[1]; j++) {
				contadoraux[j] += 1;
				if(maior == 0) {
					cache[0] = bloco;
					cout << "0" << endl; // CASO NAO HAJA MAIOR(SEJA O PRIMEIRO A ENTRAR NA CACHE)ALOCA NA LINHA 0 DA CACHE
					return 0;
				}

				else if(maior != 0) { // SE NAO, ALOCA NO BLOCO QUE AINDA NAO ALOCOU(REPRESSENTADO POR -1)
					if(cache[j] == -1) {
						cache[j] = bloco;
						cout << j << endl;
						if(j == cabecalho[1]-1) cheio = true; // VERIFICACAO SE CACHE ESTA CHEIO
						return 0;
					}
				}
			}
			if(maior != 0 && cheio == true) {
				maior = maiorta(cabecalho, contadoraux);
				for(int i = 0; i < cabecalho[1]; i++) {
					if(contadoraux[i] == maior) { // SE A CHACE JA ESTAVA CHEIA, ALOCA NO MAIOR E DEPOIS GERA O QUE ALOCOU = 1;
						cache[i] = bloco;
						contadoraux[i] = 1;
						cout << i << endl;
						return 0;
					}
				}				
			}
		}
	}
	//LFU(MENOS FREQUENTEMENTE UTILIZADO)
	else if(subs == 3) {
		bool procura = false;
		int post;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				procura = true;
				contadoraux[i] += 1;
				post=i;
			//	cout<<contadoraux[i]<<"---"<<endl;
			}
		}
		////cout<<post<<endl;
		//for(int l=0;l<cabecalho[1];l++){
		//	cout<<contadoraux[l]<<"    ";
		//}
		if(!procura) {
			cout << "MISS -> alocado na linha ";
			int menor = menorta(cabecalho, contadoraux);
			for(int i = 0; i < cabecalho[1]; i++) {
				if(menor == 0 && cache[i]==-1) { // ALGUMA LINHA NAO FOI UTILIZADA AINDA
					
						cache[i] = bloco; // SUBSTITUI
						contadoraux[i] = 1; // UTILIZADO UMA VEZ
						cout << i << endl; // QUAL LINHA FOI ALOCADA
						if(i == cabecalho[1]-1) cheio = true; // CASO FICOU CHEIO
						return 0;
					
				}
			}
			//menor = menorta(cabecalho, contadoraux);
			if(menor != 0 && cheio == true) {
				int aux = 0;
				for(int i = 0; i < cabecalho[1]; i++) {
					if(contadoraux[i] == menor) {
						aux += 1; 
					}
				}
				if(aux > 1) {
					for(int i = 0; i < cabecalho[1]; i++) {
						if(contadoraux[i] == menor) {
							cache[i] = bloco;
							contadoraux[i] += 1;
							cout << i << endl;
							return 0;
						}
					}
				}else if(aux == 1) {
					for(int i = 0 ; i<cabecalho[1]; i++){
						if(contadoraux[i]==menor){
							cache[i]=bloco;
							contadoraux[i]+=1;
							cout<< i <<endl;
						}
					}
					return 0;
				}
			}

		}
	}
	else if(subs == 4) {
		bool procura = false;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				procura = true;
				contadoraux[i] = 1+contquantos;
				for(int z = 0;z<cabecalho[1];z++){ // 0 4 3 2
					if(contadoraux[z]==cabecalho[1]){
						existemaior=true;
						posmaior=z;
					}
				}
				if(existemaior && posmaior!=i){
					for(int z = 0;z<cabecalho[1];z++){ // 0 0 4 2
						contadoraux[z]--;
						if(contadoraux[z]<=0) contadoraux[z]=0;
					}
				}
				if(contadoraux[i]>=4){
					contadoraux[i]=4;
					existemaior=true;
				}
				contquantos++;
			}
		}
		if(!procura) {
			cout << "MISS -> alocado na linha ";
			for(int i = 0; i < cabecalho[1]; i++) {
					if(cache[i] == -1) { // ACHA ESTA LINHA
						if(existemaior){
							for(int z = 0;z<cabecalho[1];z++){ // 3 2 4 0
								contadoraux[z]--;
								if(contadoraux[z]<=0) contadoraux[z]=0;
							}
						}
						cache[i] = bloco; // SUBSTITUI
						contadoraux[i]=1+contquantos; // UTILIZADO UMA VEZ
						if(contadoraux[i]>cabecalho[1]){
							contadoraux[i]=cabecalho[1];
						}
						cout << i << endl; // QUAL LINHA FOI ALOCADA
						contquantos++;
						if(i == cabecalho[1]-1) cheio = true; //  4*4 2*4 3*4 4*4
						return 0;
					}
			}
			int menor = menorta(cabecalho, contadoraux);
			if(menor != 0 && cheio == true) {
					for(int i = 0; i < cabecalho[1]; i++) {
						if(contadoraux[i] == menor) {
							cache[i] = bloco;
								for(int z = 0;z<cabecalho[1];z++){
									contadoraux[z]--;
								}
								contadoraux[i] = cabecalho[1];
							cout << i << endl;

							return 0;
						}
					}
			}
		}
	}
	return 0;
}
int parcialmenteassociativo(int *cabecalho, int palavra, int* v, int* cont, bool &cheio,int &contquantos, int &posmaior, bool &existemaior) {
	int subs = cabecalho[5];
	int bloco = palavra / cabecalho[0];
	int qtVias = cabecalho[4];
	int via = bloco % qtVias;
	int linhasPorVia = cabecalho[1] / cabecalho[4];

	//ALEATÓRIO
	if(subs == 1) {
		via = rand() % qtVias;

		int linha = rand() % linhasPorVia;

		for(int i = 0; i < qtVias; i++) {
			if(via == i) {
				if(v[linha + linhasPorVia*via] == bloco) cout << "HIT: via " << via << " - Linha: " << linha << endl;
				else {
					v[linha + linhasPorVia*via] = bloco;
					cout << "HIT: via " << via << " - Linha: " << linha << endl;
				}
			}
		}
	}

	//FIFO
	else if(subs == 2) {
		bool estaCompleta = false;

		for(int i = 0; i < cabecalho[1]; i++) {
			if(v[i] == bloco) {
				cout << "HIT: Via: " << i / linhasPorVia << " - Linha: " << i % linhasPorVia << endl;
				estaCompleta = true;
			}
		}

		if(!estaCompleta) {
			cout << "MISS -> alocado na via: " << via << " - Linha: ";

			for(int j = via*linhasPorVia; j < ((via*linhasPorVia) + linhasPorVia); j++) {
				cont[j] += 1;

				if(v[j] == -1) {
					v[j] = bloco;
					cout << j % linhasPorVia << endl;
					if(j == ((via*linhasPorVia) + linhasPorVia)-1) cheio = true;
					return 0;
				}
			}

			if(cheio == true) {
				int maior = maiorta(cabecalho, cont);

				for(int i = via*linhasPorVia; i < ((via*linhasPorVia) + linhasPorVia); i++) {
					if(cont[i] == maior) {
						v[i] = bloco;
						cont[i] = 1;
						cout << i % linhasPorVia << endl;
						return 0;
					}
				}				
			}
		}
	}

	//LFU
	else if(subs == 3) {
		bool estaCompleta = false;

		for(int i = 0; i < cabecalho[1]; i++) {
			if(v[i] == bloco) {
				cout << "HIT: Via: " << i / linhasPorVia << " - Linha: " << i % linhasPorVia << endl;
				estaCompleta = true;
				cont[i] += 1;
			}
		}

		if(!estaCompleta) {
			cout << "MISS -> alocado na via: " << via << " - Linha: ";

			for(int j = via*linhasPorVia; j < ((via*linhasPorVia) + linhasPorVia); j++) {
				if(v[j] == -1) {
					v[j] = bloco;
					cont[j] += 1;
					cout << j % linhasPorVia << endl;
					if(j == ((via*linhasPorVia) + linhasPorVia)-1) cheio = true;
					return 0;
				}
			}

			if(cheio == true) {
				int menor = menorpa(cabecalho, cont,(via*linhasPorVia));
				int aux = 0;
				int aux2;

				for(int i = via*linhasPorVia; i < ((via*linhasPorVia) + linhasPorVia); i++){
					if(cont[i] == menor) {
						aux += 1;
						aux2 = i; 
					}
				}

				if(aux > 1) {
					for(int i = via*linhasPorVia; i < ((via*linhasPorVia) + linhasPorVia); i++) {
						if(cont[i] == menor) {
							v[i] = bloco;
							cont[i] += 1;
							cout << i % linhasPorVia << endl;
							return 0;
						}
					}
				}

				else if(aux == 1) {
					v[aux2] = bloco;
					cont[aux2] += 1;
					cout << aux2 % linhasPorVia << endl;
					return 0;
				}
			}
		}
	}
	//LRU
		else if(subs == 4) {
		bool procura = true;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(v[i] == bloco) {
				cout << "HIT: Via: " << i / linhasPorVia << " - Linha: " << i % linhasPorVia << endl;
				procura = false;
				cont[i] = 1+contquantos;
				for(int z = via*linhasPorVia;z<((via*linhasPorVia) + linhasPorVia);z++){ // 0 4 3 2
					if(cont[z]==linhasPorVia){
						existemaior=true;
						posmaior=z;
					}
				}
				if(existemaior && posmaior!=i){
					for(int z = via*linhasPorVia;z<((via*linhasPorVia) + linhasPorVia);z++){ // 0 0 4 2
						cont[z]--;
						if(cont[z]<=0) cont[z]=0;
					}
				}
				if(cont[i]>=linhasPorVia){
					cont[i]=linhasPorVia;
					existemaior=true;
				}
				contquantos++;
			}
		}
		if(procura) {
			cout << "MISS -> alocado na via: " << via << " - Linha: ";
			for(int i = via*linhasPorVia; i < ((via*linhasPorVia) + linhasPorVia)	; i++) { // via*linhasPorVia = 2 * 2
					if(v[i] == -1) { // ACHA ESTA LINHA
						if(existemaior){
							for(int z = via*linhasPorVia;z<((via*linhasPorVia) + linhasPorVia);z++){ // 3 2 4 0
								cont[z]--;
								if(cont[z]<=0) cont[z]=0;
							}
						}
						v[i] = bloco; // SUBSTITUI
						cont[i]=1+contquantos; // UTILIZADO UMA VEZ
						if(cont[i]>linhasPorVia){
							cont[i]=linhasPorVia;
						}
						cout << i%linhasPorVia << endl; // QUAL LINHA FOI ALOCADA
						contquantos++;
						if(i == linhasPorVia-1) cheio = true; //  4*4 2*4 3*4 4*4
						return 0;
					}
			}
			int menor =menorpa(cabecalho,cont,(via*linhasPorVia));
			if(menor != 0 && cheio == true) {
					for(int i =  via*linhasPorVia; i < ((via*linhasPorVia) + linhasPorVia); i++) {
						if(cont[i] == menor) {
							v[i] = bloco;
								for(int z = via*linhasPorVia;z<((via*linhasPorVia) + linhasPorVia);z++){
									cont[z]--;
									if(cont[z]<=0) cont[z]=1;
								}
							cont[i] = linhasPorVia;
							cout << i%linhasPorVia << endl;

							return 0;
						}
					}
			}
		}
	}
	return 0;
}