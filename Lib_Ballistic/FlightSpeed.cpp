#include "FlightSpeed.h"
#include "Lib_Ballistic_global.h"
///<summary>Ucus anındaki x,y ve z parametlerine göre hizi hesaplar</summary>
///<param name = "incSpeed">Hiz cinsinden deger</param>
///<param name = "incVerticalAngle">Dikey aci cinsinden deger</param>
///<param name = "incHorizontalAngle">Yatay aci cinsinden deger</param>
FlightSpeed::FlightSpeed(double incSpeed, double incVerticalAngle, double incHorizontalAngle)
{
	VerticalAngle = incVerticalAngle;
	HorizontalAngle = incHorizontalAngle;
	XSpeed = incSpeed * cos(Conversions::DegreeToRadian(incVerticalAngle));
	YSpeed = incSpeed * sin(Conversions::DegreeToRadian(incVerticalAngle));
	ZSpeed = incSpeed * sin(Conversions::DegreeToRadian(incHorizontalAngle));
	
}

FlightSpeed::~FlightSpeed()
{
}

double FlightSpeed::getXComponent()
{
	return XSpeed;
}

double FlightSpeed::getYComponent()
{
	return YSpeed;
}

double FlightSpeed::getZComponent()
{
	return ZSpeed;
}


