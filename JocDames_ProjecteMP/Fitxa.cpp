#include<iostream>
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