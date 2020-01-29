#ifndef ATMOSPHERE_H
#define ATMOSPHERE_H
#include "AirDensity.h"
#include "Wind.h"


#include "Lib_Ballistic_global.h"

	class Atmosphere
	{
	public:
		///<summary>Verilen hava yogunluguna ve ruzgar degerine gore atmosfer nesnesi yaraticisi.</summary>
		///<param name = "IncAirDensity">Hava yogunlugu objesi</param>
		///<param name = "IncWind">Ruzgar objesi</param>
		Atmosphere(AirDensity IncAirDensity, Wind IncWind);
		///<summary>Sabit degerlere gore hava yogunlugu ve ruzgr nesnesi yaratıcısı.</summary>
		Atmosphere();
		~Atmosphere();
		AirDensity getAirDensity();
		void setAirDensity(AirDensity incAirDensity);
		Wind getWind();
		void setWind(Wind incWind);
	private:
		AirDensity airDensity;
		Wind wind;
	};


#endif
