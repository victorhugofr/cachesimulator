#ifndef PROCESSOS_HPP
#define PROCESSOS_HPP
#include <iostream>
using namespace std;
void mapeamentodireto(int *cabecalho, int palavra, int * cache);
int maiorta(int* cabecalho, int* contadoraux);
int menorta(int* cabecalho, int* contadoraux);
int totalmenteassociativo(int *cabecalho, int palavra, int* cache, int* contadoraux, bool &cheio, int &contquantos, int &posmaior, bool &existemaior);
int parcialmenteassociativo(int *cabecalho, int palavra, int* cache, int* contadoraux, bool &cheio,int &contquantos, int &posmaior, bool &existemaior);
#endif