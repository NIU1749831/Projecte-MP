#pragma once
#include <iostream>
using namespace std;

class Posicio
{
public:
    Posicio() : m_posicio("") {}
    Posicio(const string& posicio) : m_posicio(posicio) {}

    void setPosicio(const string& posicio) { m_posicio = posicio; }
    string getPosicio() const { return m_posicio; }

    string PosicioAString(int x, int y);
    bool operator==(const Posicio& posicio) const;
    void stringToInts(const string& posicio, int& i, int& j) const;

private:
    string m_posicio;
};

ostream& operator<<(ostream& out, const Posicio& pos);
