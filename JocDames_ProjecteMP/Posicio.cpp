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

string Posicio::PosicioAString()
{
	char x = 'a' + m_x;
	char y = '1' + m_y;
	string posicio = x + y;

	return posicio;
}

void Posicio::stringToInts(const Posicio& p, int& i, int& j)
{
	//convertimos la posicion a una variable de la cual podemos leer su contenido
	istringstream posicio(p.getPosicio());
	posicio >> j; //el numero de columnas (el valor de x), es una letra
	posicio >> i; //el numero de filas (el valor de y), es un numero

	j -= 97;
	i -= 48;
}