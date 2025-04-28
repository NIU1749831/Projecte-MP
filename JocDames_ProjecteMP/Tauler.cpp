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
                m_tauler [i][j].Fitxa(TIPUS_EMPTY, i, j);
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

}