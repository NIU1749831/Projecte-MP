#ifndef TAULER_HPP
#define TAULER_HPP

#include <iostream>
#include <vector>
#include <queue>
#include<stack>
#include <fstream>
#include "Fitxa.h"
using namespace std;

#define FILES 8
#define COLUMNES 8
#define N_FILES 7
#define N_COLUMNES 7

typedef struct {
    Posicio pos;
    vector<Posicio> camino;
} Nodo;

class Tauler
{
public:
    Fitxa getFitxa(int fila, int columna) const { return m_tauler[fila][columna]; }

    void inicialitza(const string& nomFitxer);
    void actualitzaMovimentsValids();
    bool mouFitxa(const Posicio& origen, const Posicio& desti);
    void getPosicionsPossibles(const Posicio& origen, vector<Moviment>& posicionsPossibles);
    string toString() const;
    bool esMovimentDeCaptura(const Posicio& origen, const Posicio& desti) const;
    bool esPosicioValida(int i, int j) const;
    //return true si hay movimiento de matar
    bool obtenirPosicionsValides(int i, int j, stack<Moviment>& SimplesPossibles, stack<Moviment>& MatarPossible);
    void verificarCaptura(int i, int j, int direccio, int deltaJ, stack<Moviment>& MatarPossible);
    void verificarMovimentsDama(int i, int j, stack<Moviment>& MatarPossible,stack<Moviment>& SimplesPossibles);
    void dfs(int i, int j, int direccio, vector<Moviment>& MovimentsPossibles);
    void dfsRecursiu(int i, int j, Moviment movimentActual, vector<Moviment>& resultats, bool visitat[FILES][COLUMNES]);

    bool comprovaFinalPartida(int jugador);
    void visualitza() const;
    void bufarFitxa(const Posicio& p);


private:
    Fitxa m_tauler[FILES][COLUMNES];
};

#endif