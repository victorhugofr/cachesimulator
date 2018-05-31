#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#ifndef PROCESSOS_HPP
#define PROCESSOS_HPP
void mapeamentodireto(int *cabecalho, string palavra, int * v);
int maiorta(int* cabecalho, int* cont);
int menorta(int* cabecalho, int* cont);
int totalmenteassociativo(int *cabecalho, string palavra, int* v, int* cont, bool &cheio);
#endif