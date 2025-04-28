#include "Posicio.h"

/**
 * @class Moviment
 * @brief Classe que representa un moviment possible d'una fitxa al tauler de dames.
 *
 * Conté informació sobre l'origen, destí, peces mortes i camí seguit durant el moviment.
 */
class Moviment
{
public:
    // Constructors
    /**
     * @brief Constructor per defecte.
     */
    Moviment();

    /**
     * @brief Constructor amb paràmetres.
     * @param origen Posició d'origen del moviment.
     * @param desti Posició de destí del moviment.
     * @param pecesMortes Nombre de peces contràries mortes en aquest moviment (opcional, per defecte 0).
     */
    Moviment(const Posicio& origen, const Posicio& desti, int pecesMortes = 0);

    // Setters
    void setOrigen(const Posicio& posicio) { m_origen = posicio; };
    void setDesti(const Posicio& posicio) { m_desti = posicio; };
    void setPecesMortes(int pecesMortes);
    void setDireccio(const char& direccio);

    //getters
    Posicio getOrigen() const;
    Posicio getDesti() const;
    int getPecesMortes() const;
    char getDireccio() const;

    /**
     * Comprova si el moviment és vàlid.
     * @return Cert si el moviment és vàlid, fals altrament
     */
    bool esValid() const;
    
    /*
    * Funcio que ens calcula la direccio cap a on es moura la fitxa en funcio de la direccio on anira
    * @params: no tindra parametres
    * @return: retornara un char, on d = dreta i e= esquerra
    */
    void calcularDireccion();

    /*
    * Funcio que ens permet realitzar un moviemnt normal
    * @params: no recive parametros
    * @return: retornara un bool en funció de si ha pogut fer o no el moviment
    */
    bool movimentNormal();

    /*
    * Funcio que nos permite realizar un movimiento de matar
    * @params: no recive parametros
    * @return: retornara un bool
    */
    bool movimentMatarUnaFitxa();

    /*
    * Funcio que ens permetra realitzar mes dun moviment de matar
    * @params: revra un valor int, amb el numero de cops que matara
    * @return: fara un return d'un bool en cas que hagi matat o no.
    */
    bool movimentMatarMultiplesFitxes();

private:
    Posicio m_origen;     // Posició d'origen del moviment.
    Posicio m_desti;      // Posició de destí del moviment.
    int m_pecesMortes;    // Nombre de peces contràries mortes en aquest moviment.
    char m_direccionMovimento;
};
