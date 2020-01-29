#ifndef FLIGHTSPEED_H
#define FLIGHTSPEED_H

#include<math.h>
#include "Conversions.h"

#include "Lib_Ballistic_global.h"


    class LIB_BALLISTIC_EXPORT FlightSpeed
	{
	public:
		///<summary>Ucus anındaki x,y ve z parametlerine göre hizi hesaplar</summary>
		///<param name = "incSpeed">Hiz cinsinden deger</param>
		///<param name = "incVerticalAngle">Dikey aci cinsinden deger</param>
		///<param name = "incHorizontalAngle">Yatay aci cinsinden deger</param>
		FlightSpeed(double incSpeed, double incVerticalAngle, double incHorizontalAngle);
		~FlightSpeed();
		double getXComponent();
		double getYComponent();
		double getZComponent();
	private:
		double XSpeed;
		double YSpeed;
		double ZSpeed;
		double VerticalAngle;
		double HorizontalAngle;
	};
#endif
