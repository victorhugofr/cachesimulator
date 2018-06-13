#ifndef PROCESSOS_HPP
#define PROCESSOS_HPP
#include <iostream>
using namespace std;
void mapeamentodireto(int *cabecalho, int palavra, int * cache);
int maiorta(int* cabecalho, int* contadoraux);
int menorta(int* cabecalho, int* contadoraux);
int menorpa(int *cabecalho, int *contadoraux, int inicioBusca);
void totalmentealeatorio (int*cabecalho, int palavra,int*cache);
void totalmentefifo(int*cabecalho,int palavra, int *cache, int *contadoraux, bool &cheio);
void totalmentelfu(int*cabecalho,int palavra, int *cache, int *contadoraux, bool &cheio);
void totalmentelru(int *cabecalho, int palavra, int* cache, int* contadoraux, bool &cheio,int &contquantos, int &posmaior, bool &existemaior);
void totalmenteassociativo(int *cabecalho, int palavra, int* cache, int* contadoraux, bool &cheio, int &contquantos, int &posmaior, bool &existemaior);
void parcialmentealeatorio(int *cabecalho, int*v, int palavra);
void parcialmentefifo(int *cabecalho,int *v, int palavra, int*cont, bool &cheio);
void parcialmentelfu(int *cabecalho, int *v,int palavra, bool &cheio, int* cont);
void parcialmentelru(int *cabecalho,int *v,int palavra, int*cont, bool &cheio,int &contquantos, int &posmaior, bool &existemaior);
void parcialmenteassociativo(int *cabecalho, int palavra, int* v, int* cont, bool &cheio,int &contquantos, int &posmaior, bool &existemaior);
#endif