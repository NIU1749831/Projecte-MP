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

    //Pasamos la variable origen a i y j
    origen.stringToInts(origen.getPosicio(), i, j);

    //Ponemos direccion a 1 si la pieza es blanca debido a que solo van hacia arriba, y direccion a -1 si es negra porque va hacia abajo
    if (m_tauler[i][j].getColor() == COLOR_BLANC) direccio = 1;
    else if (m_tauler[i][j].getColor() == COLOR_BLANC) direccio = -1;

    //Comprobamos los movimientos simples antes de pasar al bfs
    if (i + direccio >= 0 && i + direccio < N_FILES && j + 1 >= 0 && j + 1 < N_COLUMNES)
    {
        if (m_tauler[i + direccio][j + 1].getTipus() == TIPUS_EMPTY)
        {
            posicionsPossibles[nPosicions] = m_tauler[i + direccio][j + 1].getPosicio();
            nPosicions++;
        }
       
    }
    if (i + direccio >= 0 && i + direccio < N_FILES && j - 1 >= 0 && j - 1 < N_COLUMNES)
    {
        if (m_tauler[i + direccio][j - 1].getTipus() == TIPUS_EMPTY)
        {
            posicionsPossibles[nPosicions] = m_tauler[i + direccio][j - 1].getPosicio();
            nPosicions++;
        }
        
    }
}

void Tauler::bfs(int i, int j, int direccio, Posicio posicionsPossibles[], int& nPosicions)
{
    int k = 0;
    // bsf per les fitxes blanques
    if (direccio == 1)
    {
        do
        {
            //comprovem si es pot moure cap a la diagonal dreta (j+1)
            if (m_tauler[i + 1][j + 1].getColor() != m_tauler[i][j].getColor()) //comporvem si tenim una pe�a del color contrari al costat
            {
                if (m_tauler[i + 2][j + 2].getTipus() == TIPUS_EMPTY) //mirem si la casella seguent a la enemiga, esta buida
                {
                    posicionsPossibles[nPosicions] = m_tauler[i][j].getPosicio();
                    nPosicions++;
                    j = j + 2; // se li suma 2 a j, ja que ens hem mogut cap a la dreta
                    i = i +2*k;/* i = i + 2 * k, ja que la i sempre augmentara en funcio del valor de k, ja que a cada iteracio del bucle, 
                                  es mira 2 caselles endevant(2 * k)*/
                }                   
            }

            //comporvem si es pot moure cap a la diagonal esquerra (j-1)
            if (m_tauler[i + 1][j - 1].getColor() != m_tauler[i][j].getColor()) //comporvem si tenim una pe�a del color contrari al costat
            {
                if ( m_tauler[i - 2][j - 2].getTipus() == TIPUS_EMPTY) //mirem si la casella seguent a la enemiga, esta buida
                {
                    posicionsPossibles[nPosicions] = m_tauler[i + 2][j - 2].getPosicio();
                    nPosicions++;
                    j = j - 2; // es resta 2 a j, ja que ens hem mogut cap a la esquerra
                    i = i +2*k;

                }
            }
        k++;
        } while (k <= nPosicions && i < N_FILES - 2 && j < N_COLUMNES - 2 && j > 2);
        /*
        * sortira del bucle un cop volguem mourens fora del taulell o haguem k sigui mes gran que nPosicions, el que vol dir que no hi ha cap posicio
        * a la que ens poguem moure, per tant no s incrementa nPosicions
        */
    }

    //bfs per les fitxes negres
    if (direccio == -1)
    {
        do
        {
            if (m_tauler[i - 1][j + 1].getColor() != m_tauler[i][j].getColor())
            {
                if (m_tauler[i + 2][j + 2].getTipus() == TIPUS_EMPTY)
                {
                    posicionsPossibles[nPosicions] = m_tauler[i][j].getPosicio();
                    nPosicions++;
                    j = j + 2;
                    i = i +2*k;
                }
            }
            if (m_tauler[i - 1][j - 1].getColor() != m_tauler[i][j].getColor()) 
            {
                if ( m_tauler[i - 2][j - 2].getTipus() == TIPUS_EMPTY)
                {
                    posicionsPossibles[nPosicions] = m_tauler[i + 2][j - 2].getPosicio();
                    nPosicions++;
                    j = j - 2;
                    i = i +2*k;
                }
            }
        k++;
        } while (k <= nPosicions && i > 2 && j < N_COLUMNES - 2 && j > 2);
    }
}
