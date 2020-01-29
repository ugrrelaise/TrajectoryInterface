#include "AirDensity.h"
#include<math.h>


///<summary>Hava yogunlugu obje yaraticisi</summary>
///<param name = "H">Nem değeri</param>
///<param name = "T">Sıcaklık değeri</param>
///<param name = "A">İrtifa değeri</param>
///<param name = "P">Basınç değeri</param>
AirDensity::AirDensity(double H, double T, double A, double P)
{
	Humidity = H;
	Temperature = T;
	Altitude = A;
	Pressure = P;
}

AirDensity::AirDensity()
{
}
AirDensity::~AirDensity()
{
}
// Hava Yoğunluğunu döndürür.
///<summary>Hava yogunlugu degerini hesaplayan fonskiyonu döndürür.</summary>
double AirDensity::CalculateAirDensity()
{
	return CalculateAirDensity(Humidity,Temperature, Altitude, Pressure);
}
//Hava yoğunluğunu hesaplar.
///<summary>Hava yogunlugu degerini hesaplar</summary>
///<param name = "H">Nem değeri</param>
///<param name = "T">Sıcaklık değeri</param>
///<param name = "A">İrtifa değeri</param>
///<param name = "P">Basınç değeri</param>
double AirDensity::CalculateAirDensity(double H, double T, double A, double P)
{
	//Env0,K1,K2 sabit katsayı değerleri.
	double Env0 = 0.0023342877450915;
	double K1 = 0.190284;
	double K2 = 0.000084288;
	
	double Pressure1 = pow((P * 0.03937 *  33.863881579), K1);
	double Pressure2 = (A * 3.2808399 * K2) / 3.3804;
	double PressureEnd = (pow((Pressure1 - Pressure2), 1 / K1)) / 33.863881579;
	
	double SaturationPressure = 0.1804281 * (pow(10, (7.5 * T) / (T + 237.7)));
	double Temp = (0.02289205 * PressureEnd) / (T + 273.15);
	double Env1 = (Temp * (PressureEnd - 0.3783 * 0.01 * H * SaturationPressure)) / PressureEnd;

	double AirDensity = Env1 / Env0;

	return AirDensity;
}

double AirDensity::getAltitude()
{
	return Altitude;
}

void AirDensity::setAltitude(double altitude)
{
	Altitude = altitude;
}

double AirDensity::getHumidity()
{
	return Humidity;
}

void AirDensity::setHumidity(double humidity)
{
	Humidity = humidity;
}

double AirDensity::getPressure()
{
	return Pressure;
}

void AirDensity::setPressure(double pressure)
{
	Pressure = pressure;
}

double AirDensity::getTemperature()
{
	return Temperature;
}

void AirDensity::setTemperature(double temperature)
{
	Temperature = temperature;
}
