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
int menorpa(int *cabecalho, int *contadoraux, int iniciovia){
	int menor = contadoraux[iniciovia];
	for(int i = iniciovia; i < (iniciovia + (cabecalho[1] / cabecalho[4])); i++) {
		if(contadoraux[i] == 0) return 0;
	}

	for(int i = iniciovia + 1; i < (iniciovia + (cabecalho[1] / cabecalho[4])); i++) {
		if(contadoraux[i] < menor) menor = contadoraux[i];
	}
	return menor;
}
int totalmenteassociativo(int *cabecalho, int palavra, int* cache, int* contadoraux, bool &cheio,int &contquantos, int &posmaior, bool &existemaior) {	
	int subs = cabecalho[5];
	int bloco = palavra / cabecalho[0];
	//ALEATORIO
	if(subs == 1) {	
		int linha = rand() % cabecalho[1];
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				return 0;
			}
		}
		cache[linha] = bloco;
		cout << "MISS -> alocado na linha " << linha << endl;
	}
	//FIFO(FILA)
	else if(subs == 2) {
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				return 0;
			}
		}
			cout << "MISS -> alocado na linha ";
			int maior = maiorta(cabecalho, contadoraux);
			for(int j = 0; j < cabecalho[1]; j++) {
				contadoraux[j] += 1;
				if(maior == 0) {
					cache[0] = bloco;
					cout << "0" << endl; // CASO NAO HAJA MAIOR(SEJA O PRIMEIRO A ENTRAR NA CACHE)ALOCA NA LINHA 0 DA CACHE
					return 0;
				}
					if(cache[j] == -1) {
						cache[j] = bloco;
						cout << j << endl;
						if(j == cabecalho[1]-1) cheio = true; // VERIFICACAO SE CACHE ESTA CHEIO
						return 0;
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
	//LFU(MENOS FREQUENTEMENTE UTILIZADO)
	else if(subs == 3) {
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				contadoraux[i] += 1;
				return 0;
			}
		}
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
	//LRU
	else if(subs == 4) {
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i] == bloco) {
				cout << "HIT: linha " << i << endl;
				contadoraux[i] = 1+contquantos;
				for(int z = 0;z<cabecalho[1];z++){ // 0 4 3 2
					if(contadoraux[z]==cabecalho[1]){
						existemaior=true;
						posmaior=i;
					}
				}
				if(existemaior && posmaior!=i){
					for(int z = 0;z<cabecalho[1];z++){ // 1 2 3 4
						contadoraux[z]--;
						if(contadoraux[z]<=0) contadoraux[z]=1;
					}
				}
				if(contadoraux[i]>=cabecalho[1]){
					contadoraux[i]=cabecalho[1];
					existemaior=true;
				}
				contquantos++;
				return 0;
			}
		}
		cout << "MISS -> alocado na linha ";
		for(int i = 0; i < cabecalho[1]; i++) {
			if(cache[i] == -1) { // ACHA ESTA LINHA
				if(existemaior){
					for(int z = 0;z<cabecalho[1];z++){ // 3 2 4 0
						contadoraux[z]--;
						if(contadoraux[z]<=0) contadoraux[z]=1;
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
								if(contadoraux[z]<=0){
									contadoraux[z]=1;
								}
							}
							contadoraux[i] = cabecalho[1];
						cout << i << endl;
						return 0;
					}
				}
		}
	}
	return 0;
}
void parcialmentealeatorio(int *cabecalho, int*v, int palavra){
	int qtddevias = cabecalho[4];
	int linhaspv = cabecalho[1] / cabecalho[4];
	int bloco = palavra / cabecalho[0];
	int	via = rand() % qtddevias;
	int linha = rand() % linhaspv;
	for(int i=0; i<cabecalho[1];i++){
		if(v[i]==bloco){
			cout << "HIT: via " << i/linhaspv << " - Linha: " << i%linhaspv << endl;
			return;
		}
	}
		v[linha + linhaspv*via] = bloco;
		cout << "MISS-> alocado na via: " << via << " - Linha: " << linha << endl;
}
void parcialmentefifo(int *cabecalho,int *v, int palavra, int* cont, bool &cheio){
	int linhaspv = cabecalho[1] / cabecalho[4];
	int bloco = palavra / cabecalho[0];
	int qtVias = cabecalho[4];
	int via = bloco % qtVias;
	int auxx=via*linhaspv;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(v[i] == bloco) {
				cout << "HIT: Via: " << i / linhaspv << " - Linha: " << i % linhaspv << endl;
				return;
			}
		}
		cout << "MISS -> alocado na via: " << via << " - Linha: ";
		for(int j = auxx; j < ((auxx) + linhaspv); j++) {
			cont[j] += 1;
				if(v[j] == -1) {
				v[j] = bloco;
				cout << j % linhaspv << endl;
				if(j == ((auxx) + linhaspv)-1) cheio = true;
				return;
			}
		}
		if(cheio == true) {
			int maior = maiorta(cabecalho, cont);
			for(int i = auxx; i < ((auxx) + linhaspv); i++) {
				if(cont[i] == maior) {
					v[i] = bloco;
					cont[i] = 1;
					cout << i % linhaspv << endl;
					return ;
				}
			}				
		}
}
void parcialmentelfu(int *cabecalho, int *v,int palavra, bool &cheio, int* cont){
	int bloco = palavra / cabecalho[0];
	int qtVias = cabecalho[4];
	int via = bloco % qtVias;
	int linhaspv = cabecalho[1] / cabecalho[4];
	int auxx=via*linhaspv;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(v[i] == bloco) {
				cout << "HIT: Via: " << i / linhaspv << " - Linha: " << i % linhaspv << endl;
				cont[i] += 1;
				return;
			}
		}
			cout << "MISS -> alocado na via: " << via << " - Linha: ";
			for(int j = auxx; j < ((auxx) + linhaspv); j++) {
				if(v[j] == -1) {
					v[j] = bloco;
					cont[j] += 1;
					cout << j % linhaspv << endl;
					if(j == ((auxx) + linhaspv)-1) cheio = true;
					return;
				}
			}
			if(cheio == true) {
				int menor = menorpa(cabecalho, cont,(auxx));
				int aux = 0;
				int aux2;
				for(int i = auxx; i < ((auxx) + linhaspv); i++){
					if(cont[i] == menor) {
						aux += 1;
						aux2 = i; 
					}
				}
				if(aux > 1) {
					for(int i = auxx; i < ((auxx) + linhaspv); i++) {
						if(cont[i] == menor) {
							v[i] = bloco;
							cont[i] += 1;
							cout << i % linhaspv << endl;
							return;
						}
					}
				}
				else if(aux == 1) {
					v[aux2] = bloco;
					cont[aux2] += 1;
					cout << aux2 % linhaspv << endl;
					return;
				}
			}
}
void parcialmentelru(int *cabecalho,int *v,int palavra, int*cont, bool &cheio,int &contquantos, int &posmaior, bool &existemaior){
	int bloco = palavra / cabecalho[0];
	int qtVias = cabecalho[4];
	int via = bloco % qtVias;
	int linhaspv = cabecalho[1] / cabecalho[4];
	int auxx=via*linhaspv;
		for(int i = 0; i < cabecalho[1]; i++) {
			if(v[i] == bloco) {
				cout << "HIT: Via: " << i / linhaspv << " - Linha: " << i % linhaspv << endl;
				cont[i] = 1+contquantos;
				for(int z = auxx;z<((auxx) + linhaspv);z++){ // 0 4 3 2
					if(cont[z]==linhaspv){
						existemaior=true;
						posmaior=i;
					}
				}
				if(existemaior && posmaior!=i){
					for(int z = auxx;z<((auxx) + linhaspv);z++){ // 0 0 4 2
						cont[z]--;
						if(cont[z]<=0) cont[z]=1;
					}
				}
				if(cont[i]>=linhaspv){
					cont[i]=linhaspv;
					existemaior=true;
				}
				contquantos++;
				return;
			}
		}
		cout << "MISS -> alocado na via: " << via << " - Linha: ";
		for(int i = auxx; i < ((auxx) + linhaspv)	; i++) { // auxx = 2 * 2
				if(v[i] == -1) { // ACHA ESTA LINHA
					if(existemaior){
						for(int z = auxx;z<((auxx) + linhaspv);z++){ // 3 2 4 0
							cont[z]--;
							if(cont[z]<0) cont[z]=0;
						}
					}
					v[i] = bloco; // SUBSTITUI
					cont[i]=1+contquantos; // UTILIZADO UMA VEZ
					if(cont[i]>linhaspv){
						cont[i]=linhaspv;
					}
					cout << i%linhaspv << endl; // QUAL LINHA FOI ALOCADA
					contquantos++;
					if(i == linhaspv-1) cheio = true; //  4*4 2*4 3*4 4*4
					return;
				}
		}
		int menor =menorpa(cabecalho,cont,(auxx));
		if(menor != 0 && cheio == true) {
				for(int i =  auxx; i < ((auxx) + linhaspv); i++) {
					if(cont[i] == menor) {
						v[i] = bloco;
							for(int z = auxx;z<((auxx) + linhaspv);z++){
								cont[z]--;
								if(cont[z]<=0) cont[z]=1;
							}
						cont[i] = linhaspv;
						cout << i%linhaspv << endl;
						return;
					}
				}
		}
}
void parcialmenteassociativo(int *cabecalho, int palavra, int* v, int* cont, bool &cheio,int &contquantos, int &posmaior, bool &existemaior) {
	int subs = cabecalho[5];
	if(subs == 1) {
		parcialmentealeatorio(cabecalho,v,palavra);
	}
	else if(subs == 2) {
		parcialmentefifo(cabecalho,v,palavra,cont,cheio);
	}
	//LFU
	else if(subs == 3) {
		parcialmentelfu(cabecalho,v,palavra,cheio,cont);
	}
	//LRU
	else if(subs == 4) {
		parcialmentelru(cabecalho,v,palavra,cont,cheio,contquantos,posmaior,existemaior);
	}
}