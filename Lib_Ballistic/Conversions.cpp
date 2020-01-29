#include "Conversions.h"
#include "Lib_Ballistic_global.h"
///<summary>Matematiksel donusumlerin yapildigi nesne.</summary>
Conversions::Conversions()
{
}


Conversions::~Conversions()
{
}
double Conversions::PI = 3.1415926535897931;
///<summary>Santimetreyi inche donusturur.</summary>
///<param name = "Cm">Santimetre cinsinden deger</param>
double Conversions::CmToInch(double Cm)
{
	double Inch = 0.393700787 * Cm;
	return Inch;
}
///<summary>Inchi santimetreye donusturur.</summary>
///<param name = "Inch">Inch cinsinden deger</param>
double Conversions::InchToCm(double Inch)
{
	double Cm = 2.54 * Inch;
	return Cm;
}
///<summary>Fahrenheiti Celsiusa donusturur.</summary>
///<param name = "Fahrenheit">Fahrenheit cinsinden deger</param>
double Conversions::FahrenheitToCelsius(double Fahrenheit)
{
	double Celsius = (Fahrenheit - 32) * 0.5555555555;
	return Celsius;
}
///<summary>Celsiusu Fahrenheita donusturur.</summary>
///<param name = "Celsius">Celsius cinsinden deger</param>
double Conversions::CelsiusToFahrenheit(double Celsius)
{
	double Fahrenheit = (1.8 * Celsius) + 32;
	return Fahrenheit;
}
///<summary>Milibarı inç civaya donusturur.</summary>
///<param name = "Mbar">Milibar cinsinden deger</param>
double Conversions::MbarToHg(double Mbar)
{
	double Hg = 0.0295300 * Mbar;
	return Hg;
}
///<summary>İnç civayı milibara donusturur.</summary>
///<param name = "Hg">İnç civa cinsinden deger</param>
double Conversions::HgToMbar(double Hg)
{
	double Mbar = 33.8639 * Hg;
	return Mbar;
}
///<summary>Dereceyi radyana donusturur.</summary>
///<param name = "Degree">Derece cinsinden deger</param>
double Conversions::DegreeToRadian(double Degree)
{
	double Radian = (PI / 180.0) * Degree;
	return Radian;
}
///<summary>Radyanı dereceye donusturur.</summary>
///<param name = "Radian">Radyan cinsinden deger</param>
double Conversions::RadianToDegree(double Radian)
{
	double Degree = (180.0 / PI) * Radian;
	return Degree;
}
///<summary>Fahrenheiti Kelvine donusturur.</summary>
///<param name = "Fahrenheit">Fahrenheit cinsinden deger</param>
double Conversions::FahrenheitToKelvin(double Fahrenheit)
{
	double Kelvin = ((Fahrenheit - 32) * (5.0 / 9.0)) + 273.15;
	return Kelvin;
}
///<summary>Kelvini Fahrenheita donusturur.</summary>
///<param name = "Kelvin">Kelvin cinsinden deger</param>
double Conversions::KelvinToFahrenheit(double Kelvin)
{
	double Fahrenheit = ((Kelvin - 273.15) * (9.0 / 5.0)) + 32;
	return Fahrenheit;
}
///<summary>Santimetreyi Feete donusturur.</summary>
///<param name = "Cm">Santimetre cinsinden deger</param>
double Conversions::CmToFeet(double Cm)
{
	double Feet = 0.032808399 * Cm;
	return Feet;
}
///<summary>Feeti santimetreye donusturur.</summary>
///<param name = "Feet">Feet cinsinden deger</param>
double Conversions::FeetToCm(double Feet)
{
	double Cm = 30.48 * Feet;
	return Cm;
}
///<summary>Kilometre/saati mil/saate donusturur.</summary>
///<param name = "Km">Kilometre cinsinden deger</param>
double Conversions::KmPerHourToMilesPerHour(double Km)
{
	double Miles = 1.609344 * Km;
	return Miles;
}
///<summary>Mil/saati kilometre/saate donusturur.</summary>
///<param name = "Miles">Mil cinsinden deger</param>
double Conversions::MilesPerHourToKmPerHour(double Miles)
{
	double Km = 0.621371192 * Miles;
	return Km;
}
///<summary>Mil/saati feet/saniyeye donusturur.</summary>
///<param name = "Miles">Mil cinsinden deger</param>
double Conversions::MilesPerHourToFeetPerSecond(double Miles)
{
	double Feet = 1.46666667 * Miles;
	return Feet;
}
///<summary>Feet/saniyeyi Mil/saate donusturur.</summary>
///<param name = "Feet">Feet cinsinden deger</param>
double Conversions::FeetPerSecondToMilesPerHour(double Feet)
{
	double Miles = 0.681818182 * Feet;
	return Miles;
}
///<summary>Feete/saniyeyi metre/saniyeye donusturur.</summary>
///<param name = "Feet">Feet cinsinden deger</param>
double Conversions::FeetPerSecondToMeterPerSecond(double Feet)
{
	double Meter = 0.3048 * Feet;
	return Meter;
}
///<summary>Metre/saniyeyi feet/saniyeye donusturur.</summary>
///<param name = "Meter">Metre cinsinden deger</param>
double Conversions::MeterPerSecondToFeetPerSecond(double Meter)
{
	double Feet = 3.2808399 * Meter;
	return Feet;
}

