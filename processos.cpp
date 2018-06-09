#include "processos.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
using namespace std;
void mapeamentodireto(int *cabecalho, int palavra, int * v){ // read25
	//int palavra2=stoi(palavra);
	int bloco = palavra / cabecalho[0]; // 6
	int linha = bloco % cabecalho[1]; // 2
	if(v[linha] == bloco) cout << "HIT: linha " << linha << endl; 
	else {
		v[linha] = bloco;
		cout << "MISS -> alocado na linha " << linha << endl;
	}
}
int maiorta(int* cabecalho, int* cont) {
	int maior = 0;
	for(int j = 0; j < cabecalho[1]; j++) {
		if(maior < cont[j]) maior = cont[j];
	}
	return maior;
}
int menorta(int* cabecalho, int* cont){
	int menor = cont[0];
	for(int j = 0; j < cabecalho[1]; j++) {
		if(cont[j] == 0) return 0;
	}
	for(int i = 1; i < cabecalho[1]; i++) {
		if(cont[i] < menor) menor = cont[i];
	}
	return menor;
}
int totalmenteassociativo(int *cabecalho, int palavra, int* v, int* cont, bool &cheio,int &contquantos, int &posmaior, bool &existemaior) {	
	//int palavra2=stoi(palavra);
	int subs = cabecalho[5];
	int bloco = palavra / cabecalho[0];
	//ALEATORIO
	if(subs == 1) {	
		bool procura = false;
		int linha = rand() % cabecalho[1];
		for(int i = 0; i < cabecalho[1]; i++) {
			if(v[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				procura = true;
			}
		}
		//if(v[linha] == bloco) cout << "HIT: linha " << linha << endl;
		if(!procura) {
			v[linha] = bloco;
			cout << "MISS -> alocado na linha " << linha << endl;
		}
	}
	//FIFO(FILA)
	else if(subs == 2) {
		bool procura = false;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(v[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				procura = true;
			}
		}
		if(!procura) {
			cout << "MISS -> alocado na linha ";
			int maior = maiorta(cabecalho, cont);
			for(int j = 0; j < cabecalho[1]; j++) {
				cont[j] += 1;
				if(maior == 0) {
					v[0] = bloco;
					cout << "0" << endl; // CASO NAO HAJA MAIOR(SEJA O PRIMEIRO A ENTRAR NA CACHE)ALOCA NA LINHA 0 DA CACHE
					return 0;
				}

				else if(maior != 0) { // SE NAO, ALOCA NO BLOCO QUE AINDA NAO ALOCOU(REPRESSENTADO POR -1)
					if(v[j] == -1) {
						v[j] = bloco;
						cout << j << endl;
						if(j == cabecalho[1]-1) cheio = true; // VERIFICACAO SE CACHE ESTA CHEIO
						return 0;
					}
				}
			}
			if(maior != 0 && cheio == true) {
				maior = maiorta(cabecalho, cont);
				for(int i = 0; i < cabecalho[1]; i++) {
					if(cont[i] == maior) { // SE A CHACE JA ESTAVA CHEIA, ALOCA NO MAIOR E DEPOIS GERA O QUE ALOCOU = 1;
						v[i] = bloco;
						cont[i] = 1;
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
		for(int i = 0; i < cabecalho[1]; i++) {
			if(v[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				procura = true;
				cont[i] += 1;
			}
		}
		if(!procura) {
			cout << "MISS -> alocado na linha ";
			int menor = menorta(cabecalho, cont);
			for(int i = 0; i < cabecalho[1]; i++) {
				if(menor == 0) { // ALGUMA LINHA NAO FOI UTILIZADA AINDA
					if(v[i] == -1) { // ACHA ESTA LINHA
						v[i] = bloco; // SUBSTITUI
						cont[i] += 1; // UTILIZADO UMA VEZ
						cout << i << endl; // QUAL LINHA FOI ALOCADA
						if(i == cabecalho[1]-1) cheio = true; // CASO FICOU CHEIO
						return 0;
					}
				}
			}
			menor = menorta(cabecalho, cont);
			if(menor != 0 && cheio == true) {
				int aux = 0;
				for(int i = 0; i < cabecalho[1]; i++) {
					if(cont[i] == menor) {
						aux += 1; 
					}
				}
				if(aux > 1) {
					for(int i = 0; i < cabecalho[1]; i++) {
						if(cont[i] == menor) {
							v[i] = bloco;
							cont[i] = 1;
							cout << i << endl;
							return 0;
						}
					}
				}else if(aux == 1) {
					for(int i = 0 ; i<cabecalho[1]; i++){
						if(cont[i]==menor){
							v[i]=bloco;
							cont[i]=1;
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
			if(v[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				procura = true;
				cont[i] = 1+contquantos;
				for(int z = 0;z<cabecalho[1];z++){ // 0 4 3 2
					if(cont[z]==cabecalho[1]){
						existemaior=true;
						posmaior=z;
					}
				}
				if(existemaior && posmaior!=i){
					for(int z = 0;z<cabecalho[1];z++){ // 0 0 4 2
						cont[z]--;
						if(cont[z]<=0) cont[z]=0;
					}
				}
				if(cont[i]>=4){
					cont[i]=4;
					existemaior=true;
				}
				contquantos++;
			}
		}
		if(!procura) {
			cout << "MISS -> alocado na linha ";
			for(int i = 0; i < cabecalho[1]; i++) {
					if(v[i] == -1) { // ACHA ESTA LINHA
						if(existemaior){
							for(int z = 0;z<cabecalho[1];z++){ // 3 2 4 0
								cont[z]--;
								if(cont[z]<=0) cont[z]=0;
							}
						}
						v[i] = bloco; // SUBSTITUI
						cont[i]=1+contquantos; // UTILIZADO UMA VEZ
						if(cont[i]>4){
							cont[i]=4;
						}
						cout << i << endl; // QUAL LINHA FOI ALOCADA
						contquantos++;
						if(i == cabecalho[1]-1) cheio = true; //  4*4 2*4 3*4 4*4
						return 0;
					}
			}
			int menor = menorta(cabecalho, cont);
			if(menor != 0 && cheio == true) {
					for(int i = 0; i < cabecalho[1]; i++) {
						if(cont[i] == menor) {
							v[i] = bloco;
								for(int z = 0;z<cabecalho[1];z++){
									cont[z]--;
								}
								cont[i] = 4;
							cout << i << endl;

							return 0;
						}
					}
			}
		}
	}
	return 0;
}