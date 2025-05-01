#include<iostream>
#include<sstream>
#include"Fitxa.h"

Fitxa::Fitxa(TipusFitxa tipus, Posicio posico)
{
	m_tipus = tipus;
	m_color = COLOR_BLANC;
	m_numMovimentsValids = 0;
	
}

void Fitxa::convertirADama()
{
	m_tipus = TIPUS_DAMA;
}

void Fitxa::afegirMovimentValid(const Moviment& moviment)
{
	m_movimentsValids[m_numMovimentsValids++] = moviment;
}

