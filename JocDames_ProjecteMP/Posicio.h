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

	/*
	* @brief Funcion que nos permite converitr una posicion en formati string a dos valores int, la usaremos solo en la classe Tauler para trabajar con m_tauler
	* @params string posicion que ceremos convrtir i los valors de i,j a los que convertimos la posicion
	* @return n otendra return
	*/
    void stringToInts(const string& posicio, int& i, int& j);
private:
	int m_x, m_y;
	string m_posicio;
};