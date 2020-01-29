#ifndef CONVERSIONS_H
#define CONVERSIONS_H

#include "Lib_Ballistic_global.h"


	class Conversions
	{
	public:
		///<summary>Matematiksel donusumlerin yapildigi nesne.</summary>
		Conversions();
		~Conversions();
		static double PI;
		///<summary>Santimetreyi inche donusturur.</summary>
		///<param name = "Cm">Santimetre cinsinden deger</param>
		static double CmToInch(double Cm);
		///<summary>Inchi santimetreye donusturur.</summary>
		///<param name = "Inch">Inch cinsinden deger</param>
		static double InchToCm(double Inch);
		///<summary>Fahrenheiti Celsiusa donusturur.</summary>
		///<param name = "Fahrenheit">Fahrenheit cinsinden deger</param>
		static double FahrenheitToCelsius(double Fahrenheit);
		///<summary>Celsiusu Fahrenheita donusturur.</summary>
		///<param name = "Celsius">Celsius cinsinden deger</param>
		static double CelsiusToFahrenheit(double Celsius);
		///<summary>Milibarı inç civaya donusturur.</summary>
		///<param name = "Mbar">Milibar cinsinden deger</param>
		static double MbarToHg(double Mbar);
		///<summary>İnç civayı milibara donusturur.</summary>
		///<param name = "Hg">İnç civa cinsinden deger</param>
		static double HgToMbar(double Hg);
		///<summary>Dereceyi radyana donusturur.</summary>
		///<param name = "Degree">Derece cinsinden deger</param>
		static double DegreeToRadian(double Degree);
		///<summary>Radyanı dereceye donusturur.</summary>
		///<param name = "Radian">Radyan cinsinden deger</param>
		static double RadianToDegree(double Radian);
		///<summary>Fahrenheiti Kelvine donusturur.</summary>
		///<param name = "Fahrenheit">Fahrenheit cinsinden deger</param>
		static double FahrenheitToKelvin(double Fahrenheit);
		///<summary>Kelvini Fahrenheita donusturur.</summary>
		///<param name = "Kelvin">Kelvin cinsinden deger</param>
		static double KelvinToFahrenheit(double Kelvin);
		///<summary>Santimetreyi Feete donusturur.</summary>
		///<param name = "Cm">Santimetre cinsinden deger</param>
		static double CmToFeet(double Cm);
		///<summary>Feeti santimetreye donusturur.</summary>
		///<param name = "Feet">Feet cinsinden deger</param>
		static double FeetToCm(double Feet);
		///<summary>Kilometre/saati mil/saate donusturur.</summary>
		///<param name = "Km">Kilometre cinsinden deger</param>
		static double KmPerHourToMilesPerHour(double Km);
		///<summary>Mil/saati kilometre/saate donusturur.</summary>
		///<param name = "Miles">Mil cinsinden deger</param>
		static double MilesPerHourToKmPerHour(double Miles);
		///<summary>Mil/saati feet/saniyeye donusturur.</summary>
		///<param name = "Miles">Mil cinsinden deger</param>
		static double MilesPerHourToFeetPerSecond(double Miles);
		///<summary>Feet/saniyeyi Mil/saate donusturur.</summary>
		///<param name = "Feet">Feet cinsinden deger</param>
		static double FeetPerSecondToMilesPerHour(double Feet);
		///<summary>Feete/saniyeyi metre/saniyeye donusturur.</summary>
		///<param name = "Feet">Feet cinsinden deger</param>
		static double FeetPerSecondToMeterPerSecond(double Feet);
		///<summary>Metre/saniyeyi feet/saniyeye donusturur.</summary>
		///<param name = "Meter">Metre cinsinden deger</param>
		static double MeterPerSecondToFeetPerSecond(double Meter);
	};

#endif
