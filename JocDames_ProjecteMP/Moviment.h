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
    void setOrigen(const Posicio& posicio);
    void setDesti(const Posicio& posicio);
    void setPecesMortes(int pecesMortes);

    //getters
    Posicio getOrigen() const;
    Posicio getDesti() const;
    int getPecesMortes() const;

    /**
     Comprova si el moviment és vàlid.
     * @return Cert si el moviment és vàlid, fals altrament.
     */
    bool esValid() const;

private:
    Posicio m_origen;     // Posició d'origen del moviment.
    Posicio m_desti;      // Posició de destí del moviment.
    int m_pecesMortes;    // Nombre de peces contràries mortes en aquest moviment.
};
