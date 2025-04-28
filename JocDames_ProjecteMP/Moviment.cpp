#include<iostream>
#include"Moviment.h"

void Moviment::calcularDireccion()
{
	if (m_origen.getPosicio()[0] < m_desti.getPosicio()[0])
	{
		m_direccionMovimento = 'd';
	}
	else if (m_origen.getPosicio()[0] > m_desti.getPosicio()[0])
	{
		m_direccionMovimento = 'e';
	}
}

bool Moviment::movimentNormal()
{



}