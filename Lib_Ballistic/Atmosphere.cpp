#include "Atmosphere.h"

#include "Lib_Ballistic_global.h"

///<summary>Verilen hava yogunluguna ve ruzgar degerine gore atmosfer nesnesi yaraticisi.</summary>
///<param name = "IncAirDensity">Hava yogunlugu objesi</param>
///<param name = "IncWind">Ruzgar objesi</param>
Atmosphere::Atmosphere(AirDensity IncAirDensity, Wind IncWind)
{		
	/*this->airDensity = &IncAirDensity;
	this->wind = &IncWind;   */

	this->airDensity = IncAirDensity;
	this->wind = IncWind;

}
///<summary>Sabit degerlere gore hava yogunlugu ve ruzgr nesnesi yaratıcısı.</summary>
Atmosphere::Atmosphere()
{	
	 AirDensity airDensity (85, 20, 0, 760);
	 Wind wind (0, 0);	
	 this->airDensity = airDensity;
	 this->wind = wind;
}

Atmosphere::~Atmosphere()
{
}

AirDensity Atmosphere::getAirDensity()
{
	return airDensity;
}

void Atmosphere::setAirDensity(AirDensity incAirDensity)
{
	airDensity = incAirDensity;
}

Wind Atmosphere::getWind()
{
	return wind;
}

void Atmosphere::setWind(Wind incWind)
{
	wind = incWind;
}
