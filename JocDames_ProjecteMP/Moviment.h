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
    void setOrigen(const Posicio& posicio);
    void setDesti(const Posicio& posicio);
    void setPecesMortes(int pecesMortes);

    //getters
    Posicio getOrigen() const;
    Posicio getDesti() const;
    int getPecesMortes() const;

    /**
     Comprova si el moviment �s v�lid.
     * @return Cert si el moviment �s v�lid, fals altrament.
     */
    bool esValid() const;

private:
    Posicio m_origen;     // Posicio d'origen del moviment.
    Posicio m_desti;      // Posicio de desti del moviment.
    int m_pecesMortes;    // Nombre de peces contraries mortes en aquest moviment.
};
