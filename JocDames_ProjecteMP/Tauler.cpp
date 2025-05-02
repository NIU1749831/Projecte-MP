#include <fstream>
#include<sstream>
#include "tauler.hpp"

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
                string pos;
                Posicio p;
                pos=p.PosicioAString(j, i);
                m_tauler [i][j] = Fitxa(TIPUS_EMPTY, Posicio(pos));
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
        ficher.close();
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
                    
                }
                else
                {
                    
                }
            } 
            else if (m_tauler[i][j].getTipus() == TIPUS_DAMA) 
            {
                
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

/*void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[])
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
*/

void Tauler::getPosicionsPossibles(const Posicio & origen, int& nPosicions, Posicio posicionsPossibles[]) 
{
        nPosicions = 0;
        int i, j;
        origen.stringToInts(origen.getPosicio(), i, j); // Descomentar y corregir

        TipusFitxa tipus = m_tauler[i][j].getTipus();
        ColorFitxa color = m_tauler[i][j].getColor();

        if (tipus == TIPUS_NORMAL) {
            //falta poner por cada color
            int direccio = (color == COLOR_BLANC) ? -1 : 1; //ta raro
            // Comprobar movimientos normales y capturas
            // Implementar lógica correcta para movimientos y capturas
        }
        else if (tipus == TIPUS_DAMA) {
            // Implementar lógica para damas
        }
}


void Tauler::bfs(int i, int j, int direccio, Posicio posicionsPossibles[], int& nPosicions)
{
    int k = 0;
    int x=j, y=i;
    // bsf per les fitxes blanques
    if (direccio == 1)
    {
        do
        {
            //comprovem si es pot moure cap a la diagonal dreta (j+1)
            if (m_tauler[i + 1][j + 1].getColor() != m_tauler[i][j].getColor()) //comporvem si tenim una peça del color contrari al costat
            {
                if (m_tauler[i + 2][j + 2].getTipus() == TIPUS_EMPTY) //mirem si la casella seguent a la enemiga, esta buida
                {
                    
                    j +=2;  //es suma 2, ja que ens movem cap a la dreta
                 
                  
                    posicionsPossibles[nPosicions] = m_tauler[i][j].getPosicio();
                    nPosicions++;

                }                   
            }

            //comporvem si es pot moure cap a la diagonal esquerra (j-1)
            if (m_tauler[i + 1][j - 1].getColor() != m_tauler[i][j].getColor()) //comporvem si tenim una peça del color contrari al costat
            {
                if ( m_tauler[i + 2][j - 2].getTipus() == TIPUS_EMPTY) //mirem si la casella seguent a la enemiga, esta buida
                {
                    j -= 2; //es resta 2, ja que ens movem cap a la esquerra
                    
                    posicionsPossibles[nPosicions] = m_tauler[i][j].getPosicio();
                    nPosicions++;
                    

                }
            }
        i+=2;
        k++;

        } while (k <= nPosicions && i <= N_FILES - 2 && j <= N_COLUMNES - 2 && j >= 2);
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
                if (m_tauler[i - 2][j + 2].getTipus() == TIPUS_EMPTY)
                {
                    posicionsPossibles[nPosicions] = m_tauler[i][j].getPosicio();
                    nPosicions++;
                    j = j + 2;
                    i = i - 2;
                }
            }
            if (m_tauler[i - 1][j - 1].getColor() != m_tauler[i][j].getColor()) 
            {
                if ( m_tauler[i - 2][j - 2].getTipus() == TIPUS_EMPTY)
                {
                    posicionsPossibles[nPosicions] = m_tauler[i + 2][j - 2].getPosicio();
                    nPosicions++;
                    j = j - 2;
                    i = i - 2;
                }
            }
        k++;
        } while (k <= nPosicions && i > 2 && j < N_COLUMNES - 2 && j > 2);
    }
}

string Tauler::toString() const
{
     //usamos sstream para poder operar con los string como si fueran outputs stream
    // stringstream, lo que nos hace, es crear una variable de tipos stringstream, la cual nos permite operar con strings con el oeprador << y endl, facilitando la implementacion
    stringstream tauler;

    for (int i = 0; i < N_FILES; i++) //for que nos va cambiando de linea al acabar una fila
    {
        tauler << 8 - i << ": ";
        for (int j = 0; j < N_COLUMNES; j++) //este for realiza la tarea de convertir cada fila del tablero a un caracter para ponder en el stringstream
        {
            switch (m_tauler[i][j].getTipus())
            {
            case TIPUS_EMPTY:
                tauler << "_ ";
                break;
            case TIPUS_NORMAL:
                if (m_tauler[i][j].getColor() == COLOR_BLANC)
                    tauler << "O ";
                else
                    tauler << "X ";
                break;
            case TIPUS_DAMA:
                if(m_tauler[i][j].getColor() == COLOR_BLANC)
                    tauler << "D ";
                else
                    tauler << "R ";
                break;
            default:
                break;
            }


        }
        tauler << endl;
    }
    tauler << "   A B C D E F G H" << endl;
    return tauler.str(); //la funcion .str() convierte la variable tauler que es stringstream a un string
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
    Posicio posicionsPossibles[100];
    int nPosicions;
    /*
    * Trobar la fitxa, si no es troba --> return false
    * Buscar si posicio desti esta dintre de posicionsPossibles
    * 
    */

    return false;

}