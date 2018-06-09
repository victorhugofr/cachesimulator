#ifndef PROCESSOS_HPP
#define PROCESSOS_HPP
#include <iostream>
using namespace std;
void mapeamentodireto(int *cabecalho, int palavra, int * v);
int maiorta(int* cabecalho, int* cont);
int menorta(int* cabecalho, int* cont);
int totalmenteassociativo(int *cabecalho, int palavra, int* v, int* cont, bool &cheio, int &contquantos, int &posmaior, bool &existemaior);
#endif