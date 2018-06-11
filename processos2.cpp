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
int parcialmenteassociativo(int *cabecalho, int palavra, int* cache, int* contadoraux, bool &cheio,int &contquantos, int &posmaior, bool &existemaior){
	int subs = cabecalho[5];
	int bloco = palavra / cabecalho[0];
	int qtdvias = cabecalho[4];
	int via = bloco % qtdvias;
	int linhaspv = cabecalho[1] / cabecalho[4];
	int auxx=via*linhaspv;
	//ALEATÓRIO
	if(subs == 1) {
		via = rand() % qtdvias;
		int linha = rand() % linhaspv;
		for(int i = 0; i < qtdvias; i++) {
			if(via == i) {
				if(cache[auxx+linha] == bloco) cout << "HIT: via " << via << " - Linha: " << linha << endl;
				else {
					cache[auxx+linha] = bloco;
					cout << "HIT: via " << via << " - Linha: " << linha << endl;
				}
			}
		}
	}
			//FIFO
	else if(subs == 2) {
		bool procura = false;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i]==bloco){
				cout << "HIT: Via: " << i / linhaspv << " - Linha: " << i % linhaspv << endl;
				procura = true;
			}
		}
		if(!procura) {
			cout << "MISS -> alocado na via: " << via << " - Linha: ";
			for(int i = auxx; i < auxx + linhaspv; i++) {
				contadoraux[i] += 1;
				if(cache[i] == -1) {
					cache[i] = bloco;
					cout << i % linhaspv << endl;
					if(i == auxx + linhaspv-1) cheio = true;
					return 0;
				}
			}
			if(cheio == true) {
				int maior = maiorta(cabecalho, contadoraux);
				for(int i = auxx; i < auxx + linhaspv; i++) {
					if(contadoraux[i] == maior) {
						cache[i] = bloco;
						contadoraux[i] = 1;
						cout << i % linhaspv << endl;
						return 0;
					}
				}				
			}
		}
	}

	//LFU
	else if(subs==3){
		bool procura = false;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i]==bloco){
				cout << "HIT: Via: " << i / linhaspv << " - Linha: " << i % linhaspv << endl;
				procura = true;
				contadoraux[i] += 1;
			}
		}
		if(!procura) {
			cout << "MISS -> alocado na via: " << via << " - Linha: ";
			for(int i = auxx; i < auxx + linhaspv; i++) {
				if(cache[i] == -1) {
					cache[i] = bloco;
					contadoraux[i] += 1;
					cout << i % linhaspv << endl;
					if(i == auxx + linhaspv-1) cheio = true;
					return 0;
				}
			}
			if(cheio == true) {
				int menor = menorta(cabecalho, contadoraux);
				int aux = 0;
				int aux2;
				for(int i = auxx; i < auxx+linhaspv; i++){
					if(contadoraux[i] == menor) {
						aux += 1;
						aux2 = i; 
					}
				}
				if(aux > 1) {
					for(int i = auxx; i < auxx + linhaspv; i++) {
						if(contadoraux[i] == menor) {
							cache[i] = bloco;
							contadoraux[i] = 1;
							cout << i % linhaspv << endl;
							return 0;
						}
					}
				}else if(aux == 1){
					cache[aux2] = bloco;
					contadoraux[aux2] = 1;
					cout << aux2 % linhaspv << endl;
					return 0;
				}
			}
		}
	}
	//LRU
		else if(subs == 4) {
		bool procura = false;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i] == bloco) {
				cout << "HIT: Via: " << i / linhaspv << " - Linha: " << i % linhaspv << endl;
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
			cout << "MISS -> alocado na via: " << via << " - Linha: ";
			for(int i = 0; i < cabecalho[1]	; i++) { // auxx = 2 * 2
					if(cache[i] == -1) { // ACHA ESTA LINHA
						if(existemaior){
							for(int z = 0;z<cabecalho[1];z++){ // 3 2 4 0
								contadoraux[z]--;
								if(contadoraux[z]<=0) contadoraux[z]=0;
							}
						}
						cache[i] = bloco; // SUBSTITUI
						contadoraux[i]=1+contquantos; // UTILIZADO UMA VEZ
						if(contadoraux[i]>cabecalho[i]){
							contadoraux[i]=cabecalho[i];
						}
						cout << i%linhaspv << endl; // QUAL LINHA FOI ALOCADA
						contquantos++;
						if(i == cabecalho[1]-1) procura = true; //  4*4 2*4 3*4 4*4
						return 0;
					}
			}
			int menor =menorta(cabecalho,contadoraux);
			if(menor != 0 && procura == true) {
					for(int i = 0; i < cabecalho[1]; i++) {
						if(contadoraux[i] == menor) {
							cache[i] = bloco;
								for(int z = 0;z<cabecalho[1];z++){
									contadoraux[z]--;
								}
								contadoraux[i] = cabecalho[1];
							cout << i%linhaspv << endl;

							return 0;
						}
					}
			}
		}
	}
	return 0;
}
