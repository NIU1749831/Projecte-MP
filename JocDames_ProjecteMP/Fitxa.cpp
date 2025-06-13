#include "Fitxa.h"
#include <iostream>
#include<sstream>

Fitxa::Fitxa(TipusFitxa tipus, Posicio posicio)
{
    m_tipus = tipus;
    m_color = COLOR_BLANC;
    m_posicio = posicio;
    m_numMovimentsValids = 0;
}

void Fitxa::convertirADama()
{
    if (m_tipus == TIPUS_NORMAL)
        m_tipus = TIPUS_DAMA;
}

void Fitxa::afegirMovimentValid(const Moviment& moviment)
{
    if (m_numMovimentsValids < 10)
        m_movimentsValids[m_numMovimentsValids++] = moviment;
}

void Fitxa::netejarMoviments()
{
    m_numMovimentsValids = 0;
}

void Fitxa::setMovimentsValids(const vector<Moviment>& moviments) {
    netejarMoviments();
    for (const Moviment& m : moviments) {
        afegirMovimentValid(m);
    }
}

void Fitxa::visualitza() const
{
    if (m_tipus == TIPUS_EMPTY)
        return;
    

    if (m_tipus != TIPUS_EMPTY)
    {
        int col, fila;

        m_posicio.stringToInts(m_posicio.getPosicio(), fila, col);

        int x = CASELLA_INICIAL_X + col * AMPLADA_CASELLA + correcioErrorPosicioX + AMPLADA_CASELLA;
        int y = CASELLA_INICIAL_Y + fila * ALCADA_CASELLA + correcioErrorPosicioY;

        if (m_color == COLOR_BLANC)
        {
            if (m_tipus == TIPUS_DAMA)
            {
                GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_BLANCA, x, y);
            }
            else
            {
                GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, x, y);
            }
        }
        else if (m_color == COLOR_NEGRE)
        {
            if (m_tipus == TIPUS_DAMA)
            {
                GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_NEGRA, x, y);
            }
            else
            {
                GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_NEGRA, x, y);
            }
        }
    }
}