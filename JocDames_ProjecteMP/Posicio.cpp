#include <iostream>
#include "Posicio.h"
#include <sstream>

bool Posicio::operator==(const string& posicio)
{
	bool comparacio;
	if (m_posicio == posicio)
		comparacio = true;
	else
		comparacio = false;

	return comparacio;
}

string Posicio::PosicioAString(int x, int y)
{
	char cx = 'a' + x;
	char cy = '1' + y;
	string posicio;
	posicio += cx;
	posicio += cy;

	return posicio;
}

void Posicio::stringToInts(const string& posicio, int& i, int& j)
{
	j=posicio[0]; //el numero de columnas (el valor de x), es una letra
	i=posicio[1]; //el numero de filas (el valor de y), es un numero

	j -= 97;
	i -= 48;
}