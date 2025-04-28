#include "Posicio.h"

/**
 * @class Moviment
 * @brief Classe que representa un moviment possible d'una fitxa al tauler de dames.
 *
 * Cont� informaci� sobre l'origen, dest�, peces mortes i cam� seguit durant el moviment.
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
     * @brief Constructor amb par�metres.
     * @param origen Posici� d'origen del moviment.
     * @param desti Posici� de dest� del moviment.
     * @param pecesMortes Nombre de peces contr�ries mortes en aquest moviment (opcional, per defecte 0).
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
<<<<<<< HEAD
     * Comprova si el moviment �s v�lid.
     * @return Cert si el moviment �s v�lid, fals altrament
=======
     Comprova si el moviment �s v�lid.
     * @return Cert si el moviment �s v�lid, fals altrament.
>>>>>>> 0693642b689bbe873acb45c7e0498da6a3f45f04
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
    * @return: retornara un bool en funci� de si ha pogut fer o no el moviment
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
<<<<<<< HEAD
    Posicio m_origen;     // Posici� d'origen del moviment.
    Posicio m_desti;      // Posici� de dest� del moviment.
    int m_pecesMortes;    // Nombre de peces contr�ries mortes en aquest moviment.
    char m_direccionMovimento;
=======
    Posicio m_origen;     // Posicio d'origen del moviment.
    Posicio m_desti;      // Posicio de desti del moviment.
    int m_pecesMortes;    // Nombre de peces contraries mortes en aquest moviment.
>>>>>>> 0693642b689bbe873acb45c7e0498da6a3f45f04
};
