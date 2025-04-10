#include"Posicio.h"

bool Posicio::operator==(const string& posicio)
{
	bool comparacio;
	if (m_posicio == posicio)
		comparacio = true;
	else
		comparacio = false;

	return comparacio;
}

string Posicio::PosicioAString(int columna, int fila)
{
	char x = 'a' + columna;
	char y = '1' + fila;
	string posicio = x + y;

	return posicio;
}

