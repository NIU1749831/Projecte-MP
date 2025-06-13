#ifndef JOC_H
#define JOC_H

#include "Tauler.hpp"
#include"CuaMoviments.h"
#include <stdio.h>
#include "info_joc.hpp"

using namespace std;


class Joc 
{

public:
    bool actualitza(int mousePosX, int mousePosY, bool mouseStatus);
    void inicialitza(ModeJoc mode, const string& nomFitxerTauler, const string& nomFitxerMoviments);
    void finalitza(ModeJoc mode, const string& nomFitxerMoviments);
    void SerONoSer(int maxCami, const bool& esMovimentMatar, int j, const Moviment& m);
        
private:
    Tauler m_tauler;
    ModeJoc m_modeJoc;
    int m_jugadorActual;
    bool m_finalPartida;
    int m_guanyador;
    bool m_pecaSeleccionada;
    Fitxa PecaSeleccionada;
    CuaMoviments m_cua;
    vector<Moviment> m_movimentsPecaSeleccionada;
    bool m_mouseAnterior;
};

#endif 
