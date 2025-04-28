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

string Posicio::PosicioAString()
{
	char x = 'a' + m_x;
	char y = '1' + m_y;
	string posicio = x + y;

	return posicio;
}

