//
//  CurrentGame.cpp
//  LearnChess
//
//  Created by Enric Vergara on 21/2/22.
//

#include "joc.hpp"
#include <iostream>
#include <fstream>
#include<sstream>
#include<thread>
#include "GraphicManager.h"

void Joc::inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments)
{
    m_tauler.inicialitza(nomFitxerTauler);
    
  
    m_modeJoc = mode;
    m_jugadorActual = 0; // Jugador 0 comença
    m_finalPartida = false;
    m_guanyador = -1; // No hi ha guanyador al principi
    m_pecaSeleccionada = false; // No hi ha cap peça seleccionada al principi
    PecaSeleccionada = Fitxa(); // Inicialitzem la peça seleccionada
    m_movimentsPecaSeleccionada.clear(); // Netejar els moviments de la peça seleccionada
    m_mouseAnterior = false;

    // Dibuixar el fons del joc
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);


    
    // Dibuixar el tauler inicial amb les fitxes en les posicions inicials
    for (int fila = 0; fila < FILES; ++fila)
    {
        for (int columna = 0; columna < COLUMNES; ++columna)
        {
            Fitxa fitxa = m_tauler.getFitxa(fila, columna);
            if (fitxa.getTipus() != TIPUS_EMPTY)
            {
                int posXFitxa = CASELLA_INICIAL_X + (columna * AMPLADA_CASELLA);
                int posYFitxa = CASELLA_INICIAL_Y + (fila * ALCADA_CASELLA);

                if (fitxa.getColor() == COLOR_BLANC)
                {
                    if (fitxa.getTipus() == TIPUS_DAMA)
                    {
                        GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_BLANCA, posXFitxa, posYFitxa);
                    }
                    else
                    {
                        GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_BLANCA, posXFitxa, posYFitxa);
                    }
                }
                else if (fitxa.getColor() == COLOR_NEGRE)
                {
                    if (fitxa.getTipus() == TIPUS_DAMA)
                    {
                        GraphicManager::getInstance()->drawSprite(GRAFIC_DAMA_NEGRA, posXFitxa, posYFitxa);

                    }
                    else
                    {
                        GraphicManager::getInstance()->drawSprite(GRAFIC_FITXA_NEGRA, posXFitxa, posYFitxa);
                    }
                }
            }
        }
    }
    // Dibuixar el text de la posici� del ratol��
 
    ifstream fitxer(nomFitxerMoviments);

    if (m_modeJoc == MODE_JOC_REPLAY)
    {
        string origen, desti;
        while (fitxer >> origen >> desti)
        {
            m_cua.push(Moviment(Posicio(origen), Posicio(desti)));
        }
    }
}

bool Joc::actualitza(int mousePosX, int mousePosY, bool mouseStatus)
{
    //obres el fitrxer


    // Dibuixar fons i tauler
    GraphicManager::getInstance()->drawSprite(GRAFIC_FONS, 0, 0);
    GraphicManager::getInstance()->drawSprite(GRAFIC_TAULER, POS_X_TAULER, POS_Y_TAULER);

    // Mostrar torn actual i mode de joc
    stringstream ss;
    string guanyador;
    string jugador;
    if (m_jugadorActual == 0)
    {
        guanyador = "BLANQUES";
        jugador = "blanques";
    }
    else
    {
        guanyador = "NEGRES";
        jugador = "negres";
    }
    ss << "Torn: Jugador " << jugador;
    GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 20, 790, 0.5, ss.str());


    if (m_finalPartida) {
        stringstream msg;
        msg << "FI DE LA PARTIDA! GUANYADOR " << guanyador;
        GraphicManager::getInstance()->drawFont(FONT_RED_30, 20, 750, 1.0, msg.str());
        return true;
    }

    // --- M O D E   N O R M A L ---
    if (m_modeJoc == MODE_JOC_NORMAL && mouseStatus)
    {


        if (mouseStatus && mousePosX >= POS_X_TAULER + CASELLA_INICIAL_X && mousePosY >= POS_Y_TAULER + CASELLA_INICIAL_Y &&
            mousePosX < POS_X_TAULER + CASELLA_INICIAL_X + AMPLADA_CASELLA * COLUMNES && mousePosY < POS_Y_TAULER + CASELLA_INICIAL_Y + ALCADA_CASELLA * FILES)
        {
            int col = ((mousePosX - CASELLA_INICIAL_X) / AMPLADA_CASELLA) - 1;
            int fila = (mousePosY - CASELLA_INICIAL_Y) / ALCADA_CASELLA;
            if (mouseStatus)
            {
                string title = "Mouse Cursor";
                string msg = "PosX: " + to_string(mousePosX) + ", PosY: " + to_string(mousePosY);
                GraphicManager::getInstance()->drawFont(FONT_GREEN_30, 20, 700, 0.8, title);
                GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 20, 730, 0.8, msg);
                stringstream click;
                click << "Posicio: " << char(col + 97) << 8 - fila << endl;
                GraphicManager::getInstance()->drawFont(FONT_WHITE_30, 20, 670, 0.8, click.str());

            }

            if (m_tauler.esPosicioValida(fila, col))
            {
                int filaMatriu = 7 - fila;
                Fitxa fitxa = m_tauler.getFitxa(fila, col);
                Posicio clicada;
                clicada.setPosicio(clicada.PosicioAString(col, fila));


                if (!m_pecaSeleccionada) {
                    // Selecció inicial
                    if (fitxa.getTipus() != TIPUS_EMPTY && fitxa.getColor() == m_jugadorActual) {
                        PecaSeleccionada = fitxa;
                        m_pecaSeleccionada = true;
                        Posicio origen = fitxa.getPosicio();
                        m_tauler.getPosicionsPossibles(origen, m_movimentsPecaSeleccionada);
                    }
                }
                else {
                    //trobar cami mes llarg per buffar peça
                    int maxCami = 0; //variable con la distancia del camino mas largo possible
                    bool esMovimentMatar = false;
                    for (int i = 0; i < m_movimentsPecaSeleccionada.size(); ++i)
                    {
                        if (m_movimentsPecaSeleccionada[i].getCami().size() > maxCami)
                            maxCami = m_movimentsPecaSeleccionada[i].getCami().size();
                        if (m_movimentsPecaSeleccionada[i].getTipusMoviment() == MATAR)
                            esMovimentMatar = true;
                    }


                    // Comprovar si clic és destí vàlid
                    for (int i = 0; i < m_movimentsPecaSeleccionada.size(); ++i)
                    {
                        Moviment m = m_movimentsPecaSeleccionada[i];
                        
                        for (int j = 0; j < m_movimentsPecaSeleccionada[i].getCami().size(); j++)
                        {
                            if (m.getCami()[j] == clicada)
                            {
                                SerONoSer(maxCami, esMovimentMatar, j, m);
                                break;
                            }
                        }
                    }
                }
            }

        }
        else 
        {
            // Clic fora del tauler, deseleccionar fitxa
            m_pecaSeleccionada = false;
            m_movimentsPecaSeleccionada.clear();
        }
    }

    // --- M O D E   R E P L A Y ---
    else if (m_modeJoc == MODE_JOC_REPLAY)
    {
        bool clickDetectado = (mouseStatus && !m_mouseAnterior);  // flanco de subida

        if (clickDetectado &&
            mousePosX >= POS_X_TAULER && mousePosX <= POS_X_TAULER + (AMPLADA_CASELLA * FILES) &&
            mousePosY >= POS_Y_TAULER && mousePosY <= POS_Y_TAULER + (AMPLADA_CASELLA * FILES))
        {
            if (m_cua.getSize() != 0)
            {
                Moviment m = m_cua.getInici()->getValor();
                m_cua.pop();
                m_tauler.mouFitxa(m.getOrigen(), m.getDesti());

                string moviment = m.getOrigen().getPosicio() + " ---------> " + m.getDesti().getPosicio();
                GraphicManager::getInstance()->drawFont(FONT_GREEN_30, 20, 720, 1.0, moviment);

                if (m_tauler.comprovaFinalPartida(m_guanyador))
                    m_finalPartida = true;
                else
                    m_jugadorActual = 1 - m_jugadorActual;
            }
            else
            {
                GraphicManager::getInstance()->drawFont(FONT_RED_30, 250, 700, 0.5, "No queden moviments.");
            }
        }

        // IMPORTANTE: actualizar el estado anterior del mouse DESPUÉS del procesamiento
        m_mouseAnterior = mouseStatus;
    }

    
    // Mostrar fitxes
    m_tauler.visualitza();
    
    // Mostrar posicions vàlides
    if (m_pecaSeleccionada) {
        if (m_pecaSeleccionada) {
            for (int i = 0; i < m_movimentsPecaSeleccionada.size(); ++i) 
            {
                const vector<Posicio>& cami = m_movimentsPecaSeleccionada[i].getCami();

                for (int j = 0; j < cami.size(); ++j) 
                {
                    int fila, columna;
                    cami[j].stringToInts(cami[j].getPosicio(), fila, columna);


                    int px = CASELLA_INICIAL_X + columna * AMPLADA_CASELLA + correcioErrorPosicioX;
                    int py = CASELLA_INICIAL_Y + fila * ALCADA_CASELLA + correcioErrorPosicioX;
                    px += AMPLADA_CASELLA;


                    GraphicManager::getInstance()->drawSprite(GRAFIC_POSICIO_VALIDA, px, py);
                }
            }
        }

    }
    
    return false;
}

void Joc::finalitza(ModeJoc mode, const string& nomFitxerMoviments)
{
    if (mode != MODE_JOC_NORMAL)
        return;

    ofstream fitxer(nomFitxerMoviments);

    if (!fitxer.is_open())
    {
        cerr << "No s'ha pogut obrir el fitxer: " << nomFitxerMoviments << endl;
        return;
    }

    NodeMoviments* it = m_cua.getInici();

    while (it != nullptr)
    {
        fitxer << it->getValor().getOrigen() << " " << it->getValor().getDesti() << endl;
        it = it->getNext();
    }

    fitxer.close(); // opcional, pero recomanat
}

void Joc::SerONoSer(int maxCami, const bool& esMovimentMatar, int j, const Moviment& m)
{
    if ((j + 1) == maxCami)
    {
        if (maxCami == 1 && esMovimentMatar && m.getTipusMoviment() == MATAR) //moviment
        {
            if (m_tauler.mouFitxa(PecaSeleccionada.getPosicio(), m.getCami()[j]))
            {
                m_cua.push(Moviment(PecaSeleccionada.getPosicio(), m.getCami()[j]));
                m_pecaSeleccionada = false;
                m_movimentsPecaSeleccionada.clear();

                if (m_tauler.comprovaFinalPartida(m_jugadorActual))
                {
                    m_finalPartida = true;
                }
                else
                {
                    m_jugadorActual = 1 - m_jugadorActual;
                }
            }
        }
        else if (maxCami == 1 && !esMovimentMatar) //moviment
        {
            if (m_tauler.mouFitxa(PecaSeleccionada.getPosicio(), m.getCami()[j]))
            {
                m_cua.push(Moviment(PecaSeleccionada.getPosicio(), m.getCami()[j]));
                m_pecaSeleccionada = false;
                m_movimentsPecaSeleccionada.clear();

                if (m_tauler.comprovaFinalPartida(m_jugadorActual))
                {
                    m_finalPartida = true;
                }
                else
                {
                    m_jugadorActual = 1 - m_jugadorActual;
                }
            }
        }
        else if (maxCami = 1 && esMovimentMatar && m.getTipusMoviment() == MOVIMENT) //bufada
        {
            m_tauler.bufarFitxa(PecaSeleccionada.getPosicio());
            m_pecaSeleccionada = false;
            m_movimentsPecaSeleccionada.clear();
            if (m_tauler.comprovaFinalPartida(m_jugadorActual))
            {
                m_finalPartida = true;
            }
            else
            {
                m_jugadorActual = 1 - m_jugadorActual;
            }
        }
        else//maxCami != 1
        {
            if (m_tauler.mouFitxa(PecaSeleccionada.getPosicio(), m.getCami()[j]))
            {
                m_cua.push(Moviment(PecaSeleccionada.getPosicio(), m.getCami()[j]));
                m_pecaSeleccionada = false;
                m_movimentsPecaSeleccionada.clear();

                if (m_tauler.comprovaFinalPartida(m_jugadorActual))
                {
                    m_finalPartida = true;
                }
                else
                {
                    m_jugadorActual = 1 - m_jugadorActual;
                }
            }
        }

    }
    else
    {
        m_tauler.bufarFitxa(PecaSeleccionada.getPosicio());
        m_pecaSeleccionada = false;
        m_movimentsPecaSeleccionada.clear();
        if (m_tauler.comprovaFinalPartida(m_jugadorActual))
        {
            m_finalPartida = true;
        }
        else
        {
            m_jugadorActual = 1 - m_jugadorActual;
        }
    }

}