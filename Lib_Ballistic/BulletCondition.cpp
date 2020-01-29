#include "BulletCondition.h"
#include "Lib_Ballistic_global.h"
///<summary>Mermi durumunu tanimlayan nesne.</summary>
///<param name = "incDistance">Uzaklik degeri</param>
///<param name = "incHeight">Yukseklik degeri</param>
///<param name = "incDeflection">Sapma degeri</param>
///<param name = "incTotalVelocity">Toplam surat degeri</param>
///<param name = "incTime">Sure degeri</param>
///<param name = "incVelocityX">X yonundeki surat degeri</param>
///<param name = "incVelocityY">Y younundeki surat degeri</param>
///<param name = "incVelocityZ">z younundeki surat degeri</param>
BulletCondition::BulletCondition(double incDistance, double incHeight, double incDeflection, double incTotalVelocity, double incTime, double incVelocityX, double incVelocityY, double incVelocityZ)
{
	Distance = incDistance;
	Height = incHeight;
	Deflection = incDeflection;
	TotalVelocity = incTotalVelocity;
	Time = incTime;
	VelocityX = incVelocityX;
	VelocityY = incVelocityY;
	VelocityZ = incVelocityZ;
}

BulletCondition::~BulletCondition()
{
}

double BulletCondition::getDistance()
{
	return Distance;
}

double BulletCondition::getHeight()
{
	return Height;
}

double BulletCondition::getDeflection()
{
	return Deflection;
}

double BulletCondition::getTotalVelocity()
{
	return TotalVelocity;
}

double BulletCondition::getTime()
{
	return Time;
}

double BulletCondition::getTheVelocityX()
{
	return VelocityX;
}

double BulletCondition::getTheVelocityY()
{
	return VelocityY;
}

double BulletCondition::getTheVelocityZ()
{
	return VelocityZ;
}
