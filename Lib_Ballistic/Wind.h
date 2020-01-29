#ifndef WIND_H
#define WIND_H
#include "Conversions.h"

#include "Lib_Ballistic_global.h"


    class LIB_BALLISTIC_EXPORT Wind
	{
	public:
		///<summary>Ruzgar hesaplamalarinin yapildigi nesne.</summary>
		///<param name = "incSpeed">Hiz cinsinden deger</param>
		///<param name = "incAngle">Aci cinsinden deger</param>
		Wind(double incSpeed, double incAngle);
		Wind();
		~Wind();
		double getCrossWindSpeed();
		double getHeadWindSpeed();
		double getCrossWindSpeedinfeetpers();
		double getHeadWindSpeedinfeetpers();
		double getAngle();
		double getSpeed();
		///<summary>Yandan esen ruzgar hesaplamasini yapar</summary>
		///<param name = "incAngle">Aci cinsinden deger</param>
		///<param name = "incSpeed">Hiz cinsinden deger</param>
		double CalculateCrossWind(double incAngle, double incSpeed);
		///<summary>Karsi yonden esen ruzgar hesaplamasini yapar.</summary>
		///<param name = "incSpeed">Hiz cinsinden deger</param>
		///<param name = "incAngle">Aci cinsinden deger</param>
		double CalculateHeadWind(double incAngle, double incSpeed);
		void setAngle(double angle);
		void setSpeed(double speed);
	private:
		double CrossWindSpeed;
		double HeadWindSpeed;
		double Angle;
		double Speed;
	};

#endif
