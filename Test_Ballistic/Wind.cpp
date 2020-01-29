#include "Wind.h"
#include <math.h>


///<summary>Ruzgar hesaplamalarinin yapildigi nesne.</summary>
///<param name = "incSpeed">Hiz cinsinden deger</param>
///<param name = "incAngle">Aci cinsinden deger</param>
Wind::Wind(double incSpeed, double incAngle)
{
	Angle = incAngle;
	Speed = incSpeed;
	CalculateCrossWind(incAngle, incSpeed);
	CalculateHeadWind(incAngle, incSpeed);
}

Wind::Wind()
{
}

Wind::~Wind()
{
}

double Wind::getCrossWindSpeed()
{
	return CrossWindSpeed;
}

double Wind::getHeadWindSpeed()
{
	return HeadWindSpeed;
}

double Wind::getCrossWindSpeedinfeetpers()
{
	return CrossWindSpeed;
}

double Wind::getHeadWindSpeedinfeetpers()
{
	return HeadWindSpeed;
}

double Wind::getAngle()
{
	return this->Angle;
}

double Wind::getSpeed()
{
	return this->Speed;
}

///<summary>Yandan esen ruzgar hesaplamasini yapar</summary>
///<param name = "incAngle">Aci cinsinden deger</param>
///<param name = "incSpeed">Hiz cinsinden deger</param>
double Wind::CalculateCrossWind(double incAngle, double incSpeed)
{
	CrossWindSpeed = incSpeed * sin(Conversions::DegreeToRadian(incAngle));
	return CrossWindSpeed;
}

///<summary>Karsi yonden esen ruzgar hesaplamasini yapar.</summary>
///<param name = "incSpeed">Hiz cinsinden deger</param>
///<param name = "incAngle">Aci cinsinden deger</param>
double Wind::CalculateHeadWind(double incAngle, double incSpeed)
{
	HeadWindSpeed = incSpeed * cos(Conversions::DegreeToRadian(incAngle));
	return HeadWindSpeed;
}

void Wind::setAngle(double incAngle)
{
	Angle = incAngle;
	CalculateCrossWind(Angle, Speed);
	CalculateHeadWind(Angle, Speed);
}

void Wind::setSpeed(double incSpeed)
{
	Speed = incSpeed;
	CalculateCrossWind(Angle, Speed);
	CalculateHeadWind(Angle, Speed);
}
