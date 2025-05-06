#include <iostream>
#include <vector>
#include <queue>
#include<fstream>
#include "Fitxa.h"
using namespace std;

// dimension del tauler
#define FILES 8
#define COLUMNES 8

// Per controlar els bucles que necessiten tenir fer servir la dimensio del tauler
#define N_FILES 7
#define N_COLUMNES 7

typedef struct {
    Posicio pos;
    vector<Posicio> camino;
} Nodo;

class Tauler
{
public:
    /*
    * @brief Aquesta funcio inicialitza el tauler d'una partida en funcio d'un fitxer
    * @params El nom del fitxer, on es troben les posicions de les fitxes
    * @return no te return, es un metode
    */
    void inicialitza(const string& nomFitxer); //TOT BE

    /*
    * @brief Funcio que ens permet actualitzar tots els moviments valids de qualsevol de les fitxes del tauler
    * @params no te parametres, ja que la posicio de la fitxa es pot accedir des de la classe fitxa
    * @return es un metode, no te returns
    */
    void actualitzaMovimentsValids(); //TOT BE

    /*
    * @brief Aquesta funcio mou la fitxa cap a una posicio desti, tenint en compte la posicio d'aquesta fitxa
    *        Comprovara si el moviment esta dins dels moviments valids d'aquesta fitxa
    * @params la posicio d'origen ens permet saber la fitxa que volem moure, i la posicio desti es la posicio final del moviment
    * @return retornara false, en cas que no s'hagi pogut realitzar el moviment, i true en cas contrari
    */
    bool mouFitxa(const Posicio& origen, const Posicio& desti); //TOT BE

    /*
    * @brief es un getter que ens retorna totes les posicions possibles (i el numero d'elles) a les que es pot moure una fitxa
    * @param Posicio origen --> Ens permet saber quina es la peça que volem aconseguirs les posicions
    * @param Int nPosicions --> "return" del numero de posicions possibles
    * @param Posicio posicionsPossibles[] -> Array amb les posicions possibles d'una fitxa
    */
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]); //TOT BE

    /*
    * @brief converteix una posicio en forma de doble int a una variable Posicio i afegeix aquest moviment a l'array de MovimentsPossibles d'una fitxa
    * @params dos ints, que ens serveixen per generar una variable posicio
    * @return es un metode, no te return
    */
    void asigna(int i, int j); //TOT BE

    /*
    * @brief ens permet convertir el tauler en un string
    * @params no te parametres, ja que nomes fa servir el tauler que ja forma part de la classe
    * @return retorna el string amb el tauler
    */
    string toString() const; //TOT BE

    /*
    *@brief Ens permet comprovar si un moviment es de captura o no
    * @param Posicio origen --> Ens permet saber quina es la fitxa 
    * @param Posicio desti --> Ens indica quin moviment es 
    * @return true en cas que sigui un moviment de captura i false si no ho es
    */
    bool esMovimentDeCaptura(const Posicio& origen, const Posicio& desti) const; //TOT BE
                    
    /*
    *@brief Comprova si una posicio es valida (esta dintre del taulell)
    * @param int i,j --> La posicio en format de coordanades
    * @return true si es valida, false en cas que no sigui valida
    */
    bool esPosicioValida(int i, int j) const; //TOT BE

    /*
    * @brief Ens permet obtenir totes les posicions a les que es pot moure una fitxa, tenint en compte si es dama o no
    * @param int i,j --> posicio de la fitxa en forma cartesiana
    * @param tor<Posicio>& posicionsValides --> Vector on anem guardant les posicions a mesura que les anem troabt
    */
    void obtenirPosicionsValides(int i, int j, vector<Posicio>& posicionsValides); //TOT BE

    void verificarCaptura(int i, int j, int direccio, int deltaJ, vector<Posicio>& posicionsValides);

    void verificarMovimentsDama(int i, int j, vector<Posicio>& posicionsValides);

    void bfs(int i, int j, int direccio, Posicio posicionsPossibles[], int& nPosicions);

private:
    Fitxa m_tauler[FILES][COLUMNES];
};