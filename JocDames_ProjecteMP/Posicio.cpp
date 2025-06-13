#include "Posicio.hpp"
#include <sstream>

bool Posicio::operator==(const Posicio& posicio) const
{
    return (m_posicio == posicio.m_posicio);
}

string Posicio::PosicioAString(int x, int y)
{
    return string(1, 'a' + x) + string(1, '1' + y);
}

void Posicio::stringToInts(const string& posicio, int& i, int& j) const
{
    j = posicio[0] - 'a';
    i = posicio[1] - '1';
}

ostream& operator<<(ostream& out, const Posicio& pos)
{
    return out << pos.getPosicio();
}
