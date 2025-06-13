#include <sstream>
#include<iostream>
#include <set>
#include "Tauler.hpp"
using namespace std;

void Tauler::inicialitza(const string& nomFitxer)
{
    for (int i = 0; i < N_FILES + 1; i++)
    {
        for (int j = 0; j < N_COLUMNES + 1; j++)
        {
            string pos = Posicio().PosicioAString(j, i);
            m_tauler[i][j] = Fitxa(TIPUS_EMPTY, Posicio(pos));
        }
    }

    ifstream ficher(nomFitxer);
    if (!ficher.is_open())
    {
        cout << "Error obrint el fitxer: " << nomFitxer << endl;
        return;
    }

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
            m_tauler[7 - Y][X].setTipus(TIPUS_NORMAL);
            m_tauler[7 - Y][X].setColor(COLOR_BLANC);
            break;
        case 'X':
            m_tauler[7 - Y][X].setTipus(TIPUS_NORMAL);
            m_tauler[7 - Y][X].setColor(COLOR_NEGRE);
            break;
        case 'D':
            m_tauler[7 - Y][X].setTipus(TIPUS_DAMA);
            m_tauler[7 - Y][X].setColor(COLOR_BLANC);
            break;
        case 'R':
            m_tauler[7 - Y][X].setTipus(TIPUS_DAMA);
            m_tauler[7 - Y][X].setColor(COLOR_NEGRE);
            break;
        default:
            break;
        }
    }
    ficher.close();
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

    TipusFitxa tipus = m_tauler[iOrigen][jOrigen].getTipus();

    if (tipus == TIPUS_NORMAL) 
    {
        return (abs(iDesti - iOrigen) == 2 && abs(jDesti - jOrigen) == 2);
    }
    else if (tipus == TIPUS_DAMA) {
        if (abs(iDesti - iOrigen) == abs(jDesti - jOrigen)) {
            int di = (iDesti > iOrigen) ? 1 : -1;
            int dj = (jDesti > jOrigen) ? 1 : -1;
            int count = 0;
            for (int i = iOrigen + di, j = jOrigen + dj; i != iDesti; i += di, j += dj) {
                if (m_tauler[i][j].getTipus() != TIPUS_EMPTY) {
                    if (m_tauler[i][j].getColor() != m_tauler[iOrigen][jOrigen].getColor())
                        count++;
                    else
                        return false;
                }
            }
            return (count == 1);
        }
    }
    return false;
}

void Tauler::verificarCaptura(int i, int j, int direccio, int deltaJ, stack<Moviment>& MatarPossible)
{
    int iInter = i + direccio;
    int jInter = j + deltaJ;
    int iDest = i + 2 * direccio;
    int jDest = j + 2 * deltaJ;

    if (esPosicioValida(iInter, jInter) && esPosicioValida(iDest, jDest))
    {
        Fitxa fitxaInter = m_tauler[iInter][jInter];

        if (fitxaInter.getTipus() != TIPUS_EMPTY && fitxaInter.getColor() != m_tauler[i][j].getColor() && m_tauler[iDest][jDest].getTipus() == TIPUS_EMPTY)
        {
            Posicio desti, origen;
            
            origen.setPosicio(origen.PosicioAString(j, i));
            desti.setPosicio(desti.PosicioAString(jDest, iDest));

            Moviment m(origen, desti, MATAR);
            m.afegeixCaptura(fitxaInter.getPosicio());
            MatarPossible.push(m);
        }
    }
}

void Tauler::verificarMovimentsDama(int i, int j, stack<Moviment>& MatarPossible, stack<Moviment>& SimplesPossibles)
{
    int direccions[4][2] = { {1,1}, {1,-1}, {-1,1}, {-1,-1} };
    ColorFitxa color = m_tauler[i][j].getColor();

    for (int k = 0; k < 4; ++k) {
        int di = direccions[k][0];
        int dj = direccions[k][1];
        int iActual = i + di;
        int jActual = j + dj;
        bool enemicTrobat = false;
        int iCaptura = -1, jCaptura = -1;

        while (esPosicioValida(iActual, jActual)) {
            Fitxa actual = m_tauler[iActual][jActual];

            if (actual.getTipus() == TIPUS_EMPTY) {
                Posicio origen, desti;
                origen.setPosicio(origen.PosicioAString(j, i));
                desti.setPosicio(desti.PosicioAString(jActual, iActual));

                if (!enemicTrobat) {
                    // moviment simple
                    SimplesPossibles.push(Moviment(origen, desti, MOVIMENT));
                }
                else {
                    // moviment de captura (només una per direcció)
                    Moviment m(origen, desti, MATAR);
                    Posicio capturada;
                    capturada.setPosicio(capturada.PosicioAString(jCaptura, iCaptura));
                    m.afegeixCaptura(capturada);
                    MatarPossible.push(m);
                    break;
                }
                iActual += di;
                jActual += dj;
            }
            else if (actual.getColor() != color && !enemicTrobat) {
                // primer enemic trobat
                enemicTrobat = true;
                iCaptura = iActual;
                jCaptura = jActual;
                iActual += di;
                jActual += dj;
            }
            else {
                // segon enemic o una peça pròpia: no és vàlid continuar
                break;
            }
        }
    }
}


bool Tauler::obtenirPosicionsValides(int i, int j, stack<Moviment>& SimplesPossibles, stack<Moviment>& MatarPossible)
{
    TipusFitxa tipus = m_tauler[i][j].getTipus();
    ColorFitxa color = m_tauler[i][j].getColor();
    
    int direccio = (color == COLOR_BLANC) ? -1 : 1;

    if (tipus == TIPUS_NORMAL)
    {
        //mira moviments simples
        if (esPosicioValida(i + direccio, j + 1) && m_tauler[i + direccio][j + 1].getTipus() == TIPUS_EMPTY)
        {
            Posicio desti, origen;

            origen.setPosicio(origen.PosicioAString(j, i));
            desti.setPosicio(desti.PosicioAString(j + 1, i + direccio));

            Moviment movSimple1(origen, desti, MOVIMENT);
            SimplesPossibles.push(movSimple1);
        }
            
        if (esPosicioValida(i + direccio, j - 1) && m_tauler[i + direccio][j - 1].getTipus() == TIPUS_EMPTY)
        {
            Posicio desti, origen;

            origen.setPosicio(origen.PosicioAString(j, i));
            desti.setPosicio(desti.PosicioAString(j - 1,i + direccio));

            Moviment movSimple2(origen, desti, MOVIMENT);
            SimplesPossibles.push(movSimple2);
        }
            
        //mira camptures
        verificarCaptura(i, j, direccio, 1, MatarPossible);
        verificarCaptura(i, j, direccio, -1, MatarPossible);

        if (!MatarPossible.empty())
            return true;
    }
    else if (tipus == TIPUS_DAMA)
    {
        verificarMovimentsDama(i, j, MatarPossible, SimplesPossibles);
    }
    return false;
}

void Tauler::dfsRecursiu(int i, int j, Moviment movActual, vector<Moviment>& resultats, bool visitat[FILES][COLUMNES]) {
    bool haTrobat = false;
    Posicio p;
    int x, y;
    p.stringToInts(movActual.getOrigen().getPosicio(), y, x);


    TipusFitxa tipus = m_tauler[y][x].getTipus();
    ColorFitxa color = m_tauler[y][x].getColor();
    // Direcciones válidas dependiendo del tipo
    vector<pair<int, int>> dirs;
    if (tipus == TIPUS_DAMA) {
        dirs = { {1,1}, {1,-1}, {-1,1}, {-1,-1} }; // Todas las direcciones
    }
    else 
    {
        int direccio = (color == COLOR_BLANC) ? -1 : 1;
        dirs = { {direccio, 1}, {direccio, -1} }; // Solo adelante
    }

    for (auto d : dirs) {
        int iMid = i + d.first;
        int jMid = j + d.second;
        int iDest = i + 2 * d.first;
        int jDest = j + 2 * d.second;

        if (!esPosicioValida(iDest, jDest) || !esPosicioValida(iMid, jMid))
            continue;

        Fitxa inter = m_tauler[iMid][jMid];
        Fitxa desti = m_tauler[iDest][jDest];

        if (inter.getTipus() != TIPUS_EMPTY && inter.getColor() != color &&
            desti.getTipus() == TIPUS_EMPTY && !visitat[iMid][jMid]) 
        {

            haTrobat = true;
            visitat[iMid][jMid] = true;

            Posicio novaPos;
            novaPos.setPosicio(novaPos.PosicioAString(jDest, iDest));

            Moviment nouMov = movActual;
            nouMov.setDesti(novaPos);
            nouMov.afegeixPosicioAlCamino(novaPos);

            Posicio cap;
            cap.setPosicio(cap.PosicioAString(jMid, iMid));
            nouMov.afegeixCaptura(cap);
            nouMov.setTipusMoviment(MATAR_ENCADENAT);

            cout << cap.getPosicio() << endl;

            dfsRecursiu(iDest, jDest, nouMov, resultats, visitat);

            visitat[iMid][jMid] = false;
        }
    }

    if (!haTrobat && !movActual.getCaptures().empty()) 
    {
        if (movActual.getCami().size() == 1)
            movActual.setTipusMoviment(MATAR);
        else
            movActual.setTipusMoviment(MATAR_ENCADENAT_FINAL);
        resultats.push_back(movActual);
    }
}

void Tauler::dfs(int i, int j, int direccio, vector<Moviment>& movimentsValids) {
    stack<Moviment> capturesInicials, simples;

    obtenirPosicionsValides(i, j, simples, capturesInicials);

    bool hiHaEncadenats = false;

    while (!capturesInicials.empty()) {
        Moviment mov = capturesInicials.top();
        capturesInicials.pop();

        int iNou, jNou;
        mov.getDesti().stringToInts(mov.getDesti().getPosicio(), iNou, jNou);

        bool visitat[FILES][COLUMNES] = { false };
        for (const Posicio& p : mov.getCaptures()) {
            int x, y;
            p.stringToInts(p.getPosicio(), x, y);
            visitat[x][y] = true;
        }

        vector<Moviment> encadenats;
        dfsRecursiu(iNou, jNou, mov, encadenats, visitat);
        if (!encadenats.empty()) {
            hiHaEncadenats = true;
            movimentsValids.insert(movimentsValids.end(), encadenats.begin(), encadenats.end());
        }
        else {
            movimentsValids.push_back(mov);
        }
    }

   while (!simples.empty()) 
   {
            movimentsValids.push_back(simples.top());
            simples.pop();
        
   }
}
    

void Tauler::actualitzaMovimentsValids()
{
    bool hiHaCaptura = false;

    for (int i = 0; i < FILES; i++)
    {
        for (int j = 0; j < COLUMNES; j++)
        {
            TipusFitxa tipus = m_tauler[i][j].getTipus();
            ColorFitxa color = m_tauler[i][j].getColor();
            Posicio pos = m_tauler[i][j].getPosicio();

            m_tauler[i][j] = Fitxa(tipus, pos);
            m_tauler[i][j].setColor(color);

            if (tipus != TIPUS_EMPTY) {
                vector<Moviment> possibles;
                int n = 0;
                int direccio = (color == COLOR_BLANC) ? -1 : 1;

                dfs(i, j, direccio, possibles);
                for (int k = 0; k < possibles.size(); k++)
                    m_tauler[i][j].afegirMovimentValid(possibles[k]);
            }
        }
    
    }

}

bool Tauler::mouFitxa(const Posicio& origen, const Posicio& desti)
{
    actualitzaMovimentsValids();

    int iO, jO;
    origen.stringToInts(origen.getPosicio(), iO, jO);

    if (!esPosicioValida(iO, jO) || m_tauler[iO][jO].getTipus() == TIPUS_EMPTY)
        return false;

    Fitxa& fitxa = m_tauler[iO][jO];
    Moviment movimentSeleccionat;
    bool trobat = false;

    for (int i = 0; i < fitxa.getNumMovimentsValids(); i++) {
        Moviment m = fitxa.getMovimentValid(i);
        const vector<Posicio>& cami = m.getCami();

        for (int j = 0; j < cami.size(); ++j) 
        {
            if (cami[j] == desti) 
            {
                movimentSeleccionat = m;
                movimentSeleccionat.setDesti(m.getCami()[j]);

                // recortar camino hasta la posición seleccionada
                vector<Posicio> nouCami;
                vector<Posicio> capturesOriginals = m.getCaptures();
                vector<Posicio> novesCaptures;
                for (int k = 0; k <= j; ++k)
                {
                    nouCami.push_back(cami[k]);
                    if(!capturesOriginals.empty())
                        novesCaptures.push_back(capturesOriginals[k]);
                }

                movimentSeleccionat.setCami(nouCami);
                movimentSeleccionat.setCaptures(novesCaptures);

                trobat = true;
                break;
            }
        }

        if (trobat) break;
    }

    if (!trobat) return false;

    // Eliminar captures
    const vector<Posicio>& captures = movimentSeleccionat.getCaptures();

    for (int i = 0; i < captures.size(); ++i) 
    {
        int iC, jC;
        captures[i].stringToInts(captures[i].getPosicio(), iC, jC);
        m_tauler[iC][jC] = Fitxa(TIPUS_EMPTY, captures[i]);
    }

    // Moure fitxa
    int iD, jD;
    movimentSeleccionat.getDesti().stringToInts(movimentSeleccionat.getDesti().getPosicio(), iD, jD);

    m_tauler[iD][jD] = fitxa;
    m_tauler[iD][jD].setPosicio(desti);
    m_tauler[iO][jO] = Fitxa(TIPUS_EMPTY, origen);

    // Convertir en dama si ha arribat al final
    if (m_tauler[iD][jD].getTipus() == TIPUS_NORMAL)
    {
        if ((m_tauler[iD][jD].getColor() == COLOR_BLANC && iD == 0) ||
            (m_tauler[iD][jD].getColor() == COLOR_NEGRE && iD == 7))
        {
            m_tauler[iD][jD].convertirADama();
        }
    }

    return true;
}


void Tauler::getPosicionsPossibles(const Posicio& origen, vector<Moviment>& posicionsPossibles)
{
    int i, j;
    origen.stringToInts(origen.getPosicio(), i, j);
    if (!esPosicioValida(i, j) || m_tauler[i][j].getTipus() == TIPUS_EMPTY) 
        return;
    int direccio = (m_tauler[i][j].getColor() == COLOR_BLANC) ? -1 : 1;
    dfs(i, j, direccio, posicionsPossibles);
}

bool Tauler::comprovaFinalPartida(int jugador)
{
    ColorFitxa color = (jugador == 0 || jugador == -1) ? COLOR_BLANC : COLOR_NEGRE;

    for (int i = 0; i < FILES; ++i)
    {
        for (int j = 0; j < COLUMNES; ++j)
        {
            if (m_tauler[i][j].getTipus() != TIPUS_EMPTY && m_tauler[i][j].getColor() != color)
            {
                return false;
            }
        }
    }

    return true;
}


void Tauler::visualitza() const
{
    // Dibuixa el tauler (fons i gràfic)
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    for (int i = 0; i < FILES; i++)
    {
        for (int j = 0; j < COLUMNES; ++j)
        {
            m_tauler[i][j].visualitza(); // Cada fitxa dibuixa si no és buida
        }
    }
}

void Tauler::bufarFitxa(const Posicio& p)
{
    int i, j;
    p.stringToInts(p.getPosicio(), i, j);

    m_tauler[i][j].setTipus(TIPUS_EMPTY);
    m_tauler[i][j].setColor(COLOR_BLANC);
}
