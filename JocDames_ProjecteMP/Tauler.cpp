#include <fstream>
#include "Tauler.h"

using namespace std;

void Tauler::inicialitza(const string& nomFitxer)
{
    //Abro el fichero que nos han pasado como parametros
    ifstream ficher(nomFitxer);
    if (ficher.is_open())
    {
        //Inicializo primero todas las casillas como empty 
        for (int i = 0; i < N_FILES; i++)
        {
            for (int j = 0; j < N_COLUMNES; j++)
            {
                m_tauler [i][j] = Fitxa(TIPUS_EMPTY, i, j);
            }
            
        }
        
        //Ahora extraigo los datos de el fichero linea por linea y modifico sus respectivos atributos segun los datos leidos
        char tipus;
        char x;
        int y;
        while (ficher >> tipus >> x >> y)
        {
            int Y = y - 1;
            int X = x - 'a';
            switch (tipus)
            {
            case 'O':
                m_tauler [X][Y].setTipus(TIPUS_NORMAL);
                m_tauler [X][Y].setColor(COLOR_BLANC);
                break;
            case 'X':
                m_tauler [X][Y].setTipus(TIPUS_NORMAL);
                m_tauler [X][Y].setColor(COLOR_NEGRE);
                break;
            case 'D':
                m_tauler [X][Y].setTipus(TIPUS_DAMA);
                m_tauler [X][Y].setColor(COLOR_BLANC);
                break;
            case 'R':
                m_tauler [X][Y].setTipus(TIPUS_DAMA);
                m_tauler [X][Y].setColor(COLOR_NEGRE);
                break;
            default:
                break;
            }
        }
    }
}

void Tauler::actualitzaMovimentsValids()
{
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            if (m_tauler[i][j].getTipus() == TIPUS_NORMAL)
            {
                if (m_tauler[i][j].getColor() == COLOR_BLANC)
                {
                    buscaMovimentsValidSimple(i, j, 1);
                }
                else
                {
                    buscaMovimentsValidSimple(i, j, -1);
                }
            } 
            else if (m_tauler[i][j].getTipus() == TIPUS_DAMA) 
            {
                buscaMovimentsDama(i, j);
            }
        }
        
    }
    
}

void Tauler::asigna(int i, int j)
{
    Posicio p;
    p.setPosicio(p.PosicioAString(i, j));
    m_tauler[i][j].afegirMovimentValid(Moviment(p));
}

void Tauler::getPosicionsPossibles (Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
{
    int i, j, direccio;
    origen.stringToInts(origen.getPosicio(), i, j);
    if (m_tauler[i][j].getColor() = COLOR_BLANC) direccio = 1;
    //Comprobamos los movimientos simples antes de pasar al bfs
    if (i + direccio >= 0 && i + direccio < N_FILES && j + 1 >= 0 && j + 1 < N_COLUMNES)
    {
        if (m_tauler[i + direccio][j + 1].getTipus() == TIPUS_EMPTY)
        {
            asigna(i + direccio, j + 1);
        }
       
    }
    if (i + direccio >= 0 && i + direccio < N_FILES && j - 1 >= 0 && j - 1 < N_COLUMNES)
    {
        if (m_tauler[i + direccio][j - 1].getTipus() == TIPUS_EMPTY)
        {
            asigna(i + direccio, j - 1);
        }
        
    }
}

 /*else if (m_tauler[i + direccio][j + 1].getColor() != m_tauler[i][j].getColor())
        {
            // Check for capture move (two squares ahead)
            if (i + 2*direccio >= 0 && i + 2*direccio < N_FILES && j + 2 >= 0 && j + 2 < N_COLUMNES && m_tauler[i + 2*direccio][j + 2].getTipus() == TIPUS_EMPTY)
            {
                asigna(i + 2*direccio, j + 2);
                trobat = true;
            }
        }*/
       /*else if (m_tauler[i + direccio][j - 1].getColor() != m_tauler[i][j].getColor())
        {
            // Check for capture move (two squares ahead)
            if (i + 2*direccio >= 0 && i + 2*direccio < N_FILES && j - 2 >= 0 && j - 2 < N_COLUMNES && m_tauler[i + 2*direccio][j - 2].getTipus() == TIPUS_EMPTY)
            {
                asigna(i + 2*direccio, j - 2);
                trobat = true;
            }
        }
        */