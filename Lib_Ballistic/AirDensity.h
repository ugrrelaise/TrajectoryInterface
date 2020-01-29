#ifndef AIRDENSITY_H
#define AIRDENSITY_H

#include "Lib_Ballistic_global.h"


    class LIB_BALLISTIC_EXPORT AirDensity
	{
		double Altitude;
		double Humidity;
		double Pressure;
		double Temperature;
	public:
		///<summary>Hava yogunlugu obje yaraticisi</summary>
		///<param name = "H">Nem değeri</param>
		///<param name = "T">Sıcaklık değeri</param>
		///<param name = "A">İrtifa değeri</param>
		///<param name = "P">Basınç değeri</param>
		AirDensity(double H, double T, double A, double P);
		AirDensity();
		~AirDensity();
		///<summary>Hava yogunlugu degerini hesaplayan fonskiyonu döndürür.</summary>
		double CalculateAirDensity();
		///<summary>Hava yogunlugu degerini hesaplar</summary>
		///<param name = "H">Nem değeri</param>
		///<param name = "T">Sıcaklık değeri</param>
		///<param name = "A">İrtifa değeri</param>
		///<param name = "P">Basınç değeri</param>
		double CalculateAirDensity(double H, double T, double A, double P);
		double getAltitude();
		void setAltitude(double altitude);
		double getHumidity();
		void setHumidity(double humidity);
		double getPressure();
		void setPressure(double pressure);
		double getTemperature();
		void setTemperature(double temperature);
	};

#endif
