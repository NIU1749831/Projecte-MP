#include <iostream>
#include "posicio.hpp"
#include <sstream>

bool Posicio::operator==(Posicio posicio) const
{
	return (m_posicio==posicio.m_posicio);
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

void Posicio::stringToInts(const string& posicio, int& i, int& j)const
{
	j=posicio[0]; //el numero de columnas (el valor de x), es una letra
	i=posicio[1]; //el numero de filas (el valor de y), es un numero

	j -= 97;
	i -= 48;
}

ostream& operator<<(ostream& out, const Posicio& pos)
{
	return out << pos.getPosicio();
}