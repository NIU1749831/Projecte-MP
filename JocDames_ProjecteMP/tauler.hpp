#include <iostream>
#include "Fitxa.h"
using namespace std;

//dimensio del tauler
#define FILES 8
#define COLUMNES 8

//Per controlar els bucles que necesiten tenir fer servir la dimensio del tauler
#define N_FILES  7
#define N_COLUMNES  7


class Tauler
{
public:

    /*
    * @brief Esta funcion inicializa el tablero de una partida en funcion de un fitxero
    * @params El nombre del fitxero, donde se encuentran las posiciones de las fitxas
    * @return no tiene return, es un metodo
    */
    void inicialitza(const string& nomFitxer); //fet

    /*
    * @brief Funcio que nos permite actualizar todos los movimientos validos de cualquiera de las fitxas del tablero, para poder 
    *        actualiazar el array de movimentsValids de la classe Fitxa
    * @params no tiene parametros, ya que la posicion del a fitxa se puede acceder des de la classe fitxa
    * @return es un metodo, no tiene returns
    */
    void actualitzaMovimentsValids();

    /*
    * @brief Esta funcion mueve la ficha hacia una posicion destino, teniendo en cuenta la posicon de esa ficha, tambien tendra en cuenta si mata alguan/s ficha por el camino
    *        Comprovara si el movimiento esta dentro de los movimientos validos de esa ficha, tambien convertira a esa ficha en dama si llega al final del tablero
    * @params, la posicion de origen nos permite saber la ficha que queremos mover, y la posicion desti, es la posicion final del movimiento
    * @return, retornara false, en caso que no se haya podido realizar el movimiento, y true en caso contrario 
    */
    bool mouFitxa(const Posicio& origen, const Posicio& desti);

    /*
    * @brief Esta funcion nos permite calcular todos los movimientos possibles que peude hacer una pieza en una posicion origen
    * @params la posicion de origen, la cual nos indica que pieza queremos analiazr; nPosicones es el numero de posiciones que puede hacer la pieza, 
    *         y el array de posiciones psssibles de la pieza 
    */
    void getPosicionsPossibles(const Posicio& origen, int& nPosicions, Posicio posicionsPossibles[]);

    /*
    * @brief convierte una posicion en forma de doble int a una variable Posicio y añade ese movimiento al array de MovimentsPossibles de una ficha
    * @params dos ints, que nos sirven para generar una variable posicion
    * @reutrn es un metodo, no tiene return
    */
    void asigna(int i, int j); //fet

    /*
    * @brief, nos permite convertir el tablero en un string
    * @params no tiene parametros, ya que solo usa el tablero que ya forma parte de la classe
    * @ return retorna el string con el tablero
    */
    string toString() const; //fet

    /*
    @brief: aquest funcio ens permet realitzar un algoritme de bfs, ja que tractem el taulell com un graf, es una funcio auxiliar de getPosicionsPosssibles
    @params
        *int i,j --> ens donen la posicio dintre del taulell, son its i no Posicio, ja que es mes facil per treballar amb la matriu del taulell
        *            i,j no estan passats per referencia, ja que els necesitem modificar dintre de la funcio, sense alterar la posicio fora de la funcio
        * int direccio --> ens serveix per poder distingir entre peçes blanques i negres
        * Posicio posicionsPossibles[] --> Es l'array on es van guardant totes les posicions possibles del graf/taulell
        * int6 nPosicions --> El numero de posicions a les cuals es pot moure la fitxa de la posicio i,j
    @return no te return, ja que es un metode el cual ens serveix per opmplir l'array posicionsPossibles
        */
    void bfs(int i, int j, int direccio, Posicio posicionsPossibles[], int& nPosicions);
private:
    Fitxa m_tauler[FILES][COLUMNES];
};
