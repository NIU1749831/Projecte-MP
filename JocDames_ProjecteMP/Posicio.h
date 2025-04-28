#include<iostream>

using namespace std;

class Posicio
{
public:
	//constructores por defecto y por parametro
	Posicio() :m_x(0), m_y(0), m_posicio("") {};
	Posicio(const string& posicio): m_posicio(posicio){};

	//setters
	void setPosicio(const string& posicio) { m_posicio = posicio; };

	//getters
	string getPosicio() const { return m_posicio; };

	//Funcion que convierte una posicon a un string
	//@params:la x,y son dos ints
	string PosicioAString();
	
	//sobrecarrega operador per comparar 
	bool operator==(const string& posicio);
private:
	int m_x, m_y;
	string m_posicio;
};