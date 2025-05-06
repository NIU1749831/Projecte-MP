#include <sstream>
#include "tauler.hpp"

using namespace std;

void Tauler::inicialitza(const string& nomFitxer)
{
    
    //Inicializo primero todas las casillas como empty 
    for (int i = 0; i < N_FILES; i++)
    {
        for (int j = 0; j < N_COLUMNES; j++)
        {
            string pos;
            Posicio p;
            pos = p.PosicioAString(j, i);
            m_tauler[i][j] = Fitxa(TIPUS_EMPTY, Posicio(pos));
        }

    }
    //Abro el fichero que nos han pasado como parametros
    ifstream ficher(nomFitxer);
    if (ficher.is_open())
    {
       

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
                m_tauler[Y][X].setTipus(TIPUS_NORMAL);
                m_tauler[Y][X].setColor(COLOR_BLANC);
                break;
            case 'X':
                m_tauler[Y][X].setTipus(TIPUS_NORMAL);
                m_tauler[Y][X].setColor(COLOR_NEGRE);
                break;
            case 'D':
                m_tauler[Y][X].setTipus(TIPUS_DAMA);
                m_tauler[Y][X].setColor(COLOR_BLANC);
                break;
            case 'R':
                m_tauler[Y][X].setTipus(TIPUS_DAMA);
                m_tauler[Y][X].setColor(COLOR_NEGRE);
                break;
            default:
                break;
            }
        }
        ficher.close();
    }
}

string Tauler::toString() const
{
    stringstream tauler;
    for (int i = FILES; i > 0; i--)
    {
        tauler << i << ": ";
        for (int j = 0; j <= N_COLUMNES; j++)
        {
            switch (m_tauler[i - 1][j].getTipus())
            {
            case TIPUS_EMPTY:
                tauler << "_ ";
                break;
            case TIPUS_NORMAL:
                if (m_tauler[i - 1][j].getColor() == COLOR_BLANC)
                    tauler << "O ";
                else
                    tauler << "X ";
                break;
            case TIPUS_DAMA:
                if (m_tauler[i - 1][j].getColor() == COLOR_BLANC)
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
    tauler << "   a b c d e f g h" << endl;
    return tauler.str();
}

bool Tauler::esPosicioValida(int i, int j) const 
{
    return (i >= 0 && i < FILES && j >= 0 && j < COLUMNES);
}

bool Tauler::esMovimentDeCaptura(const Posicio& origen, const Posicio& desti) const
{
    int iOrigen, jOrigen, iDesti, jDesti;

    origen.stringToInts(origen.getPosicio(), iOrigen, jOrigen);
    desti.stringToInts(desti.getPosicio(), iDesti, jDesti);

    //un moviment de captura simple, es dona cuan la peça es mou 2 posicions en la x i y, per aixo fem la resta i valor absolut
    return (abs(iDesti - iOrigen) == 2 && abs(jDesti - jOrigen) == 2);
}

void Tauler::verificarCaptura(int i, int j, int direccio, int deltaJ, vector<Posicio>& posicionsValides) 
{
    
    //posicio de la fitxa enemiga
    int iInter = i + direccio;
    int jInter = j + deltaJ;

    //posicio post captura
    int iDest = i + 2 * direccio;
    int jDest = j + 2 * deltaJ;
    

    Fitxa fitxaInter = m_tauler[iInter][jInter]; //Possible enemiga


    if (esPosicioValida(iInter, jInter) && esPosicioValida(iDest, jDest)) 
    {
        if (fitxaInter.getTipus() != TIPUS_EMPTY && fitxaInter.getColor() != m_tauler[i][j].getColor() && m_tauler[iDest][jDest].getTipus() == TIPUS_EMPTY) 
        {
            posicionsValides.push_back(m_tauler[iDest][jDest].getPosicio()); //pone al final del array de movimientos la posicion
        }
    }
}

void Tauler::verificarMovimentsDama(int i, int j, vector<Posicio>& posicionsValides) 
{
    int direccions[4][2] = { {1,1}, {1,-1}, {-1,1}, {-1,-1} }; //array bidimensional con todas las direcciones possibles
    
    for (int k = 0; k < 4; k++) //bucle para comrpovar movimientos dama en todas las direcciones
    {
        int di = direccions[k][0];
        int dj = direccions[k][1];

        //primer movimiento en esa direccion
        int iActual = i + di; 
        int jActual = j + dj;

        while (esPosicioValida(iActual, jActual)) 
        {
            if (m_tauler[iActual][jActual].getTipus() == TIPUS_EMPTY) //if para comprovar movimientos simples de dama
            {
                posicionsValides.push_back(m_tauler[iActual][jActual].getPosicio()); //pone en el array de direcciones el movimiento valido

                iActual += di;
                jActual += dj;
            }
            else if (m_tauler[iActual][jActual].getColor() != m_tauler[i][j].getColor()) //comprueva movimientos de captura
            {
                int iSalto = iActual + di;
                int jSalto = jActual + dj;

                if (esPosicioValida(iSalto, jSalto) && m_tauler[iSalto][jSalto].getTipus() == TIPUS_EMPTY) 
                {
                    posicionsValides.push_back(m_tauler[iSalto][jSalto].getPosicio()); //guarda la posicion como valida
                    break; //si troba un moviment de captura, comprova les seguents direccions, no te en compte captures multiples
                }
                else 
                {
                    break; //ha trobat una ficha enemiga que no pot captura, no es podra seguir movent en aquella direccio
                }
            }
            else 
            {
                break;
            }
        }
    }
}

void Tauler::obtenirPosicionsValides(int i, int j, vector<Posicio>& posicionsValides) 
{
    TipusFitxa tipus = m_tauler[i][j].getTipus();
    ColorFitxa color = m_tauler[i][j].getColor();

    int direccio = (color == COLOR_BLANC) ? 1 : -1;

    if (tipus == TIPUS_NORMAL) 
    {
        if (esPosicioValida(i + direccio, j + 1) && m_tauler[i + direccio][j + 1].getTipus() == TIPUS_EMPTY) 
        {
            posicionsValides.push_back(m_tauler[i + direccio][j + 1].getPosicio());
        }
        if (esPosicioValida(i + direccio, j - 1) && m_tauler[i + direccio][j - 1].getTipus() == TIPUS_EMPTY) 
        {
            posicionsValides.push_back(m_tauler[i + direccio][j - 1].getPosicio());
        }

        verificarCaptura(i, j, direccio, 1, posicionsValides);
        verificarCaptura(i, j, direccio, -1, posicionsValides);
    }
    else if (tipus == TIPUS_DAMA) 
    {
        verificarMovimentsDama(i, j, posicionsValides);
    }
}

void Tauler::bfs(int i, int j, int direccio, Posicio posicionsPossibles[], int& nPosicions) 
{
    vector<Posicio> movimientosValidos;
    
    queue<Nodo> cola;
    Nodo inicial;
    Nodo actual;

    int iActual, jActual;

    inicial.pos = m_tauler[i][j].getPosicio();
    inicial.camino.push_back(inicial.pos);
    cola.push(inicial);

    while (!cola.empty()) {
        actual = cola.front();
        cola.pop();
       
        actual.pos.stringToInts(actual.pos.getPosicio(), iActual, jActual);
       
        obtenirPosicionsValides(iActual, jActual, movimientosValidos);

        if (movimientosValidos.empty()) 
        {
            if (actual.camino.size() > 1) 
            {
                for (int k = 1; k < actual.camino.size() && nPosicions < 100; k++) 
                {
                    posicionsPossibles[nPosicions] = actual.camino[k];
                    nPosicions++;
                }
            }
        }
        else {
            for (int k = 0; k < movimientosValidos.size(); k++) 
            {
                Nodo siguiente;
                siguiente.pos = movimientosValidos[k];
                siguiente.camino = actual.camino;
                siguiente.camino.push_back(siguiente.pos);
                cola.push(siguiente);
            }
        }
    }
}

void Tauler::actualitzaMovimentsValids() 
{
    for (int i = 0; i < FILES; i++)
    {
        for (int j = 0; j < COLUMNES; j++) 
        {
            m_tauler[i][j] = Fitxa(m_tauler[i][j].getTipus(), m_tauler[i][j].getPosicio());
            m_tauler[i][j].setColor(m_tauler[i][j].getColor());

            if (m_tauler[i][j].getTipus() == TIPUS_NORMAL || m_tauler[i][j].getTipus() == TIPUS_DAMA) 
            {
                Posicio posicionsPossibles[100];
                int nPosicions = 0;
                int direccio = (m_tauler[i][j].getColor() == COLOR_BLANC) ? -1 : 1;

                bfs(i, j, direccio, posicionsPossibles, nPosicions);

                for (int k = 0; k < nPosicions; k++) 
                {
                    Moviment mov(posicionsPossibles[k], (esMovimentDeCaptura(m_tauler[i][j].getPosicio(), posicionsPossibles[k]) ? MATAR : MOVIMENT));
                    m_tauler[i][j].afegirMovimentValid(mov);
                }
            }
        }
    }
}

void Tauler::asigna(int i, int j) {
    Posicio p;
    p.setPosicio(p.PosicioAString(i, j));
    m_tauler[i][j].afegirMovimentValid(Moviment(p));
}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti) {
    int iOrigen, jOrigen;
    origen.stringToInts(origen.getPosicio(), iOrigen, jOrigen);

    if (!esPosicioValida(iOrigen, jOrigen) || m_tauler[iOrigen][jOrigen].getTipus() == TIPUS_EMPTY) {
        return false;
    }

    bool movimentValid = false;
    int numMoviments = m_tauler[iOrigen][jOrigen].getNumMovimentsValids();
    Moviment mov;

    for (int i = 0; i < numMoviments; i++) {
        mov = m_tauler[iOrigen][jOrigen].getMovimentValid(i);
        if (mov.getDesti() == desti) {
            movimentValid = true;
            break;
        }
    }

    if (!movimentValid) {
        return false;
    }

    int iDesti, jDesti;
    desti.stringToInts(desti.getPosicio(), iDesti, jDesti);

    m_tauler[iDesti][jDesti] = m_tauler[iOrigen][jOrigen];
    m_tauler[iDesti][jDesti].setPosicio(desti);
    m_tauler[iOrigen][jOrigen] = Fitxa(TIPUS_EMPTY, origen);

    if (esMovimentDeCaptura(origen, desti)) {
        Posicio p;
        int iCaptura = (iOrigen + iDesti) / 2;
        int jCaptura = (jOrigen + jDesti) / 2;

        p.PosicioAString(jCaptura, iCaptura);
        m_tauler[iCaptura][jCaptura] = Fitxa(TIPUS_EMPTY, p);
    }

    if ((m_tauler[iDesti][jDesti].getColor() == COLOR_BLANC && iDesti == 0) || (m_tauler[iDesti][jDesti].getColor() == COLOR_NEGRE && iDesti == FILES - 1)) 
    {
        m_tauler[iDesti][jDesti].convertirADama();
    }

    actualitzaMovimentsValids();
    return true;
}

void Tauler::getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]) 
{
    nPosicions = 0;
    int i, j;
    origen.stringToInts(origen.getPosicio(), i, j);

    if (!esPosicioValida(i, j) || m_tauler[i][j].getTipus() == TIPUS_EMPTY) {
        return;
    }

    int direccio = (m_tauler[i][j].getColor() == COLOR_BLANC) ? 1 : -1;

    bfs(i, j, direccio, posicionsPossibles, nPosicions);

    for (int k = 0; k < nPosicions; k++) 
    {
        for (int l = k + 1; l < nPosicions; l++) 
        {
            if (posicionsPossibles[k] == posicionsPossibles[l]) 
            {
                for (int m = l; m < nPosicions - 1; m++) {
                    posicionsPossibles[m] = posicionsPossibles[m + 1];
                }
                nPosicions--;
            }
        }
    }
}