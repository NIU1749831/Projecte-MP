#include<iostream>
#include<sstream>
#include"Fitxa.h"

Fitxa::Fitxa(TipusFitxa tipus, ColorFitxa color, Posicio posico, int numMovimentsValids, Moviment movimentsValids[10])
{
	for (int i = 0; i < 11; i++)
		m_movimentsValids[i] = movimentsValids[i];
}

void Fitxa::convertirADama()
{
	m_tipus = TIPUS_DAMA;
}

void Fitxa::afegirMovimentValid(const Moviment& moviment)
{
	m_movimentsValids[m_numMovimentsValids++] = moviment;
}

void Fitxa::stringToInts(const Posicio& p, int& i, int& j)
{
	//convertimos la posicion a una variable de la cual podemos leer su contenido
	istringstream posicio(p.getPosicio());
	posicio >> j; //el numero de columnas (el valor de x), es una letra
	posicio >> i; //el numero de filas (el valor de y), es un numero

	j -= 97;
	i -= 48;
}