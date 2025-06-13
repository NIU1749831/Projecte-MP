#ifndef TAULER_HPP
#define TAULER_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <fstream>
#include "Fitxa.h"

using namespace std;

// Dimensions del tauler
#define FILES 8
#define COLUMNES 8
#define N_FILES 7
#define N_COLUMNES 7

/**
 * @brief Estructura auxiliar que representa un node amb una posici�
 *        i un cam� associat (normalment usada per recorreguts).
 */
typedef struct {
    Posicio pos;
    vector<Posicio> camino;
} Nodo;

/**
 * @brief Classe que representa el tauler del joc. Gestiona les fitxes, els moviments
 *        v�lids, les captures i les regles b�siques del joc.
 */
class Tauler
{
public:
    /**
     * @brief Obt� la fitxa que hi ha a una determinada casella.
     * @param fila Fila del tauler (0 a 7).
     * @param columna Columna del tauler (0 a 7).
     * @return Fitxa situada a la posici� indicada.
     */
    Fitxa getFitxa(int fila, int columna) const { return m_tauler[fila][columna]; }

    /**
     * @brief Inicialitza el tauler amb les dades llegides d�un fitxer.
     * @param nomFitxer Ruta del fitxer amb la configuraci� inicial.
     */
    void inicialitza(const string& nomFitxer);

    /**
     * @brief Recalcula els moviments v�lids per a totes les fitxes del tauler.
     */
    void actualitzaMovimentsValids();

    /**
     * @brief Mou una fitxa des d'una posici� d'origen a una de dest� si �s v�lid.
     * @param origen Casella de sortida.
     * @param desti Casella de destinaci�.
     * @return true si el moviment ha estat realitzat correctament.
     */
    bool mouFitxa(const Posicio& origen, const Posicio& desti);

    /**
     * @brief Calcula les possibles posicions a les quals pot moure's una fitxa.
     * @param origen Posici� actual de la fitxa.
     * @param posicionsPossibles Vector on s'emmagatzemaran els moviments legals.
     */
    void getPosicionsPossibles(const Posicio& origen, vector<Moviment>& posicionsPossibles);

    /**
     * @brief Converteix el tauler a una representaci� en text.
     * @return Cadena que representa el contingut del tauler.
     */
    string toString() const;

    /**
     * @brief Comprova si un moviment de captura �s possible entre dues posicions.
     */
    bool esMovimentDeCaptura(const Posicio& origen, const Posicio& desti) const;

    /**
     * @brief Determina si una posici� donada es troba dins dels l�mits v�lids del tauler.
     */
    bool esPosicioValida(int i, int j) const;

    /**
     * @brief Busca i separa els moviments v�lids (normals i de captura) per una fitxa.
     * @param i Fila de la fitxa.
     * @param j Columna de la fitxa.
     * @param SimplesPossibles Stack on es guarden moviments normals.
     * @param MatarPossible Stack on es guarden moviments amb captura.
     * @return true si hi ha alguna captura disponible.
     */
    bool obtenirPosicionsValides(int i, int j, stack<Moviment>& SimplesPossibles, stack<Moviment>& MatarPossible);

    /**
     * @brief Verifica si una pe�a pot capturar en una direcci� concreta.
     */
    void verificarCaptura(int i, int j, int direccio, int deltaJ, stack<Moviment>& MatarPossible);

    /**
     * @brief Calcula els moviments especials que pot fer una dama (fitxa promocionada).
     */
    void verificarMovimentsDama(int i, int j, stack<Moviment>& MatarPossible, stack<Moviment>& SimplesPossibles);

    /**
     * @brief Algorisme DFS no recursiu per explorar moviments complexos (ex: cadenes de captures).
     */
    void dfs(int i, int j, int direccio, vector<Moviment>& MovimentsPossibles);

    /**
     * @brief Versi� recursiva del DFS per explorar tots els moviments possibles d�una fitxa.
     */
    void dfsRecursiu(int i, int j, Moviment movimentActual, vector<Moviment>& resultats, bool visitat[FILES][COLUMNES]);

    /**
     * @brief Comprova si la partida ha finalitzat per a un dels jugadors.
     * @param jugador Jugador que es vol comprovar (0 o 1).
     * @return true si no pot fer cap moviment v�lid.
     */
    bool comprovaFinalPartida(int jugador);

    /**
     * @brief Mostra el tauler actual pel terminal (per depuraci� o consola).
     */
    void visualitza() const;

    /**
     * @brief Elimina la fitxa que hi ha en una posici� determinada (es bufa).
     */
    void bufarFitxa(const Posicio& p);

private:
    Fitxa m_tauler[FILES][COLUMNES]; // Matriu que representa totes les caselles del tauler.
};

#endif
