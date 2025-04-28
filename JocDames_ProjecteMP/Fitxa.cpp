#include<iostream>
#include"Fitxa.h"

Fitxa::Fitxa(TipusFitxa tipus, int x, int y)
{
	m_tipus = tipus;
	m_color = COLOR_BLANC;
	m_posicio.setPosicio(m_posicio.PosicioAString(x, y));
}